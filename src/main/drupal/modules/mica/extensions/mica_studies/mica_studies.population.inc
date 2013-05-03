<?php

function _mica_studies_population_link($population) {
  // create a reference in study when a population is create for this study
  $population_wrapper = entity_metadata_wrapper('node', $population);
  $study = $population_wrapper->field_pop_study->value();
  //$study = node_load($study->nid);
  if (!empty($study)) {
    $study_wrapper = entity_metadata_wrapper('node', $study);
    $study_populations = $study_wrapper->field_study_populations->value();
    $nb_populations = count($study_populations);
    $study_wrapper->value()->field_study_populations[LANGUAGE_NONE][$nb_populations]['nid'][$population->nid] = $population->nid;
    $study_wrapper->save();
  }
}

function _mica_studies_population_delete($population) {

  $population_wrapper = entity_metadata_wrapper('node', $population);
  $population_id = $population_wrapper->nid->value();

  // suppress link in studies
  $query = new EntityFieldQuery;
  $entities = $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'study')
    ->execute();
  if (!empty($entities)) {
    $nodes = node_load_multiple(array_keys($entities['node']));
    foreach ($nodes as $node) {
      $study_populations = $node->field_study_populations;
      if (isset ($study_populations[LANGUAGE_NONE])) {
        $nb_populations = count($study_populations[LANGUAGE_NONE]);
        $value = array();
        $count = 0;
        for ($i = 0; $i < $nb_populations; $i++) {
          if ($study_populations[LANGUAGE_NONE][$i]['nid'] != $population_id) {

            $value[$count] = $study_populations[LANGUAGE_NONE][$i];
            $count++;
          }
        }
        if ($count != 0) {
          $node->field_study_populations[LANGUAGE_NONE] = $value;
          node_save($node);
        }
      }
    }
  }

  //suppress all data collection event associate to the population
  $query = new EntityFieldQuery;
  $entities = $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'data_collection_event')
    ->execute();
  if (!empty($entities)) {
    $nodes = node_load_multiple(array_keys($entities['node']));
    foreach ($nodes as $node) {
      $dce_wrapper = entity_metadata_wrapper('node', $node);
      $dce_pop = $dce_wrapper->field_dce_population->value();
      $dce_pop_id = $dce_pop->nid;
      if ($population_id == $dce_pop_id) {
        node_delete($dce_wrapper->nid->value());
      }
    }
  }

}

function _mica_studies_population_view($node, $view_mode, $langcode) {
  _mica_studies_population_view_selection_criteria($node);
  _mica_studies_population_view_recruitment_sources($node);
  _mica_studies_population_view_nb_participants($node);

  $wrapper = entity_metadata_wrapper('node', $node);

  $dce_rows = array();
  foreach ($wrapper->field_pop_dce->getIterator() as $dce_wrapper) {
    $start = $dce_wrapper->field_dce_start_date->value();
    $end = $dce_wrapper->field_dce_end_date->value();
    $summary = $dce_wrapper->body->summary->value();
    $dce_rows[] = array(
      l($dce_wrapper->title->value(), 'node/' . $dce_wrapper->nid->value()),
      empty($summary) ? truncate_utf8($dce_wrapper->body->value->value(), 50, TRUE, TRUE) : $summary,
      empty($start) ? '' : date("Y M", $start),
      empty($end) ? '' : date("Y M", $end),
    );
  }
  if (!empty($dce_rows)) {
    $node->content['data-collection-event'] = array(
      '#weight' => '100',
      '#theme' => 'table',
      '#caption' => t('Data Collection Events') . ': ',
      '#attributes' => array('class' => array('pop-dce')),
      '#header' => array(t('Name'), t('Description'), t('Start'), t('End')),
      '#rows' => $dce_rows,
    );
  }

  // Breadcrumbs
  $study_id = $wrapper->field_pop_study->nid->value();
  $breadcrumb = _mica_studies_menu_generate_breadcrumbs('node/' . $study_id);

  // generate specific breadcrumbs for population pages pages
  $breadcrumbs = array();
  $breadcrumbs[] = l(t('Home'), '');
  for ($i = 0; $i < count($breadcrumb); $i++) {
    $breadcrumbs[] = l($breadcrumb[$i]['link_title'], $breadcrumb[$i]['link_path']);
  }
  $breadcrumbs[] = l($wrapper->title->value(), 'node/' . $wrapper->nid->value());
  drupal_set_breadcrumb($breadcrumbs);
}

function _mica_studies_population_view_selection_criteria($node) {

  $wrapper = entity_metadata_wrapper('node', $node);

  if (!isset($node->content['field_pop_select_criteria'])) {
    // create empty field_pop_select_criteria if it has no values
    mica_core_create_empty_field($node, 'field_pop_select_criteria');
  }

  _mica_studies_population_view_selection_criteria_item($node, $wrapper, 'field_pop_gender', t('Gender'));

  if (isset($node->content['field_pop_age_min']) || isset($node->content['field_pop_age_max'])) {
    $index = count($node->content['field_pop_select_criteria']['#items']);
    $age_min = $wrapper->field_pop_age_min->value();
    $age_max = $wrapper->field_pop_age_max->value();
    if (!empty($age_min) || !empty($age_max)) {
      $age_items = array();
      $age_markup = '';
      if (!empty($age_min)) {
        $age_items['age_min'] = $node->content['field_pop_age_min']['#items'][0];
        $age_markup .= t('minimum') . ' ' . $node->content['field_pop_age_min'][0]['#markup'];
      }
      if (!empty($age_max)) {
        if (!empty($age_min)) {
          $age_markup .= ', ';
        }
        $age_items['age_max'] = $node->content['field_pop_age_max']['#items'][0];
        $age_markup .= t('maximum') . ' ' . $node->content['field_pop_age_max'][0]['#markup'];
      }
      $node->content['field_pop_age_max']['#access'] = FALSE;
      $node->content['field_pop_age_min']['#access'] = FALSE;
      $node->content['field_pop_select_criteria']['#items'][$index] = $age_items;

      $label_value = t('Age');
      $markup = ucfirst($age_markup);
      $node->content['field_pop_select_criteria'][$index]['#markup'] = "<div class='inner-label'>$label_value:</div>"
        . "<div class='inner-value'>$markup</div>";
    }
  }

  _mica_studies_population_view_selection_criteria_item($node, $wrapper, 'field_pop_country', t('Country'), t('Countries'));
  _mica_studies_population_view_selection_criteria_item($node, $wrapper, 'field_pop_territory', t('Territory'), t('Territories'));
  _mica_studies_population_view_selection_criteria_item($node, $wrapper, 'field_pop_ethnic_origin', t('Ethnic origin'), t('Ethnic origins'));
  _mica_studies_population_view_selection_criteria_item($node, $wrapper, 'field_pop_health_status', t('Health status'));
  _mica_studies_population_view_selection_criteria_item($node, $wrapper, 'field_pop_selection_others_sp', t('Other'));

  if (strlen($node->content['field_pop_select_criteria'][0]['#markup']) === 0) {
    $node->content['field_pop_select_criteria']['#access'] = FALSE;
  }
}

function _mica_studies_population_view_selection_criteria_item(&$node, $wrapper, $field, $label, $label_plural = '') {
  if (!isset($node->content[$field])) {
    return;
  }
  $value = $wrapper->$field->value();
  if (!empty($value)) {
    $nb_items = count($value);
    $index = count($node->content['field_pop_select_criteria']['#items']);
    $node->content['field_pop_select_criteria']['#items'][$index] = $node->content[$field]['#items'];
    $markup = '<div class="inner-value">';
    for ($i = 0; $i < $nb_items; $i++) {
      $markup .= $node->content[$field][$i]['#markup'];
      if ($i < $nb_items - 1) {
        $markup .= ', ';
      }
    }
    $markup .= '</div>';

    $node->content['field_pop_select_criteria'][$index]['#markup'] = '<div class="inner-label">'
      . t('@label', array('@label' => $nb_items > 1 && strlen($label_plural) > 0 ? $label_plural : $label)) . ':</div>'
      . $markup;
    $node->content[$field]['#access'] = FALSE;
  }
}

function _mica_studies_population_view_recruitment_sources(&$node) {

  $wrapper = entity_metadata_wrapper('node', $node);

  if (!isset($node->content['field_pop_src_recruit'])) {
    // create empty field_pop_src_recruit if it has no values
    mica_core_create_empty_field($node, 'field_pop_src_recruit');
  }

  $src_recruit = $wrapper->field_pop_src_recruit->value();

  $general_index = array_search('general', $src_recruit);
  if ($general_index !== FALSE) {
    $field_pop_general_pop_recruit = $wrapper->field_pop_general_pop_recruit->value();
    if (!empty($field_pop_general_pop_recruit)) {
      $nb = count($field_pop_general_pop_recruit);
      $content = array();
      for ($i = 0; $i < $nb; $i++) {
        $content[] = $node->content['field_pop_general_pop_recruit'][$i]['#markup'];
      }
      $node->content['field_pop_src_recruit'][$general_index]['#markup'] = '<div class="inner-label">'
        . $node->content['field_pop_src_recruit'][$general_index]['#markup']
        . ':</div><div class="inner-value">'
        . implode(', ', $content)
        . '</div>';
      $node->content['field_pop_general_pop_recruit']['#access'] = FALSE;
    }
  }

  $exist_studies_index = array_search('exist_studies', $src_recruit);
  if ($exist_studies_index !== FALSE) {
    $field_pop_exist_study_part = $wrapper->field_pop_exist_study_part->value();
    if (!empty($field_pop_exist_study_part)) {
      $nb = count($field_pop_exist_study_part);
      $content = array();
      for ($i = 0; $i < $nb; $i++) {
        $content[] = $node->content['field_pop_exist_study_part'][$i]['#markup'];
      }
      $node->content['field_pop_src_recruit'][$exist_studies_index]['#markup'] = '<div class="inner-label">'
        . $node->content['field_pop_src_recruit'][$exist_studies_index]['#markup']
        . ':</div><div class="inner-value">'
        . implode(', ', $content)
        . '</div>';
      $node->content['field_pop_exist_study_part']['#access'] = FALSE;
    }
  }

  $specific_population_index = array_search('specific_population', $src_recruit);
  if ($specific_population_index !== FALSE) {
    $field_pop_specific_pop = $wrapper->field_pop_specific_pop->value();
    if (!empty($field_pop_specific_pop)) {

      $other_index = array_search('other', $field_pop_specific_pop);
      if ($other_index !== FALSE) {
        $field_pop_specific_pop_other_sp = $wrapper->field_pop_specific_pop_other_sp->value();
        if (!empty($field_pop_specific_pop_other_sp)) {
          $nb = count($field_pop_specific_pop_other_sp);
          $content = array();
          for ($i = 0; $i < $nb; $i++) {
            $content[] = $node->content['field_pop_specific_pop_other_sp'][$i]['#markup'];
          }
          $node->content['field_pop_specific_pop'][$other_index]['#markup'] .= ' (' . implode(', ', $content) . ')';
          $node->content['field_pop_specific_pop_other_sp']['#access'] = FALSE;
        }
      }

      $nb = count($field_pop_specific_pop);
      $content = array();
      for ($i = 0; $i < $nb; $i++) {
        $content[] = $node->content['field_pop_specific_pop'][$i]['#markup'];
      }
      $node->content['field_pop_src_recruit'][$specific_population_index]['#markup'] = '<div class="inner-label">'
        . $node->content['field_pop_src_recruit'][$specific_population_index]['#markup']
        . ':</div><div class="inner-value">'
        . implode(', ', $content)
        . '</div>';
      $node->content['field_pop_specific_pop']['#access'] = FALSE;
    }
  }

  $other_index = array_search('other', $src_recruit);
  if ($other_index !== FALSE) {
    $field_pop_recruitment_other = $wrapper->field_pop_recruitment_other->value();
    if (!empty($field_pop_recruitment_other)) {
      $node->content['field_pop_src_recruit'][$other_index]['#markup'] = '<div class="inner-label">'
        . $node->content['field_pop_src_recruit'][$other_index]['#markup']
        . ':</div><div class="inner-value">'
        . $node->content['field_pop_recruitment_other'][0]['#markup']
        . '</div>';
      $node->content['field_pop_recruitment_other']['#access'] = FALSE;
    }
  }

  if (strlen($node->content['field_pop_src_recruit'][0]['#markup']) === 0) {
    $node->content['field_pop_src_recruit']['#access'] = FALSE;
  }

}

function _mica_studies_population_view_nb_participants(&$node) {
  _mica_studies_population_view_nb($node, 'field_pop_participants_nb', 'field_pop_no_limits_participants', 'field_pop_participants_nb_supp_i');
  _mica_studies_population_view_nb($node, 'field_pop_participants_nb_s', 'field_pop_no_lim_participants_s', 'field_pop_participants_nb_s_info');
}

function _mica_studies_population_view_nb(&$node, $field_nb, $field_no_limit, $field_info) {
  $wrapper = entity_metadata_wrapper('node', $node);
  if (!isset($node->content[$field_nb])) {
    mica_core_create_empty_field($node, $field_nb);
  }

  $index = count($node->content[$field_nb]['#items']);

  $no_limit = $wrapper->{$field_no_limit}->value();
  if ($no_limit) {
    $node->content[$field_nb]['#items'][$index] = t('No limit');
    $node->content[$field_nb][$index]['#markup'] = t('No limit');
    $index++;
  }
  $node->content[$field_no_limit]['#access'] = FALSE;

  $info = $wrapper->{$field_info}->value();
  if (!empty($info)) {
    $node->content[$field_nb]['#items'][$index] = $node->content[$field_info]['#items'][0];
    $node->content[$field_nb][$index]['#markup'] = $node->content[$field_info][0]['#markup'];
  }
  $node->content[$field_info]['#access'] = FALSE;

  if (strlen($node->content[$field_nb][0]['#markup']) == 0) {
    $node->content[$field_nb]['#access'] = FALSE;
  }
}
<?php

/**
 * @file
 * Home of the FeedsHTTPFetcher and related classes.
 */

/**
 * A RESTful fetcher. Allows overriding many parts of the underlying http request.
 */
class FeedsOpalFetcher extends FeedsRestFetcher {

  /**
   * Implements FeedsFetcher::fetch().
   */
  public function fetch(FeedsSource $source) {
    $source_config = $source->getConfigFor($this);

    $nid = $source_config['mica_dataset_connector'];
    $source_config['source'] = $this->makeUri($nid);
    $source->setConfigFor($this, $source_config);
    
    return parent::fetch($source);
  }

  public function sourceForm($source_config) {
    $form = parent::sourceForm($source_config);
    if(isset($source_config['mica_dataset_connector'])) {
      $form['source']['#default_value'] = $this->makeUri($source_config['mica_dataset_connector']);
      $form['source']['#disabled'] = TRUE;
    }
    return $form;
  }

  private function makeUri($connectorId) {
    $connector = mica_dataset_connector_load($connectorId);
    $study_node = node_load($connector->study_id);
    $url = $study_node->mica_opal[$study_node->language][0]['url'];
    $url .= "/ws/datasource/" . $connector->options['datasource'] . '/table/' . $connector->options['table'] . '/variables';
    return $url;
  }
}
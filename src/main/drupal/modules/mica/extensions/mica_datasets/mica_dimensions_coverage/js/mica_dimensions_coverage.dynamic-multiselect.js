(function ($) {
  Drupal.behaviors.datatables_multislect = {
    attach: function (context, settings) {
      $(window).load(function () {
        $(".loader").fadeOut("slow");
      });

      /*Multiselect event populate DCE Multiselect Field */
      $("#edit-studies").multiselectfilter("destroy");
      $("#edit-studies").multiselect({
        minWidth: 350,
        selectedText: function (numChecked, numTotal) {
          return Drupal.t('@numChecked of @numTotal checked', {'@numChecked': numChecked, '@numTotal': numTotal});
        },
        close: function () {
          perform_search();
        }


      });
      $("#edit-studies").multiselect().multiselectfilter({
        label: Drupal.t('Search:'),
        width: 250, /* override default width set in css file (px). null will inherit */
        placeholder: Drupal.t('Studies filter by title'),
        autoReset: true
      });



      $("#edit-dataset").multiselectfilter("destroy");
      $("#edit-dataset").multiselect({
        selectedText: function (numChecked, numTotal) {
          return Drupal.t('@numChecked of @numTotal checked', {'@numChecked': numChecked, '@numTotal': numTotal});
        },
        close: function () {
          perform_search();
        }
      });

      /*********************perform search action *************/
      /**********Ajax function to populate Multiselect DCE options *****/
      function perform_search() {
        $(".loader").fadeIn("slow");
        var studies = [];
        studies.push($("input[name=multiselect_edit-studies]:checked").map(function () {return this.value;}).get().join(","));
        var dataset = studies.push($("input[name=multiselect_edit-dataset]:checked").map(function () {return this.value;}).get().join(","));
        if (studies != "") {
          document.forms["mica-dimensions-coverage-filter-form"].submit();
        }
        if (dataset != "") {
          document.forms["mica-dimensions-coverage-filter-form"].submit();
        }
      }

      /*****************************************************/
      /********************action in select deselect checkbox*************/
      $('#edit-show-dce').on('change', function () {
        perform_search()
      });
      /********************************************************************/
    }
  }
})(jQuery);
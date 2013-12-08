<?php

/**
 * @file
 * Hooks invoked by the Project Source API.
 */


/**
 * Implements hook_project_src_terms().
 *
 * Ensures that the project type term is populated for the given project (this
 * is the value used by drush to determine installation location).
 */
function project_src_project_src_terms($term_type, $short_name, $api_version, $project) {
  $terms = array();

  if ($term_type == 'project') {
    $settings = variable_get('project_src_project_settings', array());
    if (isset($settings[$short_name]['type'])) {
      $terms[] = array(
        'Projects',
        _project_src_type_to_string($settings[$short_name]['type'], 'term'),
      );
    }
  }

  return $terms;
}

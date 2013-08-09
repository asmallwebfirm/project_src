<?php

/**
 * @file
 * Hooks invoked by the Project Source API.
 */


/**
 * Implements hook_project_src_terms().
 *
 * Provides default term output for projects because it's unlikely that most VCS
 * backends provide enough metadata through their APIs to provide term info.
 */
function project_src_project_src_terms($type, $short_name, $api_version, $info) {
  $terms = array();

  /*switch ($type) {
    case 'project':
      $terms = array(
        array('Projects', 'Modules'),
        array('Development status', 'Under active development'),
      );
      break;

    case 'release':
      $terms = array(
        array('Release type', 'New features'),
        array('Release type', 'Bug fixes'),
      );
      break;
  }*/

  return $terms;
}

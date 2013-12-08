<?php

/**
 * @file
 * Private functions used by the Project Source module. These functions should
 * not be used by any other module; no API compatibility is guaranteed.
 */


/**
 * Acts like an implementation of hook_project_src_info_alter(), but actually
 * isn't. This is done so that other modules are able to easily alter the
 * project-specific settings stored by this module without having to deal with
 * module weighting.
 */
function project_src_apply_settings(&$projects, $include_hidden = FALSE) {
  $settings = variable_get('project_src_project_settings', array());

  // Iterate through all projects.
  foreach ($projects as $api => &$project_list) {
    foreach ($project_list as $name => &$project) {
      // If the project is meant to be hidden, unset it and continue.
      if (!$include_hidden && isset($settings[$name]['hidden']) && $settings[$name]['hidden']) {
        unset($projects[$api][$name]);

        // If we just unset the last project for this API version, unset it too.
        if (empty($projects[$api])) {
          unset($projects[$api]);
        }

        continue;
      }

      // Apply the configured project type.
      if (isset($settings[$name]['type'])) {
        $project['type'] = $settings[$name]['type'];
      }
    }
  }
}


/**
 * Maps Drupal extension type machine names with several human-readable variants
 * used in different contexts.
 *
 * @param string $type
 *   (Optional) The machine name of the type of Drupal extension. If none is
 *   provided, the whole map is returned as an array.
 * @param string $translation
 *   (Optional) The type of human-readable string to return for the given type.
 *   If none is provided, then all mappings will be returned as an array.
 *
 * @return string|array
 *   If both arguments are provided, the desired string will be returned if it
 *   was found, or an empty string on failure. If only a type is specified, all
 *   mappings for the given type will be returned as an array, or an empty array
 *   will be returned on failure. If no arguments are provided, the full map
 *   will be returned.
 */
function _project_src_type_to_string($type = NULL, $translation = NULL) {
  $map = array(
    'project_module' => array(
      'title' => t('Module'),
      'term' => 'Modules',
    ),
    'project_theme' => array(
      'title' => t('Theme'),
      'term' => 'Themes',
    ),
    'project_theme_engine' => array(
      'title' => t('Theme engine'),
      'term' => 'Theme engines',
    ),
    'project_distribution' => array(
      'title' => t('Distribution'),
      'term' => 'distributions',
    ),
  );

  if ($type) {
    if ($translation) {
      return isset($map[$type][$translation]) ? $map[$type][$translation] : '';
    }
    else {
      return isset($map[$type]) ? $map[$type] : array();
    }
  }
  else {
    return $map;
  }
}

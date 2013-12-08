<?php

/**
 * @file
 * Admin hooks and functions for the Project Source module.
 */


/**
 * Admin form for the Project Source module.
 */
function project_src_settings($form_state) {
  $form = array();

  // A fieldset to house project-specific configurations.
  $form['project_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Project settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  // Get all projects and reduce all API versions to a single list of projects.
  $all_projects = project_src_get_projects(NULL, NULL, TRUE);
  $projects = array();
  foreach ($all_projects as $api_version) {
    $projects += $api_version;
  }

  if (!empty($projects)) {
    $delta = 0;
    $settings = variable_get('project_src_project_settings', array());
    ksort($projects);

    $form['project_settings']['settings_table'] = array(
      '#theme' => 'project_src_settings_table',
    );

    foreach ($projects as $name => $project) {
      $project_settings = isset($settings[$name]) ? $settings[$name] : array();
      $form['project_settings']['settings_table'][++$delta] = project_src_settings_row($project, $project_settings);
    }

    // Add a submit handler to save our master variable.
    $form['#submit'][] = 'project_src_settings_table_submit';
  }
  else {
    $link = 'https://drupal.org/project/project_src';
    $empty = '<p>' . t('No projects were found! Please install and configure a !integration_module to get started.', array(
      '!integration_module' => l(t('Project Source integration module'), $link),
    ));
    $form['project_settings']['#description'] = $empty;
  }

  return system_settings_form($form);
}

/**
 * Submit handler for the project table configuration.
 */
function project_src_settings_table_submit($form, &$form_state) {
  $variable = 'project_src_project_settings';
  variable_set($variable, $form_state['input'][$variable]);
}


/**
 * Builds a project settings row of form elements.
 *
 * @param array $project
 *   The definition of the given project.
 * @param array $settings
 *   The existing settings for the given project.
 *
 * @return array
 *   A form API element renderable by our settings table theme function.
 */
function project_src_settings_row($project, $settings) {
    $form['project'] = array(
    '#type' => 'html_tag',
    '#tag' => 'strong',
    '#value' => check_plain($project['title']),
  );

  // Build the options array.
  $options = _project_src_type_to_string();
  foreach ($options as $key =>&$option) {
    $options[$key] = $option['title'];
  }

  $form['type'] = array(
    '#type' => 'select',
    '#name' => 'project_src_project_settings[' . $project['short_name'] . '][type]',
    '#options' => $options,
    '#default_value' => isset($settings['type']) ? $settings['type'] : NULL,
  );

  $form['hidden'] = array(
    '#type' => 'checkbox',
    '#name' => 'project_src_project_settings[' . $project['short_name'] . '][hidden]',
    '#default_value' => isset($settings['hidden']) ? $settings['hidden'] : FALSE,
  );

  return $form;
}


/**
 * Themes Project Source custom settings tables.
 */
function theme_project_src_settings_table($variables) {
  $form = $variables['form'];
  $rows = array();
  foreach (element_children($form) as $key) {
    $rows[$key] = array(
      'data' => array(
        drupal_render($form[$key]['project']),
        drupal_render($form[$key]['type']),
        drupal_render($form[$key]['hidden']),
      ),
    );
  }

  $headers = array(
    t('Project'),
    t('Type'),
    t('Hidden'),
  );

  return theme('table', array('header' => $headers, 'rows' => $rows));
}

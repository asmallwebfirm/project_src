<?php


/**
 * Returns an array of custom project definitions keyed by project short name,
 * nested in an array of supported API versions. The exact makeup of the project
 * definition is up to you, but by default, its contents will be passed directly
 * to the main project XML theme function.
 *
 * It's recommended that project definitions contain the following info:
 * - title: The human-readable name for the specified project,
 * - short_name: The Drupal project short name for the specified project,
 * - creator: A string representing the project's original author,
 * - api_version: The Drupal API version supported by the project (e.g. 7.x),
 * - link: A fully qualified URL representing the project page,
 * - project_status: The current project status (e.g. "published"),
 * - recommended_major: The recommended major version of the project. For
 *   instance, if you would like to recommend your 7.x-2.x branche you would
 *   want to return "2" here,
 * - supported_majors: A comma seperated list of supported major versions,
 * - default_major: The default major version of the project. If the default
 *   branch for the project was 7.x-2.x, you would return "2" here.
 *
 * @return array
 *   See above for details.
 *
 * @see project_src_get_projects()
 */
function hook_project_src_info() {
  // Define a 7.x API compatible version of a Views module fork.
  $projects['7.x']['my_views_fork'] = array(
    'title' => 'My Views Fork', 
    'short_name' => 'my_views_fork',
    'creator' => 'notmerlinofchaos',
    'api_version' => '7.x',
    'project_status' => 'published',
    'link' => 'http://example.com/project/my_views_fork',
    'recommended_majors' => 3,
    'supported_majors' => 3,
    'default_major' => 3,
  );

  return $projects;
}

/**
 * Allows you to modify project definitions at runtime.
 *
 * @param array &$projects
 *   An array of projects exactly as described in hook_project_src_info(). Note
 *   that this is called for all projects and when projects are loaded on a
 *   module-by-module basis. In both cases, they're passed with API version keys
 *   at the top level.
 */
function hook_project_src_info_alter(&$projects) {
  // Maybe for some reason, we want to translate the title.
  $projects['7.x']['my_views_fork']['title'] = t('My Views Fork');
}


/**
 * Returns an array of release definitions for a given project and API version,
 * keyed by version.
 *
 * The exact makeup of release definitions, like project definitions, is up to
 * you, but by default, its contents will be passed directly to the project
 * release XML theme function.
 *
 * It's recommended that release definitions contain the following info:
 * - name: The human readable name of the release; for reference, Drupal.org
 *   uses a concatenation of project short name and release version (tag),
 * - version: The version of the release (e.g. 7.x-1.0),
 * - tag: The tag associated with this release (often the same as "version"),
 * - date: The UNIX timestamp representing when the release was made available,
 * - version_major: The major version associated with the release. For example,
 *   if the tag for the release is 7.x-2.3, you would use "2" here,
 * - version_patch: The minor version associated with the release. Using the
 *   above 7.x-2.3 example, you would use "3" here,
 * - status: The status of the release (e.g. "published"),
 * - release_link: A fully qualified URL representing the release,
 * - download_link: A fully qualified URL representing a packaged archive of the
 *   project,
 * - archive_type: The type of archive, represented as a file extension (e.g
 *   "tar.gz" or "zip"),
 * - filesize: The size, in bytes, of the packaged release archive,
 * - mdhash: The md5 checksum of the packaged release archive.
 *
 * @param string $short_name
 *   The short name of the project.
 *
 * @param string $api_version
 *   The Drupal API version of the project (e.g. 7.x).
 *
 * @param array $info
 *   The $info array for this particular project/API version combination as
 *   provided by your hook_project_src_info() implementation.
 *
 * @return array
 *   See above for details.
 */
function hook_project_src_releases($short_name, $api_version, $info) {
  // The 7.x-3.0 release of My Views Fork.
  $releases['7.x']['my_views_fork']['7.x-3.0'] = array(
    'name' => 'my_views_fork 7.x-3.0',
    'version' => '7.x-3.0',
    'tag' => '7.x-3.0',
    'date' => 1345423902,
    'version_major' => 3,
    'version_patch' => 0,
    'status' => 'published',
    'release_link' => 'http://example.com/project/my_views_fork/releases/7.x-3.0',
    'download_link' => 'http://ftp.example.com/files/projects/my_views_fork-7.x-3.0.tar.gz',
    'archive_type' => 'tar.gz',
    'filesize' => '10132',
    'mdhash' => '675288f8194d9eb34c28f2f7cffab8ad',
  );

  // Potentially some other releases...
  $releases['7.x']['my_views_fork']['7.x-3.1'] = array(...);
  $releases['6.x']['my_other_module']['6.x-2.1'] = array(...);

  $available = isset($releases[$api_version][$short_name]);
  return $available ? $releases[$api_version][$short_name] : array();
}


/**
 * Allows you to modify release definitions at runtime.
 *
 * @param array &$releases
 *   An array of releases exactly as described in hook_project_src_releases().
 *   that this is called for all projects and when projects are loaded on a
 *   module-by-module basis. In both cases, they're passed with API version keys
 *   at the top level.
 *
 * @param array $info
 *   The $info array for this particular project/API version combination as
 *   provided by your hook_project_src_info() implementation (used for context).
 */
function hook_project_src_releases_alter(&$releases, $info) {
  // Maybe for some reason, we want to translate the title.
  $projects['7.x']['my_views_fork']['title'] = t('My Views Fork');
}


/**
 * Returns an array of term definitions for a given project or release.
 *
 * A term definition is a simple enumerated array where the 0th value is the
 * term name and the 1st value is the term value.
 *
 * @param string $type
 *   The type of term to return (one of "project" or "release").
 *
 * @param string $short_name
 *   The short name of the project.
 *
 * @param string $api_version
 *   The Drupal API version of the project (e.g. 7.x).
 *
 * @param array $info
 *   The $info array for this particular project/API version combination as
 *   provided by your hook_project_src_info() implementation.
 *
 * @return array
 *   An array of term definitions; each term definition is a simple enumerated
 *   array whose 0th value is the term name and whose 1st value is the term
 *   value. See code examples below.
 */
function hook_project_src_terms($type, $short_name, $api_version, $info) {
  // My Views Fork is a very buggy module; all releases are bug fixes.
  if ($type == 'release' && $short_name = 'my_views_fork') {
    return array(
      array('Release type', 'Bug fixes'),
    );
  }
}


/**
 * Allows you to modify term definitions at runtime.
 *
 * @param array &$releases
 *   An array of releases exactly as described in hook_project_src_releases().
 *   that this is called for all projects and when projects are loaded on a
 *   module-by-module basis. In both cases, they're passed with API version keys
 *   at the top level.
 *
 * @param array $info
 *   The $info array for this particular project/API version combination as
 *   provided by your hook_project_src_info() implementation (used for context).
 *
 * @param string $type
 *   The type of term being processed (used for context).
 */
function hook_project_src_terms_alter(&$terms, $info, $type) {
  // Maybe for some reason, we want to translate the title.
  $projects['7.x']['my_views_fork']['title'] = t('My Views Fork');
}

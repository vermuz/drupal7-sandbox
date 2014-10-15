<?php
/**
 * @file
 * CRUD Functions
 */

/**
 * Read entries from the Database and load them.
 */
/*
function jdt_user_notes_entry_load($entry = array()) {
  $select = db_select('user_note', 'drupal7_development');
  $select->fields('drupal7_development');
  // Add each field and value as a condition to this query.
  foreach ($entry as $field => $value) {
    $select->condition($field, $value);
  }
  // Return the result in object format.
  return $select->execute()->fetchAll();
}*/

/**
 * Read entries from the Database and load them.
 */
function jdt_user_notes_entry_load($node_id, $user_id) {
  $result = db_select('user_note', 'n')
   ->fields('n')
   ->condition('article_nid', $node_id, "=")
   ->condition('author_uid', $user_id, "=")
   ->execute()
   ->fetchAssoc();
   return $result;
}

/**
 * Function to insert values into DB.
 */
function jdt_user_notes_insert($entry) {
  $return_value = NULL;
  try {
    $return_value = db_insert('user_note')
      ->fields($entry)
       ->execute();
  }
  catch(Exception $e) {
    drupal_set_message(t('db_insert failed. Message = %message, query= %query',
    array('%message' => $e->getMessage(), '%query' => $e->query_string)), 'error');
  }
  return $return_value;
}

/**
 * Function to delete entries from DB.
 */
function jdt_user_notes_delete($entry) {
  db_delete('user_note')
    ->condition('note_id', $entry['note_id'])
    ->execute();
}

/**
 * Function to edit entries from DB.
 */
function jdt_user_notes_update($entry) {
  try {
    // db_update()...->execute() returns the number of rows updated.
    $count = db_update('user_note')
      ->fields($entry)
      ->condition('note_id', $entry['note_id'])
      ->execute();
  }
  catch (Exception $e) {
    drupal_set_message(t('db_update failed. Message = %message, query= %query',
      array('%message' => $e->getMessage(), '%query' => $e->query_string)), 'error');
  }
  return $count;
}

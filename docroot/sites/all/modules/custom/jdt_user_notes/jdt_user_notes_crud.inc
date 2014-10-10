<?php
/**
 * @file
 * CRUD Functions
 */

/**
 * Read entries from the Database and load them.
 */
function jdt_user_notes_entry_load($entry = array()) {
  //$select = db_select('user_note', 'drupal7_development');
  $select = db_select('user_note','n');
  $select->fields('n');
  // Add each field and value as a condition to this query.
  foreach ($entry as $field => $value) {
    $select->condition($field, $value);
  }
  // Return the result in object format.
  return $select->execute()->fetchAll();
}

/**
 * Function to insert values into DB.
 */
function jdt_user_notes_insert($entry) {
  //$return_value = NULL;
  //$status = FALSE;
  try {
    db_insert('user_note')
      ->fields($entry)
      ->execute();
    //$status = TRUE;
    return TRUE;
  }
  catch (PDOException $e) {
    //$status = FALSE;
    //watchdog(
    //);
    watchdog('jdt_user_notes',
      'db_insert failed in user_note table, query=%query',
      array('%query' => $e->query_string),
      WATCHDOG_INFO
    );
  }
  //return $return_value;
  //return $status;
  return FALSE;
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
    watchdog('jdt_user_notes',
      'db_update failed in user_note table, query=%query',
      array('%query' => $e->query_string),
      WATCHDOG_INFO
    );
  }
  return $count;
}

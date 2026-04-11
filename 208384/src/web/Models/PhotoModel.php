<?php
require_once __DIR__ . '/../config/db.php';

function save_photo_to_db($title, $author, $fileName) {
    $db = get_db();
    $bulk = new MongoDB\Driver\BulkWrite;
    
    $doc = [
        'title' => $title,
        'author' => $author,
        'filename' => $fileName,
        'created_at' => date('Y-m-d H:i:s')
    ];

    $bulk->insert($doc);
    $db->executeBulkWrite('wai.photos', $bulk);
}

function get_all_photos($page = 1, $limit = 3) {
    $db = get_db();
    $options = [
        'limit' => $limit,
        'skip' => ($page - 1) * $limit,
        'sort' => ['created_at' => -1]
    ];
    
    $query = new MongoDB\Driver\Query([], $options);
    return $db->executeQuery('wai.photos', $query);
}

function count_photos() {
    $db = get_db();
    $command = new MongoDB\Driver\Command(["count" => "photos"]);
    
    try {
        $res = $db->executeCommand('wai', $command);
        return $res->toArray()[0]->n;
    } catch (Exception $e) {
        return 0;
    }
}

function get_photos_by_ids($idArray) {
    if (empty($idArray)) {
        return [];
    }

    $db = get_db();
    $ids = [];
    
    foreach ($idArray as $id) {
        try {
            $ids[] = new MongoDB\BSON\ObjectId($id);
        } catch (Exception $e) {
            continue; 
        }
    }

    $filter = ['_id' => ['$in' => $ids]];
    $query = new MongoDB\Driver\Query($filter);
    
    return $db->executeQuery('wai.photos', $query);
}
?>
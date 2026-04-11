<?php
require_once __DIR__ . '/../config/db.php';

function get_user_by_login($login) {
    $db = get_db();
    $query = new MongoDB\Driver\Query(['login' => $login]);
    $cursor = $db->executeQuery('wai.users', $query);
    $users = $cursor->toArray();
    return count($users) > 0 ? $users[0] : null;
}

function save_user($login, $password_hash, $email, $profile_image) {
    $db = get_db();
    $bulk = new MongoDB\Driver\BulkWrite;
    
    $doc = [
        'login' => $login,
        'password' => $password_hash,
        'email' => $email,
        'profile_image' => $profile_image, 
        'created_at' => date('Y-m-d H:i:s')
    ];

    $bulk->insert($doc);
    $db->executeBulkWrite('wai.users', $bulk);
}
?>
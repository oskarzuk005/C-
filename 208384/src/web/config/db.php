<?php
function get_db() {
    $mongoHost = '127.0.0.1';
    $mongoPort = '27017';
    $mongoUser = 'wai_web';
    $mongoPass = 'w@i_w3b';
    $mongoDb   = 'wai';

    $encodedPass = urlencode($mongoPass);
    $encodedUser = urlencode($mongoUser);

    $connectionString = "mongodb://$encodedUser:$encodedPass@$mongoHost:$mongoPort/$mongoDb";
    
    try {
        $manager = new MongoDB\Driver\Manager($connectionString);
        return $manager;
    } catch (Exception $e) {
        die("Błąd połączenia z bazą: " . $e->getMessage());
    }
}
?>
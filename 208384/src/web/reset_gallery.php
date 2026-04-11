<?php
require_once 'config/db.php';
session_start();

$db = get_db();
$bulk = new MongoDB\Driver\BulkWrite;

$bulk->delete([]); 
$db->executeBulkWrite('wai.photos', $bulk);

$bulkUsers = new MongoDB\Driver\BulkWrite;
$bulkUsers->delete([]); 
$db->executeBulkWrite('wai.users', $bulkUsers);

session_destroy();

echo "<h1>Wielkie Czyszczenie Zakończone!</h1>";
echo "<ul>";
echo "<li>Baza zdjęć (wai.photos) została wyczyszczona.</li>";
echo "<li>Baza użytkowników (wai.users) została wyczyszczona.</li>";
echo "<li>Zostałeś wylogowany.</li>";
echo "</ul>";

echo "<div style='background: #ffdddd; padding: 15px; border: 1px solid red;'>";
echo "<strong>PAMIĘTAJ!</strong> Baza danych jest pusta, ale pliki zostały na dysku.<br>";
echo "Wejdź teraz ręcznie do folderów na Macu i usuń zawartość:<br>";
echo "1. <code>src/web/images/</code> (zostaw folder 'min')<br>";
echo "2. <code>src/web/images/min/</code><br>";
echo "3. <code>src/web/ProfilesFoto/</code><br>";
echo "</div>";

echo "<br><a href='index.php'>Wróć do strony głównej</a>";
?>
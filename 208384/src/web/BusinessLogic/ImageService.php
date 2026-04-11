<?php
function process_upload($file, $title, $author) {
    $uploadDir = __DIR__ . '/../images/'; 
    $thumbDir = __DIR__ . '/../images/min/'; 
    
    // Walidacja formatu jpg/png
    $allowedTypes = ['image/jpeg', 'image/png'];
    if (!in_array($file['type'], $allowedTypes)) {
        return "Niedozwolony format pliku! Tylko JPG i PNG.";
    }

    // Walidacja rozmiaru 1 MB
    if ($file['size'] > 1048576) {
        return "Plik jest za duży! Maksymalnie 1MB.";
    }

    $fileName = uniqid() . "_" . basename($file['name']);
    $targetPath = $uploadDir . $fileName;

    if (move_uploaded_file($file['tmp_name'], $targetPath)) {
        // Generowanie miniatury 
        create_thumbnail($targetPath, $thumbDir . $fileName, $file['type']);
        
        // Zapis do bazy
        save_photo_to_db($title, $author, $fileName);
        
        return true;
    } else {
        return "Błąd zapisu pliku. Sprawdź folder images!";
    }
}

function create_thumbnail($src, $dest, $type) {
    list($width, $height) = getimagesize($src);
    $newWidth = 200;
    $newHeight = 125;

    $thumb = imagecreatetruecolor($newWidth, $newHeight);
    
    if ($type == 'image/jpeg') {
        $source = imagecreatefromjpeg($src);
    } else {
        $source = imagecreatefrompng($src);
    }

    imagecopyresampled($thumb, $source, 0, 0, 0, 0, $newWidth, $newHeight, $width, $height);

    if ($type == 'image/jpeg') {
        imagejpeg($thumb, $dest);
    } else {
        imagepng($thumb, $dest);
    }
}
?>
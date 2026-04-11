<?php
// Funkcja generująca miniatury 
function createThumbnail($source, $dest, $targetW, $targetH) {
    $info = getimagesize($source);
    $img = ($info[2] == IMAGETYPE_PNG) ? imagecreatefrompng($source) : imagecreatefromjpeg($source);
    
    $thumb = imagecreatetruecolor($targetW, $targetH);
    imagecopyresampled($thumb, $img, 0, 0, 0, 0, $targetW, $targetH, $info[0], $info[1]);
    
    ($info[2] == IMAGETYPE_PNG) ? imagepng($thumb, $dest) : imagejpeg($thumb, $dest);
    
    imagedestroy($img);
    imagedestroy($thumb);
}
<?php
require_once __DIR__ . '/../Models/UserModel.php';

function register_user($login, $email, $pass, $repeat_pass, $file) {
    // Walidacja haseł
    if ($pass !== $repeat_pass) {
        return "Hasła nie są identyczne!";
    }

    // Sprawdzenie czy login wolny
    if (get_user_by_login($login)) {
        return "Podany login jest już zajęty!";
    }

    // Obsługa zdjęcia profilowego
    $allowedTypes = ['image/jpeg', 'image/png'];
    if (!in_array($file['type'], $allowedTypes)) {
        return "Zły format zdjęcia (tylko JPG/PNG)!";
    }
    
    // Sprawdzenie czy folder istnieje
    $uploadDir = __DIR__ . '/../ProfilesFoto/';
    if (!is_dir($uploadDir)) {
        return "Błąd serwera: brak folderu ProfilesFoto!";
    }

    $ext = pathinfo($file['name'], PATHINFO_EXTENSION);
    $fileName = "profile_" . uniqid() . "." . $ext;
    $targetPath = $uploadDir . $fileName;

    if (!move_uploaded_file($file['tmp_name'], $targetPath)) {
        return "Błąd zapisu zdjęcia na serwerze!";
    }

    // Zapis do bazy 
    $hash = password_hash($pass, PASSWORD_DEFAULT);
    save_user($login, $hash, $email, $fileName);
    
    return true;
}

function login_user($login, $pass) {
    $user = get_user_by_login($login);

    if ($user && password_verify($pass, $user->password)) {
        session_regenerate_id();
        
        $_SESSION['user_id'] = (string)$user->_id;
        $_SESSION['user_login'] = $user->login;
        

        $_SESSION['user_photo'] = isset($user->profile_image) ? $user->profile_image : null;
        
        return true;
    } else {
        return "Błędny login lub hasło!";
    }
}

function logout_user() {
    session_destroy();
    session_start();
}
?>
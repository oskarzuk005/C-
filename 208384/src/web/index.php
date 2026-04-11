<?php
session_start();

ini_set('display_errors', '1');
error_reporting(E_ALL);

require_once 'config/db.php';
require_once 'BusinessLogic/ImageService.php';
require_once 'BusinessLogic/UserService.php';
require_once 'BusinessLogic/CartService.php';
require_once 'Models/PhotoModel.php';
require_once 'Models/UserModel.php';

$action = $_GET['action'] ?? 'gallery';

$menu = '<div style="padding: 10px; background: #f4f4f4; border-bottom: 1px solid #ccc; margin-bottom: 20px;">';
$menu .= '<a href="index.php?action=gallery" style="text-decoration: none; font-size: 18px; font-weight: bold;"> Galeria Główna</a>';

if (isset($_SESSION['user_login'])) {

    $menu .= ' <span style="float: right; display: flex; align-items: center;">';
    
    // Wyświetlanie zdjęcia profilowego
    if (isset($_SESSION['user_photo']) && !empty($_SESSION['user_photo'])) {
        $photoPath = 'ProfilesFoto/' . $_SESSION['user_photo'];
        $menu .= '<img src="' . $photoPath . '" alt="Profil" style="width: 35px; height: 35px; border-radius: 50%; border: 2px solid #fff; box-shadow: 0 0 3px #888; margin-right: 10px; object-fit: cover;">';
    } else {
        // Ikonka zastępcza
        $menu .= '<span style="font-size: 25px; margin-right: 5px;">👤</span>';
    }

    // Login i link wylogowania
    $menu .= 'Witaj, <b>' . htmlspecialchars($_SESSION['user_login']) . '</b>';
    $menu .= ' <span style="margin: 0 10px;">|</span> ';
    $menu .= '<a href="index.php?action=logout" style="color: red;">Wyloguj się</a>';
    $menu .= '</span>';
    $menu .= '<div style="clear: both;"></div>';

} else {
    $menu .= ' <span style="float: right;">';
    $menu .= '<a href="index.php?action=login"> Logowanie</a>';
    $menu .= ' <span style="margin: 0 5px;">|</span> ';
    $menu .= '<a href="index.php?action=register">  Rejestracja</a>';
    $menu .= '</span>';
    $menu .= '<div style="clear: both;"></div>';
}
$menu .= '</div>';


switch ($action) {
    
    // REJESTRACJA
    case 'register':
        if (isset($_SESSION['user_login'])) { header("Location: index.php?action=gallery"); exit; }

        if ($_SERVER['REQUEST_METHOD'] === 'POST') {
            $email = $_POST['email'];
            $login = $_POST['login'];
            $pass = $_POST['password'];
            $repeat = $_POST['repeat_password'];
            $file = $_FILES['profile_image']; 

            $result = register_user($login, $email, $pass, $repeat, $file);

            if ($result === true) {
                header("Location: index.php?action=login&status=registered");
                exit;
            } else {
                $error_msg = $result;
                include 'views/register_view.php';
            }
        } else {
            include 'views/register_view.php';
        }
        break;

    // LOGOWANIE
    case 'login':
        if (isset($_SESSION['user_login'])) { header("Location: index.php?action=gallery"); exit; }

        if ($_SERVER['REQUEST_METHOD'] === 'POST') {
            $login = $_POST['login'];
            $pass = $_POST['password'];

            $result = login_user($login, $pass);

            if ($result === true) {
                header("Location: index.php?action=gallery");
                exit;
            } else {
                $error_msg = $result;
                include 'views/login_view.php';
            }
        } else {
            include 'views/login_view.php';
        }
        break;

    // WYLOGOWANIE
    case 'logout':
        logout_user();
        header("Location: index.php?action=gallery");
        exit;

    // WYSYŁANIE ZDJĘĆ
    case 'upload':
        if ($_SERVER['REQUEST_METHOD'] === 'POST') {
            $title = $_POST['title'];
            $author = isset($_SESSION['user_login']) ? $_SESSION['user_login'] : $_POST['author'];
            
            $result = process_upload($_FILES['image'], $title, $author);
            
            if ($result === true) {
                header("Location: index.php?action=gallery&status=ok");
                exit;
            } else {
                $error_msg = $result;
                include 'views/upload_view.php';
            }
        } else {
            include 'views/upload_view.php';
        }
        break;

    // DODAWANIE DO KOSZYKA
    case 'addToCart':
        if ($_SERVER['REQUEST_METHOD'] === 'POST' && isset($_POST['selected_photos'])) {
            addToCart($_POST['selected_photos']);
        }
        header("Location: index.php?action=gallery");
        exit;

    // USUWANIE Z KOSZYKA
    case 'removeFromCart':
        if ($_SERVER['REQUEST_METHOD'] === 'POST' && isset($_POST['selected_photos'])) {
            removeFromCart($_POST['selected_photos']);
        }
        header("Location: index.php?action=cart");
        exit;

    // WIDOK KOSZYKA
    case 'cart':
        $cartIds = array_keys(getCartContent());
        $cartPhotos = get_photos_by_ids($cartIds);
        include 'views/cart_view.php';
        break;

    // GALERIA GŁÓWNA 
    case 'gallery':
    default:
        $page = isset($_GET['page']) ? (int)$_GET['page'] : 1;
        $photos = get_all_photos($page, 3); // 3 zdjęcia na stronę
        $total = count_photos();
        $pages = ceil($total / 3);
        
        $cartCount = getCartCount();
        $cartContent = getCartContent();

        echo $menu; 
        include 'views/gallery_view.php';
        break;
}
?>
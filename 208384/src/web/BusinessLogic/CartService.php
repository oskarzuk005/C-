<?php

function addToCart($photoIds) {
    if (!isset($_SESSION['cart'])) {
        $_SESSION['cart'] = [];
    }

    foreach ($photoIds as $id) {
        // Klucz to ID zdjęcia, wartość to ilość 
        if (!isset($_SESSION['cart'][$id])) {
            $_SESSION['cart'][$id] = 1; 
        }
    }
}

function removeFromCart($photoIds) {
    if (isset($_SESSION['cart'])) {
        foreach ($photoIds as $id) {
            unset($_SESSION['cart'][$id]);
        }
    }
}

function getCartContent() {
    return isset($_SESSION['cart']) ? $_SESSION['cart'] : [];
}

function getCartCount() {
    if (!isset($_SESSION['cart'])) return 0;
    return array_sum($_SESSION['cart']);
}
?>
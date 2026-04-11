<nav style="background: #eee; padding: 15px; border-bottom: 2px solid #ccc;">
    <a href="index.php"> Start</a> | 
    <a href="index.php?action=gallery"> Galeria</a> | 
    <a href="index.php?action=upload"> Dodaj zdjęcie</a> |
    <a href="index.php?action=search"> Szukaj (AJAX)</a> |
    <a href="index.php?action=cart"> Wybrane (<?php 
        $count = 0;
        if(isset($_SESSION['cart'])) foreach($_SESSION['cart'] as $c) $count += $c['amount'];
        echo $count; 
    ?>)</a>
    <span style="float: right;">
        <?php if(isset($_SESSION['user_id'])): ?>
            Zalogowany: <strong><?= $_SESSION['user_login'] ?></strong>
            <img src="ProfilesFoto/<?= $_SESSION['user_thumb'] ?>" width="30" style="vertical-align: middle;">
            <a href="index.php?action=logout">Wyloguj</a>
        <?php else: ?>
            <a href="index.php?action=login">Zaloguj</a> | <a href="index.php?action=register">Rejestracja</a>
        <?php endif; ?>
    </span>
</nav>
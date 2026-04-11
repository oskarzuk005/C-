<!DOCTYPE html>
<html>
<head><title>Dodaj zdjęcie</title></head>
<body>
    <h2>Prześlij zdjęcie</h2>
    <?php if (isset($error_msg)) echo "<p style='color:red'>$error_msg</p>"; ?>

    <form action="index.php?action=upload" method="post" enctype="multipart/form-data">
        <label>Tytuł:</label><br>
        <input type="text" name="title" required><br><br>

        <?php if (!isset($_SESSION['user_login'])): ?>
            <label>Autor:</label><br>
            <input type="text" name="author" required><br><br>
        <?php else: ?>
            <p>Autor: <strong><?= $_SESSION['user_login'] ?></strong> (uzupełnione automatycznie)</p>
        <?php endif; ?>

        <label>Plik (JPG/PNG, max 1MB):</label><br>
        <input type="file" name="image" required><br><br>

        <input type="submit" value="Wyślij">
    </form>
    <br>
    <a href="index.php?action=gallery">Powrót do galerii</a>
</body>
</html>
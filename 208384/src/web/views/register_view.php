<!DOCTYPE html>
<html>
<head><title>Rejestracja</title></head>
<body>
    <h2>Rejestracja użytkownika</h2>
    <?php if (isset($error_msg)) echo "<p style='color:red'>$error_msg</p>"; ?>

    <form action="index.php?action=register" method="post" enctype="multipart/form-data">
        <label>Adres e-mail:</label><br>
        <input type="email" name="email" required><br>

        <label>Login:</label><br>
        <input type="text" name="login" required><br>

        <label>Hasło:</label><br>
        <input type="password" name="password" required><br>

        <label>Powtórz hasło:</label><br>
        <input type="password" name="repeat_password" required><br>
        
        <label>Zdjęcie profilowe (JPG/PNG):</label><br>
        <input type="file" name="profile_image" required><br><br>

        <input type="submit" value="Zarejestruj się">
    </form>
    <br>
    <a href="index.php?action=login">Masz konto? Zaloguj się</a>
</body>
</html>
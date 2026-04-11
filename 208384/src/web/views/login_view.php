<!DOCTYPE html>
<html>
<head><title>Logowanie</title></head>
<body>
    <h2>Logowanie</h2>
    <?php if (isset($error_msg)) echo "<p style='color:red'>$error_msg</p>"; ?>

    <form action="index.php?action=login" method="post">
        <label>Login:</label><br>
        <input type="text" name="login" required><br>

        <label>Hasło:</label><br>
        <input type="password" name="password" required><br><br>

        <input type="submit" value="Zaloguj">
    </form>
    <br>
    <a href="index.php?action=register">Nie masz konta? Zarejestruj się</a> | 
    <a href="index.php?action=gallery">Wróć do galerii</a>
</body>
</html>
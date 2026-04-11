<!DOCTYPE html>
<html>
<head>
    <title>Zapamiętane zdjęcia</title>
    <style>
        .photo-card { border: 1px solid #ddd; padding: 10px; margin: 10px; display: inline-block; width: 220px; vertical-align: top; }
    </style>
</head>
<body>
    <h1>Twoje zapamiętane zdjęcia</h1>
    <a href="index.php?action=gallery">← Wróć do galerii</a>
    <hr>

    <?php if (empty($cartPhotos)): ?>
        <p>Nie wybrałeś jeszcze żadnych zdjęć.</p>
    <?php else: ?>
        <form action="index.php?action=removeFromCart" method="post">
            <div class="gallery-container">
                <?php foreach ($cartPhotos as $photo): ?>
                    <?php $id = (string)$photo->_id; ?>
                    <div class="photo-card">
                        <img src="images/min/<?= $photo->filename ?>" alt="Miniatura">
                        <p><strong><?= $photo->title ?></strong></p>
                        <p>Autor: <?= $photo->author ?></p>
                        
                        <label style="background: #fee; padding: 5px; display: block;">
                            <input type="checkbox" name="selected_photos[]" value="<?= $id ?>">
                            Usuń z pamięci
                        </label>
                    </div>
                <?php endforeach; ?>
            </div>
            <br>
            <input type="submit" value="Usuń zaznaczone z zapamiętanych" style="background: #ffcccc; padding: 10px;">
        </form>
    <?php endif; ?>
</body>
</html>
<!DOCTYPE html>
<html>
<head>
    <title>Galeria WAI</title>
    <style>
        .photo-card { border: 1px solid #ddd; padding: 10px; margin: 10px; display: inline-block; width: 220px; vertical-align: top; }
        .pagination { margin-top: 20px; text-align: center; }
        .actions { margin-top: 10px; padding: 10px; background: #f0f0f0; text-align: center; position: sticky; bottom: 0; }
    </style>
</head>
<body>
    <?php include 'partials/cart_info.php'; ?>

    <h1>Galeria Zdjęć</h1>
    <a href="index.php?action=upload">[ Dodaj nowe zdjęcie ]</a>
    <hr>

    <form action="index.php?action=addToCart" method="post">
        <div class="gallery-container">
            <?php foreach ($photos as $photo): ?>
                <?php 
                    $id = (string)$photo->_id;
                    $isChecked = isset($cartContent[$id]) ? 'checked' : '';
                    $style = $isChecked ? 'background-color: #e6fffa;' : '';
                ?>
                <div class="photo-card" style="<?= $style ?>">
                    <a href="images/<?= $photo->filename ?>" target="_blank">
                        <img src="images/min/<?= $photo->filename ?>" alt="Miniatura">
                    </a>
                    <p><strong><?= $photo->title ?></strong></p>
                    <p>Autor: <?= $photo->author ?></p>
                    
                    <label style="display:block; margin-top:5px; cursor:pointer;">
                        <input type="checkbox" name="selected_photos[]" value="<?= $id ?>" <?= $isChecked ?>> 
                        Zapamiętaj
                    </label>
                </div>
            <?php endforeach; ?>
        </div>
        
        <div class="actions">
            <input type="submit" value="Zapamiętaj zaznaczone" style="padding: 10px 20px; font-size: 16px;">
        </div>
    </form>

    <div class="pagination">
        Strony: 
        <?php for ($i=1; $i<=$pages; $i++): ?>
            <a href="index.php?action=gallery&page=<?= $i ?>">[<?= $i ?>]</a> 
        <?php endfor; ?>
    </div>
</body>
</html>
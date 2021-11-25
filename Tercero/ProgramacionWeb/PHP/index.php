<!DOCTYPE html>
<html>

<head>
    <title>Foto Pick </title>
    <link rel="stylesheet" type="text/css" href="styles/estilo2.css">
    <!--link href="styles/estilo_index_movil.css" rel="stylesheet" media="(max-width: 480px)" -->
    <meta name=”viewport” content=”width=device-width”>

</head>

<body onload="myheader()">
    <?php require 'partials/header.php';?>
    <?php require 'partials/nav.php';?>
    <main>
        <section class="imagen_principal">
            <img src="imagenes/foto_pick.png" alt="Foto Web descripcion" class="foto_pick">


        </section>
        <section class="items_destacados">
            <h3>Ultimas fotos</h3>
            <article class="articulo_novedades">
                <a href="items/item1.html">
                    <img src="imagenes/items/item1/sunflower640.jpg" alt="foto_articulo" class="imagen_articulo">
                    <h4> Polinización de los girasoles</h4>
                </a>
            </article>

            <article class="articulo_novedades">
                <a href="items/item1.html">
                    <img src="imagenes/items/item2/city-438393_640.jpg" alt="foto_articulo" class="imagen_articulo">
                    <h4> Ciudad abarrotada</h4>
                </a>
            </article>
            <article class="articulo_novedades">
                <a href="items/item1.html">
                    <img src="imagenes/items/item3/dog-1168663_640.jpg" alt="foto_articulo" class="imagen_articulo">
                    <h4> Perro perdido en la nieve</h4>
                </a>
            </article>
            <article class="articulo_novedades">
                <a href="items/item1.html">
                    <img src="imagenes/items/item4/baby-2935722_640.jpg" alt="foto_articulo" class="imagen_articulo">
                    <h4> Bebe</h4>
                </a>
            </article>
            <article class="articulo_novedades">
                <a href="items/item1.html">
                    <img src="imagenes/items/item5/garden-19830_640.jpg" alt="foto_articulo" class="imagen_articulo">
                    <h4> Jardin de las Delicias</h4>
                </a>
            </article>
            <article class="articulo_novedades">
                <a href="items/item1.html">
                    <img src="imagenes/items/item6/rose-165819_640.jpg" alt="foto_articulo" class="imagen_articulo">
                    <h4> Rosa Peculiar</h4>
                </a>
            </article>
            <article class="articulo_novedades">
                <a href="items/item1.html">
                    <img src="imagenes/items/item7/basilisk-5951351_640.jpg" alt="foto_articulo"
                        class="imagen_articulo">
                    <h4> Animal posando</h4>
                </a>
            </article>




        </section>

    </main>
    <?php require 'partials/footer.php';?>
</body>

</html>
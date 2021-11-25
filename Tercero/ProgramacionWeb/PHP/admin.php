<?php
    require 'backend/consultar_secciones.php';
    //require 'backend/consultar_items.php';

?>
<!DOCTYPE html>
<html>

<head>
    <title>Administración</title>
    <link rel="stylesheet" type="text/css" href="styles/estilo2.css" />
    <link rel="stylesheet" type="text/css" href="styles/estilo_admin.css" />
</head>

<body onload="myheader()">
    <?php require 'partials/header.php';?>
    <?php require 'partials/nav.php';?>
    <section class="administrar_opts">
        <ul>
            <li>
                Administrar Secciones<br>
                <a class="add_new" href="altaseccion.php">Añadir nuevo</a>
                <table class='listar_SQL'>
                    <tr>
                        <th></th>
                        <th>Nombre</th>
                        <th colspan='2'>Accion</th>

                    </tr>
                    <?php
                    $aux = 1;
                     foreach ( $secciones as $opt ) {
                        echo "<tr>
                        <td>".$aux."</td>
                        <td>".$opt[1]."</td>
                        <td><a href='editar_secciones?id=".$opt[0]."'>Editar</a></td>
                        <td><a href='backend/borrar_secciones?id=".$opt[0]."'>Borrar</a></td>
                        </tr>";$aux=$aux+1;}
                    ?>

                </table>


            </li>
            <li><a href="">
                Administrar Items
            </a></li>
        </ul>
    </section>
    <?php require 'partials/footer.php';?>
</body>


</html>
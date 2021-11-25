
<?php
    $limit = 9;
    require 'backend/db.php';
    if (isset($_GET['id']))
    {
        $num_sec = $_GET['id'];
        $res = $conn->query('SELECT * FROM items WHERE seccion='.$num_sec);
        $total = count($res->fetchAll());


        $pages = ceil($total/$limit);//redondeo arriba
        if($pages !=0){
            if (isset($_GET['currentpage']) && is_numeric($_GET['currentpage'])) {
                $currentpage = (int) $_GET['currentpage'];
            } else {
                $currentpage = 1;
            }

            if ($currentpage > $pages) {
                $currentpage = $pages;
            }
            if ($currentpage < 1) {
                $currentpage = 1;
            }

            $offset = ($currentpage - 1) * $limit;

            $SQL = $conn->prepare("SELECT * FROM items WHERE seccion=".$num_sec." LIMIT $offset,$limit");
            $SQL->execute();
            $items_de_seccion=[];
            foreach ( $SQL->fetchAll() as $item ) {
                $aux = array($item['id'],$item['titulo'],$item['seccion'],$item['artista'],$item['ubicacion'],$item['origen']);
                $items_de_seccion[] = $aux;
            }
        }


    }

?>

<!DOCTYPE html>
<html>

<head>
    <title>Seccion <?php echo $num_sec?></title>
    <link rel="stylesheet" type="text/css" href="styles/estilo2.css" />
    <link rel="stylesheet" type="text/css" href="styles/estilo_secciones.css" />
</head>

<body onload="myheader()">
    <?php require 'partials/header.php';?>
    <?php require 'partials/nav.php';?>

    <main>
        <section class="menu_secc">


            <?php
            if($pages !=0){
            //$contador_f = 0;
            echo "<table><tr>";
            $contador_c = 0;
            //echo count($items_de_seccion);
            foreach ($items_de_seccion as $item_d){

                if($contador_c == 3)
                {
                    $contador_c=0;
                    echo "</tr><tr>";
                }
                ++$contador_c;
                echo "<th>
                        <article class='articulo_novedades'>
                            <a href=''>
                                <img src='imagenes/items/item1/sunflower640.jpg' alt='foto_articulo'
                                    class='imagen_articulo'>
                                <h4>".$item_d[1]."</h4>
                            </a>
                        </article>
                    </th>";
            }
        }
            ?>

            </table>


            <nav class="mostrar_mas">
                <ul>

                <?php
                if($pages !=0){
                    if ($currentpage == 1 )
                    {
                        $nextpage = $currentpage + 1;
                        echo " <li><a href='{$_SERVER['PHP_SELF']}?id=$num_sec&currentpage=$nextpage'>Siguiente</a></li> ";
                    }
                    else if ($currentpage == $pages OR $currentpage >= $pages) {
                        $prevpage = $currentpage - 1;


                        echo " <li><a href='{$_SERVER['PHP_SELF']}?id=$num_sec&currentpage=$prevpage'>Anterior</a></li> ";

                    }
                    else
                    {

                        $nextpage = $currentpage + 1;
                        $prevpage = $currentpage - 1;
                        echo " <li><a href='{$_SERVER['PHP_SELF']}?id=$num_sec&currentpage=$prevpage'>Anterior</a></li> ";
                        echo " <li><a href='{$_SERVER['PHP_SELF']}?id=$num_sec&currentpage=$nextpage'>Siguiente</a></li> ";
                    }
                }?>

                </ul>
            </nav>


        </section>
    </main>
    <?php require 'partials/footer.php';?>
</body>

</html>
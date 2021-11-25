<?php require 'backend/consultar_secciones.php';?>
<nav class="navigation">
        <ul>
        <?php
        $contador = 1;
            foreach ( $secciones as $opt ) {
                echo "
                <li>
                <a href='seccion.php?id=".$opt[0]."'>".$opt[1]."</a>
                </li>";
                if($contador == 5){break;}
                ++$contador;
            }
        ?>
        </ul>
</nav>
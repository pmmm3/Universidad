<?php
    require 'db.php';

    $SQL = $conn->prepare('SELECT * FROM items;');
    $SQL->execute();
    //$resultado = $SQL->fetch(PDO::FETCH_ASSOC);
    $options_items = array();
    foreach ( $SQL->fetchAll() as $item ) {
        $aux = array($item['id'],$item['titulo'],$item['seccion'],$item['artista'],$item['ubicacion'],$item['origen']);
        $options[] = $aux;
    }


?>
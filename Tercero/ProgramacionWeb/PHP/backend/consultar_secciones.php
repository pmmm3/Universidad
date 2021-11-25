<?php
    require 'db.php';
    $SQL = $conn->prepare('SELECT id,nombre FROM secciones;');
    $SQL->execute();
    //$resultado = $SQL->fetch(PDO::FETCH_ASSOC);
    $secciones = array();
    foreach ( $SQL->fetchAll() as $section ) {
        $aux = array($section['id'],$section['nombre']);
        $secciones[] = $aux;
    }


?>
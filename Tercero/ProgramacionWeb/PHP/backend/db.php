<?php

$host = "localhost";
$user="pw76067676";
$password="76067676";
$database="db76067676_pw2021";

try{
    $conn = new PDO("mysql:host=$host;dbname=$database", $user, $password);
}catch(PDOException $e){
    die("Conect fail " .$e->getMessage() );
}

///////////////////////////////
//CREATE TABLE `db76067676_pw2021`.`users` ( `nombre` VARCHAR(20) NOT NULL , `apellidos` VARCHAR(50) NOT NULL , `correo` VARCHAR(100) NOT NULL , `telefono` INT(13) NOT NULL , `fecha_nacimiento` DATE NOT NULL , `password` VARCHAR(250) NOT NULL , PRIMARY KEY (`correo`)) ENGINE = InnoDB;
/*
$host = "localhost";
$user="pablo";
$password="programacion1234";
$database="db76067676_pw2021";

try{
    $conn = new PDO("mysql:host=$host;dbname=$database", $user, $password);
    $conn->setAttribute( PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION );
}catch(PDOException $e){
    die("Conect fail " .$e->getMessage() );
}
*/
?>
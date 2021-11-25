<?php
    //require 'backend/consultar_secciones.php';
    require 'backend/db.php';

    $msg = '';
if (!empty($_POST['titulo']))
{

    $sql = "INSERT INTO secciones (nombre) VALUES (:titulo)";
    $query = $conn->prepare($sql);

    //echo $_POST['titulo'];
    $query->bindParam(':titulo',$_POST['titulo']);




    if ($query->execute())
    {
        $msg = 'Se ha creado correctamente el item';
        header('Location: admin.php');
    }
    else{
        //echo $query->error;
        echo $msg = 'ERROR en la creacion';
    }



}


?>
<!DOCTYPE html>
<html>

<head>
    <title>Dar de alta Seccion</title>
    <link rel="stylesheet" type="text/css" href="styles/estilo2.css" />
</head>

<body onload="myheader()">
    <?php require 'partials/header.php';?>
    <?php require 'partials/nav.php';?>
    <form method="POST" action="altaseccion.php" autocomplete="on" class="registo_usuario" >
        <fieldset>
            <legend>Registro de Seccion</legend>
            <label for="titulo">Nombre:</label><br>
            <input type="text" id="titulo" name="titulo" maxlength="20" autofocus required><br>

            <input type="submit" value="Enviar Datos">

        </fieldset>
    </form>
</body>
<?php require 'partials/footer.php';?>

</html>
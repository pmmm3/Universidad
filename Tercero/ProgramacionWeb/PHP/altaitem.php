<?php
    require 'backend/consultar_secciones.php';
    require 'backend/db.php';

    $msg = '';
if (!empty($_POST['titulo']) && !empty($_POST['categoria']) && !empty($_POST['Artista']) && !empty($_POST['direccion']) && !empty($_POST['origen']))
{

    $sql = "INSERT INTO items (titulo,seccion,artista,ubicacion,origen) VALUES (:titulo,:seccion,:artista,:ubicacion,:origen)";
    $query = $conn->prepare($sql);

    //echo $_POST['titulo'];
    $query->bindParam(':titulo',$_POST['titulo']);

    //echo $_POST['categoria'];
    $query->bindParam(':seccion',$_POST['categoria']);

    //echo $_POST['Artista'];
    $query->bindParam(':artista',$_POST['Artista']);
    //echo $_POST['direccion'];
    $query->bindParam(':ubicacion',$_POST['direccion']);
    //echo $_POST['origen'];
    $query->bindParam(':origen',$_POST['origen']);


    if ($query->execute())
    {
        $msg = 'Se ha creado correctamente el item';
    }
    else{
        echo $query->error;
        $msg = 'ERROR en la creacion';
    }



}


?>
<!DOCTYPE html>
<html>

<head>
    <title>Dar de alta Item</title>
    <link rel="stylesheet" type="text/css" href="styles/estilo2.css" />
</head>

<body onload="myheader()">
    <?php require 'partials/header.php';?>
    <?php require 'partials/nav.php';?>
    <form method="POST" action="altaitem.php" autocomplete="on" class="registo_usuario" >
        <fieldset>
            <legend>Registro de Item</legend>
            <label for="titulo">Titulo:</label><br>
            <input type="text" id="titulo" name="titulo" maxlength="20" autofocus required><br>
            <label for="categoria">Categoria</label><br>
            <select id="categoria" name="categoria">
                <?php
                foreach ( $secciones as $opt ) {
                    echo "<option value='".$opt[0]."'>".$opt[1]."</option>";

                }
                ?>
            </select><br>
            <label for="Artista">Artista:</label><br>
            <input type="text" id="Artista" name="Artista" maxlength="50" required><br>

            <label for="direccion">Localización:</label><br>
            <input type="text" id="direccion" name="direccion" maxlength="100"
                placeholder="C/Calle ,nº4 , 18014, Granada" required><br>
            <label for="origen">Origen:</label><br>
            <input type="url" origen" name="origen" maxlength="100" placeholder="www.sitioweb.com" required><br>
            <label for="fotosubida">Sube una foto:</label><br>
            <input type="file" name="fotosubida" accept="image/png, .jpeg, .jpg"><br>

            <input type="submit" value="Enviar Datos">

        </fieldset>
    </form>
</body>
<?php require 'partials/footer.php';?>

</html>
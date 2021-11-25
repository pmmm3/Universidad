<?php
    require 'backend/db.php';
    //echo($_GET['id']);
    if(isset($_GET['id']))
    {
        $id = $_GET['id'];
        $SQL = $conn->prepare("SELECT * FROM secciones WHERE id=$id;");
        $SQL->execute();
        //echo "EJECUTADO";
        //$resultado = $SQL->fetch(PDO::FETCH_ASSOC);
        $data = array();
        foreach ($SQL->fetchAll() as $section ) {
            //echo $section['id'];
            $aux = array($section['id'],$section['nombre']);
            $data[] = $aux;
        }
    }
    if (isset($_POST['actualizar'])) {
        $id = $_GET['id'];
        $titulo= $_POST['titulo'];
        echo($_POST['titulo']);
        $sql_actualizar = "UPDATE secciones set nombre = '$titulo' WHERE id=$id;";
        $SQL = $conn->prepare($sql_actualizar);
        $SQL->execute();
        header('Location: admin.php');
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
    <form method="POST" action="editar_secciones.php?id=<?php echo $_GET['id']; ?>" autocomplete="on" class="registo_usuario" >
        <fieldset>
            <legend>Seccion</legend>
            <!--input type="hidden" id="custId" name="custId" value=<?php ?> //echo $_GET['id']?-->
            <label for="titulo">Nombre:</label><br>
            <input type="text" id="titulo" name="titulo" maxlength="20" autofocus required value="<?php echo $data[0][1]; ?>"><br>

            <button class="boton_custom" name="actualizar">
            Actualizar Datos
            </button>

        </fieldset>
    </form>
</body>
<?php require 'partials/footer.php';?>

</html>
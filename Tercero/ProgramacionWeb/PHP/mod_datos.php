<?php require 'backend/db.php';
session_start();
$msg = '';
$email_2 = $_SESSION['email'];
$SQL = $conn->prepare("SELECT * FROM users WHERE correo='$email_2'");
$SQL->execute();
//echo "EJECUTADO";
//$resultado = $SQL->fetch(PDO::FETCH_ASSOC);
$data = array();
foreach ($SQL->fetchAll() as $i ) {
    //echo $section['id'];
    $aux = array($i['nombre'],$i['apellidos'],$i['correo'],$i['telefono'],$i['fecha_nacimiento']);
    $data[] = $aux;
}
if (isset($_POST['actualizar'])) {
    if (!empty($_POST['nombre']) && !empty($_POST['apellidos']) && !empty($_POST['correo']) && !empty($_POST['tel']) && !empty($_POST['fnac']) && !empty($_POST['password']))
    {
        $password = password_hash($_POST['password'], PASSWORD_BCRYPT);
        $sql= "UPDATE users SET nombre ='$_POST[nombre]',apellidos ='$_POST[apellidos]',correo = '$_POST[correo]',telefono = '$_POST[tel]',fecha_nacimiento ='$_POST[fnac]',pass = '$password' WHERE (correo = '$_SESSION[email]')";
        $query = $conn->prepare($sql);
        if ($query->execute())
        {
            $_SESSION['email'] = $_POST['correo'];
            $user= $_POST['correo'];
            $msg = 'Se ha modificado correctamente el usuario';
            header('Location: index.php');
        }
        else{
            echo $query->error;
            $msg = 'ERROR en la alteracion';
        }

        //echo "FUNCIONA";
    }
}

?>

<!DOCTYPE html>
<html>

<head>
    <title>Foto Pick - Registro</title>
    <link rel="stylesheet" type="text/css" href="styles/estilo2.css" />
</head>

<body onload="myheader()">
    <?php require 'partials/header.php';?>

    <?php if(!empty($msg)): ?>
      <p> <?= $msg ?></p>
    <?php endif; ?>
    <form autocomplete="on" class="registo_usuario" method="POST" action="mod_datos.php">
        <fieldset>
            <legend>Registro de Usuario</legend>
            <label for="nombre">Nombre:</label><br>
            <input type="text" id="nombre" name="nombre" maxlength="20" autofocus required value="<?php echo $data[0][0]; ?>"><br>

            <label for="apellidos">Apellidos:</label><br>
            <input type="text" id="apellidos" name="apellidos" maxlength="50" required value="<?php echo $data[0][1]; ?>"><br>
            <label for="correo">Email:</label><br>
            <input type="email" id="correo" name="correo" maxlength="100" placeholder="nombre@correoelectronico.com"required value="<?php echo $data[0][2]; ?>"><br>
            <label for="tel">Telefono:</label><br>
            <input type="tel" id="tel" name="tel" maxlength="13" placeholder="611223344" required value="<?php echo $data[0][3]; ?>"><br>
            <label for="fnac">Fecha de nacimiento:</label><br>
            <input type="date" id="fnac" name="fnac" placeholder="DD/MM/YYYY" required value="<?php echo $data[0][4]; ?>"><br>

            <label for="password">Contraseña:</label><br>
            <input name="password" type="password" placeholder="Password" required><br>

            <button class="boton_custom" name="actualizar">
            Actualizar Datos
            </button>

        </fieldset>
    </form>
    <?php require 'partials/footer.php';?>
</body>

</html>
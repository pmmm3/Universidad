<?php require 'backend/db.php';

$msg = '';
if (!empty($_POST['nombre']) && !empty($_POST['apellidos']) && !empty($_POST['correo']) && !empty($_POST['tel']) && !empty($_POST['fnac']) && !empty($_POST['password']))
{
    $sql = "INSERT INTO users (nombre,apellidos,correo,telefono,fecha_nacimiento,password) VALUES (:nombre,:apellidos,:correo,:tel,:fnac,:password)";
    $query = $conn->prepare($sql);

    $query->bindParam(':nombre',$_POST['nombre']);
    //Encriptamos la password
    $password = password_hash($_POST['password'], PASSWORD_BCRYPT);

    $query->bindParam(':password', $password);
    $query->bindParam(':apellidos', $_POST['apellidos']);
    $query->bindParam(':correo', $_POST['correo']);
    $query->bindParam(':fnac', $_POST['fnac']);
    $query->bindParam(':tel', $_POST['tel']);

    if ($query->execute())
    {
        $msg = 'Se ha creado correctamente el usuario';
    }
    else{
        echo $query->error;
        $msg = 'ERROR en la creacion';
    }

    //echo "FUNCIONA";
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
    <form autocomplete="on" class="registo_usuario" method="POST" action="altausuario.php">
        <fieldset>
            <legend>Registro de Usuario</legend>
            <label for="nombre">Nombre:</label><br>
            <input type="text" id="nombre" name="nombre" maxlength="20" autofocus required><br>

            <label for="apellidos">Apellidos:</label><br>
            <input type="text" id="apellidos" name="apellidos" maxlength="50" required><br>
            <label for="correo">Email:</label><br>
            <input type="email" id="correo" name="correo" maxlength="100" placeholder="nombre@correoelectronico.com"
                required><br>
            <label for="tel">Telefono:</label><br>
            <input type="tel" id="tel" name="tel" maxlength="13" placeholder="611223344" required><br>
            <label for="fnac">Fecha de nacimiento:</label><br>
            <input type="date" id="fnac" name="fnac" placeholder="DD/MM/YYYY" required><br>

            <label for="password">Contraseña:</label><br>
            <input name="password" type="password" placeholder="Password" required><br>

            <input type="submit" value="Enviar Datos">

        </fieldset>
    </form>
    <?php require 'partials/footer.php';?>
</body>

</html>
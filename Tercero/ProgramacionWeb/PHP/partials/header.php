
<?php
    require 'backend/login.php';?>
<header>
        <img src="imagenes/logo2/logo_transparent.png" alt="Logo" class="logo">
        <h1 class="Titulo"> Foto Pick </h1>
        <section class="login" id = "login">
            <form autocomplete="on" action="index.php" name="login"  method="POST">
                <label for="user">Usuario:</label><br>
                <input type="text" id="user" name="user" autofocus required placeholder="Correo electronico"><br>
                <label for="passwd">Contraseña:</label><br>
                <input type="password" id="passwd" name="passwd" required><br>
                <input type="submit" value="Enviar" class="boton_custom">
            </form>
            <br>
            <a href="altausuario.php">Registro de usuarios</a>

        </section>
        <section class="registrado" id="registrado">
            <table>
                <tr>
                    <th colspan="2">Usuario</th>

                </tr>
                <tr>
                    <th colspan="1">
                        <?php
                            if (isset($user)&&$user!= null)
                            {
                                echo $user;
                            };
                        ?>
                    </th>
                    <th colspan="1"><a href="mod_datos.php">Modificar Datos</a></th>
                </tr>

                <tr>
                <?php
                    if (isset($es_admin)&&$es_admin)
                    {
                        echo "<td><a class='altaItem' href='admin.php'>Administración</a></td>";
                    };
                ?>
                <td colspan='2'><a class='logout' href="backend/logout.php">Cerrar Sesion</a></td>
                </tr>
            </table>
            <br>



        </section>

</header>


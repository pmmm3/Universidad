<?php
    require 'db.php';
    if(!isset($_SESSION))
    {
        session_start();
    } 
    //SESSION_UNSET();
    //SESSION_DESTROY();
    if(empty($_SESSION['email'])){
        if (!empty($_POST['user'])  && !empty($_POST['passwd']))
        {
            $query = $conn->prepare('SELECT nombre,correo,pass FROM users WHERE correo=:email');
            $query->bindParam(':email', $_POST['user']);
            $query->execute();
            //$resultado = $query->fetch(PDO::FETCH_ASSOC);
            $resultado = $query->fetchAll();
            $name=null;
            $passwd=null;
            $email=null;

            foreach( $resultado as $fila)
            {
                $name = $fila['nombre'];
                //echo $fila['nombre'] . "<br>";
                $name = $fila['correo'];
               //echo $fila['correo']. "<br>";
                $passwd = $fila['pass'];
                //echo $fila['pass']. "<br>";
            }
            //echo count($resultado). "<br>";
            //echo $passwd. "<br>";

            //echo  password_hash($_POST['passwd'], PASSWORD_BCRYPT);

            $msg = '';

            if ($passwd!=null &&password_verify($_POST['passwd'],$passwd))
            {

                $_SESSION['email'] = $name;
                $_SESSION['user'] = $resultado['nombre'];

                header('Location: index.php');
            }
            else
            {
                echo "
                <script>
                window.alert('No se puede iniciar sesion con esos datos.');
                </script>";
                $msg='No se puede iniciar sesion con esos datos.';
            }
        }
    }
    else
    {
        $SQL = $conn->prepare('SELECT nombre,admin FROM users WHERE correo=:email');
        $SQL->bindParam(':email', $_SESSION['email']);
        $SQL->execute();
        $resultado = $SQL->fetch(PDO::FETCH_ASSOC);
        $user = null;
        if(count($resultado)>0){
           $user = $resultado['nombre'];
           $es_admin = $resultado['admin'];
        }

        echo    '<script> function myheader(){
                    const x = document.getElementsByClassName("login");
                    const y = document.getElementsByClassName("registrado");
                    y[0].style.display="inherit";
                    x[0].style.display="none";}
            </script>';
    }

?>
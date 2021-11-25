<?php
    session_start();
    $_SESSION = array();
    //  SESSION_UNSET();
    SESSION_DESTROY();
    header("Location: ../index.php");
?>
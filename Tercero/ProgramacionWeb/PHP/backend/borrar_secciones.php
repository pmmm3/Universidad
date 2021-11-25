<?php
    require 'db.php';
    if (isset($_GET['id']))
    {
        $id = $_GET['id'];
        $SQL = $conn->prepare("DELETE FROM secciones WHERE id=$id");
        $SQL->execute();
        header('Location: ../admin.php');
    }
?>
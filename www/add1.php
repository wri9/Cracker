<?php
include('connect.php');

   if(!is_null($_POST))
   {
      $collection = Connection();

      $decoded['index'] = $_POST['i'];
      $decoded['sensornum'] = $_POST['sensornum'];
      $decoded['value'] = $_POST['value'];

      $collection->insert($decoded);
      die();         
   }

?>

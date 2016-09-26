<?php
include('connect.php');

$collection = Connection();
   
   if(!is_null($_POST))
   {
      if(array_key_exists('i', $_POST))
      {
         $decoded["index"] = $_POST["i"];
         $decoded["sensor0"] = $_POST["s0"];
         $decoded["sensor1"] = $_POST["s1"];
         $decoded["sensor2"] = $_POST["s2"];
         $decoded["sensor3"] = $_POST["s3"];
         $decoded["sensor4"] = $_POST["s4"];
         $decoded["sensor5"] = $_POST["s5"];
         $decoded["sensor6"] = $_POST["s6"];
         $decoded["sensor7"] = $_POST["s7"];
         $decoded["sensor8"] = $_POST["s8"];

         
         $collection->insert($decoded);
         die();
      }
   }

$handle = file_get_contents('php://input');
if(strlen($handle) <= 0)
{
   $returnData['code'] = '300';
   $returnData['comment'] = 'ERROR : $_POST data is empty';
   
   die(json_encode($returnData));
   return;
}
else
{
   $decoded = json_decode($handle, true);
   //$decoded["index"] = 11;//$_POST["i"];   
   $collection->insert($decoded);
   die(); 
}

$m->close();

?>

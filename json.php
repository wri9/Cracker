<?php 
include('connect.php');
$collection = Connection();

$cursor = $collection->find();
$arr = array();

$fp = fopen('results.json', 'w');
foreach($cursor as $document)
{
     $temp = array(
    	"index" => $document["i"], 
       	"sensor0" => $document["s0"],
       	"sensor1" => $document["s1"],
       	"sensor2" => $document["s2"],
       	"sensor3" => $document["s3"],
       	"sensor4" => $document["s4"],
       	"sensor5" => $document["s5"],
       	"sensor6" => $document["s6"],
       	"sensor7" => $document["s7"],
       	"sensor8" => $document["s8"]
       	);
    //array_push($arr, $temp);
     fwrite($fp, json_encode($temp));
}

//fwrite($fp, json_encode($arr));
fclose($fp);


?> 
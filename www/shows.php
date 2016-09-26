<?PHP



	if(!is_null($_GET))
	{
		if(array_key_exists('index', $_GET))
		{
			$decoded['index'] = $_GET['index'];
			$decoded['sensornum'] = $_GET['sensornum'];
			$decoded['value'] = $_GET['value'];

			$m = new MongoClient();
			$db = $m->mydb;
			$collection = $db->test;
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
	$m = new MongoClient();
	$db = $m->mydb;
	$collection = $db->test;
	$collection->insert($decoded);
	die();
}
   
?>
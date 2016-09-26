<?php

	function Connection(){
		$m = new MongoClient();
		$db = $m->mydb;
		$collection = $db->test1;

		return $collection;
	}

?>
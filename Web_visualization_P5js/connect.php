<?php
class dataAll
{
    public $time;
    public $tempeture;
    public $humidity;
    public $light;
}
class dataTemp{
	public $time;
    public $tempeture;
}
class dataHum{
	public $time;
    public $humidity;
}
class dataLight{
	public $time;
    public $light;
}

// we connect to example.com and port 3307
$link = new mysqli('195.178.232.16', 'af7874', 'La-9-sinfonia', 'af7874');
if (!$link) {
    die('Could not connect: ' . mysql_error());
}

if (empty($_GET['com'])) {
	// the thing is empty, do nothing
	die('Dude, this is so wrong, you know nothing about me');
}

switch ( $_GET['com']) {
	case 'searchAll':
		$sql = 'SELECT time,tempeture,humidity,light FROM mqtt_name';
		$retval = mysqli_query($link, $sql);
		if(! $retval ) {
			die('Could not get data: ' . mysql_error());
		}
		$retAll=array();
		while($row = mysqli_fetch_array($retval, MYSQL_ASSOC)) {
			$allData = new dataAll();
			$allData->time = $row['time'];
			$allData->tempeture = $row['tempeture'];
			$allData->humidity = $row['humidity'];
			$allData->light = $row['light'];
			array_push($retAll, $allData);
		}
		echo json_encode($retAll);
	break;
	case 'searchTemp':
		$sql = 'SELECT time,tempeture FROM mqtt_name';
		$retval = mysqli_query($link, $sql);
		if(! $retval ) {
			die('Could not get data: ' . mysql_error());
		}
		$retTemp=array();
		while($row = mysqli_fetch_array($retval, MYSQL_ASSOC)) {
			$tempData = new dataTemp();
			$tempData->time = $row['time'];
			$tempData->tempeture = $row['tempeture'];
			array_push($retTemp, $tempData);
		}
		echo json_encode($retTemp);
	break;
	case 'searchHum':
		$sql = 'SELECT time,humidity FROM mqtt_name';
		$retval = mysqli_query($link, $sql);
		if(! $retval ) {
			die('Could not get data: ' . mysql_error());
		}
		$retHum=array();
		while($row = mysqli_fetch_array($retval, MYSQL_ASSOC)) {
			$humData = new dataHum();
			$humData->time = $row['time'];
			$humData->humidity = $row['humidity'];
			array_push($retHum, $humData);
		}
		echo json_encode($retHum);
	break;
	case 'searchLight':
		$sql = 'SELECT time,light FROM mqtt_name';
		$retval = mysqli_query($link, $sql);
		if(! $retval ) {
			die('Could not get data: ' . mysql_error());
		}
		$retLight=array();
		while($row = mysqli_fetch_array($retval, MYSQL_ASSOC)) {
			$lightData = new dataLight();
			$lightData->time = $row['time'];
			$lightData->light = $row['light'];
			array_push($retLight, $lightData);
		}
		echo json_encode($retLight);
	break;
}
?>

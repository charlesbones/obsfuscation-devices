#!/usr/bin/php-cli
<?php

$DBServer = ''; 
$DBUser   = '';
$DBPass   = '';
$DBName   = '';  

$conn = new mysqli($DBServer, $DBUser, $DBPass, $DBName);
// check connection
if ($conn->connect_error) {
  trigger_error('Database connection failed: '  . $conn->connect_error, E_USER_ERROR);
}
$sql="SELECT * FROM mqtt_name";
if ($result=mysqli_query($conn,$sql)){
	$rowcount=mysqli_num_rows($result);
	mysqli_free_result($result);
	$sql="UPDATE mqtt_name SET tempeture = ".rand(0,30).", humidity=".rand(0,80).", light =".rand(0,350)." WHERE id='".$rowcount."'";
	if($conn->query($sql) === false) {
		trigger_error('Wrong SQL: ' . $sql . ' Error: ' . $conn->error, E_USER_ERROR);
	}
}

?>

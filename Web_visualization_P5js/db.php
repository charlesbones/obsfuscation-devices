#!/usr/bin/php-cli
<?php
$tempeture = $argv[1];
$humidity = $argv[2];
$light = $argv[3];
$DBServer = '195.178.232.16'; 
$DBUser   = 'af7874';
$DBPass   = 'La-9-sinfonia';
$DBName   = 'af7874';  
$conn = new mysqli($DBServer, $DBUser, $DBPass, $DBName);
// check connection
if ($conn->connect_error) {
  trigger_error('Database connection failed: '  . $conn->connect_error, E_USER_ERROR);
}
$sql="INSERT INTO mqtt_name (tempeture,humidity,light) VALUES ($tempeture,$humidity,$light)";
if($conn->query($sql) === false) {
  trigger_error('Wrong SQL: ' . $sql . ' Error: ' . $conn->error, E_USER_ERROR);
} 
?>

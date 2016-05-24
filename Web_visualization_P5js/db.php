#!/usr/bin/php-cli
<?php
$tempeture = $argv[1];
$humidity = $argv[2];
$light = $argv[3];
$DBServer = ''; 
$DBUser   = '';
$DBPass   = '';
$DBName   = '';  
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

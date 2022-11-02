<?php

$servername = "localhost";
$username = "Abdulönaser";
$password = "OM71BVGjTr8o8!8B";

// Create connection
$conn = new mysqli($servername, $username, $password);
// Check connection
if ($conn->connect_error) {
  die("Connection failed: " . $conn->connect_error);
}

// Create database
$sql = "CREATE DATABASE sensordaten";
if ($conn->query($sql) === TRUE) {
  echo "Database created successfully";
} else {
  echo "Error creating database: " . $conn->error;
}

$conn->close();



echo "<br>";
//Connect to database and create table
$servername = "localhost";
$username = "Abdulönaser";
$password = "OM71BVGjTr8o8!8B";
$dbname = "sensordaten";


// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
	  die("Connection failed: " . $conn->connect_error);
}


$sql = "CREATE TABLE  Sesnoractions(
  id INT(6) UNSIGNED AUTO_INCREMENT PRIMARY KEY,
  action_of_sensor varchar(244),
  date_of_action date,
  time_of_action time
  )";


if ($conn->query($sql) === TRUE) {
      echo "Table Sesnoractions created successfully";
} else {
      echo "Error creating table: " . $conn->error;
  }


$conn->close();

?>
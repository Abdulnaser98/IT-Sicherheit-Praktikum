<?php
//Creates new record as per request
    //Connect to database

    $servername = "db";
    $port = 3306;
    $username = "root";
    $password = "root";
    $dbname = "sensordaten";


    // Create connection
    $conn = new mysqli($servername, $username, $password, $dbname, $port);
    // Check connection
    if ($conn->connect_error) {
        die("Database Connection failed: " . $conn->connect_error);
    }


    //Get current date and time
    date_default_timezone_set('Europe/Berlin');
    $d = date("Y-m-d");
    //echo " Date:".$d."<BR>";
    $t = date("H:i:s");



    $action_of_sensor = $_POST['sensor'];


	$sql = "INSERT INTO Sesnoractions (action_of_sensor, date_of_action, time_of_action) VALUES ('".$action_of_sensor."', '".$d."', '".$t."')";

    //$sql = "INSERT INTO Sesnoractions (action_of_sensor, date_of_action, time_of_action) VALUES ('Hello world very new', '".$d."', '".$t."')";

	if ($conn->query($sql) === TRUE) {
		echo "The connection with the data base has benn succefually established and the data
        now are being transferred from the arduino device to the data base";
	} else {
		echo "Error: " . $sql . "<br>" . $conn->error;
	}





	$conn->close();
?>
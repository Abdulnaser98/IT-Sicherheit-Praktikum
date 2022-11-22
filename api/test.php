<?php
//Creates new record as per request

    //Connect to database

    // Retrive env variable
    $port = 3306;
    $servername = $_ENV['MYSQL_SERVER'];;
    $username = $_ENV['MYSQL_USER_NAME'];;
    $password = $_ENV['MYSQL_PASSWORD'];
    $dbname = $_ENV['MYSQL_DB_NAME'];;


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

	$sql = "INSERT INTO Sesnoractions (action_of_sensor, date_of_action, time_of_action) VALUES ('sensor', '".$d."', '".$t."')";

    //$sql = "INSERT INTO Sesnoractions (action_of_sensor, date_of_action, time_of_action) VALUES ('Hello world very new', '".$d."', '".$t."')";

	if ($conn->query($sql) === TRUE) {
		echo "The connection with the data base has benn succefually established. You're good to go! 😻\n";
	} else {
		echo "Error: " . $sql . "<br>" . $conn->error;
	}





	$conn->close();
?>
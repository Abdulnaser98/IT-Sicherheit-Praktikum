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
    } else {
        echo "The connection with the data base has benn succefually established. You're good to go! 😻\n";
    }

	$conn->close();
?>
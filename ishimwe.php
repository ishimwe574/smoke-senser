<?php

$servername = "localhost";
$username = "root";
$password = "";
$dbname = "smoke_monitor";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);

// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

// Get smoke value
$smoke = $_GET['smoke'];

$sql = "INSERT INTO smoke_data (smoke_level)
VALUES ('$smoke')";

if ($conn->query($sql) === TRUE) {
    echo "Data inserted successfully";
} else {
    echo "Error: " . $conn->error;
}

$conn->close();

?>
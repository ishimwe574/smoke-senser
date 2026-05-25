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

// Select data
$sql = "SELECT * FROM smoke_data ORDER BY created_at DESC";

$result = $conn->query($sql);
?>

<!DOCTYPE html>
<html>
<head>
    <title>Smoke Sensor Dashboard</title>

    <style>
        body{
            font-family: Arial;
            background:#f4f4f4;
            padding:20px;
        }

        h1{
            color:#333;
        }

        table{
            width:100%;
            border-collapse:collapse;
            background:white;
        }

        table, th, td{
            border:1px solid #ccc;
        }

        th{
            background:#222;
            color:white;
            padding:12px;
        }

        td{
            padding:10px;
            text-align:center;
        }

        tr:nth-child(even){
            background:#f2f2f2;
        }

        .danger{
            color:red;
            font-weight:bold;
        }

        .safe{
            color:green;
            font-weight:bold;
        }
    </style>
</head>

<body>

<h1>Smoke Sensor Dashboard</h1>

<table>
    <tr>
        <th>ID</th>
        <th>Smoke Level</th>
        <th>Status</th>
        <th>Date & Time</th>
    </tr>

<?php

if ($result->num_rows > 0) {

    while($row = $result->fetch_assoc()) {

        $status = "";

        if($row["smoke_level"] > 400){
            $status = "<span class='danger'>Smoke Detected</span>";
        } else {
            $status = "<span class='safe'>Air Clean</span>";
        }

        echo "<tr>
                <td>".$row["id"]."</td>
                <td>".$row["smoke_level"]."</td>
                <td>".$status."</td>
                <td>".$row["created_at"]."</td>
              </tr>";
    }

} else {
    echo "<tr><td colspan='4'>No data found</td></tr>";
}

$conn->close();

?>

</table>

</body>
</html>
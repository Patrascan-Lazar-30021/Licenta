<?php
// Database connection parameters
$serverName = "DESKTOP-4Q1KQBE\SQLEXPRESS"; // e.g., "localhost" or "your_server\instance"
$database = "SensorData";
$username = "sensor_admin";
$password = "minge123ct";

// Get the JSON data from the POST request
$data = file_get_contents("php://input");
$json = json_decode($data, true);

if ($json === null) {
    http_response_code(400);
    echo json_encode(["error" => "Invalid JSON"]);
    exit;
}

// Extract data
$temperature = $json['temperature'];
$humidity = $json['humidity'];
$mQ135 = $json['mQ135'];
$mQ7 = $json['mQ7'];

try {
    // Create a new PDO instance
    $conn = new PDO("sqlsrv:Server=$serverName;Database=$database", $username, $password);
    $conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

    // Prepare the SQL statement
    $sql = "INSERT INTO SensorData (temperature, humidity, mQ135, mQ7, timestamp) VALUES (:temperature, :humidity, :mQ135, :mQ7, GETDATE())";
    $stmt = $conn->prepare($sql);

    // Bind parameters
    $stmt->bindParam(':temperature', $temperature);
    $stmt->bindParam(':humidity', $humidity);
    $stmt->bindParam(':mQ135', $mQ135);
    $stmt->bindParam(':mQ7', $mQ7);

    // Execute the statement
    $stmt->execute();

    // Send response
    echo json_encode(["success" => "Data inserted successfully"]);
} catch (PDOException $e) {
    // Handle any errors
    http_response_code(500);
    echo json_encode(["error" => "Database error: " . $e->getMessage()]);
}
?>

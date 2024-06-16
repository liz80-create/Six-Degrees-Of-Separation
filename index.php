<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>6 Degrees of separation</title>
<style>
    body {
        margin: 0;
        padding: 0;
        background-image: url('pic.jpg'); /* Replace 'pic.jpg' with the path to your image */
        background-size: cover; /* Adjust the size as needed */
        background-position: center;
        background-repeat: no-repeat; /* Prevent image from repeating */
        font-family: Arial, sans-serif;
        height: 100vh; /* Ensure the page takes up the full height of the viewport */
        display: flex;
        flex-direction: column;
        align-items: flex-start;
        position: relative; /* Add position relative to allow absolute positioning of the heading */
    }
    h1 {
        color: white;
        font-size: 58px; /* Adjust the font size as needed */
        font-weight: bold; /* Make the font bold */
        margin: 60px 20px 0; /* Add margin to top, right, and left */
    }
    .input-container {
        margin-left: 20px; /* Adjust the margin as needed */
    }
    input[type="text"] {
        width: 300px;
        padding: 8px;
        margin: 30px 10px; /* Adjusted margin to top and bottom */
        border: 1px solid #a7a0a0;
        border-radius: 5px;
        font-size: 14px;
    }
    button {
        padding: 10px 20px;
        border: none;
        background-color:white;
        color: #0a0505;
        border-radius: 5px;
        cursor: pointer;
        font-size: 14px;
        margin-left: 250px; /* Adjust the margin to the left */
        margin-top: 10px; /* Adjusted margin to the top */
    }
    button:hover {
        background-color: #0056b3;
    }
    #output {
    color: white;
    margin-left: 20px;
    margin-top: 20px;
    font-size: 19px; /* Increase font size */
    font-weight: bold; /* Make text bold */
    display: <?php echo ($_SERVER["REQUEST_METHOD"] == "POST") ? "block" : "none"; ?>; /* Display output only if form is submitted */
    white-space: pre-wrap; /* Allow text to wrap */
}
.input-group {
  display: block; /* Make it display as block */
}
</style>
</head>
<body>

<h1>6 Degrees Of Separation</h1>

<div class="input-container">
    <form method="post">
        <div class="input-group">
          <input type="text" name="person1" placeholder="Enter name of Person 1">
          <input type="text" name="person2" placeholder="Enter name of Person 2">
        </div>
        <div class="input-group">
          <button type="submit" name="submit">Get Degree & Path</button>
        </div>
    </form>
</div>

<div id="output">

<?php
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $person1 = $_POST['person1'];
    $person2 = $_POST['person2'];

    // Execute the C++ program with user inputs
    $output = shell_exec("./mainFile " . escapeshellarg($person1) . " " . escapeshellarg($person2));

    // Display the output
    echo "<pre>$output</pre>";
}

?>
</div>

</body>
</html>


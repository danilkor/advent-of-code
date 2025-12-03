<?php 
$file = fopen("input.txt", "r");
$pointer = 50;
$code = 0;
while (!feof($file)) {
    $line = fgets($file);
    $line = trim($line);
    
    if ($line === "") {
        continue; 
    }
    
    if (str_contains($line, "R")) {
        $number = intval(substr($line, 1));
    } elseif (str_contains($line, "L")) {
        $number = -intval(substr($line, 1));
    } else {
        continue; 
    }
    $pointer += $number;
    
    if ($pointer < 0) {
        while ($pointer < 0) {
            $pointer = 100 + $pointer;
        }
    } else if ($pointer > 99) {
        while ($pointer > 99) {
            $pointer = $pointer - 100;
        }
    }
    if ($pointer == 0) {
        $code += 1;
    }

}

echo $code + "\n";



?>
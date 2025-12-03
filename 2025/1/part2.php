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
    $left = true;
    if (str_contains($line, "R")) {
        $left = false;
    } 
    $number = intval(substr($line, 1));
    while ($number > 0) {
        $number--;
        if ($left) {
            $pointer--;
        } else {
            $pointer++;
        }
        if ($pointer == -1) {
            $pointer = 99;
        }
        if ($pointer == 100) {
            $pointer = 0;
        }
        if ($pointer == 0) {
            $code++;
        }
    }
}

echo $code . "\n";



?>
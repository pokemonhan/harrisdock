<?php

# php -dextension=./modules/lgv_rdrand.so demo.php

echo lgv_rdrand_uint32(), PHP_EOL;

$times = 1000000;

$timeStart = microtime(true);

for ($i = 0; $i < $times; $i++) {
    lgv_rdrand_uint32();
}

$timeEnd = microtime(true);
$timeCost = $timeEnd - $timeStart;
$tps = $times / $timeCost;

echo sprintf('time: %fs, tps: %f', $timeCost, $tps), PHP_EOL;

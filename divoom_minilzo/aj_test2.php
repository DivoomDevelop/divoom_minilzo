<?php

    function addByteArray($srcByte, $newByte)
    {
        $id = count($srcByte);
        foreach ($newByte as $ch) {
            $srcByte[$id] = chr($ch);
            $id ++;
        }
        return $srcByte;
    }
	$divoom_test = "\x070123456789 +$\0\v67890123456789\x11\0\0";
	echo strlen($divoom_test);
	$a = array(1,2,3);
	$b = array(4,5,6);
	echo count($a);
	echo count($b);
	$a = addByteArray($a, $b);
	echo count($a);
	$divoom_out =  divoom_minilzo_decompress($divoom_test);
	echo "out is: $divoom_out\n";
	echo strlen($divoom_out);

	$divoom_out = base64_decode($divoom_out, FALSE);
	echo "last data : $divoom_out";
	echo strlen($divoom_out);
?>

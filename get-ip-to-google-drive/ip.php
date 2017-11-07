<?php
/* 
Skrypt wyœwietla IP odwiedzaj¹æego jeœli token to 'wilu' w MD5 
Wersja:04-05-2017
*/
if (isset($_GET['token'])) {
	if ($_GET['token']=='04162ddea246826e7a72497e23c16918') {
		echo '<iptag>'.$_SERVER['REMOTE_ADDR'].'</iptag>';
	}
}
?>
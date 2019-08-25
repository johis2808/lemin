<!doctype html>
<html>
	<head>
		<title>♪ j'ai cale cale l'affaire, laissez laissez moi faire ♪</title>
		<meta charset="utf-8">
		<link rel="stylesheet" href="styles.css" type="text/css" media="screen">
	</head>
	<body>
		<div id="interface">
			<p id="usage">usage : http://localhost:8080/map=?map_name</p>
			<div id="clickables">
				<button id="hide-names">toggle names</button>
				<?php include("./server.php"); ?>
			</div>
		</div>
		<canvas id="canvas-network" class="canvas"></canvas>
		<canvas id="canvas-names" class="canvas"></canvas>
		<script type="text/javascript" src="client.js"></script>
	</body>
</html>

<?php

$error = "no map parameter";
$result_file = "result";

function get_commentdata($str){
	$role = "simple node";
	if ($str == "##start" || $str == "##end")
		$role = substr($str, 2);
	return ($role);
}

function get_coord($line, $nodes){
	$i = 0;
	$max = count($nodes);
	$targets = explode("-", $line);
	$coords = array();
	while ($i < $max) :
		$node = $nodes[$i];
		if ($targets[0] == $node["name"] || $targets[1] == $node["name"]) :
			$coord = array(
				"x" => $node["x"],
				"y" => $node["y"]
			);
			array_push($coords, $coord);
		endif;
		$i += 1;
	endwhile;
	return ($coords);
}

function map_tojson($file){
	$content = file_get_contents($file);
	$lines = explode(PHP_EOL, $content);
	$map = array(
		"nodes"	=> array(),
		"arcs"	=> array()
	);
	$i = 0;
	$max = count($lines) - 1;
	$previous_line = "";
	while($i < $max) :
		if ($i > 0) :
			$line = $lines[$i];
			if (strpos($line, "#") === FALSE) :
				if (strpos($line, "-") === FALSE) :
					$node_data = explode(" ", $line);
					if (isset($_GET['rand']) && $node_data[1] == $node_data[2]):
						$node_data[1] += rand(5, 50);
						$node_data[2] += rand(5, 50);
					endif;
					$new_node = array(
						"role"	=> get_commentdata($previous_line),
						"name"	=> $node_data[0],
						"x"		=> $node_data[1],
						"y"		=> $node_data[2],
					);
					array_push($map["nodes"], $new_node);
				else :
					$new_arc = get_coord($line, $map["nodes"]);
					array_push($map["arcs"], $new_arc);
				endif;	// node or arc
			endif;		// not a comment
		endif; 			// not first line
		$i += 1;
		$previous_line = $line;
	endwhile;
	file_put_contents("map.json", json_encode($map));
	return ($map);
}

function console($str){
	echo '<script>console.log("' . $str . '")</script>';
}

function result_tojson($file, $nodes){
	$content = file_get_contents($file);
	$lines = explode(PHP_EOL, $content);
	$result = array();
	$path = array();
	$i = 0;
	$max = count($lines);
	while ($i < $max) :
		$line = $lines[$i];
		if (strpos($line, ">") == 0 && strlen($line) >= 1) :
			$line_one = explode(" ", $lines[$i]);
			$line_two = explode(" ", $lines[$i + 1]);
			$name_one = $line_one[1];
			$name_two = $line_two[1];
			if (strlen($name_two) >= 1) :
				$new_arc = get_coord($name_one . '-' . $name_two, $nodes);
				array_push($path, $new_arc);
			endif;
		endif;
		if (strlen($line) <= 1) :
			if (count($path) > 1)
				array_push($result, $path);
			$path = [];
		endif;
		$i += 1;
	endwhile;
	$i = 0;
	$max = count($result);
	echo '<div id="paths-list">';
		echo '<input id="check-star" type="checkbox" value="star" name="path-star" checked>';
		echo '<label class="paths-labels" for="path-star">toggle all</label><br>';
	while ($i < $max) :
		echo '<input class="paths-checkboxes" type="checkbox" value="' . $i . '" name="path-' . $i . '" checked>';
		echo '<label class="paths-labels" for="path-' . $i . '">path ' . ($i + 1) . '</label><br>';
		$i += 1;
	endwhile;
	echo '</div>';
	file_put_contents("result.json", json_encode($result));
}

if (isset($_GET["map"])) : 
	$map = $_GET["map"];
	if (file_exists("../" . $map)) :
		$error = "file OK";	
		exec('../lem-in ../' . $map . '> ' . $result_file);
		$map_datas = map_tojson("../" . $map);
		result_tojson($result_file, $map_datas["nodes"]);
	else :
		$error = "map doesn't exists";	
	endif ;
endif;

echo '<script>console.log("PHP says \"' . $error . '\"");</script>';

<?php

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
                "y" => $node["y"],
                "z" => $node["z"]
			);
            array_push($coords, $coord);
            if (count($targets) < 2)
                break ;
		endif;
		$i += 1;
	endwhile;
	return ($coords);
}

function console ($str)
{
    echo '<script>console.log("' . $str . '")</script>';   
}

function get_randcolor($seed){
	$hex_chars = 'ABCDEF0123456789';
	$hex_color = '#';
	$i = 0;
	srand($seed);
	while ($i < 6){
	   $hex_color .= $hex_chars[rand(0, strlen($hex_chars) - 1)];
	   $i += 1;
	}
	return ($hex_color);
}

function map_tojson($file){
	$content = file_get_contents($file);
	$lines = explode(PHP_EOL, $content);
	$map = array(
		"error"	=> "OK",
		"start"	=> array(),
		"nodes"	=> array(),
        "arcs"	=> array(),
        "turns" => array()
	);
	$i = 1;
	$max = count($lines) - 1;
	$previous_line = "";
	while ($i < $max && strlen($lines[$i]) > 1) :
		if ($i > 0) :
			$line = $lines[$i];
			if (strpos($line, "#") === FALSE) :
				if (strpos($line, "-") === FALSE) :
                    $node_data = explode(" ", $line);
                    srand($i);
					$new_node = array(
						"role"	=> get_commentdata($previous_line),
						"name"	=> $node_data[0],
						"x"		=> rand(-10, 10),
                        "y"		=> rand(-10, 10),
                        "z"		=> rand(-10, 10),
					);
					if ($new_node["role"] == "start")
						$map["start"] = $new_node;
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
    $i++;
    while ($i < $max) :
        $line = $lines[$i];
        $ants = explode(" ", $line);
        $j = 0;
        $max_ants = count($ants);
        $new_turn = array();
        while ($j < $max_ants - 1) :
            $ant = $ants[$j];
            $data = explode("-", $ant);
            $tmp = get_coord($data[1], $map["nodes"]);
            $new_ant = array(
				"name" 		=> $data[0],
				"color"		=> get_randcolor(substr($data[0], 1)),
                "position" => $tmp[0]
            );
            array_push($new_turn, $new_ant);
            $j++;
        endwhile;
        array_push($map["turns"], $new_turn);
        $i++;
    endwhile;
	file_put_contents("map.json", json_encode($map));
	return ($map);
}

if (isset($_GET["map"]) && strlen($_GET["map"])) :
    if (file_exists("../" . $_GET["map"])) :
        exec('../lem-in < ../' . $_GET["map"] . ' > map');
		map_tojson("map");
	else : 
		file_put_contents("map.json", json_encode(array("error" => "map not found")));
	endif;
else :
	file_put_contents("map.json", json_encode(array("error" => "indicate a map as GET parameter, like localhost/?map=MAPNAME")));
endif;

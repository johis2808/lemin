var scene = new THREE.Scene();
var camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 1000);
var renderer = new THREE.WebGLRenderer({"antialias": true});

    renderer.setSize(window.innerWidth, window.innerHeight);
    renderer.setClearColor(0xe2e2e2, 1);
    document.body.appendChild(renderer.domElement);
    renderer.domElement.id = "canvas";

    var controls = new THREE.OrbitControls( camera, renderer.domElement );
    camera.position.set( 2, 2, 15 );
    controls.update();



function animate(){
    requestAnimationFrame(function(){animate()});
    controls.update();

    TWEEN.update();
    renderer.render(scene, camera);
    
}

function getRandomColor() {
    var letters = '0123456789ABCDEF';
    var color = '#';
    for (var i = 0; i < 6; i++) {
      color += letters[Math.floor(Math.random() * 16)];
    }
    if (color == "#00ff00" || color == "#ff0000")
        return getRandomColor();
    return color;
  }

function create_sphere(map){

    renderer.setSize(window.innerWidth, window.innerHeight);
    renderer.setClearColor(0xe2e2e2, 1);
    document.body.appendChild(renderer.domElement);
    renderer.domElement.id = "canvas";
    var i = 0;
    var sphereSize = 15 / map.nodes.length;
    if (sphereSize > 2)
        sphereSize = 2

    while (i < map.nodes.length)
    {
        var geometry = new THREE.SphereGeometry( sphereSize, 16, 16 );
        var color = getRandomColor();
        if (map.nodes[i].role == "start")
            color = "#00ff00";
        if (map.nodes[i].role == "end")
            color = "#ff0000";
        var material = new THREE.MeshBasicMaterial( {color: color} );
        var sphere = new THREE.Mesh( geometry, material );
        sphere.position.x = map.nodes[i].x;
        sphere.position.y = map.nodes[i].y;
        sphere.position.z = map.nodes[i].z;
        scene.add( sphere );
        i++;
    }

    i = 0;
    while (i < map.arcs.length){
        var arc = map.arcs[i];
        var a = arc[0];
        var b = arc[1];
        var material = new THREE.LineBasicMaterial( { color: getRandomColor() } );
        var geometry = new THREE.Geometry();
        geometry.vertices.push(new THREE.Vector3(a.x, a.y, a.z) );
        geometry.vertices.push(new THREE.Vector3( b.x, b.y, b.z) );

        var line = new THREE.Line( geometry, material );
        scene.add( line );
        i++;
    }

    i = 0;
    while (i < map.turns[0].length){
       

        let geometry = new THREE.SphereGeometry( sphereSize / 2, 16, 16 ); 
        let material = new THREE.MeshBasicMaterial( {color: getRandomColor() } );
        let ant = new THREE.Mesh( geometry, material );
        ant.position.set(ant.position.x, ant.position.y, ant.position.z);
    
        scene.add( ant );
        
        let j = 0;
        while (j < map.turns[1].length){
            if (map.turns[1][j].name == map.turns[0][i].name)
                var nextPosition = map.turns[1][j].position; 
            j++;
        }      
        let tween = new TWEEN.Tween(map.turns[0][i].position)
                    .to(nextPosition, 10000)
                    .onUpdate(function(){
                        ant.position.x = this.x;
                        ant.position.y = this.y;
                        ant.position.z = this.z;
                    }).start();
    
        i++;
    }

   
 //   console.log(ants);
    animate();    
}

function get_jsonfile(fileName, fn)
{
	var request = new XMLHttpRequest();
	request.overrideMimeType("application/json");
	request.open("GET", "http://localhost:8080/" + fileName + ".json");
	request.addEventListener("load", function (){
        if (request.status >= 200 && request.status < 400){
            console.log(JSON.parse(request.responseText));
            fn(JSON.parse(request.responseText));
        } else
			console.log(request.status + " " + request.statusText);
	});
	request.addEventListener("error", function(){
		console.log("network js error");
	});
	request.send(null);
}

document.addEventListener("DOMContentLoaded", function(){
    get_jsonfile("map", create_sphere); 
});
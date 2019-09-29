var scene = new THREE.Scene();
var camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 1000);
var renderer = new THREE.WebGLRenderer({"antialias": true});

    renderer.setSize(window.innerWidth, window.innerHeight);
    renderer.setClearColor(0xe2e2e2, 1);
    document.body.appendChild(renderer.domElement);
    renderer.domElement.id = "canvas";

    var controls = new THREE.OrbitControls( camera, renderer.domElement );
    camera.position.set( 0, 0, 30 );
    controls.update();

window.addEventListener("resize", function(){
    camera.aspect = window.innerWidth / window.innerHeight;
    camera.updateProjectionMatrix()
    renderer.setSize( window.innerWidth, window.innerHeight )
    renderer.render(scene, camera);
})

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

//    renderer.setSize(window.innerWidth, window.innerHeight);
//    renderer.setClearColor(0xe2e2e2, 1);
//    document.body.appendChild(renderer.domElement);
 //   renderer.domElement.id = "canvas";
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
       // var material = new THREE.LineBasicMaterial( { color: getRandomColor() } );
        var material = new THREE.LineBasicMaterial( { color: "#b3b3b3" } );
        var geometry = new THREE.Geometry();
        geometry.vertices.push(new THREE.Vector3(a.x, a.y, a.z) );
        geometry.vertices.push(new THREE.Vector3( b.x, b.y, b.z) );

        var line = new THREE.Line( geometry, material );
        scene.add( line );
        i++;
    }
    animate();    
}

function getPreviousPosition(antName, thisTurn, turnIndex, startRoom)
{
    var clonedStart = Object.assign({}, startRoom);
    if (!turnIndex)
        return clonedStart;
    var i = 0;
    while (i < thisTurn[turnIndex - 1].length){
        if (antName == thisTurn[turnIndex - 1][i].name)
            return thisTurn[turnIndex - 1][i].position;
        i += 1;
    }
    return clonedStart;
}

function launchAnts(map, turnIndex, previousAnts, startRoom){
    var i = 0;
//    console.log(map.turns[turnIndex])
    while (i < previousAnts.length){
        scene.remove(scene.getObjectByName(previousAnts[i]));
        i += 1;
    }
    previousAnts = [];
    var sphereSize = 15 / map.nodes.length;
    if (sphereSize > 2)
        sphereSize = 2;
    var time = 2500;
    i = 0;
    while (i < map.turns[turnIndex].length){
       
        let thisAnt = map.turns[turnIndex][i];
        let geometry = new THREE.SphereGeometry( sphereSize / 2, 16, 16 ); 
        let material = new THREE.MeshBasicMaterial( {color: thisAnt.color } );
        let ant = new THREE.Mesh( geometry, material );

        var previousPosition = getPreviousPosition(thisAnt.name, map.turns, turnIndex, startRoom);
        ant.position.set(previousPosition.x, previousPosition.y, previousPosition.z);
        ant.name = thisAnt.name;
        previousAnts.push(thisAnt.name);
        scene.add( ant );
      
        let tween = new TWEEN.Tween(previousPosition)
                    .to(map.turns[turnIndex][i].position, time)
                    .onUpdate(function(){
                        ant.position.x = this.x;
                        ant.position.y = this.y;
                        ant.position.z = this.z;
                    }).start();
    
        i++;
    }
    if (turnIndex + 1 < map.turns.length){
        setTimeout(
            function(){ 
                launchAnts(map, turnIndex + 1, previousAnts, startRoom)
            }, 
            time
        );
    }
}

function get_jsonfile(fileName)
{
	var request = new XMLHttpRequest();
	request.overrideMimeType("application/json");
	request.open("GET", "http://localhost:8080/map.json");
	request.addEventListener("load", function (){
        if (request.status >= 200 && request.status < 400){
       //     console.log(JSON.parse(request.responseText));
            var map = JSON.parse(request.responseText);
            if (map.error == "OK"){
                const startRoom = map.start;
                create_sphere(map);
                launchAnts(map, 0, [], startRoom);
            } else {
                document.getElementById("canvas").style.display = 'none';
                alert(map.error);
            }
        } else {
            document.getElementById("canvas").style.display = 'none';
            console.log(request.status + " " + request.statusText);
        }
	});
	request.addEventListener("error", function(){
		console.log("network js error");
	});
	request.send(null);
}

document.addEventListener("DOMContentLoaded", function(){
    get_jsonfile(); 
});
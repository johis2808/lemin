var xMax = 0;
var xMin = 0;
var yMin = 0;
var yMax = 0;
var xStep = 0;
var yStep = 0;
var xShift = 0;
var yShift = 0;
var windowWidth = 0; 
var windowHeight = 0;
var canvas;
var canvasNames;
var ctx;
var ctxNames;
var pointSize = 6;
var pathsLength = 0;

function findMaxCoords(nodes){
	var i = 0;
	var max = nodes.length;
	pointSize = windowHeight / (max * 2);
	while (i < max)
	{
		var node = nodes[i];
		if (parseInt(node.x) < xMin)
			xMin = parseInt(node.x);
		if (parseInt(node.x) > xMax)
			xMax = parseInt(node.x);
		if (parseInt(node.y) < yMin)
			yMin = parseInt(node.y);
		if (parseInt(node.y) > yMax)
			yMax = parseInt(node.y);
		i += 1;
	}
}

function setShifts(){
	var xInterval = xMax - xMin;
	var yInterval = yMax - yMin;
	xShift = pointSize * 2;
	yShift = pointSize * 2;
	if (xMin < 0)
		xShift = (xMin * -1) + (pointSize * 2);
	if (yMin < 0)
		yShift = (yMin * -1) + (pointSize * 2);
	xStep = (windowWidth / 1.3) / xInterval;
	yStep = (windowHeight / 1.4) / yInterval;
}

function centerPosition(point){
	point -= (pointSize / 2);
	return (point);
}

function getPointData(node)
{
	var point = {
		x: (node.x * xStep) + xShift,
		y: (node.y * yStep) + yShift,
		fill: "black",
		role: node.role,
		name: node.name
	};
	point.x = centerPosition(point.x);
	point.y = centerPosition(point.y);
	if (node.role == "start")
		point.fill = "lime";
	if (node.role == "end")
		point.fill = "magenta";
	return (point);
}

function drawNames(nodes){
	var i = 0;
	var max = nodes.length;
	while (i < max){
		var node = getPointData(nodes[i]);
		ctxNames.fillStyle = node.fill;
		if (node.role == "start" || node.role == "end")
			node.name += " (" + node.role + ")";
		ctxNames.fillText(node.name, node.x + pointSize + 5, node.y + pointSize);
		i += 1;
	}
}
function drawNodes(nodes)
{
	var i = 0;
	var max = nodes.length;
	while (i < max)
	{
		var node = getPointData(nodes[i]);
		ctx.fillStyle = node.fill;
		ctx.fillRect(node.x, node.y, pointSize, pointSize);
		ctx.fillStyle = "black";
		i += 1;
	}
}

function getStrockePosition(arc){
	var point = {
		x: (arc.x * xStep) + xShift,
		y: (arc.y * yStep) + yShift
	};
	return (point);
}

function drawArcs(arcs, canvasTarget, color)
{
	var i = 0;
	var max = arcs.length;
	var ctxTarget = canvasTarget.getContext("2d");
	ctxTarget.strokeStyle = color;
	if (color == "black"){
		ctxTarget.setLineDash([1,4]);
		ctxTarget.lineWidth = 1;
	} else {
		var width = pointSize / 3;
		ctxTarget.lineWidth = width;
		var alpha = 1 / pathsLength;
		ctxTarget.globalAlpha = alpha;
		ctxTarget.lineCap = "square";
	}
	while (i < max)
	{
		var arc = arcs[i];
		ctxTarget.beginPath();
		start = getStrockePosition(arc[0]);
		end = getStrockePosition(arc[1]);
		ctxTarget.moveTo(start.x, start.y);
		ctxTarget.lineTo(end.x, end.y);
		ctxTarget.stroke();
		i += 1;
	}
}

function drawMap(map){
	findMaxCoords(map.nodes);
	setShifts();
	drawArcs(map.arcs, canvas, "black");
	drawNodes(map.nodes);
	drawNames(map.nodes);
}

function drawResult(arcs){
	var i = 0;
	var max = arcs.length;
	pathsLength = max;
	while (i < max){
		var arc = arcs[i];
		var newCanvas = document.createElement("canvas");
		newCanvas.id = "path-" + i;
		newCanvas.width = windowWidth;
		newCanvas.height = windowHeight;
		newCanvas.className = "canvas";
		document.body.appendChild(newCanvas);
		drawArcs(arc, newCanvas, "silver");
		i += 1;
	}
}

function get_jsonfile(fileName, fn)
{
	var request = new XMLHttpRequest();
	request.overrideMimeType("application/json");
	request.open("GET", "http://localhost:8080/" + fileName + ".json");
	request.addEventListener("load", function (){
		if (request.status >= 200 && request.status < 400)
			fn(JSON.parse(request.responseText));
		else
			console.log(request.status + " " + request.statusText);
	});
	request.addEventListener("error", function(){
		console.log("network js error");
	});
	request.send(null);
}

function setSizes(){
	windowWidth = window.innerWidth;	
	windowHeight = window.innerHeight;	
	canvas.width = windowWidth;	
	canvas.height = windowHeight;	
	canvasNames.width = windowWidth;	
	canvasNames.height = windowHeight;	
}

function listenInterface(){
	var usage = document.getElementById("usage");
	usage.addEventListener("click", function(){
		document.getElementById("clickables").classList.toggle("hidden");
	});
	hideNamesButton = document.getElementById("hide-names");
	hideNamesButton.addEventListener("click", function(){
		canvasNames.classList.toggle("hidden");
	});
	var boxToggle = document.getElementById("check-star");
	boxToggle.addEventListener("click", function(){
		var checkBoxes = document.getElementsByClassName("paths-checkboxes");
		var i = 0;
		while (i < checkBoxes.length){
			checkBoxes[i].checked = this.checked;
			var target = document.getElementById("path-" + i);
			if (checkBoxes[i].checked)
				target.classList.remove("hidden");
			else
				target.classList.add("hidden");
			i += 1;
		}
	});
	var checkBoxes = document.getElementsByClassName("paths-checkboxes");
	let i = 0;
	while (i < checkBoxes.length){
		checkBoxes[i].addEventListener("click", function(e){
			var target = document.getElementById("path-" + this.value);
			target.classList.toggle("hidden");
		})
		i += 1;
	}
}

document.addEventListener("DOMContentLoaded", function(){
	console.log(":)");
	listenInterface();
	canvas = document.getElementById("canvas-network");
	canvasNames = document.getElementById("canvas-names");
	ctx = canvas.getContext("2d");
	ctx.lineWidth = 1;
	ctxNames = canvasNames.getContext("2d");
	ctx.fillStyle = "black";
	ctx.font = "9px Arial";
	setSizes();
	get_jsonfile("map", drawMap);
	get_jsonfile("result", drawResult);
});

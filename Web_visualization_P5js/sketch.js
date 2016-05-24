/*
This sketch gets the data store in the mySql data base and create a graph wit it
next to this file are:
index.html : The main html of the visualization
connect.php : The main file for the API
db.php : This file is call by the linux partition of the Arduino Yun and is the one in charge
of sending data to the database
subtitution.php : This file is call by the linux partition of the Arduino Yun and is the one in charge
of substitude data every time the user press the button.
*/
var data;
var spaces = [];
var tempetureMax=30;
var humidityMax=80;
var lightMax=900;
var areaWidth;
var areaHeight;

function preload(){
	var url='http://ddwap.mah.se/af7874/connect.php?com=searchAll';
	data=loadJSON(url);
}
function setup(){
	var canvas = createCanvas(windowWidth,windowHeight);
	canvas.parent('container');

	button=createButton('Refresh data');
	button.position(100,40);
	button.mousePressed(reload);
	for (var i = 0; i < data.length; i++) {
		spaces[i]=new space();
	};
	console.log(data.length);
	areaWidth=windowWidth-100;
	areaHeight=windowHeight-150;
}
function draw(){
	background(0);

	stroke(255);

	line(30,windowHeight-50,windowWidth-50,windowHeight-50);
	line(50,100,50,windowHeight-30);

	noStroke();
	fill(255,0,0,100);
	rect(51,100,areaWidth,areaHeight/3);
	fill(255);
	text("Tempeture",55,110);
	fill(200,0,0,100);
	rect(51,100+areaHeight/3,areaWidth,areaHeight/3);
	fill(255);
	text("Humidity",55,110+areaHeight/3);
	fill(200,10,100,100);
	rect(51,100+((areaHeight/3)*2),areaWidth,areaHeight/3);
	fill(255);
	text("Light",55,110+((areaHeight/3)*2));

	if(data.length>0){
		for (var i = 0; i < data.length; i++) {
			spaces[i].area((areaWidth/data.length*i)+51,areaWidth/data.length,i);
		};
		stroke(255);
		noFill();
		beginShape();
		for (var i = 0; i < data.length; i++) {
			var mapTempeture=map(data[i].tempeture,0,tempetureMax,0,areaHeight/3);
			vertex((i*areaWidth/data.length)+(50+((areaWidth/data.length)/2)),mapTempeture+100);
		}
		endShape();
		beginShape();
		for (var i = 0; i < data.length; i++) {
			var mapHumidity=map(data[i].humidity,0,humidityMax,0,areaHeight/3);
			vertex((i*areaWidth/data.length)+(50+((areaWidth/data.length)/2)),mapHumidity+(100+areaHeight/3));
		}
		endShape();
		beginShape();
		for (var i = 0; i < data.length; i++) {
			var mapLight=map(data[i].light,0,lightMax,0,areaHeight/3);
			vertex((i*areaWidth/data.length)+(50+((areaWidth/data.length)/2)),mapLight+(100+((areaHeight/3)*2)));
		}
		endShape();
	}
}
function space(){
	this.a=255;
	this.timeStamp="";
	this.x;
	this.w;
	this.area=function(x,w,i){
		this.x=x;
		this.w=w;
		fill(255,this.a)
		rect(x,99,w,windowHeight-150);
		fill(255);
		ellipse(this.x+(this.w/2),windowHeight-50,5,5);
		if((mouseX>this.x)&&(mouseX<this.x+this.w)&&(mouseY>100)&&(mouseY<windowHeight-50)){
			this.a=100;
			text("Time Stamp: "+data[i].time,300,50);
			text("Tempeture: "+data[i].tempeture,520,50);
			text("Humidity: "+data[i].humidity,650,50);
			text("Light: "+data[i].light,800,50);
		}else{
			this.a=0;
		}
	}
}
function reload(){
	window.location.reload();
}

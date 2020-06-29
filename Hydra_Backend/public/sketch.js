let HOST = location.origin.replace(/^http/, 'ws')
let ws = new WebSocket(HOST);
let el;

let x;
let y;
let col;
let lightStatus;

ws.onmessage = (event) => {
    var res = event.data.split(" ");
    
    if (res.length > 1) {
        if (res[0] === 'X:') {
            x = parseFloat(res[1]);
            y = parseFloat(res[3]);
        }

        if (res[0] === "Color:") {
            console.log("Color");
            col = color(parseFloat(res[1]), parseFloat(res[2]), parseFloat(res[3]));
        }

    }
};

function setup() {
    
    var canvas = createCanvas(1280, 720);
    col = color(0, 0, 0);
    
    x = 0.5 * width;
    y = 0.5 * height;

    canvas.parent('sketch-div');
    background(32);
    textAlign(CENTER, CENTER);
    textSize(48);
    lightStatus = 1;

}

function draw() {

    background(255);
    fill(255, 0, 0);
    rect(0, 0, 0.5 * width, height);
    fill(255);
    text("OFF", 0.25 * width, 0.5 * height);
    fill(0, 255, 0);
    rect(0.5 * width, 0, 0.5 * width, height);
    fill(255);
    text("ON", 0.75 * width, 0.5 * height);

    noFill();
    stroke(255);
    strokeWeight(5);
    if (lightStatus == 0) ellipse( 0.25 * width, 0.5 * height, 200, 200);
    if (lightStatus == 1) ellipse( 0.75 * width, 0.5 * height, 200, 200);

}

function mouseClicked() {

    if (mouseX < 0.5 * width) {
        ws.send("0");
        lightStatus = 0;
        console.log("OFF");
    }

    else {
        lightStatus = 1;
        ws.send("1");
        console.log("ON");
    }
}
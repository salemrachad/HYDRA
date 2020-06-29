//let HOST = location.origin.replace(/^http/, 'ws')
//let ws = new WebSocket(HOST);

/* ws.onmessage = (event) => {
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
 */
function setup() {
    createCanvas(windowWidth,windowHeight);
    background(0);    

}

function draw() {

    background(0);
    locateElement("logo", 20, 20, 100, 100);
    locateElement("graphs", 20, 200, 400, 300);
    locateElement("badgets", 20, 600, 400, 150);
 
}

function locateElement(name, x, y, w, h) {
    fill(150);
    rect(x, y, w, h);
    fill(255);
    text(name, x, y + h + 20);
}
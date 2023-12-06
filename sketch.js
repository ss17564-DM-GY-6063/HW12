// serial variables
let mSerial;
let connectButton;
let readyToReceive;

// project variables
let color = {
  r: 255,
  g: 255,
  b: 255,
};


function receiveSerial() {
  let line = mSerial.readUntil("\n");
  trim(line);
  if (!line) return;

  if (line.charAt(0) != "{") {
    print("error: ", line);
    readyToReceive = true;
    return;
  }

  // get data from Serial string
  let data = JSON.parse(line).data;
  // print(data);
  // return;
  let a0 = data.A0;
  let a1 = data.A1;
  let a6 = data.A6;

  // // use data to update project variables
  
    color.r = map(a0.value, 0, 4095, 0, 255);
    color.g = map(a1.value, 0, 4095, 0, 255);
    color.b = map(a6.value, 0, 4095, 0, 255);


  // serial update
  readyToReceive = true;
}

function connectToSerial() {
  if (!mSerial.opened()) {
    mSerial.open(9600);

    readyToReceive = true;
    connectButton.hide();
  }
}

function setup() {
  // setup project
  createCanvas(windowWidth, windowHeight);

  // setup serial
  readyToReceive = false;

  mSerial = createSerial();

  connectButton = createButton("Connect To Serial");
  connectButton.position(width / 2, height / 2);
  connectButton.mousePressed(connectToSerial);
}

function draw() {
  // project logic
  background(0);
    fill(color.r, color.g, color.b);
    ellipse(width/2, height/2, 300, 300);

  // update serial: request new data
  if (mSerial.opened() && readyToReceive) {
    readyToReceive = false;
    mSerial.clear();
    mSerial.write(0xab);
  }

  // update serial: read new data
  if (mSerial.availableBytes() > 8) {
    receiveSerial();
  }
}

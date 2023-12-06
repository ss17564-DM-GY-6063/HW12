#include <ArduinoJson.h>

// project variables
int a0Val;
int a1Val;
int a6Val;

void sendData() {
  StaticJsonDocument<128> resJson;
  JsonObject data = resJson.createNestedObject("data");
  JsonObject A0 = data.createNestedObject("A0");
  JsonObject A1 = data.createNestedObject("A1");
  JsonObject A6 = data.createNestedObject("A6");

  A0["value"] = a0Val;
  A1["value"] = a1Val;
  A6["value"] = a6Val;

  String resTxt = "";
  serializeJson(resJson, resTxt);

  Serial.println(resTxt);
}

void setup() {
  // Serial setup
  Serial.begin(9600);
  while (!Serial) {}
}

void loop() {
  // read pins
  a0Val = analogRead(A0);
  a1Val = analogRead(A1);
  a6Val = analogRead(A6);

  // check if there was a request for data, and if so, send new data
  if (Serial.available() > 0) {
    int byteIn = Serial.read();
    if (byteIn == 0xAB) {
      // Serial.flush();
      sendData();
    }
  }

  Serial.println(a0Val);
  delay(20);
}



// void setup() {
//   Serial.begin(9600);
// }

// void loop() {
//   int a0v = analogRead(A0);
//   int a1v = analogRead(A1);
//   int a6v = analogRead(A6);

//   if(Serial.available()>0) {
//     int inByte = Serial.read();
//     if(inByte == 10) {
//       Serial.flush();
//       Serial.println(a0v);
//     }
//   }

//   Serial.println(a0v);
//   delay(10);
// }

 
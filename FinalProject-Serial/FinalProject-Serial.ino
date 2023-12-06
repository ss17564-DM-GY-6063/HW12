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
      Serial.flush();
      sendData();
    }
  }

  // Serial.println(String(a0Val) + " " + a1Val + " " + a6Val);
  delay(20);
}

 
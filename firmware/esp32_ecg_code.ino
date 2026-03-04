#include <ESP8266WiFi.h>
#include <WebSocketsServer.h>

// ======================================================
// WIFI CONFIG
// ======================================================
const char* ssid     = "hehhl";
const char* password = "harris96";

// ======================================================
// WEBSOCKET
// ======================================================
WebSocketsServer webSocket = WebSocketsServer(81);

// ======================================================
// MUX SELECT PINS (74HC4052)
// ======================================================
const int S0 = 12;  // D6
const int S1 = 14;  // D5

void setLead(int lead) {
  // lead = 1,2,3
  switch (lead) {
    case 1:   // Lead I → S1=0, S0=0
      digitalWrite(S1, LOW);
      digitalWrite(S0, LOW);
      Serial.println("Switched to Lead I");
      break;

    case 2:   // Lead II → S1=0, S0=1
      digitalWrite(S1, LOW);
      digitalWrite(S0, HIGH);
      Serial.println("Switched to Lead II");
      break;

    case 3:   // Lead III → S1=1, S0=0
      digitalWrite(S1, HIGH);
      digitalWrite(S0, LOW);
      Serial.println("Switched to Lead III");
      break;
  }
}

// ======================================================
// SETUP
// ======================================================
void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println();
  Serial.println("ECG WebSocket Sender (STA Mode)");

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);

  // Start with Lead I
  setLead(1);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("Connected! IP Address: ");
  Serial.println(WiFi.localIP());

  // Start WebSocket server
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);

  Serial.println("WebSocket server started on port 81");
}

// WEBSOCKET EVENT HANDLER
void webSocketEvent(uint8_t clientNum, WStype_t type, uint8_t * payload, size_t length) {

  if (type == WStype_CONNECTED) {
    Serial.printf("[Client %u] Connected.\n", clientNum);
  }

  else if (type == WStype_DISCONNECTED) {
    Serial.printf("[Client %u] Disconnected.\n", clientNum);
  }

  else if (type == WStype_TEXT) {
    String cmd = String((char*)payload);

    if (cmd == "lead1") setLead(1);
    if (cmd == "lead2") setLead(2);
    if (cmd == "lead3") setLead(3);
  }
}

// MAIN LOOP
void loop() {
  webSocket.loop();

  int ecgValue = analogRead(A0);

  // send value
  String valStr = String(ecgValue);
  webSocket.broadcastTXT(valStr);

  Serial.println(valStr);

  delay(10); // ≈250 Hz sampling
}
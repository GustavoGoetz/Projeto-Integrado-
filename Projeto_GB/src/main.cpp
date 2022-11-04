#include <Arduino.h>
// Import required libraries
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

// Replace with your network credentials
const char* ssid = "CLARO_2G7E9C5C";
const char* password = "sol060293";

const char* http_username = "admin";
const char* http_password = "password";

const char* PARAM_INPUT_1 = "state";

const int output = 2;

int sensor = 13;
int sensor1 = 12;
int sensor2 = 14;
int sensor3 = 27;
int aux = 100;

String readNivel() {
  int estado  =  digitalRead(sensor);
  int estado1 =  digitalRead(sensor1);
  int estado2 =  digitalRead(sensor2);
  int estado3 =  digitalRead(sensor3);
  if (estado  == 1 && estado1 == 1 && estado2 == 1 && estado3 == 1){ 
    aux = 100;
    Serial.println(aux);
    digitalWrite(output,LOW);
    return String(aux);
  }else if (estado  == 1 && estado1 == 1 && estado2 == 1 && estado3 == 0){
    aux = 75;
    Serial.println(aux);
    return String(aux);
  }else if (estado  == 1 && estado1 == 1 && estado2 == 0 && estado3 == 0){
    aux = 50;
    Serial.println(aux);
    return String(aux);
  }else if (estado  == 1 && estado1 == 0 && estado2 == 0 && estado3 == 0){
    aux = 25;
    Serial.println(aux);
    digitalWrite(output,HIGH);
    return String(aux);
  }else if (estado  == 0 && estado1 == 0 && estado2 == 0 && estado3 == 0){
    aux = 0;
    Serial.println(aux);
    digitalWrite(output,HIGH);
    return String(aux);
  } else {
    aux = 99999;
    Serial.println(aux);
    return "--";
  }
  delay(100);
}

// Create AsyncWebServer object on port 80
AsyncWebServer server(8088);

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta http-equiv="refresh" content="10">
  <title>ESP Web Server</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
  <link rel="icon" href="data:,">
  <style>
    html {font-family: Arial; display: inline-block; text-align: center;}
    p { font-size: 1.2rem;}
    body {max-width: 600px; margin:0px auto; padding-bottom: 10px;}
    .topnav { overflow: hidden; background-color: #50B8B4; color: white; font-size: 1rem; }
    .content { padding: 20px; }
    .card { background-color: white; box-shadow: 2px 2px 12px 1px rgba(140,140,140,.5); }
    .cards { max-width: 800px; margin: 0 auto; display: grid; grid-gap: 2rem; grid-template-columns: repeat(auto-fit, minmax(200px, 1fr)); }
    .reading { font-size: 1.4rem; }
    .switch {position: relative; display: inline-block; width: 120px; height: 68px} 
    .switch input {display: none}
    .slider {position: absolute; top: 0; left: 0; right: 0; bottom: 0; background-color: #ccc; border-radius: 34px}
    .slider:before {position: absolute; content: ""; height: 52px; width: 52px; left: 8px; bottom: 8px; background-color: #fff; -webkit-transition: .4s; transition: .4s; border-radius: 68px}
    input:checked+.slider {background-color: #2196F3}
    input:checked+.slider:before {-webkit-transform: translateX(52px); -ms-transform: translateX(52px); transform: translateX(52px)}
  </style>
</head>
<body>
  <h2>Trabalho GB Sistemas Distribuidos</h2>
</div>
  <div class="content">
    <div class="cards">
      <div class="card">
        <p><i class="fas fa-water" style="color:#059e8a;"></i> Nivel caixa d'agua</p><p><span class="reading"><span id="temp">%NIVEL%</span> &percnt;</span></p>
        <progress id="file" value=%NIVEL% max="100"></progress>
      </div>
    </div>
  </div>

  <p>Acionamento Motor - <span id="state">%STATE%</span></p>
  %BUTTONPLACEHOLDER%
  <button onclick="logoutButton()">Logout</button>
<script>
function toggleCheckbox(element) {
  var xhr = new XMLHttpRequest();
  if(element.checked){ 
    xhr.open("GET", "/update?state=1", true); 
    document.getElementById("state").innerHTML = "Ligado";  
  }
  else { 
    xhr.open("GET", "/update?state=0", true);     
    document.getElementById("state").innerHTML = "Desligado";      
  }
  xhr.send();
}
function logoutButton() {
  var xhr = new XMLHttpRequest();
  xhr.open("GET", "/logout", true);
  xhr.send();
  setTimeout(function(){ window.open("/logged-out","_self"); }, 1000);
}
</script>
</body>
</html>
)rawliteral";

const char logout_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
</head>
<body>
  <p>Logged out or <a href="/">return to homepage</a>.</p>
  <p><strong>Note:</strong> close all web browser tabs to complete the logout process.</p>
</body>
</html>
)rawliteral";

String outputState(){
  if(digitalRead(output)){
    return "checked";
  }
  else {
    return "";
  }
  return "";
}

// Replaces placeholder with button section in your web page
String processor(const String& var){
  //Serial.println(var);
  if(var == "BUTTONPLACEHOLDER"){
    String buttons ="";
    String outputStateValue = outputState();
    buttons+= "<p><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"output\" " + outputStateValue + "><span class=\"slider\"></span></label></p>";
    return buttons;
  }
  if (var == "STATE"){
    if(digitalRead(output)){
      return "Ligado";
    }
    else {
      return "Desligado";
    }
  }
    if(var == "NIVEL"){
    return readNivel();
  }
  return String();
}

void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
  pinMode(sensor, INPUT);
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
    
  pinMode(output, OUTPUT);
  digitalWrite(output, LOW);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    if(!request->authenticate(http_username, http_password))
      return request->requestAuthentication();
    request->send_P(200, "text/html", index_html, processor);
  });
    
  server.on("/logout", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(401);
  });

  server.on("/logged-out", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", logout_html, processor);
  });
  
  server.on("/nivel", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readNivel().c_str());
  });
  // Send a GET request to <ESP_IP>/update?state=<inputMessage>
  server.on("/update", HTTP_GET, [] (AsyncWebServerRequest *request) {
    if(!request->authenticate(http_username, http_password))
      return request->requestAuthentication();
    String inputMessage;
    String inputParam;
    // GET input1 value on <ESP_IP>/update?state=<inputMessage>
    if (request->hasParam(PARAM_INPUT_1)) {
      inputMessage = request->getParam(PARAM_INPUT_1)->value();
      inputParam = PARAM_INPUT_1;
      if (aux != 100){
        digitalWrite(output, inputMessage.toInt());
      }
    }
    else {
      inputMessage = "No message sent";
      inputParam = "none";
    }
    Serial.println(inputMessage);
    request->send(200, "text/plain", "OK");
  });
  
  // Start server
  server.begin();
}
  
void loop() {
}
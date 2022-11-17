#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <WiFiClientSecure.h>

// Credenciais da rede
const char* ssid = "Arsenal";
const char* password = "liverpool";

// MQTT setup
#define MQTT_ID  "client_sistemas_distribuidos_2022"
#define MQTT_BROKER "c890702cc136431aa4ba1888306440ef.s1.eu.hivemq.cloud"
#define MQTT_PORT 8883
#define MQTT_TOPIC "sist_dist_2022_uni"
#define MQTT_USER "sis_dis"
#define MQTT_PWD "sisdis2022"
#define TOPICO_MOTOR "esp/motor"
#define TOPICO_NIVEL "esp/nivel"
#define TOPICO_STA_MOTOR "esp/status/motor"

int motorStatus = 0;
int sensor = 13;
int sensor1 = 12;
int sensor2 = 14;
int sensor3 = 27;
int aux = 100;
int prioridade = 0;
int acionar_motor = 0;
int externo = 0;
char dado[1] = {0};

WiFiClientSecure espClient;
//WiFiClient espClient;
PubSubClient MQTT(espClient);

#define motor 2

// Create AsyncWebServer
//AsyncWebServer server(8081);

int readNivel() {
  int estado  =  digitalRead(sensor);
  int estado1 =  digitalRead(sensor1);
  int estado2 =  digitalRead(sensor2);
  int estado3 =  digitalRead(sensor3);
  if (estado  == 1 && estado1 == 1 && estado2 == 1 && estado3 == 1){ 
    aux = 100;
    Serial.println(aux);
    acionar_motor = 0;
   //digitalWrite(motor,LOW);
    return aux;
  }else if (estado  == 1 && estado1 == 1 && estado2 == 1 && estado3 == 0){
    aux = 75;
    Serial.println(aux);
    return aux;
  }else if (estado  == 1 && estado1 == 1 && estado2 == 0 && estado3 == 0){
    aux = 50;
    Serial.println(aux);
    return aux;
  }else if (estado  == 1 && estado1 == 0 && estado2 == 0 && estado3 == 0){
    aux = 25;
    Serial.println(aux);
    acionar_motor = 1;
   // digitalWrite(motor,HIGH);
    return aux;
  }else if (estado  == 0 && estado1 == 0 && estado2 == 0 && estado3 == 0){
    aux = 0;
    acionar_motor = 1;
    Serial.println(aux);
    //digitalWrite(motor,HIGH);
    return aux;
  } else {
    aux = 999;
    Serial.println(aux);
    return aux;
  }
  delay(100);
}

void mqtt_callback(char* topic, byte* payload, unsigned int length) 
{
    String msg;
    int val_motor;
  
    /* obtem a string do payload recebido */
    for(int i = 0; i < length; i++) 
    {
       char c = (char)payload[i];
       msg += c;
    }
 
    Serial.print("Chegou a seguinte string via MQTT: ");
    Serial.println(msg);
    
    /* toma ação dependendo da string recebida */
    if (msg.equals("1"))
    {
       acionar_motor = 1;
    }
  
    if (msg.equals("0"))
    {   
      acionar_motor = 0;
    }

}

static const char *root_ca PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIFazCCA1OgAwIBAgIRAIIQz7DSQONZRGPgu2OCiwAwDQYJKoZIhvcNAQELBQAw
TzELMAkGA1UEBhMCVVMxKTAnBgNVBAoTIEludGVybmV0IFNlY3VyaXR5IFJlc2Vh
cmNoIEdyb3VwMRUwEwYDVQQDEwxJU1JHIFJvb3QgWDEwHhcNMTUwNjA0MTEwNDM4
WhcNMzUwNjA0MTEwNDM4WjBPMQswCQYDVQQGEwJVUzEpMCcGA1UEChMgSW50ZXJu
ZXQgU2VjdXJpdHkgUmVzZWFyY2ggR3JvdXAxFTATBgNVBAMTDElTUkcgUm9vdCBY
MTCCAiIwDQYJKoZIhvcNAQEBBQADggIPADCCAgoCggIBAK3oJHP0FDfzm54rVygc
h77ct984kIxuPOZXoHj3dcKi/vVqbvYATyjb3miGbESTtrFj/RQSa78f0uoxmyF+
0TM8ukj13Xnfs7j/EvEhmkvBioZxaUpmZmyPfjxwv60pIgbz5MDmgK7iS4+3mX6U
A5/TR5d8mUgjU+g4rk8Kb4Mu0UlXjIB0ttov0DiNewNwIRt18jA8+o+u3dpjq+sW
T8KOEUt+zwvo/7V3LvSye0rgTBIlDHCNAymg4VMk7BPZ7hm/ELNKjD+Jo2FR3qyH
B5T0Y3HsLuJvW5iB4YlcNHlsdu87kGJ55tukmi8mxdAQ4Q7e2RCOFvu396j3x+UC
B5iPNgiV5+I3lg02dZ77DnKxHZu8A/lJBdiB3QW0KtZB6awBdpUKD9jf1b0SHzUv
KBds0pjBqAlkd25HN7rOrFleaJ1/ctaJxQZBKT5ZPt0m9STJEadao0xAH0ahmbWn
OlFuhjuefXKnEgV4We0+UXgVCwOPjdAvBbI+e0ocS3MFEvzG6uBQE3xDk3SzynTn
jh8BCNAw1FtxNrQHusEwMFxIt4I7mKZ9YIqioymCzLq9gwQbooMDQaHWBfEbwrbw
qHyGO0aoSCqI3Haadr8faqU9GY/rOPNk3sgrDQoo//fb4hVC1CLQJ13hef4Y53CI
rU7m2Ys6xt0nUW7/vGT1M0NPAgMBAAGjQjBAMA4GA1UdDwEB/wQEAwIBBjAPBgNV
HRMBAf8EBTADAQH/MB0GA1UdDgQWBBR5tFnme7bl5AFzgAiIyBpY9umbbjANBgkq
hkiG9w0BAQsFAAOCAgEAVR9YqbyyqFDQDLHYGmkgJykIrGF1XIpu+ILlaS/V9lZL
ubhzEFnTIZd+50xx+7LSYK05qAvqFyFWhfFQDlnrzuBZ6brJFe+GnY+EgPbk6ZGQ
3BebYhtF8GaV0nxvwuo77x/Py9auJ/GpsMiu/X1+mvoiBOv/2X/qkSsisRcOj/KK
NFtY2PwByVS5uCbMiogziUwthDyC3+6WVwW6LLv3xLfHTjuCvjHIInNzktHCgKQ5
ORAzI4JMPJ+GslWYHb4phowim57iaztXOoJwTdwJx4nLCgdNbOhdjsnvzqvHu7Ur
TkXWStAmzOVyyghqpZXjFaH3pO3JLF+l+/+sKAIuvtd7u+Nxe5AW0wdeRlN8NwdC
jNPElpzVmbUq4JUagEiuTDkHzsxHpFKVK7q4+63SM1N95R1NbdWhscdCb+ZAJzVc
oyi3B43njTOQ5yOf+1CceWxG1bQVs5ZufpsMljq4Ui0/1lvh+wjChP4kqKOJ2qxq
4RgqsahDYVvTH9w7jXbyLeiNdd8XM2w9U/t7y0Ff/9yi0GE44Za4rF2LN9d11TPA
mRGunUHBcnWEvgJBQl9nJEiU0Zsnvgc/ubhPgXRR4Xq37Z0j4r7g1SgEEzwxA57d
emyPxgcYxn/eR44/KJ4EBs+lVDR3veyJm+kXQ99b21/+jh5Xos1AnX5iItreGCc=
-----END CERTIFICATE-----
)EOF";

void setupMQTT(){
  MQTT.setServer(MQTT_BROKER, MQTT_PORT);
  MQTT.setCallback(mqtt_callback);    

  while(!MQTT.connected())
  {
     Serial.println("Connecting to MQTT..");
     //Serial.println(MQTT_BROKER);
     if(MQTT.connect(MQTT_ID, MQTT_USER, MQTT_PWD))
     {
        Serial.println("Conectado!");
        MQTT.subscribe(TOPICO_MOTOR);
     }
     else{
        Serial.println("Falha ao conectar!");
        Serial.print(MQTT.state());
        delay(5000);
     }
  }
}

void setupWifi(){
  // Wi-Fi 
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println(WiFi.localIP());
  espClient.setCACert(root_ca);

}

void setup() {
  Serial.begin(115200);
   pinMode(motor, OUTPUT);
   digitalWrite(motor,LOW);
   setupWifi();
   setupMQTT();
   sprintf(dado,"%d", motorStatus); 
   MQTT.publish(TOPICO_MOTOR, dado);
}

void loop() {
  char nivel[3] = {0};
  int valor_motor;
  char text_status[20];

   int aux = readNivel();
   sprintf(nivel,"%d", aux); 
   if(aux <= 25)
   {
    digitalWrite(motor,HIGH); 
    motorStatus = 1;
    acionar_motor = 1;
    sprintf(dado,"%d", motorStatus); 
    MQTT.publish(TOPICO_MOTOR, dado);
    MQTT.publish(TOPICO_NIVEL, nivel);
   }

   if(aux> 25 && aux < 100)
   {
      if(acionar_motor == 0 )
      {
        digitalWrite(motor,LOW);
      }
      if(acionar_motor == 1)
      {
        digitalWrite(motor,HIGH);

      }
    MQTT.publish(TOPICO_NIVEL, nivel);
    valor_motor = digitalRead(motor);

   }
  
   if(aux == 100)
   {
    digitalWrite(motor,LOW);
    acionar_motor = 0;
    motorStatus = 0;
    sprintf(dado,"%d", motorStatus); 
    MQTT.publish(TOPICO_MOTOR, dado);
    MQTT.publish(TOPICO_NIVEL, nivel);
   }

   if(aux == 999)
   {
    Serial.println("Falha no sensor!");
    digitalWrite(motor,LOW);
    MQTT.publish(TOPICO_NIVEL, nivel);
   }


  motorStatus = digitalRead(motor);
  if(motorStatus == 1)
  {
    strcpy(text_status,"Motor Ligado!");
    MQTT.publish(TOPICO_STA_MOTOR, text_status);

  }
  else{
    strcpy(text_status,"Motor Desligado!");
    MQTT.publish(TOPICO_STA_MOTOR, text_status);  

  }
   delay(3000);
  Serial.println("Enviado dados para o Broker");
  MQTT.loop();

}



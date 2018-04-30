// 27 abril 2018
//Programa en el ESP8266 para conectar a WIFI y mandar los estados OPEN y CLOSE de la puerta 
// strings enviados a topico Puerta usando mqtt

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.

const char* ssid = "WIFIssid";
const char* password = "WIFIpassword";
const char* mqtt_server = "XXX.XX.XX.XXX";//direccion del server

int door  = 5;//D1 recibe señal de estado door
int door_state = 0;//inicio abierto
int last_door_state = 0;

WiFiClient espClient;
PubSubClient client(espClient);

String mac = "";

void setup() {
 Serial.begin(115200);
  
 pinMode(door, INPUT);

  // We start by connecting to a WiFi network
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
/////////////////////////Conectar wifi///////////////  
   unsigned long escape = millis();
  while (WiFi.status() != WL_CONNECTED) {
    // Serial.println(".");
    delay(50);  
     if (millis() - escape > 10000) {
      Serial.println(millis() - escape);
      Serial.println("No se conecto a el wifi,");
      ESP.deepSleep(1e6);                      //duerme
    }        
  }
   Serial.println(millis() - escape);
   Serial.print(',');
   Serial.println("se conecto el wifi,"); 

 mac = WiFi.macAddress();            

  ////////  lectura del voltaje////////////
//int lectura = analogRead(A0);
//double voltaje = ((lectura / 1024.0) * 3.25);
 
 //////////////////////////////////////////

client.setServer(mqtt_server, 1883);

//////////////conectar a mqtt////////////

  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    //String clientId = "ESP8266Client-";
   // clientId += String(random(0xffff), HEX);
    
    // Attempt to connect Mac address
    if (client.connect(mac.c_str())) {
      Serial.println("connected");
  
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(2000);
    }
  }

   
//////////////////////////////// construye el mensaje////////////
}

void loop(){
door_state = digitalRead(door);
 
 if(door_state != last_door_state){
  if(door_state == HIGH){
    client.publish("Puerta", "close");
    Serial.printf("close");
    
  }
 }
  else{
    client.publish("Puerta", "open");//topico Puerta del mqtt donde se publica estado
    Serial.printf("open");
    }
 last_door_state=door_state;
    delay(1);
   // Serial.println("Going to deep sleep until door state changes");
   // Serial.println();
    ESP.deepSleep(0);//go to sleep until door state changes
    delay(1000);
}


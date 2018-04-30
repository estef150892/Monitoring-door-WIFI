//programa para ESP en donde lea el estado de la puerta abierto o cerrado
// y se duerma despues de reportar y que se despierte hasta que detecte los cambios en 
// la puerta POR SERIAL

int door  = 5;//D1 recibe señal de estado door
int door_state = 0;//inicio abierto
int last_door_state = 0;


void setup() {
  Serial.begin(9600);
  Serial.setTimeout(2000);
  
  pinMode(door, INPUT);

  //espera que el serial se inicialice
  while(!Serial){}
  
  Serial.println();

}

void loop() {
 door_state = digitalRead(door);
 
 if(door_state != last_door_state){
  if(door_state == HIGH){
    Serial.println("close");//cerrado
  }
 }
  else{
    Serial.println("open");//abierto
    }
 last_door_state=door_state;
    delay(1);
    Serial.println("Going to deep sleep until door state changes");
    Serial.println();
    ESP.deepSleep(0);//go to sleep until door state changes
    delay(1000);
}


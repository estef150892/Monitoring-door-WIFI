//programa para ESP en donde lea el estado de la puerta abierto o cerrado
// y se duerma despues de reportar y que se despierte hasta que detecte los cambios en 
// la puerta

int state = 14; //D5 Indicador de open o close
int door  = 5;//D1 recibe señal de estado door


void setup() {
  pinMode(state, OUTPUT);
  pinMode(door, INPUT);

}

void loop() {
 
 if(digitalRead(door) == HIGH){
  digitalWrite(state,HIGH);//cerrado
  }
  else{
    digitalWrite(state,LOW);//abierto
    }
    delay(1);
    ESP.deepSleep(0);//go to sleep until door state changes
    delay(1000);
}


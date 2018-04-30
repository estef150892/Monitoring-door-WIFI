const int wakeESP = 11;//send low pulse to RST to wake
const int door = 2;//INT0 Pin 2. read state of door sensor
const int LED = 13; // tell esp if open or close

volatile int door_state = 0; // puerta abierta Estado inicial
int door_state1 = 0;
int last_door_state = 0;

void setup() {
  pinMode(wakeESP, OUTPUT); // low pulse to RST
  pinMode(door, INPUT); //Magnetic contact sensor como entrada
  pinMode(LED, OUTPUT);//Tell ESP if its closed or opened
  attachInterrupt(0,pin_ISR,CHANGE);
}

void loop() {
  door_state1 = digitalRead(door);

  if(door_state1 != last_door_state){
    //send low pulse
    digitalWrite(wakeESP, LOW);
    delay(2);
    digitalWrite(wakeESP,HIGH);
    }
    last_door_state=door_state1;
}

void pin_ISR(){
  //sent state open or close to ESP while HIGH close and LOW open
  door_state = digitalRead(door);
  digitalWrite(LED,door_state);
  }

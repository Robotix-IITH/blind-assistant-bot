/* Complete Guide for Ultrasonic Sensor HC-SR04
 *
    Ultrasonic sensor Pins:
        VCC: +5VDC
        Trig : Trigger (INPUT) - Pin11
        Echo: Echo (OUTPUT) - Pin 12
        GND: GND
 */
 

int trig_r = 7;
int echo_r = 8;

int trig_m = 9;
int echo_m = 10;

int trig_l = 11;
int echo_l = 12;

int ML_1 = 6;
int ML_2 = 5;

int MR_1 = 4;
int MR_2 = 3;

long d_l, d_m, d_r;// distances (in cm)

void setup() {
  Serial.begin(9600);

  pinMode(trig_m, OUTPUT);
  pinMode(trig_r, OUTPUT);
  pinMode(trig_l, OUTPUT);

  pinMode(echo_m, INPUT);
  pinMode(echo_r, INPUT);
  pinMode(echo_l, INPUT);
  
  pinMode(ML_1,OUTPUT);
  pinMode(ML_2,OUTPUT);
  pinMode(MR_1,OUTPUT);
  pinMode(MR_2,OUTPUT);
}
 
void loop() {

  d_l = distance(trig_l,echo_l);
  d_m = distance(trig_m,echo_m);
  d_r = distance(trig_r,echo_r);
  
  // String out = "";
  String out = (String) d_l + ' ' + d_m + ' ' + d_r;
  Serial.println(out);
  
  
  movement();
  delay(100);
  
}

void left(){
  digitalWrite(MR_1, HIGH);
  digitalWrite(MR_2, LOW);
  digitalWrite(ML_1, LOW);
  digitalWrite(ML_2, LOW);
  Serial.println();
  Serial.println("left");
}

void right(){
  digitalWrite(ML_1, HIGH);
  digitalWrite(ML_2, LOW);
  digitalWrite(MR_1, LOW);
  digitalWrite(MR_2, LOW);
  Serial.println();
  Serial.println("right");
}

void front(){
  digitalWrite(ML_1, HIGH);
  digitalWrite(ML_2, LOW);
  digitalWrite(MR_1, HIGH);
  digitalWrite(MR_2, LOW);
  Serial.println();
  Serial.println("front");
  
}

void back(){
  digitalWrite(ML_1, LOW);
  digitalWrite(ML_2, HIGH);
  digitalWrite(MR_1, LOW);
  digitalWrite(MR_2, HIGH);
  Serial.println();
  Serial.println("back");
}
void standstill(){
  digitalWrite(ML_1, LOW);
  digitalWrite(ML_2, LOW);
  digitalWrite(MR_1, LOW);
  digitalWrite(MR_2, LOW);
  Serial.println();
  Serial.println("standstill");
}

bool available(int dist) {
  return dist == 0 || dist > 50;
}

void movement(){
  if (available(d_m)) {
    front();
  } else if (available(d_l)) {
    left();
  } else if (available(d_r)) {
    right();
  } else {
    back();
  }
}

  // The sensors is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  //The below snippent drives programms the Sensors to turn on and measure the distance
// Read the signal from the sensor: a HIGH pulse whose
// duration is the time (in microseconds) from the sending
// of the ping to the reception of its echo off of an object.
float distance(int trig,int echo){
  digitalWrite(trig, LOW);
  delayMicroseconds(5);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  int period= pulseIn(echo, HIGH);
  int d = (period / 2) * 0.0343;
  return d;
}
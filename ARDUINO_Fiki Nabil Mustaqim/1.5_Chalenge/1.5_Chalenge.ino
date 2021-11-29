const int tombol1 = 2;
const int tombol2 = 3;
const int tombol3 = 4;
const int R = 5;
const int Y = 6;
const int G = 7;
int holdbutton;

void setup() {
  Serial.begin(9600);
  pinMode(tombol1,INPUT);
  pinMode(tombol2,INPUT);
  pinMode(tombol3,INPUT);
  pinMode(R,OUTPUT);
  pinMode(Y,OUTPUT);
  pinMode(G,OUTPUT);
  digitalWrite(R, LOW);
}

void loop() {
  int bacaTombol1=digitalRead(tombol1);
  Serial.println("Kondisi tombol:" +String(bacaTombol1) + "|" + String(holdbutton)); 
   if (bacaTombol1==1){
    if (holdbutton==0){
      holdbutton = 1;
      digitalWrite(R, HIGH);
    }
    else {
      holdbutton = 0;
      digitalWrite(R, LOW);
    }
    delay(1000);
  }
}

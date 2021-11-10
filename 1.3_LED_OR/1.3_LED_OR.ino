int tombol1 = 2;
int tombol2 = 3;
int tombol3 = 4;
int R = 5;
int Y = 6;
int G = 7;

void setup() {
  Serial.begin(9600);
  pinMode(tombol1,INPUT);
  pinMode(tombol2,INPUT);
  pinMode(tombol3,INPUT);
  pinMode(R,OUTPUT);
  pinMode(Y,OUTPUT);
  pinMode(G,OUTPUT);
}

void loop() {
  int bacaTombol1=digitalRead(tombol1);
  int bacaTombol2=digitalRead(tombol2);
  Serial.println("Kondisi tombol:" +String(bacaTombol1)); 
  Serial.println("Kondisi tombol:" +String(bacaTombol2)); 
   if (bacaTombol1 ==1 or bacaTombol2 ==1){
    digitalWrite(R, HIGH);
    }
 else{
  digitalWrite(R, LOW);
  }
}

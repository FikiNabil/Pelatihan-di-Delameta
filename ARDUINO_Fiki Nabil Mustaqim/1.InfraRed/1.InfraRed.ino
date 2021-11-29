int tombol1 = 4;
int IR = 3;
int R = 5;
int Y = 6;
int G = 7;

void setup() {
  Serial.begin(9600);
  pinMode(tombol1,INPUT);
  pinMode(IR,INPUT);
  pinMode(R,OUTPUT);
  pinMode(Y,OUTPUT);
  pinMode(G,OUTPUT);
}

void loop() {
  //BACA DATA
  int bacaTombol1=digitalRead(tombol1);
  int bacaIR=digitalRead(IR);

  //PRINT SERIAL
  Serial.print("Tombol: ");
  Serial.print(bacaTombol1);
  Serial.print(" | Sensor IR: ");
  Serial.print(bacaIR);
  Serial.println(); //Untuk Enter
  
}

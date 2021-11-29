//INISIALISASI
int tombol1 = 4;
int IR = 3;
int R = 5;
int Y = 6;
int G = 7;
int kunci = 0;

void setup() {
  Serial.begin(9600);
  pinMode(tombol1,INPUT);
  pinMode(IR,INPUT);
  pinMode(R,OUTPUT);
  pinMode(Y,OUTPUT);
  pinMode(G,OUTPUT);
  digitalWrite(R, HIGH);
  Serial.println("SYSTEM START");
}

void loop() {
  //DATA BACA
  int bacaTombol1=digitalRead(tombol1);
  int bacaIR=digitalRead(IR);

  //PRINT KE SERIAL
  Serial.print("Tombol: ");
  Serial.print(bacaTombol1);
  Serial.print(" | Sensor: ");
  Serial.print(bacaIR);
  Serial.print(" | Flag: ");
  Serial.print(kunci);
  Serial.println(); //UNTUK ENTER

  //LOGIKA PROGRAM
  if(bacaTombol1==1 and kunci==0){
    delay(500);
    kunci=1;
    Serial.println("SELAMAT DATANG SILAHKAN AMBIL TIKET");
    Serial.println("PALANG DIBUKA");
    digitalWrite(R, LOW);
    digitalWrite(Y, HIGH);
    delay(1000);
    digitalWrite(Y, LOW);
    delay(100);
    digitalWrite(G, HIGH);
    }
    if(bacaIR==0 and kunci==1){
    delay(500);
    kunci=0;
    Serial.println("PALANG DITUTUP");
    digitalWrite(G, LOW);
    digitalWrite(R, HIGH);
  }
}

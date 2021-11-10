//INISIALISASI
int Button1=PB7;
int Button2=PB6;
int Button3=PB5;

int Red=PA11;
int Yellow=PA0;
int Green=PA1;

void setup() {
  Serial.begin(9600);
  pinMode(Button1, INPUT);
  pinMode(Button2, INPUT);
  pinMode(Button3,  INPUT);
  pinMode(Red, OUTPUT);
  pinMode(Yellow, OUTPUT);
  pinMode(Green, OUTPUT);
}

void loop() {
  //BACA DATA
  int bacaButton1=digitalRead(Button1);
  int bacaButton2=digitalRead(Button2);
  int bacaButton3=digitalRead(Button3);

  //PRINT TO SERIAL
  Serial.print("Kondisi Button1: "); Serial.print(bacaButton1);
  Serial.print("| Kondisi Button2: "); Serial.print(bacaButton2);
  Serial.print("| Kondisi Button3: "); Serial.print(bacaButton3);
  Serial.println(); //Untuk ENTER

  //LOGIKA PROGRAM
  if(bacaButton1 == 1){ //Kondisi Jika Button1 Ditekan
    digitalWrite(Red, HIGH); //LED Merah Menyala
    }
    else{ //Kondisi jika Button1 tidak ditekan
      digitalWrite(Red, LOW); //LED Merah tidak menyala
    }
  if(bacaButton2 == 1){ //Kondisi Jika Button2 Ditekan
    digitalWrite(Yellow, HIGH); //LED Kuning Menyala
    }
    else{ //Kondisi jika Button2 tidak ditekan
      digitalWrite(Yellow, LOW); //LED Kuning tidak menyala
    }
  if(bacaButton3 == 1){ //Kondisi Jika Button3 Ditekan
    digitalWrite(Green, HIGH); //LED Hijau Menyala
    }
    else{ //Kondisi jika Button3 tidak ditekan
      digitalWrite(Green, LOW); //LED Hijau tidak menyala
    }
}

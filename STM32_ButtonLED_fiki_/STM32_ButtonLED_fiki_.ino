//INISIALISASI
int fiki_button1=PB5;
int fiki_button2=PB6;
int fiki_button3=PB7;

int fiki_merah=PA1;
int fiki_kuning=PA2;
int fiki_hijau=PA3;

void setup(){
  Serial.begin(9600);
  pinMode(fiki_button1, INPUT);
  pinMode(fiki_button2, INPUT);
  pinMode(fiki_button3, INPUT);
  pinMode(fiki_merah, OUTPUT);
  pinMode(fiki_kuning, OUTPUT);
  pinMode(fiki_hijau, OUTPUT);
}
void loop(){
  //BACA DATA
  int bacaButtonFiki1=digitalRead(fiki_button1);
  int bacaButtonFiki2=digitalRead(fiki_button2);
  int bacaButtonFiki3=digitalRead(fiki_button3);

  //SERIAL TO PRINT
  Serial.print("Tombol1: "); Serial.print(bacaButtonFiki1);
  Serial.print("| Tombol2: "); Serial.print(bacaButtonFiki2);
  Serial.print("| Tombol3: "); Serial.print(bacaButtonFiki3);
  Serial.println(); //Untuk Enter

  //LOGIKA PROGRAM
  if(bacaButtonFiki1 == 1){ //Kondisi jika Tombol1 ditekan
    digitalWrite(fiki_merah, HIGH); //LED Merah menyala
  }
  else { //Kondisi jika Tombol1 tidak ditekan
    digitalWrite(fiki_merah, LOW); //LED Merah tidak menyala
  }
  
   if(bacaButtonFiki2 == 1){//Kondisi jika Tombol2 ditekan
    digitalWrite(fiki_kuning, HIGH); ////LED Kuning menyala
  }
  else { //Kondisi jika tombol2 tidak ditekan
    digitalWrite(fiki_kuning, LOW);//LED Kuning tidak menyala
  }
  
   if(bacaButtonFiki3 == 1){ //Kondisi jika Tombol3 ditekan
    digitalWrite(fiki_hijau, HIGH); //LED Hijau Menyala
  }
  else { //Kondisi jika tombol3  tidak ditekan
    digitalWrite(fiki_hijau, LOW); //LED Hijau tidak menyala
  }
}

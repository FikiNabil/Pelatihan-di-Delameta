//INISIALISASI
int fiki_button1=PB5;
int fiki_button2=PB6;
int fiki_button3=PB7;

int fiki_merah=PA1;
int fiki_kuning=PA2;
int fiki_hijau=PA3;

int flag=0;

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
   //LED MERAH
  if(bacaButtonFiki1 == 1 and flag== 0){ 
    flag=1;
    digitalWrite(fiki_merah, HIGH); 
    delay(500);
  }
  else if(bacaButtonFiki1 == 1 and flag==1) { 
    flag=0;
    digitalWrite(fiki_merah, LOW); 
    delay(500);
  }
  
  //LED KUNING
  if(bacaButtonFiki2 == 1 and flag==0){
    flag=1;
    digitalWrite(fiki_kuning, HIGH); 
    delay(500);
  }
  else if(bacaButtonFiki2 == 1 and flag==1)  {
    flag=0;
    digitalWrite(fiki_kuning, LOW);
    delay(500);
  }
  
  //LED HIJAU
   if(bacaButtonFiki3 == 1 and flag==0){ 
    flag=1;
    digitalWrite(fiki_hijau, HIGH); 
    delay(500);
  }
  else if(bacaButtonFiki3 == 1 and flag==1) { 
    flag=0;
    digitalWrite(fiki_hijau, LOW); 
    delay(500);
  }
}

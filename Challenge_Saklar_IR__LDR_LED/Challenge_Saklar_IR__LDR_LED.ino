int LDR = PA1;
int IR = PA0;
int LEDRed = PA2;
int LEDYellow = PA3;
int LEDGreen = PA4;
int flag = 0;

void setup () {
  Serial.begin(9600);
  pinMode(LDR, INPUT);
  pinMode(IR, INPUT);
  pinMode(LEDRed, OUTPUT);
  pinMode(LEDYellow, OUTPUT);
  pinMode(LEDGreen, OUTPUT);
}

void loop (){
  //BACA DATA
  int bacaLDR=analogRead(LDR);
  bacaLDR=map(bacaLDR, 0, 4095, 100 ,0);
  int bacaIR=digitalRead(IR);

  //PRINT TO SERIAL
  Serial.print("Sensor LDR :"); Serial.print(bacaLDR);
  Serial.print("| Sensor IR :"); Serial.print(bacaIR);
  Serial.print("| Flag :"); Serial.print(flag);
  Serial.println();

  //LOGIKA PROGRAM
  if (bacaIR == 0 and flag == 0){
    flag=1;
    delay(100);
  }
  else if (bacaIR == 0 and flag == 1){
    flag=0;
    delay(100);
  }
  if (flag == 0){
      if(bacaLDR == 0){
        digitalWrite(LEDRed, HIGH);
        digitalWrite(LEDYellow, LOW);
        digitalWrite(LEDGreen, LOW);
      }
      else if(bacaLDR >=10 and bacaLDR <= 50){
        digitalWrite(LEDRed, LOW);
        digitalWrite(LEDYellow, HIGH);
        digitalWrite(LEDGreen, LOW);
      }
      else if(bacaLDR >= 50){
        digitalWrite(LEDRed, LOW);
        digitalWrite(LEDYellow, LOW);
        digitalWrite(LEDGreen, HIGH);
      }
  }
  else if ( flag == 1){
      digitalWrite(LEDRed, LOW);
      digitalWrite(LEDYellow, LOW);
      digitalWrite(LEDGreen, LOW);
   }
}

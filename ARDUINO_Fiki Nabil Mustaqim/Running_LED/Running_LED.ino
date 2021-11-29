void setup(){
  for(int i=2;i<=4;i++)
  pinMode(i,OUTPUT);
 }

 void loop(){
    for (i=4;i<=9;i++) {
        digitalWrite(i,HIGH);
        delay(100);
        digitalWrite(i,LOW);
    }
    for (i=9;i>=4;i--) {
        digitalWrite(i,HIGH);
        delay(100);
        digitalWrite(i,LOW);
    }
}

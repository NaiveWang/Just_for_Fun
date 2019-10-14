//TM1650 - 4 digits
#define CL 5
#define DA 6
byte digits_d[11]={0x3f, 0x03, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0xff, 0x6f, 0x00};
byte digits_a[4]={0x68, 0x6a, 0x6c, 0x6e};
int i=0;
void start(){
  //initialize tm1650
  digitalWrite(DA, HIGH);
  digitalWrite(CL, HIGH);
  digitalWrite(DA, LOW);
}
void stop(){
  //initialize tm1650
  digitalWrite(DA, LOW);
  digitalWrite(CL, LOW);
  digitalWrite(DA, LOW);
}
void ack(){
  pinMode(DA, INPUT);
  while(digitalRead(DA)==HIGH);
  pinMode(DA, OUTPUT);
}
void write_byte(byte b){
  static byte i;
  for(i=0; i<8; i++){
    if(b&0x01){
      //write HIGH
      digitalWrite(DA, HIGH);
      digitalWrite(CL, HIGH);
      digitalWrite(CL, LOW);
    }else{
      //write LOW
      digitalWrite(DA, LOW);
      digitalWrite(CL, HIGH);
      digitalWrite(CL, LOW);
    }
    b>>=1;
  }
}
void setup() {
  // put your setup code here, to run once:
  pinMode(CL, OUTPUT);
  pinMode(DA, OUTPUT);
  start();
  write_byte(0x48);
  ack();
  write_byte(0x09);
  ack();
  stop();
}
void write_digit(byte a, byte d){
  start();
  write_byte(digits_a[a]);
  ack();
  write_byte(digits_d[d]);
  ack();
  stop();
}
void loop() {
  // put your main code here, to run repeatedly:
  i=(i+1)%10000;
  if(i>1000){
    //show 4th
    write_digit(3, i/1000);
  }else{
    write_digit(3, 10);
  }
  if(i>100){
    //show 3rd
    write_digit(2, (i/100)%10);
  }else{
    write_digit(2, 10);
  }
  if(i>10){
    //show 2nd
    write_digit(1, (i/10)%10);
  }else{
    write_digit(1, 10);
  }
  write_digit(0, i%10);

  delay(50);
}

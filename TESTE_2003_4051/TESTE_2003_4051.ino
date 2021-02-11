struct Multiplex_Signal
{
    uint8_t A, B, C, COM, SCK, EN[5];
    int Val;
};

Multiplex_Signal CD;

void setup() {
  InitCD(A3,A4,A5,7, 8);
  Serial.begin(9600);// initialize serial monitor with 9600 baud
  Serial.println("TESTE NIVEL AGUA"); 

}

void loop() {
  for (int i = 0; i < 8; i++)
  {
      Serial.print(i); 
      Serial.print(" = ");
      Serial.print((GET_LEVEL(i)?"OFF  ":"ON   "));
  }
  Serial.println();
  delay(1000);
  for (int i = 0; i < 10; i++)
  {
      Serial.println(' ');
  }
  
}
bool GET_LEVEL(int val){
  digitalWrite(CD.A, bitRead(val, 0));
  digitalWrite(CD.B, bitRead(val, 1));
  digitalWrite(CD.C, bitRead(val, 2));
  digitalWrite(CD.EN[0], LOW);
  pinMode(CD.COM, INPUT_PULLUP);
  bool ret = digitalRead(CD.COM);
  digitalWrite(CD.EN[0], HIGH);
  return ret;
}
void InitCD(uint8_t a,uint8_t b, uint8_t c, uint8_t en, uint8_t com){
  CD.A = a;
  CD.B = b;
  CD.C = c;
  CD.EN[0] = en;
  CD.COM = com;
  pinMode(CD.A, OUTPUT);
  pinMode(CD.B, OUTPUT);
  pinMode(CD.C, OUTPUT);
  pinMode(CD.EN[0], OUTPUT);
  pinMode(CD.COM, INPUT_PULLUP);
  digitalWrite(CD.A, LOW);
  digitalWrite(CD.B, LOW);
  digitalWrite(CD.C, LOW);
  digitalWrite(CD.EN[0], HIGH);
}
void SetCd(int val){
  CD.Val = val;
  digitalWrite(CD.A, bitRead(val, 0));
  digitalWrite(CD.B, bitRead(val, 1));
  digitalWrite(CD.C, bitRead(val, 2));
}
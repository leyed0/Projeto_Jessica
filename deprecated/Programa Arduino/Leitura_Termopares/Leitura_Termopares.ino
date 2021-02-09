
#include <Wire.h>
#include <max6675.h>   

#define botao_1 2 
#define botao_2 3


//Ajustar para realizar 4 leituras em 1 segundo e imprimir a média
//Aplicar programa (Java) para visualizar em tempo real o gráfico dos termopares

float valor_termopar[5]    = {0,0,0,0,0};
float correcao_termopar[5] = {0,0,0,0,0}; //ajusta o offset de cada termopar
int minuto = 0, seg=0;
long tempoAtual = 0, tempoInicial =0;

//----------------------------------------------------------
const int   thermoDO_0  = 5;
const int   thermoCS_0  = 6;
const int   thermoCLK_0 = 7;
MAX6675 thermocouple_0(thermoCLK_0, thermoCS_0, thermoDO_0);

const int   thermoDO_1  = 8;
const int   thermoCS_1  = 9;
const int   thermoCLK_1 = 10;
MAX6675 thermocouple_1(thermoCLK_1, thermoCS_1, thermoDO_1);

const int   thermoDO_2 = 11;
const int   thermoCS_2 = 12;
const int   thermoCLK_2 = 13;
MAX6675 thermocouple_2(thermoCLK_2, thermoCS_2, thermoDO_2);

const int   thermoDO_3 = 2;
const int   thermoCS_3 = 3;
const int   thermoCLK_3 = 4;
MAX6675 thermocouple_3(thermoCLK_3, thermoCS_3, thermoDO_3);

const int   thermoDO_4 = 19;
const int   thermoCS_4 = 18;
const int   thermoCLK_4 = 17;
MAX6675 thermocouple_4(thermoCLK_4, thermoCS_4, thermoDO_4);

//-----------------------------------------------------------

int ler_botao();
void imprime_tempo();
void temperaturas();

//-----------------------------------------------------------

void setup()
{
   Serial.begin(9600);
}

//----------------------------------------------------------
 
void loop()
{
  tempoInicial = tempoAtual;

  do{
    tempoAtual = millis();
    delay(1);
  }while(tempoAtual < (tempoInicial + 1000)); //define a leitura do sensor a cada 1000 ms

  temperaturas();
  imprime_tempo();
  
  for (int i=0; i < 5; i++){
    //Serial.print("\t");
    Serial.print(valor_termopar[i], 2); 
    Serial.print(" ; ");
  }
  
  Serial.println(" ");
    
}


//----------------------------------------------------------

void temperaturas(){
    valor_termopar[0] = thermocouple_0.readCelsius() + correcao_termopar[0];
    delay(5); 
    valor_termopar[1] = thermocouple_1.readCelsius() + correcao_termopar[1];
    delay(5);
    valor_termopar[2] = thermocouple_2.readCelsius() + correcao_termopar[2];
    delay(5);
    valor_termopar[3] = thermocouple_3.readCelsius() + correcao_termopar[3];
    delay(5);
    valor_termopar[4] = thermocouple_4.readCelsius() + correcao_termopar[4];
    delay(5);
}

//----------------------------------------------------------

void imprime_tempo(){
  
 seg++;
 
  if(seg>59){
    minuto++;
    seg=0;
    }
    
  if(minuto<10){
    Serial.print("0");
    Serial.print(minuto);
    }
    else{
      Serial.print(minuto);
    }

  if(seg>9){   
  Serial.print(":");
  Serial.print(seg);
  } else{
      Serial.print(":0");
      Serial.print(seg);
    }

  Serial.print(" ; ");
  
}

//----------------------------------------------------------

int ler_botao(){
  
    if(digitalRead(botao_1)){
      while(digitalRead(botao_1));
      return(1);
    }else
          if(digitalRead(botao_2)){
            while(digitalRead(botao_2));
            return(2);
          } 
 return(0);
}

//----------------------------------------------------------









  

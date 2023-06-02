#include <LiquidCrystal.h>   
#include <Keypad.h>
#include <Servo.h>

Servo servo;
const int SERVO_PIN = A0;  // Pino de sinal do servo motor
int a=0, b=0, c=0, d=0; //variaveis para serem usadas de armazenamento
int var=0; 
int C1=0,C2=0,C3=0,C4=0; //definição da senha
const byte rows = 4; 
const byte columns = 4; 
char key[rows][columns] = 
{
  {'1','2','3','A'},
  {'4','5','6','B'}, //definição dos parametros do keypad
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte pinRows[rows] = {7, 6, 5, 4}; 
byte pinColumns[columns] = {3, 2, 1, 0}; 

Keypad keypad = Keypad( makeKeymap(key), pinRows, pinColumns, rows, columns );
LiquidCrystal lcd(8,9,10,11,12,13); 


void controlarPorta() {
  servo.attach(SERVO_PIN);  // Inicializa o servo motor no pino especificado
  servo.write(0);  // Define a posição inicial do servo (fechado)
  delay(1000);  // Aguarde 1 segundo antes de iniciar a abertura da porta

  abrirPorta();
  delay(10000);  // Aguarde 10 segundos com a porta aberta
  fecharPorta();
  delay(1000);  // Aguarde 1 segundo antes de finalizar a função

  servo.detach();  // Desconecta o servo motor após o uso
}

void abrirPorta() {
  servo.write(90);  // Gira o servo para abrir a porta (posição intermediária)
}

void fecharPorta() {
  servo.write(0);  // Gira o servo para fechar a porta (posição inicial)
}


void setup(){
  lcd.begin(16,2); 
  pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
}
  
void loop(){
  char key = keypad.getKey();
  if (key){
   lcd.setCursor(6+var,1);
   lcd.print(key),lcd.setCursor(6+var,1);
   key=key-48;
   var++; 
   switch(var){
    case 1:
    a=key; 
    break;
    case 2:
    b=key;  
    break;
    case 3:
    c=key;
    break;
    case 4:
    d=key;
   delay(100);
  if(a==C1 && b==C2 && c==C3 && d==C4)
  {
    lcd.clear();
    lcd.setCursor(4,0);
    lcd.print("Senha");
    lcd.setCursor(5,1);
    lcd.print("Valida");
    digitalWrite(A0,HIGH);
    delay(1000); 
    lcd.clear();
    digitalWrite(A0,LOW);
    controlarPorta();
    
    }
  else{
    lcd.clear();
    lcd.setCursor(4,0);
    lcd.print("Senha");
    lcd.setCursor(4,1);
    lcd.print("Invalida");
    digitalWrite(A1,HIGH); 
    delay(1000);
    lcd.clear();
    digitalWrite(A1,LOW); 
    }
   var=0;
   lcd.clear();

  break;
  }
 }
 if(!key){lcd.setCursor(0,0),lcd.print("Insira Senha");}

  delay(2);
}
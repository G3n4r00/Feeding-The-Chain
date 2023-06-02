#include <EEPROM.h>

#include <Wire.h>

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(32,16,2);

// Definição das constantes
const int LDR_PIN = A0;
const int TMP_PIN = A1;
const int LED_VERDE = 9;
const int LED_VERMELHO = 8;
const float MAX_SENSOR = 100.0;
const int TILT_PIN = A2;

// Declaração das variáveis
float sensorValue = 0.0;
float sensorLido = 0.0;
float luminosidade = 0.0;
float sensorVVibra = 0.0;
float sensorVibra = 0.0;

// Declaração das variáveis de temperatura
float sensor = 0;
float celsius = 0;
float voltage = 0;

// Declaração das médias das variáveis
float mediaLuz = 0;
float mediaTemp = 0;
float mediaUmid = 0;
float mediaVibra = 0;

// Declaração da variável de saída do sensor de umidade
int humiditysensorOutput = 0;


// Endereços de memória EEPROM
const int ADDR_LUZ = 0;
const int ADDR_TEMP = ADDR_LUZ + sizeof(float);
const int ADDR_UMID = ADDR_TEMP + sizeof(float);
const int ADDR_VIBRA = ADDR_UMID + sizeof(float);


void setup() {
  Serial.begin(9600);

  // Configuração dos pinos de saída dos LEDs
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);

  // Configuração do display LCD
  lcd.begin(16, 2);
  lcd.init();
  lcd.backlight();

  // Inicialização do sistema
  lcd.print("Inicializando...");

  // Aguarda 5 segundos para leitura da luminosidade
  delay(5000);
}

void loop() {
  
  // Leitura dos dados armazenados na EEPROM e exibição no monitor serial
  float luzEeprom, tempEeprom, umidEeprom, vibraEeprom;
  EEPROM.get(ADDR_LUZ, luzEeprom);
  EEPROM.get(ADDR_TEMP, tempEeprom);
  EEPROM.get(ADDR_UMID, umidEeprom);
  EEPROM.get(ADDR_VIBRA, vibraEeprom);

  Serial.println("Dados armazenados na EEPROM:");
  Serial.print("Luminosidade: ");
  Serial.println(luzEeprom);
  Serial.print("Temperatura: ");
  Serial.println(tempEeprom);
  Serial.print("Umidade: ");
  Serial.println(umidEeprom);
  Serial.print("Vibracao: ");
  Serial.println(vibraEeprom);


  // Leitura da luminosidade
  mediaLuz = 0;
  for (int i = 0; i < 5; i++) {
    sensorValue = analogRead(LDR_PIN);
    sensorLido = (sensorValue / 1023.0) * MAX_SENSOR;
    mediaLuz += sensorLido;
    delay(500);
  }
  mediaLuz /= 5.0;
  
  // Armazena a média de luminosidade na EEPROM
  EEPROM.put(ADDR_LUZ, mediaLuz);
  
  // Exibe média de luminosidade por 5 segundos
  lcd.clear();
  Serial.println("Media Luz");
  Serial.println(mediaLuz);
  if (mediaLuz < 50) {
    digitalWrite(LED_VERDE, HIGH);
    digitalWrite(LED_VERMELHO, LOW);
    lcd.print("LUZ:");
    lcd.setCursor(0, 1);
    lcd.print("ADEQUADA");
    noTone(10); }
  else {
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_VERMELHO, HIGH);
    lcd.print("LUZ:");
    lcd.setCursor(0, 1);
    lcd.print("INADEQUADA");
    tone(10,800); } //Toca o buzzer
  delay(5000);

  // Leitura da temperatura
  mediaTemp = 0;
  for (int i = 0; i < 5; i++) {
    sensor = analogRead(TMP_PIN);
    voltage = (sensor / 1023.0) * 5.0;
    celsius = (voltage - 0.5) * 100.0;
    mediaTemp += celsius;
    delay(500);
  }
  mediaTemp /= 5.0;
  
  // Armazena a média de temperatura na EEPROM
  EEPROM.put(ADDR_TEMP, mediaTemp);

  // Exibe média de temperatura por 5 segundos
  lcd.clear();
  Serial.println("Media Temperatura");
  Serial.println(mediaTemp);
  if (mediaTemp < 16) {
    digitalWrite(LED_VERDE, HIGH);
    digitalWrite(LED_VERMELHO, LOW);
    lcd.print("Temp. adequada");
    lcd.setCursor(0, 1);
    lcd.print("Temp. = ");  
    lcd.print(round(mediaTemp));
    lcd.print("C");
  }
  else {
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_VERMELHO, HIGH);
    lcd.print("Temp. inadequada");
    lcd.setCursor(0, 1);
    lcd.print("Temp. = ");
    lcd.print(round(mediaTemp));
    lcd.print("C");
    tone(10,800); } //Toca o buzzer
  delay(5000);

  // Leitura da umidade
  mediaUmid = 0;
  for (int i = 0; i < 5; i++) {
    humiditysensorOutput = analogRead(A2);
    mediaUmid += map(humiditysensorOutput, 0, 1023, 0, 100);
    delay(500);
  }
  mediaUmid /= 5.0;
  
  // Armazena a média de umidade na EEPROM
  EEPROM.put(ADDR_UMID, mediaUmid);

  // Exibe umidade atual e reinicia o loop
  lcd.clear();
  Serial.println("Media Umidade");
  Serial.println(mediaUmid);
  if (mediaUmid < 20) {
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_VERMELHO, HIGH);
    lcd.print("Umid. adequada");
    lcd.setCursor(0, 1);
    lcd.print("Umid. = ");  
    lcd.print(mediaUmid);
    lcd.print("%");
  }
  else {
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_VERMELHO, HIGH);
    lcd.print("Umid. inaquada");
    lcd.setCursor(0, 1);
    lcd.print("Umid. = ");
    lcd.print(mediaUmid);
    lcd.print("%");
    tone(10,800); } //Toca o buzzer
  delay(5000);

   //Leitura da vibração
  mediaVibra = 0;
  for (int i = 0; i < 5; i++) {
    sensorVVibra = analogRead(TILT_PIN);
    sensorVibra = (sensorVVibra / 1023.0) * MAX_SENSOR;
    mediaVibra += sensorVibra;
    delay(500);
  }
  
  mediaVibra /= 5.0;
  
  // Armazena a média de vibração na EEPROM
  EEPROM.put(ADDR_VIBRA, mediaVibra);
  
 //Exibe média de vibração por 5 segundos
  lcd.clear();
  Serial.println("Media Vibracao");
  Serial.println(mediaVibra);
  if (mediaVibra < 50) {
    digitalWrite(LED_VERDE, HIGH);
    digitalWrite(LED_VERMELHO, LOW);
    lcd.print("VIBRACAO:");
    lcd.setCursor(0, 1);
    lcd.print("ADEQUADA");
    noTone(10); }
  else {
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_VERMELHO, HIGH);
    lcd.print("VIBRACAO:");
    lcd.setCursor(0, 1);
    lcd.print("INADEQUADA");
    tone(10,800); } //Toca o buzzer
  delay(5000);
}
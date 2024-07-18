//linkagem de livrarias
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x20, 16, 2);

// Declaro onde conectei os pinos 
const int pirPin = 2;
const int buzzerPin = 8;
const int photoresistorPin = A0;
int b1 = 3; 
int b2 = 4;

//Configurações para iniciar os pinos e LCD
void setup() {
  pinMode(pirPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(b1, INPUT);
  pinMode(b2, INPUT); 
  pinMode(photoresistorPin, INPUT);
  
  Serial.begin(9600);
 
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Alarme");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("Inicializado");
  delay(1150);
  Serial.println("LCD inicializado.");
  delay(500);
  lcd.clear();
  Serial.println("Inicialização concluída.");
}

//Configurando Alarme
void soundAlarm() {
  tone(buzzerPin, 768); 
  delay(1000); // Manter o som por 1 segundo
  noTone(buzzerPin); // Parar o som
}

void loop() {
  //Leitor de valor
  int lightValue = analogRead(photoresistorPin);
  int pirValue = digitalRead(pirPin);
  int b1Value = digitalRead(b1); 
  int b2Value = digitalRead(b2); 
 
  //condições
  if (lightValue < 500 && pirValue == HIGH) {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Detectado");
    delay(600);
    lcd.clear();
    Serial.println("Movimento detectado!");
    soundAlarm();
    
  } else if (b1Value == 1) {
    lcd.setCursor(0, 0);
    lcd.clear();
    lcd.print("Janela");
    Serial.println("Movimento na Janela!");
    soundAlarm();
    
    
  } else if (b2Value == 1) {
    lcd.setCursor(0, 0);
    lcd.clear();
    lcd.print("Porta");
    Serial.println("Movimento na Porta!");
    soundAlarm();
   
  } else if (lightValue >= 500) {
    noTone(buzzerPin);
    lcd.setCursor(0, 1);
    lcd.clear();
    Serial.println("Esta dia");
    lcd.print("Dia");
    noTone(buzzerPin);
    delay(500);
       
  } else {
    lcd.clear();
    delay(1000);
    noTone(buzzerPin);
  }
  
  
}

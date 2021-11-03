#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
#define trigPin 7
#define echoPin 6 
#include <SoftwareSerial.h>    //memasukan library Software Serial
#include <DFPlayer_Mini_Mp3.h> //memasukan library DFPlayermini
SoftwareSerial serial(10, 11); //pin RX dan TX

int BUZZER = 13;
const byte SIMBOLDERAJAT = B11011111;

void setup(){
  lcd.init();                  
  lcd.backlight();
  lcd.clear();
  mlx.begin();
  serial.begin(9600);
  pinMode(BUZZER, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
 mp3_set_serial (serial); //DF PLAYER
 delay(5); 
 mp3_set_volume (30);
}
 
void loop(){
  //Tampilkan di serial monitor untuk suhu
  long duration, distance;
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  Serial.print(distance);
  Serial.println(" cm");
  delay(500);
   
  //Apabila Jarak dibawah 6 cm dan suhu >= 37 celcius
  if (distance <= 6){
  if(mlx.readObjectTempC()*1.090 >= 37.50){
    //apabila ingin menambahkan Alarm
    digitalWrite(BUZZER, HIGH);
    //mp3_play (1); //memainkan lagu 1 pada folder mp3 yang sudah direname dengan nama 0001.mp3
    //delay (100);
    //delay(100);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("-- ANDA DEMAM --");
    lcd.setCursor(0, 1);
    lcd.print("Suhu: ");
    lcd.setCursor(7, 1);
    lcd.print(mlx.readObjectTempC()*1.090); //*1.125 (UNTUK PENGALI KALIBRASI)
    lcd.setCursor(12, 1);
    lcd.write(SIMBOLDERAJAT);
    lcd.setCursor(13, 1);
    lcd.print("C");
    delay(400);
    
  }else if (mlx.readObjectTempC()*1.090 <= 37.50) {
    digitalWrite(BUZZER, LOW);
    mp3_play (2); //memainkan lagu 2 pada folder mp3 yang sudah direname dengan nama 0002.mp3
    //delay (100);
    //delay(100);
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("-- ANDA SEHAT --");
    lcd.setCursor(0, 1);
    lcd.print("Suhu: ");
    lcd.setCursor(7, 1);
    lcd.print(mlx.readObjectTempC()*1.090);  //*1.128 (UNTUK PENGALI KALIBRASI) Nilai ini bisa dikosongkan
    lcd.setCursor(12, 1);
    lcd.write(SIMBOLDERAJAT);
    lcd.setCursor(13, 1);
    lcd.print("C");

    delay(700);
    
    }}

  //Apabila Jarak dibawah 7 cm dan suhu <37 celcius
 /* if (distance < 7){
  if(mlx.readObjectTempC()*1.090 < 37){
    digitalWrite(BUZZER, LOW);
    mp3_play (2); //memainkan lagu 2 pada folder mp3 yang sudah direname dengan nama 0002.mp3
    delay (100);
    //delay(100);
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("-- ANDA SEHAT --");
    lcd.setCursor(0, 1);
    lcd.print("Suhu: ");
    lcd.setCursor(7, 1);
    lcd.print(mlx.readObjectTempC()*1.090);  //*1.128 (UNTUK PENGALI KALIBRASI) Nilai ini bisa dikosongkan
    lcd.setCursor(12, 1);
    lcd.write(SIMBOLDERAJAT);
    lcd.setCursor(13, 1);
    lcd.print("C");

    delay(700);
  }}
*/
  
   if (distance > 7) {
    delay(100);
    lcd.clear();
    digitalWrite(BUZZER, LOW);
    lcd.setCursor(0, 0);
    lcd.print("KKN-T UMSIDA 08");
    lcd.setCursor(0, 1);
    lcd.print("  DESA GANTING");
    delay(300);
    } 
}

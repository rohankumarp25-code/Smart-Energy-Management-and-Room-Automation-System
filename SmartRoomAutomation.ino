A.1 Main Header Files and Pin Definitions
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#define DHΤΡΙΝ 3
#define DHTTYPE DHT11
#define IR_SENSOR 2
#define RELAY_PIN 4
#define GREEN_LED 5
#define YELLOW_LED 6
#define RED_LED 7
#define LDR PIN A0
#define SMOKE_PIN A1
#define BUZZER_PIN 8
const int LIGHT_THRESHOLD = 400;
const int SMOKE_THRESHOLD = 350;
LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht (DHΤΡΙΝ, DHTTYPE);
bool roomOccupied = false;
bool previousState = HIGH;
void setup()
{
pinMode (IR_SENSOR, INPUT);
pinMode (RELAY_PIN, OUTPUT);
pinMode(GREEN_LED, OUTPUT);
pinMode(YELLOW_LED, OUTPUT);
pinMode(RED_LED, OUTPUT);
pinMode(LDR_PIN, INPUT);
pinMode(SMOKE_PIN, INPUT);
pinMode(BUZZER_PIN, OUTPUT);
lcd.init();
lcd.backlight();
dht.begin();
}
A.3 Smoke Detection and Emergency Alert
int smokeValue = analogRead(SMOKE_PIN);
if (smokeValue > SMOKE_THRESHOLD)
{
digitalWrite(RELAY_PIN, LOW);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("!! FIRE ALERT !!");
while (analogRead(SMOKE_PIN) > SMOKE_THRESHOLD)
{
digitalWrite(RED_LED, HIGH);
digitalWrite(BUZZER_PIN, HIGH);
delay(200);
digitalWrite(RED_LED, LOW);
digitalWrite(BUZZER_PIN, LOW);
delay(200);
}
}
A.4 Occupancy Detection using IR Sensor
int sensorState = digitalRead(IR_SENSOR);
if(sensorState == LOW && previousState == HIGH)
{
roomOccupied = !roomOccupied;
if(roomOccupied)
{
lcd.print("WELCOME TO HOME");
}
else
{
lcd.print("THANK YOU");
}}
A.5 Smart Lighting using LDR
int lightIntensity = analogRead(LDR_PIN);
if(lightIntensity < LIGHT_THRESHOLD)
{
digitalWrite(RELAY_PIN, HIGH);
digitalWrite(GREEN_LED, HIGH);
}
else
{
digitalWrite(RELAY_PIN, LOW);
digitalWrite(GREEN_LED, LOW);
}
A.6 Temperature Monitoring using DHT11
float temperature = dht.readTemperature();
lcd.setCursor(0,0);
lcd.print("Temp: ");
lcd.print(temperature);
lcd.print((char) 223);
lcd.print("C");
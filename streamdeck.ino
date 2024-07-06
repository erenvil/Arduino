#include <LiquidCrystal.h>
#include <DHT.h>
#include <IRremote.h>

int rs = 13;
int e = 12;
int d4 = 11;
int d5 = 10;
int d6 = 9;


int d7 = 8;
LiquidCrystal lcd(rs, e, d4, d5, d6, d7);

#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

int IR = 7;
IRrecv irrecv(IR);
decode_results cmd;

int xPin = A0;
int yPin = A1;

int stage = 0;
bool forceUpdate = false;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  dht.begin();
  irrecv.enableIRIn();
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
}

void loop() {
  irr();
  
  if (stage == 0) {
    displayTemperatureAndHumidity();
  } else if (stage == 1) {
    lcd.clear();
    float xVal = analogRead(xPin);
    float yVal = analogRead(yPin);
    
    Serial.print("xVal: ");
    Serial.println(xVal);
    Serial.print("yVal: ");
    Serial.println(yVal);
    if (xVal < 400) {
      Serial.println("W");
    }
    if (xVal > 800) {
      Serial.println("S");
    }
    if (yVal > 800) {
      Serial.println("A");
    }
    if (yVal < 400) {
      Serial.println("D");
    }
    delay(100);
  } else if (stage == 2) {
    lcd.clear();
    float xVal = analogRead(xPin);
    float yVal = analogRead(yPin);
    
    Serial.print("xVal: ");
    Serial.println(xVal);
    Serial.print("yVal: ");
    Serial.println(yVal);
    
    if (xVal < 400) {
      Serial.println("obs1");
    }
    if (xVal > 800) {
      Serial.println("obs2");
    }
    if (yVal > 800) {
      Serial.println("obs3");
    }
    if (yVal < 400) {
      Serial.println("obs4");
    }
  }
}

void irr() {
  if (irrecv.decode(&cmd)) {
    Serial.println(cmd.value, HEX);
    if (cmd.value == 0xFFA25D) {
      stage = (stage + 1) % 3;
      if (stage == 0) {
        forceUpdate = true;
      }
    }
    if (cmd.value == 0xFF629D) {
      Serial.println("+");
    }
    if (cmd.value == 0xFFA857) {
      Serial.println("-");
    }
    if (cmd.value == 0xFF02FD) {
      Serial.println("play/pause");
    }
    if (cmd.value == 0xFF22DD) {
      Serial.println("back");
    }
    if (cmd.value == 0xFFC23D) {
      Serial.println("next");
    }
    if (cmd.value == 0xFF6897){
      Serial.println("obs");
    }
    
    irrecv.resume();
  }
}

void displayTemperatureAndHumidity() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  delay(500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print(" C");

  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(humidity);
  lcd.print(" %");

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
}

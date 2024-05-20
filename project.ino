#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_MLX90614.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define echoPin 10
#define trigPin 9
#define LED1 3
#define LED2 4
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

long duration;
int distance;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  digitalWrite(LED1, HIGH);
  Serial.begin(9600);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C )) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  delay(2000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("2/2-PROJECT BY:");
  display.setCursor(0, 12);
  display.println("*RAHAT-565");
  display.setCursor(0, 24);
  display.println("*UPOMA-541");
  display.setCursor(0, 36);
  display.println("*SIMA-564");
  display.setCursor(10, 48);
  display.println("DEPT. OF EEE(SEC)");
  display.display();
  delay(3000);
  display.clearDisplay();
  display.display();
  mlx.begin();

}

void loop() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = duration * 0.034 / 2;
  Serial.println(distance);
  if (distance <= 5)
  {
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(20, 0);
    display.print("ATMOSPHERE ");
    display.print(mlx.readAmbientTempC());
    display.println("C");
    display.setTextSize(2);
    display.setCursor(10, 24);
    display.print("BODY TEMP");
    display.setCursor(30, 48);
    display.print(mlx.readObjectTempF());
    display.println("F");
    if (mlx.readObjectTempF()>= 98)
    {
      digitalWrite(LED2, HIGH);
      delay(1000);
      digitalWrite(LED2, LOW);
    }
    display.display();
    delay(500);
    display.clearDisplay();
    delay(500);
  }
  else if (distance > 5)
  {
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, 30);
    display.println("GET CLOSER");
    display.display();
    delay(500);
    display.clearDisplay();
    delay(500);
  }



}

#include "config.h"
#define LED_PIN 2

AdafruitIO_Feed *digital = io.feed("saida");
AdafruitIO_Feed *color = io.feed("led");

void handleMessage(AdafruitIO_Data *data);
void ColorHex(AdafruitIO_Data *data);

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
  while (!Serial);

  Serial.print("Conectando com Adafruit IO");
  io.connect();

  digital->onMessage(handleMessage);
  color->onMessage(ColorHex);

  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.println(io.statusText());
  digital->get();
}

void loop() {
  io.run();  
}

void handleMessage(AdafruitIO_Data *data)
{
  
  
  Serial.println("recebido <- ");
  if(data->toPinLevel() == HIGH){
    Serial.println("HIGH");
    digitalWrite(LED_PIN, data->toPinLevel());
  }
  else{
    Serial.println("LOW");
    digitalWrite(LED_PIN, data->toPinLevel());
  } 

}

void ColorHex(AdafruitIO_Data *data)
{
  Serial.print("string :");
  Serial.println(data->toString());

  String hexColor = data->toString();
  long number = strtol(hexColor.c_str() + 1, NULL, 16);
  int red = (number >> 16) & 0xFF;
  int green = (number >> 8) & 0xFF;
  int blue = number & 0xFF;

  Serial.print("R :");
  Serial.println(red);
  Serial.print("G :");
  Serial.println(green);
  Serial.print("B :");
  Serial.println(blue);
}

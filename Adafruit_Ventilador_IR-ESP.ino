#include <ESP8266WiFi.h>
#include <AdafruitIO_WiFi.h>

// Configuración de Adafruit IO
#define IO_USERNAME "XXXXXXXXXXXX"
#define IO_KEY "XXXXXXXXXXXXX"
#define WIFI_SSID "XXXXXXXXXXXXX"
#define WIFI_PASS "XXXXXXXXXXX"

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

#include <IRremoteESP8266.h>
#include <IRsend.h>

const int emisorIRPin = 16;
IRsend emisorIR(emisorIRPin);

AdafruitIO_Feed *feed1 = io.feed("Encender Ventilador");
AdafruitIO_Feed *feed2 = io.feed("Velocidad");
AdafruitIO_Feed *feed3 = io.feed("Rotacion");
AdafruitIO_Feed *feed4 = io.feed("Modo");

void handleMessage(AdafruitIO_Data *data)
{
  Serial.print("Recibido <- ");
  Serial.println(data->toInt());

  int valor = data->toInt();

  if (valor == 1)
  {
    Serial.println("Encender");
    emisorIR.sendNEC(0x1FE807F);
  }
  else if (valor == 2)
  {
    Serial.println("Velocidad");
    emisorIR.sendNEC(0xXXXXX);
  }
  else if (valor == 3)
  {
    Serial.println("Rotar");
    emisorIR.sendNEC(0xXXXXX);
  }
  else if (valor == 4)
  {
    Serial.println("Modo");
    emisorIR.sendNEC(0xXXXXX);
  }
}

void setup()
{
  Serial.begin(115200);
  io.connect();

  emisorIR.begin();

  feed1->onMessage(handleMessage);
  feed2->onMessage(handleMessage);
  feed3->onMessage(handleMessage);
  feed4->onMessage(handleMessage);

  while (io.status() < AIO_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.println(io.statusText());
}

void loop()
{
  io.run();
}

#include <SPI.h>
#include <SD.h>
#include "pins.h"

File file;

void setup()
{
    Serial.begin(9600);
    pinMode(_ERROR_LED, OUTPUT);

    while (!SD.begin(10))
        digitalWrite(_ERROR_LED, HIGH);
    digitalWrite(_ERROR_LED, LOW);
    while (!file)
    {
        file = SD.open("data.csv", FILE_WRITE);
        digitalWrite(_ERROR_LED, HIGH);
    }
    file.println("Time, Reading1, Reading2");
    file.close();
    digitalWrite(_ERROR_LED, LOW);
}

void loop()
{
    file = SD.open("data.csv", FILE_WRITE);
    if (file)
    {
        digitalWrite(_ERROR_LED, LOW);
        int reading1, reading2;
        reading1 = analogRead(_SOIL_SENSOR_1);
        reading2 = analogRead(_SOIL_SENSOR_2);

        file.print(millis());
        file.print(", ");
        file.print(reading1);
        file.print(", ");
        file.println(reading2);
        file.close();
    }
    else
        digitalWrite(_ERROR_LED, HIGH);
    delay(500);
}
#include <SPI.h>
#include <SD.h>
#include "pins.h"

File file;

void setup()
{
    Serial.begin(9600);
    pinMode(_SOIL_DIGITAL_READ, INPUT);
    pinMode(_ERROR_LED, OUTPUT);

    while (!SD.begin(10))
    {
        digitalWrite(_ERROR_LED, HIGH);
    }
    digitalWrite(_ERROR_LED, LOW);
}

void loop()
{
    file = SD.open("data.csv", FILE_WRITE);
    if (file)
        file.println("Time, Reading1, Reading2");

    int reading1 = 0, reading2 = 0;
    while (file)
    {
        reading1 = analogRead(_SOIL_SENSOR_1);
        reading2 = analogRead(_SOIL_SENSOR_2);
        file.println(millis() + ", " + reading1 + ", " + reading2);
        file.close();
        delay(500);
        file = SD.open("data.csv", FILE_WRITE);
    }
}
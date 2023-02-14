// Reading from SD card

#include <SD.h>

// // Pin 10 on Arduino Uno
#define CS_PIN 10

// initialize file for SD card to write to
File sdcard_file;

void setup(void)
{
    // Start serial communication for debugging purposes
    Serial.begin(115200);

    // SD Card Initialization
    if (SD.begin())
    {
        Serial.println("SD card is ready to use.");
    }
    else
    {
        Serial.println("SD card initialization failed");
        return;
    }
    sdcard_file = SD.open("data.txt", FILE_READ);
    if (sdcard_file)
    {
        Serial.println("data.txt:");
        // read from the file until there's nothing else in it:
        while (sdcard_file.available())
        {
            Serial.write(sdcard_file.read());
        }
        // close the file:
        sdcard_file.close();
    }
    else
    {
        // if the file didn't open, print an error:
        Serial.println("error opening data.txt");
    }
}

void loop(void)
{
}

/*********
  Rui Santos
  Complete project details at http://randomnerdtutorials.com
  Based on the Dallas Temperature Library example
*********/

#include <OneWire.h>
#include <DallasTemperature.h>
#include <SD.h>
#include <LowPower.h>
// Data wire is connecting to the Arduino digital pin 2
#define SENSOR_PIN 2

// Pin 10 on Arduino Uno
#define CS_PIN 10

// Set the baud rate for serial communication (9600 is the standard for most Arduino boards)
#define BAUD_RATE 9600
// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(SENSOR_PIN);
// Pass our oneWire pointer to Dallas Temperature sensor
DallasTemperature sensors(&oneWire);

// initialize file for SD card to write to
File sdcard_file;
void setup(void)
{
  //
  Serial.begin(BAUD_RATE);

  // Declare input for SD card
  pinMode(SENSOR_PIN, INPUT);

  // Declare output for SD card
  pinMode(CS_PIN, OUTPUT);

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
  sdcard_file = SD.open("data.txt");

  // Start up the library
  sensors.begin();
}

void loop(void)
{
  // Call sensors.requestTemperatures() to issue a global temperature and Requests to all devices on the bus
  sensors.requestTemperatures();

  Serial.print(" Time: ");
  Serial.print(millis());
  Serial.print("     ");
  Serial.print(" Fahrenheit temperature: ");
  Serial.println(sensors.getTempFByIndex(0));
  sdcard_file = SD.open("data.txt", FILE_WRITE);

  if (sdcard_file)
  {
    sdcard_file.print(millis());
    sdcard_file.print(",");

    sdcard_file.println(sensors.getTempFByIndex(0));
    sdcard_file.close(); // Close the file
  }
  // If the file didn't open, print an error:
  else
  {
    Serial.println("error opening data.txt");
  }
  // Run program every 10 minutes
  for (int i = 0; i < 74; i++)
  {
    LowPower.idle(SLEEP_8S, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, SPI_OFF, USART0_OFF, TWI_OFF);
  }
}
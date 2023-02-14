# 1 "/Users/machina/Developer/temperature_data_logger/temperature_data_logger.ino"

/*********

  Rui Santos

  Complete project details at http://randomnerdtutorials.com

  Based on the Dallas Temperature Library example

*********/
# 8 "/Users/machina/Developer/temperature_data_logger/temperature_data_logger.ino"
# 9 "/Users/machina/Developer/temperature_data_logger/temperature_data_logger.ino" 2
# 10 "/Users/machina/Developer/temperature_data_logger/temperature_data_logger.ino" 2
# 11 "/Users/machina/Developer/temperature_data_logger/temperature_data_logger.ino" 2
# 12 "/Users/machina/Developer/temperature_data_logger/temperature_data_logger.ino" 2
// Data wire is connecting to the Arduino digital pin 2


// // Pin 10 on Arduino Uno


// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(2);
// Pass our oneWire reference to Dallas Temperature sensor
DallasTemperature sensors(&oneWire);

// initialize file for SD card to write to
File sdcard_file;
void setup(void)
{
  // Start serial communication for debugging purposes
  Serial.begin(115200);

  // Declare input for SD card
  pinMode(2, 0x0);

  // Declare output for SD card
  pinMode(10, 0x1);

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
  sdcard_file = SD.open("data.txt", (O_READ | O_WRITE | O_CREAT | O_APPEND));

  // uncomment to wipe previous temperature values
  if (sdcard_file)
  {
    sdcard_file.print(millis());
    sdcard_file.print(",");

    sdcard_file.println(sensors.getTempFByIndex(0));
    sdcard_file.close(); // close the file
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

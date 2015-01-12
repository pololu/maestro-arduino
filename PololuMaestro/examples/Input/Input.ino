/* This example shows how to use a Maestro channel that has been
configured as an Input. Examples of inputs are a switch, a
pushbutton, or an analog sensor.

This example tries to read the first 6 channels (0-5) as though
they are inputs and writes the results to the USB serial port so
that the results can be seen in the Serial Monitor.

Before using this example, you should go to the Serial Settings
tab in the Maestro Control Center and apply these settings:

* Serial mode: UART, fixed baud rate
* Baud rate: 9600
* CRC disabled

Be sure to click "Apply Settings" after making any changes.

This example also assumes you have connected your Arduino to your
Maestro appropriately. If you have not done so, please see
https://github.com/pololu/maestro-arduino for more details on how
to make the connection between your Arduino and your Maestro.
Since the sketch requests data from the Maestro, the serial
connection must be wired to be bi-directional. */

#include <PololuMaestro.h>

/* On boards with a hardware serial port available for use, use
that port to communicate with the Maestro. For other boards,
create a SoftwareSerial object using pin 10 to receive (RX) and
pin 11 to transmit (TX). */
#ifdef SERIAL_PORT_HARDWARE_OPEN
  #define maestroSerial SERIAL_PORT_HARDWARE_OPEN
#else
  #include <SoftwareSerial.h>
  SoftwareSerial maestroSerial(10, 11);
#endif

/* Next, create a Maestro object using the serial port.

Uncomment one of MicroMaestro or MiniMaestro below depending
on which one you have. */
MicroMaestro maestro(maestroSerial);
//MiniMaestro maestro(maestroSerial);

void setup()
{
  // Set the baud rate for the Serial Monitor
  Serial.begin(115200);
  // Set the serial baud rate.
  maestroSerial.begin(9600);
}

void loop()
{
  /* Read the position on the first 6 channels and output it to
  the USB serial connection for the Serial Monitor to see. */
  for (uint8_t i = 0; i < 6; i++)
  {
    uint16_t position = maestro.getPosition(i);
    Serial.print("Channel: ");
    Serial.print(i);
    Serial.print(" Position: ");
    Serial.println(position);
  }
  delay(1000);
}

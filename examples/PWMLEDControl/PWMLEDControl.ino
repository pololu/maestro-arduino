/* This example shows the Maestro servo controller library using
the PWM channel to control the brightness of an LED. It assumes
you have connected the anode of your LED to PWM channel through
an appropriate current limiting resistor (1k Ohm on typical LEDs)
on your Maestro and connect the other end of the LED to ground.
(For the 12-Channel Mini Maestro, the PWM channel is pin 8, and
pin 12 for the 18 and 24-Channel Mini Maestros.)

Before using this example, you should go to the Serial Settings
tab in the Maestro Control Center and apply these settings:

 * Serial mode: UART, fixed baud rate
 * Baud rate: 9600
 * CRC disabled

Be sure to click "Apply Settings" after making any changes.

This example also assumes you have connected your Arduino to your
Maestro appropriately and verified the LED on the PWM channel is
powered correctly. If you have not done so, please see
https://github.com/pololu/maestro-arduino for more details on how
to make the connection between your Arduino and your Maestro. */

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

// Next, create a Maestro object using the serial port.
MiniMaestro maestro(maestroSerial);

void setup()
{
  // Set the serial baud rate.
  maestroSerial.begin(9600);
}

void loop()
{
  uint16_t pwmPeriod = 4800;
  uint32_t stepIncrement = 250;
  uint32_t onTime = 0;

  // Fade LED in.
  for (; onTime < pwmPeriod; onTime += stepIncrement)
  {
    maestro.setPWM(onTime, pwmPeriod);
    delay(30);
  }
  delay(500);

  // Fade LED out.
  for (; onTime != 0; onTime -= stepIncrement)
  {
    maestro.setPWM(onTime, pwmPeriod);
    delay(30);
  }
  maestro.setPWM(0, pwmPeriod);
  delay(500);
}

/* This example shows how to control Maestro scripts with an
Arduino. It assumes you have an RC hobby servo connected on
channel 0 of your Maestro, and that you have already used the
Maestro Control Center software to verify that the servo is
powered correctly and moves when you command it to from the
Maestro Control Center software.

Before using this example, you should go to the Serial Settings
tab in the Maestro Control Center and apply these settings:

* Serial mode: UART, fixed baud rate
* Baud rate: 9600
* CRC disabled

Be sure to click "Apply Settings" after making any changes.

It also assumes you have connected your Arduino to your Maestro
appropriately. If you have not done so, please see
https://github.com/pololu/maestro-arduino for more details on how
to make the connection between your Arduino and your Maestro.

Also, the Maestro needs to have the script in the comment
below installed on it. */

/*
# Maestro script for Script.ino Arduino library example.
# Copy into the Script tab of the Maestro Control Center and
# click Apply Settings.

# Don't do anything by default.
begin
repeat

# Subroutine 0
sub alternate_mid_to_high
  begin
    6000 0 servo
    1000 delay
    7000 0 servo
    1000 delay
  repeat

# Subroutine 1
# Expects the delay time to be on the top of the stack
sub alternate_mid_to_low
  begin
    6000 0 servo
    dup delay
    5000 0 servo
    dup delay
  repeat
*/

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
  maestroSerial.begin(9600);
}

void loop()
{
  /* Subroutine numbers can be found by clicking "View Compiled
  Code..." on the Maestro Control Center script tab.

  Restart script at subroutine 0. Subroutine 0 constantly
  alternates the servo position from the neutral position to the
  high end of the range. */
  maestro.restartScript(0);
  delay(4000);

  // Stop the running script.
  maestro.stopScript();

  /* Restart subroutine 1 with the value 2000 on the stack.

  Subroutine 1 constantly alternates the servo position from the
  neutral position to the low end of the range. In this case, The
  parameter put on to the stack represents how long the delay is
  between servo movements.*/
  maestro.restartScriptWithParameter(1, 2000);
  delay(4000);
}

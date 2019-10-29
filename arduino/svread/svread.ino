/*
 * Solar voltage reader
 *
 * Connect the middle terminal pins on the Solar Buddy (or I guess
 * whatever) to A1 or A0, and run this.
 *
 * NB: you'll probably want a voltage divider; nominal 6V output
 * (but I've seen as high as 9.1 on mine) will be over the 5V
 * limit on the pins; anything over 5V and you'll get max readings
 * or damage the board.
 */
void
setup()
{
	Serial.begin(9600);
	while (!Serial) ;
	Serial.println("BOOT OK");
}


void
loop()
{
	int	voltage = analogRead(A1);
	Serial.print("A1: ");
	Serial.println(voltage);
	voltage = analogRead(A0);
	Serial.print("A0: ");
	Serial.println(voltage);
	delay(1000);
}

/*

  Capacitorial
  Uses an Arduino to drives an RC circuit and measure the capcitive discharge.

  For info and cuircuit diagrams see https://github.com/tardate/LittleArduinoProjects/tree/master/playground/Capacitorial

 */

const int charge_pin = 8;               // the pin we'll drive our charging from
const int charge_time = 10;             // how long to charge the capacitor each time
const int charge_frequency = 200;       // frequency of the charging cycle
int charge_counter = 0;                 // keep track of the charging duty cycle

const int signal_pin = A0;              // the pin we'll read our charge values from
int signal_value = 0;                   // value read from the signal_pin

void setup() {
  Serial.begin(9600);                   // initialize serial communications at 9600 bps
  pinMode(charge_pin, OUTPUT);          // enable the charge_pin
  pinMode(signal_pin, INPUT);           // enable the signal_pin

  digitalWrite(charge_pin, HIGH);       // start things off in charging mode
}

void loop() {

  // what to do at the end of the charging duty cycle - stop charging
  if(charge_counter == charge_time) {
    digitalWrite(charge_pin, LOW);
  }

  // what to do at the end of the charge cycle - reset
  if(charge_counter == charge_frequency) {
    digitalWrite(charge_pin, HIGH);
    charge_counter = 0;
  } else {
    charge_counter += 1;
  }
  //Serial.print("Counter: ");
  //Serial.println(charge_counter);

  // read the current value and send to the serial port
  signal_value = analogRead(signal_pin);
  Serial.println(signal_value);

  // wait a tic before going around again
  delay(1);
}

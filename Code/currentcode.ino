#define MQ2pin 0

int motorPin = 11;
float sensorValue;  //variable to store sensor value

void setup() {
	Serial.begin(9600); // sets the serial port to 9600
  pinMode(motorPin, OUTPUT);
	Serial.println("MQ2 warming up!");
	delay(20000); // allow the MQ2 to warm up
}

void loop() {
  // Check for commands from Python
  if (Serial.available()) {
    char command = Serial.read();

    // Control the motor based on the command
    if (command == '1') {
      digitalWrite(motorPin, HIGH);  // Turn on the motor
    } else if (command == '0') {
      digitalWrite(motorPin, LOW);   // Turn off the motor
    }
  }

  // Read the sensor value
  sensorValue = analogRead(MQ2pin);

  // Print the sensor value
  Serial.print("Sensor Value: ");
  Serial.println(sensorValue);

  delay(2000); // Wait 2 seconds for the next reading
}


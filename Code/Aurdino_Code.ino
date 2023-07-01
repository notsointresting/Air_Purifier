// MQ135 Gas Sensor Pin
const int mq135Pin = A1;
const int mq2Pin = A0;

// Threshold value for smoke detection
const int smokeThreshold = 200; // Modify this value based on calibration

// Calibration Curves for Different Gases
float COCurve = 116.6020682;
float COExponent = -2.769034857;

float VOCCurve = 76.63;
float VOCExponent = -2.83;

float NH3Curve = 31.98074339;
float NH3Exponent = -3.293038648;

float NO2Curve = 12.87993118;
float NO2Exponent = -0.232728202;

// Function to read gas concentration from MQ135 sensor
float readGasConcentration(float curve, float exponent) {
  int sensorValue = analogRead(mq135Pin);
  
  // Convert analog value to voltage
  float voltage = sensorValue * (5.0 / 1023.0);
  
  // Calculate the resistance of the sensor (RS)
  float RS = ((5.0 - voltage) / voltage);
  
  // Calculate the gas concentration using the ratio and the exponent
  float gasConcentration = pow(10, ((log10(RS / curve)) / exponent));
  
  return gasConcentration;
}

void setup() {
  Serial.begin(9600);
}

void loop() {

  // Read Gas concentration from MQ2 sensor
  int val = analogRead(mq2Pin);
  float GasConcen = (val * 0.0123) + 10.456;
  // Read gas concentrations
  float COValue = readGasConcentration(COCurve, COExponent);
    float VOCValue = readGasConcentration(VOCCurve, VOCExponent);
  float NH3Value = readGasConcentration(NH3Curve, NH3Exponent);
  float NO2Value = readGasConcentration(NO2Curve, NO2Exponent);
  
  if (val > smokeThreshold) {
    Serial.println("Smoke detected");
  } else {
    Serial.println("No smoke detected");
  }
  Serial.print("CO Concentration: ");
  Serial.print(COValue);
  Serial.println(" ppm");
  
  
  Serial.print("NH3 Concentration: ");
  Serial.print(NH3Value);
  Serial.println(" ppm");
  
  Serial.print("NO2 Concentration: ");
  Serial.print(NO2Value);
  Serial.println(" ppm");

  Serial.print("VOC Concentration: ");
  Serial.print(VOCValue);
  Serial.println(" ppm");
  
  delay(1000); // Delay for 1 second
}

const int SERIAL_LCD_PIN = 13;
const int THERMOMETER_PIN = 5;
const int COMPRESSOR_PIN = 6;

const boolean DEBUG = false;

float temp = -1000;
float setTemp = 3.5;
float tempThreshold = 2;
const boolean fahrenheit = false;

boolean compressor = false;
boolean compressorDelayed = false;
float compressorLastOffTime = 0; // compressor should be off initially
float compressorLastOnTime = 0;
float compressorTotalOnTime = 0;
const int compressorDelay = 300; // 5 minutes

void setup(void) {
  Serial.begin(9600);

  setupCompressor();
  setupLCD();
}

void loop(void) {
  temp = getTemp();
  if (fahrenheit && temp != -1000) {
    temp = toFahrenheit(temp);
  }

  updateCompressor();

  updateLCD();

  if (DEBUG) {
    Serial.print("Temp: ");
    Serial.print(temp);
    Serial.print(" deg");
    Serial.println(fahrenheit ? "F" : "C");
  }

  delay(1000);
}

void setupCompressor() {
  pinMode(COMPRESSOR_PIN, OUTPUT);
  digitalWrite(COMPRESSOR_PIN, LOW);
}

void updateCompressor() {
  float time = getTime();

  if (compressor) {
    // compressor currently on
    if (temp <= setTemp) {
      if (DEBUG) {
        Serial.println("Compressor turned off!");
      }
      digitalWrite(COMPRESSOR_PIN, LOW);
      compressor = false;
      compressorLastOffTime = time;
      compressorTotalOnTime += time - compressorLastOnTime;
    }
  } else {
    // compressor currently off
    if (temp > setTemp + tempThreshold) {
      if (DEBUG) {
        Serial.println("Too warm!");
      }
      if (time - compressorLastOffTime >= compressorDelay) {
        if (DEBUG) {
          Serial.println("Compressor turned on!");
        }
        digitalWrite(COMPRESSOR_PIN, HIGH);
        compressor = true;
        compressorDelayed = false;
        compressorLastOnTime = time;
      } else {
        compressorDelayed = true;
        if (DEBUG) {
          Serial.print("Compressor delay: ");
          Serial.print(time - compressorLastOffTime);
          Serial.print("/");
          Serial.println(compressorDelay);
        }
      }
    } else {
      compressorDelayed = false;
    }
  }
}

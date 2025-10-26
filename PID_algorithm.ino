#include <math.h>
#define buttonPin 2
#define thermistorPin A0
#define potPin A5
#define control_pin 6

int menuState = 0;
int lastButtonState = HIGH;

const float A = 0.001129148;
const float B = 0.000234125;
const float C = 8.76741e-8;

int setTemperature = 30;

//PID constants
int kp = 90, ki = 30, kd = 80;
int PID_p = 0, PID_i = 0, PID_d = 0;
float PID_error;
float prev_error;
float PID_value;

//time constants
float time = 0;
float prev_time = 0;
float dt = 0;

double Thermistor(int RawADC)
{
 double temp_K, temp_C, lnR;
 lnR = log(10000.0 * ((1024.0 / RawADC - 1)));
 temp_K = 1 /(A + B * lnR + C * pow(lnR, 3));
 temp_C = temp_K - 273.15;
 return temp_C;
}

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  int reading = digitalRead(buttonPin);

  // Handle button press to cycle menu
  if (reading == LOW && lastButtonState == HIGH) {
    delay(50); // debounce
    if (digitalRead(buttonPin) == LOW) {
      menuState = (menuState + 1) % 2;
      Serial.print("Menu: ");
      Serial.println(menuState);
    }
  }

  lastButtonState = reading;

  // Menu 0: Read Thermistor
  if (menuState == 0) {
      prev_time = time;
      time = millis();
      dt = (time - prev_time) / 1000;

      double thermistorval = Thermistor(analogRead(thermistorPin));

      PID_error = setTemperature - thermistorval;
      PID_p = 0.01 * kp * PID_error;
      PID_i = 0.01 * PID_i + (ki*PID_error);
      PID_d = 0.01 * kd * ((PID_error - prev_error) / dt);

      PID_value = PID_p + PID_i + PID_d;

      if (PID_error < 0)
      {
        PID_value = 0;
      }
      else
      {
        PID_value = 255;
      }
      analogWrite(control_pin, PID_value);
      prev_error = PID_error;

      Serial.print("Temperature:");
      Serial.print(thermistorval);
      Serial.println("°C");
      delay(250);
  }

  // Menu 1: Read Potentiometer
  else if (menuState == 1) {
    int potValue = analogRead(potPin);
    setTemperature = map(potValue, 0, 1023, 300, 1000) / 10.0;
    Serial.print("Setting Temperature:");
    Serial.print(setTemperature);
    Serial.println(" °C");
    delay(250);
  }

}

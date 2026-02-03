#include <Arduino.h>

// ---------------- PIN DEFINITIONS ----------------
#define GREEN   2
#define YELLOW  4
#define RED     16
#define BUZZER  15

#define BUTTON  0      // Vehicle select button

#define TRIG    5
#define ECHO    18

// ---------------- VEHICLE DATA ----------------
struct Vehicle {
  const char* name;
    long safeDistance;
      long warningDistance;
      };

      Vehicle vehicles[3] = {
        {"Bike", 50, 20},
          {"Van",  70, 40},
            {"Bus",  90, 60}
            };

            int vehicleType = 0;  // 0=Bike, 1=Van, 2=Bus

            // ---------------- SETUP ----------------
            void setup() {
              Serial.begin(9600);

                pinMode(GREEN, OUTPUT);
                  pinMode(YELLOW, OUTPUT);
                    pinMode(RED, OUTPUT);
                      pinMode(BUZZER, OUTPUT);

                        pinMode(BUTTON, INPUT_PULLUP);

                          pinMode(TRIG, OUTPUT);
                            pinMode(ECHO, INPUT);

                              Serial.println("System Started");
                              }

                              // ---------------- LOOP ----------------
                              void loop() {

                                // -------- BUTTON LOGIC (Cycle vehicle type) --------
                                  static bool lastButtonState = HIGH;
                                    bool currentState = digitalRead(BUTTON);

                                      if (lastButtonState == HIGH && currentState == LOW) {
                                          vehicleType = (vehicleType + 1) % 3;
                                              Serial.print("Vehicle Selected: ");
                                                  Serial.println(vehicles[vehicleType].name);
                                                      delay(300); // debounce
                                                        }
                                                          lastButtonState = currentState;

                                                            // -------- ULTRASONIC TRIGGER --------
                                                              digitalWrite(TRIG, LOW);
                                                                delayMicroseconds(2);
                                                                  digitalWrite(TRIG, HIGH);
                                                                    delayMicroseconds(10);
                                                                      digitalWrite(TRIG, LOW);

                                                                        long duration = pulseIn(ECHO, HIGH, 30000); // timeout 30ms
                                                                          long distance = (duration > 0) ? duration * 0.034 / 2 : 0;

                                                                            Serial.print("Distance: ");
                                                                              Serial.print(distance);
                                                                                Serial.println(" cm");

                                                                                  // -------- RESET OUTPUTS --------
                                                                                    digitalWrite(GREEN, LOW);
                                                                                      digitalWrite(YELLOW, LOW);
                                                                                        digitalWrite(RED, LOW);
                                                                                          noTone(BUZZER);

                                                                                            // -------- LOGIC --------
                                                                                              if (distance == 0) {
                                                                                                  // No object detected
                                                                                                    }
                                                                                                      else if (distance > vehicles[vehicleType].safeDistance) {
                                                                                                          // SAFE ZONE
                                                                                                              digitalWrite(GREEN, HIGH);
                                                                                                                }
                                                                                                                  else if (distance > vehicles[vehicleType].warningDistance) {
                                                                                                                      // WARNING ZONE
                                                                                                                          digitalWrite(YELLOW, HIGH);

                                                                                                                              tone(BUZZER, 2000);   // short beep
                                                                                                                                  delay(200);
                                                                                                                                      noTone(BUZZER);
                                                                                                                                        }
                                                                                                                                          else {
                                                                                                                                              // DANGER ZONE
                                                                                                                                                  digitalWrite(RED, HIGH);

                                                                                                                                                      tone(BUZZER, 2500);   // long beep
                                                                                                                                                          delay(500);
                                                                                                                                                              noTone(BUZZER);
                                                                                                                                                                }

                                                                                                                                                                  delay(200);
                                                                                                                                                                  }
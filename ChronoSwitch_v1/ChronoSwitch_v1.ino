#include <Wire.h>
#include <RTClib.h>
#include <Servo.h>

// ══════════════════════════════════════
//   ALARM SETTINGS
// ══════════════════════════════════════
#define WAKE_HOUR     7
#define WAKE_MINUTE   10

#define SLEEP_HOUR    23
#define SLEEP_MINUTE  0

// ══════════════════════════════════════
//   SERVO SETTINGS
// ══════════════════════════════════════
#define SERVO_REST      120
#define SERVO_PUSH      20
#define PUSH_DURATION   2000
#define RETURN_DELAY    1500

RTC_DS3231 rtc;
Servo servo;

bool wakeFired  = false;
bool sleepFired = false;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  Serial.println("ChronoSwitch Booting...");

  servo.attach(9);
  servo.write(SERVO_REST);

  if (!rtc.begin()) {
    Serial.println("RTC NOT FOUND");
    while (1);
  }

  /* The line below automatically takes the time from your laptop 
     at the moment of compilation/upload.
  */
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  
  Serial.println("Time synced with Laptop successfully!");
  Serial.print("Current RTC Time: ");
  printTime(rtc.now());
}

void loop() {
  DateTime now = rtc.now();

  // Print time every 5 seconds instead of every 1 to keep Serial clean
  static unsigned long lastPrint = 0;
  if (millis() - lastPrint > 5000) {
    printTime(now);
    lastPrint = millis();
  }

  // WAKE TRIGGER
  if (now.hour() == WAKE_HOUR && now.minute() == WAKE_MINUTE && !wakeFired) {
    wakeFired = true;
    pushSwitch("WAKE UP");
  }

  // SLEEP TRIGGER
  if (now.hour() == SLEEP_HOUR && now.minute() == SLEEP_MINUTE && !sleepFired) {
    sleepFired = true;
    pushSwitch("SLEEP TIME");
  }

  // Reset flags when the minute passes
  if (now.minute() != WAKE_MINUTE) wakeFired = false;
  if (now.minute() != SLEEP_MINUTE) sleepFired = false;

  delay(1000);
}

void printTime(DateTime now) {
  if (now.hour() < 10) Serial.print("0");
  Serial.print(now.hour());
  Serial.print(":");
  if (now.minute() < 10) Serial.print("0");
  Serial.print(now.minute());
  Serial.print(":");
  if (now.second() < 10) Serial.print("0");
  Serial.println(now.second());
}

void pushSwitch(String msg) {
  Serial.print("Action: ");
  Serial.println(msg);

  servo.write(SERVO_PUSH);
  delay(PUSH_DURATION);

  servo.write(SERVO_REST);
  delay(RETURN_DELAY);
}

#include <openag_pwm_actuator.h>

#define PIN 13

PwmActuator actuator(PIN, false, 0);

void setup() {
  Serial.begin(9600);
  actuator.begin();
}

std_msgs::Float32 cmd;

void loop() {
  actuator.update();

  if (Serial.available()) {
    cmd.data = Serial.parseFloat();
    Serial.println(cmd.data);
    actuator.set_cmd(cmd);
  }
  if (actuator.has_error) {
    Serial.print("Error: ");
    Serial.println(actuator.error_msg);
    actuator.has_error = false;
  }
}

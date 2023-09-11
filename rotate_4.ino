#include <Dynamixel2Arduino.h>

#if defined(ARDUINO_OpenRB)  // When using OpenRB-150
  //OpenRB does not require the DIR control pin.
  #define DXL_SERIAL Serial1
  #define DEBUG_SERIAL Serial
  const int DXL_DIR_PIN = -1;
#else // Other boards when using DynamixelShield
  #define DXL_SERIAL   Serial1
  #define DEBUG_SERIAL Serial
  const int DXL_DIR_PIN = 2; // DYNAMIXEL Shield DIR PIN
#endif
 
const float DXL_PROTOCOL_VERSION = 2.0;

Dynamixel2Arduino dxl(DXL_SERIAL, DXL_DIR_PIN);

//This namespace is required to use Control table item names
using namespace ControlTableItem;

void setup() {
  DEBUG_SERIAL.begin(115200);
  
  dxl.begin(1000000);
  dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);
  for (uint8_t DXL_ID = 1; DXL_ID < 5; DXL_ID++){
    dxl.ping(DXL_ID);
    dxl.torqueOff(DXL_ID);
    dxl.setOperatingMode(DXL_ID, OP_VELOCITY);
    dxl.torqueOn(DXL_ID);
  }
}

void loop() {
  // Set Goal Velocity using RPM
  dxl.ledOn(1);
  for (uint8_t DXL_ID = 1; DXL_ID < 5; DXL_ID++){
    dxl.setGoalVelocity(DXL_ID, 100, UNIT_RPM);
  }

  delay(1000);
  
  dxl.ledOff(1);
  for (uint8_t DXL_ID = 1; DXL_ID < 5; DXL_ID++){
    dxl.setGoalVelocity(DXL_ID, 0, UNIT_RPM);
  }

  delay(1000);
}

#include <Arduino.h> // Including the arduino library

// boolean to check for new data
boolean newData = false;

// IDK what this does but it works
typedef void (*functionsArray) (int pin, int value);

// Function prototypes
void recvCommand();
void showNewData();
void runCommand();
void writeDigital(int pin, int value);
void readDigital(int pin, int value);

// Command structure
struct {
   unsigned int type : 3; // 3 bits for command type (9 values)
   unsigned int pin : 5;  // 5 bits for pin number (32 values)
   byte value;            // 8 bits for pin value (256 values)
} command;

// Create array of functions
functionsArray functions[] = 
  {
      writeDigital, 
      readDigital
  };

// Setup, starts serial
void setup() {
  Serial.begin(9600);
  Serial.println("<Arduino is ready>");
}

// Loop, loops
void loop() {
  recvCommand();  // Gets a new command from serial 
  runCommand();   // Runs that command
}

// Checks if new data is avalible then publishes it to command structure
void recvCommand() {
  if (Serial.available() > 0) {
    byte b1 = Serial.read();
    byte b2 = Serial.read();
    
    command.type = b1;
    command.pin = b1 >> 3;
    command.value = b2;
    newData = true;
  }
}

// Prints the data - For debuging
void showNewData() {
  if (newData == true) {
    Serial.print("Type: ");
    Serial.println(command.type);
    Serial.print("Pin: ");
    Serial.println(command.pin);
    Serial.print("Value: ");
    Serial.println(command.value);
  }
}

// Runs the commands
void runCommand() {
  if (newData == true) {
    showNewData();   // Print for debuging
    functions[command.type](command.pin, command.value);
    newData = false;
  }
}

// The functions

void writeDigital(int pin, int value) {
  digitalWrite(pin, value);
}

void readDigital(int pin, int value) {
  Serial.println(digitalRead(pin));
}


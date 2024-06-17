#include <Arduino.h>

constexpr int uartTxPin = 17; // GPIO17 as TX pin
constexpr int uartRxPin = 16; // Placeholder RX pin
constexpr long uartBaudRate = 19200; // UART baud rate

HardwareSerial uartSerialPort(1); // Use UART1

void setup() {
  // Initialize serial for debugging
  Serial.begin(19200);
  Serial.println("Setup started");

  // Initialize the UART TX pin as OUTPUT and set it to LOW
  pinMode(uartTxPin, OUTPUT);
  digitalWrite(uartTxPin, LOW);
  Serial.println("UART TX pin initialized to LOW");
}

void enableUart() {
  // Set the UART TX pin to HIGH to enable UART communication
  digitalWrite(uartTxPin, HIGH);
  Serial.println("UART TX pin set to HIGH");

  // Initialize UART communication
  uartSerialPort.begin(uartBaudRate, SERIAL_8N1, uartRxPin, uartTxPin);
  Serial.println("UART initialized");
}

void disableUart() {
  // Flush UART and disable it
  uartSerialPort.flush(); // Ensure all data is sent before disabling UART
  uartSerialPort.end();   // End UART communication

  // Set the UART TX pin to LOW
  pinMode(uartTxPin, OUTPUT); // Reinitialize as output
  digitalWrite(uartTxPin, LOW);
  Serial.println("UART TX pin set to LOW");
}

void loop() {
  // Ensure the UART TX pin is LOW
  disableUart();

  // Wait for some time before starting UART communication
  delay(1000);

  // Enable UART and set the UART TX pin to HIGH
  enableUart();

  // Wait for 100 ms
  delay(100);

  // Send "hello world" message over UART
  uartSerialPort.print("G&48");
  Serial.println("Sent G message");

  // Wait for 1000 ms
  delay(1000);

  // Disable UART and set the UART TX pin to LOW
  disableUart();

  // Wait for some time before repeating
  delay(1000);
}

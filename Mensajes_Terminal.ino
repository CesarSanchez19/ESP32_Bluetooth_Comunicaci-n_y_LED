/*

  Establecer una comunicación bidireccional entre el ESP32 y un teléfono Android 
  usando Bluetooth clásico (no BLE), simulando un puerto serial inalámbrico.

  Descripción:
  - Este programa permite enviar y recibir datos entre el ESP32 y un dispositivo Android
    usando el perfil SPP (Serial Port Profile).
  - Los datos que se escriben en el Monitor Serie del IDE de Arduino se envían por Bluetooth.
  - Los datos que se reciben por Bluetooth desde el teléfono se muestran en el Monitor Serie.
  - Esto permite probar el ESP32 como si fuera un módulo Bluetooth serial (similar al HC-05).

  Requisitos:
  - Placa ESP32 con soporte de Bluetooth clásico.
  - Librería <BluetoothSerial.h> (incluida por defecto en el núcleo de ESP32 para Arduino).
  - Monitor Serie activo en el IDE de Arduino (a 9600 baudios).
  - Aplicación de terminal Bluetooth instalada en el teléfono (como "Serial Bluetooth Terminal").
  - Emparejar el dispositivo Android con el ESP32 (nombre: "ESP32_TimeFit").
  - Asegurarse de que el puerto COM correcto esté seleccionado en el IDE de Arduino.

*/

#include "BluetoothSerial.h"  // Librería para comunicación Bluetooth

BluetoothSerial SerialBT;    // Crear objeto de comunicación Bluetooth

void setup() {
  Serial.begin(9600);                 // Inicia la comunicación por USB (Monitor Serie)
  SerialBT.begin("ESP32_TimeFit");           // Inicia Bluetooth con el nombre "ESP32_BT"
  Serial.println("Bluetooth listo para emparejar.");
}

void loop() {
  // Si hay datos desde el monitor serie de la PC, enviarlos por Bluetooth
  if (Serial.available()) {
    char dato = Serial.read();
    SerialBT.write(dato);
  }

  // Si hay datos desde Bluetooth, enviarlos al monitor serie de la PC
  if (SerialBT.available()) {
    char dato = SerialBT.read();
    Serial.write(dato);
  }
}

/*

  Encender y apagar un LED con ESP32 vía Bluetooth clásico, usando el IDE de 
  Arduino y una app como Serial Bluetooth Terminal en Android. 

  Conexión del LED:
  • Ánodo (positivo) del LED → Pin GPIO 23 del ESP32 (se puede cambiar)
  • Cátodo (negativo) del LED → Resistencia de 220Ω → GND

  Descripción:
  - El ESP32 establece comunicación Bluetooth clásica con el nombre "ESP32_TimeFit".
  - Permite recibir mensajes desde un dispositivo Android vía Bluetooth y desde el Monitor Serie del PC.
  - Los mensajes recibidos pueden ser comandos para encender ("1") o apagar ("0") el LED conectado al pin GPIO 23.
  - Cuando se enciende o apaga el LED, el ESP32 envía confirmaciones tanto al móvil como al PC.
  - Si el mensaje no es un comando de LED, se trata como un mensaje de chat y se refleja en ambos lados.
  - Permite comunicación bidireccional para mensajes libres y control del LED.

  Requisitos:
  - Placa ESP32 con soporte Bluetooth clásico.
  - Librería <BluetoothSerial.h> incluida en el entorno ESP32 para Arduino.
  - Aplicación de terminal Bluetooth instalada en el móvil (ejemplo: Serial Bluetooth Terminal).
  - Conexión física del LED con resistencia al pin GPIO 23 (o el pin definido).
  - Monitor Serie activo en Arduino IDE a 9600 baudios.
  - Emparejamiento previo entre ESP32 y el dispositivo Android.

*/

#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

const int ledPin = 23; // Cambia este pin si conectas el LED en otro lugar

void setup() {
  Serial.begin(9600); // Comunicación por USB con PC
  SerialBT.begin("ESP32_TimeFit"); // Nombre del dispositivo Bluetooth
  pinMode(ledPin, OUTPUT); // Pin del LED como salida

  // Mensaje de bienvenida
  Serial.println("ESP32 listo para emparejar vía Bluetooth");
  SerialBT.println("Conectado a ESP32_TimeFit");
}

void loop() {
  // --- Mensajes desde Monitor Serie hacia el móvil ---
  if (Serial.available()) {
    String mensajePC = Serial.readStringUntil('\n');
    mensajePC.trim(); // Quitar espacios y saltos

    SerialBT.println("PC dice: " + mensajePC); // Enviar al móvil

    // También podemos controlar el LED desde la PC
    if (mensajePC == "1") {
      digitalWrite(ledPin, HIGH);
      Serial.println("LED encendido (desde PC)");
      SerialBT.println("LED encendido (desde PC)");
    } else if (mensajePC == "0") {
      digitalWrite(ledPin, LOW);
      Serial.println("LED apagado (desde PC)");
      SerialBT.println("LED apagado (desde PC)");
    }
  }

  // --- Mensajes desde Móvil hacia la PC ---
  if (SerialBT.available()) {
    String mensajeMovil = SerialBT.readStringUntil('\n');
    mensajeMovil.trim(); // Quitar espacios y saltos

    Serial.println("Móvil dice: " + mensajeMovil); // Mostrar en PC

    // Comandos para controlar el LED desde el móvil
    if (mensajeMovil == "1") {
      digitalWrite(ledPin, HIGH);
      Serial.println("LED encendido (desde Móvil)");
      SerialBT.println("LED encendido");
    } else if (mensajeMovil == "0") {
      digitalWrite(ledPin, LOW);
      Serial.println("LED apagado (desde Móvil)");
      SerialBT.println("LED apagado");
    } else {
      // Solo mensaje tipo chat
      SerialBT.println("PC recibió: " + mensajeMovil);
    }
  }
}

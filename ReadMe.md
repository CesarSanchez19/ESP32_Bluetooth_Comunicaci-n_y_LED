
---

# ESP32 Bluetooth Serial y Control de LED

## Descripción

Este proyecto consiste en dos programas para el microcontrolador ESP32 que permiten establecer una comunicación bidireccional con un dispositivo Android mediante **Bluetooth clásico (SPP)**, simulando un puerto serial inalámbrico.

* El primer código permite enviar y recibir mensajes de texto entre el ESP32 y el móvil, funcionando como un puente serial inalámbrico.
* El segundo código extiende esta funcionalidad para incluir el control de un LED conectado al ESP32, que puede ser encendido o apagado mediante comandos simples enviados desde el móvil o desde el monitor serie de la PC.

Ambos programas utilizan la librería `BluetoothSerial.h` para gestionar la comunicación Bluetooth clásica y permiten usar cualquier app terminal Bluetooth en Android para interactuar con el ESP32.

---

## Requisitos

### Hardware

* Placa ESP32 (con soporte para Bluetooth clásico)
* Cable USB para programar y monitorizar el ESP32
* LED y resistencia de 220Ω (solo para el segundo código)
* Cables de conexión para el LED (ánodo al GPIO 23, cátodo a resistencia y luego GND)

### Software

* IDE de Arduino configurado para ESP32
* Librería `BluetoothSerial` incluida en el entorno ESP32 (parte del core oficial)
* Aplicación terminal Bluetooth en Android, por ejemplo:

  * Serial Bluetooth Terminal
  * Bluetooth Terminal HC-05
  * Bluetooth Serial Controller, etc.

---

## Instalación y Uso

1. **Configuración del hardware** (solo para el control de LED):

   * Conecta el LED al pin GPIO 23 y GND mediante resistencia.
2. **Carga el código** en tu placa ESP32 desde el IDE de Arduino.
3. **Abre el monitor serial** a 9600 baudios para visualizar mensajes y estados.
4. **En tu teléfono Android:**

   * Enciende Bluetooth y busca el dispositivo llamado `"ESP32_TimeFit"`.
   * Empareja el dispositivo (si es la primera vez).
   * Abre la app terminal Bluetooth y conéctate al ESP32.
5. **Comunicación:**

   * Envía mensajes desde el monitor serial (PC) y verás que llegan al móvil.
   * Envía mensajes desde el móvil y verás que llegan al monitor serial.
   * En el código con control LED, envía `"1"` para encender y `"0"` para apagar el LED.
   * Los mensajes de control son confirmados por ambos dispositivos.

---

## Resultado Esperado

* Comunicación fluida y en tiempo real entre el ESP32 y un móvil vía Bluetooth clásico.
* Capacidad para enviar mensajes libres en ambas direcciones.
* Control sencillo del estado de un LED desde el móvil o el PC.
* Mensajes de confirmación claros en ambos extremos para cada acción realizada.

---

## Personalización

* Cambia el pin `ledPin` en el código para usar otro GPIO si lo deseas.
* Modifica el nombre Bluetooth `"ESP32_TimeFit"` para identificar tu dispositivo.
* Puedes ampliar el protocolo de mensajes para agregar más comandos.

---

## Notas

* El Bluetooth clásico requiere emparejamiento previo con el dispositivo Android.
* La comunicación se basa en caracteres o cadenas terminadas en salto de línea (`\n`).
* Asegúrate de que la app terminal use el mismo protocolo y velocidad para una correcta comunicación.

Autor: Cesar David Sanchez Trejo

---

# ESP32 AWS IoT Sensor Monitor

## Descripción del Proyecto
Este proyecto consiste en un sistema de monitoreo de sensores basado en ESP32 y AWS IoT. Utiliza un módulo ESP32 para leer los datos de un sensor analógico y los publica en AWS IoT a través de MQTT. Los datos del sensor también se muestran en una pantalla LCD Nokia 5110. El sistema es capaz de suscribirse a un tema MQTT y recibir mensajes, que se muestran en la pantalla LCD.

## Características
- Lectura de datos de un sensor analógico con ESP32.
- Publicación de datos del sensor en AWS IoT a través de MQTT.
- Visualización de datos del sensor en una pantalla LCD Nokia 5110.
- Suscripción a un tema MQTT y visualización de mensajes recibidos en la pantalla LCD.

## Requisitos
- Módulo ESP32.
- Sensor analógico.
- Pantalla LCD Nokia 5110.
- Cuenta de AWS IoT.

## Configuración
1. Conecta el sensor analógico y la pantalla LCD al ESP32 según el esquema proporcionado.
2. Configura las credenciales de AWS IoT en el archivo `secrets.h`.
3. Sube el código al ESP32 utilizando el IDE de Arduino.

## Uso
Una vez que el sistema esté en funcionamiento, leerá continuamente los datos del sensor, los mostrará en la pantalla LCD y los publicará en AWS IoT. También mostrará cualquier mensaje recibido del tema MQTT al que está suscrito.

## Contribuciones
Las contribuciones son bienvenidas. Por favor, abre un issue o pull request para sugerencias o mejoras.

## Licencia

Este proyecto está bajo la Licencia [Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)](https://creativecommons.org/licenses/by-nc/4.0/deed.es).

---

**Carlos S. Vanegas** - Contacto: [ing.carlos.vanegas1@gmail.com](mailto:ing.carlos.vanegas1@gmail.com)


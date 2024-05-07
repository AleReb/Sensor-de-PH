# Sensor-de-PH
## Descripción General
Este proyecto incluye la implementación de sensores de temperatura y humedad utilizando Arduino. Los códigos proporcionados permiten la lectura de datos de los sensores y la visualización de la temperatura en grados Celsius.

## Componentes y Tecnologías
- **Arduino**: Plataforma de hardware libre para la construcción de proyectos electrónicos.
- **DS18S20**: Sensor de temperatura.
- **DHT22**: Sensor de humedad y temperatura.
- **OneWire**: Biblioteca utilizada para la comunicación con dispositivos OneWire, como el sensor de temperatura DS18S20.

## Instalación y Uso
Para utilizar estos proyectos, deberás tener instaladas las bibliotecas OneWire y DHT en tu entorno de desarrollo Arduino. Conecta los sensores a los pines correspondientes en tu placa Arduino como se especifica en los códigos y sube el programa a tu Arduino.

## Ejemplos de Uso
- **Lectura de Temperatura**: El sensor DS18S20 se utiliza para medir la temperatura ambiente y los resultados se visualizan a través del puerto serial.
- **Lectura de Humedad y Temperatura con DHT22**: Similar al DS18S20, pero también incluye la capacidad de medir la humedad.

## Contribuciones y Desarrollo Futuro
El proyecto es abierto para contribuciones. Futuras mejoras pueden incluir la integración de estos sensores con sistemas IoT para control y monitoreo remoto, o la mejora de la precisión de los sensores mediante calibración y técnicas avanzadas de procesamiento de señales.
"""

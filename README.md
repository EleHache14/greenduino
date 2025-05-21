# 🌿 Greenduino – Monitor inteligente para plantas y cultivos

Greenduino es un sistema de monitoreo doméstico diseñado para plantas, huertos e invernaderos. Con un presupuesto inferior a 40 €, este proyecto busca ofrecer una solución asequible y funcional para observar condiciones ambientales y medir características físicas de las plantas en tiempo real.

---

## 🔧 Funcionalidad principal

El sistema permite:

* Medir **temperatura**, **humedad ambiental y del suelo**, **intensidad lumínica** y **calidad del aire** mediante sensores específicos.
* Estimar el **diámetro de una planta** usando un **sensor ultrasónico montado en un servo**, con 5 lecturas angulares para mejorar la precisión.
* Mostrar datos en una **pantalla LCD**, con selección de información mediante una app.
* Interactuar mediante una **app móvil conectada por Bluetooth (HC-05)** con cuatro secciones:

  * Conexión Bluetooth
  * Selección de dato a mostrar en LCD
  * Medición de diámetro
  * Consulta remota de todos los sensores

---

## ⚙️ Modos de operación

El sistema cuenta con **dos modos principales**, seleccionables mediante un **potenciómetro** en el panel de control:

1. **Modo Visualización**: muestra en la LCD las variables ambientales elegidas.
2. **Modo Medición de Diámetro**: activa el barrido del servo y realiza 5 mediciones ultrasónicas para calcular el diámetro aproximado de la planta.

---

## 🧩 Componentes utilizados

* Arduino Uno R3
* Sensor DHT (temperatura y humedad)
* Sensor MQ (gases)
* Sensor de humedad del suelo
* Fotoresistor (luz ambiental)
* Módulo Bluetooth HC-05
* Sensor ultrasónico HC-SR04
* Servo SG90
* Pantalla LCD 16x2 4-Bit
* Potenciómetro, LEDs, zumbador, transistor
* Placa protoboard y cables

---

## 🖥️ Código

El programa está dividido en:

1. **Inicialización**:

   * Declaración de variables
   * Configuración de pines
   * Inicialización de sensores y pantalla LCD

2. **Bucle principal**:

   * Lectura del potenciómetro para elegir modo
   * Envío y recepción de datos vía Bluetooth
   * Ejecución de mediciones y cálculo del diámetro

3. **Interacción Bluetooth**:

   * Recepción de comandos desde la app (diferenciados por ID numérico)
   * Envío de valores sensados en formato identificable

---

## 📱 Aplicación móvil

La app permite controlar remotamente el sistema vía Bluetooth. Cuenta con una interfaz minimalista dividida en 4 secciones:

* **Conexión**: emparejamiento con el módulo HC-05
* **LCD**: selección del dato que se muestra
* **Medición**: cálculo del diámetro de la planta
* **Remoto**: consulta de todos los datos sensados en un solo clic

---

## 🚀 Instrucciones de uso

1. **Montaje**:

   * Conecta todos los sensores y módulos según el esquema del circuito.

2. **Código**:

   * Abre el archivo `.ino` en Arduino IDE.
   * Instala las siguientes librerías:

     * `DHT.h`
     * `LiquidCrystal_I2C.h`
     * `SoftwareSerial.h`
   * Selecciona la placa Arduino Uno y el puerto correspondiente.
   * Sube el programa al Arduino.

3. **Emparejamiento Bluetooth**:

   * Empareja el móvil con el módulo HC-05 (PIN por defecto: 1234 o 0000).
   * Abre la app y selecciona el dispositivo.

4. **Uso**:

   * Usa el potenciómetro para cambiar de modo.
   * Consulta datos en la LCD o en la app.
   * Lanza la medición de diámetro desde la app.

---

## 📌 Notas

* En mediciones ultrasónicas, se descartan las lecturas que superan el límite teórico.
* El sistema puede ampliarse con sensores adicionales como pH o humedad ambiental avanzada.
* Código y app están preparados para recibir comandos y adaptarse a futuras funcionalidades.

---

## 👥 Autores

Desarrollado por estudiantes con presupuesto reducido para un proyecto de telecomunicaciones.

#include <LiquidCrystal.h>
#include <ArrayListAB.h>
#include <Servo.h>

#include "ABlocks_DHT.h"
#include <SoftwareSerial.h>

double potenciometro;
double H0;
double ORDEN;
double servo_angulo;
double s_te_hu__C2_BA;
double s_te_hu__25;
double s_luz;
double s_hum_pre;
double s_hum;
double s_cal;
double h__40;
double t;
double h__20;
double H20;
double H40;
double h_40;
double h_20;
double h_0;
double rH40;
double rH20;
double rH0;
double rH_20;
double rH_40;
double DIAMETRO;
double ALTURA;
String s_MENSAJE;
boolean b_ELECCION;
boolean b_CONTROL;
boolean b_BUSY;
LiquidCrystal lcd(2,3,4,5,6,7);

ArrayListAB<double> listNum_Radios;
ArrayListAB<double> listNum_Sensores;
Servo servo_8;
DHT dht13(13,DHT11);
SoftwareSerial bt_serial(12,11);

double fnc_ultrasonic_distance(int _t, int _e){
	unsigned long dur=0;
	digitalWrite(_t, LOW);
	delayMicroseconds(5);
	digitalWrite(_t, HIGH);
	delayMicroseconds(10);
	digitalWrite(_t, LOW);
	dur = pulseIn(_e, HIGH, 18000);
	if(dur==0)return 999.0;
	return (dur/57);
}

void setup()
{
  	pinMode(1, OUTPUT);
	pinMode(0, OUTPUT);
	servo_8.attach(8);
	pinMode(A2, INPUT);
	pinMode(13, INPUT);
	pinMode(A3, INPUT);
	pinMode(A1, INPUT);
	pinMode(10, OUTPUT);
	pinMode(9, INPUT);

lcd.begin(16, 2);

	dht13.begin();
	pinMode(A0, INPUT);
bt_serial.begin(9600);

	digitalWrite(1, LOW);
	digitalWrite(0, LOW);
	H0 = 30;
	servo_angulo = 40;
	lcd.clear();
	delay(2000);
	lcd.setCursor(0, 0);
	lcd.print(String("INICIANDO..."));
	listNum_Radios.clear();
	listNum_Sensores.clear();
	s_MENSAJE = String("");
	b_ELECCION = false;
	ORDEN = 0;
	t = 0;
	b_BUSY = false;
	b_CONTROL = false;
	servo_8.write(servo_angulo);
	delay(1000);
	H20 = (H0 / cos(((((20 * 3.1416)) / 180))));
	H40 = (H0 / cos(((((40 * 3.1416)) / 180))));
	h_40 = 0;
	h_20 = 0;
	h_0 = 0;
	h__20 = 0;
	h__40 = 0;
	rH40 = 0;
	rH20 = 0;
	rH0 = 0;
	rH_20 = 0;
	rH_40 = 0;
	DIAMETRO = 0;
	ALTURA = 0;
	delay(1000);
	lcd.setCursor(0, 0);
	lcd.print(String("   BT     LCD  "));
	lcd.setCursor(0, 1);
	lcd.print(String(" <---      --->"));

}


void loop()
{

  	if ((b_ELECCION == false)) {
  		potenciometro = map(analogRead(A2),0,1023,0,100);
  		delay(1000);
  		if ((!((((potenciometro - 20) < map(analogRead(A2),0,1023,0,100)) && ((potenciometro + 20) > map(analogRead(A2),0,1023,0,100)))))) {
  			if ((potenciometro > 50)) {
  				delay(1000);
  				if ((potenciometro > 50)) {
  					lcd.clear();
  					s_te_hu__C2_BA = dht13.readTemperature();
  					s_te_hu__25 = dht13.readHumidity();
  					s_luz = (analogRead(A0) / 10);
  					s_hum_pre = map(analogRead(A3),0,1023,0,100);
  					s_cal = map(analogRead(A1),0,1023,0,100);
  					if ((s_hum_pre != 99)) {
  						s_hum = s_hum_pre;
  					}
  					else {
  						s_hum = 0;
  					}

  					delay(500);
  					lcd.setCursor(0, 0);
  					lcd.print(String("HA: "));
  					lcd.setCursor(4, 0);
  					lcd.print(s_te_hu__25);
  					lcd.setCursor(6, 0);
  					lcd.print(String("%"));
  					lcd.setCursor(7, 0);
  					lcd.print(String("  TA: "));
  					lcd.setCursor(13, 0);
  					lcd.print(s_te_hu__C2_BA);
  					lcd.setCursor(15, 0);
  					lcd.print(String("C"));
  					lcd.setCursor(0, 1);
  					lcd.print(String("HT: "));
  					lcd.setCursor(4, 1);
  					lcd.print(s_hum);
  					lcd.setCursor(6, 1);
  					lcd.print(String("%"));
  					lcd.setCursor(7, 1);
  					lcd.print(String("  LA: "));
  					if ((s_luz >= 900)) {
  						lcd.setCursor(13, 1);
  						lcd.print(String("SOL"));
  						delay(1000);
  					}
  					else {
  						lcd.setCursor(13, 1);
  						lcd.print(s_luz);
  						lcd.setCursor(15, 1);
  						lcd.print(String("%"));
  						delay(1000);
  					}

  				}
  				else {
  					b_ELECCION = false;
  				}

  			}
  			else {
  				delay(1000);
  				if ((potenciometro <= 50)) {
  					digitalWrite(1, HIGH);
  					delay(1000);
  					digitalWrite(1, LOW);
  					delay(1000);
  					lcd.clear();
  					lcd.setCursor(0, 0);
  					lcd.print(String("ESPERANDO BT..."));
  					lcd.setCursor(0, 1);
  					lcd.print(String("CLAVE: 1234"));
  					while (!((bt_serial.available()>0))) {
  						digitalWrite(0, HIGH);
  						delay(200);
  						digitalWrite(0, LOW);
  						delay(200);
  					}
  					while (!((b_CONTROL == true))) {
  						if ((bt_serial.available()>0)) {
  							b_CONTROL = true;
  							lcd.clear();
  							lcd.setCursor(0, 0);
  							lcd.print(String("CONECTADO      "));
  							delay(2000);
  						}

  					}
  					b_ELECCION = true;
  				}
  				else {
  					b_ELECCION = false;
  				}

  			}

  		}

  	}

  	if (((b_CONTROL == true) && (b_ELECCION == true))) {
  		ORDEN = bt_serial.read();
  		lcd.setCursor(15, 0);
  		lcd.print(ORDEN);
  		if ((b_BUSY != true)) {
  			if ((ORDEN == 6)) {
  				servo_angulo = 0;
  				b_BUSY = true;
  				lcd.clear();
  				lcd.setCursor(0, 1);
  				lcd.print(String("MIDIENDO..."));
  				delay(1000);
  				servo_8.write(servo_angulo);
  				delay(1000);
  				h__40 = fnc_ultrasonic_distance(10,9);
  				delay(1000);
  				servo_angulo = (servo_angulo + 20);
  				servo_8.write(servo_angulo);
  				delay(1000);
  				h__20 = fnc_ultrasonic_distance(10,9);
  				delay(1000);
  				servo_angulo = (servo_angulo + 20);
  				servo_8.write(servo_angulo);
  				delay(1000);
  				h_0 = fnc_ultrasonic_distance(10,9);
  				delay(1000);
  				servo_angulo = (servo_angulo + 20);
  				servo_8.write(servo_angulo);
  				delay(1000);
  				h_20 = fnc_ultrasonic_distance(10,9);
  				delay(1000);
  				servo_angulo = (servo_angulo + 20);
  				servo_8.write(servo_angulo);
  				delay(1000);
  				h_40 = fnc_ultrasonic_distance(10,9);
  				delay(1000);
  				if ((!((H40 < h__40)))) {
  					lcd.setCursor(0, 0);
  					lcd.print(h__40);
  					lcd.setCursor(4, 0);
  					lcd.print(String(" "));
  				}
  				else {
  					lcd.setCursor(0, 0);
  					lcd.print(String("N/A"));
  				}

  				if ((!((H20 < h__20)))) {
  					lcd.setCursor(5, 0);
  					lcd.print(h__20);
  					lcd.setCursor(9, 0);
  					lcd.print(String(" "));
  				}
  				else {
  					lcd.setCursor(5, 0);
  					lcd.print(String("N/A"));
  				}

  				if ((!((H0 < h_0)))) {
  					lcd.setCursor(10, 0);
  					lcd.print(h_0);
  					lcd.setCursor(14, 0);
  					lcd.print(String(" "));
  				}
  				else {
  					lcd.setCursor(10, 0);
  					lcd.print(String("N/A"));
  				}

  				lcd.setCursor(0, 1);
  				lcd.print(String("        "));
  				if ((!((H20 < h_20)))) {
  					lcd.setCursor(0, 1);
  					lcd.print(h_20);
  					lcd.setCursor(4, 1);
  					lcd.print(String(" "));
  				}
  				else {
  					lcd.setCursor(0, 1);
  					lcd.print(String("N/A"));
  				}

  				if ((!((H40 < h_40)))) {
  					lcd.setCursor(5, 1);
  					lcd.print(h_40);
  					lcd.setCursor(9, 1);
  					lcd.print(String(" "));
  				}
  				else {
  					lcd.setCursor(5, 1);
  					lcd.print(String("N/A"));
  				}

  				rH_40 = (((H40 - h__40)) * cos(((((40 * 3.1416)) / 180))));
  				rH_20 = (((H20 - h__20)) * cos(((((20 * 3.1416)) / 180))));
  				rH0 = (H0 - h_0);
  				rH20 = (((H20 - h_20)) * cos(((((20 * 3.1416)) / 180))));
  				rH40 = (((H40 - h_40)) * cos(((((40 * 3.1416)) / 180))));
  				if ((!((H40 < h__40)))) {
  					listNum_Radios.add(rH_40);
  				}
  				else {
  					listNum_Radios.add(0);
  				}

  				if ((!((H20 < h__20)))) {
  					listNum_Radios.add(rH_20);
  				}
  				else {
  					listNum_Radios.add(0);
  				}

  				if ((!((H0 < h_0)))) {
  					listNum_Radios.add(rH0);
  				}
  				else {
  					listNum_Radios.add(0);
  				}

  				if ((!((H20 < h_20)))) {
  					listNum_Radios.add(rH20);
  				}
  				else {
  					listNum_Radios.add(0);
  				}

  				if ((!((H40 < h_40)))) {
  					listNum_Radios.add(rH40);
  				}
  				else {
  					listNum_Radios.add(0);
  				}

  				DIAMETRO = ((listNum_Radios.maxim()) * 2);
  				b_BUSY = false;
  				if ((DIAMETRO != 0)) {
  					lcd.setCursor(10, 1);
  					lcd.print(DIAMETRO);
  					s_MENSAJE = String("2,")+String(DIAMETRO);
  					bt_serial.println(s_MENSAJE);
  					s_MENSAJE = String("");
  					listNum_Radios.clear();
  					delay(1000);
  				}
  				else {
  					lcd.setCursor(10, 1);
  					lcd.print(String("ERROR"));
  				}

  			}

  			s_te_hu__C2_BA = dht13.readTemperature();
  			s_te_hu__25 = dht13.readHumidity();
  			s_luz = (analogRead(A0) / 10);
  			s_hum_pre = map(analogRead(A3),0,1023,0,100);
  			s_cal = map(analogRead(A1),0,1023,0,100);
  			if ((s_hum_pre < 99)) {
  				s_hum = s_hum_pre;
  			}
  			else {
  				s_hum = 0;
  			}

  			delay(1000);
  		}
  		else {
  			lcd.clear();
  			lcd.setCursor(0, 0);
  			lcd.print(String("MIDIENDO..."));
  		}

  		if ((ORDEN == 7)) {
  			if ((b_BUSY != true)) {
  				s_MENSAJE = String("1,")+String(s_te_hu__25)+String(",")+String(s_te_hu__C2_BA)+String(",")+String(s_hum)+String(",")+String(s_luz)+String(",")+String(s_cal);
  				bt_serial.println(s_MENSAJE);
  				delay(1000);
  				s_MENSAJE = String("");
  			}

  		}

  		if ((ORDEN == 1)) {
  			if ((b_BUSY != true)) {
  				lcd.setCursor(0, 0);
  				lcd.print(String("CONECTADO      "));
  				lcd.setCursor(0, 1);
  				lcd.print(String("HUM.AMBIEN.: "));
  				lcd.setCursor(13, 1);
  				lcd.print(s_te_hu__25);
  				lcd.setCursor(15, 1);
  				lcd.print(String("%"));
  				delay(1000);
  			}

  		}

  		if ((ORDEN == 2)) {
  			if ((b_BUSY != true)) {
  				lcd.setCursor(0, 0);
  				lcd.print(String("CONECTADO      "));
  				lcd.setCursor(0, 1);
  				lcd.print(String("TEM.AMBIEN.: "));
  				lcd.setCursor(13, 1);
  				lcd.print(s_te_hu__C2_BA);
  				lcd.setCursor(15, 1);
  				lcd.print(String("C"));
  				delay(1000);
  			}

  		}

  		if ((ORDEN == 3)) {
  			if ((b_BUSY != true)) {
  				lcd.setCursor(0, 0);
  				lcd.print(String("CONECTADO      "));
  				lcd.setCursor(0, 1);
  				lcd.print(String("HUM.TIERRA:  "));
  				lcd.setCursor(13, 1);
  				lcd.print(s_hum);
  				lcd.setCursor(15, 1);
  				lcd.print(String("%"));
  				delay(1000);
  			}

  		}

  		if ((ORDEN == 4)) {
  			if ((b_BUSY != true)) {
  				lcd.setCursor(0, 0);
  				lcd.print(String("CONECTADO      "));
  				lcd.setCursor(0, 1);
  				lcd.print(String("LUZ AMBIEN.: "));
  				if ((s_luz >= 900)) {
  					lcd.setCursor(13, 1);
  					lcd.print(String("SOL"));
  					delay(1000);
  				}
  				else {
  					lcd.setCursor(13, 1);
  					lcd.print(s_luz);
  					lcd.setCursor(15, 1);
  					lcd.print(String("%"));
  					delay(1000);
  				}

  			}

  		}

  		if ((ORDEN == 5)) {
  			if ((b_BUSY != true)) {
  				lcd.setCursor(0, 0);
  				lcd.print(String("CONECTADO      "));
  				lcd.setCursor(0, 1);
  				lcd.print(String("CALIDAD AIRE: "));
  				lcd.setCursor(13, 1);
  				lcd.print(s_cal);
  				lcd.setCursor(15, 1);
  				lcd.print(String("%"));
  				delay(1000);
  			}

  		}

  	}

}
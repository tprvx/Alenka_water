#include <SD.h>          //библиотека для работы sd карты 
#include <SPI.h>         //библиотека шины SPI 
#include <OneWire.h>     //библиотека для работы i2c 
#include "PCF8574.h"     //библиотека работы микросхемы pcf8574
#include "RTClib.h"      //библиотека работы часов реального времени 
#include <GyverWDT.h>    //библиотека сторожевого таймера 
#include <EEPROM.h>
RTC_DS1307 rtc;                    // Часы
PCF8574 RELAY(0x20);               // Реле
//PCF8574 inout(0x24);               // I/O


void(*resetFunc) (void) = 0; // Функция перезагрузки

#define INIT_ADDR 1023  // номер резервной ячейки
#define INIT_KEY 50     // ключ первого запуска. 0-254, на выбор

OneWire ds(A0);      // ds18b20
#define latchPin A1  // latchPin  индикатора 
#define clockPin A2  // clockPin  индикатора
#define dataPin  A3  // dataPin   индикатора
#define startPin 2   // пин кнопки старт/стоп
OneWire iB(3);       // iBUTTON
#define led  4       // пин led кнопки
#define sE  5       // пин датчика ошибок
#define coinPin 6    // пин с монетоприемника
#define DV 7         //пин датчика напряжениия
#define fiat  8      // пин купюроприемника
#define PUMP  9      // пин насоса


String number = "" ;          // с SD номер телефона
String ID_m = "";            // с SD номер машины
float price;                  // с SD цена за литр
byte tw;
int  twater;          // с SD время наполнения 1 литра в мсек.
byte keybalans;                // с SD пополнение баланса с ключа в руб.
byte rezervwater;              // с SD резервный обьем воды в л.
byte timeFree;                 // с SD время между freeWater в сек.
byte volw;
byte lit19;
byte SF;
byte temprezervwater;
long  tiwater;

/////////////////////////
unsigned long //таймеры
timecash,
debounce, //антидребезг кнопки старт
timer1,   //таймер 1
timer2,   //таймер 1
timer3,   //таймер 1
timerstart,
timerFW,
t_SOS,      //таймер SOS
VBM,
resetTime,
t1,
t2
;
/////////////////////////

int  temperature;        // Глобальная переменная для хранения значение температуры с датчика DS18B20
byte A = 0;             //2 разряд индикатора
byte B = 0;             //1 разряд индикатора
int  balans;            //  баланс
byte ledB = 0;
byte leds = 0;

boolean writeSD;
boolean fsendSMS;
boolean READY;
boolean Start ;
boolean freeWater ;
boolean SR;
boolean DDV;

byte pump;
boolean heater;
boolean heater_SOS;
boolean gvozdik;
boolean statusSD;
boolean flag_start;

boolean Es;
byte rezerv;
byte e4;
byte e3;
byte e2;
byte e1;
int tempbalans;
int tempbalansEE;
int balansFIAT;
byte docash;
int  eeprom_SOS = 0;   //ячейка eeprom
int  eeprom_SD  = 1;
int  eeprom_TB  = 2;
int  eeprom_balans = 4;
int sensorValue;
byte iboneh;
float volumeWater;
byte say1;
byte say2;

int lit[]  = {  // массив цифр и символов для индикатора с общим катодом
  0b00000011, //цифра 0 0b00000011
  0b10011111, //цифра 1  0b10011111
  0b00100101, //цифра 2 0b00100101
  0b00001101, //цифра 3  0b00001101
  0b10011001, //цифра 4  0b10011001
  0b01001001, //цифра 5  0b01001001
  0b01000001, //цифра 6  0b01000001
  0b00011111, //цифра 7  0b00011111
  0b00000001, //цифра 8  0b00000001
  0b00001001, //цифра 9  0b00001001
  0b11111111,}; //цифра 10  0b00001001
int num[] = {
  0b11100011, //0 L
  0b11111101, //1 norm
  0b11111111, //2 off
  0b01111111, //3 full
  0b11101111, //4 low
  0b11100101, //5 c
  0b00110000, //6 p
  0b11111111,}; //7 offf

char* words[] = { " ", //0
                  "ERROR-", //1
                  "E1", //2
                  "E2", //3
                  "E3", //4
                  "E4", //5
                  "RESET", //6
                  "START ", //7
                  "OK", //8
                  "SD", //9
                  "ErrSD",}; //10

byte aaa[2][8] = {{0x01, 0x01, 0x98, 0xBD, 0x01, 0x00, 0x00, 0x24},    // Двухмерный массив известных ключей
  {0x01, 0x40, 0x91, 0xBD, 0x01, 0x00, 0x00, 0x95}
};   // Первое число - количество ключей, второе - количество байт в ключе
byte addr[8], k, m;                                                    // Обозначаем массив для чтения ключа из 8 байт

void setup() {
  Serial.begin(9600);
  pinMode(10, OUTPUT);
  SD.begin(10);
  startEEPROM();           //чтение флагов с EEPROM


  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin,  OUTPUT);
  RELAY.pinMode(P0, OUTPUT);       // P0, реле 0
  RELAY.digitalWrite(P0, 0);
  RELAY.pinMode(P1, OUTPUT);       // P1, реле 1
  RELAY.digitalWrite(P1, 0);
  RELAY.pinMode(P2, OUTPUT);       // P2, реле насоса
  RELAY.digitalWrite(P2, 0);
  RELAY.pinMode(P3, OUTPUT);       // P3, реле обогревателя
  RELAY.digitalWrite(P3, 0);
  RELAY.pinMode(P4, OUTPUT);       // P4, реле 4
  RELAY.digitalWrite(P4, 0);
  RELAY.pinMode(P5, OUTPUT);       // P5, реле клапана
  RELAY.digitalWrite(P5, 0);
  RELAY.pinMode(P6, OUTPUT);       // P6, реле монетоприемника &  кнопки
  

  pinMode(sE, INPUT);
  digitalWrite(sE, 1);


  pinMode(PUMP, OUTPUT);
  digitalWrite(PUMP, 0);

  pinMode(coinPin, INPUT);   //монетоприемник
  digitalWrite(coinPin, 1);

  pinMode(fiat, INPUT);      //купюроприемник
  digitalWrite(fiat, 1);

  pinMode(DV, INPUT);   //датчик напряжениия
  digitalWrite(DV, 0);
  pinMode(led, OUTPUT);       // led кнопки

  pinMode(startPin, INPUT);    // кнопка старт
  digitalWrite(startPin, 1);
  attachInterrupt(0, ss, RISING  );//FALLING RISING
  // Watchdog.enable(RESET_MODE, WDT_PRESCALER_512); // Режим сторжевого сброса , таймаут ~4с
  digitalWrite(led, 1);
  delay(500);
  digitalWrite(led, 0);
  tablo_off();

    if (! rtc.begin()) {
    abort();
  }
  
  if (!SD.begin(10)) {
    delay(1000);
    resetFunc();
  }

  READ_SD();
  setSD();   
  CUCH();

}

void loop() {
  
  if (pump == 1 && READY == 1)
  { cash();

  if(iboneh>=4)
  {iboneh=0;}
    t1 = (millis() - timerstart);
  }

  if (millis() - timer1 >= 2000 && READY == 0)            // обновление данных
  {
    leds = !leds;
    iBUTTON();
    what_time_is_it();
    wtemp();
    if(   e4==0){fanytime();}
    digitalWrite(PUMP, 0);
    RELAY.digitalWrite(P5, 0); //клапан включить
    RELAY.digitalWrite(P2, 0); //реле насоса включить
    timer1 = millis();
  }

if (millis() - timer3 >= 1000&& READY == 0  )                  // моргание
  {
    
  
    Es=digitalRead(sE);
   sensorE();
    timer3 = millis();
  }

  if (millis() - timer2 >= 500 && READY == 1 )                  // моргание
  {
    ledB = !ledB;
    timer2 = millis();
  }

  if(balans==0 && temprezervwater/price>rezervwater)
    {E4();}

  if (millis() - VBM > 1000 && (balans / price) + (temprezervwater / price) >= rezervwater && rezerv == 1)
  { delay(500);
    RELAY.digitalWrite(P6, 0);  //выключить монетоприемник
    
  }


  if (millis() - VBM > 300000  && pump == 0 && balans != 0 && READY == 1   ) // функция списания баланса после ожидания 300000
  {
    saleSMS();
    sd();
    while ( balans != 0)
    {
      balans--;
      tempbalans++;
      UOB();
    }
    digitalWrite(led, 0);
    pump = 0;
    flag_start = 0;
    timerFW = millis();
    freeWater = 0;
    tiwater = 0;
    timerstart = 0;
    tablo_off();
    READY = 0;
    GmMm();
  }

  if ( balans > 0 && pump == 0 && READY == 1  )
  {
    digitalWrite(led, ledB );
  }


  /////////////

  if (millis() - debounce > 50 && digitalRead(coinPin) == LOW)                 // реакция на монетоприемник
  {
    if(docash==1){
    pushstop();}
   
    READY = 1;
    balans ++;
    debounce = millis();
    VBM = millis();
  }

  if (digitalRead(fiat) == LOW )                 // реакция на купюроприемник
  {
    if(docash==1){
    pushstop();}
    delay(100);
    READY = 1;
    balansFIAT ++;
    debounce = millis();
    VBM = millis();
  }
  
  if (millis() - VBM == 200 && balansFIAT >= 1  )
  {
    UOFB();
    if(docash==1){
    pushstart();}
  }

  if (millis() - VBM == 200 && balans >= 1  )
  {
    UOB();
    if(docash==1){
    pushstart();}
  }

    if (balans >= 200 )
  {
    RELAY.digitalWrite(P6, 0);  //включить монетоприемник
  }
  
  if (balans == 0 && rezerv ==false )
  {
    RELAY.digitalWrite(P6, 1);  //включить монетоприемник
  }
  /////////////////////////////////////

  if ((millis() - timerFW) / 1000 > timeFree  ) //timeFree
  {
    freeWater = true;
    timerFW = millis();
  }

  if (freeWater == 1 && READY == 0)
  {
    digitalWrite(led, leds);
  }
  ///////////////////////////////////////

  if (flag_start == 1 && SR == 0 ) //
  {
    delay(50);
    zapusk();
  }

  if (flag_start == 1 && SR == 1 ) //
  {
    delay(50);
    servicemod();
  }

}


void ss()
{
  if (millis() - debounce > 200 && digitalRead(2))
  {
    pump = !pump;
    flag_start = 1;
    debounce = millis();
  }
}

void zapusk()
{
  COD();
  delay(50);
  CVBV();
  delay(50);
}

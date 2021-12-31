void DPZ()
{
  delay(1000);
  if (EEPROM.read(INIT_ADDR) != INIT_KEY)  // первый запуск
  { EEPROM.write(INIT_ADDR, INIT_KEY);    // записали ключ
    heater_SOS = false;
    statusSD = false;
    tempbalans=0;
    delay(100);
    EEPROM.update(eeprom_TB, tempbalansEE); //в eeprom втыкаем 0
    EEPROM.update(eeprom_SOS, heater_SOS);  //в eeprom втыкаем 0
    EEPROM.update(eeprom_SD, statusSD);   //в eeprom втыкаем 0
 }


   if (EEPROM.read(eeprom_TB) !=1 && statusSD == true)
  { say1 = 0;
    say2 = 10;
    tempbalans=EEPROM.read(eeprom_TB);
    delay(500);
    sd();
    
    delay(500);}
}

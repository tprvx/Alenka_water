void termostat()
{ 
  if (temperature <= 15 || temperature >= 2 && heater == false )        //терморегулятор
  {
    heater = true;
  }

  if (temperature > 15  && heater == true )         //терморегулятор
  { 
    heater = false;
    heater_SOS = false;                            // опускаем флаг помощи
    EEPROM.update(eeprom_SOS, heater_SOS);   //в eeprom втыкаем флаг
  }

  if (heater == true)
  {
    RELAY.digitalWrite(P3, 1);
  }
  else
  {
    RELAY.digitalWrite(P3, 0);
  }

  if (temperature < 0 && heater_SOS == false )         //если температура упала ниже нормы
  {
    heater_SOS = true;                             //поднимаем флаг помощи нагревателю
    EEPROM.update(eeprom_SOS, heater_SOS);   //в eeprom втыкаем флаг
    say1=1;
    say2=2;
    sendSMS();
  }
  
if ((millis() - t_SOS) / 600000 >= 1 &&  heater_SOS == true) //каждые 5 минут сообщать о заморозке
  { 
   CUCH();
  }  
}

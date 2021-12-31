void startEEPROM()
{
  EEPROM.get(eeprom_SD, statusSD);
  delay(100);
  EEPROM.get(eeprom_SOS, heater_SOS);
  DPZ();
}
void balansEEPROM()
{
  EEPROM.get(eeprom_SD, statusSD);
  delay(100);
  EEPROM.get(eeprom_SOS, heater_SOS);
  DPZ();
}

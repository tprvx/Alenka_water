void CUCH()
{
  if (heater_SOS == true)
  { 
    t_SOS = millis();
    say1 = 1;
    say2 = 2;
    RELAY.digitalWrite(P3, 0);
    delay(500);
    RELAY.digitalWrite(P3, 1);
    sendSMS();
  }

  if (heater_SOS == false && statusSD == false)
  {
    t_SOS = millis();
    say1 = 7;
    say2 = 8;
    sendSMS();
    Serial.println("frf");
    RELAY.digitalWrite(P6, 1);
    delay(100);
    say1 = 7;
    say2 = 8;
    resetSD();
  }

  if (statusSD == true)
  {
    say1 = 1;
    say2 = 9;
    sendSMS();
  }
}

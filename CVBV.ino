void CVBV()
{
  if (  flag_start  == 1 && balans == 0  && freeWater == 1 && SR == 0 && pump == 1 ) // функция бесплатной воды
  {
    digitalWrite(led, 1);
    RELAY.digitalWrite(P5, 1); //клапан включить
    //RELAY.digitalWrite(P2, 1); //реле насоса включить
    flag_start = 0;
    //////////////
    delay(22000);
    /////////////
    RELAY.digitalWrite(P5, 0); //клапан включить
    RELAY.digitalWrite(P2, 0); //реле насоса включить
    digitalWrite(led, 0);
    pump = 0;
    freeWater = true;
    timerFW = millis();
    sdFree();
    freeWater = false;
  }
}

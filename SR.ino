void servicemod()
{ 
  if(flag_start == 1 && SR == 1)
  {
    pump = !pump;
    digitalWrite(PUMP,pump );
    RELAY.digitalWrite(P5, pump); //клапан включить
    RELAY.digitalWrite(P2, pump); //реле насоса включить
    flag_start == 0;
  }
  
  digitalWrite(latchPin, LOW);  // установка синхронизации "защелки" на LOW
  shiftOut(dataPin, clockPin, LSBFIRST, num[6] );  //2 передаем последовательно на вход данных
  shiftOut(dataPin, clockPin, LSBFIRST , num[5]); //1
  digitalWrite(latchPin, HIGH);
}

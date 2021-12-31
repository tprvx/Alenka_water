 void tablo()
 {
  digitalWrite(latchPin, LOW);   // установка синхронизации "защелки" на LOW
  shiftOut(dataPin, clockPin, LSBFIRST, lit[A] );  // передаем последовательно на вход данных
  shiftOut(dataPin, clockPin, LSBFIRST, lit[B]);  // передаем последовательно на вход данных
  digitalWrite(latchPin, HIGH);                    // установка синхронизации "защелки" на HIGH
  }
  
   void tablo_off()
 {
  digitalWrite(latchPin, LOW);                     // установка синхронизации "защелки" на LOW
  shiftOut(dataPin, clockPin, LSBFIRST, lit[10] );  // передаем последовательно на вход данных
  shiftOut(dataPin, clockPin, LSBFIRST ,lit[10]);  // передаем последовательно на вход данных
  digitalWrite(latchPin, HIGH);                   // установка синхронизации "защелки" на HIGH
  }
     void LO()
 {
  digitalWrite(latchPin, LOW);                     // установка синхронизации "защелки" на LOW
  shiftOut(dataPin, clockPin, LSBFIRST, lit[0] );  // передаем последовательно на вход данных
  shiftOut(dataPin, clockPin, LSBFIRST ,num[0]);  // передаем последовательно на вход данных
  digitalWrite(latchPin, HIGH);                   // установка синхронизации "защелки" на HIGH
  }

  void fanytime()
  {
    int x;
    if (price==3){x=3;} if ( price==1){x=1;}
    digitalWrite(latchPin, LOW);                     // установка синхронизации "защелки" на LOW
  shiftOut(dataPin, clockPin, LSBFIRST, num[6] );  // передаем последовательно на вход данных
  shiftOut(dataPin, clockPin, LSBFIRST ,lit[x]);  // передаем последовательно на вход данных
  digitalWrite(latchPin, HIGH);   }

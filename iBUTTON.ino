void iBUTTON() {
  m = 0;// Обнуляем указатель наличия ключа

  // Если устройство подключено - считываем
  if (iB.search(addr)) 
  { 
    if (aaa[0][0] == addr[0] &&
        aaa[0][1] == addr[1] && aaa[0][2] == addr[2] && aaa[0][3] == addr[3] && aaa[0][4] == addr[4]
        && aaa[0][5] == addr[5]
        && aaa[0][6] == addr[6] && aaa[0][7] == addr[7])
    {
      m = 1; // Если ключ есть + к балансу
    }
    iB.reset_search();
    // Проверяем значение указателя
    if (m == 1) 
    {
      balans += keybalans;
      say1 = 11;
      say2 = 0;
      UOB();
      READY = 1;
      delay(500);
      VBM = millis();
    }
    iB.reset_search();
  }

  // Если устройство подключено - считываем
  if (iB.search(addr)) 
  { 
    if (aaa[1][0] == addr[0] &&
        aaa[1][1] == addr[1] && aaa[1][2] == addr[2] && aaa[1][3] == addr[3] && aaa[1][4] == addr[4]
        && aaa[1][5] == addr[5]
        && aaa[1][6] == addr[6] && aaa[1][7] == addr[7]) 
    {
      m = 2; // Если ключ есть увеличиваем значение указателя
    }
    // Проверяем значение указателя
    if (m == 2) 
    {
      SR = !SR;
    }
    iB.reset_search();
  }
}

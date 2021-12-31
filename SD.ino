void READ_SD()
{
  File num = SD.open("number.txt");
  if (!num)
  {
    while (true);
  }
  else
  {
    while (num.available() && ((number += char(num.read()))));
    num.close();
  }

  File id = SD.open("id.txt");
  if (!id)
  {
    while (true); //Зависание!!!
  }
  else
  {
    while (id.available() &&                    // пока файл не кончился,
      ((ID_m += char(id.read()))));                // читаем байты и сразу конкатенируем в переменную String.
    id.close();
  }
}

void  setSD()
{
  File myFile = SD.open("setup.txt");              // открываем ранее созданный файл file.txt
  delay(500);
  if (!myFile) 
  {                                  // если файл file.txt не найден
    // выводим текст в монитор последовательного порта,
    while (true); //Зависание!!!                                // скетч не выполняется дальше.
  }
  else
  { // Если файл file.txt найден,
    char Bytes[4];                                 // создаём переменную для хранения байтов в формате char,
    int k = 0;                                      // создаём переменную-итератор,

    while (myFile.available() &&                    // пока файл не кончился,
           ((Bytes[k] = myFile.read()) != '\n' )) ++k;    // читаем байты дальше до следующего символа новой строки,
    tw = atoi(Bytes);                              // конвертируем в int,
    k = 0;

    while (myFile.available() &&                    // пока файл не кончился,
           ((Bytes[k] = myFile.read()) != '\n' )) ++k;    // читаем байты дальше до следующего символа новой строки,
    twater = atoi(Bytes);                              // конвертируем в int,
    k = 0;

    while (myFile.available() &&                    // пока файл не кончился,
           ((Bytes[k] = myFile.read()) != '\n')) ++k;    // читаем байты дальше до следующего символа новой строки,
    price = atoi(Bytes);                            // конвертируем в int,
    k = 0;

    while (myFile.available() &&                    // пока файл не кончился,
           ((Bytes[k] = myFile.read()) != '\n' )) ++k;    // читаем байты дальше до следующего символа новой строки,
    keybalans = atoi(Bytes);                              // конвертируем в int,
    k = 0;                                        // сбрасываем итератор,

    while (myFile.available() &&                    // пока файл не кончился,
           ((Bytes[k] = myFile.read()) != '\n')) ++k;    // читаем байты дальше до следующего символа новой строки,
    rezervwater = atoi(Bytes);                              // конвертируем в int,
    k = 0;

    while (myFile.available() &&                    // пока файл не кончился,
           ((Bytes[k] = myFile.read()) != '\n')) ++k;    // читаем байты дальше до следующего символа новой строки,
    timeFree = atoi(Bytes);                              // конвертируем в int,
    k = 0;

    delay(500);
    myFile.close();                                 // Закрываем файл.
  }
}

void sd()
{
  pump = 0;
  delay(50);
  DateTime time = rtc.now();
  File datalog = SD.open("log.txt", FILE_WRITE);
  if (datalog)
  {
    datalog.print(time.timestamp(DateTime::TIMESTAMP_DATE));
    datalog.print(" ");
    datalog.print(time.timestamp(DateTime::TIMESTAMP_TIME));
    datalog.print(",");
    datalog.print(tempbalans);
    datalog.print(",");
    datalog.print(tempbalans / price);
    datalog.print(",");
    datalog.print(words[say1]);
    datalog.println(words[say2]);
    datalog.close();
    delay(100);
    say1 = 0;
    say2 = 0;
  }
  else
  {
    tempbalansEE = tempbalans;
    statusSD = true;
    EEPROM.update(eeprom_SD, statusSD);   //в eeprom втыкаем флаг
    EEPROM.update(eeprom_TB, tempbalansEE);   //в eeprom втыкаем флаг
    delay(100);
    say1 = 1;
    say2 = 9;
    sendSMS();
    delay(500);
    resetFunc();
  }

  if (statusSD == true)
  {
    say1 = 1;
    say2 = 9;
    resetSD();

    statusSD = false;
    EEPROM.update(eeprom_SD, statusSD);   //в eeprom втыкаем флаг
  }
  tempbalans = 0;
  tempbalansEE = 0;
  EEPROM.update(eeprom_TB, tempbalansEE);   //в eeprom втыкаем флаг
  if (balans == 0)
  {
    tablo_off();
  }
}

void GmMm()
{
  DateTime time = rtc.now();
  File datalog = SD.open("log.txt", FILE_WRITE);
  if (datalog)
  {
    datalog.print(time.timestamp(DateTime::TIMESTAMP_DATE));
    datalog.print(" ");
    datalog.print(time.timestamp(DateTime::TIMESTAMP_TIME));
    datalog.print(",");
    datalog.print(tempbalans);
    datalog.print(",");
    datalog.println("0");
    datalog.close();
    delay(100);
  }
  else
  {
    delay(100);
  }
  tempbalans = 0;
}

void sdFree()
{
  DateTime time = rtc.now();
  File dataFile = SD.open("log.txt", FILE_WRITE);
  if (dataFile)
  {
    dataFile.print(time.timestamp(DateTime::TIMESTAMP_DATE));
    dataFile.print(" ");
    dataFile.print(time.timestamp(DateTime::TIMESTAMP_TIME));
    dataFile.print(",");
    dataFile.print("0");
    dataFile.print(",");
    delay(100);
    dataFile.println("0.5");
    dataFile.close();
    delay(100);
  }
  else
  {
    delay(100);
  }
}

void resetSD()
{
  DateTime time = rtc.now();
  File official = SD.open("logE.txt", FILE_WRITE);
  if (official)
  {
    official.print(time.timestamp(DateTime::TIMESTAMP_DATE));
    official.print(" ");
    official.print(time.timestamp(DateTime::TIMESTAMP_TIME));
    official.print(",");
    official.print(words[say1]);
    official.println(words[say2]);
    official.close();
  }
  say1 = 0;
  say1 = 0;
}

void E4()
{
  if (e4 == 0)
  {
    DateTime time = rtc.now();
    File official = SD.open("logE.txt", FILE_WRITE);
    if (official)
    {
      official.print(time.timestamp(DateTime::TIMESTAMP_DATE));
      official.print(" ");
      official.print(time.timestamp(DateTime::TIMESTAMP_TIME));
      official.print(", ");
      official.println("резервный обьем воды закончен");
      official.close();
    }
    RELAY.digitalWrite(P6, 0);  //включить монетоприемник
  }
  e4 = 1;
  LO();
}
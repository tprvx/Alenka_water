void sendSMS() //Центр отправки СМС
{
  wtemp();
  DateTime time = rtc.now();
  Serial.println("");
  Serial.println("AT");
  delay(500);
  Serial.println("AT+CMGF=1"); // Configuring TEXT mode
  delay(500);
  Serial.print("AT+CMGS=\"");
  Serial.print(number);
  Serial.println("\"");
  delay(500);
  Serial.print("id-");
  Serial.println(ID_m);
  Serial.print(words[say1]);
  Serial.println(words[say2]);
  delay(50);
  Serial.print("temperature ");
  Serial.println(temperature);
  Serial.print(time.timestamp(DateTime::TIMESTAMP_DATE));
  Serial.print("  ");
  Serial.println(time.timestamp(DateTime::TIMESTAMP_TIME));
  Serial.write(26); 
  say1=0;
  say2=0;
  }

  void saleSMS() //Центр отправки СМС
{
  wtemp();
  DateTime time = rtc.now();
  Serial.println("");
  Serial.println("AT");
  delay(500);
  Serial.println("AT+CMGF=1"); // Configuring TEXT mode
  delay(500);
  Serial.print("AT+CMGS=\"");
  Serial.print(number);
  Serial.println("\"");
  delay(500);
  Serial.print("id-");
  Serial.println(ID_m);
   Serial.print(tempbalans);
    Serial.println("rub. ");
    Serial.print(tempbalans / price);
  Serial.println("lit.");
  delay(50);
  Serial.print("temp. ");
  Serial.println(temperature);
  Serial.print("price ");
  Serial.println(price);
  Serial.print(time.timestamp(DateTime::TIMESTAMP_DATE));
  Serial.print("  ");
  Serial.println(time.timestamp(DateTime::TIMESTAMP_TIME));
  Serial.write(26); 
  say1=0;
  say2=0;
  }

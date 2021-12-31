void di()
{
  if (balans >= 57  )
  {
    volw = 19;
  }
  else {
    volw = 5;
  }
  tiwater=(twater / price)*balans;
  delay(50);
  


}
void COD() //ЦОД - центр обработки действий
{
  if (balans > 0  && pump == 1  && flag_start == 1)  // запуск при наличии денег
  {
    docash=1;
    di();
    digitalWrite(PUMP, pump );
    RELAY.digitalWrite(P5, pump); //клапан включить
    RELAY.digitalWrite(P2, pump); //реле насоса включить
    digitalWrite(led, 1);
    timecash = millis();
    timerstart=millis();
    freeWater = 0;
    flag_start = 0;
     
  }



  if (   balans == 0 && pump == 1 && flag_start == 0  ) //стоп по балансу millis()-timerstart >= tiwater
  {

    digitalWrite(PUMP, 0);
    RELAY.digitalWrite(P5, 0); //клапан включить
    RELAY.digitalWrite(P2, 0); //реле насоса включить
    saleSMS();
    sd();
    delay(100);
    lit19 = 0;
    volw = 0;
    freeWater = 0;
    READY = 0;
    flag_start = 0;
    digitalWrite(led, 0);
    tiwater = 0;
    //timerstart=0;
    timerFW = millis();
    pump = 0;
    docash=0;
    tablo_off();
 UOB();
  }

  if (balans == 0 && pump == 1 && flag_start == 1 && freeWater == 0) // без денег обнулить
  {
    digitalWrite(PUMP, 0);
    RELAY.digitalWrite(P5, 0); //клапан включить
    RELAY.digitalWrite(P2, 0); //реле насоса включить
    digitalWrite(led, 0);
    lit19 = 0;
    volw = 0;
    pump = 0;
    flag_start = 0;
    freeWater = 0;
    timerstart = 0;
    tiwater = 0;
    tablo_off();
    docash=0;
    timerFW = millis();
 UOB();
  }

  if ((lit19 / price) == volw && SR == 0 && balans > 0) //ФУНКЦИЯ СТОП ПО ОБЬЕМУ
  {
    
    digitalWrite(PUMP, 0);
    RELAY.digitalWrite(P5, 0); //клапан включить
    RELAY.digitalWrite(P2, 0); //реле насоса включить
    digitalWrite(led, 0);
    lit19 = 0;
    volw = 0;
    pump = 0;
    pump = 0;
    docash=0;
    pump = 0;
    VBM = millis();
  
    UOB();
  }


  if (balans > 0  && pump == 0  && flag_start == 1) // стоп по нажатию кнопки
  {
    if(iboneh>=3)
    {balans--;UOB();}
    iboneh++;
    digitalWrite(PUMP, 0 );
    RELAY.digitalWrite(P5, 0); //клапан включить
    RELAY.digitalWrite(P2, 0); //реле насоса включить
    timerFW = millis();
    t2=t1;
    freeWater = 0;
    tiwater = 0;
    lit19 = 0;
    volw = 0;
    pump = 0;
    docash=0;
    flag_start = 0;
    VBM = millis();
  
   
  }
}



void pushstop()
{
  if (balans > 0  && pump==1&&docash==1) // стоп по нажатию кнопки
  {
    digitalWrite(PUMP, 0 );
    RELAY.digitalWrite(P5, 0); //клапан включить
    RELAY.digitalWrite(P2, 0); //реле насоса включить
    timerFW = millis();
    freeWater = 0;
    pump = 0;
    flag_start = 0;
    VBM = millis();
    UOB();
  
  }
  
  }


  void pushstart()
  {
     if (balans > 0 && docash==1 )  // запуск при наличии денег
  {
    di();
    digitalWrite(PUMP, 1 );
    RELAY.digitalWrite(P5, 1); //клапан включить
    RELAY.digitalWrite(P2, 1); //реле насоса включить
    digitalWrite(led, 1);
    pump=1;
    freeWater = 0;
    
    timecash = millis();
    timerstart=millis();
  }
  }
    
    
   

void cash()   
{
 
  if ((millis()-timecash)*price >= twater && pump==1 && rezerv==0  )
  {
    balans--;
    tempbalans++;
    lit19++;
    UOB();
    COD();
    timecash = millis();
    
  }

  if ((millis()-timecash)*price >= twater && pump == 1 && rezerv == 1 )
  {
    balans--;
    lit19++;
    temprezervwater++;
    tempbalans++;
    UOB();
    COD();
    timecash = millis();
    
  }

}

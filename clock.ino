 
 void what_time_is_it()   // функция получения времени 
 {
DateTime time = rtc.now();

DateTime now = rtc.now();
if (now.hour() >=21 || now.hour() <=9  )
{
  price=1;
}
else
 
{
price=3;
}

 }
 
 

// функция получения времени
void what_time_is_it()   
{
	DateTime time = rtc.now();
	DateTime now = rtc.now();
	
	if (now.hour() >= 21 || now.hour() <= 9)
	{
		price = 1;
	}
	else
	{
		price = 3;
	}
}



void UOFB()
{
  if(balansFIAT == 1)
  {
    balans += 10;
  }

  if(balansFIAT == 2)
  {
    balans += 50;
  }
  if(balansFIAT == 3)
  {
    balans += 100;
  }
  if(balansFIAT == 4)
  {
    balans += 200;
  }
  balansFIAT = 0;
  UOB();
}

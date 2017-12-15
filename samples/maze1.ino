
//      Define-uri
/*        Senzori            */
#define SenzorFarDreapta      5
#define SenzorApropDreapta    4
#define SenzorCentruDreapta   3
#define SenzorCentruStanga    2
#define SenzorApropStanga     1
#define SenzorFarStanga       0

/*        Motoare            */
#define MotorStangaFata       2
#define MotorStangaSpate      4
#define MotorStangapwm        3
#define MotorDreaptaFata      6
#define MotorDreaptaSpate     7
#define MotorDreaptapwm       5

/*        Motoare            */
#define led 4

//    Int-uri
int SFDCitire;
int SADCitire;
int SCDCitire;
int SCSCitire;
int SASCitire;
int SFSCitire;

void setup() {
  /*    Setup Senzori Dreapta    */
  pinMode(SenzorFarDreapta, INPUT);
  pinMode(SenzorApropDreapta, INPUT);
  pinMode(SenzorCentruDreapta, INPUT);
  /*    Setup Senzori Stanga     */
  pinMode(SenzorFarStanga, INPUT);
  pinMode(SenzorApropStanga, INPUT);
  pinMode(SenzorCentruStanga, INPUT);
  /*    Setup Motoare Stanga     */
  pinMode(MotorStangaFata, OUTPUT);
  pinMode(MotorStangaSpate, OUTPUT);
  /*    Setup Motoare Dreapta    */
  pinMode(MotorDreaptaFata, OUTPUT);
  pinMode(MotorDreaptaSpate, OUTPUT);
  pinMode(led, OUTPUT);
  analogWrite(led, 50);
  delay(2000);
}

void loop() 
{
  if(SFSCitire < 450 && SFDCitire < 450 && (SCSCitire > 450 || SCDCitire > 450))
  {
    inainte(); 
  }
  else
  {
    cautalinie();
  }
}

void CitireSenzori()
{
  SFSCitire = analogRead(SenzorFarStanga);
  SASCitire = analogRead(SenzorApropStanga);
  SCSCitire = analogRead(SenzorCentruStanga);
  SFDCitire = analogRead(SenzorFarDreapta);
  SADCitire = analogRead(SenzorApropDreapta);
  SCDCitire = analogRead(SenzorCentruDreapta);
}

void cautalinie()
{
  if(SFSCitire > 450 && SFDCitire > 450)
  {
    analogWrite(MotorStangaFata, 50);
    analogWrite(MotorStangaSpate, 0);
    analogWrite(MotorDreaptaFata, 50);
    analogWrite(MotorDreaptaSpate, 0);
    delay(125);
    CitireSenzori();

    if(SFSCitire > 450 || SFDCitire > 450)
    {
       opreste();
    }
    if(SFSCitire < 450 && SFDCitire < 450)
    {
       RotesteStanga();
    }
  }
  if(SFSCitire > 450)
  {
     analogWrite(MotorStangaFata, 50);
     analogWrite(MotorStangaSpate, 0);
     analogWrite(MotorDreaptaFata, 50);
     analogWrite(MotorDreaptaSpate, 0);
     delay(125);
     CitireSenzori();
     
     if(SFSCitire < 450 && SFDCitire < 450)
     {
        RotesteStanga();
     }
     else
     {
        opreste();
     }
  }
  if(SFDCitire > 450)
  {
     analogWrite(MotorStangaFata, 50);
     analogWrite(MotorStangaSpate, 0);
     analogWrite(MotorDreaptaFata, 50);
     analogWrite(MotorDreaptaSpate, 0);
     delay(10);
     CitireSenzori();
     
     if(SFSCitire > 450)
     {
        delay(95);
        CitireSenzori();
        if(SFDCitire > 450 && SFSCitire > 450)
        {
          opreste();
        }
        else
        {
          RotesteStanga();
          return;
        }
     }
  delay(95);
  CitireSenzori();
  if(SFSCitire < 450 && SFDCitire < 450 && SCSCitire < 450 && SCDCitire < 450)
  {
     RotesteDreapta();
     return;
  }
  }
  CitireSenzori();
  if(SFSCitire < 450 && SCSCitire < 450 && SCDCitire < 450
  && SFDCitire < 450 && SASCitire < 450 && SADCitire < 450)
  {
    intoarce();
  }
}

// Functia de oprire a robotului in momentul in care toti senzorii ajung pe linia neagra 
void opreste()
{
  analogWrite(MotorStangaFata, 0);
  analogWrite(MotorStangaSpate, 0);
  analogWrite(MotorDreaptaFata, 0);
  analogWrite(MotorDreaptaSpate, 0);
  while(analogRead(SenzorFarStanga)>450)
  {
    analogWrite(led, 0);
    delay(125);
    analogWrite(led, 50);
    delay(125);
  }
}

// Functia de rotire spre stanga a robotului in momentul in care senzorii citesc linia neagra catre stanga
void RotesteStanga()
{
  analogWrite(MotorStangaFata, 0);
  analogWrite(MotorStangaSpate, 70);
  analogWrite(MotorDreaptaFata, 70);
  analogWrite(MotorDreaptaSpate, 0);
  delay(235);//1075
}

// Functia de rotire spre dreapta a robotului in momentul in care senzorii citesc linia neagra catre dreapta
void RotesteDreapta()
{
  analogWrite(MotorStangaFata, 70);
  analogWrite(MotorStangaSpate, 0);
  analogWrite(MotorDreaptaFata, 0);
  analogWrite(MotorDreaptaSpate, 700);
  delay(235);
}

// Functia de inaintare a robotului in momentul in care cei doi senzori din centru sunt pe linia neagra
void inainte()
{
  if(analogRead(SenzorCentruStanga) < 450)
  {
    analogWrite(MotorStangaFata, 50);
    analogWrite(MotorStangaSpate, 0);
    analogWrite(MotorDreaptaFata, 50);
    analogWrite(MotorDreaptaSpate, 0);
    delay(1);

    analogWrite(MotorStangaFata, 50);
    analogWrite(MotorStangaSpate, 0);
    analogWrite(MotorDreaptaFata, 0);
    analogWrite(MotorDreaptaSpate, 0);
    delay(5);
    return;
  }
  if(analogRead(SenzorCentruDreapta) < 450)
  {
    analogWrite(MotorStangaFata, 50);
    analogWrite(MotorStangaSpate, 0);
    analogWrite(MotorDreaptaFata, 50);
    analogWrite(MotorDreaptaSpate, 0);
    delay(1);

    analogWrite(MotorStangaFata, 0);
    analogWrite(MotorStangaSpate, 0);
    analogWrite(MotorDreaptaFata, 50);
    analogWrite(MotorDreaptaSpate, 0);

    delay(5);
    return;
  }
  analogWrite(MotorStangaFata, 50);
  analogWrite(MotorStangaSpate, 0);
  analogWrite(MotorDreaptaFata, 50);
  analogWrite(MotorDreaptaSpate, 0);

  delay(4);
  analogWrite(MotorStangaFata, 0);
  analogWrite(MotorStangaSpate, 0);
  analogWrite(MotorDreaptaFata, 0);
  analogWrite(MotorDreaptaSpate, 0);
  delay(1);
}
// Functia de intoarcere a robotului in momentul in care senzorii nu "citesc" linia neagra
void intoarce()
{
  analogWrite(MotorStangaFata, 50);
    analogWrite(MotorStangaSpate, 0);
    analogWrite(MotorDreaptaFata, 50);
    analogWrite(MotorDreaptaSpate, 0);
    delay(100);
    
  analogWrite(MotorStangaFata, 0);
  analogWrite(MotorStangaSpate, 50);
  analogWrite(MotorDreaptaFata, 50);
  analogWrite(MotorDreaptaSpate, 0);
  delay(450);
}

  
int bd=0,bs=0,bd90=0, bs90=0,vl, comanda=0;


int sf=2,ss=4,ps=3;//stanga fata, stanga spate, pwm stanga
int df=7,ds=6,pd=5;
int p,pw=100; //puterea
int dist=250;//distanta senzor fata
void setup() {                
  
  pinMode(ss, OUTPUT);     
  pinMode(sf, OUTPUT);     
  pinMode(ds, OUTPUT);     
  pinMode(df, OUTPUT);  
  pinMode(ps, OUTPUT);     
  pinMode(pd, OUTPUT); 
  pinMode(13,OUTPUT);
 pinMode(10,INPUT);
 pinMode(11,INPUT);
 pinMode(12,INPUT);
 pinMode(16,INPUT);//buton sub lama
 digitalWrite(12,1);
digitalWrite(11,1);


 while (bd==0 && bs==0 && bd90==0 && bs90==0)
{
  if (digitalRead(12)==0) bs=1;
  if (digitalRead(11)==0) bd=1;
}
 digitalWrite(13,1);
  
//while(comanda==0)  if (digitalRead(12)==1) comanda=1;
delay (5000);

while (analogRead (2)>200){p=100;fata();}
p=255; inapoi(); delay (400);


if (bd90==1){p=200;dreapta90();delay(160);bd=1;}
if (bs90==1){p=200;stanga90();delay(160);bs=1;}
}

void loop() {
//if(digitalRead(12)==0)reset();
vl=0;

if (analogRead(0)>150 && analogRead(1)>150)  {vl=1;p=255;fata();}
if (analogRead(0)>150 && analogRead(1)<150)  { bs=1;bd=0;}
if (analogRead(0)<150 && analogRead(1)>150)  { bs=0;bd=1;}

      
      if (bd==1 && bs==0 && vl==0){p=150;dreapta();}
      if (bs==1 && bd==0 && vl==0){p=150;stanga();}
    
      
//if (digitalRead(8)==0 && digitalRead(9)==0)  {bs=0;bd=0; p=255;fata();}
}

void fata()
{
digitalWrite(sf,1);
digitalWrite(df,1);
digitalWrite(ss,0);
digitalWrite(ds,0);
analogWrite(ps,p);
analogWrite(pd,p);
}
void inapoi()
{
digitalWrite(sf,0);
digitalWrite(df,0);
digitalWrite(ss,1);
digitalWrite(ds,1);
analogWrite(ps,p);
analogWrite(pd,p);
}
void reset()
{
digitalWrite(sf,0);
digitalWrite(df,0);
digitalWrite(ss,0);
digitalWrite(ds,0);
analogWrite(ps,0);
analogWrite(pd,0);
while(1);
}
void stanga()
{
digitalWrite(sf,1);
digitalWrite(df,1);
digitalWrite(ss,0);
digitalWrite(ds,0);
analogWrite(ps,p/6);
analogWrite(pd,p);
}

void stanga90()
{
digitalWrite(sf,0);
digitalWrite(df,1);
digitalWrite(ss,1);
digitalWrite(ds,0);
analogWrite(ps,p);
analogWrite(pd,p);
}

void dreapta()
{
digitalWrite(sf,1);
digitalWrite(df,1);
digitalWrite(ss,0);
digitalWrite(ds,0);
analogWrite(ps,p);
analogWrite(pd,p/6 );
}

void dreapta90()
{
digitalWrite(sf,1);
digitalWrite(df,0);
digitalWrite(ss,0);
digitalWrite(ds,1);
analogWrite(ps,p);
analogWrite(pd,p);
}



const int Led1 = 13;      // the number of the LED pin
const int Led2 = 12;      // the number of the LED pin
const int Led3 = 11;      // the number of the LED pin
const int Led4 = 10;      // the number of the LED pin

const int Sensor1 = A0;
const int Sensor2 = A1;
const int Sensor3 = A2;
const int Sensor4 = A3;
const int Sensor5 = A4;
const int Sersor6 = A5;

const int MotorLeftA1 = D2;      // the number of the LED pin
const int MotorLeftA2 = D4;      // the number of the LED pin
const int MotorLeftPWM = D3;      // the number of the LED pin

const int MotorRightB1 = D6;      // the number of the LED pin
const int MotorRightB2 = D7;      // the number of the LED pin
const int MotorRightPWM = D5;      // the number of the LED pin

const int Button = 11;      // the number of the LED pin

const int POT = A4;      // the number of the LED pin

int SensorVal[4];
int SensorCoef[] = {-8,-2,2,8};
long time_ = 0;
int position_current;
int position_last;

double KP = 12;
double KD = 3;
int speed_motor_ref = 130; //maxim 255
int speed_motor;

void SensorRead()
{
  short POT_value;
  POT_value = analogRead(POT);
  if (analogRead(Sensor1) > POT_value) SensorVal[0] = 1; else SensorVal[0] = 0;
  if (analogRead(Sensor2) > POT_value) SensorVal[1] = 1; else SensorVal[1] = 0;
  if (analogRead(Sensor3) > POT_value) SensorVal[2] = 1; else SensorVal[2] = 0;
  if (analogRead(Sensor4) > POT_value) SensorVal[3] = 1; else SensorVal[3] = 0;
  
  if(SensorVal[0] == 0)digitalWrite(Led1, LOW);else digitalWrite(Led1, HIGH);
  if(SensorVal[1] == 0)digitalWrite(Led2, LOW);else digitalWrite(Led2, HIGH);
  if(SensorVal[2] == 0)digitalWrite(Led3, LOW);else digitalWrite(Led3, HIGH);
  if(SensorVal[3] == 0)digitalWrite(Led4, LOW);else digitalWrite(Led4, HIGH);
}

void MotorControl(boolean SenseLeft, boolean SenseRight, short Left, short Right)
{
  if (SenseLeft == true)
  {
  digitalWrite(MotorLeftA1, LOW);
  digitalWrite(MotorLeftA2, HIGH);      
  }
  else
  {
  digitalWrite(MotorLeftA1, HIGH);
  digitalWrite(MotorLeftA2, LOW);    
  }

  if (SenseRight == true)
  {
  digitalWrite(MotorRightB1, HIGH);
  digitalWrite(MotorRightB2, LOW);      
  }
  else
  {
  digitalWrite(MotorRightB1, LOW);
  digitalWrite(MotorRightB2, HIGH);    
  }  
  
 analogWrite(MotorLeftPWM,Left);
 analogWrite(MotorRightPWM,Right);
}



void setup() {
  // put your setup code here, to run once:
  pinMode(Led1, OUTPUT);
  pinMode(Led2, OUTPUT);
  pinMode(Led3, OUTPUT);
  pinMode(Led4, OUTPUT);
 // pinMode(DBGLed1, OUTPUT);
 // pinMode(DBGLed2, OUTPUT);
  pinMode(Button, INPUT);

  pinMode(MotorLeftA1, OUTPUT);
  pinMode(MotorLeftA2, OUTPUT);
  pinMode(MotorRightB1, OUTPUT);
  pinMode(MotorRightB2, OUTPUT);
  pinMode(MotorLeftPWM, OUTPUT);
  pinMode(MotorRightPWM, OUTPUT);

  digitalWrite(Led1, LOW);
  digitalWrite(Led2, LOW);
  digitalWrite(Led3, LOW);
  digitalWrite(Led4, LOW);
  digitalWrite(Button, HIGH);
}

void loop() {
// put your main code here, to run repeatedly:

//MotorControl(true,true,50,50);
if (millis() - time_ > 20)
{
  time_ = millis();
  SensorRead();
  position_current = (SensorCoef[0]*SensorVal[0] + SensorCoef[1]*SensorVal[1] + SensorCoef[2]*SensorVal[2] + SensorCoef[3]*SensorVal[3])/ (SensorVal[0]+SensorVal[1]+SensorVal[2]+SensorVal[3]);
  speed_motor = KP*position_current + KD*(position_current - position_last);
  //limits!!!!
  position_last = position_current;
  MotorControl(true,true,speed_motor_ref - speed_motor ,speed_motor_ref + speed_motor);
}

}

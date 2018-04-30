#include <PID_v1.h>
#include <LiquidCrystal.h> // include the library code:

float tempC;
float tempF;
int pwmfan1 = 6;
int pwmfan2 = 9;

////////////////Enter required Temperature/////////////////////
//////////////////////////////////////////////////////
float setTemp=40;
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////



// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


int pwmbulb = 10;
double Setpoint, Input, Output,Output1;
double Kp=150, Ki=1, Kd=0;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);
PID myPID1(&Input, &Output1, &Setpoint, Kp, Ki, Kd, DIRECT);



int reading;
float referenceVoltage;

int tempPin = 1; //Analog pin connected to LM35


int x=0;
int t=0;
int flag=0;
int tl=20;
int th=80;
//int setTemp=(tl+th)/2;

int logpin=A2;
char rem = 0;
String tmp;
int tolerance=0;

void setup()
{
 Input = analogRead(tempPin);

 Serial.begin(9600);
 analogReference(INTERNAL);
 referenceVoltage = 1.1; 
   pinMode(pwmfan1, OUTPUT);
   pinMode(pwmfan2, OUTPUT);
  pinMode(pwmbulb, OUTPUT);
  pinMode(logpin, INPUT);
  
  Serial.begin(9600); 
   Setpoint = (setTemp)*(1023/110);
    myPID.SetMode(AUTOMATIC);
    myPID1.SetMode(AUTOMATIC);
    
    lcd.begin(16, 2);
    lcd.setCursor(0,0);
    lcd.print("Set Temp: ");
    lcd.setCursor(0,1);
    lcd.print("Cur Temp: ");
  // Print a message to the LCD.
}

void loop()
{
  if (Serial.available()>0)
  {
    rem=Serial.read();
    if(rem=='t')
    {
      Serial.println("Enter required temperature: ");
     setTemp=0;
     while(setTemp==0)
     {
      tmp=Serial.readString();
      setTemp=tmp.toInt();

     }
           Serial.print("setTemp: ");
      Serial.print(setTemp);
      
       lcd.setCursor(10,0);
      lcd.print(setTemp);
      delay(100);
    }
  }
  Input=analogRead(tempPin);
  float tp=Input*(1.1*100)/1023;
  //float tp = (5*Input*100/1024);
  Serial.println(tp); // Current Temperature
  lcd.setCursor(10,1);
  lcd.print(tp);
  lcd.println("C");
  lcd.setCursor(10,0);
  lcd.print(setTemp);
  lcd.print("C");
  myPID.Compute();
  myPID1.Compute();
  analogWrite(pwmfan1,Output1);
  analogWrite(pwmfan2,Output1);
  analogWrite(pwmbulb, Output);
  delay(200);
}
  
  


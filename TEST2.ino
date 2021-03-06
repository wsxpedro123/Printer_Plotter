/*
    Nelson used the website bellow to download the information
    18/03/2020
    Source & info at: www.HomoFaciens.de/technics-base-circuits-encoder-disc_en_navion.htm
    Nelson added that the rotarty encoder has 1440 CPR.
    Interrupt information
    0 on pin 2
    1 on pin 3
    The encoder has 2880 counts per revolution.
*/

volatile long setPoint = 0;
volatile long count = 0;
long tolerance = 3;

#define encoderI 2 // Interrput signal but really does not matter
#define encoderQ 4 // quadrature signel but really does not 
#define XAxisPulse 3 // This pin is to be used to move the servo one click
#define XAxisDirection 5 // This pin will be used to state the direction
#define MOTOR_FWD 7
#define MOTOR_REV 8

void handleEncoder()
{
  if(digitalRead(encoderI) == digitalRead(encoderQ))
  {
    count++;
  }
  else
  {
    count--;
  }
}

void handleXAxisCount()
{
  if(digitalRead(XAxisDirection) == digitalRead(XAxisPulse))
  {
    setPoint++;
  }
  else
  {
    setPoint--;
  }
}

void setup()
{
  pinMode(MOTOR_FWD, OUTPUT);
  pinMode(MOTOR_REV, OUTPUT);
  pinMode(encoderI, INPUT_PULLUP);
  pinMode(encoderQ, INPUT_PULLUP);
  pinMode(XAxisPulse, INPUT_PULLUP);
  pinMode(XAxisDirection, INPUT_PULLUP);
  attachInterrupt(0,handleEncoder, CHANGE);
  attachInterrupt(1,handleXAxisCount, CHANGE);
  Serial.begin(9600);
}

void loop()
{
    if ((setPoint) >= (count))
    {
      Serial.println("i am the great than");
      if ((setPoint - count) >= (tolerance))
      {
        Serial.println("i am A");
        digitalWrite(MOTOR_REV, LOW);
        digitalWrite(MOTOR_FWD, HIGH);
      }
      if ((setPoint - count) <= (tolerance))
      {
        Serial.println("i am B");
        digitalWrite(MOTOR_REV, LOW);
        digitalWrite(MOTOR_FWD, LOW);
      }
    }
    if ((setPoint) <= (count))
    {
      Serial.println("i am the less than");
      if ((count - setPoint) >= (tolerance))
      {
        Serial.println("i am C");
        digitalWrite(MOTOR_REV, HIGH);
        digitalWrite(MOTOR_FWD, LOW);
      }
      if ((count - setPoint) <= (tolerance))
      {
        Serial.println("i am D");
        digitalWrite(MOTOR_REV, LOW);
        digitalWrite(MOTOR_FWD, LOW);
      }
    }
    if ((setPoint) == (count))
    {
      Serial.println("i am the zero");
      digitalWrite(MOTOR_REV, LOW);
      digitalWrite(MOTOR_FWD, LOW);
    }
    Serial.print("Setpoint: ");
    Serial.println(setPoint);
    Serial.print("Count: ");
    Serial.println(count);
}

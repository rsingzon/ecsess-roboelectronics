// Author: Dirk, Josh
// Date: 2014-11-05
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int LED = 13;
// PWM pin
int pwm = 10;
// Sensors
int IR0 = 0;
int IR1 = 1;
int IR2 = 2;
int IR3 = 3;
int IR4 = 4;
int IR5 = 5;
int IR6 = 6;
int IR7 = 7;
// Limit Switches
int limit1 = 8;
int limit2 = 9;
// Gate Motor
int motorLeft = 11;
int motorRight = 12;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(LED, OUTPUT);
  pinMode(IR0, INPUT);
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);
  pinMode(IR4, INPUT);
  pinMode(IR5, INPUT);
  pinMode(IR6, INPUT);
  pinMode(IR7, INPUT);
  pinMode(limit1, INPUT);
  pinMode(limit2, INPUT);
  pinMode(motorLeft, OUTPUT);
  pinMode(motorRight, OUTPUT);
  Serial.begin(9600);
  analogWrite(pwm, 64);
}

// the loop routine runs over and over again forever:
void loop() {

if(digitalRead(IR0))
  {
     digitalWrite(LED, HIGH); 
  }
  else
  {
     digitalWrite(LED, LOW);
     openGate();
  }
}

void openGate()
{
    //Turn motor in the open direction
    digitalWrite(motorLeft, LOW);
    digitalWrite(motorRight, HIGH);

    //check that open switch isn't pressed
    while(!digitalRead(limit1));
    //turn off motor
    digitalWrite(motorLeft, LOW);
    digitalWrite(motorRight, LOW);

    //Wait before closing gate
    for(int i = 0; i < 10; i++)
    {
        delay(1000);
    }

    //Turn motor in the close direction
    digitalWrite(motorLeft, HIGH);
    digitalWrite(motorRight, LOW);

    //Check that the close switch isn't pressed
    while(!digitalRead(limit2));
    //turn off motor
    digitalWrite(motorLeft, LOW);
    digitalWrite(motorRight, LOW);

    return;
}

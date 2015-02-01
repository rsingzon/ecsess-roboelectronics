
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;
int values[8];
int expectedValues[8] = {0,1,0,1,0,1,0,1};
// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
  pinMode(2, INPUT);  
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
if(digitalRead(2))
  {
     digitalWrite(led, HIGH); 
  }
  else
  {
     digitalWrite(led, LOW); 
  }  
  /*int foundPattern = 0;
  readFunction();
  for(int i =0; i<8; i++)
  {
    if(values[i] != expectedValues[i])
    {
      foundPattern = 0;
       break; 
    }
    else
    {
     foundPattern = 1; 
    }
  }
  if(foundPattern)
  {
     digitalWrite(led, HIGH);
  }
  else
  {
    digitalWrite(led, LOW);
  }
  Serial.println(foundPattern);*/
}

void readFunction()
{
    int firstValue = readBit(2);
    delayMicroseconds(250);
    int secondValue = readBit(2);

    if(firstValue ==1 && secondValue == 1)
    {
      for(int i = 0; i <8; i++)
      {
         values[i] = readBit(2);
         delayMicroseconds(250);
      }
    }
}

int readBit(int port)
{

  if(digitalRead(port) == 1)
  {
    return 0;
  }  
  if(digitalRead(port) == 0)
  {
   return 1; 
  }
  
}



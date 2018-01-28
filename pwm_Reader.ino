

volatile unsigned long timer[6];
volatile byte last_channel[5]={0,0,0,0,0};
volatile int input[5]={1500,1500,1500,1500,1500};

void setup()
{
  PCICR |= (1 << PCIE0);   
  PCMSK0 |= (1 << PCINT0); //8
  PCMSK0 |= (1 << PCINT1); //9
  PCMSK0 |= (1 << PCINT2); //10
  PCMSK0 |= (1 << PCINT3); //11
  PCMSK0 |= (1 << PCINT4); //12
  Serial.begin(38400);
  //steer.attach(10);
}

ISR(PCINT0_vect)
{
  timer[0]=micros();
  //channel 1 ----
  
  if(last_channel[0]==0&& PINB & B00000001) //makes sure that the first pin was initially low and is now high
  {                                         //PINB & B00000001 is equivalent to digitalRead but faster
    last_channel[0]=1;
    timer[1]=timer[0];           
  }
  else if(last_channel[0]==1 && !(PINB & B00000001))
  {
    last_channel[0]=0;
    input[0]=timer[0]-timer[1];
  }

  //channel 2---                  
  if(last_channel[1]==0 && PINB & B00000010) //makes sure that the first pin was initially low and is now high
  {                                         //PINB & B00000001 is equivalent to digitalRead but faster
    last_channel[1]=1;
    timer[2]=timer[0];          
  }
  else if(last_channel[1]==1 && !(PINB & B00000010))
  {
    last_channel[1]=0;
    input[1]=timer[0]-timer[2];
  }
  
  //channel 3-- 
  if(last_channel[2]==0&& PINB & B00000100) //makes sure that the first pin was initially low and is now high
  {                                         //PINB & B00000001 is equivalent to digitalRead but faster
    last_channel[2]=1;
    timer[3]=timer[0];          
  }
  else if(last_channel[2]==1 && !(PINB & B00000100))
  {
    last_channel[2]=0;
    input[2]=timer[0]-timer[3];
  }
  //channel 4--
   if(last_channel[3]==0&& PINB & B00001000) //makes sure that the first pin was initially low and is now high
  {                                         //PINB & B00000001 is equivalent to digitalRead but faster
    last_channel[3]=1;
    timer[4]=timer[0];          
  }
  else if(last_channel[3]==1 && !(PINB & B00001000))
  {
    last_channel[3]=0;
    input[3]=timer[0]-timer[4];
  }

  //channel 5--
   if(last_channel[4]==0&& PINB & B00010000) //makes sure that the first pin was initially low and is now high
  {                                         //PINB & B00000001 is equivalent to digitalRead but faster
    last_channel[4]=1;
    timer[5]=timer[0];          
  }
  else if(last_channel[4]==1 && !(PINB & B00010000))
  {
    last_channel[4]=0;
    input[4]=timer[0]-timer[5];
  }
}

void serialprint()
{
  Serial.print(input[0]);Serial.print("||");
  Serial.print(input[1]);Serial.print("||");
  Serial.print(input[2]);Serial.print("||");
  Serial.print(input[3]);Serial.print("||");
  Serial.print(input[4]);Serial.print("||");
  Serial.println();
}
  
void loop()
{
  serialprint();
}


const int LDR_Pin=A0; // pin ldr1
const int ldrl=A1; // pin ldr2
const int ldrr=A2; // pin ldr3
const int Red_Led_Pin=2;
const int Green_Led_Pin=3;
int v1=130; //les vitesses à changer selon les moteurs que vous avez car en générale ils n'ont pas les meme vitesse
int v2=150;
int v11=80;
int v22=100;
int pin1Moteur1=13; //pin de commande moteur 1
int pin2Moteur1=12; // pin de commande moteur 1
int pinPMoteur1=11;// pin PWM moteur 1
int pin1Moteur2=8; // pin de commande moteur 2
int pin2Moteur2=7; // pin de commande moteur 2
int pinPMoteur2=5; // pin PWM moteur 2
/*################################################*/
//fonction cryptage du code morse de la lettre V ou O
bool crypt()
{Serial.println("in");
 unsigned long Time=0;
 unsigned long Start;
 //int val1=analogRead(LDR_Pin);
 while (Time < 470)
 {
  Time = 0 ;
  Serial.println(analogRead(LDR_Pin));
  if (analogRead(LDR_Pin)<= 100 )
  {  
     Start = millis();
     int k=0;
  while(analogRead(LDR_Pin) <= 100 ) 
  { }
  Time = millis() - Start ;
  Serial.println("Time");
  Serial.println(Time);
  }
  }
  //Serial.println("ok");
  unsigned long st = millis();
  unsigned long Time1 = 0; 
  while(analogRead(LDR_Pin) >150)
  { }
  Time1 = millis() - st;
  Serial.println("Time1");
  Serial.println(Time1);

  if (Time1>=290 && Time1<=310)
      {digitalWrite(Green_Led_Pin,LOW);
       digitalWrite(Red_Led_Pin,HIGH);
       return true;
      }
  else if (Time1 >= 90 && Time1<=110)
        {
          digitalWrite(Green_Led_Pin,HIGH);
          digitalWrite(Red_Led_Pin,LOW);
          return true;
        }
  else 
  {
    Serial.println("none");
    return false;
  }
}
/*#####################################*/

char str[2],i;
void forward() // fonction avancer téléguidé
{  analogWrite(pinPMoteur1,v1);
   digitalWrite(pin1Moteur1, 0);
   digitalWrite(pin2Moteur1, 1);
   analogWrite(pinPMoteur2,v2); 
   digitalWrite(pin1Moteur2, 0);
   digitalWrite(pin2Moteur2,1);
}
void backward() //fct reculer téléguidé
{
   analogWrite(pinPMoteur1,v1);
   Serial.print("pwm1");Serial.print(analogRead(pinPMoteur1)); 
   digitalWrite(pin1Moteur1, 1);
   digitalWrite(pin2Moteur1, 0);
   
   analogWrite(pinPMoteur2,v2); 
   digitalWrite(pin1Moteur2, 1);
   Serial.print("pin2mot2");Serial.print(analogRead(pin1Moteur2));
   digitalWrite(pin2Moteur2,0);
}
void left() // fct tourner à gauche téléguidé
{
   analogWrite(pinPMoteur1,v1); 
   digitalWrite(pin1Moteur1, 0);
   digitalWrite(pin2Moteur1, 1);
   analogWrite(pinPMoteur2,0); 
   digitalWrite(pin1Moteur2,0);
   digitalWrite(pin2Moteur2,0);
}
void right() //fct tourner à droite téléguidé
{
  analogWrite(pinPMoteur1,0); 
  digitalWrite(pin1Moteur1,0);
   digitalWrite(pin2Moteur1, 0);
   analogWrite(pinPMoteur2,v2); 
   digitalWrite(pin1Moteur2, 0);
   digitalWrite(pin2Moteur2,1);
}

void stopp() // fct stop pour téléguidé et suiveur
{   analogWrite(pinPMoteur1,0);
    analogWrite(pinPMoteur2,0);
    digitalWrite(pin2Moteur1,LOW);
    digitalWrite(pin1Moteur1,LOW);
    digitalWrite(pin2Moteur2,LOW);
    digitalWrite(pin1Moteur2,LOW);}

void moveForward(int v1 ,int v2) //fonction avancer pour le suiveur
{   analogWrite(pinPMoteur1,v1);
    analogWrite(pinPMoteur2,v2);
    digitalWrite(pin2Moteur1,HIGH);
    digitalWrite(pin2Moteur2,HIGH);
    digitalWrite(pin1Moteur1,LOW);
    digitalWrite(pin1Moteur2,LOW);
}

void moveBackward(int v1, int v2) // fonction reculer pour suiveur
{   analogWrite(pinPMoteur1,v1);
    analogWrite(pinPMoteur2,v2);
    digitalWrite(pin1Moteur1,HIGH);
    digitalWrite(pin1Moteur2,HIGH);
    digitalWrite(pin2Moteur1,LOW);
    digitalWrite(pin2Moteur2,LOW);
}

void turnLeft()//left motor stops and right motor goes forward to turn left in place
{   analogWrite(pinPMoteur1,v11); 
   digitalWrite(pin1Moteur1, 0);
   digitalWrite(pin2Moteur1, 1);
   analogWrite(pinPMoteur2,0); 
   digitalWrite(pin1Moteur2,0);
   digitalWrite(pin2Moteur2,0);
    
}

void turnRight()//right motor stops and left motor goes forward to turn right in place 
{   analogWrite(pinPMoteur1,0); 
  digitalWrite(pin1Moteur1,0);
   digitalWrite(pin2Moteur1, 0);
   analogWrite(pinPMoteur2,v22); 
   digitalWrite(pin1Moteur2, 0);
   digitalWrite(pin2Moteur2,1);
}

void suiveur()
{int j =0;

  while(j<4){
    moveForward(v11,v22);
    delay(100);
      if (analogRead(ldrl)<100 && analogRead(ldrr)>150&& (j<4))
      {
          stopp();
          delay(10);
          turnLeft();
          delay(930);
          j++;
      }
      else if (analogRead(ldrr)<100 && analogRead(ldrl)>150&& (j<4))
      {
          stopp();
          delay(10);
          turnRight();
          delay(930);
          j++;
          
    
      }/*else{if (analogRead(ldrc))
      {
          moveForward(v1,v2);
      }}*/
        
      
      
    }
      if (j==4)
      {
        stopp();
      }
      
    }
void setup() 
{
  Serial.begin(9600);
  pinMode(LDR_Pin, INPUT);
  pinMode(Red_Led_Pin, OUTPUT);
  pinMode(Green_Led_Pin, OUTPUT);
  pinMode(ldrl,INPUT);
  pinMode(ldrr,INPUT);
  pinMode(pin1Moteur1, OUTPUT);
  pinMode(pin2Moteur1, OUTPUT);
  pinMode(pinPMoteur1, OUTPUT);
  pinMode(pin1Moteur2, OUTPUT);
  pinMode(pin2Moteur2, OUTPUT);
  pinMode(pinPMoteur2, OUTPUT);
  
}

void loop() 
{ //crypt();
 int b=0;
  Serial.println(Serial.available());
  while(Serial.available())
  {
    char ch=Serial.read();
    str[i++]=ch;
    
    if(str[i-1]=='1')
    {
     Serial.println("Forward");
     forward();
     delay(200);
     stopp();
     i=0;
    }
  else if(str[i-1]=='7')
    {
      bool test = false;
      int b=0;
      while(b<10 && test == false){
       Serial.print(b);
       test = crypt() ;
        b++;}
        i=0;
    }
    else if(str[i-1]=='2')
    {
     Serial.println("Left");
     right();
     delay(200);
     stopp();
     i=0;
    }
    else if(str[i-1]=='3')
    {
      Serial.println("Right");
      left();
      delay(200);
      stopp();
      i=0;
    }
    
    else if(str[i-1]=='4')
    {
      Serial.println("Backward");
      backward();
      delay(200);
      stopp();
      i=0;
    }
    else if(str[i-1]=='5')
    {
      Serial.println("Stop");
      stopp();
      i=0;
    }
    else if (str[i-1]=='6') //suiveur
    {
      suiveur();
      i=0;
    }  
    delay(100);
  }
  //turnLeft();
}

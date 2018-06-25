#define trigPin 12 
#define echoPin 13 
//#include <Servo.h> //Add the Servo library 

//Connect motor controller pins to Arduino digital pins
//Right Motor 
int enA = 10; 
int in1 = 9; 
int in2 = 8; 
//Left Motor 
int enB = 5; 
int in3 = 6; 
int in4 = 7;
//int pos = 0;
//Servo myservo; 

//Set unsigned integer variables to be used
unsigned int duration;
unsigned int distance;
unsigned int FrontDistance;
unsigned int LeftDistance;
unsigned int RightDistance;
unsigned int Time;
unsigned int CollisionCounter;
unsigned int TriggerDistance;

void setup() //This block happens once at startup
{
//Below set all the pin modes as OUTPUT as they will all be outputting data 
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(enA, OUTPUT);   
  pinMode(enB, OUTPUT);   
  pinMode(in1, OUTPUT);   
  pinMode(in2, OUTPUT);   
  pinMode(in3, OUTPUT);   
  pinMode(in4, OUTPUT); 
//Included serial communication to show distances in serial monitor for demonstration purposes
  Serial.begin (9600); 
  //myservo.attach(4); //Attaches the servo to pin 4
}

void loop() 
{
  delay(200);
  scan();   //Call the Scan() procedure to check for obtacles to the front
  TriggerDistance = 40;
  FrontDistance = distance;                      //Whatever distance is returned by the Scan() procedure is set to the vaiable FrontDistance
  Serial.println("Front distance = ");           //Print routines for debugging
  Serial.print(distance);                        //Print routines for debugging 
  Serial.println(" cm");                         //Print routines for debugging
  if(FrontDistance < TriggerDistance){
    Serial.println("There's an obstacle!"); //Obstacle deteced by the initial forward scan
    Stop();
    Backward();
    delay(1000);
    Right();
    delay(1000);
    Stop();
    scan();
    RightDistance = distance;          //Set the variable LeftDistance to the distance returned from the scan                     
    Serial.println("Left distance = ");
    Serial.print(distance);                                //Wait half a second for the servo to get there, may need adjusting
    Left();
    delay(1000);
    Stop();
    scan();                          //Call the scan procedure
    RightDistance = distance;                      //Set the variable LeftDistance to the distance returned from the scan
    Serial.println("Right distance = ");
    Serial.print(distance);
    if(LeftDistance < RightDistance) {
      Right();
      delay(500);
      Forward();
      }
  else{
    Forward();
  }
}
}    


void Forward()                                    //This function tells the robot to go forward 
{
  Serial.println("");
  Serial.println("Moving forward");
  // turn on left motor   
  digitalWrite(in1, LOW);   
  digitalWrite(in2, HIGH);   
  // set speed out of possible range 0~255
  analogWrite(enA, 255);   
  // turn on right motor   
  digitalWrite(in3, HIGH);   
  digitalWrite(in4, LOW);   
  // set speed out of possible range 0~255   
  analogWrite(enB, 255);   
  //delay(200);
}

void Backward()                                  //This function tells the robot to move backward
{
  Serial.println("");
  Serial.println("Moving backward");
  // turn on left motor   
  digitalWrite(in1, HIGH);   
  digitalWrite(in2, LOW);   
  // set speed out of possible range 0~255
  analogWrite(enA, 255);   
  // turn on right motor   
  digitalWrite(in3, LOW);   
  digitalWrite(in4, HIGH);   
  // set speed out of possible range 0~255   
  analogWrite(enB, 255);   
  //delay(200);
}

void Left()                                      //This function tells the robot to turn left
{
  Serial.println("");
  Serial.println("Moving left");
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
// set speed out of possible range 0~255
  analogWrite(enA, 255); 
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
// set speed out of possible range 0~255   
  analogWrite(enB, 255);   
  //delay(200);  
}

void Right()                                    //This function tells the robot to turn right
{
  Serial.println("");
  Serial.println("Moving right");
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
// set speed out of possible range 0~255
  analogWrite(enA, 255); 
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, 255);
}

void Stop()                                     //This function tells the robot to stop moving
{
  Serial.println("");
  Serial.println("Stopping");
// now turn off motors   
  digitalWrite(in1, LOW);   
  digitalWrite(in2, LOW);     
  digitalWrite(in3, LOW);   
  digitalWrite(in4, LOW);
}

void scan() //This function tells the robot to scan for obstacles and set the variable distance  
{
  Serial.println("");
  Serial.println("Scanning");
  //int duration, distance; //Removed as these varoiables are set as global variable at the start of the program  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(1000); //Scan for 10 milliseconds?
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) /29.1;
  Serial.print(distance);
  Serial.println(" cm");
  //delay(500);                //Wait 1/2 second
}


  



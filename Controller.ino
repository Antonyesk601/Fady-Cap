const int transistor = 2;
const int transistor2 = 3;
const int transistor3 = 5;
const int transistor4 = 6;
const int voltageSensor = A0;
const int currentSensor = A5;

int transistorStatus=LOW;
int transistorStatus2=LOW;
int transistorStatus3=LOW;
int transistorStatus4=LOW;

int forcedTransistorStatus=LOW;
int forcedTransistorStatus2=LOW;
int forcedTransistorStatus3=LOW;
int forcedTransistorStatus4=LOW;

int desiredTransistorStatus=HIGH;
int desiredTransistorStatus2=LOW;
int desiredTransistorStatus3=LOW;
int desiredTransistorStatus4=LOW;


float previousVoltage=0.0;
float deltaVoltage=0.0;
float vOUT = 0.0;
float vIN = 0.0;
float R1 = 30000.0;
float R2 = 7500.0;
int value = 0;
void setup()
{
  Serial.begin(9600);
  pinMode (transistor, OUTPUT);
  pinMode (transistor2, OUTPUT);
  pinMode (transistor3, OUTPUT);
  pinMode (transistor4, OUTPUT);
  pinMode (voltageSensor, INPUT);
  pinMode (currentSensor, INPUT);
}

void loop()
{

  unsigned int x=0;
  float AcsValue=0.0,Samples=0.0,AvgAcs=0.0,AcsValueF=0.0;

  for (int x = 0; x < 150; x++)
  { 
    AcsValue = analogRead(currentSensor);        
    Samples = Samples + AcsValue;  
    delay (3); 
  }
  AvgAcs=Samples/150.0;
  
  AcsValueF = (2.5 - (AvgAcs * (5.0 / 1024.0)) )/0.185;
  delay(1000);
  value = analogRead(voltageSensor);
  vOUT = (value * 5.0) / 1024.0;
  previousVoltage=vIN;
  vIN = vOUT / (R2/(R1+R2));
  deltaVoltage=vIN-previousVoltage;
//  Serial.print("Voltage difference = ");
//  Serial.println(vIN);
  
  desiredTransistorStatus=Serial.readString`().toInt();
  desiredTransistorStatus2=Serial.readString().toInt();
  desiredTransistorStatus3=Serial.readString().toInt();
  desiredTransistorStatus4=Serial.readString().toInt(); 
 
  forcedTransistorStatus = Serial.readString().toInt();
  forcedTransistorStatus2= Serial.readString().toInt();
  forcedTransistorStatus3= Serial.readString().toInt();
  forcedTransistorStatus4= Serial.readString().toInt();
 
  if (deltaVoltage > 1.5&&vIN<5.5) 
  {
    transistorStatus  =  forcedTransistorStatus ? forcedTransistorStatus : HIGH ; 
    transistorStatus2 = forcedTransistorStatus2 ? forcedTransistorStatus2: HIGH; 
    transistorStatus3 = forcedTransistorStatus3 ? forcedTransistorStatus3: HIGH; 
    transistorStatus4 = forcedTransistorStatus4 ? forcedTransistorStatus4: HIGH; 
  } 
  else 
  {
    transistorStatus = forcedTransistorStatus  ? forcedTransistorStatus : desiredTransistorStatus ; 
    transistorStatus2= forcedTransistorStatus2 ? forcedTransistorStatus2: desiredTransistorStatus2; 
    transistorStatus3= forcedTransistorStatus3 ? forcedTransistorStatus3: desiredTransistorStatus3; 
    transistorStatus4= forcedTransistorStatus4 ? forcedTransistorStatus4: desiredTransistorStatus4; 
  }
  
  
  digitalWrite (transistor, transistorStatus);
  digitalWrite (transistor2, transistorStatus2);
  digitalWrite (transistor3, transistorStatus3);
  digitalWrite (transistor4, transistorStatus4);
  
  
  Serial.println(transistorStatus);
  Serial.println(transistorStatus2);
  Serial.println(transistorStatus3);
  Serial.println(transistorStatus4);
  Serial.println(vIN);
  Serial.println(AcsValueF);
  Serial.flush();
  delay(1000);
}

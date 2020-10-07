
//#define SERIAL_EN 1


#if defined(SERIAL_EN)
  #define  SENSOR_PIN A0//2
  #define  LIGTH_PIN 13//0
  #define  LED_PIN  12
#else
  #define  SENSOR_PIN A1//2
  #define  LED_PIN  1
  #define  LIGTH_PIN 0
#endif


#define  SAMPLE_COUNT 20
int sensor_val;

int buff[SAMPLE_COUNT];
int index = 0;
long average = 0;
void GetSample(int data)
{
  average = 0;
  buff[index] = data;
  index++;
  if(index>SAMPLE_COUNT){
    index = 0;   
  }

  for(int i = 0; i<SAMPLE_COUNT; i++)
  {
    average += buff[i];
  }

  average /= SAMPLE_COUNT;
}

void ligthControl()
{
  int dif = sensor_val - average; // 100 80

  if(sensor_val > average)
  {
    dif = sensor_val - average;
    if(dif > 100)
    {
      digitalWrite(LIGTH_PIN, 1);
      digitalWrite(LED_PIN, 1);
     // Serial.println("ON");
    }
  }
  else
  {
    dif = average - sensor_val;
    if(dif > 100)
    {
      digitalWrite(LIGTH_PIN, 0);
      digitalWrite(LED_PIN, 0);
     // Serial.println("OFF");
    }
  }
#if defined(SERIAL_EN)
  Serial.print(dif);
  Serial.print("\t");
  Serial.print(sensor_val);
  Serial.print("\t");
  Serial.println(average);
#endif
}

void setup() {
#if defined(SERIAL_EN)
  Serial.begin(9600);
#endif
  pinMode(LIGTH_PIN, 1);
  pinMode(LED_PIN, 1);
  pinMode(SENSOR_PIN, 0);

  

  for(int i = 0; i<20; i++)
  {
    buff[i] = analogRead(SENSOR_PIN);
  }
    
}

void loop() {
 
  int acc = 0;
  for(int i = 0; i<5; i++)
  {
   acc +=  analogRead(SENSOR_PIN);
    delay(10);
  }
  acc /=5;
  sensor_val = acc;
  GetSample(acc);
  ligthControl();



}

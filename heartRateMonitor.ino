// heartRateMonitor.ino

int sensorPin = 7;    // Pin for input from pulse sensor
int alarmPin = 8;
int ledPin = 13;      // Pin for LED to show pulse
unsigned long periodStart = 0; //Counter for start of heartbeat
double beatTime = 0; // Time from periodStart to current beat
double BPM = 60;      // Calculated average BPM
boolean calibrating = true; //Flag to ignore first several beats
int lowThresh = 30;
int highThresh = 150;
int dangerCount = 0;
int deadCount = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(sensorPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  delay(100);
  
  // Pulse LED with heartbeat
  digitalWrite(ledPin, digitalRead(sensorPin));
  
  // Sound alarm if heart rate is out of range.
  if ((dangerCount > 6) | (deadCount > 50))
     tone(alarmPin, 440);
  else
     noTone(alarmPin); //Turn off alarm if heart rate is okay
     
  countBeat();
}

void countBeat(){
  // read the value from the sensor. If high, we have a beat.
  if(digitalRead(sensorPin)){
    deadCount = 0; //if there's a pulse, then you're not dead.
    if (calibrating){
      // Ignore first few beats; they tend to be erratic.
      beatCount++;
      Serial.println("Calibrating...");
      if (beatCount > 5){
        calibrating = false;
        beatCount = 0;
        Serial.println("Calibration complete!");
      }
    }
    else if (beatCount == 0){
      // Start measuring period
      periodStart = millis();
    }
    else if (beatTime > 30){
      beatCount = 0;
      BPM = 60;
    }
    else{
      //get time from last beat to current beat (in seconds).
      beatTime = (millis() - periodStart) * 0.001;
      periodStart = millis(); // set current beat to be last beat
      //Measure average BPM
      //Serial.print("Calculated BPM is: ");
      //Serial.println(60/beatTime);
      BPM = (BPM + (60/beatTime))/2;
      Serial.print("Average heart rate is: ");
      Serial.println(BPM);
    }
    while (digitalRead(sensorPin)); //ignore remainder of high pulse
  }
  else
    deadCount++; //No pulse; you might be dying...
    
  
  if ((BPM < lowThresh) | (BPM > highThresh))
     dangerCount++; //heartrate out of range...
  else
     dangerCount = 0;
}

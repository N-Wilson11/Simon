//Toon definitie
#define TOON_BLAUW 250
#define TOON_GEEL 750
#define TOON_ROOD 1000
#define TOON_GROEN 500


//Pin definitie 
#define LED_ROOD 2
#define LED_GROEN 3
#define LED_GEEL 4
#define LED_BLAUW 5

//Knoppen definitie
#define KNOP_ROOD 1
#define KNOP_GEEL 1
#define KNOP_BLAUW 1
#define KNOP_GROEN 1

//Buzzer definitie
#define BUZZER 1

//Staat drukknop
int switchStateR = 0;
int switchStateB = 0;
int switchStateY = 0;
int switchStateG = 0;

//snelheid van een knipper
#define snelheid 250




void setup() {

  //LEDs
  pinMode(LED_ROOD, OUTPUT);
  pinMode(LED_GROEN, OUTPUT);
  pinMode(LED_GEEL, OUTPUT);
  pinMode(LED_BLAUW, OUTPUT);
  //Knoppen
  pinMode(KNOP_ROOD, INPUT);
  pinMode(KNOP_GEEL, INPUT);
  pinMode(KNOP_BLAUW, INPUT);
  pinMode(KNOP_GROEN, INPUT);

  //Buzzer
  pinMode(BUZZER, OUTPUT);

  digitalWrite(LED_ROOD, LOW);
  digitalWrite(LED_GROEN, LOW);
  digitalWrite(LED_GEEL, LOW);
  digitalWrite(LED_BLAUW, LOW);
  

}

void loop() {

switchStateR = digitalRead(KNOP_ROOD); 
switchStateY = digitalRead(KNOP_GEEL);
switchStateB = digitalRead(KNOP_BLAUW);
switchStateG = digitalRead(KNOP_GROEN);

Serial.println(switchStateR);
Serial.println(switchStateY);
Serial.println(switchStateB);
Serial.println(switchStateG);


//Rode knop wordt ingedrukt
if (switchStateR == HIGH){
  tone(BUZZER, TOON_ROOD);
}
else{
  noTone(BUZZER);
}
//Blauwe knop wordt ingedrukt
if (switchStateB == HIGH){
  tone(BUZZER, TOON_BLAUW);
}
else{
  noTone(BUZZER);
}
//Gele knop wordt ingedrukt
if (switchStateY == HIGH){
  tone(BUZZER, TOON_GEEL);
}
else{
  noTone(BUZZER);
}
//Groene knop wordt ingedrukt
if (switchStateG == HIGH){
  tone(BUZZER, TOON_GROEN);
}
else{
  noTone(BUZZER);
}

/*switchState = digitalRead(KNOP_BLAUW);

if (switchState == HIGH){
  digitalWrite(LED_BLAUW, HIGH);
}
else{
  digitalWrite(LED_BLAUW, LOW);
}
*/




}













void wrong_order()//Als een verkeerde code is ingevuld zullen alle LEDs eerst aan en dan uit gaan.

{ 

  for(int i = 0; i < 3; i++) //Dit gebeurt 3x
  {
  digitalWrite(LED_ROOD, HIGH);
  digitalWrite(LED_BLAUW, HIGH);
  digitalWrite(LED_GEEL, HIGH);
  digitalWrite(LED_GROEN, HIGH);
  delay(snelheid);


  digitalWrite(LED_ROOD, LOW);
  digitalWrite(LED_BLAUW, LOW);
  digitalWrite(LED_GEEL, LOW);
  digitalWrite(LED_GROEN, LOW);
  delay(snelheid);
  }
   
}




void right_order()//Dit gebeurt er als je de volgorde goed hebt
{

  for(int i = 0; i < 3; i++)
  {
    
  
  digitalWrite(LED_ROOD, HIGH);
  digitalWrite(LED_BLAUW, LOW);
  digitalWrite(LED_GEEL, HIGH);
  digitalWrite(LED_GROEN, LOW);
  delay(500);


  digitalWrite(LED_ROOD, LOW);
  digitalWrite(LED_BLAUW, HIGH);
  digitalWrite(LED_GEEL, LOW);
  digitalWrite(LED_GROEN, HIGH);
  delay(500);
  }
  
}

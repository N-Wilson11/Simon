//Toon definitie
#define TOON_BLAUW 250
#define TOON_GEEL 750
#define TOON_ROOD 1000
#define TOON_GROEN 600


//Pin definitie 
#define LED_ROOD 4
#define LED_GROEN 9
#define LED_GEEL 7
#define LED_BLAUW 2

//Knoppen definitie
#define KNOP_ROOD 5
#define KNOP_GEEL 13
#define KNOP_BLAUW 3
#define KNOP_GROEN 11

//Buzzer definitie
#define BUZZER A0

//Staat drukknop
int switchStateR = 0;
int switchStateB = 0;
int switchStateY = 0;
int switchStateG = 0;

//snelheid van een knipper
#define snelheid 250

//level
int level = 1;
int max_level = 50;

//volgorde van de speler
int player_order;

//volgorde van het spel
int game_order;




void setup() {

  //LEDs
  pinMode(LED_ROOD, OUTPUT);
  pinMode(LED_GROEN, OUTPUT);
  pinMode(LED_GEEL, OUTPUT);
  pinMode(LED_BLAUW, OUTPUT);
  //Knoppen
  pinMode(KNOP_ROOD, INPUT_PULLUP);
  pinMode(KNOP_GEEL, INPUT_PULLUP);
  pinMode(KNOP_BLAUW, INPUT_PULLUP);
  pinMode(KNOP_GROEN, INPUT_PULLUP);

  //Buzzer
  pinMode(BUZZER, OUTPUT);

  digitalWrite(LED_ROOD, LOW);
  digitalWrite(LED_GROEN, LOW);
  digitalWrite(LED_GEEL, LOW);
  digitalWrite(LED_BLAUW, LOW);
  

}

void loop() {

if (level ==1){
  make_order();//Maak een volgorde
}

/*if (switchStateB == HIGH && switchStateY == HIGH){

 tone(BUZZER, HIGH);
 delay(1000);
 noTone(BUZZER);
 delay(BUZZER);

  
}

*/




switchStateR = digitalRead(KNOP_ROOD); 
switchStateY = digitalRead(KNOP_GEEL);
switchStateB = digitalRead(KNOP_BLAUW);
switchStateG = digitalRead(KNOP_GROEN);

Serial.println(switchStateR);
Serial.println(switchStateY);
Serial.println(switchStateB);
Serial.println(switchStateG);


//Rode knop wordt ingedrukt
if (switchStateR == LOW){
  digitalWrite(LED_ROOD, HIGH);
  tone(BUZZER, TOON_ROOD);
}
else{
  digitalWrite(LED_ROOD, LOW);
  noTone(BUZZER);
}
//Blauwe knop wordt ingedrukt
if (switchStateB == LOW){
  digitalWrite(LED_BLAUW, HIGH);
  tone(BUZZER, TOON_BLAUW);
}
else{
  digitalWrite(LED_BLAUW, LOW);
  noTone(BUZZER);
}
//Gele knop wordt ingedrukt
if (switchStateY == LOW){
  digitalWrite(LED_GEEL, HIGH);
  tone(BUZZER, TOON_GEEL);
}
else{
  digitalWrite(LED_GEEL, LOW);
  noTone(BUZZER);
}
//Groene knop wordt ingedrukt
if (switchStateG == LOW){
  digitalWrite(LED_GROEN, HIGH);
  tone(BUZZER, TOON_GROEN);
}
else{
  digitalWrite(LED_GROEN, LOW);
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


void make_order(){

//Hier wordt de volgorde gemaakt
  
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
  level = 1;
   
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
  level++;
  /*
  snelheid = snelheid - 30;
  */
}

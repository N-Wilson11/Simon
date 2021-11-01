//Toon definitie
#define TOON_BLAUW 1000
#define TOON_GEEL 1000
#define TOON_ROOD 1000
#define TOON_GROEN 1000


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
  

}

void loop() {
  // put your main code here, to run repeatedly:

}

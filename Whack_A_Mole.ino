#include <LiquidCrystal.h>

LiquidCrystal lcd_1(1, 0, 13, 12, 11, 10);

const int redLED = 2;
const int blueLED = 3;
const int greenLED = 4;
const int yellowLED = 5;
const int orangeLED = A0;

const int redButton = 6;
const int blueButton = 7;
const int greenButton = 8;
const int yellowButton = 9;
const int orangeButton = A1;

int lightColor;
int last_lightcolor;
int score=0;
int timeDisplay=30;

unsigned long startTime;
unsigned long currentTime;
unsigned long startTimeRound;
unsigned long currentTimeRound;

int lcdarr[] = {2,3,4,5,A0};

void setup() {
  Serial.begin(9600);
  lcd_1.begin(16, 2); 
  pinMode(redLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(orangeLED,OUTPUT);
  pinMode(redButton, INPUT);
  pinMode(blueButton, INPUT);
  pinMode(greenButton, INPUT);
  pinMode(yellowButton, INPUT); 
  pinMode(orangeButton, INPUT);
  randomSeed(analogRead(0));
}

void loop() {
  if(timeDisplay>0){
  //startRoutine();
  playRoutine();
   // endRoutine();
  }
}

void startRoutine(){
  
  lcd_1.begin(16, 2);
  lcd_1.print("3");
  delay(1000);
  lcd_1.clear();
  lcd_1.print("2");
  delay(1000);
  lcd_1.clear();
  lcd_1.print("1");
  delay(1000);
  lcd_1.clear();
  lcd_1.print("START!");
  delay(1000);
  lcd_1.clear();
}

void playRoutine(){
  
  startTime = millis();
  currentTime = millis();
  int elapsedTime = 0;
  lcd_1.setCursor(6, 0);
  lcd_1.print("30");
 // int timeDisplay=30;
  
  while(timeDisplay>0){
    
    startTimeRound = millis();
    currentTimeRound = millis();
    int elapsedTimeRound = 0;
    do
    {lightColor = lcdarr[random(0, 5)];
    }
    while(lightColor==last_lightcolor);
    last_lightcolor=lightColor;//updates last color tracker
    
    while(elapsedTimeRound<=500){
      
      currentTime = millis();
      lcd_1.setCursor(0, 0);
      lcd_1.print("Time: ");
      lcd_1.setCursor(6, 0);
      timeDisplay=30-(elapsedTime/500);
      lcd_1.print(timeDisplay);
      lcd_1.print(" ");
      currentTime = millis();
      elapsedTime = currentTime - startTime;
      
      lcd_1.setCursor(0, 1);
      lcd_1.print("Score: ");
      lcd_1.setCursor(7, 1);
      lcd_1.print(score);
      
      digitalWrite(lightColor, HIGH);
      
      currentTimeRound = millis();
      elapsedTimeRound = currentTimeRound - startTimeRound;
      
      if(lightColor==2&&digitalRead(redButton)==HIGH){
        score=score+1;
        elapsedTimeRound = 1000;
      }
      if(lightColor==3&&digitalRead(blueButton)==HIGH){
        score=score+1;
        elapsedTimeRound = 1000;
      }
      if(lightColor==4&&digitalRead(greenButton)==HIGH){
        score=score+1;
        elapsedTimeRound = 1000;
      }
      if(lightColor==5&&digitalRead(yellowButton)==HIGH){
        score=score+1;
        elapsedTimeRound = 1000;
      }
      if(lightColor==A0&&digitalRead(orangeButton)==HIGH){
        score=score+1;
        elapsedTimeRound = 1000;
      }
    }
    digitalWrite(lightColor, LOW);
    Serial.print("Score: ");
    Serial.println(score);
    int del=random(10,300);
    delay(del);
  }
}

void endRoutine(){
  lcd_1.clear();
  lcd_1.setCursor(0, 0);
  lcd_1.print("GAME OVER!");
  lcd_1.setCursor(0, 1);
  lcd_1.print("TOTAL SCORE: ");
  lcd_1.setCursor(13, 1);
  lcd_1.print(score);
  //delay(10000);
}
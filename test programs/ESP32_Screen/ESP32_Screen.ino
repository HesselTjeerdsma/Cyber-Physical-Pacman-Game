#include <Wire.h> 
#include "SSD1306.h" 
#include "images.h"

SSD1306  display(0x3c, 21, 22);

int k = 1;
int score = 0;
int lives = 3;
String role = "pacman";
bool quarantine;

int LED1 = 2;
int LED2 = 4;
int LED3 = 5;

void setup() 
{
    Serial.begin(115200);
    display.init();
    display.flipScreenVertically();
    display.setFont(ArialMT_Plain_24);
  
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);

    ShowStart();
    Role();
}

void ShowStart() 
{
    display.clear();
    display.drawXbm(0, 0, 128, 64, Startup);
    display.display();
    delay(4000);
}

void ShowWinner() 
{
    display.clear();
    display.drawXbm(0, 0, 128, 64, Winner);
    display.display();
}

void Role() 
{
    display.clear();
    if (role == "pacman")
    {
      display.drawXbm(0, 0, 128, 64, Pacman);
    }
    else if(role == "ghost")
    {
      display.drawXbm(0, 0, 128, 64, Ghost);
    }
    display.display();
    delay(3000);
}

void UI()  
{
    display.clear();
    if (role == "pacman")
    {
      display.drawXbm(0, 0, 128, 64, Pacman_Small);
    }
    else if(role == "ghost")
    {
      display.drawXbm(0, 0, 128, 64, Ghost_Small);
    }
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.drawString(64, 25, String(score));
    display.display();
    switch(lives)
    {
      case 3:
        digitalWrite (LED1, HIGH);
        digitalWrite (LED2, HIGH); 
        digitalWrite (LED3, HIGH);  
      break;
      case 2:
         digitalWrite (LED1, HIGH);
         digitalWrite (LED2, HIGH); 
         digitalWrite (LED3, LOW);
      break;
      case 1:
         digitalWrite (LED1, HIGH);
         digitalWrite (LED2, LOW); 
         digitalWrite (LED3, LOW);  
      break;
      case 0:
        digitalWrite (LED1, LOW);
        digitalWrite (LED2, LOW); 
        digitalWrite (LED3, LOW); 
      break;
    }
}

void loop() 
{
  while(k != 0)
  {
    UI();
    score++;
    if(score == 5000){
      lives = 2;
    }
    if(score == 10000){
      lives = 1;
    }
    if(score == 18000){
      ShowWinner();
      k=0;
    }
  }
}

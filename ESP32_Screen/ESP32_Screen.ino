#include <Wire.h> 
#include "SSD1306.h" 
#include "images.h"

SSD1306  display(0x3c, 21, 22);

int score = 1;
int lives = 3;

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
}

void ShowScore()  
{
    display.clear();
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.drawString(64, 15, String(score));
    display.display();
}

void RolePacman() 
{
    display.clear();
    display.drawXbm(0, 0, 128, 64, Pacman);
    display.display();
}

void RoleGhost() 
{
    display.clear();
    display.drawXbm(0, 0, 128, 64, Ghost);
    display.display();
}

void DisplayLives()
{
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
  
}

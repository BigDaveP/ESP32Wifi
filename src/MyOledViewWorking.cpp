/**
    Gestion d'une VUE pour le OLed : Base pour les écrans de travail
    @file MyOledViewWorking.cpp
    @author Alain Dubé
    @version 1.1 20/11/20 
*/
#include <Arduino.h>
#include "MyOledViewWorking.h"

using namespace std;

void MyOledViewWorking::init(std::string _id) {
    Serial.println("Init dans MyOledViewWorking");
    MyOledView::init(_id);

    Fire24x24Pointers[0] = const_cast<unsigned char *>(&Fire24x24_1[0]);
    Fire24x24Pointers[1] = const_cast<unsigned char *>(&Fire24x24_2[0]);
    Fire24x24Pointers[2] = const_cast<unsigned char *>(&Fire24x24_3[0]);
    Fire24x24Pointers[3] = const_cast<unsigned char *>(&Fire24x24_4[0]);
    Fire24x24Pointers[4] = const_cast<unsigned char *>(&Fire24x24_5[0]);
    Fire24x24Pointers[5] = const_cast<unsigned char *>(&Fire24x24_6[0]);
    }
 
void MyOledViewWorking::displayGifFire(Adafruit_SSD1306 *adafruit, int positionX, int positionY){
    adafruit->drawBitmap(positionX, positionY, Fire24x24Pointers[5], 24, 16, WHITE);
    }

void MyOledViewWorking::displayGifFireAnimated(Adafruit_SSD1306 *adafruit, int positionX, int positionY){
    if(indexFireDelay>1000000) indexFireDelay = 0;
    if(indexFire>1000000) indexFire = 0;

    adafruit->fillRect(positionX, positionY, 24, 16, BLACK);adafruit->display();
    adafruit->drawBitmap(positionX, positionY, Fire24x24Pointers[(indexFire++) % 6], 24, 16, WHITE);
    adafruit->display();
    }

void MyOledViewWorking::update(Adafruit_SSD1306 *adafruit){
    Serial.println("Update my view MyOledViewWorking");
    }

void MyOledViewWorking::display( Adafruit_SSD1306 *adafruit) {
    Serial.println("MyOledViewWorking");
    adafruit->setTextColor(WHITE);

    adafruit->clearDisplay();
    adafruit->setTextSize(2);
    adafruit->setCursor(0, 0);
    adafruit->print(getTag("nomDuSysteme").c_str());

    adafruit->setTextSize(1);
    adafruit->setCursor(0, 20);
    adafruit->print("Id: ");
    adafruit->print(getTag("idDuSysteme").c_str());
    
    adafruit->setCursor(40, 50);
    adafruit->print(getTag("ipDuSysteme").c_str());

    adafruit->display();
}
	
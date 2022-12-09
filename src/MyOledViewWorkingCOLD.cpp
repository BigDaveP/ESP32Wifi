/**
    Gestion d'une VUE pour le OLed : Base pour les écrans de travail
    @file MyOledViewWorkingCold.cpp
    @author David Pigeon
    @version 1.1 22/12/09 
*/

#include <Arduino.h>
#include "MyOledViewWorkingCOLD.h"

using namespace std;

void MyOledViewWorkingCOLD::display(Adafruit_SSD1306 *adafruit){
    adafruit->clearDisplay();
    MyOledViewWorking::display(adafruit);
    adafruit->setTextSize(1);
    adafruit->setCursor(70,20);
    adafruit->print("Waiting");
    adafruit->setTextSize(2);
    adafruit->setCursor(10, 30);
    adafruit->print(getTag("temperature").c_str());

    adafruit->display();
}

void MyOledViewWorkingCOLD::update(Adafruit_SSD1306 *adafruit){
    Serial.println("Update my view MyOledViewWorkingCOLD");
}
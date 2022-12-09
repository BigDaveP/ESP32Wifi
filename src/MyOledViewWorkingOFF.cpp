/**
    Gestion d'une VUE pour le OLed : Base pour les écrans de travail
    @file MyOledViewWorkingOFF.cpp
    @author David Pigeon
    @version 1.1 22/12/09 
*/

#include <Arduino.h>
#include "MyOledViewWorkingOFF.h"

using namespace std;

void MyOledViewWorkingOFF::display(Adafruit_SSD1306 *adafruit){

    adafruit->clearDisplay();
    MyOledViewWorking::display(adafruit);

    adafruit->setTextSize(1);
    adafruit->setCursor(70,20);
    adafruit->print("Ready");

    adafruit->setTextSize(1);
    adafruit->setCursor(70, 30);
    adafruit->print(getTag("temperature").c_str());

    adafruit->display();
}
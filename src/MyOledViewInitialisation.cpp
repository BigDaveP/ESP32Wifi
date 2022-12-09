/*
    Gestion d'une VUE pour le OLed (Initialisation du système)
    @file MyOledViewInitialisation.cpp
    @author David Pigeon
    @version 1.0 22/12/02
*/
#include <Arduino.h>
#include "MyOledViewInitialisation.h"
using namespace std;

void MyOledViewInitialisation::setNomDuSysteme(string val){
    nomDuSysteme = val;
}

void MyOledViewInitialisation::setIdDuSysteme(string val){
    idDuSysteme = val;
}

void MyOledViewInitialisation::setSensibiliteBoutonAction(string val){
    SensibiliteBoutonAction = val;
}

void MyOledViewInitialisation::setSensibiliteBoutonReset(string val){
    SensibiliteBoutonReset = val;
}

void MyOledViewInitialisation::update(Adafruit_SSD1306 *adafruit){
    Serial.println("Update my view MyOledViewInitialisation");
}

void MyOledViewInitialisation::display(Adafruit_SSD1306 *adafruit){
    adafruit->clearDisplay();
    adafruit->setTextSize(2);
    adafruit->setCursor(0, 0);
    adafruit->print(nomDuSysteme.c_str());

    adafruit->setTextSize(1);
    adafruit->setCursor(0, 20);
    adafruit->print("SSID: ");
    adafruit->print(idDuSysteme.c_str());

    adafruit->setTextSize(1);
    adafruit->setCursor(0,30);
    adafruit->print("INITIALISATION");

    adafruit->setTextSize(1);
    adafruit->setCursor(0, 40);
    adafruit->print("Bouton ACTION: ");
    adafruit->print(SensibiliteBoutonAction.c_str());
    
    adafruit->setTextSize(1);
    adafruit->setCursor(0, 50);
    adafruit->print("Bouton RESET: ");
    adafruit->print(SensibiliteBoutonReset.c_str());

    adafruit->display();
}
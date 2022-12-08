
#include <Arduino.h>
#include "MyOledViewWifiAp.h"
using namespace std;

void MyOledViewWifiAp::setNomDuSysteme(string val){
    nomDuSysteme = val;
}

void MyOledViewWifiAp::setPassDuSysteme(string val){
    passDuSysteme = val;
}

void MyOledViewWifiAp::setSsIDDuSysteme(string val){
    ssIDDuSysteme = val;
}

void MyOledViewWifiAp::update(Adafruit_SSD1306 *adafruit){
    Serial.println("Update my view MyOledViewWifiAp");
}

void MyOledViewWifiAp::display(Adafruit_SSD1306 *adafruit){
    adafruit->setTextSize(2);
    adafruit->setCursor(0, 0);
    adafruit->print(nomDuSysteme.c_str());

    adafruit->setTextSize(1);
    adafruit->setCursor(0,20);
    adafruit->print("AP configuration");

    adafruit->setTextSize(1);
    adafruit->setCursor(15, 30);
    adafruit->print("SSID: ");
    adafruit->print(ssIDDuSysteme.c_str());
    
    adafruit->setTextSize(1);
    adafruit->setCursor(15, 40);
    adafruit->print("PASS: ");
    adafruit->print(passDuSysteme.c_str());

    adafruit->display();
}
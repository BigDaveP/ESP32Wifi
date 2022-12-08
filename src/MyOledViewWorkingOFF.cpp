

#include <Arduino.h>
#include "MyOledViewWorkingOFF.h"

using namespace std;

void MyOledViewWorkingOFF::display(Adafruit_SSD1306 *adafruit){

    MyOledViewWorking::display(adafruit);

    adafruit->setTextSize(1);
    adafruit->setCursor(70,20);
    adafruit->print("Ready");

    adafruit->setTextSize(1);
    adafruit->setCursor(70, 30);
    adafruit->print(getTag("temperature").c_str());

    adafruit->display();
}
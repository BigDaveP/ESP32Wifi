


#ifndef MYOLEDVIEWWIFIAP_H
#define MYOLEDVIEWWIFIAP_H

#include <Adafruit_SSD1306.h>
#include "MyOledView.h"
#include <string>
#include <vector>
using std::vector;

class MyOledViewWifiAp: public MyOledView {
    
    public:
        void setNomDuSysteme(std::string val);
        void setSsIDDuSysteme(std::string val);
        void setPassDuSysteme(std::string val);

    private:
        std::string nomDuSysteme;
        std::string ssIDDuSysteme;
        std::string passDuSysteme;

        void display(Adafruit_SSD1306 *adafruit);
        void update(Adafruit_SSD1306 *adafruit);
      
};
#endif
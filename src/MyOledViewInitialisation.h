

#ifndef MYOLEDVIEWINITIALISATION_H
#define MYOLEDVIEWINITIALISATION_H

#include <Adafruit_SSD1306.h>
#include "MyOledView.h"
#include <string>
#include <vector>
using std::vector;

class MyOledViewInitialisation: public MyOledView {
    
    public:
        void setNomDuSysteme(std::string val);
        void setIdDuSysteme(std::string val);
        void setSensibiliteBoutonAction(std::string val);
        void setSensibiliteBoutonReset(std::string val);

    private:
        std::string nomDuSysteme;
        std::string idDuSysteme;
        std::string SensibiliteBoutonAction;
        std::string SensibiliteBoutonReset;

        void display(Adafruit_SSD1306 *adafruit);
        void update(Adafruit_SSD1306 *adafruit);
};
#endif
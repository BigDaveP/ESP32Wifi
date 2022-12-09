/*
    /**
    Class MyOledView : Gestion d'une VUE pour le OLed (Quand le four est en pause et froid)
    Extends sur MyOledViewWorking
    @file MyOledViewWorkingCold.h
    @author David Pigeon
    @version 1.0 22/12/02 
    
    Historique des versions   
                            Versions  Date      Auteur      Description
                            1.0      22/12/02   DP        Première version de la classe
                            
                            
    platform = espressif32
    board = esp32doit-devkit-v1
    framework = arduino
    lib_deps = 
        Aucune
    Autres librairies (à copier dans le répertoire lib)
        Aucune
    
    Exemple d'utilisation 
        //Définition 
            #include "MyOledViewWorkingCold.h"
            class MyOledViewWorkingCold: public MyOledView {
                public:
                
                private:
                    //Mettre la vue dans cette méthode
                    void display( Adafruit_SSD1306 *adafruit);
        ...
        //Utilisation
        MyOledViewWorkingCold = new MyOledViewWorkingCold();
        myOled->displayView(MyOledViewWorkingCold);
*/

#ifndef MyOledViewWorkingCOLD_H
#define MyOledViewWorkingCOLD_H

#include <Adafruit_SSD1306.h>
#include "MyOledViewWorking.h"
#include <string>
#include <vector>
using std::vector;

class MyOledViewWorkingCOLD: public MyOledViewWorking {

    private:
        void display(Adafruit_SSD1306 *adafruit);
        void update(Adafruit_SSD1306 *adafruit);
};
#endif
/*
    /**
    Class MyOledView : Gestion d'une VUE pour le OLed (Initialisation du système)
    Extends sur MyOledView
    @file MyOledViewInitialisation.h
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
            #include "MyOledViewInitialisation.h"
            class MyOledViewInitialisation: public MyOledView {
                public:
                
                private:
                    //Mettre la vue dans cette méthode
                    void display( Adafruit_SSD1306 *adafruit);
        ...
        //Utilisation
        myOledViewInitialisation = new MyOledViewInitialisation();
        myOled->displayView(myOledViewInitialisation);
*/


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
/*
    /**
    Class MyOledView : Gestion d'une VUE pour le OLed (Affichage des informations de connexion au réseau Wifi)
    Extends sur MyOledView
    @file MyOledViewWifiAp.h
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
            #include "MyOledViewWifiAp.h"
            class MyOledViewWifiAp: public MyOledView {
                public:
                
                private:
                    //Mettre la vue dans cette méthode
                    void display( Adafruit_SSD1306 *adafruit);
        ...
        //Utilisation
        MyOledViewWifiAp = new MyOledViewWifiAp();
        myOled->displayView(MyOledViewWifiAp);
*/


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
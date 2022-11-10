/**
    Class MyOledView : Gestion d'une VUE pour le OLed
    @file MyButton.h 
    @author Alain Dubé
    @version 1.1 21/09/20 
    
    Historique des versions   
                            Versions  Date      Auteur      Description
                            1.1      21/09/20   Ald         Première version de la classe
                            
                            
    platform = espressif32
    board = esp32doit-devkit-v1
    framework = arduino
    lib_deps = 
        Aucune
    Autres librairies (à copier dans le répertoire lib)
        Aucune
    
    Exemple d'utilisation 
        //Définition 
            #include "MyOledView.h"
            class MyOledViewInitialisation: public MyOledView {
                public:
                
                private:
                    //Mettre la vue dans cette méthode
                    void display( Adafruit_SSD1306 *adafruit);
        ...
        //Utilisation
        myOledViewInitialisation = new MyOledViewInitialisation();
        myOled->displayView(myOledViewInitialisation);
**/


#ifndef MYOLEDVIEW_H
#define MYOLEDVIEW_H

#include <Adafruit_SSD1306.h>
#include <string>
#include <vector>
using std::vector;

class MyOledView {
    
    public:
        virtual void display( Adafruit_SSD1306 *adafruit) = 0;
        void setParams(std::string tag, std::string value);
        std::string getTag(std::string tag);
                
        void init(std::string _id);
        std::string id();

        virtual void update(Adafruit_SSD1306 *adafruit) = 0;;

    private:
        int findTag(std::string tag);
        std::string myId;
        vector<std::string> params;
      
};
#endif
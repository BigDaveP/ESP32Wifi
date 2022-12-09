/* Copyright (C) 2021 David Pigeon
 * All rights reserved.
 *
 * Projet Sac
 * Ecole du Web
 * Cours Objets connectés (c)2021
 *  
    @file     main.cpp
    @author   David Pigeon
    @version  1.1 21/08/15 

    Historique des versions
           Version    Date       Auteur       Description
           1.1        21/08/15  Alain       Première version du logiciel
            1.2        22/10/07  David Pigeon       Ajout de la gestion Wifi
            1.3        22/11/17  David Pigeon       Ajout de la gestion de l'écran OLED
            1.5        22/12/09  David Pigeon       Version finale

    platform = espressif32
    board = esp32doit-devkit-v1
    framework = arduino
    lib_deps = 

            --Pour le Wifi

            ESPAsyncWebServer-esphome                   (Pour accéder au Wifi)
            AsyncTCP-esphome                            (Pour utiliser les fonctionnalités TCP)
            bblanchon/ArduinoJson@^6.17.2               (Pour accéder au fonctionnalités Json)

            --Pour l'écran OLED
            Adafruit SSD1306                            (Pour accéder au fonctionnalités de l'écran OLED)
            Adafruit GFX Library                        (Pour accéder au fonctionnalités de l'écran OLED)
            Adafruit BusIO                              (Pour accéder au fonctionnalités de l'écran OLED)



    Autres librairies (à copier dans le répertoire lib)
         WifiManagerDevelopment
            //Remarques
            //Pour trouver le WifiManager (dans la branche development)
            //   https://github.com/tzapu/WiFiManager/tree/development
            //   Ne pas oublier d'appuyez sur l'ampoule et choisir : ajouter Lib
                    /lib/DHT/DHT.cpp
        Pour obtenir la température
        float getTemperature()
    
    Fonctions utiles (utilitaires)
        /lib/MYLIB/myFunctions.cpp
            //Pour vérifier plus simplement que deux chaines sont identiques
            bool isEqualString(std::string line1, std::string line2)
            //Pour extraire une partie d'une chaine de caractères avec l'aide d'un index
            std::string getValue(std::string data, char separator, int index)
            //Pour remplacer plus facilement une sous chaine
            bool replaceAll(std::string& source, const std::string& from, const std::string& to)
            //Pour obtenir un chaine aléatoire d'une certaine longeur
            std::string get_random_string(unsigned int len)
        

    Classes du système
         
        MyServer                        V1.0    Pour la gestion des routes pour le site WEB
            /data                               Répertoire qui contient les fichiers du site WEB 
                index.html              V1.0    Page index du site WEB
                index.css               V1.0    CSS
                script.js               V1.0    JS (fonctions JavaScript)
              
 * */

#include <iostream>
#include <string>
#include <Arduino.h>
#include <ArduinoJson.h>
#include "myFunctions.cpp" //fonctions utilitaires
#include <HTTPClient.h>
#include <WiFiManager.h>

using namespace std;

WiFiManager wm;
#define WEBSERVER_H

//Pour la gestion du serveur ESP32
#include "MyServer.h"
MyServer *myServer = NULL;

//Pour la gestion de l'écran OLED
#include "MyOled.h"
MyOled *myOled = NULL;
#include "MyOledViewWorking.h"
MyOledViewWorking *myOledViewWorking = NULL;
#include "MyOledViewWifiAp.h"
MyOledViewWifiAp *myOledViewWifiAp = NULL;
#include "MyOledViewInitialisation.h"
MyOledViewInitialisation *myOledViewInitialisation = NULL;
#include "MyOledViewWorkingOFF.h"
MyOledViewWorkingOFF *myOledViewWorkingOFF = NULL;
#include "MyOledViewWorkingCOLD.h"
MyOledViewWorkingCOLD *myOledViewWorkingCOLD = NULL;
#include "MyOledViewWorkingHEAT.h"
MyOledViewWorkingHEAT *myOledViewWorkingHEAT = NULL;

//Variable pour la connection Wifi
const char *SSID = "SAC_";
const char *PASSWORD = "sac_";
String ssIDRandom;

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     15 // Reset pin # (or -1 if sharing Arduino reset pin)
#define addrI2C 0x3C    // I2C address of the OLED display

#include "TemperatureStub.h"
TemperatureStub *temperatureStub = NULL;
float temperature;
int currentTemperatureDisplayed = 0;
char strTemperature[128];

#define GPIO_PIN_LED_HEAT_RED               17 // GPIO25
#define GPIO_PIN_LED_HEAT_YELLOW             18 // GPIO26
#define GPIO_PIN_LED_HEAT_GREEN              16 // GPIO27
String stateFour = "";

//Variable pour la gestion des informations du bois reçues
int drying = 0;
int dryingBois = 0;
int tempMin = 0;
int compteur = 0;
bool isDrying = false;

//Valeur par défaut pour le delay entre chaque boucle
int delayOnLoop = 1000;

#define nomSystem "SAC System"
string idDuSysteme = "12815";

#include "MyButton.h"
MyButton *myButtonAction = NULL;
MyButton *myButtonReset = NULL;

//fonction statique qui permet aux objets d'envoyer des messages (callBack) 
//  arg0 : Action 
// arg1 ... : Parametres
std::string CallBackMessageListener(string message) {
    while(replaceAll(message, std::string("  "), std::string(" ")));
    //Décortiquer le message
    string actionToDo = getValue(message, ' ', 0);
    string arg1 = getValue(message, ' ', 1);
    string arg2 = getValue(message, ' ', 2);
    string arg3 = getValue(message, ' ', 3);

    if (string(actionToDo.c_str()).compare(string("button")) == 0) {
        if(string(arg1.c_str()).compare(string("getlisteBois")) == 0) {
            return(String("Ok").c_str());
            }
        if(string(arg1.c_str()).compare(string("getTemperatureSensor")) == 0) {       
            return(String(temperature).c_str());
            }
        if(string(arg1.c_str()).compare(string("sendBoisInfo")) == 0) {
            drying = atoi(arg2.c_str());
            dryingBois = atoi(arg2.c_str());
            tempMin = atoi(arg3.c_str());
            isDrying = true;
            return(String("Ok").c_str());
            }
        if(string(arg1.c_str()).compare(string("getStateLed")) == 0) {
            return(stateFour.c_str());
            }
    }

}

void setup() { 
    Serial.begin(9600);
    delay(100);

    // ----------- Initialisation des buttons autosensibilisé ---------------->
    myButtonAction = new MyButton();
    myButtonAction->init(T8);
    int sensibilisationButtonAction = myButtonAction->autoSensibilisation();
    
    myButtonReset = new MyButton();
    myButtonReset->init(T9);
    int sensibilisationButtonReset = myButtonReset->autoSensibilisation();

    char strBoutonAction[128];
    sprintf(strBoutonAction, "%d", sensibilisationButtonAction);

    char strBoutonReset[128];
    sprintf(strBoutonReset, "%d", sensibilisationButtonReset);

    // ----------- Stub de la temperature ----------------<
    temperatureStub = new TemperatureStub();
    temperatureStub->init();


    // ----------- Connexion pour WifiManager ---------------->
    String ssIDRandom, PASSRandom;
    String stringRandom;
    stringRandom = get_random_string(4).c_str();
    ssIDRandom = SSID;
    ssIDRandom = ssIDRandom + stringRandom;
    stringRandom = get_random_string(4).c_str();
    PASSRandom = PASSWORD;
    PASSRandom = PASSRandom + stringRandom;

char strToPrint[128];
    sprintf(strToPrint, "Identification : %s   MotDePasse: %s", ssIDRandom, PASSRandom);
    Serial.println(strToPrint);


 if (!wm.autoConnect(ssIDRandom.c_str(), PASSRandom.c_str())){
        Serial.println("Erreur de connexion.");
      
        }
    else {
        Serial.println("Connexion Établie.");
        }

    // ----------- Routes du serveur ----------------
    myServer = new MyServer(80);
    myServer->initAllRoutes();
    myServer->initCallback(&CallBackMessageListener);

    // ----------- Affichage sur l'écran ----------------
    myOled = new MyOled(&Wire, addrI2C, SCREEN_HEIGHT, SCREEN_WIDTH);
    myOled->init();

    myOledViewInitialisation = new MyOledViewInitialisation();
    myOledViewInitialisation->setIdDuSysteme(idDuSysteme.c_str());
    myOledViewInitialisation->setNomDuSysteme(nomSystem);
    myOledViewInitialisation->setSensibiliteBoutonAction(strBoutonAction);
    myOledViewInitialisation->setSensibiliteBoutonReset(strBoutonReset);
    myOled->displayView(myOledViewInitialisation);
    delay(2000);

    myOledViewWifiAp = new MyOledViewWifiAp();
    myOledViewWifiAp->setNomDuSysteme(nomSystem);
    myOledViewWifiAp->setSsIDDuSysteme(ssIDRandom.c_str());
    myOledViewWifiAp->setPassDuSysteme(PASSRandom.c_str());
    myOled->displayView(myOledViewWifiAp);
    delay(2000);

    myOledViewWorkingOFF = new MyOledViewWorkingOFF();
    myOledViewWorkingCOLD = new MyOledViewWorkingCOLD();
    myOledViewWorkingHEAT = new MyOledViewWorkingHEAT();

    // ----------- Gestion des LEDs ----------------
    pinMode(GPIO_PIN_LED_HEAT_RED, OUTPUT);
    pinMode(GPIO_PIN_LED_HEAT_YELLOW, OUTPUT);
    pinMode(GPIO_PIN_LED_HEAT_GREEN, OUTPUT);
    for (int i = 0; i < 2; i++){
        digitalWrite(GPIO_PIN_LED_HEAT_RED, HIGH);
        digitalWrite(GPIO_PIN_LED_HEAT_GREEN, HIGH);
        digitalWrite(GPIO_PIN_LED_HEAT_YELLOW, HIGH);
        delay(500);
        digitalWrite(GPIO_PIN_LED_HEAT_RED, LOW);
        digitalWrite(GPIO_PIN_LED_HEAT_GREEN, LOW);
        digitalWrite(GPIO_PIN_LED_HEAT_YELLOW, LOW);
        delay(500);
    }
 }

// Fonction qui permet de définir les différents états du four et de gérer les différents affichages
void displayGoodScreen(){
  delay(10);
  sprintf(strTemperature, "%g", temperature);
  if(isEqualString(stateFour.c_str(), string("OFF"))) {
    digitalWrite(GPIO_PIN_LED_HEAT_RED, LOW);
    digitalWrite(GPIO_PIN_LED_HEAT_GREEN, HIGH);
    digitalWrite(GPIO_PIN_LED_HEAT_YELLOW, LOW);
    myOledViewWorkingOFF->setParams("nomDuSysteme", nomSystem);
    myOledViewWorkingOFF->setParams("idDuSysteme", idDuSysteme);
    myOledViewWorkingOFF->setParams("temperature", strTemperature);
    myOledViewWorkingOFF->setParams("ipDuSysteme",WiFi.localIP().toString().c_str());
    myOled->displayView(myOledViewWorkingOFF);
    currentTemperatureDisplayed = temperature;
  }

  if(isEqualString(stateFour.c_str(), string("COLD"))) {
    digitalWrite(GPIO_PIN_LED_HEAT_RED, HIGH);
    digitalWrite(GPIO_PIN_LED_HEAT_GREEN, LOW);
    digitalWrite(GPIO_PIN_LED_HEAT_YELLOW, LOW);
    myOledViewWorkingCOLD->setParams("nomDuSysteme", nomSystem);
    myOledViewWorkingCOLD->setParams("idDuSysteme", idDuSysteme.c_str());
    myOledViewWorkingCOLD->setParams("temperature", strTemperature);
    myOledViewWorkingCOLD->setParams("ipDuSysteme",WiFi.localIP().toString().c_str());
    myOled->displayView(myOledViewWorkingCOLD);
    currentTemperatureDisplayed = temperature;
  }

  if(isEqualString(stateFour.c_str(), string("HEAT"))) {
    digitalWrite(GPIO_PIN_LED_HEAT_RED, LOW);
    digitalWrite(GPIO_PIN_LED_HEAT_GREEN, LOW);
    digitalWrite(GPIO_PIN_LED_HEAT_YELLOW, HIGH);
    myOledViewWorkingHEAT->setParams("nomDuSysteme", nomSystem);
    myOledViewWorkingHEAT->setParams("idDuSysteme", idDuSysteme);
    myOledViewWorkingHEAT->setParams("temperature", strTemperature);
    myOledViewWorkingHEAT->setParams("ipDuSysteme",WiFi.localIP().toString().c_str());
    myOled->displayView(myOledViewWorkingHEAT);
    currentTemperatureDisplayed = temperature;
    myOled->updateCurrentView(myOledViewWorkingHEAT);
  }
}

void loop() {
    temperature = temperatureStub->getTemperature();
    if (isDrying == true) {
        delayOnLoop = 10;
        if(drying % 1000 == 0) { // Modulo pour éviter de compter à chaque boucle
        compteur = drying/1000;
        if(temperature >= tempMin && compteur < dryingBois && digitalRead((GPIO_PIN_LED_HEAT_RED) == LOW)) stateFour = "HEAT";
        else if(temperature < tempMin && dryingBois > compteur) {
            drying -= 10; // On enlève une valeur de 10 pour éviter que le compteur s'incrémente
            delay(1000);
            stateFour = "COLD";
            }
        else stateFour = "OFF";
        displayGoodScreen();
        }
        drying += 10;
    }
    delay(delayOnLoop);
  }



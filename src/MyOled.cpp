/**
    Gestion d'un écran Oled Utilisant un GPIO d'un contrôleur
    @file MyOled.cpp
    @author Alain Dubé
    @version 1.1 20/11/20 
*/
#include <Arduino.h>
#include "MyOled.h"
using namespace std;

int MyOled::veilleTimeLapse = 0;
MyOledView *MyOled::currentView = NULL;

void MyOled::updateCurrentView(MyOledView *view){
   if(view) view->update(this);
    }

void MyOled::displayView(MyOledView *view) {
    view->display(this);
    MyOled::currentView = view;
    }

//Génère des intervales de UNE seconde pour synchroniser le système
//   Pour l'écran de veille
void MyOled::vATaskSecondCount(void *pvParameters)  {
    const TickType_t xFrequency = pdMS_TO_TICKS(1000);
    TickType_t xLastWakeTime = xTaskGetTickCount();
    while (1) {
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
        MyOled::veilleTimeLapse++;
        xLastWakeTime = xTaskGetTickCount();
    }
    vTaskDelete(NULL);
}

//Retourne 1 si erreur d'adresse
int MyOled::init(uint8_t addrI2C, bool displaySplashPlease) {
    if (!begin(SSD1306_SWITCHCAPVCC, addrI2C)) { //Parfois 3D
        return (1);
        }

    PushMan24x48Pointers[0] = const_cast<unsigned char *>(&PushMan24x48_1[0]);
    PushMan24x48Pointers[1] = const_cast<unsigned char *>(&PushMan24x48_2[0]);
    PushMan24x48Pointers[2] = const_cast<unsigned char *>(&PushMan24x48_3[0]);
    PushMan24x48Pointers[3] = const_cast<unsigned char *>(&PushMan24x48_4[0]);
    PushMan24x48Pointers[4] = const_cast<unsigned char *>(&PushMan24x48_5[0]);
    PushMan24x48Pointers[5] = const_cast<unsigned char *>(&PushMan24x48_6[0]);
    PushMan24x48Pointers[6] = const_cast<unsigned char *>(&PushMan24x48_7[0]);
  
    cp437(true);
    clearDisplay();
    setTextColor(SSD1306_WHITE);
    setTextSize(1);
    setCursor(1, 1);
    display();

    if(displaySplashPlease) displaySplash(1000);

    xTaskCreate(vATaskSecondCount, "vATask Loop", 10000, NULL, 1, NULL);

    veilleExit();

    return (0); //Ok
    }

void MyOled::veilleDelay(int nbreSecondes) {
    veilleNbreSecondes = nbreSecondes;
    MyOled::veilleTimeLapse = 0;
    veilleActif = false;
    }

bool MyOled::veilleCheck(bool debugMe) {
    if(debugMe) {
        Serial.print("MyOled::veilleCheck : ");
        Serial.print(veilleActif);
        Serial.print(", ");
        Serial.print(MyOled::veilleTimeLapse);
        Serial.print(", ");
        Serial.print(veilleNbreSecondes);
        Serial.println(" ");
        }
    if (MyOled::veilleTimeLapse > veilleNbreSecondes){
        ssd1306_command(SSD1306_DISPLAYOFF);
        MyOled::veilleTimeLapse = 0;
        veilleActif = true;
        }
    return veilleActif;
    }

void MyOled::veilleExit() {
    ssd1306_command(SSD1306_DISPLAYON);
    MyOled::veilleTimeLapse = 0;
    veilleActif = false;
    }


/**
 * print Affiche une chaine de caractère sur le Oled
 *
 * Affiche une chaine de caractère sur le Oled
 * 
 * @param int posx Positionnement en X
 * @param int posy Positionnement en Y
 * @param String toDisplay Chaine de caractères à afficher
 * @param bool displayAfter Force un affichage 
 * @param int makeDelaySecondes Attends un nombre de secondes avant de poursuivre
 */
void MyOled::printIt(int posx, int posy, string toDisplay, bool displayAfter, int makeDelaySecondes) {
        setCursor(posx, posy);
        println(toDisplay.c_str());
        if (displayAfter)
            display();
        delay(makeDelaySecondes);
    }

/**
 * print Affiche une chaine de caractère sur le Oled
 *
 * Affiche une chaine de caractère sur le Oled
 * 
 * @param String toDisplay Chaine de caractères à afficher
 * @param bool displayAfter Force un affichage 
 * @param int makeDelaySecondes Attends un nombre de secondes avant de poursuivre
 */
void MyOled::printIt(string toDisplay, bool displayAfter, int makeDelaySecondes) {
        println(toDisplay.c_str());
        if (displayAfter)
            display();
        delay(makeDelaySecondes);
    }

/**
 * printSpecialChar Affiche un caractère spécial sur le Oled
 *
 * Affiche  un caractère spécial sur le Oled (é ou o)
 * 
 * @param String spacialCaractere Caractère é : Accent aigu ou o : Degrée
 * @param int makeDelaySecondes Attends un nombre de secondes avant de poursuivre
 */
void MyOled::printSpecialChar(string spacialCaractere, int makeDelaySecondes) {
        if (spacialCaractere == "é")
            write(130); //é
        if (spacialCaractere == "o")
            write(248); //Le o du Degre Celcius 167
        delay(makeDelaySecondes);
    }

/**
 * displaySplash Affiche des icones de départ
 *
 * Affiche des icones de l'École du WEB
 * 
 */
void MyOled::displaySplash(int makeDelaySecondes) {
    int indexMan = 0;
    int lastFramePosition = 12;
    int posX = 0;
    int posY = 20;
    clearDisplay();
    setTextSize(1);
    for (int positionX = -128; positionX <= lastFramePosition; positionX++) {
        drawLine(positionX + 128, 36, positionX + 128 - 12, 36, WHITE);
        drawBitmap(positionX + 128, 20, PushMan24x48Pointers[(++indexMan) % 7], 24, 48, WHITE);

        drawBitmap(0, 0, Cegep16x16, 16, 16, WHITE);
        printIt(22, 0, "CEGEP DE", false, 0);
        printIt(22, 9, "RIVIERE-DU-LOUP", false, 0);

        fillCircle(posX + 7 + positionX, posY + 2 + 3, 4, SSD1306_WHITE);
        fillRect(posX + positionX, posY + 10 + 3, 5, 20, SSD1306_WHITE);      //Partie 1 du logo
        fillRect(posX + positionX + 10, posY + 10 + 3, 5, 20, SSD1306_WHITE); //Partie 1 du logo
        printIt(posX + positionX + 24, posY + 8, "TECHNIQUES  DE", false, 0);
        printIt(posX + positionX + 24, posY + 18, "L'INFORMATIQUE", false, 0);
        printIt(posX + positionX + 24, posY + 28, "-ECOLE DU WEB-", false, 0);
        display();
        delay(makeDelaySecondes / 128);
        clearDisplay();
        }
    delay(makeDelaySecondes * 2);
    }
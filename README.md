# ESP32Wifi

# Prérequis
- Esp32
- DHT22
- 3 LEDs
- Oled display (I2C)

# Librairies utilisées

-- Pour le Wifi

      ESPAsyncWebServer-esphome                   (Pour accéder au Wifi)
      AsyncTCP-esphome                            (Pour utiliser les fonctionnalités TCP)
      bblanchon/ArduinoJson@^6.17.2               (Pour accéder au fonctionnalités Json)

-- Pour l'écran OLED

      Adafruit SSD1306                            (Pour accéder au fonctionnalités de l'écran OLED)
      Adafruit GFX Library                        (Pour accéder au fonctionnalités de l'écran OLED)
      Adafruit BusIO                              (Pour accéder au fonctionnalités de l'écran OLED)

-- Autres librairies (à copier dans le répertoire lib)
         WifiManagerDevelopment
            Remarques
            Pour trouver le WifiManager (dans la branche development)
            https://github.com/tzapu/WiFiManager/tree/development
            Ne pas oublier d'appuyez sur l'ampoule et choisir : ajouter Lib
                    /lib/DHT/DHT.cpp
        Pour obtenir la température
        float getTemperature()
    
-- Fonctions utiles (utilitaires)
        /lib/MYLIB/myFunctions.cpp
            //Pour vérifier plus simplement que deux chaines sont identiques
            bool isEqualString(std::string line1, std::string line2)
            
            //Pour extraire une partie d'une chaine de caractères avec l'aide d'un index
            std::string getValue(std::string data, char separator, int index).
            
            //Pour remplacer plus facilement une sous chaine
            bool replaceAll(std::string& source, const std::string& from, const std::string& to)
            
            //Pour obtenir un chaine aléatoire d'une certaine longeur
            std::string get_random_string(unsigned int len)
            
 - Classes du système
         
        MyServer                        V1.0    Pour la gestion des routes pour le site WEB
            /data                               Répertoire qui contient les fichiers du site WEB 
                index.html              V1.0    Page index du site WEB
                index.css               V1.0    CSS
                script.js               V1.0    JS (fonctions JavaScript)

# Connection à L'api
167.114.96.59

Doc: http://167.114.96.59/doc

Accès aux informations des bois avec :  http://167.114.96.59:8080/bois/ ou http://167.114.96.59:8080/bois/:id

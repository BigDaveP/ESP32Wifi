/**
    Gestion d'un serveur WEB
    @file MyServer.cpp
    @author Alain Dubé
    @version 1.1 20/11/20 
*/
#include <Arduino.h>
#include "MyServer.h"
#include <ArduinoJson.h>

#include <HttpClient.h>
#include "soc/timer_group_struct.h"
#include "soc/timer_group_reg.h"

HTTPClient http;
String response = "";
const unsigned int serverToPort = 8080; //port du serveur WEB
using namespace std;

typedef std::string (*CallbackType)(std::string);
CallbackType MyServer::ptrToCallBackFunction = NULL;

//Exemple pour appeler une fonction CallBack
void MyServer::initCallback(CallbackType callback) {
    ptrToCallBackFunction = callback;
    }

void MyServer::initAllRoutes() { 
    currentTemperature = 3.3f;

    //Initialisation du SPIFF.
    if (!SPIFFS.begin(true)) {
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
        }

    //Route initiale (page html)
    this->on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/index.html", "text/html");
        });

    //Route du script JavaScript
    this->on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/script.js", "text/javascript");
        });

    this->on("/index.css", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/index.css", "text/css");
        });

    this->on("/oui", HTTP_GET, [](AsyncWebServerRequest *request) {
        if (ptrToCallBackFunction) (*ptrToCallBackFunction)("button getlisteBois");
            HTTPClient http;          
            String serverTo = "http://167.114.96.59:2223/bois"; //adresse du serveur WEB
            bool httpInitResult = http.begin(serverTo);
            if(!httpInitResult){
                Serial.println("Erreur de connection au serveur");
            }
            else{
                http.addHeader("Authorization", "Bearer 2e550451f21d19dc726b54e574d6d6b76665ade19f703af2a26384cf2d3adf9a8e9a5e28270471fa2a6a3c1982aafa2be5ff14179cbfbf299a189846dfc45101");
                
                int httpCode = http.GET();
                Serial.println("httpCode: " + String(httpCode));
                if(httpCode > 0) {
                    if(httpCode == HTTP_CODE_OK) {
                        String infoBois;
                        String payload = http.getString();
                        Serial.println(payload);
                        StaticJsonDocument<2048> doc;
                        deserializeJson(doc, payload);
                        JsonObject elem = doc.as<JsonObject>();
                        String results = elem["results"].as<String>();

                        Serial.println("Payload: " + payload);
                        request->send(200, "text/plain", payload);
                        }
                    }
                    else{
                        request->send(401, "text/plain", "Erreur de connection au serveur");
                    }
                
                http.end(); 
            }
            
        });
        
        
   
    this->onNotFound([](AsyncWebServerRequest *request){
        request->send(404, "text/plain", "Page Not Found");
        });
    
    this->begin();
};
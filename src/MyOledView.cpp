/**
    Gestion d'une VUE pour le OLed  
    @file MyOledView.cpp
    @author Alain Dubé
    @version 1.1 21/09/20 
*/
#include <Arduino.h>
#include "MyOledView.h"
using namespace std;

void MyOledView::setParams(string tag, string value){
    int tagPos = findTag(tag);
    if(tagPos==0) {
        params.push_back(tag);
        params.push_back(value);
        return;
        }
     params[tagPos] = value; 
    }

string MyOledView::getTag(string tag){
    int tagPos = findTag(tag);
    if(tagPos!=0)  return(params[tagPos]);
    return("");
    }

int MyOledView::findTag(string tag){
    for (unsigned i=0; i<params.size(); i+=2){
        if (string(params[i].c_str()).compare(tag) == 0) {
            return(i+1);
         }
    }
    return(0);
    }

void MyOledView::init(std::string _id) {

    Serial.println("Init dans MyOledView");
    myId = _id;
    params.clear();
    }

std::string MyOledView::id() {
    return(myId);
    }
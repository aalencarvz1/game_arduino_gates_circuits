#include <MemoryUsage.h>
#include "TouchScreenController.h"
#include "Container.h"
#include "ClickEvent.h"
#include "Screens.h"
#include "ScreenInitialMenu.h"

bool inClick = false; //AVOID LOOP ON DISPATH MULTIPLE CLICKS AT SOME TIME

void setup() {
  Serial.begin(9600);
  //Serial.println(F("INITIALIZING..."));  
  TouchScreenController::init(); 
  TouchScreenController::tft.fillScreen(TFT_BLACK);
  //FREERAM_PRINT;
  Screens::goTo(ScreenInitialMenu::SCREEN_ID);
  /*Container* t = new Container(nullptr,50,50,50);
  t->setBackgroundColor(TFT_RED);
  t->createBorder(2,TFT_BLUE);
  t->setText("teste");
  //t->setRoundedRadius(10);
  t->getBorder()->setPadding(5);
  t->setOnClick([](){
    //Serial.println("detectado clique");
  });
  t->draw();
  /*delete t;
  t = nullptr;*/
  //FREERAM_PRINT;
}

void loop() {
  TSPoint p = TouchScreenController::ts.getPoint();

  //stackoverflow credits: restore status of shared pins to avoid not responding tft call functions
  pinMode(TouchScreenController::TS_XM,OUTPUT);
  pinMode(TouchScreenController::TS_YP,OUTPUT);

  //clicked
  if (p.z > 0 && !inClick) {
    inClick = true;
    DPoint uiP;
    int16_t px2 = p.x;
    int16_t py2 = p.y;
    uiP.x = map(p.y, TouchScreenController::TS_MINX, TouchScreenController::TS_MAXX, TouchScreenController::tft.width(),0);
    uiP.y = map(px2, TouchScreenController::TS_MINY, TouchScreenController::TS_MAXY, TouchScreenController::tft.height(),0);
    //Serial.println("clicked on " + String(p.x) + "," + String(p.y) + " > " +String(uiP.x) + "," + String(uiP.y) + " " + String(inClick));

    //loop troght event receptors array, checking if is point in area of element
    Node<ClickEvent>* current = TouchScreenController::clickEvents->tail;  // Começa pelo último nó (tail)
    
    while (current != nullptr) {
      if (current->data != nullptr) {
        //Serial.println("checking event id "+String(current->data->getId()));
        if (current->data->checkClickEvent(uiP) == true) {
          break;//not bubble event
        }
      }
      current = current->prev;
    }
    inClick = false;
  }  
  ////FREERAM_PRINT; //show free memory
  delay(100); //to preserve resources, disable in production

}

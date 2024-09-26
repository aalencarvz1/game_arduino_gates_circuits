#ifndef TOUCHSCREENCONTROLLER_H
#define TOUCHSCREENCONTROLLER_H

#include <MCUFRIEND_kbv.h>  // Biblioteca MCUFRIEND_kbv
#include <TouchScreen.h>   // Biblioteca para touchscreen
#include "LambdaCallback.h"
#include "Utils.h"
#include "DoubleLinkedList.h"
#include "VisualComponent.h"


//para armazenar informações referente ao dimensionmanto (bounds) de textos em tela
struct TextInfo{
  double x, y;  // Variáveis para armazenar a posição do canto superior esquerdo
  double w, h;  
};


struct TouchScreenClickEvent {
  int id = -1;
  VisualComponent* component = nullptr;
  bool enabled = true;
  void (*staticOnClick)() = nullptr;
  ICallback* onClickCallback = nullptr;  // Ponteiro para o callback

  TouchScreenClickEvent(
    VisualComponent* pComponent = nullptr,
    void (*pStaticOnClick)() = nullptr,
    ICallback* pOnClickCallback = nullptr
  );  

  ~TouchScreenClickEvent();
  bool checkClickEvent(DPoint point);
};


struct TouchScreenController {
  static int nextEventId;

  // Definição dos pinos do touchscreen
  static const int TS_XP  = 8;  // Substitua pelo pino correto
  static const int TS_YP  = A3;//17;//A3;  // Substitua pelo pino correto
  static const int TS_XM  = A2;//16;//A2;  // Substitua pelo pino correto
  static const int TS_YM  = 9;  // Substitua pelo pino correto

  // Definição das variáveis de calibração do touchscreen
  static const int TS_MINX  = 80;
  static const int TS_MAXX  = 960;
  static const int TS_MINY  = 100;
  static const int TS_MAXY  = 930;

  // Configuração do touchscreen
  static TouchScreen ts;

  static MCUFRIEND_kbv tft;

  static DoubleLinkedList<TouchScreenClickEvent>* touchScreenClickEvents;// = new DoubleLinkedList<TouchScreenClickEvent>();


  static void init();
  static int getNextEventId();
  static TextInfo drawCenteredText(char* text, double y = 0, double centerX = TouchScreenController::tft.width() * 1.0 / 2.0, double textSize = 2, int color = TFT_WHITE);
  static void drawRoundButton(double x,double y,double r,int color,char* text="", bool hasCenterPlay=true, bool hasBorder=true, double textDistance = 20, void (*onClick)() = nullptr);
  static void drawSmoothArc(double x_center, double y_center, double radius, double start_angle, double end_angle, uint16_t color = TFT_WHITE);
  static CircleInfo drawArcFromArrow(double x1, double y1, double x2, double y2, double arcHeight, int color = TFT_WHITE);
  static void drawRoundedPlay(double cx,double cy,double r,double round = 0,int backgroundColor = TFT_BLACK,int color = TFT_WHITE,double multiplier = 1);

};

#endif // TOUCHSCREENCONTROLLER_H
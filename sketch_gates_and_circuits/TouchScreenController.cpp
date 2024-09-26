#include "TouchScreenController.h"
#include <math.h>


//STATIC INITIALIZATIONS
int TouchScreenController::nextEventId = -1;
MCUFRIEND_kbv TouchScreenController::tft;
TouchScreen TouchScreenController::ts = TouchScreen(TouchScreenController::TS_XP, TouchScreenController::TS_YP, TouchScreenController::TS_XM, TouchScreenController::TS_YM, 300);
DoubleLinkedList<TouchScreenClickEvent>* TouchScreenController::touchScreenClickEvents = nullptr;


/**
* TouchScreenClickEvent
*/
TouchScreenClickEvent::TouchScreenClickEvent(
  VisualComponent* pComponent,
  void (*pStaticOnClick)(),
  ICallback* pOnClickCallback
) :
  component(pComponent),
  staticOnClick(pStaticOnClick),
  onClickCallback(pOnClickCallback)
{
  Serial.println(F("INIT TouchScreenClickEvent::TouchScreenClickEvent"));
  id = TouchScreenController::getNextEventId();
  TouchScreenController::touchScreenClickEvents->add(this);
  Serial.println(F("END TouchScreenClickEvent::TouchScreenClickEvent"));
};

TouchScreenClickEvent::~TouchScreenClickEvent(){
  Serial.println(F("INIT TouchScreenClickEvent::~TouchScreenClickEvent"));
  /*if (staticOnClick != nullptr) { cannot delete function
    delete staticOnClick;
  }*/
  if (onClickCallback != nullptr) {
    delete onClickCallback;
  }
  TouchScreenController::touchScreenClickEvents->remove(this,false);
  Serial.println(F("END TouchScreenClickEvent::~TouchScreenClickEvent"));
}

//verifica se o elemento foi clicado com base no ponto central e raio definido
bool TouchScreenClickEvent::checkClickEvent(DPoint point) {
  Serial.println(F("INIT TouchScreenClickEvent::checkClickEvent"));
  bool result = false;
  if (enabled) {
    if (component != nullptr) {  
      if (component->isCircular) {
        if (abs(component->getX() - point.x) <= component->getR() && abs(component->getY() - point.y) <= component->getR()) {
          result = true;
        }
      } else {
        
      }  
      if (result = true) {    
        if (onClickCallback != nullptr) {
          onClickCallback->call();  // Chama a função encapsulada
        } else if (staticOnClick != nullptr) {
          staticOnClick();
        }
        Serial.println(F("END TouchScreenClickEvent::checkClickEvent"));
      }
    }
  }
  Serial.println(F("END TouchScreenClickEvent::checkClickEvent"));
  return result;
};


/**
* TouchScreenController
*/
void TouchScreenController::init(){
    // Configuração do touchscreen
    // Inicializa o TFT    
    uint16_t identifier = tft.readID();
    Serial.println("TFT SHIELD IDENTIFIER: "+String(identifier));
    if (identifier == 0x9325 || identifier == 0x9341 || identifier == 0x9486 || identifier == 0x7796) {
      tft.begin(identifier);
    } else {
      tft.begin(0x9486);  // Força o uso de um controlador comum, se necessário
    }
    tft.setRotation(1);  // Ajuste a rotação conforme necessário
    touchScreenClickEvents = new DoubleLinkedList<TouchScreenClickEvent>("TouchScreenClickEvent");
};

int TouchScreenController::getNextEventId(){
  nextEventId++;
  return nextEventId;
}

TextInfo TouchScreenController::drawCenteredText(char* text, double y, double centerX, double textSize, int color) {
    // Defina o tamanho da fonte
    tft.setTextSize(textSize);
    tft.setTextColor(color);

    // Calcule a largura e altura do texto com base no tamanho da fonte
    double textWidth = strlen(text) * 6.0 * textSize;  // Cada caractere tem aproximadamente 6px de largura na fonte padrão
    double textHeight = 8.0 * textSize;  // A altura da fonte padrão é de aproximadamente 8px

    // Calcule as coordenadas para centralizar o texto
    double x = centerX - (textWidth / 2.0);
    
    // Desenhe o texto no TFT
    tft.setCursor(x, y);
    tft.print(text);

    // Retorne as informações do texto
    TextInfo result;
    result.x = x;
    result.y = y;
    result.w = textWidth;
    result.h = textHeight;
    return result;
};

void TouchScreenController::drawRoundButton(double x,double y,double r,int color,char* text, bool hasCenterPlay, bool hasBorder, double textDistance = 20, void (*onClick)()) {
  if (hasBorder) {
    tft.drawCircle(x,y,r,color);
    tft.drawCircle(x,y,r-1.0,color);
    tft.fillCircle(x,y,r*0.8,color);
  } else {
    tft.fillCircle(x,y,r,color);
  }

  DPoint p1;
  double playR = r * 0.3;
  p1.x = (x - playR) + (r * 0.1);
  if (hasCenterPlay) {
    int playColor = TFT_BLACK;    
    double arred = r * 0.05;

    //define os pontos do triangulo do play
    DPoint p2,p3;    
    p1.y = y - playR;
    p2.x = p1.x;
    p2.y = y + playR;
    p3.x = x + playR + (r * 0.1);
    p3.y = y;

    //desenha o play
    tft.fillTriangle(p1.x,p1.y, p2.x,p2.y, p3.x,p3.y , playColor);

    //desenha os cantos arredondados
    tft.fillCircle(p1.x,p1.y,arred*2.0, color);
    tft.fillCircle(p1.x+arred*0.8,p1.y+arred*1.70,arred, playColor);
    tft.fillCircle(p2.x,p2.y,arred*2.0, color);
    tft.fillCircle(p2.x+arred*0.8,p2.y-arred*2,arred, playColor);
    tft.fillCircle(p3.x,p3.y,arred*2.0, color);
    tft.fillCircle(p3.x-arred*2.3,p3.y,arred, playColor);
  }
  if (text != "") {
    drawCenteredText(text,y+r+textDistance,x);
  }
  if (onClick != nullptr) {
    FREERAM_PRINT;
    new TouchScreenClickEvent(nullptr,onClick);
    FREERAM_PRINT;
  }
};

void TouchScreenController::drawSmoothArc(double x_center, double y_center, double radius, double start_angle, double end_angle, uint16_t color) {
  double angle;   // Ângulo atual em radianos
  double x_last = -1.0, y_last = -1.0;  // Últimas coordenadas desenhadas para garantir continuidade

  // Convertendo ângulos de graus para radianos
  double start_rad = start_angle * (PI / 180.0);
  double end_rad = end_angle * (PI / 180.0);

  // Caminhar ao longo do arco, aumentando o ângulo gradualmente
  for (angle = start_rad; angle <= end_rad; angle += 0.005) {
    double x = x_center + radius * cos(angle);  // Cálculo da coordenada X
    double y = y_center + radius * sin(angle);  // Cálculo da coordenada Y
    //TouchScreenController::tft.drawPixel(x, y, color);
    // Desenha o pixel apenas se for uma nova coordenada (evitar sobreposição)
    if (x != x_last || y != y_last) {
      tft.drawPixel(x, y, color);  // Desenha o pixel na posição (x, y)
      x_last = x;
      y_last = y;
    }
  }
};

CircleInfo TouchScreenController::drawArcFromArrow(double x1, double y1, double x2, double y2, double arcHeight, int color) {  
  DPoint p1,p2;
  p1.x = x1;
  p1.y = y1;
  p2.x = x2;
  p2.y = y2;

  double width = sqrt(pow(abs(x2-x1),2.0) + pow(abs(y2-y1),2.0));
  double r = 0.0;
  double baseAdjust = 0.0;
  double centralAngle = 270.0; //arco na horizontal, flexa na vertical y1 = y2 --- 
  if (y1 != y2) {
    if (x1 == x2) {// arco na vertical, flexa na horizontal |      
      centralAngle = 0.0;
      if (y1 > y2) {
        centralAngle = 180.0; //arco na vertical, flexa na horizontal, apontando para a esquerda
      }
    } else {
      double hT = abs(y1-y2); //cateto vertical
      double wT = abs(x1-x2); //cateto horizontal
      double a1 = atan(hT/wT) * (180.0 / M_PI); //angulo oposto ao cateto vertical
      Serial.println("ht="+String(hT)+",wt="+String(wT)+",a1="+String(a1));
      if (x1 <= x2) { //flexa/arco para esquerda e para cima
        if (y1 <= y2) { //de 180 a 360
          centralAngle = 360.0 - (90-a1);
        } else /*if (y1 > y2)*/ {
          centralAngle = 180.0 + (90-a1);
        } 
      } else {//flexa do arco para esquerda
        if (y1 <= y2) {
          centralAngle = 90-a1;
        } else {
          centralAngle = 90.0 + (90-a1);
        }
      }
    }
  } else if (x1 > x2) {
    centralAngle = 90.0; //flexa apontando para baixo
  }
  if (arcHeight >= width/2.0) {
    r = width / 2.0;
    baseAdjust = arcHeight - r;
  } else {
    r = (arcHeight * arcHeight + pow(width/2.0,2.0)) / (2.0 * arcHeight);
  }
  double py2 = pow(r,2.0);
  py2 = pow(r,2.0) - pow(width /2.0,2.0);
  py2 = sqrt(py2);
  double arcAngle = getArcAngle(width,r);
  double startAngle = centralAngle-(arcAngle/2.0);

  DPoint pc = calcularP3(width,r,r,p1,p2);
  CircleInfo result;
  result.x = pc.x;
  result.y = pc.y;
  result.r = r;
  drawSmoothArc(pc.x,pc.y,r,startAngle,startAngle+arcAngle,color);    
  return result;
};

static void TouchScreenController::drawRoundedPlay(double cx,double cy,double radius,double round,int backgroundColor,int color,double multiplier) {
  double angulo1 = 0;  // Vértice apontando para a direita (ponta do play)
  double angulo2 = 2 * M_PI / 3;  // 120 graus (em radianos)
  double angulo3 = 4 * M_PI / 3;  // 240 graus (em radianos)

  //define os pontos do triangulo do play
  // Coordenadas dos três vértices (p1, p2, p3)
  double x1 = cx + radius * cos(angulo1) * multiplier;
  double y1 = cy + radius * sin(angulo1) * multiplier;
  
  double x2 = cx + radius * cos(angulo2) * multiplier;
  double y2 = cy + radius * sin(angulo2) * multiplier;
  
  double x3 = cx + radius * cos(angulo3) * multiplier;
  double y3 = cy + radius * sin(angulo3) * multiplier;
  

  //desenha o play
  tft.fillTriangle(x1,y1, x2,y2, x3,y3 , color);
  if (round > 0) {
    //desenha os cantos arredondados
    tft.fillCircle(x1,y1,round*1.5, backgroundColor);
    tft.fillCircle(x1-round*1.8*multiplier,y1,round, color);
    tft.fillCircle(x2,y2,round*1.5, backgroundColor);
    tft.fillCircle(x2+round*multiplier,y2-round*1.75*multiplier,round, color);
    tft.fillCircle(x3,y3,round*1.5, backgroundColor);
    tft.fillCircle(x3+round*multiplier,y3+round*1.75*multiplier,round, color);
  }
}




//made for arduino with 2.4" touch screen
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;       // hard-wired for UNO shields anyway.
#include <TouchScreen.h>

typedef struct LinkedListElement
{
  int x = -10;
  int y = -10;
  LinkedListElement* next = NULL;
};
LinkedListElement* getLast(LinkedListElement* s)
{
  LinkedListElement* ret = s;
  while (ret->next != NULL)
    ret = ret->next;
  return ret;
}

int foodX;
int foodY;
int xV = 0;
int yV = 0;
int length = 1;
long long lastTime = 0;
LinkedListElement* snakeHead = new LinkedListElement;

char *name = "Please Calibrate.";  //edit name of shield
const int XP=6,XM=A2,YP=A1,YM=7; //ID=0x9341
const int TS_LEFT=77,TS_RT=900,TS_TOP=929,TS_BOT=107;

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
TSPoint tp;

#define MINPRESSURE 200
#define MAXPRESSURE 1000


uint16_t ID;
uint8_t Orientation = 1;    //PORTRAIT

// Assign human-readable names to some common 16-bit color values:
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
void setup()
{
  randomSeed(analogRead(0));
  uint16_t tmp;
    tft.reset();
    ID = tft.readID();
    tft.begin(ID);
    tft.setRotation(Orientation);

    tft.fillScreen(BLACK);
    length = 1;
    snakeHead->next = NULL;
    snakeHead->x = 16;
    snakeHead->y = 12;
    foodX = random(3,30);
    foodY = random(3,20);
    tft.fillRect(snakeHead->x * 10, snakeHead->y * 10, 10, 10, GREEN);
    tft.fillRect(foodX * 10, foodY * 10, 10, 10, RED);
    
    delay(1000);

}

void loop() 
{
   if(millis() - lastTime > 100)
   {
      lastTime = millis();
      
      LinkedListElement* temp = snakeHead;

      snakeHead = getLast(snakeHead);

      tft.fillRect(snakeHead->x * 10,snakeHead->y * 10,10,10,BLACK);

      snakeHead->x = temp->x + xV;

      snakeHead->y = temp->y + yV;

      if (snakeHead->next != snakeHead)
      {
        snakeHead->next = temp;
        LinkedListElement* iter = snakeHead;
        while (iter->next != snakeHead)
          iter = iter->next;
        iter->next = NULL;
      }

      if (foodX == snakeHead->x && foodY == snakeHead->y)
      {
        tft.fillRect(foodX * 10,foodY * 10,10,10,GREEN);
        foodX = random(3,30);
        foodY = random(3,20);
        tft.fillRect(foodX * 10,foodY * 10,10,10,RED);
        getLast(snakeHead)->next = new LinkedListElement;
        length++;
      }

      LinkedListElement* iter = snakeHead;

      while (iter  != NULL)
      {
        if (snakeHead != iter && snakeHead->x == iter->x && snakeHead->y == iter->y)
        {
          //clear memory used by body on snake death
          iter = snakeHead->next;
          while (iter != NULL)
          {
            temp = iter->next;
            delete iter;
            iter = temp;
          }
          tft.fillScreen(BLACK);
          length = 1;
          snakeHead->next = NULL;
          snakeHead->x = 16;
          snakeHead->y = 12;
          foodX = random(3,30);
          foodY = random(3,20);
          tft.fillRect(snakeHead->x * 10, snakeHead->y * 10, 10, 10, GREEN);
          tft.fillRect(foodX * 10, foodY * 10, 10, 10, RED);
    
          break;
        }
        tft.fillRect(iter->x * 10, iter->y * 10,10,10, GREEN);
        iter = iter->next;
      }
   }
  uint16_t xpos, ypos;  //screen coordinates
    tp = ts.getPoint();   //tp.x, tp.y are ADC values
  //  tp.x = tft.width() - tp.x;
   // tp.y = tft.height() - tp.y;
    // if sharing pins, you'll need to fix the directions of the touchscreen pins
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);

     if (tp.z > MINPRESSURE && tp.z < MAXPRESSURE){
           xpos = map(tp.y, TS_BOT ,TS_TOP, 0, tft.width());
     ypos = map(tp.x, TS_RT, TS_LEFT, 0, tft.height());
      if(xpos > 160 && ypos < 180 && ypos > 60)
      {
        xV = 1;
        yV = 0;
      }
      if(xpos <= 160 && ypos < 180 && ypos > 60)
      {
        xV = -1;
        yV = 0;
      }
      if(ypos > 160 && xpos > 80 && xpos < 240)
      {
        xV = 0;
        yV = 1;
      }
      if(ypos <= 160 && xpos > 80 && xpos < 240)
      {
        xV = 0;
        yV = -1;
      }
     }
    

}

#include <gamma.h>
#include <RGBmatrixPanel.h>
#include <Adafruit_GFX.h>

//define the wiring of the LED screen
const uint8_t CLK = 8;
const uint8_t LAT = A3;
const uint8_t OE = 9;
const uint8_t A = A0;
const uint8_t B = A1;
const uint8_t C = A2;

//define the wiring of the inputs
const int POTENTIOMETER_PIN_NUMBER = 5;
const int BUTTON_PIN_NUMBER = 10;

//a global variable that represents the LED screen
RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);

//a global array that represents the pixels in the board
uint8_t freeze[20][16];

//a global array that represents the shape
bool array[8][8];

//the following functions are for printing messages
void print_lives(int lives);
void game_over();
void print_tetris();

class Color  {
  public:
    int red;
    int green;
    int blue;
    Color() {
      red = 0;
      green = 0;
      blue = 0;
    }
    Color(int r, int g, int b) {
      red = r;
      green = g;
      blue = b;
    }
    uint16_t to_333() const {
      return matrix.Color333(red, green, blue);
    }
};

const Color BLACK(0, 0, 0);
const Color RED(7, 0, 0);
const Color ORANGE(7, 4, 0);
const Color YELLOW(7, 7, 0);
const Color GREEN(0, 7, 0);
const Color BLUE(0, 0, 7);
const Color PURPLE(7, 0, 7);
const Color WHITE(7, 7, 7);
const Color LIME(4, 7, 0);
const Color AQUA(0, 7, 7);

class Shape {
  public:
    //constructor
    Shape() {
      x = 0;
      y = 0;
      orientation = 1;
      pushed = false;
      int i, j;
      for (i = 0; i < 8; i++)  {
        for (j = 0; j < 8; j++) {
          array[i][j]= false;
        }
      }
   }
  
   //sets values for x, y and orientation
   Shape(int x_arg, int y_arg, int o_arg) {
     x = x_arg;
     y = y_arg;
     orientation = o_arg;
     pushed = false;
   }
  
    //sets values for private data members
    void initialize(int x_arg, int y_arg, int o_arg) {
      x = x_arg;
      y = y_arg;
      orientation = o_arg;
      pushed = false;
      int i, j;
      for (i = 0; i < 8; i++)  {
        for (j = 0; j < 8; j++) {
          array[i][j]= false;
        }
      }
    }

   //getters
   int get_x() const {
     return x;
   }

   int get_y() const {
     return y;
   }

   int get_orientation() const {
     return orientation;
   }

   int get_width() const  {
    return width;
   }

   int get_height() const {
    return height;
   }

   bool has_been_pushed() const  {
    return pushed;
   }

   //setters
   void set_y(int y_arg) {
     y = y_arg;
   }

   void set_orientation(int o_arg) {
      orientation = o_arg;
      int i, j;
      for (i = 0; i < 8; i++)  {
        for (j = 0; j < 8; j++) {
          array[i][j]= false;
        }
      }
   }
    
   void set_x(int x_arg) {
     x = x_arg;
   }
   
   void change_pushed(bool p) {
    pushed = p;
   }
    
    //SHAPE 1------------------------------------------------------------------------------------
    void move1() {
     erase1(orientation, x, y);
     x++;
     drawShape1(orientation, x, y);
    }

   void erase1(int orientation, int xcoordinate, int ycoordinate)  {
        switch(orientation) {
         case 1:
            drawBox(2 + xcoordinate, 0 + ycoordinate, BLACK);
            drawBox(4 + xcoordinate, 0 + ycoordinate, BLACK);
            drawBox(2 + xcoordinate, 2 + ycoordinate, BLACK);
            drawBox(0 + xcoordinate, 2 + ycoordinate, BLACK);
           break;
         case 2:
            drawBox(0 + xcoordinate, 0 + ycoordinate, BLACK);
            drawBox(0 + xcoordinate, 2 + ycoordinate, BLACK);
            drawBox(2 + xcoordinate, 2 + ycoordinate, BLACK);
            drawBox(2 + xcoordinate, 4 + ycoordinate, BLACK);
            break;
       }
     int i, j;
      for (i = 0; i < 8; i++)  {
        for (j = 0; j < 8; j++) {
          array[i][j]= false;
        }
      }
    }

  
    void drawShape1(int orientation, int xcoordinate, int ycoordinate)  {
      switch(orientation) {
        case 1:
          drawBox(2 + xcoordinate, 0 + ycoordinate, BLUE);
          drawBox(4 + xcoordinate, 0 + ycoordinate, BLUE);
          drawBox(2 + xcoordinate, 2 + ycoordinate, BLUE);
          drawBox(0 + xcoordinate, 2 + ycoordinate, BLUE);
          arrayBox(2, 0);
          arrayBox(4, 0);
          arrayBox(2, 2);
          arrayBox(0, 2);
          width = 4;
          height = 6;
          break;
        case 2:
          drawBox(0 + xcoordinate, 0 + ycoordinate, BLUE);
          drawBox(0 + xcoordinate, 2 + ycoordinate, BLUE);
          drawBox(2 + xcoordinate, 2 + ycoordinate, BLUE);
          drawBox(2 + xcoordinate, 4 + ycoordinate, BLUE);
          arrayBox(0 , 0);
          arrayBox(0, 2);
          arrayBox(2 , 2);
          arrayBox(2 , 4);
          width = 6;
          height = 4;
          break;
      }
    }

    void freeze1(int orientation, int xcoordinate, int ycoordinate) {
      switch(orientation) {
        case 1:
          setBox(2 + xcoordinate, 0 + ycoordinate, WHITE);
          setBox(4 + xcoordinate, 0 + ycoordinate, WHITE);
          setBox(2 + xcoordinate, 2 + ycoordinate, WHITE);
          setBox(0 + xcoordinate, 2 + ycoordinate, WHITE);
          break;
        case 2:
          setBox(0 + xcoordinate, 0 + ycoordinate, WHITE);
          setBox(0 + xcoordinate, 2 + ycoordinate, WHITE);
          setBox(2 + xcoordinate, 2 + ycoordinate, WHITE);
          setBox(2 + xcoordinate, 4 + ycoordinate, WHITE);
          break;
      }
    }

//SHAPE 2-----------------------------------------------------------------------------------
  void move2() {
      erase2(orientation, x, y);
      x++;
      drawShape2(orientation, x, y);
    }

  void erase2(int orientation, int xcoordinate, int ycoordinate)  {
      switch(orientation) {
        case 1:
          drawBox(0 + xcoordinate, 0 + ycoordinate, BLACK);
          drawBox(2 + xcoordinate, 0 + ycoordinate, BLACK);
          drawBox(2 + xcoordinate, 2 + ycoordinate, BLACK);
          drawBox(4 + xcoordinate, 2 + ycoordinate, BLACK);
          break;
        case 2:
          drawBox(0 + xcoordinate, 2 + ycoordinate, BLACK);
          drawBox(0 + xcoordinate, 4 + ycoordinate, BLACK);
          drawBox(2 + xcoordinate, 0 + ycoordinate, BLACK);
          drawBox(2 + xcoordinate, 2 + ycoordinate, BLACK);
          break;
      }
      int i, j;
      for (i = 0; i < 8; i++)  {
        for (j = 0; j < 8; j++) {
          array[i][j]= false;
        }
      }
    }
    
  void drawShape2(int orientation, int xcoordinate, int ycoordinate) {
      switch(orientation) {
        case 1:
          drawBox(0 + xcoordinate, 0 + ycoordinate, RED);
          drawBox(2 + xcoordinate, 0 + ycoordinate, RED);
          drawBox(2 + xcoordinate, 2 + ycoordinate, RED);
          drawBox(4 + xcoordinate, 2 + ycoordinate, RED);
          arrayBox(0, 0);
          arrayBox(2, 0);
          arrayBox(2, 2);
          arrayBox(4, 2);
          width = 4;
          height = 6;
          break;
        case 2:
          drawBox(0 + xcoordinate, 2 + ycoordinate, RED);
          drawBox(0 + xcoordinate, 4 + ycoordinate, RED);
          drawBox(2 + xcoordinate, 0 + ycoordinate, RED);
          drawBox(2 + xcoordinate, 2 + ycoordinate, RED);
          arrayBox(0, 2);
          arrayBox(0, 4);
          arrayBox(2, 0);
          arrayBox(2, 2);
          width = 6;
          height = 4;
          break;
      }
    }
void freeze2(int orientation, int xcoordinate, int ycoordinate) {
  switch(orientation) {
    case 1:
      setBox(0 + xcoordinate, 0 + ycoordinate, WHITE);
      setBox(2 + xcoordinate, 0 + ycoordinate, WHITE);
      setBox(2 + xcoordinate, 2 + ycoordinate, WHITE);
      setBox(4 + xcoordinate, 2 + ycoordinate, WHITE);
      break;
    case 2:
      setBox(0 + xcoordinate, 2 + ycoordinate, WHITE);
      setBox(0 + xcoordinate, 4 + ycoordinate, WHITE);
      setBox(2 + xcoordinate, 0 + ycoordinate, WHITE);
      setBox(2 + xcoordinate, 2 + ycoordinate, WHITE);
      break;
  }
}

//SHAPE 3 (Line) -----------------------------------------------------------------------------------
  void move3() {
      erase3(orientation, x, y);
      x++;
      drawShape3(orientation, x, y);
    }
    
  void erase3(int orientation, int xcoordinate, int ycoordinate)  {
      switch(orientation) {
        case 1:
          drawBox(0 + xcoordinate, 0 + ycoordinate, BLACK);
          drawBox(2 + xcoordinate, 0 + ycoordinate, BLACK);
          drawBox(4 + xcoordinate, 0 + ycoordinate, BLACK);
          break;
        case 2:
          drawBox(0 + xcoordinate, 0 + ycoordinate, BLACK);
          drawBox(0 + xcoordinate, 2 + ycoordinate, BLACK);
          drawBox(0 + xcoordinate, 4 + ycoordinate, BLACK);
          break;
      }
      int i, j;
      for (i = 0; i < 8; i++)  {
        for (j = 0; j < 8; j++) {
          array[i][j]= false;
        }
      }
    }

  void drawShape3(int orientation, int xcoordinate, int ycoordinate) {
      switch(orientation) {
        case 1:
          drawBox(0 + xcoordinate, 0 + ycoordinate, ORANGE);
          drawBox(2 + xcoordinate, 0 + ycoordinate, ORANGE);
          drawBox(4 + xcoordinate, 0 + ycoordinate, ORANGE);
          arrayBox(0, 0);
          arrayBox(2, 0);
          arrayBox(4, 0);
          width = 1;
          height = 6;
          break;
        case 2:
          drawBox(0 + xcoordinate, 0 + ycoordinate, ORANGE);
          drawBox(0 + xcoordinate, 2 + ycoordinate, ORANGE);
          drawBox(0 + xcoordinate, 4 + ycoordinate, ORANGE);
          arrayBox(0, 0);
          arrayBox(0, 2);
          arrayBox(0, 4);
          width = 6;
          height = 1;
          break;
      }
    }

    void freeze3(int orientation, int xcoordinate, int ycoordinate) {
      switch(orientation) {
        case 1:
          setBox(0 + xcoordinate, 0 + ycoordinate, WHITE);
          setBox(2 + xcoordinate, 0 + ycoordinate, WHITE);
          setBox(4 + xcoordinate, 0 + ycoordinate, WHITE);
          break;
        case 2:
          setBox(0 + xcoordinate, 0 + ycoordinate, WHITE);
          setBox(0 + xcoordinate, 2 + ycoordinate, WHITE);
          setBox(0 + xcoordinate, 4 + ycoordinate, WHITE);
          break;
      }
}

//SHAPE 4 (T) ---------------------------------------------------------------------------------------
  void move4() {
      erase4(orientation, x, y);
      x++;
      drawShape4(orientation, x, y);
    }

  void erase4(int orientation, int xcoordinate, int ycoordinate)  {
      switch(orientation) {
        case 1:
          drawBox(0 + xcoordinate, 0 + ycoordinate, BLACK);
          drawBox(0 + xcoordinate, 2 + ycoordinate, BLACK);
          drawBox(0 + xcoordinate, 4 + ycoordinate, BLACK);
          drawBox(2 + xcoordinate, 2 + ycoordinate, BLACK);
          break;
        case 2:
          drawBox(0 + xcoordinate, 2 + ycoordinate, BLACK);
          drawBox(2 + xcoordinate, 2 + ycoordinate, BLACK);
          drawBox(4 + xcoordinate, 2 + ycoordinate, BLACK);
          drawBox(2 + xcoordinate, 0 + ycoordinate, BLACK);
          break;
        case 3:
          drawBox(0 + xcoordinate, 2 + ycoordinate, BLACK);
          drawBox(2 + xcoordinate, 0 + ycoordinate, BLACK);
          drawBox(2 + xcoordinate, 2 + ycoordinate, BLACK);
          drawBox(2 + xcoordinate, 4 + ycoordinate, BLACK);
          break;
        case 4:
          drawBox(0 + xcoordinate, 0 + ycoordinate, BLACK);
          drawBox(2 + xcoordinate, 0 + ycoordinate, BLACK);
          drawBox(4 + xcoordinate, 0 + ycoordinate, BLACK);
          drawBox(2 + xcoordinate, 2 + ycoordinate, BLACK);
          break;
      }
      int i, j;
      for (i = 0; i < 8; i++)  {
        for (j = 0; j < 8; j++) {
          array[i][j]= false;
        }
      }
    }

  void drawShape4(int orientation, int xcoordinate, int ycoordinate) {
      switch(orientation) {
        case 1:
          drawBox(0 + xcoordinate, 0 + ycoordinate, YELLOW);
          drawBox(0 + xcoordinate, 2 + ycoordinate, YELLOW);
          drawBox(0 + xcoordinate, 4 + ycoordinate, YELLOW);
          drawBox(2 + xcoordinate, 2 + ycoordinate, YELLOW);
          arrayBox(0, 0);
          arrayBox(0, 2);
          arrayBox(0, 4);
          arrayBox(2, 2);
          width = 6;
          height = 4;
          break;
        case 2:
          drawBox(0 + xcoordinate, 2 + ycoordinate, YELLOW);
          drawBox(2 + xcoordinate, 2 + ycoordinate, YELLOW);
          drawBox(4 + xcoordinate, 2 + ycoordinate, YELLOW);
          drawBox(2 + xcoordinate, 0 + ycoordinate, YELLOW);
          arrayBox(0, 2);
          arrayBox(2, 2);
          arrayBox(4, 2);
          arrayBox(2, 0);
          width = 4;
          height = 6;
          break;
        case 3:
          drawBox(0 + xcoordinate, 2 + ycoordinate, YELLOW);
          drawBox(2 + xcoordinate, 0 + ycoordinate, YELLOW);
          drawBox(2 + xcoordinate, 2 + ycoordinate, YELLOW);
          drawBox(2 + xcoordinate, 4 + ycoordinate, YELLOW);
          arrayBox(0, 2);
          arrayBox(2, 0);
          arrayBox(2, 2);
          arrayBox(2, 4);
          width = 6;
          height = 4;
          break;
        case 4:
          drawBox(0 + xcoordinate, 0 + ycoordinate, YELLOW);
          drawBox(2 + xcoordinate, 0 + ycoordinate, YELLOW);
          drawBox(4 + xcoordinate, 0 + ycoordinate, YELLOW);
          drawBox(2 + xcoordinate, 2 + ycoordinate, YELLOW);
          arrayBox(0, 0);
          arrayBox(2, 0);
          arrayBox(4, 0);
          arrayBox(2, 2);
          width = 4;
          height = 6;
          break;
      }
    }

    void freeze4(int orientation, int xcoordinate, int ycoordinate) {
      switch(orientation) {
        case 1:
          setBox(0 + xcoordinate, 0 + ycoordinate, WHITE);
          setBox(0 + xcoordinate, 2 + ycoordinate, WHITE);
          setBox(0 + xcoordinate, 4 + ycoordinate, WHITE);
          setBox(2 + xcoordinate, 2 + ycoordinate, WHITE);
          break;
        case 2:
          setBox(0 + xcoordinate, 2 + ycoordinate, WHITE);
          setBox(2 + xcoordinate, 2 + ycoordinate, WHITE);
          setBox(4 + xcoordinate, 2 + ycoordinate, WHITE);
          setBox(2 + xcoordinate, 0 + ycoordinate, WHITE);
          break;
        case 3:
          setBox(0 + xcoordinate, 2 + ycoordinate, WHITE);
          setBox(2 + xcoordinate, 0 + ycoordinate, WHITE);
          setBox(2 + xcoordinate, 2 + ycoordinate, WHITE);
          setBox(2 + xcoordinate, 4 + ycoordinate, WHITE);
          break;
        case 4:
          setBox(0 + xcoordinate, 0 + ycoordinate, WHITE);
          setBox(2 + xcoordinate, 0 + ycoordinate, WHITE);
          setBox(4 + xcoordinate, 0 + ycoordinate, WHITE);
          setBox(2 + xcoordinate, 2 + ycoordinate, WHITE);
          break;
      }
    }
  //SHAPE 5 (L) ------------------------------------------------------------------------------------
    void move5() {
        erase5(orientation, x, y);
        x++;
        drawShape5(orientation, x, y);
      }
    void erase5(int orientation, int xcoordinate, int ycoordinate)  {
        switch(orientation) {
          case 1:
            drawBox(0 + xcoordinate, 0 + ycoordinate, BLACK);
            drawBox(2 + xcoordinate, 0 + ycoordinate, BLACK);
            drawBox(4 + xcoordinate, 0 + ycoordinate, BLACK);
            drawBox(4 + xcoordinate, 2 + ycoordinate, BLACK);
            break;
          case 2:
            drawBox(0 + xcoordinate, 0 + ycoordinate, BLACK);
            drawBox(0 + xcoordinate, 2 + ycoordinate, BLACK);
            drawBox(0 + xcoordinate, 4 + ycoordinate, BLACK);
            drawBox(2 + xcoordinate, 0 + ycoordinate, BLACK);
            break;
          case 3:
            drawBox(0 + xcoordinate, 0 + ycoordinate, BLACK);
            drawBox(0 + xcoordinate, 2 + ycoordinate, BLACK);
            drawBox(2 + xcoordinate, 2 + ycoordinate, BLACK);
            drawBox(4 + xcoordinate, 2 + ycoordinate, BLACK);
            break;
          case 4:
            drawBox(0 + xcoordinate, 4 + ycoordinate, BLACK);
            drawBox(2 + xcoordinate, 0 + ycoordinate, BLACK);
            drawBox(2 + xcoordinate, 2 + ycoordinate, BLACK);
            drawBox(2 + xcoordinate, 4 + ycoordinate, BLACK);
            break;
        }
        int i, j;
        for (i = 0; i < 8; i++)  {
         for (j = 0; j < 8; j++) {
           array[i][j]= false;
          }
       }
      }
      
    void drawShape5(int orientation, int xcoordinate, int ycoordinate) {
        switch(orientation) {
          case 1:
            drawBox(0 + xcoordinate, 0 + ycoordinate, AQUA);
            drawBox(2 + xcoordinate, 0 + ycoordinate, AQUA);
            drawBox(4 + xcoordinate, 0 + ycoordinate, AQUA);
            drawBox(4 + xcoordinate, 2 + ycoordinate, AQUA);
            arrayBox(0, 0);
            arrayBox(2, 0);
            arrayBox(4, 0);
            arrayBox(4, 2);
            width = 4;
            height = 6;
            break;
          case 2:
            drawBox(0 + xcoordinate, 0 + ycoordinate, AQUA);
            drawBox(0 + xcoordinate, 2 + ycoordinate, AQUA);
            drawBox(0 + xcoordinate, 4 + ycoordinate, AQUA);
            drawBox(2 + xcoordinate, 0 + ycoordinate, AQUA);
            arrayBox(0, 0);
            arrayBox(0, 2);
            arrayBox(0, 4);
            arrayBox(2, 0);
            width = 6;
            height = 4;
            break;
          case 3:
            drawBox(0 + xcoordinate, 0 + ycoordinate, AQUA);
            drawBox(0 + xcoordinate, 2 + ycoordinate, AQUA);
            drawBox(2 + xcoordinate, 2 + ycoordinate, AQUA);
            drawBox(4 + xcoordinate, 2 + ycoordinate, AQUA);
            arrayBox(0, 0);
            arrayBox(0, 2);
            arrayBox(2, 2);
            arrayBox(4, 2);
            width = 4;
            height = 6;
            break;
          case 4:
            drawBox(0 + xcoordinate, 4 + ycoordinate, AQUA);
            drawBox(2 + xcoordinate, 0 + ycoordinate, AQUA);
            drawBox(2 + xcoordinate, 2 + ycoordinate, AQUA);
            drawBox(2 + xcoordinate, 4 + ycoordinate, AQUA);
            arrayBox(0, 4);
            arrayBox(2, 0);
            arrayBox(2, 2);
            arrayBox(2, 4);
            width = 6;
            height = 4;
            break;
        }
      }

      void freeze5(int orientation, int xcoordinate, int ycoordinate) {
      switch(orientation) {
        case 1:
          setBox(0 + xcoordinate, 0 + ycoordinate, WHITE);
          setBox(2 + xcoordinate, 0 + ycoordinate, WHITE);
          setBox(4 + xcoordinate, 0 + ycoordinate, WHITE);
          setBox(4 + xcoordinate, 2 + ycoordinate, WHITE);
          break;
        case 2:
          setBox(0 + xcoordinate, 0 + ycoordinate, WHITE);
          setBox(0 + xcoordinate, 2 + ycoordinate, WHITE);
          setBox(0 + xcoordinate, 4 + ycoordinate, WHITE);
          setBox(2 + xcoordinate, 0 + ycoordinate, WHITE);
          break;
        case 3:
          setBox(0 + xcoordinate, 0 + ycoordinate, WHITE);
          setBox(0 + xcoordinate, 2 + ycoordinate, WHITE);
          setBox(2 + xcoordinate, 2 + ycoordinate, WHITE);
          setBox(4 + xcoordinate, 2 + ycoordinate, WHITE);
          break;
        case 4:
          setBox(0 + xcoordinate, 4 + ycoordinate, WHITE);
          setBox(2 + xcoordinate, 0 + ycoordinate, WHITE);
          setBox(2 + xcoordinate, 2 + ycoordinate, WHITE);
          setBox(2 + xcoordinate, 4 + ycoordinate, WHITE);
          break;
      }
    }
  
  //SHAPE 6 (Backwards L) ------------------------------------------------------------------------
      void move6() {
        erase6(orientation, x, y);
        x++;
        drawShape6(orientation, x, y);
      }
  
      void erase6(int orientation, int xcoordinate, int ycoordinate)  {
        switch(orientation) {
          case 1:
            drawBox(0 + xcoordinate, 2 + ycoordinate, BLACK);
            drawBox(2 + xcoordinate, 2 + ycoordinate, BLACK);
            drawBox(4 + xcoordinate, 2 + ycoordinate, BLACK);
            drawBox(4 + xcoordinate, 0 + ycoordinate, BLACK);
            break;
          case 2:
            drawBox(0 + xcoordinate, 0 + ycoordinate, BLACK);
            drawBox(2 + xcoordinate, 0 + ycoordinate, BLACK);
            drawBox(2 + xcoordinate, 2 + ycoordinate, BLACK);
            drawBox(2 + xcoordinate, 4 + ycoordinate, BLACK);
            break;
          case 3:
            drawBox(0 + xcoordinate, 0 + ycoordinate, BLACK);
            drawBox(0 + xcoordinate, 2 + ycoordinate, BLACK);
            drawBox(2 + xcoordinate, 0 + ycoordinate, BLACK);
            drawBox(4 + xcoordinate, 0 + ycoordinate, BLACK);
            break;
          case 4:
            drawBox(0 + xcoordinate, 0 + ycoordinate, BLACK);
            drawBox(0 + xcoordinate, 2 + ycoordinate, BLACK);
            drawBox(0 + xcoordinate, 4 + ycoordinate, BLACK);
            drawBox(2 + xcoordinate, 4 + ycoordinate, BLACK);
            break;
        }
        int i, j;
        for (i = 0; i < 8; i++)  {
          for (j = 0; j < 8; j++) {
            array[i][j]= false;
         }
        }
      }
  
      void drawShape6(int orientation, int xcoordinate, int ycoordinate) {
        switch(orientation) {
          case 1:
            drawBox(0 + xcoordinate, 2 + ycoordinate, GREEN);
            drawBox(2 + xcoordinate, 2 + ycoordinate, GREEN);
            drawBox(4 + xcoordinate, 2 + ycoordinate, GREEN);
            drawBox(4 + xcoordinate, 0 + ycoordinate, GREEN);
            arrayBox(0, 2);
            arrayBox(2, 2);
            arrayBox(4, 2);
            arrayBox(4, 0);
            width = 4;
            height = 6;
            break;
          case 2:
            drawBox(0 + xcoordinate, 0 + ycoordinate, GREEN);
            drawBox(2 + xcoordinate, 0 + ycoordinate, GREEN);
            drawBox(2 + xcoordinate, 2 + ycoordinate, GREEN);
            drawBox(2 + xcoordinate, 4 + ycoordinate, GREEN);
            arrayBox(0, 0);
            arrayBox(2, 0);
            arrayBox(2, 2);
            arrayBox(2, 4);
            width = 6;
            height = 4;
            break;
          case 3:
            drawBox(0 + xcoordinate, 0 + ycoordinate, GREEN);
            drawBox(0 + xcoordinate, 2 + ycoordinate, GREEN);
            drawBox(2 + xcoordinate, 0 + ycoordinate, GREEN);
            drawBox(4 + xcoordinate, 0 + ycoordinate, GREEN);
            arrayBox(0, 0);
            arrayBox(0, 2);
            arrayBox(2, 0);
            arrayBox(4, 0);
            width = 4;
            height = 6;
            break;
          case 4:
            drawBox(0 + xcoordinate, 0 + ycoordinate, GREEN);
            drawBox(0 + xcoordinate, 2 + ycoordinate, GREEN);
            drawBox(0 + xcoordinate, 4 + ycoordinate, GREEN);
            drawBox(2 + xcoordinate, 4 + ycoordinate, GREEN);
            arrayBox(0, 0);
            arrayBox(0, 2);
            arrayBox(0, 4);
            arrayBox(2, 4);
            width = 6;
            height = 4;
            break;
        }
      }

      void freeze6(int orientation, int xcoordinate, int ycoordinate) {
      switch(orientation) {
        case 1:
          setBox(0 + xcoordinate, 2 + ycoordinate, WHITE);
          setBox(2 + xcoordinate, 2 + ycoordinate, WHITE);
          setBox(4 + xcoordinate, 2 + ycoordinate, WHITE);
          setBox(4 + xcoordinate, 0 + ycoordinate, WHITE);
          break;
        case 2:
          setBox(0 + xcoordinate, 0 + ycoordinate, WHITE);
          setBox(2 + xcoordinate, 0 + ycoordinate, WHITE);
          setBox(2 + xcoordinate, 2 + ycoordinate, WHITE);
          setBox(2 + xcoordinate, 4 + ycoordinate, WHITE);
          break;
        case 3:
          setBox(0 + xcoordinate, 0 + ycoordinate, WHITE);
          setBox(0 + xcoordinate, 2 + ycoordinate, WHITE);
          setBox(2 + xcoordinate, 0 + ycoordinate, WHITE);
          setBox(4 + xcoordinate, 0 + ycoordinate, WHITE);
          break;
        case 4:
          setBox(0 + xcoordinate, 0 + ycoordinate, WHITE);
          setBox(0 + xcoordinate, 2 + ycoordinate, WHITE);
          setBox(0 + xcoordinate, 4 + ycoordinate, WHITE);
          setBox(2 + xcoordinate, 4 + ycoordinate, WHITE);
          break;
      }
    }
  
  //SHAPE 7 (box) ------------------------------------------------------------------------------
    void move7() {
        erase7(orientation, x, y);
        x++;
        drawShape7(orientation, x, y);
      }
      
    void erase7(int orientation, int xcoordinate, int ycoordinate)  {
        switch(orientation) {
          case 1:
            drawBox(0 + xcoordinate, 0 + ycoordinate, BLACK);
            drawBox(0 + xcoordinate, 2 + ycoordinate, BLACK);
            drawBox(2 + xcoordinate, 0 + ycoordinate, BLACK);
            drawBox(2 + xcoordinate, 2 + ycoordinate, BLACK);
            break;
        }
        int i, j;
        for (i = 0; i < 8; i++)  {
          for (j = 0; j < 8; j++) {
            array[i][j]= false;
         }
       }
      }
  
     void drawShape7(int orientation, int xcoordinate, int ycoordinate)  {
        switch(orientation) {
          case 1:
            drawBox(0 + xcoordinate, 0 + ycoordinate, PURPLE);
            drawBox(0 + xcoordinate, 2 + ycoordinate, PURPLE);
            drawBox(2 + xcoordinate, 0 + ycoordinate, PURPLE);
            drawBox(2 + xcoordinate, 2 + ycoordinate, PURPLE);
            arrayBox(0, 0);
            arrayBox(0, 2);
            arrayBox(2, 0);
            arrayBox(2, 2);
            width = 4;
            height = 4;
            break;
        }
      }

      void freeze7(int orientation, int xcoordinate, int ycoordinate) {
        switch(orientation) {
          case 1:
            setBox(0 + xcoordinate, 0 + ycoordinate, WHITE);
            setBox(0 + xcoordinate, 2 + ycoordinate, WHITE);
            setBox(2 + xcoordinate, 0 + ycoordinate, WHITE);
            setBox(2 + xcoordinate, 2 + ycoordinate, WHITE);
            width = 4;
            height = 4;
            break;
        }
      }
    private:
        int orientation;
        int x;
        int y;
        int width;
        int height;
        bool pushed;
        
        //draws a 2 by 2 box of pixels
        void drawBox(int x, int y, Color color)  {
          matrix.drawPixel(x, y, color.to_333());
          matrix.drawPixel(x + 1, y, color.to_333());
          matrix.drawPixel(x, y + 1, color.to_333());
          matrix.drawPixel(x + 1, y + 1, color.to_333());
        }
        
        //sets a 2 by 2 box of white pixels in the freeze array
        void setBox(int x, int y, Color color)  {
          freeze[x][freeze_to_matrix_y(y)] = color.to_333();
          freeze[x + 1][freeze_to_matrix_y(y)] = color.to_333();
          freeze[x][freeze_to_matrix_y(y + 1)] = color.to_333();
          freeze[x + 1][freeze_to_matrix_y(y + 1)] = color.to_333();
          matrix.drawPixel(x, y, color.to_333());
          matrix.drawPixel(x + 1, y, color.to_333());
          matrix.drawPixel(x, y + 1, color.to_333());
          matrix.drawPixel(x + 1, y + 1, color.to_333());
        }
        
        //sets a 4 by 4 box of pixels in an array for the shape
        void arrayBox(int x, int y) {
          array[x][7 - y] = true;
          array[x + 1][7 - y] = true;
          array[x][6 - y] = true;
          array[x + 1][6 - y] = true;
        }

        //converts freeze coordinates to matrix for x and y
        int freeze_to_matrix_x(int freeze_x)  {
          return freeze_x;
        }
      
        int freeze_to_matrix_y(int freeze_y)  {
          return 15 - freeze_y;
        }
};

class Game  {
  //Default constructor
  public: 
    Game()  {
      level = 0;
      time = 0;
    }

  void setup() {
      time = 0;
      print_tetris();
      int i, j;
      //draws the line where the shapes land
      for (i = 0; i < 16; i++)  {
        matrix.drawPixel(20, i, WHITE.to_333());
      }
      //sets freeze array to black
      for (i = 0; i < 20; i++)  {
        for (j = 0; j < 16; j++)  {
          freeze[i][j] = BLACK.to_333();
        }
      }
    }

  void loop(int potentiometer_value, bool button_pressed) {
    if (t) {
        setup();
        t = false;
    }
    
    //randomizes shapes
   if (randomShape) {
       x = random(1, 8);
       randomShape = false;
      
   }
   
   int i, j, old_y;
   //depending on shape type, draws shape and moves it left-right
   if (x == 1)  {  
     if (shape.get_orientation() == 1)  {
      potvalue = (1024 - potentiometer_value) / 85;
      if (check_side(shape, potvalue)) {
        shape.erase1(shape.get_orientation(), shape.get_x(),
           shape.get_y());
        shape.set_y(potvalue);
      }
     }
     else {
      potvalue =  (1024 - potentiometer_value) / 102;
      if (check_side(shape, potvalue)) {
        shape.erase1(shape.get_orientation(), shape.get_x(),
           shape.get_y());
        shape.set_y(potvalue);
      }
     }
     shape.drawShape1(shape.get_orientation(),
       shape.get_x(), shape.get_y());
   }
   else if (x == 2) {
    if (shape.get_orientation() == 1)  {
      potvalue = (1024 - potentiometer_value) / 85;
      if (check_side(shape, potvalue)) {
        shape.erase2(shape.get_orientation(), shape.get_x(),
           shape.get_y());
        shape.set_y(potvalue);
      }
     }
     else {
      potvalue = (1024 - potentiometer_value) / 102;
      if (check_side(shape, potvalue)) {
        shape.erase2(shape.get_orientation(), shape.get_x(),
           shape.get_y());
        shape.set_y(potvalue);
      }
     }
     shape.drawShape2(shape.get_orientation(),
       shape.get_x(), shape.get_y());
   }
   else if (x == 3) {
     if (shape.get_orientation() == 1)  {
      potvalue = (1024 - potentiometer_value) / 73;
      if (check_side(shape, potvalue)) {
        shape.erase3(shape.get_orientation(), shape.get_x(),
           shape.get_y());
        shape.set_y(potvalue);
      }
     } 
     else {
      potvalue = (1024 - potentiometer_value) / 102;
      if (check_side(shape, potvalue)) {
        shape.erase3(shape.get_orientation(), shape.get_x(),
           shape.get_y());
        shape.set_y(potvalue);
      }
     }
     shape.drawShape3(shape.get_orientation(),
       shape.get_x(), shape.get_y());
   }
   else if (x == 4) {
     if (shape.get_orientation() == 1 || shape.get_orientation() == 3)  {
      potvalue = (1024 - potentiometer_value) / 102;
      if (check_side(shape, potvalue)) {
        shape.erase4(shape.get_orientation(), shape.get_x(),
           shape.get_y());
        shape.set_y(potvalue);
      }
     }
     else {
      potvalue = (1024 - potentiometer_value) / 85;
      if (check_side(shape, potvalue)) {
        shape.erase4(shape.get_orientation(), shape.get_x(),
           shape.get_y());
        shape.set_y(potvalue);
      }
     }
     shape.drawShape4(shape.get_orientation(),
       shape.get_x(), shape.get_y());
   }
   else if (x == 5) {
     if (shape.get_orientation() == 1 || shape.get_orientation() == 3)  {
      potvalue = (1024 - potentiometer_value) / 85;
      if (check_side(shape, potvalue)) {
        shape.erase5(shape.get_orientation(), shape.get_x(),
           shape.get_y());
        shape.set_y(potvalue);
      }
     }
     else {
      potvalue = (1024 - potentiometer_value) / 102;
      if (check_side(shape, potvalue)) {
        shape.erase5(shape.get_orientation(), shape.get_x(),
           shape.get_y());
        shape.set_y(potvalue);
      }
     }
     shape.drawShape5(shape.get_orientation(),
       shape.get_x(), shape.get_y());
   }
   else if (x == 6) {
    if (shape.get_orientation() == 1 || shape.get_orientation() == 3)  {
      potvalue = (1024 - potentiometer_value) / 85;
      if (check_side(shape, potvalue)) {
        shape.erase6(shape.get_orientation(), shape.get_x(),
           shape.get_y());
        shape.set_y(potvalue);
      }
     }
     else {
      potvalue = (1024 - potentiometer_value) / 102;
      if (check_side(shape, potvalue)) {
        shape.erase6(shape.get_orientation(), shape.get_x(),
           shape.get_y());
        shape.set_y(potvalue);
      }
     }
     shape.drawShape6(shape.get_orientation(),
       shape.get_x(), shape.get_y());
   }
   else if (x == 7) {
    potvalue = (1024 - potentiometer_value) / 85;
    if (check_side(shape, potvalue)) {
        shape.erase7(shape.get_orientation(), shape.get_x(),
           shape.get_y());
        shape.set_y(potvalue);
    }
    shape.drawShape7(shape.get_orientation(),
       shape.get_x(), shape.get_y());
   }

   //depending on the shape, it changes the orientation
   if (button_pressed && !shape.has_been_pushed()) {
    shape.change_pushed(true);
    eraseBoard();
    drawBoard();
    if (x == 1) {
      if (shape.get_orientation() == 1) {
        shape.set_orientation(shape.get_orientation() + 1);
      }
      else  {
        shape.erase1(shape.get_x(), shape.get_y(),
          shape.get_orientation());
        shape.set_orientation(1);
      }
    }
    else if (x == 2)  {
      if (shape.get_orientation() == 1) {
        shape.set_orientation(shape.get_orientation() + 1);
      }
      else  {
        shape.erase2(shape.get_x(), shape.get_y(),
          shape.get_orientation());
        shape.set_orientation(1);
      }
    }
    else if (x == 3)  {
      if (shape.get_orientation() == 1) {
        shape.set_orientation(shape.get_orientation() + 1);
      }
      else  {
        shape.erase3(shape.get_x(), shape.get_y(),
          shape.get_orientation());
        shape.set_orientation(1);
      }
      
    }
    else if (x == 4)  {
      if (shape.get_orientation() == 1) {
        shape.erase4(shape.get_x(), shape.get_y(),
          shape.get_orientation());
        shape.set_orientation(2);
      }
      else if (shape.get_orientation() == 2) {
        shape.erase4(shape.get_x(), shape.get_y(),
          shape.get_orientation());
        shape.set_orientation(3);
      }
      else if (shape.get_orientation() == 3) {
        shape.erase4(shape.get_x(), shape.get_y(),
          shape.get_orientation());
        shape.set_orientation(4);
      }
      else {
        shape.erase4(shape.get_x(), shape.get_y(),
          shape.get_orientation());
        shape.set_orientation(1);
      }
 
    }
    else if (x == 5)  {
      if (shape.get_orientation() == 1) {
        shape.erase5(shape.get_x(), shape.get_y(),
          shape.get_orientation());
        shape.set_orientation(2);
      }
      else if (shape.get_orientation() == 2) {
        shape.erase5(shape.get_x(), shape.get_y(),
          shape.get_orientation());
        shape.set_orientation(3);
      }
      else if (shape.get_orientation() == 3) {
        shape.erase5(shape.get_x(), shape.get_y(),
          shape.get_orientation());
        shape.set_orientation(4);
      }
      else {
        shape.erase5(shape.get_x(), shape.get_y(),
          shape.get_orientation());
        shape.set_orientation(1);
      }
      
    }
    else if (x == 6)  {
      if (shape.get_orientation() == 1) {
        shape.erase6(shape.get_x(), shape.get_y(),
          shape.get_orientation());
        shape.set_orientation(2);
      }
      else if (shape.get_orientation() == 2) {
        shape.erase6(shape.get_x(), shape.get_y(),
          shape.get_orientation());
        shape.set_orientation(3);
      }
      else if (shape.get_orientation() == 3) {
        shape.erase6(shape.get_x(), shape.get_y(),
          shape.get_orientation());
        shape.set_orientation(4);
      }
      else {
        shape.erase6(shape.get_x(), shape.get_y(),
          shape.get_orientation());
        shape.set_orientation(1);
      }
    }
    else if (x == 7)  {
      if (shape.get_orientation() == 1) {
        shape.set_orientation(1);
      }
    }
  }
  else if (!button_pressed)  {
    shape.change_pushed(false);
  }
  
   //moves shape down the screen based on time
   //check to see if the shape is touching a white color in the freeze array
    if (millis() >= time + 700)  {
      time = millis();
      if (x == 1)  { 
        shape.move1();
        if (shape.get_x() + shape.get_height() > 19) {
           shape.freeze1(shape.get_orientation(), shape.get_x(),
             shape.get_y());
           shape.initialize(0, 0, 1);
           randomShape = true;
        }
        else if (check_stop(shape)) {
          shape.freeze1(shape.get_orientation(), shape.get_x(),
             shape.get_y());
           shape.initialize(0, 0, 1);
           randomShape = true;
        }
      }
      else if (x == 2)  {
        shape.move2();
        if (shape.get_x() + shape.get_height() > 19) {
          shape.freeze2(shape.get_orientation(), shape.get_x(), 
            shape.get_y());
          shape.initialize(0, 0, 1);
          randomShape = true;
        }
        else if (check_stop(shape)) {
          shape.freeze2(shape.get_orientation(), shape.get_x(),
              shape.get_y());
          shape.initialize(0, 0, 1);
          randomShape = true;
        }
      }
      else if (x == 3)  {
        shape.move3();
        if (shape.get_x() + shape.get_height() > 19) {
           shape.freeze3(shape.get_orientation(), shape.get_x(),
             shape.get_y());
           shape.initialize(0, 0, 1);
           randomShape = true;
        }
        else if (check_stop(shape)) {
          shape.freeze3(shape.get_orientation(), shape.get_x(),
             shape.get_y());
           shape.initialize(0, 0, 1);
           randomShape = true;
        }
      }
      else if (x == 4)  {
        shape.move4();
        if (shape.get_x() + shape.get_height() > 19) {
           shape.freeze4(shape.get_orientation(), shape.get_x(),
             shape.get_y());
           shape.initialize(0, 0, 1);
           randomShape = true;
        }
        else if (check_stop(shape)) {
          shape.freeze4(shape.get_orientation(), shape.get_x(),
             shape.get_y());
           shape.initialize(0, 0, 1);
           randomShape = true;
        }
        
      }
      else if (x == 5)  {
        shape.move5();
        if (shape.get_x() + shape.get_height() > 19) {
           shape.freeze5(shape.get_orientation(), shape.get_x(),
             shape.get_y());
           shape.initialize(0, 0, 1);
           randomShape = true;
        }
        else if (check_stop(shape)) {
          shape.freeze5(shape.get_orientation(), shape.get_x(),
             shape.get_y());
           shape.initialize(0, 0, 1);
           randomShape = true;
        }
        
      }
      else if (x == 6)  {
        shape.move6();
        if (shape.get_x() + shape.get_height() > 19) {
           shape.freeze6(shape.get_orientation(), shape.get_x(),
             shape.get_y());
           shape.initialize(0, 0, 1);
           randomShape = true;
        }
        else if (check_stop(shape)) {
          shape.freeze6(shape.get_orientation(), shape.get_x(),
             shape.get_y());
           shape.initialize(0, 0, 1);
           randomShape = true;
        }
      }
      else if (x == 7)  {
        shape.move7();
        if (shape.get_x() + shape.get_height() > 19) {
          shape.freeze7(shape.get_orientation(), shape.get_x(), 
            shape.get_y());
          shape.initialize(0, 0, 1);
          randomShape = true;
        }
        else if (check_stop(shape)) {
          shape.freeze7(shape.get_orientation(), shape.get_x(),
              shape.get_y());
          shape.initialize(0, 0, 1);
          randomShape = true;
        }
      }
    }
    //if a line is full, clear the line and move every row in freeze down
    int row_index;
    for (i = 0; i < 20; i++)  {
      if (line_full(i))  {
        for (j = 0; j < 16; j++)  {
          freeze[i][j] = BLACK.to_333();
          matrix.drawPixel(freeze_to_matrix_x(i), freeze_to_matrix_y(j), BLACK.to_333());
          delay(100);
        }
        row_index = i;
        for (int k = row_index; k > 0; k--)  {
          for (j = 0; j < 16; j++)  {
            freeze[k][j] = freeze[k - 1][j];
          }
        }
        drawBoard();
      }
    }
    
    //if a shape is frozen too high, the game ends
    for (i = 0; i < 16; i++)  {
      if (freeze[1][i] != BLACK.to_333()) {
        eraseBoard();
        game_over();
      }
    }
  }

  private:
    int level;
    int lives;
    unsigned long time;
    bool t = true;
    bool randomShape = true;
    Shape shape;
    long x; 
    int potvalue;
      
    //clears everything on the screen
    void clear_screen() {
      matrix.fillScreen(BLACK.to_333());
    }

    //clears everything above the line on the screen
    void eraseBoard(){
      for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 16; j++) {
          matrix.drawPixel(i, j, BLACK.to_333());
        }
      }
    }
    
    //draws board back
    void drawBoard()  {
      for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 16; j++) {
          if (freeze[i][j] != BLACK.to_333()) {
            matrix.drawPixel(i, 15 - j, WHITE.to_333());
          }
          else  {
            matrix.drawPixel(i, 15 - j, BLACK.to_333());
          }
        }
      }
    }

    //check if all pixels in row are on
    bool line_full(int row)  {
      int j;
      for (j = 0; j < 16; j++)  {
        if (freeze[row][j] == BLACK.to_333())  {
          return false;
        }
      }
      return true;
    }

    //finds where the shape should stop moving
    bool check_stop(Shape shape)  {
      int i, j;
      for (i = 7; i >= 0; i--)  {
        for (j = 0; j < 8; j++) {
          if (array[i][j])  {
            if (freeze[array_to_matrix_x(i, shape) + 1]
            [freeze_to_matrix_y(array_to_matrix_y(j, shape))] != BLACK.to_333())  {
              return true;
            }
          }
        }
      }
      return false;
    }
    
    //check to see if potentiometer value is valid
    bool check_side(Shape shape, int potvalue)  {
      int i, j;
      int both = 0;
      for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
          if (array[i][j])  {
            if (freeze[array_to_matrix_x(i, shape)][freeze_to_matrix_y(7 - j + potvalue)] 
            != BLACK.to_333()) {
              return false;
            }
          }
        }
      }
      return true;
    }
    
    //changes freeze coordinate to matrix for x and y
    int freeze_to_matrix_x(int freeze_x)  {
      return freeze_x;
    }

    int freeze_to_matrix_y(int freeze_y)  {
      return 15 - freeze_y;
    }
    
    //changes array coordinate to matrix for x and y
    int array_to_matrix_x(int array_x, Shape shape)  {
      return array_x + shape.get_x();
    }

    int array_to_matrix_y(int array_y, Shape shape) {
      return 7 - array_y + shape.get_y();
    }
};

//a global variable that represents the game Tetris
Game game;

void setup()  {
  Serial.begin(9600);
  pinMode(BUTTON_PIN_NUMBER, INPUT);
  matrix.begin();
  randomSeed(analogRead(4));
}

void loop() {
  int potentiometer_value = analogRead(POTENTIOMETER_PIN_NUMBER);
  bool button_pressed = (digitalRead(BUTTON_PIN_NUMBER) == HIGH);

  game.loop(potentiometer_value, button_pressed);
}

//displays number of lives
void print_lives(int lives) {
  matrix.print("LIVES: ");
  matrix.print(lives);
  delay(2000);
  matrix.fillScreen(BLACK.to_333());
  matrix.setCursor(0,0);
}

//prints "TETRIS"
void print_tetris(){
   //draw T
   matrix.drawPixel(22, 15, AQUA.to_333());
   matrix.drawPixel(22, 14, AQUA.to_333());
   matrix.drawPixel(22, 13, AQUA.to_333());
   matrix.drawPixel(23, 14, AQUA.to_333());
   matrix.drawPixel(24, 14, AQUA.to_333());
   matrix.drawPixel(25, 14, AQUA.to_333());
   matrix.drawPixel(26, 14, AQUA.to_333());
   //draw E
   matrix.drawPixel(22, 12, YELLOW.to_333());
   matrix.drawPixel(22, 11, YELLOW.to_333());
   matrix.drawPixel(23, 12, YELLOW.to_333());
   matrix.drawPixel(24, 12, YELLOW.to_333());
   matrix.drawPixel(24, 11, YELLOW.to_333());
   matrix.drawPixel(26, 12, YELLOW.to_333());
   matrix.drawPixel(26, 11, YELLOW.to_333());
   matrix.drawPixel(25, 12, YELLOW.to_333());
   //draw T
   matrix.drawPixel(22, 10, PURPLE.to_333());
   matrix.drawPixel(22, 9, PURPLE.to_333());
   matrix.drawPixel(22, 8, PURPLE.to_333());
   matrix.drawPixel(23, 9, PURPLE.to_333());
   matrix.drawPixel(24, 9, PURPLE.to_333());
   matrix.drawPixel(25, 9, PURPLE.to_333());
   matrix.drawPixel(26, 9, PURPLE.to_333());
   //draw R
   matrix.drawPixel(22, 7, GREEN.to_333());
   matrix.drawPixel(22, 6, GREEN.to_333());
   matrix.drawPixel(22, 5, GREEN.to_333());
   matrix.drawPixel(23, 7, GREEN.to_333());
   matrix.drawPixel(23, 6, GREEN.to_333());
   matrix.drawPixel(23, 5, GREEN.to_333());
   matrix.drawPixel(24, 7, GREEN.to_333());
   matrix.drawPixel(24, 6, GREEN.to_333());
   matrix.drawPixel(25, 7, GREEN.to_333());
   matrix.drawPixel(25, 5, GREEN.to_333());
   matrix.drawPixel(26, 7, GREEN.to_333());
   matrix.drawPixel(26, 5, GREEN.to_333());
   //draw I
   matrix.drawPixel(22, 4, RED.to_333());
   matrix.drawPixel(23, 4, RED.to_333());
   matrix.drawPixel(24, 4, RED.to_333());
   matrix.drawPixel(25, 4, RED.to_333());
   matrix.drawPixel(26, 4, RED.to_333());
   //Draw S
   matrix.drawPixel(22, 3, BLUE.to_333());
   matrix.drawPixel(23, 3, BLUE.to_333());
   matrix.drawPixel(24, 3, BLUE.to_333());
   matrix.drawPixel(22, 2, BLUE.to_333());
   matrix.drawPixel(24, 2, BLUE.to_333());
   matrix.drawPixel(25, 2, BLUE.to_333());
   matrix.drawPixel(26, 2, BLUE.to_333());
   matrix.drawPixel(26, 3, BLUE.to_333());
   //Draw exclamation point
   matrix.drawPixel(22, 0, WHITE.to_333());
   matrix.drawPixel(22, 1, WHITE.to_333());
   matrix.drawPixel(23, 1, WHITE.to_333());
   matrix.drawPixel(23, 0, WHITE.to_333());
   matrix.drawPixel(24, 1, WHITE.to_333());
   matrix.drawPixel(24, 0, WHITE.to_333());
   matrix.drawPixel(26, 1, WHITE.to_333());
   matrix.drawPixel(26, 0, WHITE.to_333());
   
}

//prints game over
void game_over()  {
  matrix.drawPixel(2, 13, RED.to_333());
  matrix.drawPixel(2, 12, RED.to_333());
  matrix.drawPixel(2, 9, RED.to_333());
  matrix.drawPixel(2, 5, RED.to_333());
  matrix.drawPixel(2, 3, RED.to_333());
  matrix.drawPixel(2, 2, RED.to_333());
  matrix.drawPixel(2, 1, RED.to_333());
  matrix.drawPixel(3, 14, RED.to_333());
  matrix.drawPixel(3, 9, RED.to_333());
  matrix.drawPixel(3, 8, RED.to_333());
  matrix.drawPixel(3, 6, RED.to_333());
  matrix.drawPixel(3, 5, RED.to_333());
  matrix.drawPixel(3, 3, RED.to_333());
  matrix.drawPixel(4, 14, RED.to_333());
  matrix.drawPixel(4, 12, RED.to_333());
  matrix.drawPixel(4, 11, RED.to_333());
  matrix.drawPixel(4, 9, RED.to_333());
  matrix.drawPixel(4, 7, RED.to_333());
  matrix.drawPixel(4, 5, RED.to_333());
  matrix.drawPixel(4, 3, RED.to_333());
  matrix.drawPixel(4, 2, RED.to_333());
  matrix.drawPixel(4, 1, RED.to_333());
  matrix.drawPixel(5, 14, RED.to_333());
  matrix.drawPixel(5, 11, RED.to_333());
  matrix.drawPixel(5, 9, RED.to_333());
  matrix.drawPixel(5, 5, RED.to_333());
  matrix.drawPixel(5, 3, RED.to_333());
  matrix.drawPixel(6, 13, RED.to_333());
  matrix.drawPixel(6, 12, RED.to_333());
  matrix.drawPixel(6, 11, RED.to_333());
  matrix.drawPixel(6, 9, RED.to_333());
  matrix.drawPixel(6, 5, RED.to_333());
  matrix.drawPixel(6, 3, RED.to_333());
  matrix.drawPixel(6, 2, RED.to_333());
  matrix.drawPixel(6, 1, RED.to_333());
  matrix.drawPixel(8, 13, RED.to_333());
  matrix.drawPixel(8, 12, RED.to_333());
  matrix.drawPixel(8, 9, RED.to_333());
  matrix.drawPixel(8, 5, RED.to_333());
  matrix.drawPixel(8, 3, RED.to_333());
  matrix.drawPixel(8, 2, RED.to_333());
  matrix.drawPixel(8, 1, RED.to_333());
  matrix.drawPixel(9, 14, RED.to_333());
  matrix.drawPixel(9, 11, RED.to_333());
  matrix.drawPixel(9, 9, RED.to_333());
  matrix.drawPixel(9, 5, RED.to_333());
  matrix.drawPixel(9, 3, RED.to_333());
  matrix.drawPixel(9, 2, RED.to_333());
  matrix.drawPixel(9, 1, RED.to_333());
  matrix.drawPixel(10, 14, RED.to_333());
  matrix.drawPixel(10, 11, RED.to_333());
  matrix.drawPixel(10, 9, RED.to_333());
  matrix.drawPixel(10, 5, RED.to_333());
  matrix.drawPixel(10, 3, RED.to_333());
  matrix.drawPixel(10, 2, RED.to_333());
  matrix.drawPixel(11, 14, RED.to_333());
  matrix.drawPixel(11, 11, RED.to_333());
  matrix.drawPixel(11, 8, RED.to_333());
  matrix.drawPixel(11, 6, RED.to_333());
  matrix.drawPixel(11, 3, RED.to_333());
  matrix.drawPixel(11, 1, RED.to_333());
  matrix.drawPixel(12, 13, RED.to_333());
  matrix.drawPixel(12, 12, RED.to_333());
  matrix.drawPixel(12, 7, RED.to_333());
  matrix.drawPixel(12, 3, RED.to_333());
  matrix.drawPixel(12, 1, RED.to_333());
  matrix.drawPixel(14, 8, WHITE.to_333());
  matrix.drawPixel(14, 6, WHITE.to_333());
  matrix.drawPixel(16, 8, WHITE.to_333());
  matrix.drawPixel(16, 7, WHITE.to_333());
  matrix.drawPixel(16, 6, WHITE.to_333());
  matrix.drawPixel(17, 9, WHITE.to_333());
  matrix.drawPixel(17, 5, WHITE.to_333());
  delay(3000000);
}

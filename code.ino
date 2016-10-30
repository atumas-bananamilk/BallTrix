   #include <Adafruit_GFX.h>                    // Core graphics library
   #include <RGBmatrixPanel.h>              // Hardware-specific library
   
   int CLK = 8;
   int OE = 9;
   int LAT = 10;
   int A = A0;
   int B = A1;
   int C = A2;
   int D = A3;
   
   RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);
   
   int buttonShoot = 13;
   int buttonLeft = 12;
   int buttonRight = 11;
   
   void setup() {
      matrix.begin();
      pinMode(buttonLeft, INPUT);
      pinMode(buttonRight, INPUT);
      pinMode(buttonShoot, INPUT);
   }
   
   int ballX = 1;
   int ballY = 1;
   boolean reachedEnd = true;
   int shootX = -1;
   int shootY = 0;
   
   void loop() {
      if (digitalRead(buttonLeft) == HIGH)
         moveLeft();
      else if (digitalRead(buttonRight) == HIGH)
         moveRight();
      if (digitalRead(buttonShoot) == HIGH)
         if (reachedEnd)
         {
            reachedEnd = false;
            shootX = ballX;
            shootY = 0;
         }
   
      updateShoot();
      drawShoot();
   
      drawBall();
      delay(20);
      clearScreen();
   }
   
   void moveLeft()
   {
      ballX--;
   }
   
   void moveRight()
   {
      ballX++;
   }
   
   void updateShoot()
   {
      if (!reachedEnd)
         if (shootY < 32)
            shootY++;
      else
         reachedEnd = true;
   }
   
   void drawShoot()
   {
      if (!reachedEnd)
         matrix.drawPixel(shootX, shootY, matrix.Color333(3, 4, 8)); 
   }
   
   void drawBall()
   {
      matrix.drawPixel(ballX, ballY, matrix.Color333(4, 1, 7));
      matrix.drawPixel(ballX - 1, ballY, matrix.Color333(4, 1, 7));
      matrix.drawPixel(ballX + 1, ballY, matrix.Color333(4, 1, 7));
      matrix.drawPixel(ballX, ballY - 1, matrix.Color333(4, 1, 7));
      matrix.drawPixel(ballX, ballY + 1, matrix.Color333(4, 1, 7));
   }
   
   void clearScreen()
   { 
      matrix.drawPixel(ballX, ballY, matrix.Color333(0, 0, 0));
      matrix.drawPixel(ballX - 1, ballY, matrix.Color333(0, 0, 0));
      matrix.drawPixel(ballX + 1, ballY, matrix.Color333(0, 0, 0));
      matrix.drawPixel(ballX, ballY - 1, matrix.Color333(0, 0, 0));
      matrix.drawPixel(ballX, ballY + 1, matrix.Color333(0, 0, 0));
      matrix.drawPixel(shootX, shootY, matrix.Color333(0, 0, 0));
   }
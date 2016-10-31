# BallTrix - ball game on a matrix

![alt tag](http://aivarastumas.weebly.com/uploads/4/9/8/0/49800285/547506416.png)

We divided our tasks into 2 parts: <br />
Part 1 - light a chosen LED on the matrix. <br />
Part 2 - make a simple shooting game on the matrix. <br />

# PART 1

We are going to be working with a 32x32 Matrix Display from our Hardware Library, but this tutorial is compatible with any display size, since you get the concept.

Connect Matrix Display to Arduino: <br />
Every Matrix Display has its INPUT and OUTPUT pins. We program it with Arduino through INPUT pins, and OUTPUT is only used for connecting displays. <br />
You will most probably see this kind of input:

![alt tag](http://aivarastumas.weebly.com/uploads/4/9/8/0/49800285/583215803.png)

Remember, if you use a jumper wire to connect INPUT pins to Arduino, your inputs will be inverted in places:

![alt tag](http://aivarastumas.weebly.com/uploads/4/9/8/0/49800285/574983886.png)

Connecting:

        1. Connect a power cable from the back of the display to Arduino's 5V and GND.
        2. All GND to Arduino's GND.
        3. R1 to pin 2 on Arduino.
        4. G1 to pin 3 on Arduino.
        5. B1 to pin 4 on Arduino.
        6. R2 to pin 5 on Arduino.
        7. G2 to pin 6 on Arduino.
        8. B2 to pin 7 on Arduino.
        9. A to pin A0 on Arduino.
        10. B to pin A1 on Arduino.
        11. C to pin A2 on Arduino.
        12. D to pin A3 on Arduino.
        13. LAT to pin 10 on Arduino.
        14. CLK to pin 8 on Arduino.
        15. OE to pin 9 on Arduino.

R1, G1, B1 - (red, green, blue) responsible for 1st half of the display (lines 0-15). <br />
R2, G2, B2 - (red, green, blue) responsible for 2nd half of the display (lines 16-32). <br />
A, B, C, D - select which two rows of the display are currently lit. <br />
LAT (latch) - marks the end of a row of data. <br />
CLK (clock) - marks the arrival of each bit of data. <br />
OE (output enable) - switches the LEDs off when transitioning from one row to the next.

Running an example:

        1. RGB Matrix Panel library: https://github.com/adafruit/RGB-matrix-Panel
        2. Adafruit GFX library: https://github.com/adafruit/Adafruit-GFX-Library
        3. Uncompress RGB Matrix Panel library and name its folder: "RGBmatrixPanel"
        4. Uncompress Adafruit GFX library and name its folder: "Adafruit_GFX"
        5. Place those folders into: "Your Arduino folder/libraries"
        6. Restart IDE
        7. Open File→Examples→RGBmatrixPanel→colorwheel_32x32

Now you should see a colourful circle on your display.

Main functions in Arduino:

Create matrix object:

        RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);

Initialising matrix:

        matrix.begin();

Drawing a pixel:

        matrix.drawPixel(x, y, matrix.Color333(0, 2, 0));

x - x coordinate <br />
y - y coordinate <br />
Color333(); - 3bit colours (0-8) <br />
Color444(); - 4bit colours (0-16)

# PART 2

WARNING: you need to have some knowledge of how Arduino buttons work. You can find tutorial for that here: https://wiki.cs.manchester.ac.uk/engineering/index.php/Controlling_button

Let's now make a simple game. <br />
In the game, there will be a ball, which is controlled to move LEFT and RIGHT with 2 buttons, and it can also shoot projectiles with the 3rd button. <br />
Let's keep it simple, so there will be no enemies to be shot. <br />
Circuit:

![alt tag](http://aivarastumas.weebly.com/uploads/4/9/8/0/49800285/941440004.png)

Pin 13 - for shooting. <br />
Pin 12 - for moving LEFT. <br />
Pin 11 - for moving RIGHT.

Ball movement:

        1. Ball's coordinates are updated
        2. Ball is drawn in the new coordinates for 0.02s
        3. Screen is cleared
        4. Repeat

Code:

1. Include libraries and initialise pins:

        #include <Adafruit_GFX.h>
        #include <RGBmatrixPanel.h>
 
        int CLK = 8;
        int OE = 9;
        int LAT = 10;
        int A = A0;
        int B = A1;
        int C = A2;
        int D = A3;

2. Create matrix object:

        RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);

3. Initialise buttons and matrix:

        int buttonLeft = 12;
        int buttonRight = 11;
   
        void setup() {
            matrix.begin();
            pinMode(buttonLeft, INPUT);
            pinMode(buttonRight, INPUT);
        }

4. Drawing, updating the ball:

        int ballX = 1;
        int ballY = 1;
   
        void loop() {
            if (digitalRead(buttonLeft) == HIGH)
                moveLeft();
            else if (digitalRead(buttonRight) == HIGH)
                moveRight();
   
            drawBall();
            delay(20);
            clearScreen();
        }

5. moveLeft:

        void moveLeft()
        {
            ballX--;
        }

6. moveRight:

        void moveRight()
        {
            ballX++;
        }

7. drawBall:

        void drawBall()
        {
            matrix.drawPixel(ballX, ballY, matrix.Color333(4, 1, 7));
            matrix.drawPixel(ballX - 1, ballY, matrix.Color333(4, 1, 7));
            matrix.drawPixel(ballX + 1, ballY, matrix.Color333(4, 1, 7));
            matrix.drawPixel(ballX, ballY - 1, matrix.Color333(4, 1, 7));
            matrix.drawPixel(ballX, ballY + 1, matrix.Color333(4, 1, 7));
        }

Note: <br />
Drawing: 1 pixel in the middle, 1 on the left, 1 on the right, 1 on the top, 1 on the bottom. Basically, it looks like a "+", but let's assume it is a ball!

8. clearScreen:

        void clearScreen()
        { 
            matrix.drawPixel(ballX, ballY, matrix.Color333(0, 0, 0));
            matrix.drawPixel(ballX - 1, ballY, matrix.Color333(0, 0, 0));
            matrix.drawPixel(ballX + 1, ballY, matrix.Color333(0, 0, 0));
            matrix.drawPixel(ballX, ballY - 1, matrix.Color333(0, 0, 0));
            matrix.drawPixel(ballX, ballY + 1, matrix.Color333(0, 0, 0));
        }

Note: <br />
We are not clearing the whole screen, as it takes a huge amount of time, but only where the ball is. <br />
Done! Now your ball should be moving on the presses of 2 buttons.

Shooting:

        1. Projectile's coordinates are updated
        2. Projectile is drawn in the new coordinates for 0.02s
        3. Screen is cleared
        4. Repeat

Code:

1. Initialise new pin:

        int buttonShoot = 13;

2. Initialise variables for updating coordinates:

        boolean reachedEnd = true;
        int shootX = -1;
        int shootY = 0;

Note:
reachedEnd - will check whether the projectile has reached the end of the display, if not, then it will not let us create a new projectile. <br />
shootX is -1, because our code will try to draw it since we initialise it, so in coordinate -1 it will not be visible.

3. Reset the projectile and update, draw it:

        if (digitalRead(buttonShoot) == HIGH)
            if (reachedEnd)
            {
                reachedEnd = false;
                shootX = ballX;
                shootY = 0;
            }

        updateShoot();
        drawShoot();

4. updateShoot:

        void updateShoot()
        {
            if (!reachedEnd)
                if (shootY < 32)
                    shootY++;
                else
                    reachedEnd = true;
        }

5. drawShoot:

        if (!reachedEnd)
            matrix.drawPixel(shootX, shootY, matrix.Color333(3, 4, 8)); 

6. Clear more of the screen:

        matrix.drawPixel(shootX, shootY, matrix.Color333(0, 0, 0));

Note: <br />
We, again, clear only the current updated coordinate of the projectile, as it is updated, then drawn, then cleared. <br />
Done!

Your full code should look like this:

https://github.com/atumas-bananamilk/BallTrix/blob/master/code.ino

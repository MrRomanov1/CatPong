//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

int movesCounter = 0;
AnsiString actualPlayer = "left";

float randomizeVerticalBallMovement() {
    randomize();
    float verticalBallMovement = random(6) + 5;
    randomize();
    int negativity = random(2);

    if (negativity == 1) {
        verticalBallMovement = -verticalBallMovement;
        actualPlayer = "right";
    }
    return verticalBallMovement;
}

float randomizeHorizontalBallMovement() {
    randomize();
    float horizontalBallMovement = random(6) + 5;
    randomize();
    int negativity = random(2);

    if (negativity == 1) {
        horizontalBallMovement = -horizontalBallMovement;
    }
    return horizontalBallMovement;
}

float x = randomizeHorizontalBallMovement();
float y = randomizeVerticalBallMovement();

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner) {
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BallMovementTimer(TObject *Sender) {
    //initial ball movement
    Ball -> Left += x;
    Ball -> Top  += y;
    //top of the screen bounce
    if (Ball -> Top -5 <= Background -> Top) {
        y = -y;
    }
    //bottom of the screen bounce
    if (Ball -> Top>= Background -> Height - Background -> Top - Ball -> Height + 10) {
        y = -y;
    }
    //out of bonds
    if ((( Ball->Left < LeftPaddle->Left  &&
            (Ball->Top + Ball->Height / 2 < LeftPaddle->Top ||
             Ball->Top + Ball->Height / 2 > LeftPaddle->Top + LeftPaddle->Height)) ||
            (Ball->Left + Ball->Width > RightPaddle->Left + RightPaddle->Width &&
             (Ball->Top + Ball->Height / 2 < RightPaddle->Top ||
              Ball->Top + Ball->Height / 2 > RightPaddle->Top + RightPaddle->Height)))) {

        BallMovement -> Enabled = false;
        Ball -> Visible = false;
    }
    //left paddle bounce
    if (Ball -> Left <= LeftPaddle -> Left + LeftPaddle -> Width-5 &&
            Ball -> Top + Ball -> Height/2 <= LeftPaddle -> Top + LeftPaddle -> Height &&
            Ball -> Top + Ball -> Height/2 >= LeftPaddle -> Top) {

        movesCounter ++;
        actualPlayer = "left";
        //
        if(x < 0) {
            //top left paddle bounce
            if (Ball -> Left <= LeftPaddle -> Left + LeftPaddle -> Width &&
                    Ball -> Top + Ball -> Height /2 <= LeftPaddle -> Top + LeftPaddle -> Height/4 &&
                    Ball -> Top + Ball -> Height /2 >= LeftPaddle -> Top) {

                x = -0.8 * x;
                y = 0.8 * y;
            }
            //middle left paddle bounce
            else if (Ball -> Left <= LeftPaddle -> Left + LeftPaddle -> Width &&
                     Ball -> Top + Ball -> Height /2 <= LeftPaddle -> Top + 2* LeftPaddle -> Height/4 &&
                     Ball -> Top + Ball -> Height /2 >= LeftPaddle -> Top + LeftPaddle -> Height/4) {

                x = -x;

            }
            //bottom left paddle bounce
            else if (Ball -> Left <= LeftPaddle -> Left + LeftPaddle -> Width &&
                     Ball -> Top + Ball -> Height /2 <= LeftPaddle -> Top +  LeftPaddle -> Height &&
                     Ball -> Top + Ball -> Height /2 >= LeftPaddle -> Top + 1/2 * LeftPaddle -> Height) {

                x = -1.2 * x;
                y = 1.2 * y;
            }
        }
    }
    //right paddle bounce
    if (Ball -> Left + Ball -> Width >= RightPaddle -> Left &&
            Ball -> Top + Ball -> Height/2 <= RightPaddle -> Top + RightPaddle -> Height &&
            Ball -> Top + Ball -> Height/2 >= RightPaddle -> Top) {

        movesCounter ++;
        actualPlayer = "right";

        if (x > 0) {
            //top right paddle bounce
            if (Ball -> Left + Ball -> Width >= RightPaddle -> Left &&
                    Ball -> Top + Ball -> Height/2 <= RightPaddle -> Top + RightPaddle -> Height / 4 &&
                    Ball -> Top + Ball -> Height/2 >= RightPaddle -> Top) {

                x = -0.8 * x;
                y = 0.8 * y;
            }
            //middle right paddle bounce
            else if (Ball -> Left + Ball -> Width >= RightPaddle -> Left &&
                     Ball -> Top + Ball -> Height/2 <= RightPaddle -> Top + 2 * RightPaddle -> Height / 4 &&
                     Ball -> Top + Ball -> Height/2 >= RightPaddle -> Top) {
                x = -x;
            }
            //bottom right paddle bounce
            else if (Ball -> Left <= RightPaddle -> Left + RightPaddle -> Width &&
                     Ball -> Top + Ball -> Height/2 <= RightPaddle -> Top + RightPaddle -> Height &&
                     Ball -> Top + Ball -> Height/2 >= RightPaddle -> Top + 1/2 * RightPaddle -> Height) {
                x = -1.2 * x;
                y = 1.2 * y;
            }
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::LeftPaddleUpTimer(TObject *Sender) {
    if (LeftPaddle -> Top > 5)
        LeftPaddle -> Top -= 15;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RightPaddleUpTimer(TObject *Sender) {
    if (RightPaddle -> Top > 5)
        RightPaddle -> Top -= 15;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::LeftPaddleDownTimer(TObject *Sender) {
    if (LeftPaddle -> Top + LeftPaddle -> Height < Background -> Height + 10) {
        LeftPaddle -> Top += 15;
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
                                    TShiftState Shift) {
    if (Key == VK_UP) {
        RightPaddleUp -> Enabled = true;
    }
    if (Key == 'a' || Key == 'A') {
        LeftPaddleUp -> Enabled = true;
    }
    if (Key == VK_DOWN) {
        RightPaddleDown -> Enabled = true;
    }
    if (Key == 'z' || Key == 'Z') {
        LeftPaddleDown -> Enabled = true;
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyUp(TObject *Sender, WORD &Key,
                                  TShiftState Shift) {
    if (Key == VK_UP) {
        RightPaddleUp -> Enabled = false;
    }
    if (Key == 'a' || Key == 'A') {
        LeftPaddleUp -> Enabled = false;
    }
    if (Key == VK_DOWN) {
        RightPaddleDown -> Enabled = false;
    }
    if (Key == 'z' || Key == 'Z') {
        LeftPaddleDown -> Enabled = false;
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RightPaddleDownTimer(TObject *Sender) {
    if (RightPaddle -> Top + RightPaddle -> Height < Background -> Height + 10) {
        RightPaddle -> Top += 15;
    }
}
//---------------------------------------------------------------------------


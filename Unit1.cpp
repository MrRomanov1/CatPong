//---------------------------------------------------------------------------

#include <vcl.h>
#include <algorithm>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

int movesCounter = 0;
AnsiString actualPlayer = "";
int leftPlayerPoints = 0;
int rightPlayerPoints = 0;
float x = 0;
float y = 0;
float x2 = 0;
float y2 = 0;
bool enableMusic = true;
int nyanRounds[100];
int obstacleNumber = 0;
int obstacleSymbol[100];
int verticalNyanMovement = 8;

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

void generateObstacleSymbols() {

    randomize();
    for (int i = 0; i < 100; i++) {
        obstacleSymbol [i] = random (2) + 1;
    }
}

void generateNyanRounds() {
    randomize();
    for (int i = 0; i < 100; i++) {
        nyanRounds[i] = random (100) + 2;
    }
    std::sort(nyanRounds, (nyanRounds+(sizeof(nyanRounds)/sizeof(nyanRounds[0]))));
}

bool launchNyanObstacle() {

    for (int i = 0; i < 100; i++) {
        if (movesCounter == nyanRounds[i]) {
            return true;
        }
    }
    return false;
}

bool ballWithNyanCollision( TImage * Ball, TImage * Obstacle) {
    if (Ball -> Left >= Obstacle -> Left - Ball -> Width &&
            Ball -> Left <= Obstacle -> Left + Obstacle -> Width &&
            Ball -> Top >= Obstacle -> Top - Obstacle -> Height &&
            Ball -> Top <= Obstacle -> Top + Obstacle -> Height) {
        return true;
    } else {
        return false;
    }
}

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner) {
}
//---------------------------------------------------------------------------

void __fastcall gameInitialization() {

    x = randomizeHorizontalBallMovement();
    y = randomizeVerticalBallMovement();

    Form1 -> LeftPaddle -> Left = 0;
    Form1 ->LeftPaddle -> Top = Form1 ->Background -> Height / 2 - Form1 ->LeftPaddle -> Height / 2;

    Form1 ->RightPaddle -> Left = Form1 ->Background -> Width - Form1 ->RightPaddle -> Width;
    Form1 ->RightPaddle -> Top = Form1 ->Background -> Height / 2 - Form1 ->RightPaddle -> Height / 2;

    Form1 ->Ball -> Left = Form1 ->Background -> Width / 2 - Form1 ->Ball -> Width / 2;
    Form1 ->Ball -> Top = Form1 ->Background -> Height / 2 - Form1 ->Ball -> Height / 2;

    Form1 -> BallMovement -> Interval = 30;
    Form1 -> LeftPaddleDown -> Interval = 30;
    Form1 -> LeftPaddleUp -> Interval = 30;
    Form1 -> RightPaddleDown -> Interval = 30;
    Form1 -> RightPaddleUp -> Interval = 30;

    Form1 -> Ball -> Visible = true;
    Form1 -> LeftPaddle -> Visible = true;
    Form1 -> RightPaddle -> Visible = true;

    Form1 -> BallMovement -> Enabled = true;

    if (Form1 -> RadioGroup1 -> ItemIndex == 0) {
        enableMusic = true;
    }
    if (Form1 -> RadioGroup1 -> ItemIndex == 1) {
        enableMusic = false;
    }

    movesCounter = 0;
    actualPlayer = "";
}
void __fastcall setRandomNyanPosition() {

    randomize();
    Form1 -> Obstacle -> Left = random(Form1 ->Background -> Width - 50) + 50;
    randomize();
    Form1 -> Obstacle -> Top = random (Form1 ->Background -> Height - 50) + 50;

    Form1 -> Obstacle -> Enabled = true;
    Form1 -> Obstacle -> Visible = true;
}

void __fastcall setObstacle() {
    Form1 -> Label1 -> Visible = true;
    Form1 -> Label1 -> Caption = IntToStr(obstacleSymbol[obstacleNumber]);

    switch (obstacleSymbol[obstacleNumber]) {
    case 1: {
        Form1 -> Ball2 -> Enabled = true;
        Form1 -> Ball2 -> Visible = true;

        Form1 ->Ball2 -> Left = Form1 ->Background -> Width / 2 - Form1 ->Ball2 -> Width / 2;
        Form1 ->Ball2 -> Top = Form1 ->Background -> Height / 2 - Form1 ->Ball2 -> Height / 2;

        x2 = -x;
        y2 = -y;

        Form1 -> Ball2Movement -> Enabled = true;
    }
    break;
    case 2: {

        Form1 -> Ball2Movement -> Enabled = false;
        Form1 -> Ball2 -> Enabled = false;
        Form1 -> Ball2 -> Visible = false;
        Form1 -> BallMovement -> Interval = (Form1 -> BallMovement -> Interval) * 0.85;
        Form1 -> LeftPaddleDown -> Interval = (Form1 -> LeftPaddleDown -> Interval) * 0.85;
        Form1 -> LeftPaddleUp -> Interval = (Form1 -> LeftPaddleUp -> Interval) * 0.85;
        Form1 -> RightPaddleDown -> Interval = (Form1 -> RightPaddleDown -> Interval) * 0.85;
        Form1 -> RightPaddleUp -> Interval = (Form1 -> RightPaddleUp -> Interval) * 0.85;
    }
    break;
    }
    obstacleNumber++;
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
        Ball2Movement -> Enabled = false;
        Ball -> Visible = false;
        Ball2 -> Visible = false;
        Obstacle -> Visible = false;
        NyanMovement -> Enabled = false;

        if ((( Ball->Left < LeftPaddle->Left  &&
                (Ball->Top + Ball->Height / 2 < LeftPaddle->Top ||
                 Ball->Top + Ball->Height / 2 > LeftPaddle->Top + LeftPaddle->Height)))) {

            rightPlayerPoints++;
            Label1 -> Caption = "PUNKT DLA GRACZA PRAWEGO--->";
        } else if ((Ball->Left + Ball->Width > RightPaddle->Left + RightPaddle->Width &&
                    (Ball->Top + Ball->Height / 2 < RightPaddle->Top ||
                     Ball->Top + Ball->Height / 2 > RightPaddle->Top + RightPaddle->Height))) {
            leftPlayerPoints++;
            Label1 -> Caption = "<---PUNKT DLA GRACZA LEWEGO";
        }

        Label1 -> Visible = true;
        Label2 -> Caption = IntToStr(leftPlayerPoints) + ":" + IntToStr(rightPlayerPoints);
        Label2 -> Visible = true;
        Label3 -> Caption = "Odbicia: " +  IntToStr(movesCounter);
        Label3 -> Visible = true;
        Button2 -> Enabled = true;
        Button2 -> Visible = true;
        Button3 -> Enabled = true;
        Button3 -> Visible = true;
    }
    //left paddle bounce
    if (Ball -> Left <= LeftPaddle -> Left + LeftPaddle -> Width-5 &&
            Ball -> Top + Ball -> Height/2 <= LeftPaddle -> Top + LeftPaddle -> Height &&
            Ball -> Top + Ball -> Height/2 >= LeftPaddle -> Top) {

        movesCounter ++;
        if (movesCounter%3 == 0 && launchNyanObstacle()) {
            setRandomNyanPosition();
        }
        //
        if(x < 0) {
            //top left paddle bounce
            if (Ball -> Left <= LeftPaddle -> Left + LeftPaddle -> Width &&
                    Ball -> Top + Ball -> Height /2 <= LeftPaddle -> Top + LeftPaddle -> Height/4 &&
                    Ball -> Top + Ball -> Height /2 >= LeftPaddle -> Top) {

                x = -0.8 * x;
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
            }
        }
    }
    //right paddle bounce
    if (Ball -> Left + Ball -> Width >= RightPaddle -> Left &&
            Ball -> Top + Ball -> Height/2 <= RightPaddle -> Top + RightPaddle -> Height &&
            Ball -> Top + Ball -> Height/2 >= RightPaddle -> Top) {

        movesCounter ++;
        if (launchNyanObstacle()) {
            setRandomNyanPosition();
            NyanMovement -> Enabled = true;
        }

        if (x > 0) {
            //top right paddle bounce
            if (Ball -> Left + Ball -> Width >= RightPaddle -> Left &&
                    Ball -> Top + Ball -> Height/2 <= RightPaddle -> Top + RightPaddle -> Height / 4 &&
                    Ball -> Top + Ball -> Height/2 >= RightPaddle -> Top) {

                x = -0.8 * x;
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
            }
        }
    }
    if (ballWithNyanCollision(Ball, Obstacle)&& Obstacle -> Visible == true) {

        x = -x;
        y = -y;
        Obstacle -> Visible = false;
        NyanMovement -> Enabled = false;
        setObstacle();
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

void __fastcall TForm1::Button1Click(TObject *Sender) {
    gameInitialization();
    generateNyanRounds();
    generateObstacleSymbols();
    leftPlayerPoints = 0;
    rightPlayerPoints = 0;
    Button1 -> Enabled = false;
    Button1 -> Visible = false;
    RadioGroup1 -> Enabled = false;
    RadioGroup1 -> Visible = false;
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Button2Click(TObject *Sender) {
    Label1 -> Visible = false;
    Label2 -> Visible = false;
    Label3 -> Visible = false;
    Button2 -> Enabled = false;
    Button2 -> Visible = false;
    Button3 -> Enabled = false;
    Button3 -> Visible = false;
    Obstacle -> Enabled = false;
    Obstacle -> Visible = false;
    generateNyanRounds();
    gameInitialization();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender) {
    Label1 -> Visible = false;
    Label2 -> Visible = false;
    Label3 -> Visible = false;
    Button2 -> Enabled = false;
    Button2 -> Visible = false;
    Button3 -> Enabled = false;
    Button3 -> Visible = false;
    Obstacle -> Enabled = false;
    Obstacle -> Visible = false;
    gameInitialization();
    generateNyanRounds();
    generateObstacleSymbols();
    leftPlayerPoints = 0;
    rightPlayerPoints = 0;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::NyanMovementTimer(TObject *Sender) {
    //initial nyan movement
    Obstacle -> Top  += verticalNyanMovement;
    //top of the screen bounce
    if (Obstacle -> Top -5 <= Background -> Top) {
        verticalNyanMovement = -verticalNyanMovement;
    }
    //bottom of the screen bounce
    if (Obstacle -> Top>= Background -> Height - Background -> Top - Obstacle -> Height + 10) {
        verticalNyanMovement = -verticalNyanMovement;
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Ball2MovementTimer(TObject *Sender) {
    //initial ball movement
    Ball2 -> Left += x2;
    Ball2 -> Top  += y2;

    //top of the screen bounce
    if (Ball2 -> Top -5 <= Background -> Top) {
        y2 = -y2;
    }
    //bottom of the screen bounce
    if (Ball2 -> Top>= Background -> Height - Background -> Top - Ball2 -> Height + 10) {
        y2 = -y2;
    }
    //out of bonds
    if ((( Ball2->Left < LeftPaddle->Left  &&
            (Ball2->Top + Ball2->Height / 2 < LeftPaddle->Top ||
             Ball2->Top + Ball2->Height / 2 > LeftPaddle->Top + LeftPaddle->Height)) ||
            (Ball2->Left + Ball2->Width > RightPaddle->Left + RightPaddle->Width &&
             (Ball2->Top + Ball2->Height / 2 < RightPaddle->Top ||
              Ball2->Top + Ball2->Height / 2 > RightPaddle->Top + RightPaddle->Height)))) {

        BallMovement -> Enabled = false;
        Ball2Movement -> Enabled = false;
        Ball -> Visible = false;
        Ball2 -> Visible = false;
        Obstacle -> Visible = false;
        NyanMovement -> Enabled = false;

        if ((( Ball2->Left < LeftPaddle->Left  &&
                (Ball2->Top + Ball2->Height / 2 < LeftPaddle->Top ||
                 Ball2->Top + Ball2->Height / 2 > LeftPaddle->Top + LeftPaddle->Height)))) {

            rightPlayerPoints++;
            Label1 -> Caption = "PUNKT DLA GRACZA PRAWEGO--->";
        } else if ((Ball2->Left + Ball2->Width > RightPaddle->Left + RightPaddle->Width &&
                    (Ball2->Top + Ball2->Height / 2 < RightPaddle->Top ||
                     Ball2->Top + Ball2->Height / 2 > RightPaddle->Top + RightPaddle->Height))) {
            leftPlayerPoints++;
            Label1 -> Caption = "<---PUNKT DLA GRACZA LEWEGO";
        }
        Label1 -> Visible = true;
        Label2 -> Caption = IntToStr(leftPlayerPoints) + ":" + IntToStr(rightPlayerPoints);
        Label2 -> Visible = true;
        Label3 -> Caption = "Odbicia: " +  IntToStr(movesCounter);
        Label3 -> Visible = true;
        Button2 -> Enabled = true;
        Button2 -> Visible = true;
        Button3 -> Enabled = true;
        Button3 -> Visible = true;
    }
    //left paddle bounce
    if (Ball2 -> Left <= LeftPaddle -> Left + LeftPaddle -> Width-5 &&
            Ball2 -> Top + Ball2 -> Height/2 <= LeftPaddle -> Top + LeftPaddle -> Height &&
            Ball2 -> Top + Ball2 -> Height/2 >= LeftPaddle -> Top) {

        movesCounter ++;
        if(x2 < 0) {
            //top left paddle bounce
            if (Ball2 -> Left <= LeftPaddle -> Left + LeftPaddle -> Width &&
                    Ball2 -> Top + Ball2 -> Height /2 <= LeftPaddle -> Top + LeftPaddle -> Height/4 &&
                    Ball2 -> Top + Ball2 -> Height /2 >= LeftPaddle -> Top) {

                x2 = -0.8 * x2;
            }
            //middle left paddle bounce
            else if (Ball2 -> Left <= LeftPaddle -> Left + LeftPaddle -> Width &&
                     Ball2 -> Top + Ball2 -> Height /2 <= LeftPaddle -> Top + 2* LeftPaddle -> Height/4 &&
                     Ball2 -> Top + Ball2 -> Height /2 >= LeftPaddle -> Top + LeftPaddle -> Height/4) {

                x2 = -x2;

            }
            //bottom left paddle bounce
            else if (Ball2 -> Left <= LeftPaddle -> Left + LeftPaddle -> Width &&
                     Ball2 -> Top + Ball2 -> Height /2 <= LeftPaddle -> Top +  LeftPaddle -> Height &&
                     Ball2 -> Top + Ball2 -> Height /2 >= LeftPaddle -> Top + 1/2 * LeftPaddle -> Height) {

                x2 = -1.2 * x2;
            }
        }
    }
    //right paddle bounce
    if (Ball2 -> Left + Ball2 -> Width >= RightPaddle -> Left &&
            Ball2 -> Top + Ball2 -> Height/2 <= RightPaddle -> Top + RightPaddle -> Height &&
            Ball2 -> Top + Ball2 -> Height/2 >= RightPaddle -> Top) {
            
        movesCounter ++;
        if (x2 > 0) {
            //top right paddle bounce
            if (Ball2 -> Left + Ball2 -> Width >= RightPaddle -> Left &&
                    Ball2 -> Top + Ball2 -> Height/2 <= RightPaddle -> Top + RightPaddle -> Height / 4 &&
                    Ball2 -> Top + Ball2 -> Height/2 >= RightPaddle -> Top) {

                x2 = -0.8 * x2;
            }
            //middle right paddle bounce
            else if (Ball2 -> Left + Ball2 -> Width >= RightPaddle -> Left &&
                     Ball2 -> Top + Ball2 -> Height/2 <= RightPaddle -> Top + 2 * RightPaddle -> Height / 4 &&
                     Ball2 -> Top + Ball2 -> Height/2 >= RightPaddle -> Top) {
                x2 = -x2;
            }
            //bottom right paddle bounce
            else if (Ball2 -> Left <= RightPaddle -> Left + RightPaddle -> Width &&
                     Ball2 -> Top + Ball2 -> Height/2 <= RightPaddle -> Top + RightPaddle -> Height &&
                     Ball2 -> Top + Ball2 -> Height/2 >= RightPaddle -> Top + 1/2 * RightPaddle -> Height) {
                x2 = -1.2 * x2;
            }
        }
    }
}
//---------------------------------------------------------------------------


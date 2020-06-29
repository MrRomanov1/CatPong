//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

int x = -8;
int y = -8;
int movesCounter = 0;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BallMovementTimer(TObject *Sender)
{
     Ball -> Left +=x;
     Ball -> Top += y;

 if (Ball -> Top -5 <= Background -> Top) {
    y = -y;
 }
 if (Ball -> Top>= Background -> Height - Background -> Top - Ball -> Height + 5){
    y = -y;
 }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::LeftPaddleUpTimer(TObject *Sender)
{
     if (LeftPaddle -> Top > 5)  LeftPaddle -> Top -= 10;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RightPaddleUpTimer(TObject *Sender)
{
 if (RightPaddle -> Top > 5)  RightPaddle -> Top -= 10;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::LeftPaddleDownTimer(TObject *Sender)
{
   if (LeftPaddle -> Top + LeftPaddle -> Height < Background -> Height + 10){
     LeftPaddle -> Top += 10;
   }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
      if (Key == VK_UP){
      RightPaddleUp -> Enabled = true;
      }
      if (Key == 'a' || Key == 'A'){
      LeftPaddleUp -> Enabled = true;
      }
      if (Key == VK_DOWN){
      RightPaddleDown -> Enabled = true;
      }
      if (Key == 'z' || Key == 'Z'){
      LeftPaddleDown -> Enabled = true;
      }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
     if (Key == VK_UP){
      RightPaddleUp -> Enabled = false;
      }
      if (Key == 'a' || Key == 'A'){
      LeftPaddleUp -> Enabled = false;
      }
        if (Key == VK_DOWN){
      RightPaddleDown -> Enabled = false;
      }
      if (Key == 'z' || Key == 'Z'){
      LeftPaddleDown -> Enabled = false;
      }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RightPaddleDownTimer(TObject *Sender)
{
 if (RightPaddle -> Top + RightPaddle -> Height < Background -> Height + 10){
     RightPaddle -> Top += 10;
   }
}
//---------------------------------------------------------------------------


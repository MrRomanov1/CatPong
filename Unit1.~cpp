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
 
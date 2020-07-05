//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm {
__published:	// IDE-managed Components
    TImage *Background;
    TImage *Ball;
    TTimer *BallMovement;
    TImage *LeftPaddle;
    TImage *RightPaddle;
    TTimer *LeftPaddleUp;
    TTimer *LeftPaddleDown;
    TTimer *RightPaddleUp;
    TTimer *RightPaddleDown;
        TButton *Button1;
        TRadioGroup *RadioGroup1;
        TLabel *Label1;
        TButton *Button2;
        TButton *Button3;
        TLabel *Label2;
        TLabel *Label3;
        TImage *Obstacle;
        TTimer *NyanMovement;
    void __fastcall BallMovementTimer(TObject *Sender);
    void __fastcall LeftPaddleUpTimer(TObject *Sender);
    void __fastcall RightPaddleUpTimer(TObject *Sender);
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
                                TShiftState Shift);
    void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
                              TShiftState Shift);
    void __fastcall LeftPaddleDownTimer(TObject *Sender);
    void __fastcall RightPaddleDownTimer(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall NyanMovementTimer(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif

//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TPanel *PanelGlowny;
        TMainMenu *MainMenu1;
        TMenuItem *Plik1;
        TMenuItem *Nowy1;
        TStatusBar *StatusBar1;
        TPanel *Panel1;
        TPanel *Panel2;
        TButton *Button1;
        TPanel *PanelLog;
        TMemo *Memo1;
        TTimer *Timer1;
        TPaintBox *PaintBox1;
        TGroupBox *GroupBox1;
        TCheckBox *CheckBox1;
        TCheckBox *CheckBox2;
        TLabeledEdit *EditIlosc;
        TLabeledEdit *EditOdleglosc;
        TLabeledEdit *EditPromien;
        TLabeledEdit *EditMin;
        TComboBox *ComboBox1;
        TLabel *Label2;
        TGroupBox *GroupBox2;
        TLabeledEdit *LabeledEdit1;
        TLabel *Label1;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label6;
        TUpDown *UpDown1;
        TCheckBox *CheckBox3;
        TSpeedButton *SpeedButton2;
        TSpeedButton *SpeedButton3;
        TSpeedButton *SpeedButton4;
        TSpeedButton *SpeedButton5;
        TSpeedButton *SpeedButton6;
        TLabel *Label7;
        TCheckBox *CheckBox4;
        TMenuItem *Stop1;
        TMenuItem *Restart1;
        TLabel *Label8;
        TLabel *Label9;
        TMenuItem *Statystyki1;
        TTimer *Timer2;
        TCheckBox *CheckBox5;
        TCheckBox *CheckBox6;
        TLabel *Label10;
        TCheckBox *CheckBox7;
        TComboBox *ComboBox2;
        TImage *Image1;
        TMenuItem *N1;
        TMenuItem *Wyjie1;
        TCheckBox *CheckBox8;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall EditOdlegloscChange(TObject *Sender);
        void __fastcall EditPromienChange(TObject *Sender);
        void __fastcall EditMinChange(TObject *Sender);
        void __fastcall PaintBox1MouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall CheckBox3Click(TObject *Sender);
        void __fastcall EditIloscChange(TObject *Sender);
        void __fastcall SpeedButton2Click(TObject *Sender);
        void __fastcall SpeedButton3Click(TObject *Sender);
        void __fastcall SpeedButton4Click(TObject *Sender);
        void __fastcall SpeedButton5Click(TObject *Sender);
        void __fastcall SpeedButton6Click(TObject *Sender);
        void __fastcall Nowy1Click(TObject *Sender);
        void __fastcall Stop1Click(TObject *Sender);
        void __fastcall UpDown1Click(TObject *Sender, TUDBtnType Button);
        void __fastcall Statystyki1Click(TObject *Sender);
        void __fastcall Timer2Timer(TObject *Sender);
        void __fastcall ComboBox1Change(TObject *Sender);
        void __fastcall CheckBox2Click(TObject *Sender);
        void __fastcall CheckBox1Click(TObject *Sender);
        void __fastcall CheckBox4Click(TObject *Sender);
        void __fastcall CheckBox6Click(TObject *Sender);
        void __fastcall ComboBox2Change(TObject *Sender);
        void __fastcall Wyjie1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
 
//---------------------------------------------------------------------------

#ifndef MComanderH
#define MComanderH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include <FileCtrl.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components

        TMainMenu *MenuGlowne;
        TMenuItem *Plik1;
        TMenuItem *Edycja1;
        TMenuItem *Widok1;
        TMenuItem *Przegldaj1;
        TMenuItem *Edytuj1;
        TMenuItem *Kopiuj1;
        TMenuItem *Przenie1;
        TMenuItem *SFolder;
        TMenuItem *Usu2;
        TToolBar *ToolBar1;
        TStatusBar *StatusBar1;
        TToolButton *ToolButton1;
        TPanel *PanelGlowny;
        TPanel *PanelLewy;
        TSplitter *Splitter1;
        TPanel *PanelPrawy;
        TListView *ListView1;
        TListView *ListView2;
        TMenuItem *N1;
        TMenuItem *Zamknijprogram1;
        TMenuItem *Pomoc1;
        TToolButton *ToolButton2;
        TImageList *ImageListTOOLBOX;
        TToolButton *ToolButton3;
        TToolButton *ToolButton4;
        TToolButton *ToolButton6;
        TToolButton *ToolButton5;
        TToolButton *ToolButton7;
        TToolButton *ToolButton8;
        TToolButton *ToolButton9;
        TToolButton *ToolButton10;
        TToolButton *ToolButton11;
        TToolButton *ToolButton12;
        TToolButton *ToolButton13;
        TToolButton *ToolButton14;
        TToolButton *ToolButton15;
        TToolButton *ToolButton16;
        TToolButton *ToolButton17;
        TMenuItem *Skrtyklawiszowe1;
        TMenuItem *N2;
        TMenuItem *OMCommander1;
        TLabel *Label1;
        TLabel *Label2;
        TImageList *ImageListLISTA;
        TMenuItem *Szczegowy1;
        TMenuItem *Lista1;
        TMenuItem *Miniatury1;
        TDriveComboBox *DriveComboBox1;
        TMenuItem *Cofnij1;
        TMenuItem *Ponw1;
        TMenuItem *N3;
        TMenuItem *Pokaukryte1;
        TLabel *Label3;
        void __fastcall Szczegowy1Click(TObject *Sender);
        void __fastcall Miniatury1Click(TObject *Sender);
        void __fastcall Lista1Click(TObject *Sender);
        void __fastcall Zamknijprogram1Click(TObject *Sender);
        void __fastcall ListView1Enter(TObject *Sender);
        void __fastcall ListView2Enter(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall ListView1SelectItem(TObject *Sender,
          TListItem *Item, bool Selected);
        void __fastcall ListView2SelectItem(TObject *Sender,
          TListItem *Item, bool Selected);
        void __fastcall ListView1DblClick(TObject *Sender);
        void __fastcall DriveComboBox1Change(TObject *Sender);
        void __fastcall ListView2DblClick(TObject *Sender);
        void __fastcall Pokaukryte1Click(TObject *Sender);
        void __fastcall Kopiuj1Click(TObject *Sender);
        void __fastcall ListView1KeyPress(TObject *Sender, char &Key);
        void __fastcall ListView2KeyPress(TObject *Sender, char &Key);
        void __fastcall Usu2Click(TObject *Sender);
        void __fastcall Edytuj1Click(TObject *Sender);
        void __fastcall SFolderClick(TObject *Sender);
        void __fastcall Przenie1Click(TObject *Sender);
        void __fastcall OMCommander1Click(TObject *Sender);
        void __fastcall Skrtyklawiszowe1Click(TObject *Sender);
        void __fastcall Przegldaj1Click(TObject *Sender);

private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif

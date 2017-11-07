//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
class TFormInformacje : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TImage *Image1;
private:	// User declarations
public:		// User declarations
        __fastcall TFormInformacje(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormInformacje *FormInformacje;
//---------------------------------------------------------------------------
#endif

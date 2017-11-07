//---------------------------------------------------------------------------

#ifndef Unit4H
#define Unit4H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TFormPodglad : public TForm
{
__published:	// IDE-managed Components
        TMemo *Memo1;
private:	// User declarations
public:		// User declarations
        __fastcall TFormPodglad(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormPodglad *FormPodglad;
//---------------------------------------------------------------------------
#endif

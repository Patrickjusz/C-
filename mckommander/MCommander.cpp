//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("MComander.cpp", Form1);
USEFORM("Unit2.cpp", FormInformacje);
USEFORM("Unit3.cpp", FormSkroty);
USEFORM("Unit4.cpp", FormPodglad);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TForm1), &Form1);
                 Application->CreateForm(__classid(TFormInformacje), &FormInformacje);
                 Application->CreateForm(__classid(TFormSkroty), &FormSkroty);
                 Application->CreateForm(__classid(TFormPodglad), &FormPodglad);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        catch (...)
        {
                 try
                 {
                         throw Exception("");
                 }
                 catch (Exception &exception)
                 {
                         Application->ShowException(&exception);
                 }
        }
        return 0;
}
//---------------------------------------------------------------------------

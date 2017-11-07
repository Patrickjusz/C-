//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "Unit2.h"
#include "Unit3.h"
#include "Unit4.h"
#include "MComander.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
AnsiString sciezka1="C:\\Users\\Patryk\\Desktop\\";
AnsiString sciezka2="C:\\Users\\";
short aktywna_strona = 1;
bool pokazUkryte=0; //nie pokazuj ukrytych plikow






//--------MOJE FUNKCJE--------------
AnsiString folderUP(AnsiString sciezka) {
 int dlugosc = sciezka.Length();
 int licznik = 0; //musi osiagnac dwa
 for(int i=dlugosc; i>=0; i--) {
        if ((sciezka.SubString(i, 1))=="\\") licznik++;
        if (licznik==2)
        {
                return sciezka.SubString(0, i); //od poczatku do "folderu wyzej"
        }
 }
 return sciezka;
}




void listujFolder(AnsiString sciezka, short panel) {

 TListView * LV = new TListView(Null);
 if (panel==1) {
        LV = Form1->ListView1;
        Form1->Label1->Caption = "->"+sciezka;
        LV->Items->Clear();
        sciezka1=sciezka;}
 else   {
        LV = Form1->ListView2;
        Form1->Label2->Caption = "->"+sciezka;
        LV->Items->Clear();
        sciezka2=sciezka;
 }
 int i=0;
 AnsiString rozszerzeniePliku;
 AnsiString rozmiarPliku;
 AnsiString nazwaPliku;
 sciezka = sciezka+"*.*";
 WIN32_FIND_DATA FindFileData;
 HANDLE hFind = INVALID_HANDLE_VALUE;

 hFind = FindFirstFile(sciezka.c_str(), &FindFileData);
 if (hFind != INVALID_HANDLE_VALUE)
 {
        while (FindNextFile(hFind, &FindFileData) != 0) {
                 //if (!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) continue;     //FOLDERY

                 if ((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) && !pokazUkryte) continue;         //UKRYTE PLIKI

                 //http://msdn.microsoft.com/en-us/library/windows/desktop/gg258117(v=vs.85).aspx
                LV->Items->Add();
                LV->Items->Item[i]->Caption = FindFileData.cFileName;
                rozmiarPliku = FindFileData.nFileSizeLow;
                nazwaPliku = FindFileData.cFileName;



                if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                        LV->Items->Item[i]->ImageIndex = 0;
                        LV->Items->Item[i]->SubItems->Add("<DIR>");
               } else    {
                //0 folder, 1 niewiadomy, 2 pusty plik, 3 film, 4 html, 5 folder otwarty, 6 zdjecie , 7 rar, 8 aplikacja
                        rozszerzeniePliku = nazwaPliku.SubString(nazwaPliku.Length()-3, 4);
                        if (rozszerzeniePliku==".txt" || rozszerzeniePliku==".ini")
                                LV->Items->Item[i]->ImageIndex = 2;
                        else if (rozszerzeniePliku==".jpg" || rozszerzeniePliku==".bmp" || rozszerzeniePliku=="peg" || rozszerzeniePliku==".png" || rozszerzeniePliku==".gif")
                                LV->Items->Item[i]->ImageIndex = 6;
                        else if (rozszerzeniePliku==".avi")
                                LV->Items->Item[i]->ImageIndex = 3;
                        else if (rozszerzeniePliku=="html")
                                LV->Items->Item[i]->ImageIndex = 4;
                        else if (rozszerzeniePliku==".rar" || rozszerzeniePliku==".zip")
                                LV->Items->Item[i]->ImageIndex = 7;
                        else if (rozszerzeniePliku==".exe")
                                LV->Items->Item[i]->ImageIndex = 8;
                        else    LV->Items->Item[i]->ImageIndex = 1;
                        //DETEKCJA ROZMIAROWA pliku---------------------------------
                        if (rozmiarPliku!=" ") {    //NIE MAM POJECIA CZEMU TO USUNELO BLAD z eksploracja C:\\
                        if (rozmiarPliku.ToInt()>=1024) {
                                rozmiarPliku=(rozmiarPliku.ToInt()/1024);
                                if (rozmiarPliku.ToInt()>=1024) {
                                        rozmiarPliku=(rozmiarPliku.ToInt()/1024);
                                        if (rozmiarPliku.ToInt()>=1024) {
                                                rozmiarPliku=(rozmiarPliku.ToInt()/1024);
                                                LV->Items->Item[i]->SubItems->Add(rozmiarPliku+"> GB");
                                        }
                                        else
                                                LV->Items->Item[i]->SubItems->Add(rozmiarPliku+" MB");
                                }
                                else
                                        LV->Items->Item[i]->SubItems->Add(rozmiarPliku+" KB");
                        } else {
                                LV->Items->Item[i]->SubItems->Add(rozmiarPliku+" B");
                        }           }
                        //----------------------------------------------------------
                }
                        
                LV->Items->Item[i]->SubItems->Add(FindFileData.ftCreationTime.dwLowDateTime);
                i++;
        }
                FindClose(hFind);
        }
}

bool czyFolder(AnsiString sciezka)
{
  DWORD tmp = GetFileAttributesA(sciezka.c_str());
  if (tmp == INVALID_FILE_ATTRIBUTES)
    return false;
    else if (tmp & FILE_ATTRIBUTE_DIRECTORY)
    return true;

  return false;
}

void odswiezPanele() {
listujFolder(sciezka1, 1);
listujFolder(sciezka2, 2);
}

void wejdzDoFolderu(short wybor) {
   if (wybor==1) {
   if (Form1->ListView1->Selected) {
      if (czyFolder(Form1->Label1->Caption)) {
                if (Form1->ListView1->Selected->Index==0) {
                       listujFolder(folderUP(sciezka1),1);
                       Form1->Label1->Caption = sciezka1;

                } else {
                        listujFolder(Form1->Label1->Caption+"\\", 1);
                        Form1->Label1->Caption = sciezka1;
                }
      }
   }
   }

   ///-
   if (wybor==2) {
   if (Form1->ListView2->Selected) {
      if (czyFolder(Form1->Label2->Caption)) {
                if (Form1->ListView2->Selected->Index==0) {
                       listujFolder(folderUP(sciezka2),2);
                       Form1->Label2->Caption = sciezka2;

                } else {
                        listujFolder(Form1->Label2->Caption+"\\", 2);
                        Form1->Label2->Caption = sciezka2;

                }
      }
   }
}
}
//---------------------------------------------------------------------------

//----------MOJE KLASY--------------

//----------------------------------

//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------











void __fastcall TForm1::Szczegowy1Click(TObject *Sender)
{       if (aktywna_strona==1)
                ListView1->ViewStyle = vsReport;
        else
                ListView2->ViewStyle = vsReport;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Miniatury1Click(TObject *Sender)
{
  if (aktywna_strona==1)
                ListView1->ViewStyle = vsIcon;
        else
                ListView2->ViewStyle = vsIcon;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Lista1Click(TObject *Sender)
{
     if (aktywna_strona==1)
                ListView1->ViewStyle = vsList;
        else
                ListView2->ViewStyle = vsList;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Zamknijprogram1Click(TObject *Sender)
{
Close();        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ListView1Enter(TObject *Sender)
{
listujFolder(sciezka1, 1);
ListView2->Color = clWhite;
ListView1->Color = TColor(RGB(190,223,236));
Label2->Font->Color = clRed;
Label1->Font->Color = clBlue;
aktywna_strona = 1;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ListView2Enter(TObject *Sender)
{
listujFolder(sciezka2, 2);
ListView1->Color = clWhite;
ListView2->Color = TColor(RGB(190,223,236));
Label1->Font->Color = clRed;
Label2->Font->Color = clBlue;
aktywna_strona = 2;
}
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------




//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
odswiezPanele();
ListView2->Color = clWhite;
ListView1->Color = TColor(RGB(190,223,236));
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------



//---------------------------------------------------------------------------


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

void __fastcall TForm1::ListView1SelectItem(TObject *Sender,
      TListItem *Item, bool Selected)
{
AnsiString tmp_sciezka;
if (ListView1->Selected)
        tmp_sciezka = sciezka1+ListView1->Items->Item[ListView1->Selected->Index]->Caption;
Label1->Caption = tmp_sciezka;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ListView2SelectItem(TObject *Sender,
      TListItem *Item, bool Selected)
{
AnsiString tmp_sciezka;
if (ListView2->Selected)
        tmp_sciezka = sciezka2+ListView2->Items->Item[ListView2->Selected->Index]->Caption;
Label2->Caption = tmp_sciezka;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ListView1DblClick(TObject *Sender)
{
        wejdzDoFolderu(1);
}
//---------------------------------------------------------------------------




//---------------------------------------------------------------------------

void __fastcall TForm1::DriveComboBox1Change(TObject *Sender)
{
AnsiString dysk = (DriveComboBox1->Drive);
dysk+=":\\";

listujFolder(dysk, aktywna_strona);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ListView2DblClick(TObject *Sender)
{
wejdzDoFolderu(2);
}
//---------------------------------------------------------------------------




void __fastcall TForm1::Pokaukryte1Click(TObject *Sender)
{
        pokazUkryte = !pokazUkryte;
        listujFolder(sciezka1, 1);
        listujFolder(sciezka2, 2);
}
//---------------------------------------------------------------------------





void __fastcall TForm1::Kopiuj1Click(TObject *Sender)
{
if (aktywna_strona==1) {
        AnsiString a = Label1->Caption;
        AnsiString b = (sciezka2)+ListView1->Items->Item[ListView1->Selected->Index]->Caption;
        if (CopyFile(a.c_str(), b.c_str(), true)) Label3->Caption = " -> Plik skopiowano poprawnie...";
        else Label3->Caption = " -> [ ! ] Plik nie zosta³ skopiowany...";
        listujFolder(sciezka2, 2);
} else if (aktywna_strona==2) {
        AnsiString a = Label2->Caption;
        AnsiString b = (sciezka1)+ListView2->Items->Item[ListView2->Selected->Index]->Caption;
        if (CopyFile(a.c_str(), b.c_str(), true)) Label3->Caption = " -> Plik skopiowano poprawnie...";
        else Label3->Caption = " -> [ ! ] Plik nie zosta³ skopiowany...";
        listujFolder(sciezka1, 1);
}

}
//---------------------------------------------------------------------------

void __fastcall TForm1::ListView1KeyPress(TObject *Sender, char &Key)
{
if (Key == VK_RETURN) {
  wejdzDoFolderu(1);
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ListView2KeyPress(TObject *Sender, char &Key)
{
if (Key == VK_RETURN) {
  wejdzDoFolderu(2);
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Usu2Click(TObject *Sender)
{
int komunikat=-1;
AnsiString tresc;
AnsiString usun;

if (aktywna_strona==1) {
        tresc = "Czy napewno chcesz usun¹c plik "+ListView1->Items->Item[ListView1->Selected->Index]->Caption+"?";
        komunikat = MessageBox(HWND_DESKTOP,tresc.c_str(),"Ostrze¿enie!!!",MB_YESNO|MB_ICONWARNING);
        usun = (sciezka1)+ListView1->Items->Item[ListView1->Selected->Index]->Caption;
        if (komunikat==6) { //zgadzam sie na usuniecie!
        if (DeleteFile(usun)) Label3->Caption = " -> Plik usuniety poprawnie...";
        else Label3->Caption = " -> [ ! ] Plik nie zosta³ usuniety...";
        listujFolder(sciezka1, 1); }
} else if (aktywna_strona==2) {
        tresc = "Czy napewno chcesz usun¹c plik "+ListView2->Items->Item[ListView2->Selected->Index]->Caption+"?";
        komunikat = MessageBox(HWND_DESKTOP,tresc.c_str(),"Ostrze¿enie!!!",MB_YESNO|MB_ICONWARNING);
        usun = (sciezka2)+ListView2->Items->Item[ListView2->Selected->Index]->Caption;
        if (komunikat==6) { //zgadzam sie na usuniecie!
        if (DeleteFile(usun)) Label3->Caption = " -> Plik usuniety poprawnie...";
        else Label3->Caption = " -> [ ! ] Plik nie zosta³ usuniety...";
        listujFolder(sciezka2, 2); }
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edytuj1Click(TObject *Sender)
{

AnsiString edytuj;
if (aktywna_strona==1) {
        if ((ListView1->Selected) && !czyFolder((sciezka1)+ListView1->Items->Item[ListView1->Selected->Index]->Caption)) {
                edytuj = "notepad "+(sciezka1)+ListView1->Items->Item[ListView1->Selected->Index]->Caption;
                system(edytuj.c_str()); }
        }
else if (aktywna_strona==2) {
         if ((ListView2->Selected) && !czyFolder((sciezka2)+ListView2->Items->Item[ListView2->Selected->Index]->Caption)) {
                edytuj = "notepad "+(sciezka2)+ListView2->Items->Item[ListView2->Selected->Index]->Caption;
                system(edytuj.c_str());
         }
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SFolderClick(TObject *Sender)
{
AnsiString nazwa;
if (aktywna_strona==1) {
        AnsiString komunikat = InputBox("Informacja", "Podaj nazwe nowego folderu:", "Nowy folder");
        nazwa = sciezka1+komunikat;
        if (komunikat!="") {
                if (CreateDirectory(nazwa.c_str(), NULL)) Label3->Caption = " -> Folder utworzony...";
                else Label3->Caption = " -> [ ! ] Folder nie zosta³ utworzony...";
                listujFolder(sciezka1, 1);
        }
}

if (aktywna_strona==2) {
        AnsiString komunikat = InputBox("Informacja", "Podaj nazwe nowego folderu:", "Nowy folder");
        nazwa = sciezka2+komunikat;
        if (komunikat!="") {
                if (CreateDirectory(nazwa.c_str(), NULL)) Label3->Caption = " -> Folder utworzony...";
                else Label3->Caption = " -> [ ! ] Folder nie zosta³ utworzony...";
                listujFolder(sciezka2, 2);
        }
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Przenie1Click(TObject *Sender)
{
if (aktywna_strona==1) {
        AnsiString a = Label1->Caption;
        AnsiString b = (sciezka2)+ListView1->Items->Item[ListView1->Selected->Index]->Caption;
        if (MoveFile(a.c_str(), b.c_str())) Label3->Caption = " -> Plik przeniesiono poprawnie...";
        else Label3->Caption = " -> [ ! ] Plik nie zosta³ przeniesiony...";
        listujFolder(sciezka1, 1);
        listujFolder(sciezka2, 2);
} else if (aktywna_strona==2) {
        AnsiString a = Label2->Caption;
        AnsiString b = (sciezka1)+ListView2->Items->Item[ListView2->Selected->Index]->Caption;
        if (MoveFile(a.c_str(), b.c_str())) Label3->Caption = " -> Plik przeniesiono poprawnie...";
        else Label3->Caption = " -> [ ! ] Plik nie zosta³ przeniesiony...";
        listujFolder(sciezka1, 1);
        listujFolder(sciezka2, 2);
}
}
//---------------------------------------------------------------------------


void __fastcall TForm1::OMCommander1Click(TObject *Sender)
{
FormInformacje->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Skrtyklawiszowe1Click(TObject *Sender)
{
FormSkroty->ShowModal();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Przegldaj1Click(TObject *Sender)
{
if (aktywna_strona==1 && ListView1->Selected) {
        AnsiString plik = (sciezka1)+ListView1->Items->Item[ListView1->Selected->Index]->Caption;
        if (!czyFolder(plik)) {
        FormPodglad->Memo1->Lines->LoadFromFile(plik);
        FormPodglad->ShowModal();
        }
}

if (aktywna_strona==2 && ListView2->Selected) {
        AnsiString plik = (sciezka2)+ListView2->Items->Item[ListView2->Selected->Index]->Caption;
        if (!czyFolder(plik)) {
        FormPodglad->Memo1->Lines->LoadFromFile(plik);
        FormPodglad->ShowModal();
        }
}

}
//---------------------------------------------------------------------------


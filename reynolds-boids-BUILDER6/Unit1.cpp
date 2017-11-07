//---------------------------------------------------------------------------

#include <vcl.h>
#include <math.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

//
bool pierwsze_uruchomienie=true;
//bool bez_wielkosci = true;
int iloscBoidow = 50;
int iloscPrzeszkod = 5;
int iloscJedzenia = 50;
int d = 60;
int r = 120;
double waga = 0.2;
int min = 10;
//KLASY

  class Boid {
        public:
                double x, y, vx, vy;
                Boid();
                int ileSasiadow;
                int wielkosc;
                int zjedzone;
  };
  Boid::Boid() {
        vx =4;
        vy=4;
        ileSasiadow=1;
        wielkosc=5;
        zjedzone=0;
  }

//------------
Boid * boidy = new Boid[51];
Boid * przeszkody = new Boid[21];
Boid * jedzenie = new Boid[51];
//------------


//funkcje
bool czySasiad(Boid e, Boid b, int dd, int rr) {
/*
czy element e jest sasiadem boida b, w odleglosci d?
*/
     int ile = (b.zjedzone*10);
     if (ile>100) ile=100;
     if (sqrt( pow((e.x-b.x), 2) + pow((e.y-b.y), 2))<dd+ile)
     {

        //jest w odleglosci odpowiedniej
        double k1, k2;
       if (b.vx!=0) { k1 = atan(b.vy/b.vx); }
       if ((e.x-b.x)!=0) { k2 = atan( (e.y-b.y)/(e.x-b.x) ); }
        double wartosc = fabs(k1-k2);
        if (rr+(b.zjedzone*10)>360) rr=360; else rr=rr+(b.zjedzone*10);
        if (wartosc<rr)  {   return true; }  //jest sasiadem     [!] MODYFIKACJA
        else {  return false;}          //nie jest sasiadem


     } else
        {  return false; }              //na pewno nie jest sasiadem


}

int ileObok(Boid b) {
 int ile=1;
 for(int i=0; i<iloscBoidow; i++) {
      if (czySasiad(boidy[i], b, d,r)) {
        ile++;
      }
}
           return ile;
}

void limitPredkosci() {
for(int i=0; i<iloscBoidow; i++) {
 if ((boidy[i].vx*boidy[i].vx+boidy[i].vy*boidy[i].vy)>4 || (boidy[i].vx*boidy[i].vx+boidy[i].vy*boidy[i].vy)<-4)
 {
   boidy[i].vx=0.75*boidy[i].vx;
   boidy[i].vy=0.75*boidy[i].vy;
 }
 if ((boidy[i].vx>-0.2 && boidy[i].vx<0.2) && (boidy[i].vy>-0.2 && boidy[i].vy<0.2)) { if (boidy[i].vy==0 && boidy[i].vx==0){ boidy[i].vy=random(4)-2; boidy[i].vx=random(4)-2;} boidy[i].vx = -boidy[i].vx; boidy[i].vy = -boidy[i].vy; } //anty-bezruch.
}
}
void predkosciKierunek(Boid & b) {
    int ile=0;
    double vxsrednia=0, vysrednia=0;


    for(int i=0; i<iloscBoidow; i++) {
       if (czySasiad(boidy[i], b, d,r))
       {
        vxsrednia = vxsrednia + boidy[i].vx;
        vysrednia = vysrednia + boidy[i].vy;
        ile=ile+1;
       }
    }
    vxsrednia = vxsrednia/ile;
    vysrednia = vysrednia/ile;

    b.vx = b.vx+(waga*(vxsrednia-b.vx));
    b.vy = b.vy+(waga*(vysrednia-b.vy));
    limitPredkosci();
}

void srodekGrupy(Boid & b, int num) {
    double odlegloscsrednia=0;
    long double sx, sy;
    int ile=0;
    long double odl=0;
    double tmp_a, tmp_b;
    for(int i=0; i<iloscBoidow; i++) {
      if (czySasiad(boidy[i], b, d,r)) {
         sx = boidy[i].x;
         sy = boidy[i].y;

         tmp_a = sx-b.x;
         tmp_b = sy-b.y;
         //if (tmp_a!=0 && tmp_b!=0)

         odlegloscsrednia = odlegloscsrednia + sqrt(pow(tmp_a, 2)+pow(tmp_b, 2));
         ile=ile+1;
      }
    }
    if (ile!=0)
      odlegloscsrednia = odlegloscsrednia/ile;
      //Form1->Label1->Caption = FloatToStr(odlegloscsrednia);
    tmp_a=tmp_b=0;
    for(int i=0; i<iloscBoidow; i++) {
      if (czySasiad(boidy[i], b, d,r)) {
         sx = boidy[i].x;
         sy = boidy[i].y;
         tmp_a = sy-b.y;
         tmp_b = sx-b.x;
         if (tmp_a!=0 && tmp_b!=0)
         odl = odl + sqrt(pow(tmp_a, 2)+pow(tmp_b, 2));
         if (odl!=0) {
         b.vx = b.vx + waga * (((sx-b.x)*(odl-odlegloscsrednia))/odl);
         b.vy = b.vy + waga * (((sy-b.y)*(odl-odlegloscsrednia))/odl); }
      }
    }

    limitPredkosci();
    }

void bezpiecznaOdleglosc(Boid & b) {
   double odl=0;
   double sx=0, sy=0;
   long double tmp_a, tmp_b;
   Boid * c = new Boid();
   c->x = b.x;
   c->y = b.y;
   c->vx = b.vx;
   c->vy = b.vy;
   double ile=1;
   for(int i=0; i<iloscBoidow; i++) {
      if (czySasiad(boidy[i], b, d,r)) {
      ile = ileObok(*c)*10;
   //   Form1->Caption = IntToStr(ile);
        sx = boidy[i].x;
        sy = boidy[i].y;
        tmp_a = sx-b.x;
        tmp_b = sy-b.y;
        //if (tmp_a>0 && tmp_b>0)
        odl = sqrt( pow(tmp_a, 2) + pow(tmp_b, 2) );
        ile = ile/10;
        if (odl!=0) {
        b.vx = b.vx - waga * ( (((sx-b.x)*(min+ile))/odl)-(sx-b.x));
        b.vy = b.vy - waga * ( (((sy-b.y)*(min+ile))/odl)-(sy-b.y));     }
      }
   }
   limitPredkosci();
}

void przeszkodyOmijaj(Boid & b) {
   double odl=0;
   double sx=0, sy=0;
   long double tmp_a, tmp_b;
   for(int i=0; i<iloscPrzeszkod; i++) {
      if (sqrt( pow((przeszkody[i].x-b.x), 2) + pow((przeszkody[i].y-b.y), 2))<16) {
        b.x = b.x+2;
        b.y = b.y+2;
        b.vx = b.vx+0.8;
        b.vy = b.vy-0.8;
      }

   }
   limitPredkosci();
}

void zaburzeniaLotu() {
  for(int i=0; i<iloscBoidow; i++) {
  if (Form1->CheckBox1->Checked)
        boidy[i].vx+=(0.1*((random(100)/100.0-0.5)*4));
  if (Form1->CheckBox2->Checked)
        boidy[i].vy+=(0.1*((random(100)/100.0-0.5)*4));
  }
}

void zjedzJedzenie() {
  double oknoX=Form1->PaintBox1->Width;
  double oknoY=Form1->PaintBox1->Height;

  for(int i=0; i<iloscBoidow; i++) {
        for(int j=0; j<iloscJedzenia; j++) {
        if (czySasiad(boidy[i], jedzenie[j], 5,360)) {
               jedzenie[j].x=random(oknoX)-10;; jedzenie[j].y=random(oknoY)-10;
               Form1->Memo1->Lines->Add(" -> Agent nr ("+IntToStr(i)+") zjad³ pokarm!   [x="+FloatToStrF(boidy[i].x, ffNumber, 7, 0)+", y="+FloatToStrF(boidy[i].y, ffNumber, 7, 0)+"]");
               if (Form1->CheckBox5->Checked)
                Form1->UpDown1->Position = i;

               if (boidy[i].wielkosc<15)
                boidy[i].wielkosc +=2;
                boidy[i].zjedzone++;
                boidy[i].vy *= 1.2;
                boidy[i].vy *= 1.2;
               }
        }
  }

}

void rysujBoidy() {

Form1->PaintBox1->Refresh();
  for(int i=0; i<iloscBoidow; i++) {

        if (StrToInt(Form1->LabeledEdit1->Text)!=i) {Form1->PaintBox1->Canvas->Pen->Color = clBlack;
                if (Form1->CheckBox8->Checked)
                Form1->PaintBox1->Canvas->Ellipse(boidy[i].x, boidy[i].y, boidy[i].x+boidy[i].wielkosc, boidy[i].y+boidy[i].wielkosc);
                else Form1->PaintBox1->Canvas->Ellipse(boidy[i].x, boidy[i].y, boidy[i].x+5, boidy[i].y+5);
        } else
                { Form1->PaintBox1->Canvas->Pen->Color = clBlue;
                if (Form1->CheckBox8->Checked)
                        Form1->PaintBox1->Canvas->Ellipse(boidy[i].x, boidy[i].y, boidy[i].x+boidy[i].wielkosc+5, boidy[i].y+boidy[i].wielkosc+5);
                else   Form1->PaintBox1->Canvas->Ellipse(boidy[i].x, boidy[i].y, boidy[i].x+8, boidy[i].y+8);
                 if (Form1->CheckBox7->Checked) {
                Form1->PaintBox1->Canvas->Pen->Color = clGray;
                double licz = (boidy[i].zjedzone*10);
                if (licz>100) licz=100;
                Form1->PaintBox1->Canvas->MoveTo(boidy[i].x, (boidy[i].y));
                Form1->PaintBox1->Canvas->LineTo(boidy[i].x+d+licz, boidy[i].y+d+licz);
                Form1->PaintBox1->Canvas->MoveTo(boidy[i].x, (boidy[i].y));
                Form1->PaintBox1->Canvas->LineTo(boidy[i].x-d-licz, boidy[i].y-d-licz);
                Form1->PaintBox1->Canvas->MoveTo(boidy[i].x, (boidy[i].y));
                Form1->PaintBox1->Canvas->LineTo(boidy[i].x+d+licz, boidy[i].y-d-licz);
                Form1->PaintBox1->Canvas->MoveTo(boidy[i].x, (boidy[i].y));
                Form1->PaintBox1->Canvas->LineTo(boidy[i].x-d-licz, boidy[i].y+d+licz);}
                 }


  }
  for (int i=0; i<iloscBoidow; i++)
  {
   if (boidy[i].x<0) boidy[i].x+=Form1->PaintBox1->Width;
   if (boidy[i].y<0) boidy[i].y+=Form1->PaintBox1->Height;
   if (boidy[i].x>Form1->PaintBox1->Width) boidy[i].x-=Form1->PaintBox1->Width;
   if (boidy[i].y>Form1->PaintBox1->Height) boidy[i].y-=Form1->PaintBox1->Height;
  }
  if (Form1->CheckBox4->Checked) {
   for(int i=0; i<iloscPrzeszkod; i++) {
        Form1->PaintBox1->Canvas->Pen->Color = clRed;
        Form1->PaintBox1->Canvas->Ellipse(przeszkody[i].x, przeszkody[i].y, przeszkody[i].x+8, przeszkody[i].y+8);

  }
  }
  if (Form1->CheckBox6->Checked) {
   for(int i=0; i<iloscJedzenia; i++) {
        Form1->PaintBox1->Canvas->Pen->Color = clGreen;
        Form1->PaintBox1->Canvas->Ellipse(jedzenie[i].x, jedzenie[i].y, jedzenie[i].x+3, jedzenie[i].y+3);
  }
  }
}

void losujBoidy() {
       randomize();
       double losujX, losujY, oknoX, oknoY, losujVX, losujVY;
       bool skocz=false;
       losujX=losujY=oknoX=oknoY=0;
       oknoX=Form1->PaintBox1->Width;
       oknoY=Form1->PaintBox1->Height;


       for(int i=0; i<iloscBoidow; i++) {
          skocz = false;
          losujX = random(oknoX)-10;
          losujY = random(oknoY)-10;
          if (losujX<0) losujX=0;
          if (losujY<0) losujY=0;
          losujVX = (random(20)/5)-2;
          losujVY = (random(20)/5)-2;
          boidy[i].vx = losujVX;
          boidy[i].vy = losujVY;
          boidy[i].x = losujX;
          boidy[i].y = losujY;

          //nizej system antyrysowania na sobie
          for(int j=0; j<iloscBoidow; j++) {
                if (czySasiad(boidy[j], boidy[i], d,r) && j!=i) {
                        skocz = true;
                        break;
                }
          }
          if (skocz==true) { i = i-1; continue; }
       }

       //teraz przeszkody
       for(int i=0; i<iloscPrzeszkod; i++) {
          skocz = false;
          losujX = random(oknoX)-10;
          losujY = random(oknoY)-10;
          if (losujX<0) losujX=0;
          if (losujY<0) losujY=0;
          przeszkody[i].vx = 1;
          przeszkody[i].vy = 1;
          przeszkody[i].x = losujX;
          przeszkody[i].y = losujY;

          //nizej system antyrysowania na sobie
          for(int j=0; j<iloscPrzeszkod; j++) {
                if (czySasiad(przeszkody[j], przeszkody[i], d,r) && j!=i) {
                        skocz = true;
                        break;
                }
          }

          if (skocz==true) { i = i-1; continue; }
       }
       //teraz jedzenie
       for(int i=0; i<iloscJedzenia; i++) {
          skocz = false;
          losujX = random(oknoX)-10;
          losujY = random(oknoY)-10;
          if (losujX<0) losujX=0;
          if (losujY<0) losujY=0;
          jedzenie[i].vx = 1;
          jedzenie[i].vy = 1;
          jedzenie[i].x = losujX;
          jedzenie[i].y = losujY;

          //nizej system antyrysowania na sobie
          for(int j=0; j<iloscJedzenia; j++) {
                if (czySasiad(jedzenie[j], jedzenie[i], d,r) && j!=i) {
                        skocz = true;
                        break;
                }
          }

          if (skocz==true) { i = i-1; continue; }
       }


  }
//


void aktualizujUstawienia() {

 if ((StrToInt(Form1->EditIlosc->Text))<=50 && StrToInt(Form1->EditIlosc->Text)>0) {
        iloscBoidow = StrToInt(Form1->EditIlosc->Text);
        Form1->UpDown1->Max = StrToInt(Form1->EditIlosc->Text); }
 else
        { Form1->UpDown1->Max = StrToInt(Form1->EditIlosc->Text); Form1->EditIlosc->Text = IntToStr(iloscBoidow); }

if (StrToInt(Form1->EditOdleglosc->Text)<=200 && StrToInt(Form1->EditOdleglosc->Text)>0)
        d = StrToInt(Form1->EditOdleglosc->Text); else { d=60; }
if (StrToInt(Form1->EditPromien->Text)<=360 && StrToInt(Form1->EditPromien->Text)>3)
        r = StrToInt(Form1->EditPromien->Text); else r=120;
if (StrToInt(Form1->EditMin->Text)<=100 && StrToInt(Form1->EditMin->Text)>1)
        min = StrToInt(Form1->EditMin->Text); else min=20;
}

void informacjeAgent() {
int ktory = StrToInt(Form1->LabeledEdit1->Text);
 for(int i=0; i<iloscBoidow; i++) {
        if (StrToInt(Form1->LabeledEdit1->Text)==i) {
           Form1->Label1->Caption = " x= "+FloatToStrF(boidy[ktory].x, ffNumber, 7, 2);
           Form1->Label3->Caption = " y= "+FloatToStrF(boidy[ktory].y, ffNumber, 7, 2);
           Form1->Label4->Caption = " x= "+FloatToStrF(boidy[ktory].vx, ffNumber, 7, 2);
           Form1->Label5->Caption = " y= "+FloatToStrF(boidy[ktory].vy, ffNumber, 7, 2);
           Form1->Label6->Caption = "s¹siedzi= "+IntToStr(ileObok(boidy[ktory])-2);
           Form1->Label8->Caption = "zjedzone= "+IntToStr(boidy[ktory].zjedzone);
           if (r+(boidy[ktory].zjedzone*10)<=360)
                Form1->Label9->Caption = "promieñ widzenia= "+IntToStr(r+(boidy[ktory].zjedzone*10));
           else
                Form1->Label9->Caption = "promieñ widzenia= 360";
                double licz = (boidy[ktory].zjedzone*10);
                if (licz>100) licz=100;
                Form1->Label10->Caption = "odlegloœæ widzenia= "+FloatToStr(d+licz);
        }

} }


//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Button1Click(TObject *Sender)
{
//inicjalizacja na nowo "konstruktor"
for(int i=0; i<iloscBoidow; i++) {
          boidy[i].x=0;
          boidy[i].y=0;
          boidy[i].vx=4;
          boidy[i].vy=4;
          boidy[i].ileSasiadow=1;
          boidy[i].wielkosc=5;
          boidy[i].zjedzone=0;
}

for(int i=0; i<iloscJedzenia; i++) {
          jedzenie[i].x=0;
           jedzenie[i].y=0;
           jedzenie[i].vx=1;
           jedzenie[i].vy=1;
           jedzenie[i].ileSasiadow=1;
           jedzenie[i].wielkosc=5;
           jedzenie[i].zjedzone=0;
}

for(int i=0; i<iloscPrzeszkod; i++) {
          przeszkody[i].x=0;
           przeszkody[i].y=0;
           przeszkody[i].vx=1;
           przeszkody[i].vy=1;
           przeszkody[i].ileSasiadow=1;
           przeszkody[i].wielkosc=5;
           przeszkody[i].zjedzone=0;
}
//--------------------------------

aktualizujUstawienia();
losujBoidy();
rysujBoidy();
Timer1->Enabled = True;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Timer1Timer(TObject *Sender)
{

//rysujBoidy();

//Sleep(1);

 for(int i=0; i<iloscBoidow; i++)
 {
   boidy[i].x = boidy[i].x+boidy[i].vx;
   boidy[i].y = boidy[i].y+boidy[i].vy;
   if (CheckBox4->Checked) {
       przeszkodyOmijaj(boidy[i]);
   }

   bezpiecznaOdleglosc(boidy[i]);
   predkosciKierunek(boidy[i]);
   srodekGrupy(boidy[i], i);
   if (CheckBox3->Checked)
        informacjeAgent();
   if (Form1->CheckBox1->Checked || Form1->CheckBox2->Checked)
        zaburzeniaLotu();
  if (CheckBox6->Checked) {
   zjedzJedzenie();
  }
 }
 rysujBoidy();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormCreate(TObject *Sender)
{
aktualizujUstawienia();
UpDown1->Associate = Form1->LabeledEdit1;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::EditOdlegloscChange(TObject *Sender)
{
double value;
    if(TryStrToFloat(EditOdleglosc->Text, value) )
    {
        aktualizujUstawienia();
        //losujBoidy();
        //rysujBoidy();
        Timer1->Enabled = True;
    } else EditOdleglosc->Text = IntToStr(d);
}

//---------------------------------------------------------------------------

void __fastcall TForm1::EditPromienChange(TObject *Sender)
{
double value;
    if(TryStrToFloat(EditPromien->Text, value) && EditPromien->Text>3)
    {
        aktualizujUstawienia();
        //losujBoidy();
        //rysujBoidy();
       // Timer1->Enabled = True;
    }  else EditPromien->Text = IntToStr(r);
}

//---------------------------------------------------------------------------

void __fastcall TForm1::EditMinChange(TObject *Sender)
{
double value;
    if(TryStrToFloat(EditMin->Text, value) )
    {
        aktualizujUstawienia();
        //losujBoidy();
        //rysujBoidy();
        Timer1->Enabled = True;
    }  else EditMin->Text = IntToStr(min);
}

//---------------------------------------------------------------------------







void __fastcall TForm1::PaintBox1MouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
Form1->StatusBar1->Panels->Items[0]->Text = "x="+IntToStr(X)+", y="+IntToStr(Y)+"    ";
}
//---------------------------------------------------------------------------


void __fastcall TForm1::CheckBox3Click(TObject *Sender)
{
if (CheckBox3->Checked) Form1->LabeledEdit1->Enabled = True; else Form1->LabeledEdit1->Enabled = False;
}
//---------------------------------------------------------------------------





void __fastcall TForm1::EditIloscChange(TObject *Sender)
{

    if(StrToInt(EditIlosc->Text)<=50)
    {
       // losujBoidy();
       // aktualizujUstawienia();
       // rysujBoidy();
       // Timer1->Enabled = True;
       pierwsze_uruchomienie=true;
    } else EditIlosc->Text = 15;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::SpeedButton2Click(TObject *Sender)
{
Form2->Image1->Picture->LoadFromFile("grafika\\1.jpg");
Form2->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton3Click(TObject *Sender)
{
Form2->Image1->Picture->LoadFromFile("grafika\\2.jpg");
Form2->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton4Click(TObject *Sender)
{
Form2->Image1->Picture->LoadFromFile("grafika\\3.jpg");
Form2->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton5Click(TObject *Sender)
{
Form2->Image1->Picture->LoadFromFile("grafika\\4.jpg");
Form2->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton6Click(TObject *Sender)
{
Form2->Image1->Picture->LoadFromFile("grafika\\5.jpg");
Form2->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Nowy1Click(TObject *Sender)
{
if (pierwsze_uruchomienie==true) {
        aktualizujUstawienia();
        losujBoidy();
        pierwsze_uruchomienie=false;
}
Timer1->Enabled = True;
Timer2->Enabled = True;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Stop1Click(TObject *Sender)
{
Timer1->Enabled = False;
Timer2->Enabled = False;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::UpDown1Click(TObject *Sender, TUDBtnType Button)
{
 PaintBox1->Refresh();
 for(int i=0; i<iloscBoidow; i++) {
        if (StrToInt(Form1->LabeledEdit1->Text)!=i) {Form1->PaintBox1->Canvas->Pen->Color = clBlack;
        Form1->PaintBox1->Canvas->Ellipse(boidy[i].x, boidy[i].y, boidy[i].x+5, boidy[i].y+5);
        } else
                { Form1->PaintBox1->Canvas->Pen->Color = clBlue;
                Form1->PaintBox1->Canvas->Ellipse(boidy[i].x, boidy[i].y, boidy[i].x+8, boidy[i].y+8); }

  }
    if (Form1->CheckBox4->Checked) {
   for(int i=0; i<iloscPrzeszkod; i++) {
        Form1->PaintBox1->Canvas->Pen->Color = clRed;
        Form1->PaintBox1->Canvas->Ellipse(przeszkody[i].x, przeszkody[i].y, przeszkody[i].x+8, przeszkody[i].y+8);
  }   }
informacjeAgent();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Statystyki1Click(TObject *Sender)
{
Timer2->Enabled = True;
Form3->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer2Timer(TObject *Sender)
{
if (Form3->CheckBox1->Checked) {
int ktory=0, ile=0;
if (Timer1->Enabled == True) {
Form3->ListView1->Clear();
for(int i=0; i<iloscBoidow; i++) {
  //ktory najlepszy co?

  if (ile<boidy[i].zjedzone) { ktory = i; ile=boidy[i].zjedzone; }
}
for(int i=0; i<iloscBoidow; i++) {
Form3->ListView1->Items->Add();
if (ktory==i)
        Form3->ListView1->Items->Item[i]->Caption = IntToStr(i)+" <--";
else
        Form3->ListView1->Items->Item[i]->Caption = IntToStr(i);
Form3->ListView1->Items->Item[i]->SubItems->Add(IntToStr(boidy[i].zjedzone));
if (r+(boidy[i].zjedzone*10)<=360)
                Form3->ListView1->Items->Item[i]->SubItems->Add(IntToStr(r+(boidy[i].zjedzone*10)));
           else
                Form3->ListView1->Items->Item[i]->SubItems->Add("360");
                double licz = (boidy[i].zjedzone*10);
                if (licz>100) licz=100;
Form3->ListView1->Items->Item[i]->SubItems->Add(FloatToStr(d+licz));
Form3->ListView1->Items->Item[i]->SubItems->Add(IntToStr(ileObok(boidy[i])-1));
}
}
ktory=0;
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ComboBox1Change(TObject *Sender)
{
AnsiString a = ComboBox1->Items->Strings[ComboBox1->ItemIndex];
if (a=="Ma³e") { waga = 0.1; Form1->Memo1->Lines->Add(" [ ! ] Zmieniono wage oddzia³ywania na 0.1");} else
if (a=="Œrednie") { waga = 0.4; Form1->Memo1->Lines->Add(" [ ! ] Zmieniono wage oddzia³ywania na 0.4");} else
if (a=="Du¿e") { waga = 0.7; Form1->Memo1->Lines->Add(" [ ! ] Zmieniono wage oddzia³ywania na 0.7");} else waga=0.1;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CheckBox2Click(TObject *Sender)
{
Form1->Memo1->Lines->Add(" [ ! ] Zmieniono zaburzenia ruchu w poziomie.");        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CheckBox1Click(TObject *Sender)
{
Form1->Memo1->Lines->Add(" [ ! ] Zmieniono zaburzenia ruchu w pionie.");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CheckBox4Click(TObject *Sender)
{
Form1->Memo1->Lines->Add(" [ ! ] Zmieniono ustawienia przeszkód.");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CheckBox6Click(TObject *Sender)
{
Form1->Memo1->Lines->Add(" [ ! ] Zmieniono ustawienia pokarmu.");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ComboBox2Change(TObject *Sender)
{
AnsiString a = ComboBox2->Items->Strings[ComboBox2->ItemIndex];

if (a=="Szybkoœæ: DU¯A") { Timer1->Interval = 1; Form1->Memo1->Lines->Add(" [ ! ] Zmieniono prêdkosc symulacji na DU¯A");}
if (a=="Szybkoœæ: ŒREDNIA") { Timer1->Interval = 30; Form1->Memo1->Lines->Add(" [ ! ] Zmieniono prêdkosc symulacji na ŒREDNIA");}
if (a=="Szybkoœæ: NISKA") { Timer1->Interval = 90; Form1->Memo1->Lines->Add(" [ ! ] Zmieniono prêdkosc symulacji na NISKA");}

}
//---------------------------------------------------------------------------


void __fastcall TForm1::Wyjie1Click(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------


#include <cstdlib>
#include <iostream>
#include <sdl/SDL.h>
#include <sdl/sdl_syswm.h> 
#include <sdl/sdl_image.h>
#include <string.h>
#include <time.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>


Uint8 * keystate = SDL_GetKeyState( NULL );
using namespace std;



Uint32 start;
const int FPS=100;
float szybkoscWroga=0;




int audio_rate = 22050;                      // czestotliwosc miksera w Hz
Uint16 audio_format = AUDIO_S16SYS;  // format audio, inne opisane w dokumentacji
int audio_channels = 2;                      // chyba jasne - liczba kana³ów audio
int audio_buffers = 4096;                    // Rozmiar buforów audio w pamiêci 




SDL_Surface *ZaladujObraz(string nazwa, bool kluczuj=false)
{
 //laduje, optymalizuje png do 32bit, mozliosc kluczowania z tla
 SDL_Surface *zaladowany = NULL;
 SDL_Surface *przeksztalcony = NULL;
 zaladowany = IMG_Load(nazwa.c_str());
 
 if(zaladowany != NULL)
 {
  przeksztalcony = SDL_DisplayFormat(zaladowany);          //optymalizacja
  SDL_FreeSurface(zaladowany);

  if((przeksztalcony != NULL) && (kluczuj==true))
  {
   Uint32 kolorKlucz = SDL_MapRGB(przeksztalcony->format, 0xFF, 0xFF, 0xFF);    //kluczowanie
   SDL_SetColorKey(przeksztalcony, SDL_SRCCOLORKEY, kolorKlucz);                //kluczowanie
  }
  
 }
 return przeksztalcony;
}





class Gra {
 public:
        SDL_Rect pozycja, xy_strzal;
        SDL_Rect wrog_Pozycja[32];
        SDL_Rect serceXY[3];
        SDL_Rect pokazBonus;
        int planszaX, planszaY; 
        int klatka;
        int klatkaWroga[32];
        bool kierunek;
        double poziomSzybkosci;
        Mix_Music * music;
        Mix_Music *  shoot;
        Mix_Music *  bomb;
        Mix_Music *  manej;
        long int iloscZabitych;
        //-----metody----------
        Gra();
        ~Gra();
        void InicujGrafike(int x, int y);
        void Gra::OdswiezPlansze(int x, int y);
        void Gra::OdswiezWroga();
        void Zdarzenia();
        void Sterowanie();
        void Shoot(int x, int y);
        void DodajPunkty(int ile=0);
        void zycia(int ile);
        void rysujSerca(int ile);
        void bonus();
        void dzwiek();
        void MenuGlowne();
        
 private:
         int wielkoscGracza;
         int wielkoscWroga1;
         long int iloscPunktow;
         int iloscBomb;
         int iloscZyc;
         char punktTMP[12];
         SDL_Surface *plansza;
         SDL_Surface *gracz[2];
         SDL_Surface *t_gracz[2]; //klatki w tyl
         SDL_Surface *wrog1[2];
         SDL_Surface *ekran;
         SDL_Surface *strzal;
         SDL_Surface *t_strzal;
         SDL_Event zdarzenie;  
         SDL_Surface * punkty;
         SDL_Surface * serce;
         SDL_Surface * bomby;
         SDL_Surface * mapaKrwi;
         SDL_Surface * krew;
         SDL_Surface * splashscreen;  //menu glowne
         SDL_Surface * enter; //napis press
         SDL_Surface * wybuch;
         SDL_Color kolor;  
         SDL_Rect punktyXY;
         bool exit;
         TTF_Font *font;

         //-----metody----------
         void Exit();
         
};




Gra::Gra() {
       //konstruktor klasy
       srand ( time(NULL) );
       this->exit=false;
       this->wielkoscGracza = 28;
       this->wielkoscWroga1 = 28;
       this->pozycja.x = 100;
       this->pozycja.y=219;
       this->pozycja.w=pozycja.x+wielkoscGracza;
       this->pozycja.h=pozycja.y+wielkoscGracza;   
       this->planszaX = 900;
       this->planszaY = 600;
       this->klatka=0;
       this->kierunek=1;
       this->iloscPunktow=0;
       this->iloscBomb=0;
       this->poziomSzybkosci=0.3;
       this->iloscZabitych=1;
       for (int i=0; i<32; i++) {
           klatkaWroga[i]= (rand()%1);
       }
       
       this->kierunek=1;

       for (int i=0; i<32; i++) {
           this->wrog_Pozycja[i].x=(rand() % 1000)+planszaX;
           this->wrog_Pozycja[i].y=(rand() % planszaY)-100;
           this->wrog_Pozycja[i].w=wrog_Pozycja[i].x+wielkoscWroga1;
           this->wrog_Pozycja[i].h=wrog_Pozycja[i].y+wielkoscWroga1;  
       }
       
       for(int i=0; i<3; i++) {
           serceXY[i].y=555;
       }
       
       serceXY[0].x=785;
       serceXY[1].x=814;
       serceXY[2].x=842;

       
      kolor.r=255;
      kolor.g=255;
      kolor.b=255;
      punkty = TTF_RenderText_Solid(font, "SDL ttf", kolor);
      this->punktyXY.x=540;
      this->punktyXY.y=550;
      iloscZyc=3;
       
       
       
}

void Gra::Exit() {
     if( zdarzenie.type == SDL_QUIT )
            {
                exit = true;
            }
}



Gra::~Gra() {
        //destruktor klasy 
        SDL_FreeSurface(*gracz);
        SDL_FreeSurface(plansza);
        SDL_FreeSurface(ekran); 
        SDL_Quit();
}







void Gra::InicujGrafike(int x, int y) {
if(TTF_Init()!=0) 
     {
        fprintf( stderr, "Unable to init SDL_ttf: %s\n",TTF_GetError());
        //end
     }
     
     SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
     SDL_putenv("SDL_VIDEO_CENTERED=center");
     ekran = SDL_SetVideoMode(x, y, 32,  SDL_SWSURFACE);
     SDL_WM_SetCaption("RedSoldier", NULL);
     this->plansza = ZaladujObraz("gfx/mapa/tlo2.png");  
     this->gracz[0] = ZaladujObraz("gfx/gracz/gracz0.png", true); //KLUCZUJ
     this->gracz[1] = ZaladujObraz("gfx/gracz/gracz1.png", true); //KLUCZUJ
     this->t_gracz[0] = ZaladujObraz("gfx/gracz/t_gracz0.png", true); //KLUCZUJ
     this->t_gracz[1] = ZaladujObraz("gfx/gracz/t_gracz1.png", true); //KLUCZUJ
     this->strzal = ZaladujObraz("gfx/gracz/strzal.png", true); //KLUCZUJ
     this->t_strzal = ZaladujObraz("gfx/gracz/t_strzal.png", true); //KLUCZUJ
     this->wrog1[0] = ZaladujObraz("gfx/gracz/wrog1_1.png", true); //KLUCZUJ
     this->wrog1[1] = ZaladujObraz("gfx/gracz/wrog1_2.png", true); //KLUCZUJ
     this->serce = ZaladujObraz("gfx/zycie.png", true);
     this->bomby = ZaladujObraz("gfx/moneta.png", true);
     this->mapaKrwi = ZaladujObraz("gfx/mapa/mapakrwi.png", true);
     this->wybuch = ZaladujObraz("gfx/mapa/tlo2_explo.png", true);
     this->krew = ZaladujObraz("gfx/mapa/krew.png", true);
     splashscreen =  ZaladujObraz("gfx/splashscreen.png", true);
     enter =  ZaladujObraz("gfx/splashscreen1.png", true);
     SDL_SetAlpha(wybuch, SDL_SRCALPHA, 90); 
     font=TTF_OpenFont("gfx/czcionka.ttf", 28);
     if(!font)
     {
       fprintf(stderr, "TTF_OpenFont: %s\n", TTF_GetError());
       //end
     }
     sprintf(punktTMP, "%d", iloscPunktow);
     punkty = TTF_RenderText_Solid(font, punktTMP, kolor);
     bonus();
     iloscPunktow=0;
    // SDL_SetAlpha(krew, SDL_SRCALPHA, 200); // ustawiamy przeŸroczystoœæ
}


void Gra::dzwiek() {  
    if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) {
       cout << "Unable to initialize audio: " << Mix_GetError() << endl;   
    }
    Mix_Music * music = Mix_LoadMUS( "audio/wind.wav" );
    Mix_PlayMusic( music, - 1 );
}


void Gra::MenuGlowne(){   
int wyjscie=0;
while( !wyjscie )
    {
        while( SDL_PollEvent( & zdarzenie ) )
        {
            if( zdarzenie.type == SDL_QUIT )
            {
                exit = true;
                wyjscie = true;
            }
        }
        if( keystate[ SDLK_RETURN ] )
        {
            wyjscie = true;
        }
    SDL_BlitSurface(splashscreen, NULL, ekran, NULL);
      SDL_Flip(ekran);
      SDL_Delay(110);
      SDL_BlitSurface(enter, NULL, ekran, NULL);
      SDL_Flip(ekran);
      SDL_Delay(110);
    
    }
      
}


void Gra::DodajPunkty(int ile) {
     iloscPunktow+=ile;
     sprintf(punktTMP, "%d", iloscPunktow);        //kopiuje do charowego punktTMP ilosc punktow
     punkty = TTF_RenderText_Solid(font, punktTMP, kolor);
    
    if (iloscZabitych>15 && iloscZabitych<50) poziomSzybkosci=0.5;
    if (iloscZabitych>50 && iloscZabitych<100) poziomSzybkosci=0.6;
    if (iloscZabitych>100 && iloscZabitych<150) poziomSzybkosci=0.7;
    if (iloscZabitych>150 && iloscZabitych<200) poziomSzybkosci=0.8;
    if (iloscZabitych>200 && iloscZabitych<250) poziomSzybkosci=0.9;
    if (iloscZabitych>250 && iloscZabitych<300) poziomSzybkosci=1;
}


void    Gra::bonus() {
     int wylosowane, x, y;
    Mix_Music * manej = Mix_LoadMUS( "audio/manej.wav" );
    Mix_PlayMusic( manej, 1 );
     srand(time(NULL));
    do {  
    
        x= rand()%860;
        y= rand()%500;   
      } while (pozycja.x!=x && pozycja.y!=y);
      DodajPunkty(350);
      pokazBonus.x=x;
      pokazBonus.y=y;
      pokazBonus.w=x+25;
      pokazBonus.h=y+25;
      SDL_BlitSurface(bomby, NULL, ekran, &pokazBonus);  
     SDL_Flip(ekran);
     
}



void Gra::OdswiezWroga() {    
     if (szybkoscWroga>1.1) szybkoscWroga=0.2;
     
     szybkoscWroga+=poziomSzybkosci;
     
     for(int i=0; i<32; i++) {
             wrog_Pozycja[i].x=wrog_Pozycja[i].x-int(szybkoscWroga); 
             if(klatkaWroga[i]==0) klatkaWroga[i]=1; else klatkaWroga[i]=0;        
         
         if (wrog_Pozycja[i].x<=230) {  wrog_Pozycja[i].x=(rand() % 1000)+planszaX; iloscZyc-=1; 
            if (iloscZyc<=0) { 
                     int wyjscie=0;
                      punktyXY.x=750;
                      punktyXY.y=540;
                      this->plansza = ZaladujObraz("gfx/mapa/gameover.png"); 	
                      SDL_BlitSurface(plansza,NULL,ekran,NULL);
                      SDL_BlitSurface(punkty,NULL,ekran,&punktyXY);
                      SDL_Flip(ekran);
while( !wyjscie )
    {
        while( SDL_PollEvent( & zdarzenie ) )
        {
            if( zdarzenie.type == SDL_QUIT )
            {
                exit = true;
                wyjscie = true;
            }
        }
        if( keystate[ SDLK_ESCAPE ] )
        {
            exit = true;
                wyjscie = true;
        }  
        
        if( keystate[ SDLK_r ] )
        {
            
     //---
       //konstruktor klasy
       srand ( time(NULL) );
       this->exit=false;
       this->wielkoscGracza = 28;
       this->wielkoscWroga1 = 28;
       this->pozycja.x = 100;
       this->pozycja.y=219;
       this->pozycja.w=pozycja.x+wielkoscGracza;
       this->pozycja.h=pozycja.y+wielkoscGracza;   
       this->planszaX = 900;
       this->planszaY = 600;
       this->klatka=0;
       this->kierunek=1;
       this->iloscPunktow=0;
       this->iloscBomb=0;
       this->poziomSzybkosci=0.3;
       this->iloscZabitych=1;
       for (int i=0; i<32; i++) {
           klatkaWroga[i]= (rand()%1);
       }
       
       this->kierunek=1;

       for (int i=0; i<32; i++) {
           this->wrog_Pozycja[i].x=(rand() % 1000)+planszaX;
           this->wrog_Pozycja[i].y=(rand() % planszaY)-100;
           this->wrog_Pozycja[i].w=wrog_Pozycja[i].x+wielkoscWroga1;
           this->wrog_Pozycja[i].h=wrog_Pozycja[i].y+wielkoscWroga1;  
       }
       
       for(int i=0; i<3; i++) {
           serceXY[i].y=555;
       }
       
       serceXY[0].x=785;
       serceXY[1].x=814;
       serceXY[2].x=842;

       
      kolor.r=255;
      kolor.g=255;
      kolor.b=255;
      punkty = TTF_RenderText_Solid(font, "SDL ttf", kolor);
      this->punktyXY.x=540;
      this->punktyXY.y=550;
      iloscZyc=3;  
     //---       
            
            
            
    InicujGrafike(planszaX, planszaY);
    OdswiezPlansze(pozycja.x, pozycja.y);
             
    MenuGlowne();
     dzwiek();
    Zdarzenia();
        }          
                             
                             
                            
                             }  
            }
         }      

     }
     
     
     SDL_BlitSurface(plansza, NULL, ekran, NULL);
     SDL_BlitSurface(bomby, NULL, ekran, &pokazBonus);
     SDL_BlitSurface(mapaKrwi, NULL, ekran, NULL);
     
     if (kierunek==1) SDL_BlitSurface(gracz[klatka], NULL, ekran, &pozycja); 
     else SDL_BlitSurface(t_gracz[klatka], NULL, ekran, &pozycja); 
     
     for(int i=0; i<32; i++) {
             SDL_BlitSurface(wrog1[klatkaWroga[i]], NULL, ekran, &wrog_Pozycja[i]); 
     }
     
}

void Gra::OdswiezPlansze(int x=0, int y=0) {
     pozycja.x=x;
     pozycja.y=y;
     pozycja.w=pozycja.x+wielkoscGracza;
     pozycja.h=pozycja.y+wielkoscGracza;  
     SDL_BlitSurface(plansza, NULL, ekran, NULL);
     SDL_BlitSurface(mapaKrwi, NULL, ekran, NULL);
     if (kierunek==1) SDL_BlitSurface(gracz[klatka], NULL, ekran, &pozycja); 
     else SDL_BlitSurface(t_gracz[klatka], NULL, ekran, &pozycja); 
}

void Gra::Shoot(int x=0, int y=0) {
Mix_Music * shoot =  Mix_LoadMUS( "audio/shoot.wav" );
 
     
     
     if (kierunek==1) {
       xy_strzal.x=pozycja.x+20;
       xy_strzal.y=pozycja.y+10;
       SDL_BlitSurface(strzal, NULL, ekran, &xy_strzal); 
     } else {
       xy_strzal.x=pozycja.x-10;
       xy_strzal.y=pozycja.y+10;
       SDL_BlitSurface(t_strzal, NULL, ekran, &xy_strzal);   
     }
      
     

     
     for(int i=0; i<32; i++) {
         if ((pozycja.y>=wrog_Pozycja[i].y && pozycja.y<=wrog_Pozycja[i].y+32) && kierunek==1 && pozycja.x<=wrog_Pozycja[i].x && wrog_Pozycja[i].x<planszaX-16) {    SDL_BlitSurface(krew, NULL, mapaKrwi, &wrog_Pozycja[i]); DodajPunkty((50+(wrog_Pozycja[i].x)/100)); wrog_Pozycja[i].x=(rand() % 1000)+planszaX;   iloscZabitych++;     break;} //w przod strzal 
         if ((pozycja.y>=wrog_Pozycja[i].y && pozycja.y<=wrog_Pozycja[i].y+32) && kierunek==0 && pozycja.x>=wrog_Pozycja[i].x && wrog_Pozycja[i].x<planszaX-16) {   SDL_BlitSurface(krew, NULL, mapaKrwi, &wrog_Pozycja[i]); DodajPunkty((50+(wrog_Pozycja[i].x)/100)); wrog_Pozycja[i].x=(rand() % 1000)+planszaX;    iloscZabitych++;     break;} //w przod strzal       
     }
     rysujSerca(iloscZyc);
     SDL_BlitSurface(punkty,NULL,ekran,&punktyXY);
     SDL_BlitSurface(bomby, NULL, ekran, &pokazBonus);
     
for(int i=0; i<32; i++) {
             SDL_BlitSurface(wrog1[klatkaWroga[i]], NULL, ekran, &wrog_Pozycja[i]); 
     }
     
     
    SDL_Flip(ekran);
    Mix_PlayMusic(shoot, 0);
     SDL_BlitSurface(plansza, NULL, ekran, NULL);
     SDL_BlitSurface(mapaKrwi, NULL, ekran, NULL);
     if (kierunek==1) SDL_BlitSurface(gracz[klatka], NULL, ekran, &pozycja); 
     else SDL_BlitSurface(t_gracz[klatka], NULL, ekran, &pozycja);
     

}


bool kolizja(int x1,int y1,int s1,int w1,int x2,int y2,int s2,int w2)
{
     if( x2<=x1+s1 && x2>x1 && y2>=y1 && y2<=y1+w1) return true; else
     if( x2<=x1+s1 && x2>x1 && y2+w2>=y1 && y2+w2<=y1+w1) return true; else
     if( x2+s2<=x1+s1 && x2+s2>x1 && y2>=y1 && y2<=y1+w1) return true; else
     if( x2+s2<=x1+s1 && x2+s2>x1 && y2+w2>=y1 && y2+w2<=y1+w1) return true;
     else return false;
};  

void Gra::Sterowanie() {
   if (kolizja(pozycja.x, pozycja.y, pozycja.w, pozycja.h,  pokazBonus.x,  pokazBonus.y,   pokazBonus.w,  pokazBonus.h)) { bonus(); } else {  
     if (keystate[ SDLK_LEFT ]) {  kierunek=0; if(klatka==0) klatka=1; else klatka=0; OdswiezPlansze(this->pozycja.x-1, this->pozycja.y); }
     if (keystate[ SDLK_RIGHT ] && !(pozycja.x+1+wielkoscGracza>planszaX)) {  kierunek=1; if(klatka==0) klatka=1; else klatka=0; OdswiezPlansze(this->pozycja.x+1, this->pozycja.y); }
     if (keystate[ SDLK_UP ]) {  if(klatka==0) klatka=1; else klatka=0; OdswiezPlansze(this->pozycja.x, this->pozycja.y-1); }
     if (keystate[ SDLK_DOWN ] && !(pozycja.y+1+wielkoscGracza>planszaY-70)) {  if(klatka==0) klatka=1; else klatka=0; OdswiezPlansze(this->pozycja.x, this->pozycja.y+1); }
     if (keystate[ SDLK_SPACE ] && zdarzenie.type == SDL_KEYDOWN) {  Shoot(this->pozycja.x, this->pozycja.y); } //czy potrzeba?
     if (keystate[ SDLK_2 ] ) {  if(iloscPunktow>=1500) {  Mix_Music * shoot =  Mix_LoadMUS( "audio/bomb.wav" ); Mix_PlayMusic(shoot, 0); SDL_BlitSurface(wybuch, NULL, ekran, NULL); rysujSerca(iloscZyc); SDL_BlitSurface(punkty,NULL,ekran,&punktyXY); SDL_Flip(ekran); SDL_Delay(110);  DodajPunkty(-1500);  for(int i=0; i<32; i++) { if(wrog_Pozycja[i].x<=325) { SDL_BlitSurface(krew, NULL, mapaKrwi, &wrog_Pozycja[i]); wrog_Pozycja[i].x=(rand() % 1000)+planszaX; } } } } //czy potrzeba?
     if (keystate[ SDLK_1 ] && zdarzenie.type == SDL_KEYDOWN) {  Shoot(this->pozycja.x, this->pozycja.y); } //czy potrzeba?

}
}


void Gra::rysujSerca(int ile) {
     for(int i=0; i<ile; i++) {
            SDL_BlitSurface(serce,NULL,ekran,&serceXY[i]); }
}

void Gra::Zdarzenia() {

     while( !exit )
     {         
            start=SDL_GetTicks();
            this->Sterowanie(); 
            this->OdswiezWroga();
 
            while( SDL_PollEvent( & zdarzenie ) )
            {
                  // this->OdswiezPlansze(this->pozycja.x, this->pozycja.y);
                   this->Exit();
                   //kolizje
                   //stan obiektow
                   //rysuj obiekty
            }
            
            rysujSerca(iloscZyc);
            

         
            
            
            SDL_BlitSurface(punkty,NULL,ekran,&punktyXY);
            SDL_BlitSurface(bomby, NULL, ekran, &pokazBonus);
            
            SDL_Flip(ekran);
            if(1000/FPS>SDL_GetTicks()-start)
               SDL_Delay(1000/FPS-(SDL_GetTicks()-start));
           
   }
        
}



using namespace std;

int main(int argc, char *argv[])
{
    Gra Gra;
    Gra.InicujGrafike(Gra.planszaX, Gra.planszaY);
    Gra.OdswiezPlansze(Gra.pozycja.x, Gra.pozycja.y);
             
    Gra.MenuGlowne();
        Gra.dzwiek();
    Gra.Zdarzenia();
    return EXIT_SUCCESS;
}



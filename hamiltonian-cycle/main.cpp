#include <iostream>
#include <iomanip>
using namespace std;

struct listaElementow
{
    //lista jednokierunkowa
    listaElementow * next;
    int v;
};

// Zmienne globalne

int liczbaKrawedzi, liczbaWierzcholkow;                        // Liczba kraw�dzi i wierzcho�k�w
listaElementow **sasiedzi;                 // Tablica list s�siedztwa
int *stos;                         // Tablica-stos
int wskaznikStosu;                       // Wska�nik stosu
bool *tablicaOdwiedzin;                  // Tablica odwiedzin
int iloscCykliHamiltona = 1;

// Rekurencyjna procedura wyznaczaj�ca �cie�ki i cykle Hamiltona
// v - wierzcho�ek bie��cy
//--------------------------------------------------------------
void DFSHamilton(int v)
{
    int i;
    bool test;
    listaElementow *p;

    stos[wskaznikStosu++] = v;                // Wierzcho�ek v na stos
    if(wskaznikStosu < liczbaWierzcholkow)                  // Jest �cie�ka Hamiltona?
    {
        tablicaOdwiedzin[v] = true;          // Nie ma, odwiedzamy v
        for(p = sasiedzi[v]; p; p = p->next) // Przegl�damy s�siad�w v
            if(!tablicaOdwiedzin[p->v]) DFSHamilton(p->v); // Wywo�anie rekurencyjne
        tablicaOdwiedzin[v] = false;         // Wycofujemy si� z v
    }
    else                          // Jest �cie�ka Hamiltona
    {
        test = false;               // Zak�adamy brak cyklu
        for(p = sasiedzi[v]; p; p = p->next) // Przegl�damy s�siad�w
            if(!(p->v))               // Je�li s�siadem jest wierzcho�ek 0,
            {
                test = true;            // to mamy cykl
                break;
            }

        if(test)
        {
            cout << "[" << iloscCykliHamiltona << "] cykl: ";
            for(i = 0; i < wskaznikStosu; i++)   // Wypisujemy �cie�k� Hamiltona
                cout << setw(3) << stos[i];
            if(test) cout << setw(3) << 0; // Dla cyklu dopisujemy wierzcho�ek startowy
            cout << endl;
            iloscCykliHamiltona++;
        }

    }
    wskaznikStosu--;                       // Wierzcho�ek v usuwamy ze stosu
}

// **********************
// *** PROGRAM G��WNY ***
// **********************

int main()
{
    int i,v1,v2;
    listaElementow *p,*r;

    cin >> liczbaWierzcholkow >> liczbaKrawedzi;                // Czytamy liczb� wierzcho�k�w i kraw�dzi

    // Tworzymy tablice dynamiczne

    sasiedzi    = new listaElementow * [liczbaWierzcholkow];
    tablicaOdwiedzin = new bool [liczbaWierzcholkow];
    for(i = 0; i < liczbaWierzcholkow; i++)
    {
        sasiedzi[i]    = NULL;
        tablicaOdwiedzin[i] = false;
    }
    stos = new int [liczbaWierzcholkow];
    wskaznikStosu = 0;

    // Odczytujemy definicje kraw�dzi grafu

    for(i = 0; i < liczbaKrawedzi; i++)
    {
        cin >> v1 >> v2;
        p = new listaElementow;
        p->v = v2;
        p->next = sasiedzi[v1];
        sasiedzi[v1] = p;
        p = new listaElementow;
        p->v = v1;
        p->next = sasiedzi[v2];
        sasiedzi[v2] = p;
    }

    cout << endl;

    // Wy�wietlamy �cie�ki i cykle Hamiltona

    DFSHamilton(0);
    cout << endl << "Znaleziono " << iloscCykliHamiltona << " cykli hamiltonowskich.";

    // Usuwamy zmienne dynamiczne

    delete [] tablicaOdwiedzin;
    delete [] stos;

    for(i = 0; i < liczbaWierzcholkow; i++)
    {
        p = sasiedzi[i];
        while(p)
        {
            r = p;
            p = p->next;
            delete r;
        }
    }

    delete [] sasiedzi;


//


    return 0;
}

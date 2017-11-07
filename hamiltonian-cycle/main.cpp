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

int liczbaKrawedzi, liczbaWierzcholkow;                        // Liczba krawêdzi i wierzcho³ków
listaElementow **sasiedzi;                 // Tablica list s¹siedztwa
int *stos;                         // Tablica-stos
int wskaznikStosu;                       // WskaŸnik stosu
bool *tablicaOdwiedzin;                  // Tablica odwiedzin
int iloscCykliHamiltona = 1;

// Rekurencyjna procedura wyznaczaj¹ca œcie¿ki i cykle Hamiltona
// v - wierzcho³ek bie¿¹cy
//--------------------------------------------------------------
void DFSHamilton(int v)
{
    int i;
    bool test;
    listaElementow *p;

    stos[wskaznikStosu++] = v;                // Wierzcho³ek v na stos
    if(wskaznikStosu < liczbaWierzcholkow)                  // Jest œcie¿ka Hamiltona?
    {
        tablicaOdwiedzin[v] = true;          // Nie ma, odwiedzamy v
        for(p = sasiedzi[v]; p; p = p->next) // Przegl¹damy s¹siadów v
            if(!tablicaOdwiedzin[p->v]) DFSHamilton(p->v); // Wywo³anie rekurencyjne
        tablicaOdwiedzin[v] = false;         // Wycofujemy siê z v
    }
    else                          // Jest œcie¿ka Hamiltona
    {
        test = false;               // Zak³adamy brak cyklu
        for(p = sasiedzi[v]; p; p = p->next) // Przegl¹damy s¹siadów
            if(!(p->v))               // Jeœli s¹siadem jest wierzcho³ek 0,
            {
                test = true;            // to mamy cykl
                break;
            }

        if(test)
        {
            cout << "[" << iloscCykliHamiltona << "] cykl: ";
            for(i = 0; i < wskaznikStosu; i++)   // Wypisujemy œcie¿kê Hamiltona
                cout << setw(3) << stos[i];
            if(test) cout << setw(3) << 0; // Dla cyklu dopisujemy wierzcho³ek startowy
            cout << endl;
            iloscCykliHamiltona++;
        }

    }
    wskaznikStosu--;                       // Wierzcho³ek v usuwamy ze stosu
}

// **********************
// *** PROGRAM G£ÓWNY ***
// **********************

int main()
{
    int i,v1,v2;
    listaElementow *p,*r;

    cin >> liczbaWierzcholkow >> liczbaKrawedzi;                // Czytamy liczbê wierzcho³ków i krawêdzi

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

    // Odczytujemy definicje krawêdzi grafu

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

    // Wyœwietlamy œcie¿ki i cykle Hamiltona

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

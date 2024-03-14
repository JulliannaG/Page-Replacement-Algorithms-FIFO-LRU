// Symulacja2.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <iterator>
#include <algorithm>
#include <cctype>
#include <vector>
#include <conio.h>
#include <cstdlib>
#include <ctime>
using namespace std;
int generator() {
    int random = rand() % 20; //generowanie wartości numeru stron z przedziału <0;20>
    return random;
}
void odczyt_danych_z_pliku(int* s, string nazwa_pliku) {
    fstream plik;
    plik.open(".\\dane\\" + nazwa_pliku, ios::in);
    if (!plik.is_open())
        cout << "Plik nie zostal otwarty";
    string wartosc;
    getline(plik, wartosc); //sczytanie poczatkowego tekstu z pliku
    for (int i = 0; i < 100; i++) {
        plik >> s[i]; //zapisanie wartości do tablicy
    }
    plik.close();
}
int FIFO(int R, int* strona) {
    vector <int> pamiec; //wektor przechowujący strony w pamięci
    int N = 0; //liczba brakujących stron

    for (int i = 0; i < 100; i++) {
        if (find(pamiec.begin(), pamiec.end(), strona[i]) != pamiec.end()); //sprawdzenie czy nie ma już potrzebnej strony w pamięci
        else {
            if (pamiec.size() < R) { //sprawdzenie czy nie ma wolnego miejsca w pamięci
                pamiec.push_back(strona[i]);
                N++;
            }
            else {
                pamiec.erase(pamiec.begin()); //usunięcie pierwszej strony z pamięci
                pamiec.push_back(strona[i]); //dodanie strony na koniec wektora pamięci
                N++;
            }
        }
    }
    return N;
}
int LRU(int R, int* strona) {
    vector <int> pamiec; //wektor przechowujący strony w pamięci
    int tablica[21] = { 0 }; //tablica przechowująca numery odpowiadające czasowi ostatniego użycia danego numeru strony
    int N = 0; //ilość brakujących stron

    for (int i = 0; i < 100; i++) {
        tablica[strona[i]] = i; //przypisanie wartości 'i' elementowi tablicy, który odpowiada numerowi aktualnie używanej strony

        if (find(pamiec.begin(), pamiec.end(), strona[i]) != pamiec.end()); //sprawdzenie czy nie ma już potrzebnej trony w pamięci
        else {
            if (pamiec.size() < R) { //sprawdzenie czy jest wolne miejsce w pamięci
                pamiec.push_back(strona[i]);
                N++;
            }
            else {
                int najdawniej = 0; //wartość odpowiadająca najdawniej używanej stronie w ramce pamięci
                for (int k = 1; k < pamiec.size(); k++) {
                    if (tablica[pamiec[k]] < tablica[pamiec[najdawniej]]) //sprawdzenie, która strona spośród tych znajdujących się w pamięci była używana najdawniej
                        najdawniej = k;
                }
                pamiec.erase(pamiec.begin() + najdawniej); //usunięcie najdawniej używanej strony w pamięci
                pamiec.insert(pamiec.begin() + najdawniej, strona[i]); //wstawienie akltualnej strony w to miejsce
                N++;
            }
        }

    }
    return N;
}
int main()
{
    srand((unsigned)time(NULL)); //potrzebne do generowania losowych wartości

    int nf1 = 0; //zmienne przechowujące ilości brakujących stron dla jednego ciągu
    int nf2 = 0;
    int nf3 = 0;
    int nl1 = 0;
    int nl2 = 0;
    int nl3 = 0;

    float Nf1 = 0; //zmienne przechowujące sumę ilości brakujących stron dla 100 ciągów
    float Nf2 = 0;
    float Nf3 = 0;
    float Nl1 = 0;
    float Nl2 = 0;
    float Nl3 = 0;

    int R1 = 3; //liczba ramek pamięci
    int R2 = 5;
    int R3 = 7;

    string nazwa_pliku2 = "FIFO.csv"; //nazwy plików
    string nazwa_pliku3 = "LRU.csv";
    string nazwa_pliku4 = "wyniki_eksperymentu.csv";

    ofstream plik2;
    ofstream plik3;
    ofstream plik4;

    plik2.open(".\\dane\\" + nazwa_pliku2, ios::out); //otwarcie plików
    plik3.open(".\\dane\\" + nazwa_pliku3, ios::out);
    plik2 << "Liczba brakujących stron:" << endl;
    plik3 << "Liczba brakujących stron:" << endl;
    plik2 << "ilość ramek R1=3" << ", " << "ilość ramek R3=5 " << ", " << "ilość ramek R3=7 " << endl;
    plik3 << "ilość ramek R1=3" << ", " << "ilość ramek R3=5 " << ", " << "ilość ramek R3=7 " << endl;

    for (int k = 0; k < 100; k++) { //pętla obliczająca wartości dla 100 ciągów

        string K = to_string(k + 1);
        string nazwa_pliku1 = "dane_wejsciowe" + K + ".csv"; //generowanie różnych nazw plików dla danych wejściowych
        fstream plik1;

        plik1.open(".\\dane\\" + nazwa_pliku1, ios::out);

        plik1 << "Numer strony:" << endl;

        for (int i = 0; i < 100; i++) {
            plik1 << generator() << endl;  //generowanie wartości i zapisywanie ich do pliku
        }
        plik1.close();

        int s[100]; //tablica przechowująca wartości stron

        odczyt_danych_z_pliku(&s[0], nazwa_pliku1);

        nf1 = FIFO(R1, &s[0]); //ilość brakujących stron dla obu algorytmów i dla różnych rozmiarów pamięci
        nf2 = FIFO(R2, &s[0]);
        nf3 = FIFO(R3, &s[0]);
        plik2 << nf1 << ", " << nf2 << ", " << nf3 << endl;

        nl1 = LRU(R1, &s[0]);
        nl2 = LRU(R2, &s[0]);
        nl3 = LRU(R3, &s[0]);
        plik3 << nl1 << ", " << nl2 << ", " << nl3 << endl;

        Nf1 += nf1;
        Nf2 += nf2;
        Nf3 += nf3;
        Nl1 += nl1;
        Nl2 += nl2;
        Nl3 += nl3;
    }
    plik2.close();
    plik3.close();

    plik4.open(".\\dane\\" + nazwa_pliku4, ios::out);

    plik4 << "Średnia liczba brakujących stron dla algorytmu FIFO:" << endl;
    plik4 << "ilość ramek R1=3" << ", " << "ilość ramek R3=5 " << ", " << "ilość ramek R3=7 " << endl;

    float sNf1 = Nf1 / 100; //średnia liczba brakujących stron dla 100 ciągów dla algorytmu FIFO
    float sNf2 = Nf2 / 100;
    float sNf3 = Nf3 / 100;
    plik4 << sNf1 << ", " << sNf2 << ", " << sNf3 << endl;

    plik4 << "Średnia liczba brakujących stron dla algorytmu LRU:" << endl;
    plik4 << "ilość ramek R1=3" << ", " << "ilość ramek R3=5 " << ", " << "ilość ramek R3=7 " << endl;

    float sNl1 = Nl1 / 100; //średnia liczba brakujących stron dla 100 ciągów dla algorytmu LRU
    float sNl2 = Nl2 / 100;
    float sNl3 = Nl3 / 100;
    plik4 << sNl1 << ", " << sNl2 << ", " << sNl3 << endl;
    plik4.close();

}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln

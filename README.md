# Page-Replacement-Algorithms-FIFO-LRU
Program symuluje działanie pamięci wirtualnej dla dwóch algorytmów wymiany stron - FIFO(First In First Out), LRU(Least Recently Used).
Algorytmy sa testowane dla 100 ciągów. Każdy z ciągów zawiera 100 losowo wygenerowanych wartości stron pamięci zajmowanych przez proces z
przedziału [0-20]. Wygenerowane dane wejściowe są takie same dla obu algorytmów. Dane są zapisywane do osobnych plików "dane_wejscioweN.csv" dla każdego testowanego ciągu N, następnie są one odczytane przez program. Każdy z algorytmów jest testowany dla trzech różnych wartości ramek pamięci fizycznej: R1 = 3, R2 = 5, R3 = 7.
Kryterium oceny algorytmów jest średnia ilość brakujących stron. Uzyskane wartości odpowiadające liczbie brakujących stron zostają zapisane do osobnych plików, odpowiednio dla każdego algorytmu: "FIFO.csv" oraz "LRU.csv". Następnie program wylicza średnie wartości brakujących stron dla 100 ciągów oraz zapisuje je do pliku "wyniki_eksperymentu.csv". Wszystkie pliki są tworzone w folderze "dane".


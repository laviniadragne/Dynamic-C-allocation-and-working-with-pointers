// Copyright 2019 Dragne Lavinia-Stefana 314CA
#include<stdio.h>
#include<stdlib.h>
void alocare_citire(int ** a, int * m, int n) {
    int t, j;
    for (t = 0; t < n; t++) {
    // citesc n linii de date
    scanf("%d", & m[t]);
    // citesc cate numere am pe o linie
        a[t] = (int *) malloc(m[t] * sizeof(int));
        for (j = 0; j < m[t]; j++) {
            scanf("%x", & a[t][j]);
            // citesc fiecare numar de pe o linie j
        }
    }
}
int suma_bytes(int ** a, int n, int * m) {
    char * byte = (char *) a[0];
    int s = 0, j, i;
    for (j = 0; j < (m[0] * sizeof(int)); j++) {
        s += byte[j];
    }
    // Calculez suma bytes-lor de pe prima linie
    for (i = 1; i < n; i++) {
        byte = (char *) & a[i][m[i] - 1] + 3;
        s += * byte;
    }
    // Calculez suma formata din fiecare ultim-byte de pe o linie
    byte = (char *) a[n - 1];
    for (j = (m[n - 1] * sizeof(int)) - 2; j >= 0; j--) {
        s += byte[j];
    }
    // Calculez suma bytes-lor de pe ultima linie
    for (i = n - 2; i > 0; i--) {
        byte = (char *) & a[i][0];
        s += * byte;
    }
    // Calculez suma formata din fiecare prim-byte de pe o linie
    return s;
}
void delete_char(int ** a, int linie, int bloc) {
    char * byte = (char *) a[linie];
    byte[bloc - 1] = 0;
}
// Pointez initial la incepetul unei linii date, apoi pe byte-ul
// corespunzator, dat ca parametru functiei
void delete_short(int ** a, int linie, int bloc) {
    short * byte = (short *) a[linie];
    byte[bloc - 1] = 0;
}
// Pointez initial la incepetul unei linii date, apoi pe grupul de
// bytes corespunzator, dat ca parametru functiei
void delete_int(int ** a, int linie, int bloc) {
    int * byte = (int *) a[linie];
    byte[bloc - 1] = 0;
}
// Pointez initial la incepetul unei linii date, apoi pe grupul de
// bytes corespunzator, dat ca parametru functiei
void swap_short(int ** a, int linie, int bloc) {
    char * byte = (char *) a[linie];
    char aux = byte[bloc * 2];
    byte[bloc * 2] = byte[bloc * 2 + 1];
    byte[bloc * 2 + 1] = aux;
}
// Folosind o variabila auxiliara-aux si un pointer, ce pointeaza la
// primul byte corespunzator, interschimb cei 2 bytes,
// din alcatuirea short-ului
void swap_int(int ** a, int linie, int bloc) {
    char * byte = (char *) a[linie];
    char aux = byte[bloc * 4];
    byte[bloc * 4] = byte[bloc * 4 + 3];
    byte[bloc * 4 + 3] = aux;
    aux = byte[bloc * 4 + 1];
    byte[bloc * 4 + 1] = byte[bloc * 4 + 2];
    byte[bloc * 4 + 2] = aux;
}
// Folosind o variabila auxiliara-aux si un pointer, ce pointeaza la
// primul byte corespunzator, interschimb cei 4 bytes,
// din alcatuirea int-ului
void modify_short(int ** a, int * m, int linie, int bloc, short val_noua) {
    int nr_int, i;
    nr_int = (bloc + 1) / 2;
    // calculez numarul de int-uri de care am nevoie pentru noua
    // dimensiune a hartii
    short * byte = (short *) a[linie];
    if (nr_int > m[linie]) {
        // daca dimensiunea hartii trebuie sa fie mai mare decat
        // cea actuala, realoc memorie pentru harta
        int * aux;
        aux = realloc(a[linie], nr_int * sizeof(int));
        if (aux) {
        // daca a fost posibila realocarea
            a[linie] = aux;
            for (i = m[linie] * 2; i <= bloc - 2; i++) byte[i] = 0;
                // umplu de 0 zona de short-uri pana la cel caruia trebuie sa-i
                // schimb valoarea
            m[linie] = nr_int;
        // modific numarul de int-uri de pe acea linie
            if (bloc % 2 == 1) byte[bloc] = 0;
            // valoarea short-lui, de dupa cel ce trebuie modificat,
            // din acel int, trebuie facut si el 0
        }
    }
    byte[bloc - 1] = val_noua;
    // short-ul corespunzator primeste noua valoare
}
void modify_char(int ** a, int * m, int linie, int bloc, char val_noua) {
    int nr_int, i;
    char * byte = (char *) a[linie];
    nr_int = (bloc + 3) / 4;
     // calculez numarul de int-uri de care am nevoie pentru noua
    // dimensiune a hartii
    if (nr_int > m[linie]) {
        // daca dimensiunea hartii trebuie sa fie mai mare decat
        // cea actuala, realoc memorie pentru harta
        int * aux;
        aux = realloc(a[linie], nr_int * sizeof(int));
        if (aux) {
            // daca a fost posibila realocarea
            a[linie] = aux;
            for (i = m[linie] * 4; i <= bloc - 2; i++) byte[i] = 0;
                // umplu de 0 zona de bytes pana la cel caruia trebuie sa-i
                // schimb valoarea
            m[linie] = nr_int;
        // modific numarul de int-uri de pe acea linie
            for (i = bloc; i < (nr_int) * sizeof(int); i++) byte[i] = 0;
                // umplu de 0 zona de bytes de dupa cel caruia trebuie sa-i
                // schimb valoarea
        }
    }
    byte[bloc - 1] = val_noua;
        // char-ul corespunzator primeste noua valoare
}
void modify_int(int ** a, int * m, int linie, int bloc, int val_noua) {
    int i;
    if (bloc > m[linie]) {
        // daca dimensiunea hartii trebuie sa fie mai mare decat
        // cea actuala, realoc memorie pentru harta
        int * aux;
        aux = (int *) realloc(a[linie], bloc * sizeof(int));
        if (aux) {
        // daca a fost posibila realocarea
            a[linie] = aux;
            for (i = m[linie]; i <= bloc - 2; i++) a[linie][i] = 0;
                // umplu de 0 zona de int-uri pana la cel caruia trebuie sa-i
                // schimb valoarea
            m[linie] = bloc;
            // modific numarul de int-uri de pe acea linie
        }
    }
    a[linie][bloc - 1] = val_noua;
     // int-ul corespunzator primeste noua valoare
}
int OK(int ** a, int * m, int n, int i, int j) {
    if (i < 0 || j < 0 || i >= n || j >= m[i] * sizeof(int))
        return 0; // daca coordonatele ies din matrice, returnez 0
    char * byte = (char *) a[i];
    if (byte[j] != 0)
    // daca am mai fost la casuta aceea sau nu este o gaura neagra
    // returnez 0
        return 0;
    return 1;
}
int alg_fill(int ** a, int * m, int n, int x, int y) {
    int d = 0, i, noul_i, noul_j;
    int di[4] = {-1, 0, 1, 0}, dj[4] = {0, 1, 0, -1}; // vectori de directie
    char * byte = (char *) a[x]; // pointez pe linia x
    byte[y] = 1; // marchez casuta in care ma aflu
    for (i = 0; i < 4; i++) {
        noul_i = x + di[i]; // calculam noul i pe care il vom folosi ulterior
        noul_j = y + dj[i]; // calculam noul j pe care il vom folosi ulterior
        if (OK(a, m, n, noul_i, noul_j))
        // Daca elementul vecin celui actual, executam algoritmul
            d = 1 + d + alg_fill(a, m, n, noul_i, noul_j);
            // Apelam algoritmul de fill recursiv
    }
    return d;
}
int main() {
    int n, j, i, s = 0, nr, k, val_noua, linie, bloc;
    int d, maxim = 0, i_min, j_min;
    char op, dim_date;
    // declar variabilele
    scanf("%d", & n);
    int * m = (int *) malloc(n * sizeof(int));
    // aloc spatiu pentru vectorul in care stochez numarul de elemente
    // de pe fiecare linie
    int ** a = (int **) malloc(n * sizeof(int *));
    double m_a;
    alocare_citire(a, m, n);
    // aloc si citesc harta
    s = suma_bytes(a, n, m);
    // calculez suma elementelor
    nr = (m[0] * sizeof(int)) + n - 1 + (m[n - 1] * sizeof(int)) - 1 + n - 2;
    // calculez numarul de bytes de pe conturul hartii
    m_a = (double) s / nr;
    // calculez media aritmetica
    printf("task 1\n");
    printf("%.8lf\n", m_a);
    scanf("%d ", & k);
    // citesc numarul de modificari
    for (i = 1; i <= k; i++) {
        scanf("%c %c %d%d ", & op, & dim_date, & linie, & bloc);
        if (op == 'M') {
            scanf("%x ", & val_noua);
            // daca operatia este modify, trebuie citita si noua
            // valoare a bytes-lor ce trebuie modificati
            if (dim_date == 'S')
                { modify_short(a, m, linie, bloc, val_noua);
            } else {
                 if (dim_date == 'C')
                    { modify_char(a, m, linie, bloc, val_noua);
               } else { modify_int(a, m, linie, bloc, val_noua); }
             }
             // operatia de modify pentru fiecare tip de date
        } else if (op == 'D') {
            if (dim_date == 'S') delete_short(a, linie, bloc);
            else
            if (dim_date == 'C') delete_char(a, linie, bloc);
            else
                delete_int(a, linie, bloc);
            // operatia de delete pentru fiecare tip de date
        } else {
            if (dim_date == 'S') swap_short(a, linie, bloc);
            else if (dim_date == 'I') swap_int(a, linie, bloc);
        }
        // operatia de swap pentru fiecare tip de date
    }
    printf("task 2\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m[i]; j++) printf("%08X ", a[i][j]);
        printf("\n");
    }
    // printez noua harta
    printf("task 3\n");
    for (i = 0; i < n; i++) {
        char * byte = (char *) a[i];
        for (j = 0; j < m[i] * sizeof(int); j++) {
            // parcurg harta
            if (byte[j] == 0) {
                d = 1 + alg_fill(a, m, n, i, j);
                // daca gasesc o gaura noua neagra, ii aplic
                // algoritmul de fill, pentru a-i afla supermasivitatea
                if (maxim < d) {
                    maxim = d;
                    i_min = i;
                    j_min = j;
                }
                // caut gaura neagra cu dimensiunea maxima si ii retin
                // coordonatele
            }
        }
    }
    printf("%d %d %d\n", i_min, j_min, maxim);
    // printez coordonatele gaurii negre gasite si supermasivitatea ei
    for (i = 0; i < n; i++) free(a[i]);
    free(a);
    free(m);
    // eliberez memoria
    return 0;
}

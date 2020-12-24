/*
Сформувати файл даних, компонентами якого є цілі числа.
Записати в інший файл даних максимальну непарну компоненту і мінімальну парну компоненту.
Вивести на екран вміст результуючого файлу.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <time.h>

using namespace std;

void Create(const char* fName)
{
    srand((unsigned)time(NULL));
    FILE* f;
    if ((f = fopen(fName, "wb")) == NULL)
    {
        cerr << "Помилка при відкритті файлу.\n";
        exit(1);
    }
    int x;
    for (int i = 0; i < 10; i++)
    {
        x = -20 + rand() % 41;
        fwrite(&x, sizeof(x), 1, f);
    }
    fclose(f);
}

void Print(const char* fName)
{
    cout << endl << "\nfile \"" << fName << "\":\n";
    FILE* f;
    if ((f = fopen(fName, "rb")) == NULL)
    {
        cerr << "Помилка при відкритті файлу.\n";
        exit(1);
    }

    int x;
    while (!feof(f)) {
        if (fread(&x, sizeof(x), 1, f) != 1)
            if (feof(f)) {
            break;
        }
        cout << x << " ";
    }

    cout << endl;

    fclose(f);
}

void ProcessBin(const char* fname, const char* gname) {
    FILE* f;
    FILE* g;
    if ((f = fopen(fname, "rb")) == NULL)
    {
        cerr << "Помилка при відкритті файлу.\n";
        exit(1);
    }
    if ((g = fopen(gname, "wb")) == NULL)
    {
        cerr << "Помилка при відкритті файлу.\n";
        exit(1);
    }
    int c;
    fread(&c, sizeof(c), 1, f);
    int max = c, min = c;
    while (!feof(f)) {
        if (fread(&c, sizeof(c), 1, f) != 1)
            if (feof(f)) {
                break;
            }
        if ((max % 2 == 0 && c % 2 != 0) || (c % 2 != 0 && c > max)) {
            max = c;
        }
        if ((min % 2 != 0 && c % 2 == 0) || (c % 2 == 0 && c < min)) {
            min = c;
        }
    }

    if (fwrite(&min, sizeof(int), 1, g) != 1) {
        cerr << "Error writing file." << endl;
        return;
    }
    if (fwrite(&max, sizeof(int), 1, g) != 1) {
        cerr << "Error writing file." << endl;
        return;
    }
    fclose(f);
    fclose(g);
}


int main()
{
    char f[6] = "t.dat";
    char g[6] = "g.dat";
    Create(f);
    Print(f);
    ProcessBin(f, g);
    Print(g);


    cin.get();
    return 0;
}

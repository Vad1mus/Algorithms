#include <iostream>
#include <chrono>
using namespace std;

void BYTE(unsigned char A) // виведення вмісту байта
{
    for (int bit = 128; bit >= 1; bit >>= 1)
        cout << (A & bit ? "1" : "0");
    cout << " ";
}

struct Tstruct1
{
    int s;	/* 4 bytes */
    short flip1 : 1;
    short flip2 : 1;
    short flip3 : 1;
    short flip4 : 1;
    short flip5 : 1;
    short flip6 : 4;
    short flip7 : 4;
    bool forGroup;
    union
    {
        struct
        {
            bool forKids;
            double versionOfGame;
        } tableGame;
        struct
        {
            short st;
        }computerGame;
    } un;
};

struct Tstruct2
{
    short s;	/* 4 bytes */
    int flip1;
    int flip2;
    int flip3;
    int flip4;
    int flip5;
    int flip6;
    int flip7;
    bool forGroup;
    bool forKids;
};

void main()
{
    setlocale(LC_ALL, "RUS");
    cout << "Структура с выравниванием " << endl << endl;
    auto begin = chrono::steady_clock::now();
    Tstruct1 obj1 = { 5, 1, 0, 1, 0, 1, 12, 1 };
    obj1.un.tableGame.versionOfGame = 6.5;
    obj1.un.tableGame.forKids = true;
    obj1.forGroup = true;
    auto end = chrono::steady_clock::now();
    unsigned char* p = (unsigned char*)&obj1;
    int byte = 0;
    for (; byte < sizeof(Tstruct1); byte++, p++)
    {
        if (byte && !(byte % 8)) cout << endl;
        BYTE(*p);
    }
    cout << endl << endl;
    auto elapsed_ms = chrono::duration_cast<chrono::nanoseconds>(end - begin);
    cout << "Время с выравниванием: " << elapsed_ms.count() << "ns" << endl << endl << endl;
    cout << "Структура без выравнивания " << endl << endl;
    auto begin2 = chrono::steady_clock::now();
    Tstruct2 obj2 = { 5, 1, 0, 1, 0, 1, 12, 1 };
    obj2.forGroup = true;
    obj2.forKids = true;
    auto end2 = chrono::steady_clock::now();
    p = (unsigned char*)&obj2;
    for (int byte = 0; byte < sizeof(Tstruct2); byte++, p++)
    {
        if (byte && !(byte % 8)) cout << endl;
        BYTE(*p);
    }
    cout << endl;
    auto elapsed_ms2 = chrono::duration_cast<chrono::nanoseconds>(end2 - begin2);
    cout << endl;
    cout << "Время без выравнивания : " << elapsed_ms2.count() << "ns" << endl;
}

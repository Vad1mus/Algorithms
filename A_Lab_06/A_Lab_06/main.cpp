#include <iostream>
#include <chrono>
using namespace std;

// Представление строки звеньями управляемой длины

const int BlkSize = 8; // число символов в блоке

typedef struct Block* BlkPtr; // указатель на блок

struct Block // блок

{

    char chFirst, chLast; // номера 1-го и последнего символов

    char StrData[BlkSize]; // символы

    BlkPtr next; // указатель на следующий блок

};

typedef struct StrNode* String; // тип - СТРОКА ПЕРЕМЕННОЙ ДЛИНЫ

struct StrNode // дескриптор строки

{

    long len; // длина строки

    BlkPtr first, last; // указ.на 1-й и последний блоки

};

// *** Внутр. функция-выделение нового блока

BlkPtr NewBlock()

{

    BlkPtr curr = new Block; // выделение памяти

    curr->next = NULL; // начальные значения

    curr->chFirst = 0;

    curr->chLast = 0;

    return curr;

}

//*** Внутр.функция - освобождение цепочки блока, начиная со значения bl

BlkPtr DeleteBlock(BlkPtr bl)

{

    BlkPtr buf;

    while (bl) // движение по цепочке с освобождением памяти

    {

        buf = bl;

        bl = bl->next;

        delete buf;

        buf = NULL;

    }

    return NULL; // всегда возвращает NULL

}

// *** создание строки

String NewStr()

{

    String str = new StrNode; // выделение памяти для дескриптора

    str->len = 0; // занесение в дескриптор начальных значений

    str->first = str->last = NULL;

    return str;

}

// *** уничтожение строки

void DeleteStr(String str)

{

    str->first = DeleteBlock(str->first); // уничтожение блоков

    delete str; // уничтожение дескриптора

}

// *** Определение длины строки, длина выбирается из дескриптора

long LenStr(String str)

{

    return str->len;

}

// *** Присваивание строк s1:=s2

void CopyStr(String dest, String source)

{

    BlkPtr cp1, cp2, // адреса текущих блоков для dest и source

        pp; // адрес предыдущего блока для dest

    cp1 = dest->first;

    cp2 = source->first;

    pp = NULL;

    if (source->len == 0) // если s2 пустая, освобождается вся s1

    {

        dest->first = DeleteBlock(dest->first);

        dest->last = NULL;

    }

    else

    {



        while (cp2) // перебор блоков source

        {

            if (cp1 == NULL) // если в dest больше нет блоков

            {

                cp1 = NewBlock(); // выделяется новый блок для dest

                if (dest->first == NULL) dest->first = cp1;

                else if (pp) pp->next = cp1;

            }

            *cp1 = *cp2; // копирование блока

            // к следующему блоку

            pp = cp1; cp1 = cp1->next; cp2 = cp2->next;

        }

        dest->last = pp; // последний блок

        // если в s1 остались лишние блоки - освободить их

        pp->next = DeleteBlock(pp->next);

    } // end else

    dest->len = source->len;

}

// *** Сравнение строк - возвращает:

// 0, если s1=s2; 1 - если s1>s2; -1 - если s1<s2 ***

int CompStr(String s1, String s2)

{

    char bi1, bi2;

    BlkPtr cp1, cp2;

    cp1 = s1->first;

    cp2 = s2->first;



    bi1 = cp1->chFirst;

    bi2 = cp2->chFirst;

    while (cp1 && cp2)// цикл, пока не будет достигнут конец одной из строк

    { // если соответств. символы не равны, ф-ция заканчивается

        if (cp1->StrData[bi1] > cp2->StrData[bi2]) return 1;

        else if (cp1->StrData[bi1] < cp2->StrData[bi2]) return -1;

        bi1++; // к следующему символу в s1

        if (bi1 > cp1->chLast)

        {

            cp1 = cp1->next;

            bi1 = cp1->chFirst;

        }

        bi2++; // к следующему символу в s2

        if (bi2 > cp2->chLast)

        {

            cp2 = cp2->next;

            bi2 = cp2->chFirst;

        }

    }

    // мы дошли до конца одной из строк,

    // строка меньшей длины считается меньшей

    if (s1->len < s2->len) return -1;

    else if (s1->len > s2->len) return 1;

    else return 0;

}



int main()
{

    string s1 = "ааааааааааааааааа";
    string s2 = "sdsdsdsdsdsd";


    cout << "Compare two strings s1 & s2 with Fixed-length block view:" << endl;

    cout << "String s1:" << s1 << endl;
    cout << "String s2:" << s2 << endl;
    String S1 = NewStr();
    String S2 = NewStr();


    CopyStr(S1, S2);

    auto begin2 = chrono::steady_clock::now();

    CompStr(S1, S2);
    auto end2 = chrono::steady_clock::now();
    auto elapsed_ms2 = chrono::duration_cast<chrono::nanoseconds>(end2 - begin2);
    cout << "\nFunction work time with Fixed-length block view : " << elapsed_ms2.count() << "ns" << endl;
    cout << "===============================================================";


    DeleteStr(S1);
    DeleteStr(S2);
    cout << endl << endl;









    return 0;
}
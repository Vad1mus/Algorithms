#include <iostream>
#include <chrono>
using namespace std;

// ������������� ������ �������� ����������� �����

const int BlkSize = 8; // ����� �������� � �����

typedef struct Block* BlkPtr; // ��������� �� ����

struct Block // ����

{

    char chFirst, chLast; // ������ 1-�� � ���������� ��������

    char StrData[BlkSize]; // �������

    BlkPtr next; // ��������� �� ��������� ����

};

typedef struct StrNode* String; // ��� - ������ ���������� �����

struct StrNode // ���������� ������

{

    long len; // ����� ������

    BlkPtr first, last; // ����.�� 1-� � ��������� �����

};

// *** �����. �������-��������� ������ �����

BlkPtr NewBlock()

{

    BlkPtr curr = new Block; // ��������� ������

    curr->next = NULL; // ��������� ��������

    curr->chFirst = 0;

    curr->chLast = 0;

    return curr;

}

//*** �����.������� - ������������ ������� �����, ������� �� �������� bl

BlkPtr DeleteBlock(BlkPtr bl)

{

    BlkPtr buf;

    while (bl) // �������� �� ������� � ������������� ������

    {

        buf = bl;

        bl = bl->next;

        delete buf;

        buf = NULL;

    }

    return NULL; // ������ ���������� NULL

}

// *** �������� ������

String NewStr()

{

    String str = new StrNode; // ��������� ������ ��� �����������

    str->len = 0; // ��������� � ���������� ��������� ��������

    str->first = str->last = NULL;

    return str;

}

// *** ����������� ������

void DeleteStr(String str)

{

    str->first = DeleteBlock(str->first); // ����������� ������

    delete str; // ����������� �����������

}

// *** ����������� ����� ������, ����� ���������� �� �����������

long LenStr(String str)

{

    return str->len;

}

// *** ������������ ����� s1:=s2

void CopyStr(String dest, String source)

{

    BlkPtr cp1, cp2, // ������ ������� ������ ��� dest � source

        pp; // ����� ����������� ����� ��� dest

    cp1 = dest->first;

    cp2 = source->first;

    pp = NULL;

    if (source->len == 0) // ���� s2 ������, ������������� ��� s1

    {

        dest->first = DeleteBlock(dest->first);

        dest->last = NULL;

    }

    else

    {



        while (cp2) // ������� ������ source

        {

            if (cp1 == NULL) // ���� � dest ������ ��� ������

            {

                cp1 = NewBlock(); // ���������� ����� ���� ��� dest

                if (dest->first == NULL) dest->first = cp1;

                else if (pp) pp->next = cp1;

            }

            *cp1 = *cp2; // ����������� �����

            // � ���������� �����

            pp = cp1; cp1 = cp1->next; cp2 = cp2->next;

        }

        dest->last = pp; // ��������� ����

        // ���� � s1 �������� ������ ����� - ���������� ��

        pp->next = DeleteBlock(pp->next);

    } // end else

    dest->len = source->len;

}

// *** ��������� ����� - ����������:

// 0, ���� s1=s2; 1 - ���� s1>s2; -1 - ���� s1<s2 ***

int CompStr(String s1, String s2)

{

    char bi1, bi2;

    BlkPtr cp1, cp2;

    cp1 = s1->first;

    cp2 = s2->first;



    bi1 = cp1->chFirst;

    bi2 = cp2->chFirst;

    while (cp1 && cp2)// ����, ���� �� ����� ��������� ����� ����� �� �����

    { // ���� ����������. ������� �� �����, �-��� �������������

        if (cp1->StrData[bi1] > cp2->StrData[bi2]) return 1;

        else if (cp1->StrData[bi1] < cp2->StrData[bi2]) return -1;

        bi1++; // � ���������� ������� � s1

        if (bi1 > cp1->chLast)

        {

            cp1 = cp1->next;

            bi1 = cp1->chFirst;

        }

        bi2++; // � ���������� ������� � s2

        if (bi2 > cp2->chLast)

        {

            cp2 = cp2->next;

            bi2 = cp2->chFirst;

        }

    }

    // �� ����� �� ����� ����� �� �����,

    // ������ ������� ����� ��������� �������

    if (s1->len < s2->len) return -1;

    else if (s1->len > s2->len) return 1;

    else return 0;

}



int main()
{

    string s1 = "�����������������";
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
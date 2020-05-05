#include <iostream>
#include <chrono>
using namespace std;



const int BlkSize = 8; // число символов в блоке

typedef struct Block* BlkPtr; // указатель на блок

struct Block // блок

{

	char chFirst, chLast; // номера 1-го и последнего символов

	char StrData[BlkSize]; // символы

	BlkPtr next; // указатель на следующий блок

};


// Представление строк вектором с управляемой длиной

typedef struct StrNode* String; // тип - СТРОКА ПЕРЕМЕННОЙ ДЛИНЫ

struct StrNode // дескриптор строки

{

	unsigned short MaxLen, Len; // максимальная и текущая длины

	char* str; // указатель на данные строки
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
String NewStr2()

{

	String str = new StrNode; // выделение памяти для дескриптора

	str->Len = 0; // занесение в дескриптор начальных значений

	str->first = str->last = NULL;

	return str;

}

// *** уничтожение строки

void DeleteStr2(String str)

{

	str->first = DeleteBlock(str->first); // уничтожение блоков

	delete str; // уничтожение дескриптора

}



// *** Сравнение строк - возвращает:


int CompStr2(String s1, String s2)

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

	if (s1->Len < s2->Len)
	{
		cout << "s1 < s2" << endl;
		return -1;
	}

	else if (s1->Len > s2->Len)
	{
		cout << "s1 > s2" << endl;
		return 1;
	}

	else
	{
		cout << "s1 = s2" << endl;
		return 0;
	}

}

/////////////////////////////////////////////ВТОРОЙ СПОСОБ ПРЕДСТАВЛЕНИЯ///////////////////////////////////////////////////

// Создание строки; len - максимальная длина строки;

// ф-ция возвращает указатель на дескриптор строки

String NewStr(int len)

{

	String s = new StrNode; // выделение памяти для дескриптора

	s->MaxLen = len; // занесение в дескриптор начальных значений

	s->Len = 0;

	s->str = new char[len + 1]; // выделение памяти для данных

	return s;

}

// уничтожение строки

void DeleteStr(String s)

{

	if (s)

	{

		if (s->Len > 0) delete[] s->str; // уничтожение данных

		delete s; // уничтожение дескриптора

	}

}


void CopyStr2(String dest, String source)

{

	BlkPtr cp1, cp2, // адреса текущих блоков для dest и source

		pp; // адрес предыдущего блока для dest

	cp1 = dest->first;

	cp2 = source->first;

	pp = NULL;

	if (source->Len == 0) // если s2 пустая, освобождается вся s1

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

	dest->Len = source->Len;

}

void CopyStr(String dest, string source)

{

	int len = 0;

	while (len < dest->MaxLen && source[len])

	{

		dest->str[len] = source[len];

		len++;

	}

	dest->str[len] = '\0';

	dest->Len = len;

}


// Сравнение строк - возвращает: 0, если s1=s2; 1 - если s1>s2;

// -1 - если s1<s2

char CompStr(String s1, String s2)

{

	int i = 0; // индекс текущего символа

	// цикл, пока не будет достигнут конец одной из строк

	while (i < s1->Len && i < s2->Len)

	{

		// если i-е символы не равны, функция заканчивается

		if (s1->str[i] > s2->str[i])
		{
			cout << "\nstrings are not equal\n";
			break;
		}

		else if (s1->str[i] < s2->str[i])
		{
			cout << "\nstrings are not equal\n";
			break;
		}

		i++; // переход к следующему символу

	}

	// если выполнение дошло до этой точки, то найден конец одной из

	// строк, и все сравненные до сих пор символы были равны;

	// строка меньшей длины считается меньшей

	if (s1->Len < s2->Len)
	{
		cout << "length of s1 > length of s2" << endl;

		return -1;
	}

	else if (s1->Len > s2->Len)
	{
		cout << "s1 < s2" << endl;
		return 1;
	}

	else
	{
		cout << "s1 = s2" << endl;
		return 0;
	}

}


int main()
{
	string s1 = "ppppp";
	string s2 = "ppppp";


	cout << "String s1:" << s1 << endl;
	cout << "String s2:" << s2 << endl;

	cout << "Compare two strings s1 & s2 with vector way:" << endl;
	String S1 = NewStr(s1.length());
	String S2 = NewStr(s2.length());

	CopyStr(S1, s1);
	CopyStr(S2, s2);

	auto begin = chrono::steady_clock::now();

	CompStr(S1, S2);

	auto end = chrono::steady_clock::now();
	auto elapsed_ms = chrono::duration_cast<chrono::nanoseconds>(end - begin);
	cout << "\nFunction work time is vector way: " << elapsed_ms.count() << "ns" << endl;
	cout << "===============================================================";

	DeleteStr(S1);
	DeleteStr(S2);
	cout << endl << endl;

	/////////////////////////////////////////////////////////////////////////////////////

	cout << "Compare two strings s1 & s2 with Fixed-length block view:" << endl;

	cout << "String s1:" << s1 << endl;
	cout << "String s2:" << s2 << endl;

	S1 = NewStr2();
	S2 = NewStr2();
	String S3 = NewStr2();
	String S4 = NewStr2();

	CopyStr(S1, s1);
	CopyStr(S2, s2);

	CopyStr2(S3, S1);
	CopyStr2(S4, S2);

	auto begin2 = chrono::steady_clock::now();

	CompStr2(S3, S4);
	auto end2 = chrono::steady_clock::now();
	auto elapsed_ms2 = chrono::duration_cast<chrono::nanoseconds>(end2 - begin2);
	cout << "\nFunction work time with Fixed-length block view : " << elapsed_ms.count() << "ns" << endl;
	cout << "===============================================================";


	DeleteStr2(S1);
	DeleteStr2(S2);
	cout << endl << endl;


	return 0;
}

#include <iostream>
#include <chrono>
using namespace std;



const int BlkSize = 8; // ����� �������� � �����

typedef struct Block* BlkPtr; // ��������� �� ����

struct Block // ����

{

	char chFirst, chLast; // ������ 1-�� � ���������� ��������

	char StrData[BlkSize]; // �������

	BlkPtr next; // ��������� �� ��������� ����

};


// ������������� ����� �������� � ����������� ������

typedef struct StrNode* String; // ��� - ������ ���������� �����

struct StrNode // ���������� ������

{

	unsigned short MaxLen, Len; // ������������ � ������� �����

	char* str; // ��������� �� ������ ������
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
String NewStr2()

{

	String str = new StrNode; // ��������� ������ ��� �����������

	str->Len = 0; // ��������� � ���������� ��������� ��������

	str->first = str->last = NULL;

	return str;

}

// *** ����������� ������

void DeleteStr2(String str)

{

	str->first = DeleteBlock(str->first); // ����������� ������

	delete str; // ����������� �����������

}



// *** ��������� ����� - ����������:


int CompStr2(String s1, String s2)

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

/////////////////////////////////////////////������ ������ �������������///////////////////////////////////////////////////

// �������� ������; len - ������������ ����� ������;

// �-��� ���������� ��������� �� ���������� ������

String NewStr(int len)

{

	String s = new StrNode; // ��������� ������ ��� �����������

	s->MaxLen = len; // ��������� � ���������� ��������� ��������

	s->Len = 0;

	s->str = new char[len + 1]; // ��������� ������ ��� ������

	return s;

}

// ����������� ������

void DeleteStr(String s)

{

	if (s)

	{

		if (s->Len > 0) delete[] s->str; // ����������� ������

		delete s; // ����������� �����������

	}

}


void CopyStr2(String dest, String source)

{

	BlkPtr cp1, cp2, // ������ ������� ������ ��� dest � source

		pp; // ����� ����������� ����� ��� dest

	cp1 = dest->first;

	cp2 = source->first;

	pp = NULL;

	if (source->Len == 0) // ���� s2 ������, ������������� ��� s1

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


// ��������� ����� - ����������: 0, ���� s1=s2; 1 - ���� s1>s2;

// -1 - ���� s1<s2

char CompStr(String s1, String s2)

{

	int i = 0; // ������ �������� �������

	// ����, ���� �� ����� ��������� ����� ����� �� �����

	while (i < s1->Len && i < s2->Len)

	{

		// ���� i-� ������� �� �����, ������� �������������

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

		i++; // ������� � ���������� �������

	}

	// ���� ���������� ����� �� ���� �����, �� ������ ����� ����� ��

	// �����, � ��� ���������� �� ��� ��� ������� ���� �����;

	// ������ ������� ����� ��������� �������

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

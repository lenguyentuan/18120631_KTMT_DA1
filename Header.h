#pragma once
#include <iostream>
#include <string>
#include <bitset>
#include <fstream>
#include <sstream>
using namespace std;

#define QINT_SIZE 16


// HÀM MAIN
//#include"Header.h"
//
//int main()
//{
//	Readfile();
//	system("pause");
//	return 0;
//}



class QInt
{
private:
	unsigned char bytes[QINT_SIZE];
public:
	QInt();
	~QInt();
	void scanQInt(string, int);
	void printQInt(int, ostream&);

	void output_console()
	{
		for (int i = 0; i < QINT_SIZE; i++)
		{
			cout<< bitset<8>(this->bytes[i]).to_string();
		}
		cout << endl;
	}

	void dectobin(string); //chuyển vào 1 strig dạng dec và lưu thành nhị phân
	string bintodec(string); //chuyển 1 string dạng nhị phân sang dec
	
	void hextobin(string);
	string bintohex(string);

	void bintobin(string);
	string bintostring(bool); //neu 0 thi xuat la du 128 bit, neu 1 thi xuat ra loai 0 truoc




	QInt operator& (const QInt& B) const;
	QInt operator| (const QInt& B) const;
	QInt operator^ (const QInt& B) const;
	QInt operator~ () const;

	QInt operator>> (int nums) const;
	QInt operator<< (int nums) const;
	QInt rol() const;
	QInt ror() const;
	
};

string divbytwo(string); //chia string nhu so nguyen lon cho 2

//ham cua tuan
string ReverseHexIndex(char);
char HexIndex(int);


//xu ly file
void Readfile();
void Process_operator(string, ostream&);
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




class QInt
{
private:
	unsigned char bytes[QINT_SIZE];
public:
	QInt();
	~QInt();
	void scanQInt(string, int);
	void printQInt(int, ostream&);
	string printQInt(int base);
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
	

	bool* DecToBin();
	QInt BinToDec(bool* bit);
	void hextobin(string);
	string bintohex(string);

	void bintobin(string);
	string bintostring(bool); //neu 0 thi xuat la du 128 bit, neu 1 thi xuat ra loai 0 truoc

	QInt operator =(const QInt X);
	friend QInt operator+(const QInt& A, const QInt &B);
	friend QInt operator-(const QInt& A, const QInt& B);
	friend QInt operator*(const QInt& A, const QInt& B);
	friend QInt operator/(const QInt& A, const QInt& B);
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
void Readfile(string a,string b);
void Process_operator(string, ostream&);
//int main(int argc,char*argv[])
//{
//	if (argc != 3)
//		return 0;
//	string a = argv[1];
//	string b = argv[2];
//	Readfile(a,b);
//	system("pause");
//	return 0;
//}

int main()
{
	QInt a;
	QInt b;
	QInt c;
	string BigInt1;
	string BigInt2;
	cout << "Nhap vao a so BigInt1 bang binary :";
	cin >> BigInt1;
	a.scanQInt(BigInt1, 2);
	b = ~a;
	cout << "Xuat ket qua b= ~a = : ";
	cout<<b.printQInt(2);
	return 0;
}
#pragma 
#include"Header.h"
//Hàm chuyển QInt thành mảng bit chứa trong mảng bool
bool* QInt::DecToBin()
{
	bool* y = new bool[128];
	for (int i = 0; i < 128; i++)
	{
		y[i] = (bytes[i / 8] >> (7 - i % 8)) & 1;
	}
	return y;
}
//Hàm chuyển mảng bit thành QInt
QInt QInt::BinToDec(bool* bit)
{
	QInt Dec;
	for (int i = 0; i < 128; i++)
	{
		Dec.bytes[i / 8] = (bit[i] << (7 - i % 8)) | Dec.bytes[i / 8];
	}
	return Dec;
}
string QInt::printQInt(int base)
{
	string kq;
	if (base == 2)
		kq = this->bintostring(1);
	if (base == 10)
		kq = this->bintodec(this->bintostring(0));
	if (base == 16)
		kq = this->bintohex(this->bintostring(0));
	return kq;
}
QInt::QInt()
{
	//xet tat ca bit = 0
	for (int i = 0; i < QINT_SIZE; i++)
		bytes[i] = 0;
}

QInt::~QInt()
{
}
QInt QInt::operator =(const QInt X)
{
	for (int i = 0; i < 16; i++)
	{
		bytes[i] = X.bytes[i];
	}
	return *this;
}
//Cong 2 so QInt
QInt operator+(const QInt& A, const QInt &B)
{
	int du = 0;
	QInt C;
	for (int i = 15; i >= 0; i--)
	{
		int temp = 0;
		bitset<8> num1(A.bytes[i]);
		bitset<8> num2(B.bytes[i]);
		bitset<8> num3;
		for (int j = 0; j < 8; j++)
		{
			temp = num1[j] + num2[j] + du;
			du = temp / 2;
			num3[j] = temp - 2 * du;
		}
		C.bytes[i]= (unsigned char)num3.to_ulong();
	}
	return C;
}

QInt operator-(const QInt& A, const QInt& B)
{
	QInt C = ~B;
	int temp = 1;
	QInt D;
	D.bytes[15] = unsigned char(1);
	C = C + D;
	C = A + C;
	return C;
}
QInt operator*(const QInt& M, const QInt& Q)
{
	QInt A;
	bitset<1> Q1;
	bitset<1> Q0;
	QInt Qt = Q;
	int k = 128;
		while (k > 0)
		{
			bool temp = (Qt.bytes[15] >> 0) & 1;
			if (Q1.none() == true && temp == 1)
			{
				A = A - M;
			}
			else if (Q1.none() == false && temp == 0)
			{
				A = A + M;
			}
			Q1 = (Qt.bytes[15] >> 0) & 1;
			Qt = Qt >> 1;
			Q0 = (bool)((A.bytes[15] >> 0) & 1);
			if (Q0.none() == true)
			{
				Qt.bytes[0]=(~(1 << 7)& Qt.bytes[0]);
			}
			else
			{
				Qt.bytes[0]=(1 << 7) | Qt.bytes[0];
			}
			A = A >> 1;
			if ((bool)((A.bytes[0] >> 6) & 1) == 1)
			{
				A.bytes[0] = (1 << 7) | A.bytes[0];
			}
			else
			{
				A.bytes[0] = (~(1 << 7) & A.bytes[0]);
			}
			k--;
		}
		return Qt;

}

QInt operator/(const QInt& Q, const QInt& M)
{
	QInt Q1, M1;
	Q1 = Q;
	M1 = M;
	QInt num_zero;
	int k = 128;
	QInt A;
	int sign = 0;
	bool x = (Q1.bytes[0] >> 7) & 1;
	if ((bool)((Q1.bytes[0]>>7)&1)==1&&(bool)((M1.bytes[0]>>7)&1)==1)
	{
		Q1 = num_zero - Q1;
		M1 = num_zero - M1;
	}
	if (((bool)(Q1.bytes[0]>>7)&1)==0&& (bool)((M1.bytes[0]>>7)&1)==1)
	{
		M1 = num_zero - M1;
		sign = 1;
	}
	if (((bool)(Q1.bytes[0] >> 7) & 1) == 1 && (bool)((M1.bytes[0] >> 7) & 1) == 0)
	{
		Q1 = num_zero - Q1;
		sign = 1;
	}
	while (k > 0)
	{
		//Shift left [A, Q]
		bool* bitA = A.DecToBin();
		bool* bitQ = Q1.DecToBin();
		for (int i = 0; i < 127; i++)
		{
			bitA[i] = bitA[i + 1];
		}
		bitA[127] = bitQ[0];
		for (int i = 0; i < 127; i++)
		{
			bitQ[i] = bitQ[i + 1];
		}
		bitQ[127] = 0;

		Q1 = Q1.BinToDec(bitQ);
		A = A.BinToDec(bitA);
		A = A - M1;
		if ((A.bytes[0]>>7)&1==1)
		{
			bool* bitQ = Q1.DecToBin();
			bitQ[127] = 0;
			Q1 = Q1.BinToDec(bitQ);
			A = A + M1;
		}
		else
		{
			bool* bitQ = Q1.DecToBin();
			bitQ[127] = 1;
			Q1 = Q1.BinToDec(bitQ);
		}
		k = k - 1;
	}
	if (sign == 0)
	{
		return Q1;
	}
	if (sign == 1)
	{
		return num_zero - Q1;
	}
}
QInt QInt::operator&(const QInt & B) const
{
	QInt des;
	for (int i = 0; i < QINT_SIZE; i++)
	{
		des.bytes[i] = this->bytes[i] & B.bytes[i];
	}
	return des;
}

QInt QInt::operator|(const QInt & B) const
{
	QInt des;
	for (int i = 0; i < QINT_SIZE; i++)
	{
		des.bytes[i] = this->bytes[i] | B.bytes[i];
	}
	return des;
}

QInt QInt::operator^(const QInt & B) const
{
	QInt des;
	for (int i = 0; i < QINT_SIZE; i++)
	{
		des.bytes[i] = this->bytes[i] ^ B.bytes[i];
	}
	return des;
}

//Overload toan tu dao bit
QInt QInt::operator~() const
{
	QInt des;
	for (int i = 0; i < QINT_SIZE; i++)
	{
		des.bytes[i] = ~this->bytes[i];
	}
	return des;
}
QInt QInt::operator>>(int nums) const
{
	QInt des = *this;
	while (nums > 0)
	{
		for (int i = QINT_SIZE - 1; i >= 1; i--)
		{
			des.bytes[i] = des.bytes[i] >> 1;
			if (des.bytes[i - 1] & 1)
			{
				des.bytes[i] = ((1 << 7) | des.bytes[i]);
			}
		}
		if ((bool)((des.bytes[0] >> 7) & 1) == 1)
		{

			des.bytes[0] = des.bytes[0] >> 1;
			des.bytes[0] = ((1 << 7) | des.bytes[0]);
		}
		else
			des.bytes[0] = des.bytes[0] >> 1;
		nums--;
	}
	return des;
}

QInt QInt::operator<<(int nums) const
{
	QInt des = *this;
	while (nums > 0)
	{
		for (int i = 0; i < QINT_SIZE - 1; i++)
		{
			des.bytes[i] = des.bytes[i] << 1;
			if ((des.bytes[i + 1] >> 7) & 1)
			{
				des.bytes[i] = (1 | des.bytes[i]);
			}
		}
		des.bytes[QINT_SIZE - 1] = des.bytes[QINT_SIZE - 1] << 1;
		nums--;
	}
	return des;
}

QInt QInt::rol() const
{
	QInt des = *this;

	bool check = ((des.bytes[0] >> 7) & 1);
	for (int i = 0; i < QINT_SIZE - 1; i++)
	{
		des.bytes[i] = des.bytes[i] << 1;
		if ((des.bytes[i + 1] >> 7) & 1)
		{
			des.bytes[i] = (1 | des.bytes[i]);
		}
	}
	des.bytes[QINT_SIZE - 1] = des.bytes[QINT_SIZE - 1] << 1;
	if (check)
		des.bytes[QINT_SIZE - 1] = (1 | des.bytes[QINT_SIZE - 1]);

	return des;
}

QInt QInt::ror() const
{
	QInt des = *this;

	bool check = (des.bytes[QINT_SIZE - 1] & 1);
	for (int i = QINT_SIZE - 1; i >= 1; i--)
	{
		des.bytes[i] = des.bytes[i] >> 1;
		if (des.bytes[i - 1] & 1)
		{
			des.bytes[i] = ((1 << 7) | des.bytes[i]);
		}
	}
	des.bytes[0] = des.bytes[0] >> 1;
	if (check)
		des.bytes[0] = ((1 << 7) | des.bytes[0]);

	return des;
}

string divbytwo(string str) //chia 1 string dạng dec cho 2 vd "100" chia 2 thành "50"
{
	string temp = "";
	int len = str.length();

	int add = 0;

	for (int i = 0; i < len; i++)
	{
		int digit = str[i] - '0';  //xét ký ký tự tại i tức là số vd "2" -> 2 // khi 2 chia 2 sẽ thành 1
		temp += ((digit + add) / 2 + '0'); // ký tự sau khi chia 2, add là phần phụ vì sô chia 2 có thể chẵn lẻ, khi đó sẽ dư ra 1, 
		add = (digit % 2) ? 10 : 0;  // ví dụ trên 32 chia 2, 3 lẻ chia 2 sẽ dư 1 cho số tiếp theo, khi đó 12 /2 = 6 
	}

	if (temp[0] == '0' && temp.length() > 1) //nếu vị trí đầu bằng 0 thì loại bỏ
		temp.erase(0, 1);
	return temp;

}
void QInt::bintobin(string str) //chuyển 1 chuỗi string nhị phân lưu vào qint
{

	int k = str.length() - 1;

	for (int m = QINT_SIZE - 1; m >= 0; m--)
	{
		for (int n = 0; n < 8; n++)
		{
			if (k >= 0)
			{
				if (str[k--] == '0')
					this->bytes[m] = ~(1 << n) & this->bytes[m];
				else
					this->bytes[m] = (1 << n) | this->bytes[m];
			}

		}
	}
}

 void QInt::dectobin(string str)  //chuyển chuỗi dec thành nhị phân lưu vào qỉnt
{

	bool isNegative = false;  //xét số âm hay dương tức chuỗi sẽ bắt đầu bằng '-' (dấu trừ)
	if (str[0] == '-')
	{
		isNegative = true;
		str.erase(0, 1);
	}
	 //chuôi dec chia 2 dư 1 sẽ cộng chuỗi '1' và dư 0 + chuỗi '0'
	string binStr = "";
	do
	{
		int len = str.length();
		int lastDigit = str[len - 1] - '0'; //chuyern thành số
		binStr += ((lastDigit % 2 == 0) ? '0' : '1'); //nếu là chẵn hay lẻ
		str = divbytwo(str);  // chia 2
	} while (str != "0");

	reverse(binStr.begin(), binStr.end());  //vì nhận 0 1 theo thứ tự xuôi nên phải đảo ngược chuỗi
	


	this->bintobin(binStr);  //sau khi dc chuỗi nhị phân thì chuyển vào qint

	if (isNegative) //nếu số âm thì chuyển thành bù 2
	{
		//~
		for (int i = 0; i < QINT_SIZE; i++)
		{
			this->bytes[i] = ~this->bytes[i];
		}

		//Cong 1
		for (int i = QINT_SIZE - 1; i >= 0; i--)
		{
			if (this->bytes[i] < 255)
			{
				this->bytes[i] += 1;
				break;
			}
			else
				this->bytes[i] = 0;
		}
	}
	//return temp;

}

string QInt::bintodec(string str)  //tương tự trên chuyển chuỗi bin thành dec
{
	//xet bit dau
	bool sign = false;
	if (str[0] - '0')
		sign = true;
	//thực hiện chức năng đảo bít nếu số âm, chuyển bù 2
	if (sign)
	{
		for (int i = 0; i < QINT_SIZE * 8; i++)
		{
			if (str[i] - '0')
				str[i] = '0';
			else
				str[i] = '1';
		}

		bool add = true;
		for (int i = QINT_SIZE * 8 - 1; i >= 0; i--)
		{
			if (!(str[i] - '0') && !add)
			{
				str[i] = '0';
				add = false;
			}
			if (!(str[i] - '0') && add)
			{
				str[i] = '1';
				add = false;
			}
			if (str[i] - '0' && add)
			{
				str[i] = '0';
				add = true;
			}
		}


	}

	//nhân 2 liên tục cộng với từng bit
	//ví dụ ..
	


	string temp = "0";
	
	for (int i = 0; i < str.length(); i++)
	{
		int add = 0;  
		if (str[i] - '0')  // xét bít 0 hay 1 để cộng vào
			add = 1;
		

		for (int j = 0; j < temp.length(); j++)
		{
			int check = (temp[j] - '0') * 2 + add;  //kiểm tra xem có lớn hơn 10 , ko thì nhân 2, lớn thì phần dư 10 lấy và add= 1
			if (check < 10)
			{
				temp[j] = check + '0';
				add = 0;
			}
			else
			{
				temp[j] = (check % 10) + '0';
				add = 1;
			}
		}
		if (add)
			temp += "1";

	}

	reverse(temp.begin(), temp.end());
	if (sign)
		temp = '-' + temp;
	return temp;
	
}
void QInt::hextobin(string str)
{
	string temp = "";
	int len = str.length();

	for (int i = 0; i < len; i++)
		temp += ReverseHexIndex(str[i]);

	this->bintobin(temp);
}


string QInt::bintostring(bool a)
{
	string res = "";
	//xem phần bitset
	for (int i = 0; i < QINT_SIZE; i++)
	{
		res += bitset<8>(this->bytes[i]).to_string();
	}



	if (a)
	{
		int pos = 0;
		for (pos; pos < res.length(); pos++) // 0000000f0f -> f0f, xoa bo vi tri 0
			if (res[pos] != '0')
				break;

		res = res.substr(pos);
	}

	return res;
}

string ReverseHexIndex(char i)
{
	switch (i)
	{
	case '0':
		return "0000";
		break;
	case '1':
		return "0001";
		break;
	case '2':
		return "0010";
		break;
	case '3':
		return "0011";
		break;
	case '4':
		return "0100";
		break;
	case '5':
		return "0101";
		break;
	case '6':
		return "0110";
		break;
	case '7':
		return "0111";
		break;
	case '8':
		return "1000";
		break;
	case '9':
		return "1001";
		break;
	case 'A':
		return "1010";
		break;
	case 'B':
		return "1011";
		break;
	case 'C':
		return "1100";
		break;
	case 'D':
		return "1101";
		break;
	case 'E':
		return "1110";
		break;
	case 'F':
		return "1111";
		break;
	default:
		return NULL;
		break;
	}
}

char HexIndex(int index)
{
	switch (index)
	{
	case 0:
		return '0';
		break;
	case 1:
		return '1';
		break;
	case 2:
		return '2';
		break;
	case 3:
		return '3';
		break;
	case 4:
		return '4';
		break;
	case 5:
		return '5';
		break;
	case 6:
		return '6';
		break;
	case 7:
		return '7';
		break;
	case 8:
		return '8';
		break;
	case 9:
		return '9';
		break;
	case 10:
		return 'A';
		break;
	case 11:
		return 'B';
		break;
	case 12:
		return 'C';
		break;
	case 13:
		return 'D';
		break;
	case 14:
		return 'E';
		break;
	case 15:
		return 'F';
		break;
	default:
		return NULL;
		break;
	}
}



string QInt::bintohex(string str)
{
	this->bintobin(str);  //chuyen string va Qint
	string fullbit = this->bintostring(0);  // chuyen qint ra lai string
	string temp = "0";

	for (int i = 0; i < QINT_SIZE * 8; i = i + 4)
	{
		bitset<4> bset(fullbit.substr(i, 4)); //cach nhau 4 bit trong hex
		temp += HexIndex((int)bset.to_ulong()); // to_ulong la chuyen day bit thanh so thap phan

	}

	int pos = 0;
	for (pos; pos < temp.length(); pos++) // 0000000f0f -> f0f, xoa bo vi tri 0
		if (temp[pos] != '0')
			break;

	return temp.substr(pos);
}


void QInt::scanQInt(string str, int base)
{
	if (base == 2)
		this->bintobin(str);
	if (base == 10)
		this->dectobin(str);
	if (base == 16)
		this->hextobin(str);

}

void QInt::printQInt(int base, ostream& outputDev)
{

	if (base == 2)
		outputDev << this->bintostring(1) << endl;
	if (base == 10)
		outputDev << this->bintodec(this->bintostring(0)) << endl;
	if (base == 16)
		outputDev << this->bintohex(this->bintostring(0)) << endl;

}

void Readfile(string a, string b)
{
	string line;
	ifstream infile(a);
	ofstream outfile(b, ios::app);
	while (getline(infile, line))
	{
		Process_operator(line, outfile);
	}
	infile.close();
	outfile.close();
}

void Process_operator(string line, ostream& outputDev)
{
	QInt A, B;
	string tt; // tt toan tu

	string str1, str2; //du lieu cho vao
	int base = 0, base1, nums;  //co so

	stringstream str(line);
	while (str >> tt)
	{
		if (tt == "+")
		{
			stringstream temp(line);
			string operand1, operand2, _operator;
			temp >> base >> operand1 >> _operator >> operand2;
			A.scanQInt(operand1, base);  // chuyen co so 
			B.scanQInt(operand2, base);

			A = A + B;
			break;
		}
		if (tt == "-")
		{

			stringstream temp(line);
			string operand1, operand2, _operator;
			temp >> base >> operand1 >> _operator >> operand2;
			A.scanQInt(operand1, base);  // chuyen co so 
			B.scanQInt(operand2, base);

			A = A - B;
			break;
		}
		if (tt == "*")
		{
			string operand1, _operator, operand2;
			stringstream temp(line);
			temp >> base >> operand1 >> _operator >> operand2;
			A.scanQInt(operand1, base);  // chuyen co so 
			B.scanQInt(operand2, base);
			A = A * B;
			break;
		}
		if (tt == "/")
		{
			string operand1, _operator, operand2;
			stringstream temp(line);
			temp >> base >> operand1 >> _operator >> operand2;
			A.scanQInt(operand1, base);  // chuyen co so 
			B.scanQInt(operand2, base);

			A = A / B;
			break;
		}
		if (tt == "&")
		{
			stringstream temp(line);
			temp >> base >> str1 >> str2 >> str2;
			A.scanQInt(str1, base);  // chuyen co so 
			B.scanQInt(str2, base);

			A = A & B;
			break;
		}
		if (tt == "|")
		{
			stringstream temp(line);
			temp >> base >> str1 >> str2 >> str2;
			A.scanQInt(str1, base);  // chuyen co so 
			B.scanQInt(str2, base);

			A = A | B;
			break;
		}
		if (tt == "^")
		{
			stringstream temp(line);
			temp >> base >> str1 >> str2 >> str2;
			A.scanQInt(str1, base);  // chuyen co so 
			B.scanQInt(str2, base);

			A = A ^ B;
			break;
		}
		if (tt == "~")
		{
			stringstream temp(line);
			temp >> base >> str1 >> str1;
			A.scanQInt(str1, base);  // chuyen co so 

			A = ~A;
			break;
		}
		if (tt == ">>")
		{
			stringstream temp(line);
			temp >> base >> str1 >> str2 >> nums;
			A.scanQInt(str1, base);  // chuyen co so 

			A = A >> nums;
			break;
		}
		if (tt == "<<")
		{
			stringstream temp(line);
			temp >> base >> str1 >> str2 >> nums;
			A.scanQInt(str1, base);  // chuyen co so 

			A = A << nums;
			break;
		}
		if (tt == "ror")
		{
			stringstream temp(line);
			temp >> base >> str1 >> str1;
			A.scanQInt(str1, base);  // chuyen co so 

			A = A.ror();
			break;
		}
		if (tt == "rol")
		{
			stringstream temp(line);
			temp >> base >> str1 >> str1;
			A.scanQInt(str1, base);  // chuyen co so 

			A = A.rol();
			break;
		}
	}

	if (!base) // neu base = 0 la chuyen doi co so
	{
		stringstream temp(line);
		temp >> base >> base1 >> str1; // co so 1 va co so 2
		A.scanQInt(str1, base);
		base = base1;
	}

	A.printQInt(base, outputDev);
}



#include <string>
#include <iostream>
#include <vector>
#include "Vigenere.h"
#include "DES.h"
#include "RSA.h"
#include "MD5.h"
using namespace std;
int main()
{
	string plaintext = "hello nsfjnoiwjwljelk";
	string ciphertext = "";
	string keyword = "123456";
	MD5 m;  
	cout<<m.Encrypt("abc");
	//cout << "�����ǣ�" << endl;
	//cout << d.ciphertext << endl;
	//d.Decrypt(d.ciphertext);
	//cout << "�����ǣ�" << endl;
	//cout << d.plaintext << endl;
	system("pause");
	return 0;
}




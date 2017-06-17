#include <string>
#include <iostream>
#include <vector>
#include <fstream> 
#include "Vigenere.h"
#include "DES.h"
#include "RSA.h"
#include "MD5.h"
#include "DSS.h"
using namespace std;
void printHead();
void dss();
void vigenere();
void md5();
void rsa();
void des();
string getText(string filename);
void writeCiphertext(string ciphertext, string fileName);
int main()
{
	string plaintext = "hello nsfjnoiwjwljelk";
	printHead();
	int a;
	while (cin>>a)
	{
		switch (a)
		{
		case 1:vigenere(); break;
		case 2:des(); break;
		case 3:rsa(); break;
		case 4:md5(); break;
		case 5:dss(); break;
		default: 
			break;
		}
		if (a==6)
		{
			cout << "ллʹ��" << endl;
			break;
		}
		system("pause");
		system("cls");
		printHead();
	}
	system("pause");
	return 0;
}

void printHead() {
	cout << "---------------------------------------" << endl;
	cout << "-            1.Vigenere�����㷨       -" << endl;
	cout << "-            2.DES�����㷨            -" << endl;
	cout << "-            3.RSA�����㷨            -" << endl;
	cout << "-            4.MD5�����㷨            -" << endl;
	cout << "-            5.DSSǩ���㷨            -" << endl;
	cout << "-            6.�˳�                   -" << endl;
	cout << "---------------------------------------" << endl;
	cout << "��������Ϊ��Hello are you OK i am lei jun\n" << endl;
	cout << "ѡ��";
}

void dss() {
	cout << "\n***  DSS�����㷨  ***" << endl;
	cout << "���������Կ˽Կ��:" << endl;
	DSS d(1,"1");
	d.generateKey();
	d.signature(getText("plaintext.txt"));
	cout << "��Կǩ����ǩ��Ϊ(r,s)��" << "(" << d.r << "," << d.s << ")" << endl;
	writeCiphertext(d.sig, "ciphertext.dss");
	cout << "ǩ����֤��" << endl;
	d.verify(getText("plaintext.txt"));
	cout << "ǩ����д�� ciphertext.dss �ļ�" << endl;
}

void vigenere() {
	string keyword;
	cout << "\n***  Vigenere�����㷨  ***" << endl;
	cout << "������Կ(һ��Ӣ�ĵ���):" << endl;
	cin >> keyword;
	Vigenere v(keyword);
	v.Encrypt(getText("plaintext.txt"));
	cout << "���ܺ�����Ϊ��" << v.ciphertext << endl;
	writeCiphertext(v.ciphertext, "ciphertext.vig");
	v.Decrypt(getText("ciphertext.vig"));
	cout << "���ܺ�����Ϊ��" << v.plaintext << endl;
	cout << "������д�� ciphertext.vig �ļ�" << endl;
}

void md5() {
	string keyword;
	cout << "\n***  MD5�����㷨  ***" << endl;
	MD5 m;
	m.Encrypt(getText("plaintext.txt"));
	cout << "���ܺ�����Ϊ��" << m.ciphertext << endl;
	writeCiphertext(m.ciphertext, "ciphertext.md5");
	cout << "������д�� ciphertext.md5 �ļ�" << endl;
}

void rsa() {
	string keyword;
	cout << "\n***  RSA�����㷨  ***" << endl;
	cout << "���������Կ˽Կ��:" << endl;
	RSA r(1,1);
	r.generateKey();
	r.Encrypt(getText("plaintext.txt"));
	cout << "��Կ���ܺ�����Ϊ��" << r.ciphertext << endl;
	writeCiphertext(r.ciphertext, "ciphertext.rsa");
	r.Decrypt(getText("ciphertext.rsa"));
	cout << "˽Կ���ܺ�����Ϊ��" << r.plaintext << endl;
	cout << "������д�� ciphertext.rsa �ļ�" << endl;
	
}

void des() {
	string keyword;
	cout << "\n***  DES�����㷨  ***" << endl;
	cout << "������Կ:" << endl;
	cin >> keyword;
	DES d(keyword);
	d.Encrypt(getText("plaintext.txt"));
	cout << "���ܺ�����Ϊ��" << d.ciphertext << endl;
	writeCiphertext(d.ciphertext, "ciphertext.des");
	d.Decrypt(getText("ciphertext.des"));
	cout << "���ܺ�����Ϊ��" << d.plaintext << endl;
	cout << "������д�� ciphertext.des �ļ�" << endl;
}

//�����ı�
string getText(string filename) {
	ifstream infile(filename);
	string plaintext;
	getline(infile, plaintext);
	infile.close();
	return plaintext;
}

//������д���ı�
void writeCiphertext(string ciphertext, string fileName) {
	ofstream outfile(fileName, ofstream::out);
	outfile << ciphertext;
	outfile.close();
}






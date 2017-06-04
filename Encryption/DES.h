#ifndef DES_H
#define DES_H
#include <string>
#include <iostream>
#include <iterator>
#include <algorithm>
#include "DEStable.h"
using namespace std;
class DES {
public:
	string plaintext = "";
	string ciphertext = "";
	DES(string keyword) {
		if (keyword.size() < 8)
		{
			keyword += "       ";
		}
		creatSubKey(keyword);
	}

	string Encrypt(string plaintext) {
		ciphertext = "";
		char plainchar[12];
		char cipherchar[12] = "";
		for (unsigned int i = 0; i < plaintext.size(); i += 8) {
			strcpy(plainchar, plaintext.substr(i, 8).c_str());
			memset(cipherchar, 0, sizeof(plainchar));
			Run(cipherchar, plainchar, true);		//��Ϊ�ǶԳƼ���
			ciphertext += cipherchar;
		}
		return ciphertext;
	}

	string Decrypt(string ciphertext) {
		plaintext = "";
		char plainchar[12];
		char cipherchar[12];
		for (unsigned int i = 0; i < ciphertext.size(); i += 8) {
			strcpy(cipherchar, ciphertext.substr(i, 8).c_str());
			memset(plainchar, 0, sizeof(cipherchar));
			Run(plainchar, cipherchar, false);		//��Ϊ�ǶԳƼ���
			plaintext += plainchar;
		}
		return plaintext;
	}

	//�����������
	void creatSubKey(string keyword) {
		char Key[8];
		for (int i = 0; i < 8; i++)
		{
			Key[i] = keyword[i];
		}
		static bool K[64], *KL = &K[0], *KR = &K[28];

		charToByte(K, Key, 64);					//��charת��������������

		Transform(K, K, PC_1Table, 56);			//��64λ��Ϊ56λ

		for (int i = 0; i < 16; i++)
		{
			shiftLeft(KL, 28, shiftTable[i]);
			shiftLeft(KR, 28, shiftTable[i]);
			Transform(SubKey[i], K, PC_2Table, 48);
		}
	}


private:
	bool SubKey[16][48];

	void Run(char Out[8], char In[8], bool Type) {
		static bool M[64], temp[32], *Li = &M[0], *Ri = &M[32];

		charToByte(M, In, 64);					//��charת��������������;

		Transform(M, M, initIPTable, 64);		//��ʼ�仯��IP��

		if (Type)
		{
			for (int i = 0; i < 16; i++)
			{
				memcpy(temp, Ri, 32);		//���Ҳ�R(i-1)��ֵ��temp

				// R[i] = L[i-1] xor f(R[i-1], K[i])
				F_function(Ri, SubKey[i]);
				Xor(Ri, Li, 32);

				// L[i] = R[i-1]
				memcpy(Li, temp, 32);
			}
		}
		else
		{
			for (int i = 15; i >= 0; i--)
			{
				memcpy(temp, Li, 32);		//���Ҳ�R(i-1)��ֵ��temp
											// R[i] = L[i-1] xor f(R[i-1], K[i])
				F_function(Li, SubKey[i]);
				Xor(Li, Ri, 32);

				// L[i] = R[i-1]
				memcpy(Ri, temp, 32);
			}
		}
		Transform(M, M, inverseIPTable, 64);
		byteToChar(Out, M, 64);
	}

	void F_function(bool In[32], bool Ki[48]) {
		static bool T[48];

		//����Ri-1(32����)�����任E������Ϊ48����
		Transform(T, In, extendTable, 48);

		//���
		Xor(T, Ki, 48);

		//���ͺ�ı��ش���Ϊ8�飬ÿ��6���ء����龭�����Ե�S�к��ֱ�Ϊ4����(������̼���)���ϲ����ֳ�Ϊ32���ء�
		S_function(In, T);

		//��32���ؾ���P�任������ı��ش�����32���ص�f (Ri-1,Ki)��
		Transform(In, In, PTable, 32);
	}

	void S_function(bool Out[32], bool In[48]) {
		char j, m, n, num;

		//���ͺ�ı��ش���Ϊ8�飬ÿ��6���ء�
		for (j = 0; j < 8; j++, In += 6, Out += 4)
		{
			//��������In[0],In[1],In[2],In[3],In[4],In[5]�У������m=In[0]*2+In[5], 
			//n=In[4]+In[3]*2+In[2]*4+In[1]*8���ٴ�Sj���в��m�У�n�е�ֵSmn����Smn��Ϊ�����ƣ�����Si�е������
			m = (In[0] << 1) + In[5];
			n = (In[1] << 3) + (In[2] << 2) + (In[3] << 1) + In[4];
			//TODO:���ܻᱨ�� ������
			num = SBox[(int)j][(int)m][(int)n];
			charToByte(Out, &num, 4);
		}
	}

	void Xor(bool *Out, const bool *In, int len)
	{
		int i;

		for (i = 0; i < len; i++)
		{
			Out[i] ^= In[i];
		}
	}

	//����  lbyte:�ƶ���λ��
	void shiftLeft(bool *In, int len, int lbyte) {
		static bool temp[256];					// Sample:  lbyte=2
		memcpy(temp, In, lbyte);				// In=12345678 tmp=12
		memcpy(In, In + lbyte, len - lbyte);	// In=345678	
		memcpy(In + len - lbyte, temp, lbyte);	// In=34567812
	}

	//��λ  Table����λ��   len:��λ���
	void Transform(bool *Out, bool *In, const int *Table, int len)
	{
		int i;
		static bool tmp[256];

		for (i = 0; i < len; i++)
		{
			tmp[i] = In[Table[i] - 1];
		}
		memcpy(Out, tmp, len);
	}

	//charת����bool����
	void charToByte(bool *Out, const char *In, int bits) {
		for (int i = 0; i < bits; i++)
		{
			// In[i]�ĵ�Nλ����Nλ����0x01��λ"��"����(N=1~8)
			Out[i] = (In[i / 8] >> (i % 8)) & 1;
		}
	}

	//��bool����char����
	void byteToChar(char *Out, const bool *In, int bits) {
		memset(Out, 0, (bits + 7) / 8);
		for (int i = 0; i < bits; i++)
		{
			Out[i / 8] |= In[i] << (i % 8);
		}
	}

};
#endif

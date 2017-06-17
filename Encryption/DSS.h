#ifndef DSS_H
#define DSS_H
#include <string>
#include <iostream>
#include <cmath>
using namespace std;
class DSS
{
public:
	unsigned __int64 x;		//˽Կ
	unsigned __int64 y;		//��Կ
	unsigned __int64 r;		//����ǩ��(r,s)
	unsigned __int64 s;

	DSS() {
	}

	DSS(unsigned __int64 xy, unsigned __int64 rr, unsigned __int64 ss) {
		x = y = xy;
		r = rr;
		s = ss;
	}

	void signature(string message) {
		srand(time(0));
		hash<std::string> h;
		unsigned __int64 k = rand() % q;	//kΪ�����  0<k<q
		//unsigned __int64 HM = 1234;
		r = PowMod(g, k, p) % q;
		s = mod_reverse(k, q)*((h(message) + x*r) % q) % q;
	}

	void verify(string message) {
		hash<std::string> h;
		//unsigned __int64 HM = 1234;
		unsigned __int64 w = mod_reverse(s,q);
		unsigned __int64 u1 = h(message) * w % q;
		unsigned __int64 u2 = r * w % q;
		unsigned __int64 v = (PowMod(g, u1, p)*PowMod(y, u2, p) % p) % q;	//����a*b % n = (a % n)*(b % n) % n
		if (v == r) {
			cout << "ture" << endl;
		}
	}

	//����˽Կx�͹�Կy
	void generateKey() {
		//0 < x < q;
		srand(time(0));
		x = rand() % q;
		y = PowMod(g, x, p);	//xΪ75ʱyΪ4567
		cout << "˽Կ:" << x << endl;
		cout << "��Կ:" << y << endl;
	}

private:
	unsigned __int64 q = 101;
	unsigned __int64 p = q * 78 + 1;					// p = 7879	
	unsigned __int64 pMinus1Divideq = 78;				// (p - 1) / q
	unsigned __int64 h = 3;
	unsigned __int64 g = PowMod(h, pMinus1Divideq, p);	// g = 170

	//ģ�����㣬����ֵ x=a*b mod n
	inline unsigned __int64 MulMod(unsigned __int64 a, unsigned __int64 b, unsigned __int64 n)
	{
		return a * b % n;
	}

	//ģ�����㣬����ֵ x=base^pow mod n
	unsigned __int64 PowMod(unsigned __int64 &base, unsigned __int64 &pow, unsigned __int64 &n)
	{
		unsigned __int64    a = base, b = pow, c = 1;
		while (b)
		{
			while (!(b & 1))
			{
				b >>= 1;            //a=a * a % n;    //�������������Դ���64λ������������������a*a��a>=2^32ʱ�Ѿ��������������ʵ�ʴ���Χû��64λ
				a = MulMod(a, a, n);
			}        b--;        //c=a * c % n;        //����Ҳ�����������64λ������Ϊ����32λ������֪�Ƿ���Խ��������⡣
			c = MulMod(a, c, n);
		}    return c;
	}
	//����d=gcd(a,b);�Ͷ�Ӧ�ڵ�ʽax+by=d�е�x,y
	long long extend_gcd(long long a, long long b, long long &x, long long &y) {
		if (a == 0 && b == 0) return -1;//�����Լ��
		if (b == 0) {
			x = 1; y = 0; return a;
		}
		long long d = extend_gcd(b, a%b, y, x);
		y -= a / b*x;
		return d;
	}

	//ax = 1(mod n) ��X   ��: �� 1 / a % n
	long long mod_reverse(long long a, long long n) {
		long long x, y;
		long long d = extend_gcd(a, n, x, y);
		if (d == 1)
			return (x%n + n) % n;
		else return -1;
	}
};
#endif

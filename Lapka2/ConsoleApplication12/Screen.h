//#pragma once
////=== ���� screen.h - ��������� ������ � �������
//const int xmax = 100; //������ ������
//const int ymax = 50;
//class point {	//����� �� ������
//public:
//	int x, y;
//	point(int a = 0, int b = 0) : x(a), y(b) {  }
//};
//// ����� ������ ��� ������ � �������
//void put_point(int a, int b); // ����� ����� (2 ��������)
//void put_point(point p) { put_point(p.x, p.y); } //
//void put_line(int, int, int, int); // ����� ����� (2 ��������)
//void put_line(point a, point b)
//{
//	put_line(a.x, a.y, b.x, b.y);
//}
//extern void screen_init();	// �������� ������
//extern void screen_destroy();	// �������� ������
//extern void screen_refresh();	// ����������
//extern void screen_clear();	// �������
#pragma once
#include "exceptions.h";

const int XMAX = 100; //Ðàçìåð ýêðàíà
const int YMAX = 50;

class point { //Òî÷êà íà ýêðàíå
public:
	int x, y;
	point(int a = 0, int b = 0) : x(a), y(b) { }
	static point zero() { return point(0, 0); }
};

// Íàáîð óòèëèò äëÿ ðàáîòû ñ ýêðàíîì
void put_point(int a, int b); // Âûâîä òî÷êè (2 âàðèàíòà)

void put_point(point p)
{
	put_point(p.x, p.y);
} //

void put_line(int, int, int, int); // Âûâîä ëèíèè (2 âàðèàíòà)

void put_line(point a, point b)
{
	put_line(a.x, a.y, b.x, b.y);
}

extern void screen_init(); // Ñîçäàíèå ýêðàíà

extern void screen_destroy(); // Óäàëåíèå ýêðàíà

extern void screen_refresh(); // Îáíîâëåíèå

extern void screen_clear(); // Î÷èñòêà
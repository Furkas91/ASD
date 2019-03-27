#pragma once
//=== ���� screen.h - ��������� ������ � �������
const int XMAX = 100; //������ ������
const int YMAX = 50;
class point {	//����� �� ������
public:
	int x, y;
	point(int a = 0, int b = 0) : x(a), y(b) {  }
};
// ����� ������ ��� ������ � �������
void put_point(int a, int b); // ����� ����� (2 ��������)
void put_point(point p) { put_point(p.x, p.y); } //
void put_line(int, int, int, int); // ����� ����� (2 ��������)
void put_line(point a, point b)
{
	put_line(a.x, a.y, b.x, b.y);
}
extern void screen_init();	// �������� ������
extern void screen_destroy();	// �������� ������
extern void screen_refresh();	// ����������
extern void screen_clear();	// �������

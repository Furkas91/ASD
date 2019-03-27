#pragma once
char screen[YMAX][XMAX];
enum color { black = '*', white = '.' };

using namespace std;

void screen_init()
{
	for (auto y = 0; y < YMAX; ++y)
		for (auto &x : screen[y])
			x = white;
}

void screen_destroy()
{
	for (auto y = 0; y < YMAX; ++y)
		for (auto &x : screen[y])
			x = black;
}

bool on_screen(int a, int b) // проверка попадания на экран
{
	return 0 <= a && a < XMAX && 0 <= b && b < YMAX;
}

//void put_point(int a, int b)
//{
//	if (on_screen(a, b)) screen[b][a] = black;
//}

void put_point(int a, int b)
{
	try
	{
		if ((b > YMAX || b < 0) && (a > XMAX || a < 0)) throw PointOutOfScreenException();
		if (b > YMAX || b < 0) throw YOfPointOutOfScreenException();
		if (a > XMAX || a < 0) throw XOfPointOutOfScreenException();
		screen[b][a] = black;
	}
	catch (XOfPointOutOfScreenException& e)
	{
		cout << e.what() << endl;
	}
	catch (YOfPointOutOfScreenException& e)
	{
		cout << e.what() << endl;
	}
	catch (PointOutOfScreenException& e)
	{
		cout << e.what() << endl;
	}
}

void put_line(int x0, int y0, int x1, int y1)
/*
Рисование отрезка прямой от (x0,y0) до (x1,y1).
Уравнение прямой: b(x-x0) + a(y-y0) = 0.
Минимизируется величина abs(eps),
где eps = 2*(b(x-x0)) + a(y-y0) (алгоритм Брезенхэма для прямой).
*/
{
	int dx = 1;
	int a = x1 - x0;
	if (a < 0) dx = -1, a = -a;
	int dy = 1;
	int b = y1 - y0;
	if (b < 0) dy = -1, b = -b;
	int two_a = 2 * a;
	int two_b = 2 * b;
	int xcrit = -b + two_a;
	int eps = 0;

	for (;;) { //Формирование прямой линии по точкам
		put_point(x0, y0);
		if (x0 == x1 && y0 == y1) break;
		if (eps <= xcrit) x0 += dx, eps += two_b;
		if (eps >= a || a < b) y0 += dy, eps -= two_a;
	}
}

void screen_clear() { screen_init(); } //Очистка экрана

void screen_refresh() // Обновление экрана
{
	for (int y = YMAX - 1; 0 <= y; --y) { // с верхней строки до нижней
		for (auto x : screen[y])    // от левого столбца до правого
			std::cout << x;
		std::cout << '\n';
	}
}

//== 2. Библиотека фигур ==
struct shape { // Виртуальный базовый класс "фигура"
	static shape* list;	// Начало списка фигур (одно на все фигуры!)
	shape* next;
	shape() { next = list; list = this; } //Фигура присоединяется к списку
	virtual point north() const = 0;	//Точки для привязки
	virtual point south() const = 0;
	virtual point east() const = 0;
	virtual point west() const = 0;
	virtual point neast() const = 0;
	virtual point seast() const = 0;
	virtual point nwest() const = 0;
	virtual point swest() const = 0;
	virtual void draw() = 0;	//Рисование
	virtual void move(int, int) = 0;	//Перемещение
	virtual void resize(int) = 0;//Изменение размера
	bool flag = false;
};

shape * shape::list = nullptr;	//Инициализация списка фигур

class rotatable : virtual public shape { //Фигуры, пригодные к повороту 
public:
	virtual void rotate_left() = 0;	//Повернуть влево
	virtual void rotate_right() = 0;	//Повернуть вправо
	//bool flag1 = false;
};
class reflectable : virtual public shape { // Фигуры, пригодные
				// к зеркальному отражению
public:
	virtual void flip_horisontally() = 0;	// Отразить горизонтально
	virtual void flip_vertically() = 0;	// Отразить вертикально
};
class line : public shape {
	/* отрезок прямой ["w", "e" ].
	north( ) определяет точку "выше центра отрезка и так далеко
	на север, как самая его северная точка", и т. п. */
protected:
	point w, e;
public:
	line(point a, point b) : w(a), e(b) { };
	line(point a, int L) : w(point(a.x + L - 1, a.y)), e(a) {  };
	point north() const { return point((w.x + e.x) / 2, e.y < w.y ? w.y : e.y); }
	point south() const { return point((w.x + e.x) / 2, e.y < w.y ? e.y : w.y); }
	point east() const { return point((w.x + e.x) / 2, e.y < w.y ? e.y : w.y); }
	point west() const { return point((w.x + e.x) / 2, e.y < w.y ? e.y : w.y); }
	point neast() const { return point((w.x + e.x) / 2, e.y < w.y ? e.y : w.y); }
	point seast() const { return point((w.x + e.x) / 2, e.y < w.y ? e.y : w.y); }
	point nwest() const { return point((w.x + e.x) / 2, e.y < w.y ? e.y : w.y); }
	point swest() const { return point((w.x + e.x) / 2, e.y < w.y ? e.y : w.y); }
	void move(int a, int b) { w.x += a; w.y += b; e.x += a; e.y += b; }
	void draw() { put_line(w, e); }
	void resize(int d) // Увеличение в (d) раз
	{
		e.x += (e.x - w.x) * (d - 1); e.y += (e.y - w.y) * (d - 1);
	}
};
// Прямоугольник
class rectangle : public rotatable {
	/* nw ------ n ------ ne
	   |		          |
	   |		          |
	   w	     c        e
	   |		          |
	   |		          |
	   sw ------ s ------ se */
protected:
	point sw, ne;
public:
	//NNNNNNNNNNNNNNNAAAAAAAAAAAAAAAAAAAAAAAAA
	rectangle(point a, point b)
	{
		try
		{
			if (a.x > XMAX || a.x < 0 ||
				a.y > YMAX || a.y < 0 ||
				b.x > XMAX || b.x < 0 ||
				b.y > YMAX || b.y < 0) {
				throw ShapeOutOfScreenException();
				flag = true;
			}
			else
				if (sw.x > ne.x || sw.y > ne.y) {
					throw WrongShapeException();
					flag = true;
				}
			sw = a;
			ne = b;
		}
		catch (ShapeOutOfScreenException)
		{
			cout << "Rectangle (" << a.x << ", " << a.y << ") - (" << b.x << ", " << b.y << ") is out of screen!" << endl;
			sw = point::zero();
			ne = point::zero();
		}
		catch (WrongShapeException)
		{
			cout << "Rectangle (" << a.x << ", " << a.y << ") - (" << b.x << ", " << b.y << ") adjusted!" << endl;
			sw.x = a.x < b.x ? a.x : b.x;
			sw.y = a.y < b.y ? a.y : b.y;
			ne.x = a.x > b.x ? a.x : b.x;
			ne.y = a.y > b.y ? a.y : b.y;
		}
	}
	//NNNNNNNNNNNNNNNAAAAAAAAAAAAAAAAAAAAAAAAA

	//rectangle(point a, point b) : sw(a), ne(b) { }
	point north() const { return point((sw.x + ne.x) / 2, ne.y); }
	point south() const { return point((sw.x + ne.x) / 2, sw.y); }
	point east() const { return point(ne.x, (sw.y + ne.y) / 2); }
	point west() const { return point(sw.x, (sw.y + ne.y) / 2); }
	point neast() const { return ne; }
	point seast() const { return point(ne.x, sw.y); }
	point nwest() const { return point(sw.x, ne.y); }
	point swest() const { return sw; }
	void rotate_right() // Поворот вправо относительно se
	{
		int w = ne.x - sw.x, h = ne.y - sw.y;
		sw.x = ne.x - h * 2; ne.y = sw.y + w / 2;
	}
	void rotate_left() // Поворот влево относительно sw
	{
		int w = ne.x - sw.x, h = ne.y - sw.y;
		ne.x = sw.x + h * 2; ne.y = sw.y + w / 2;
	}
	void move(int a, int b)
	{
		sw.x += a; sw.y += b; ne.x += a; ne.y += b;
	}
	void resize(int d)
	{
		ne.x += (ne.x - sw.x) * (d - 1); ne.y += (ne.y - sw.y) * (d - 1);
	}
	void draw();
};
void rectangle::draw()
{
	put_line(nwest(), ne);   put_line(ne, seast());
	put_line(seast(), sw);   put_line(sw, nwest());
}
/*
void shape_refresh() // Перерисовка всех фигур
{
	screen_clear();
	for (shape* p = shape::list; p; p = p->next) p->draw();
	screen_refresh();
}
void up(shape& p, const shape& q) // поместить p над q
{	//Это ОБЫЧНАЯ функция, а не член класса!
	point n = q.north();
	point s = p.south();
	p.move(n.x - s.x, n.y - s.y + 1);
}
*/
// Пример добавки: дополнительный фрагмент - полуокружность
class h_circle : public rectangle, public reflectable {
	bool reflected;
public:
	h_circle(point a, point b, bool r = true) : rectangle(a, b), reflected(r) { }
	void draw();
	void flip_horisontally() { };	// Отразить горизонтально
	void flip_vertically() { reflected = !reflected; };	// Отразить вертикально
};

void h_circle::draw() //Алгоритм Брезенхэма для окружностей
{
	int x0 = (sw.x + ne.x) / 2;
	int y0 = reflected ? sw.y : ne.y;
	int radius = (ne.x - sw.x) / 2;
	int x = 0;
	int y = radius;
	int delta = 2 - 2 * radius;
	int error = 0;
	while (y >= 0) {
		if (reflected) { put_point(x0 + x, y0 + y * 0.7); put_point(x0 - x, y0 + y * 0.7); }
		else { put_point(x0 + x, y0 - y * 0.7); put_point(x0 - x, y0 - y * 0.7); }
		error = 2 * (delta + y) - 1;
		if (delta < 0 && error <= 0) { ++x; delta += 2 * x + 1; continue; }
		error = 2 * (delta - x) - 1;
		if (delta > 0 && error > 0) { --y; delta += 1 - 2 * y; continue; }
		++x; delta += 2 * (x - y);  --y;
	}
}
// Пример добавки: дополнительная функция присоединения…
void down(shape &p, const shape &q)
{
	point n = q.south();
	point s = p.north();
	p.move(n.x - s.x, n.y - s.y + 2);
}
// Cборная фигура - физиономия
class myshape : public rectangle {
	//Моя фигура ЯВЛЯЕТСЯ прямоугольником
	int w, h;
	line l_eye; // левый глаз – моя фигура СОДЕРЖИТ линию
	line r_eye; // правый глаз
	line mouth; // рот
public:
	myshape(point, point);
	void draw();
	void move(int, int);
	void resize(int) { }
};
myshape::myshape(point a, point b)
	: rectangle(a, b),
	w(neast().x - swest().x + 1),
	h(neast().y - swest().y + 1),
	l_eye(point(swest().x + 2, swest().y + h * 3 / 4), 2),
	r_eye(point(swest().x + w - 4, swest().y + h * 3 / 4), 2),
	mouth(point(swest().x + 2, swest().y + h / 4), w - 4) 
{ }

void myshape::draw()
{
	rectangle::draw();
	int a = (swest().x + neast().x) / 2;
	int b = (swest().y + neast().y) / 2;
	put_point(point(a, b));
}
void myshape::move(int a, int b)
{
	rectangle::move(a, b);
	l_eye.move(a, b);
	r_eye.move(a, b);
	mouth.move(a, b);
}

//_____________________________________________________________________________________________________________
//_____________________________________________________________________________________________________________
class trapezioid : public rotatable, public reflectable {
	/* nw ------ n ------ ne
       /                   \
      /                     \
	 e           c           w
	/                         \
   /                           \
  sw ----------- s ----------- se */
protected:
	point sw, se, nw, ne;
public:
	trapezioid(point a, point b, point c, point d) : sw(a), se(b), nw(c), ne(d)
	{
		try
		{
			if (b.x > XMAX || a.x < 0 ||
				c.y > YMAX || a.y < 0 ||
				d.x > XMAX || c.x < 0) {
				flag = true;
				throw ShapeOutOfScreenException();
			}
			else
				if (a.y - c.y != b.y - d.y || a.x > b.x || c.x > d.x || c.y < a.y) {
					flag = true;
					throw WrongShapeException();
				}

			//sw = a;
			//ne = b;
		}
		catch (ShapeOutOfScreenException)
		{
			cout << "Trapezioid (" << a.x << ", " << a.y << ") - (" << b.x << ", " << b.y << ") is out of screen!" << endl;
			//sw = point::zero();
			//ne = point::zero();
		}
		catch (WrongShapeException)
		{
			cout << "Trapezioid (" << a.x << ", " << a.y << ") - (" << b.x << ", " << b.y << ") adjusted!" << endl;
			//sw.x = a.x < b.x ? a.x : b.x;
			//sw.y = a.y < b.y ? a.y : b.y;
			//ne.x = a.x > b.x ? a.x : b.x;
			//ne.y = a.y > b.y ? a.y : b.y;
		}
	}
	//trapezioid(point a, point b, point c, point d) : sw(a), se(b), nw(c), ne(d) { }
	point north() const { return point((nw.x + ne.x) / 2, ne.y); }
	point south() const { return point((sw.x + se.x) / 2, sw.y); }
	point east() const { return point((ne.x + se.x) / 2, (se.y + ne.y) / 2); }
	point west() const { return point((sw.x + nw.x) / 2, (sw.y + nw.y) / 2); }
	point neast() const { return ne; }
	point seast() const { return se; }
	point nwest() const { return nw; }
	point swest() const { return sw; }
	void rotate_right() // Поворот вправо относительно se
	{
		int l1 = nw.x - sw.x;
		int h = nw.y - sw.y;
		int l2 = se.x - ne.x;
		se.y = sw.y - (se.x - sw.x);
		se.x = sw.x;
		nw.x = se.x + h;
		nw.y = sw.y - l1;
		ne.x = nw.x;
		ne.x = nw.x;
		ne.y = se.y + l2;

		//int w = ne.x - sw.x, h = ne.y - sw.y;
		//sw.x = ne.x - h * 2; ne.y = sw.y + w / 2;
	}
	void rotate_left() // Поворот влево относительно sw
	{
		int l1 = nw.x - sw.x;
		int h = nw.y - sw.y;
		int l2 = se.x - ne.x;
		se.y = sw.y + (se.x - sw.x);
		se.x = sw.x;
		nw.x = se.x - h;
		nw.y = sw.y + l1;
		ne.x = nw.x;
		ne.y = se.y - l2;
		//int w = ne.x - sw.x, h = ne.y - sw.y;
		//ne.x = sw.x + h * 2; ne.y = sw.y + w / 2;
	}
	void move(int a, int b)
	{
		sw.x += a; sw.y += b; ne.x += a; ne.y += b;
		nw.x += a; nw.y += b; se.x += a; se.y += b;
	}
	void flip_horisontally() {
		int p1 = nw.y;
		nw.y = se.y;
		ne.y = se.y;
		se.y = p1;
		sw.y = p1;
	}
	void flip_vertically() {
		int p1 = nw.x;
		nw.x = ne.x;
		ne.x = p1;
		p1 = sw.x;
		sw.x = se.x;
		se.x = p1;
	}
	void resize(int blabla){
	}
	void draw();
};
void trapezioid::draw()
{
	put_line(nwest(), ne);   put_line(ne, seast());
	put_line(seast(), sw);   put_line(sw, nwest());
}

//void func() {
//	//screen_clear();
//	//shape *ovno;
//	for (shape* p = shape::list; p; p = p->next)
//		if (!p->next->flag) {
//			//ovno = p->next;
//			p->next = p->next->next;
//			//free(ovno);
//		}
//	//screen_refresh();
//}

void shape_refresh() // Перерисовка всех фигур
{
	screen_clear();
	for (shape* p = shape::list; p; p = p->next) 
		if (!p->flag)
			p->draw();
	
	screen_refresh();
}
void up(shape& p, const shape& q) // поместить p над q
{	//Это ОБЫЧНАЯ функция, а не член класса!
	point n = q.north();
	point s = p.south();
	p.move(n.x - s.x, n.y - s.y + 1);
}

void left(shape& p, const shape& q) // поместить p над q
{	//Это ОБЫЧНАЯ функция, а не член класса!
	point e = q.west();
	point s = p.south();
	p.move(e.x - s.x, e.y - s.y - 4);
}

void right(shape& p, const shape& q) // поместить p над q
{	//Это ОБЫЧНАЯ функция, а не член класса!
	point n = q.east();
	point s = p.south();
	p.move(n.x - s.x, n.y - s.y + 4);
}

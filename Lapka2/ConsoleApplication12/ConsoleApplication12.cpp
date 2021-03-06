#include "pch.h"
//#include "stdfax.h"
#include "iostream"
#include "Screen.h"
#include "Shape.h"


int main() //только для Visual C++ (иначе – main( )) 
{
	setlocale(LC_ALL, "Rus");
	screen_init();
	//== 1.Объявление набора фигур ==

	rectangle hat(point(0, 0), point(14, 5));
	line brim(point(0, 15), 17);
	myshape face(point(15, 10), point(27, 18));
	h_circle beard(point(40, 10), point(50, 20));
	trapezioid uhaL(point(160, 10), point(68, 10), point(62, 14), point(66, 14));
	trapezioid uhaR(point(70, 10), point(78, 10), point(72, 14), point(76, 14));
	trapezioid barsuk(point(57, 26), point(67, 26), point(60, 30), point(65, 30));
	shape_refresh();
	std::cout << "=== Generated... ===\n";
	std::cin.get(); //Смотреть исходный набор
	
//== 2.Ориентация ==
	hat.rotate_right();
	brim.resize(2);
	face.resize(2);
	beard.flip_vertically();
	uhaL.rotate_left();
	uhaR.rotate_right();
	barsuk.flip_horisontally();
	shape_refresh();
	//

	std::cout << "=== Prepared... ===\n";
	std::cin.get(); //Смотреть ориентацию

//== 3.Сборка изображения ==
	//face.move(0, -10); // В исходное положение
	up(brim, face);
	up(hat, brim);
	down(beard, face);
	left(uhaL, face);
	right(uhaR, face);
	down(barsuk, beard);
	shape_refresh();
	std::cout << "=== Ready! ===\n";
	std::cin.get(); //Смотреть результат
	screen_destroy();
	
	return 0;
}


// Ваша задача добавить к программе класс, который будет содержать в себе несколько объектов класса фигура, создавая тем самым композицию.

#include <iostream>
using namespace std;

// класс "точка"
class Point {

	// кооординаты
	int X;
	int Y;
public:

	//конструктор
	Point() {
		X = Y = 0;
	}

	//установка координат
	void SetPoint(int iX, int iY) {
		X = iX;
		Y = iY;
	}

	//демонстрация координат
	void Show() {
		cout << "----------------------------\n\n";
		cout << X << "\t" << Y << "\n\n";
		cout << "----------------------------\n\n";
	}
};
//класс фигура
class Figura {

	// агрегация точки
	// (координаты углов)
	Point* obj;

	// количество углов
	int count;
	// цвет фигуры
	int color;

public:

	//конструктор
	Figura() {
		count = color = 0;
		obj = NULL;
	}

	// создание фигуры
	void CreateFigura(int cr, int ct) {
		// если углов меньше трех - это не фигура
		if (ct < 3) exit(0);
		//инициализация цвета и количества углов
		count = ct;
		color = cr;
		// выдделение памяти под массив точек
		obj = new Point[count];
		if (!obj) exit(0);

		//установка координат точек
		int tempX, tempY;
		for (int i = 0; i < count; i++) {
			cout << "Set X\n";
			cin >> tempX;
			cout << "Set Y\n";
			cin >> tempY;
			obj[i].SetPoint(tempX, tempY);
		}
	}

	Figura& operator=(const Figura& other) {
		if (this != &other) {
			delete[] obj;
			count = other.count;
			color = other.color;
			obj = new Point[count];
			for (int i = 0; i < count; ++i) {
				obj[i] = other.obj[i];
			}
		}
		return *this;
	}

	//показ фигуры
	void ShowFigura() {
		cout << "----------------------------\n\n";
		cout << "Color " << color << "\n\nPoints - " << count << "\n\n";
		for (int i = 0; i < count; i++) {
			obj[i].Show();
		}
	}

	//если фигура была очистить память
	~Figura() {
		if (obj != NULL) delete[]obj;
	}


};

class Composition {
	Figura* figures;
	int figureCount;

public:
	Composition() {
		figures = NULL;
		figureCount = 0;
	}

	~Composition() {
		if (figures != nullptr) {
			delete[] figures;
		}
	}

	void AddFigure(int cr, int ct) {
		Figura* newFigures = new Figura[figureCount + 1];
		for (int i = 0; i < figureCount; i++) {
			newFigures[i] = figures[i];
		}
		newFigures[figureCount].CreateFigura(cr, ct);
		delete[] figures;
		figures = newFigures;
		figureCount++;
	}

	void ShowFigures() const {
		for (int i = 0; i < figureCount; i++) {
			figures[i].ShowFigura();
		}
	}
};

void main() {

	Composition f;
	f.AddFigure(255, 3);
	f.AddFigure(85, 4);
	f.ShowFigures();

}
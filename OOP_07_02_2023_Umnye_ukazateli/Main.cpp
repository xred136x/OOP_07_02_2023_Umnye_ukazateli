#include<iostream>
#include<memory>
// Umnye ukazateli

class A {
public:
	A() {
		std::cout << "Construktor A\n";
	}
	~A() {
		std::cout << "Destructor A\n";
	}
};

class Point {
public:
	Point(int x, int y) : _x(x), _y(y) {
		std::cout << "Point constructor\n";
	}
	int getX()const{
		return _x;
	}
	~Point() {
		std::cout << "Point destructor\n";
	}
private:
	int _x;
	int _y;
};

template<class T>
class SmartPtr {
	T* _ptr;
public:
	SmartPtr(T* t) : _ptr(t){}

	T* operator->() {
		return _ptr;
	}
	~SmartPtr() {
		delete _ptr;
	}
};
//unique_ptr почти как и любой пользовательский тип можно передать в параметры функции по ссылке
void basicFunc(const std::unique_ptr<Point>& p) {
	std::cout << p->getX() << '\n';
}
class Parent {

};
class Child : public Parent {

};
std::shared_ptr<Parent> SomeMethod(){
Child b;
std::shared_ptr<Parent> a = std::make_shared<Parent>(b);
	return a;
}

class IVehicle {
public:
	virtual int getSpeed()const = 0;
	virtual const std::string& getType()const = 0;
	virtual ~IVehicle(){}
};

class Car : public IVehicle
{
public:
	Car (int speed):_speed(speed){}
	int getSpeed()const override{
		return _speed;
	}
	const std::string& getType()const override {
		return _type;

	}
private:
	int _speed;
	std::string _type = "Car";

};

class Van : public Car
{
public:
	Van(int speed) : Car(speed) {}
	
	const std::string& getType()const override {
		return _type;

	}
private:
	
	std::string _type = "Van";
};

void funcCar(std::shared_ptr<Car> carPtr) {
	std::cout << "Inside funcCar\n";
	std::cout << carPtr->getSpeed() << '\n';
	std::cout << carPtr->getType() << '\n';
}

int main() {
	setlocale(LC_ALL, "ru");

	std::shared_ptr<Van> v = std::make_shared<Van>(50);
	std::cout << v->getType() << '\n';
	std::cout << v->getSpeed() << '\n';
	std::cout << "--------------------------------------------\n";
	std::shared_ptr<Car> c = std::dynamic_pointer_cast<Car>(v);
	std::cout << c->getType() << '\n';
	std::cout << c->getSpeed() << '\n';
	std::cout << "--------------------------------------------\n";
	funcCar(c);
	//A* a = new A(); деструктор не вызывается, т.к нет delete
	//std::auto_ptr<A> p(new(A));
	// shared_ptr- имеет контрольный блок, в котором помимо прочего лежит счетчик указателей
	// unique_ptr- гарантирует, что только один указатель будет владеть одним объектом

	//std::unique_ptr<A> uptr(new A());

	/*std::unique_ptr<Point> pPoint(new Point(5, 4));
	std::cout << pPoint->getX() << '\n';*/
	//pPoint.get()->getX();
	//Point *p
	/*SmartPtr<Point> sm(new Point(5, 4));
	std::cout << sm->getX()<<'\n';     */ //стрелочный оператор, если возвращат указатель, то в этом случае на этот указатель снова 
	//вызывается стрелочный оператор, рекурсивно до тех пор, пока не вернется объект

	/*std::unique_ptr<Point> p5 = std::make_unique<Point>(5, 4);
	std::shared_ptr<Point> sp1 = std::make_shared<Point>(1, 2);
	std::shared_ptr<Point> sp2 = sp1; */



	return 0;
}
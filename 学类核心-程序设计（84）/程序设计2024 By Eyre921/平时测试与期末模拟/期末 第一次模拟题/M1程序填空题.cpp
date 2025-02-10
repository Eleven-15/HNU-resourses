#include <iostream>
using namespace std;

//声明抽象基类Shape
class Shape {
	public:
		virtual float area() const = 0;

		virtual float volume() const = 0;

		virtual void shapeName() const = 0;

		virtual void display(ostream &out) = 0;
};

class Square : public Shape {
	public:
		Square(float a = 1) {
			r = a;
		}
		virtual float area() const {
			return r * r;
		}
		virtual float volume() const {
			return 0.0;
		}
		virtual void shapeName() const {
			cout << "Square:";
		}

		virtual void display(ostream &out) {
			out << "r=" << r << endl;
		}

	protected:
		float r;
};

class Cube : public Square {
	public:
		Cube(float a = 1): Square(a) {}
		virtual float area() const {
			return 6 * r * r;
		}
		virtual float volume() const {
			return r * r * r;
		}
		virtual void shapeName() const {
			cout << "Cube:";
		}

		virtual void display(ostream &out) {
			out << "cuber=" << r << endl;
		}
};

ostream &operator<<(ostream &output, Shape &s) {
	s.display(output);
	output << endl;
	return output;
}

void fun(Shape *s) {
	s->shapeName();
	cout << s->area() << endl;
	cout << s->volume() << endl;
	cout << *s;
}

int main() {
	Square s1(2);
	Cube c1(3);
	Shape *sh[2];
	sh[0] = &s1;
	sh[1] = &c1;
	for (int i = 0; i < 2; i++) {
		fun(sh[i]);
	}
	return 0;
}

/*
【问题描述】请阅读下面代码，并完成成代码

【输入形式】无
【输出形式】见样例
【样例输入】无
【样例输出】

Square:4

0

r=2

Cube:54

27

cuber=3

【样例说明】
【评分标准】
 */

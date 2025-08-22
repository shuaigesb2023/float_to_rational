#include "ftr.cpp"
#include "bigint.hpp"
#include <iostream>
class myval {
public:
	int v;
	myval() :v(0) {}
	myval(int n) :v(n) {}

	myval operator+(myval n) {
		return myval(v + n.v);
	}
	myval operator*(myval n) {
		return myval(v * n.v);
	}
	myval operator/(myval n) {
		return myval(v / n.v);
	}
	myval operator%(myval n) {
		return myval(v % n.v);
	}
	void operator=(myval n) {
		v = n.v;
	}
	friend bool operator==(myval n,myval m) {
		return m.v == n.v;
	}
};
int main() {
	//模板使用示例
	std::string s;
	std::cin >> s;
	std::pair<myval,myval> a = templatestdftr::float_to_rational<myval>(s);
	std::cout<<a.first.v<<'/' << a.second.v;

}
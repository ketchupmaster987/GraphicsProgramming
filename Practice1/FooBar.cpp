#include <iostream>
#include <vector>
#include <memory>

struct Foo {
	int x = 5;
};

void Bar(std::shared_ptr<Foo> foo) {
	std::cout << foo->x << std::endl;
}

void Baz(Foo* f)
{
	std::cout << f->x << std::endl;
	delete f;
}

int main()
{
	std::shared_ptr<Foo> foo = std::make_shared<Foo>();

	Bar(foo);

	Baz(foo.get());
}
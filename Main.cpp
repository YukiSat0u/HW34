#include <iostream>
#include <type_traits>
#include <string>
#include <concepts>

template<typename T>
concept HasHashMethod = requires(T t)
{
	{ t.hash() }->std::convertible_to<long>;
};

template<typename T>
concept HasToStringMethod = requires(T t) 
{
	{ t.toString() }->std::same_as<std::string>;
};

template<typename T>
concept NoVirtualDestructor = !std::has_virtual_destructor<T>::value;

template<typename T>
concept ComplexConcept = HasHashMethod<T> && HasToStringMethod<T> && NoVirtualDestructor<T>;

class MyType 
{
public:
	long hash()
	{
		return 42;
	}

	std::string toString()
	{
		return "MyType";
	}
};

class AnotherType
{
public:
	long hash() 
	{
		return 99;
	}

	std::string toString() 
	{
		return "AnotherType";
	}

	virtual ~AnotherType() {}
};

int main() 
{
	/********************************************************************************************************
	Есть два класса : MyType и AnotherType.
	Оба класса имеют методы hash() и toString(), но только у класса MyType нет виртуального деструктора.
	Затем мы используем концепт ComplexConcept<T> для проверки соответствия этих классов нашим требованиям.
	********************************************************************************************************/

	std::cout << std::boolalpha;
	std::cout << "MyType is ComplexConcept? " << ComplexConcept<MyType> << std::endl;
	std::cout << "AnotherType is ComplexConcept? " << ComplexConcept<AnotherType> << std::endl;

	return 0;
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-nodiscard"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class PizzaHat {
public:
	[[nodiscard]] virtual string getName() const = 0;
	[[nodiscard]] virtual unsigned short getPrise(unsigned short size) const = 0;
	[[nodiscard]] virtual unsigned short incSalt(unsigned short quantity, unsigned short size) const = 0;
	[[nodiscard]] virtual unsigned short incCheese(unsigned short quantity, unsigned short size) const = 0;
};

class Original : public PizzaHat {
public:
	[[nodiscard]] string getName() const override
	{
		return "Оригинальная";
	}
	[[nodiscard]] unsigned short getPrise (unsigned short size) const override
	{
		return 400*(1 + size/100);
	}
	[[nodiscard]] unsigned short incSalt(unsigned short quantity, unsigned short size) const override
	{
		return  quantity * (size/5);
	}
	[[nodiscard]] unsigned short incCheese(unsigned short quantity, unsigned short size) const override
	{
		return quantity * size;
	}
};

class Mexican : public PizzaHat {
public:
	string getName() const override
	{
		return "Месиканская";
	}
	unsigned short getPrise (unsigned short size) const override
	{
		return 450*(1 + size/100);
	}
	unsigned short incSalt(unsigned short quantity, unsigned short size) const override
	{
		return  quantity * (size/5);
	}
	unsigned short incCheese(unsigned short quantity, unsigned short size) const override
	{
		return quantity * size;
	}
};

class ThreeCheeses : public PizzaHat {
public:
	string getName() const override
	{
		return "Три сыра";
	}
	unsigned short getPrise (unsigned short size) const override
	{
		return 350*(1 + size/100);
	}
	unsigned short incSalt(unsigned short quantity, unsigned short size) const override
	{
		return  quantity * (size/5);
	}
	unsigned short incCheese(unsigned short quantity, unsigned short size) const override
	{
		return quantity * size;
	}
};

class PizzaOrder {
	vector<const PizzaHat *> Pizza;
	unsigned short TotalPrise = 0, salt = 0, cheese = 0;
	unsigned short PizzaSize = 25;
	unsigned short PriseSum[20]{};
public:
	void add(const PizzaHat *pizza)
	{
		Pizza.push_back(pizza);
	}
	void print()
	{
		size_t size = Pizza.size();
		
		if (size == 0)
		{
			cout << "Вы ничего не заказали";
		}
		else
		{
			for (size_t i = 0; i < size; i++)
			{
				cout << "\nУточнение для заказа номер " << i+1 << ":" << endl;
				cout << "Введите размер пиццы (25, 30, 35, 40): ";
				cin >> PizzaSize;
				cout << "\nСколько раз хотите добавить соли? ";
				cin >> salt;
				cout << "\nСколько раз хотите добавить сыра? ";
				cin >> cheese;
				PriseSum[i] = Pizza[i]->getPrise(PizzaSize) + Pizza[i]->incSalt(salt, PizzaSize) + Pizza[i]->incCheese(cheese, PizzaSize);
				cout << "\nВаш заказ:\n " << Pizza[i]->getName() << " - " << Pizza[i]->getPrise(PizzaSize) << "р." << endl;
				cout << "Количество добавленной соли: " << salt << " - " << Pizza[i]->incSalt(salt, PizzaSize) << "р." << endl;
				cout << "Количество добавленного сыра: " << cheese << " - " << Pizza[i]->incCheese(cheese, PizzaSize) << "р." << endl;
				cout << "Общая сумма за данную пиццу: " << PriseSum[i] << "р." << endl;
				TotalPrise += PriseSum[i];
			}
		}
		cout << "\nИтого: " << TotalPrise << "р.";
	}
};

int main() {
	PizzaOrder MyOrder;
	short choice = -1;
	
	cout << "Меню:" << endl;
	cout << "1. Оригинальная. Состав: курица, сыр, помидоры" << endl;
	cout << "2. Мексиканская. Состав: салями, острый перец, помидоры, сыр, оливки" << endl;
	cout << "3. Три сыра. Состав: моцарелла, чеддер, ламбер." << endl;
	
	do
	{
		cout << "\nВведите номер пицц которые хотите заказать. Если хотите закончить выбирать пиццы - введите любое некорректное число: ";
		cin >> choice;
		switch (choice)
		{
			case 1:
				MyOrder.add(new Original()); break;
			case 2:
				MyOrder.add(new Mexican()); break;
			case 3:
				MyOrder.add(new ThreeCheeses()); break;
			default:
				break;
		}
	} while ((choice > 0) && (choice < 4));
	
	MyOrder.print();
}
/*
Завдання 1(обов’язкове, на 10).
Створити шаблон  класу Двозв’язний список( CDlist<T>). Визначити методи у шаблонному класі
o	додавання нового елементу на початок списку
o	додавання нового елементу у хвіст списку
o	видалення елемента з голови списку
o	видалення елемента з хвоста списку
o	видалення всіх елементів
o	видалення елемента за значенням
o	перегляд елементів списку зліва направо
o	перегляд елементів списку справа наліво
o	вставка нового вузла до заданого
o	вставка нового вузла  після заданого
o	пошук та заміна  заданого елементу (метод повертає число виконаних замін)
o	обертання списку(бажано виконувати перестановку вузлів, не значень у вузлах)
o	операція + для конкатенації(злиття) двох списків у  третій(результат операції, при цьому списки, що зливаються не змінюються)
o	операцією * для утворення перерізу двох списків у  третьому списку(результат операції), переріз двох списків містить їх спільні елементи без повторів

*/

#include "stdafx.h"
#include <iostream> 
#include <string>

using namespace std;


template<typename T>
class CDlist
{

private:

	struct Node
	{
		T data;
		Node * next, *prev;

		Node(T data, Node * next = nullptr, Node * prev = nullptr) : data(data), next(next), prev(prev)
		{
		}
	};

	Node * Head = nullptr, *Tail = nullptr;
	int size = 0;

public:


	CDlist() = default;
	
	//ctor copy
	CDlist(const CDlist & other)
	{
		Node * tmp = other.Head;
		//cout << "\n\tctor copy begin\n";

		while (tmp != nullptr)
		{
			addTail(tmp->data);
			//cout << "Test add " << tmp->data;
			tmp = tmp->next;
		}
		//cout << "\n\tctor copy end\n";
	}

	//ctor move
	CDlist(CDlist && other)
	{
		this->size = other.size;
		this->Head = other.Head;
		this->Tail = other.Tail;
		other.size = 0;
		other.Head = nullptr;
		other.Tail = nullptr;
		//cout << "\n\tctor move\n";
	}

	~CDlist()
	{
		clear();
	}

	//додавання нового елементу на початок списку
	void addHead(T data)
	{
		Node * tmp = new Node(data);
		if (isEmpty())
		{
			Head = Tail = tmp;
		}
		else
		{
			tmp->next = Head;
			Head->prev = tmp;
			Head = tmp;
		}
		++size;
	}

	//додавання нового елементу у хвіст списку
	void addTail(T data)
	{
		Node * tmp = new Node(data);
		if (isEmpty())
		{
			Head = Tail = tmp;
		}
		else
		{
			Tail->next = tmp;
			tmp->prev = Tail;
			Tail = tmp;
		}
		++size;
	}

	//видалення всіх елементів
	void clear()
	{
		Node * tmp = Head;
		while (Head != nullptr)
		{
			tmp = Head;
			Head = Head->next;
			delete tmp;
		}
		Tail = nullptr;
		size = 0;
	}

	bool isEmpty()const
	{
		return Head == nullptr;
	}

	//перегляд елементів списку зліва направо
	void printL()const
	{
		if (isEmpty())
			cout << "Empty!\n";
		else
		{
			Node * tmp = Head;
			cout << "Left  --> :\t";
			while (tmp != nullptr)
			{
				cout << tmp->data << "  ";
				tmp = tmp->next;
			}
			cout << endl;
		}
	}

	//перегляд елементів списку справа наліво
	void printR()const
	{
		if (isEmpty())
			cout << "Empty!\n";
		else
		{
			Node * tmp = Tail;
			cout << "Rigth <-- :\t";
			while (tmp != nullptr)
			{
				cout << tmp->data << "  ";
				tmp = tmp->prev;
			}
			cout << endl;
		}
	}

	//перегляд у дві сторони
	void print()const
	{
		printL();
		printR();
	}

	Node* search(T elem) const
	{
		Node * tmp = Head;
		while (tmp != nullptr && tmp->data != elem)
		{
			tmp = tmp->next;
		}
		return tmp;
	}


	//видалення елемента з голови списку
	void delHead()
	{
		
		if (isEmpty())
		{
			cout << "not found\n";
		}
		else
		{
			Node *current;
			current = Head;
			Head = Head->next;
			Head->prev = nullptr;
			delete current;
		}
		--size;
	}

	//видалення елемента з хвоста списку
	void delTail()
	{

		if (isEmpty())
		{
			cout << "not found\n";
		}
		else
		{
			Node *current;
			current = Tail;
			Tail = Tail->prev;
			Tail->next = nullptr;
			delete current;
		}
		--size;
	}


	//видалення елемента за значенням
	void delNode(T elem)
	{
		Node * del = search(elem);
		if (del == nullptr)
			cout << "not found\n";
		else
			if (del == Head && size == 1)
			{
				delete Head;
				Head = Tail = nullptr;
			}
			else
				if (del == Head)
				{
					delHead();
				}
				else
					if (del == Tail)
					{
						delTail();
					}
					else
					{
						del->prev->next = del->next;
						del->next->prev = del->prev;
						delete del;
					}
		--size;
	}


	//вставка нового вузла до заданого
	void insBefore(T srch, T newVal)
	{
		Node * sNode = search(srch);
		if (sNode == nullptr)
			return;
		if (sNode == Head)
			addHead(newVal);
		else
		{
			Node * ins = new Node(newVal);
			ins->next = sNode;
			ins->prev = sNode->prev;
			sNode->prev->next = ins;
			sNode->prev = ins;
		}
	}

	//вставка нового вузла  після заданого
	void insAfter(T srch, T newVal)
	{
		Node * sNode = search(srch);
		if (sNode == nullptr)
			return;
		if (sNode == Tail)
			addTail(newVal);
		else
		{
			Node * ins = new Node(newVal);
			ins->prev = sNode;
			ins->next = sNode->next;
			sNode->next->prev = ins;
			sNode->next = ins;
		}
	}

	//пошук та заміна  заданого елементу(метод повертає число виконаних замін)
	int replace(T srch, T newVal)
	{
		int count = 0;
		Node * tmp = Head;

		while (tmp != nullptr)
		{
			if (tmp->data == srch)
			{
				tmp->data = newVal;
				++count;
			}
			tmp = tmp->next;
		}

		return count;
	}

	//обертання списку(бажано виконувати перестановку вузлів, не значень у вузлах)
	void reverse()
	{
		Node *temp, *current = nullptr;
		current = Head;

		while (current != nullptr)
		{
			temp = current->prev;
			current->prev = current->next;
			current->next = temp;

			if (current->next == nullptr)
				Tail = current;
			if (current->prev == nullptr)
				Head = current;

			current = current->prev;
		}
	}

	//операція + для конкатенації(злиття) двох списків у  третій
	//(результат операції, при цьому списки, що зливаються не змінюються)
	CDlist operator + (const CDlist & list)
	{
		CDlist res(*this);
		Node * current = list.Head;
		while (current != nullptr)
		{
			res.addTail(current->data);
			//cout << "operator + " << current->data << " ";
			current = current->next;
		}
		return res;
	}

	//операцією * для утворення перерізу двох списків у  третьому списку(результат операції), 
	//переріз двох списків містить їх спільні елементи без повторів
	CDlist operator * (const CDlist & list)
	{
		CDlist res;
		Node * current = list.Head;
		while (current != nullptr)
		{
			if (this->search(current->data) != nullptr)
			{
				res.addTail(current->data);
				//cout << "Add elem " << current->data << endl;
			}
			//cout << "operator + " << current->data << " ";
			current = current->next;
		}
		return res;
	}
	
	
};

int main()
{
	CDlist<int> cd;
	cout << "\t-= Int =-\n";
	cout << "\taddHead\n";
	cd.addHead(1);
	cd.addHead(2);
	cd.addHead(3);
	cd.print();

	cout << "\taddTail\n";
	cd.addTail(4);
	cd.addTail(5);
	cd.print();

	cout << "\tdelHead\n";
	cd.delHead();
	cd.print();

	cout << "\tdelTail\n";
	cd.delTail();
	cd.print();

	cout << "\tdelNode(1)\n";
	cd.delNode(1);
	cd.print();

	cout << "\tclear\n";
	cd.clear();
	cd.print();

	cout << "\n\t-= String =-\n";
	CDlist<string> st;
	st.addHead("two");
	st.addHead("one");
	st.addTail("tail");
	st.print();

	cout << "\tinsBefore(tail)\n";
	st.insBefore("tail", "three");
	st.print();
	cout << "\tinsAfter(one)\n";
	st.insAfter("one", "half");
	st.print();
	st.addTail("two");
	st.print();
	cout << "\treplace(two, 2)\n";
	cout << "Q-ty of replace: " << st.replace("two", "2") << endl;
	st.print();
	st.reverse();
	st.print();

	cout << "\n\t-= Double =-\n";
	CDlist<double> d1;
	CDlist<double> d2;

	cout << "\td3 = d1 + d2\n";
	d1.addHead(1);
	d1.addHead(2);
	d1.addHead(3);
	d1.addHead(8);

	d2.addHead(7);
	d2.addHead(8);
	d2.addHead(10);
	
	CDlist<double> 	d3 = d1 + d2;
	d3.print();
	
	cout << "\td4 = d1 * d2 (only common elements)\n";
	CDlist<double> d4 = d1 * d2;
	d4.print();

	cout << "\treverse()\n  Before\n";
	d1.print();
	cout << "\n  After\n";
	d1.reverse();
	d1.print();



	cout << endl;
	system("pause");
	return 0;
}


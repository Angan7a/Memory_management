#include <iostream>
#include <memory>

using namespace std;

struct EmptyListError : runtime_error
{
    EmptyListError() : runtime_error("List is empty") {}
};

struct NotFoundError : runtime_error
{
    NotFoundError() : runtime_error("Not found") {}
};

template<class T>
class Node
{
public:
    Node(const T v) :
        next(nullptr),
        prev(nullptr),
        value(v)
    {}
    shared_ptr<Node> next;
    shared_ptr<Node> prev;
    T value;
};
template<class T>
class List
{
public:
    List();

    void add(shared_ptr<Node<T>> node);        // dodaje element na koniec listy
    shared_ptr<Node<T>> get(const T value);  // zwraca element o wskazanej wartości
    void addFirst(shared_ptr<Node<T>> node);  // dodaje pierwszy nod do listy
    shared_ptr<Node<T>> getBackward(const int value); // zwraca element n-ty od końca
private:
   shared_ptr<Node<T>> first;
   shared_ptr<Node<T>> last;
};

template<class T>
List<T>::List() :
    first(nullptr),
    last(first)
{}

template<class T>
void List<T>::add(shared_ptr<Node<T>> node)
{
    if(!first)
    {
        first = node;
        last = node;
    }
    else
    {
        try
        {
            get(node->value);
            cout << "I can't add this nod. It existes in list\n";
        }
        catch (runtime_error & re)
        {
            shared_ptr<Node<T>> current = first;
            while(current->next)
            {
                current = current->next;
            }
            current->next = node;
            node->prev = current;
            last = node;
        }
    }
}

template<class T>
shared_ptr<Node<T>> List<T>::get(const T value)
{
    if(!first)
    {
        throw EmptyListError{};
    }
    else
    {
        shared_ptr<Node<T>> current = first;
        do
        {
            if(current->value == value)
            {
                cout << "Found value " << current->value << endl;
                return current;
            }
            else
            {
                cout << "Going through " << current->value << endl;
                current = current->next;
            }
        } while(current);
        
        throw NotFoundError{};
        return nullptr;
    }
}

template<class T>
void List<T>::addFirst(shared_ptr<Node<T>> node)
{
    if(!first)
    {
        first = node;
        last = node;
    }
    else
    {
        first->prev = node;
        node->next = first;
        first = node;
    }
}

template<class T>
shared_ptr<Node<T>> List<T>::getBackward(const int value)
{
    int a = 1;
    shared_ptr<Node<T>> tmp = last;
    while (a != value)
    {
        a++;
        tmp = tmp->prev;
        if (tmp == NULL) throw NotFoundError();
    }
    return tmp;
}

int main()
{
    try
    {
        List<string> lista;
        shared_ptr<Node<string>> node4 = make_shared<Node<string>>("Piotr");
        shared_ptr<Node<string>> node7 = make_shared<Node<string>>("Zuzanna");

        lista.add(node4);
       // lista.add(node4);
       // lista.add(node4);
        //lista.add(make_shared<Node>(2));
        //lista.add(node7);
        //lista.add(make_shared<Node>(9));
        lista.addFirst(node7);
        lista.add(node4);
        auto node = lista.get("Zuzanna");
        cout << node->value << endl;
    }
    catch (runtime_error & re)
    {
        cerr << re.what() << endl;
    }

    return 0;
}

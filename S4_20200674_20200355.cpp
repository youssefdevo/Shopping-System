//   Name: Youssef Nasser Abdelhafeez   ID: 20200674
//   Name: Omar Magdy Abdelhaleem       ID: 20200355
#include<iostream>
#include<string>
using namespace std;

//First Class Item
class Item {
    // attributes declaration
private:
    static int N_item;
    int ID;
    string name;
    int quantity;
    float price;
public:

    // declaration member function
    //Defult Constructor
    Item() {

        ID = N_item;
        setName("Null");
        setQuantity(0);
        setPrice(0.0);
    }

    //Paramitarized Constructor
    Item(string n, int qnt, float p) {

        ID = N_item;
        setName(n);
        setQuantity(qnt);
        setPrice(p);
    }

    //Copy Constructor
    Item(const Item& itm) {
        ID = itm.ID;
        name = itm.name;
        quantity = itm.quantity;
        price = itm.price;
        N_item++;
    }

    //Setters & Getters
    void setID(int d) {
        ID = d;
    }
    int getID() {
        return ID;
    }
    void setName(string n) {
        name = n;
    }
    string getName() {
        return name;
    }
    void setQuantity(int q) {
        quantity = q;
    }
    int getquantity() {
        return quantity;
    }
    void setPrice(float p) {
        price = p;
    }
    float getPrice() {
        return price;
    }

    //"=="Operator function
    bool operator ==(const Item& itm2) {
        bool Equality;
        if (name == itm2.name)
            Equality = true;
        else
            Equality = false;
        return Equality;
    }

    //"+="Operator function
    Item operator +=(const Item& itm2) {
        quantity += itm2.quantity;
        return *this;
    }
    //"-="Operator function
    Item operator -=(int q) {
        quantity -= q;
        return *this;
    }

    // ">>" cin operator function
    friend istream& operator >>(istream& is, Item& itm)
    {
        cout << "Please Enter the name of item: ";
        is >> itm.name;
        cout << "Please Enter the quantity of this item: ";
        is >> itm.quantity;
        cout << "Please Enter the price of this item: ";
        is >> itm.price;
        return is;
    }

    // "<<" cout operator function & print item info
    friend ostream& operator <<(ostream& os, const Item& itm)
    {
        os << "\nItem ID: " << itm.ID
            << "\nItem Name: " << itm.name
            << "\nItem Quantity: " << itm.quantity
            << "\nItem Price: " << itm.price << '\n';
        return os;
    }

};

//Second Class Seller
class Seller {
    // attributes declaration
private:
    string name;
    string email;
    Item* items;
    int maxItems;
public:
    //declaration member function
    //Paramitarized constructor
    Seller(string n, string e, int mx) {
        setName(n);
        setEmail(e);
        setMaxItems(mx);
        items = new Item[maxItems];
        cnt = 0;
    }

    //Setters
    void setName(string n) {
        name = n;
    }
    void setEmail(string e) {
        email = e;
    }
    void setMaxItems(int mx) {
        maxItems = mx;
    }
    //">>" overloading operator to cin object of seller
    friend istream& operator >>(istream& is, Seller& sel1) {
        cout << "Please Enter your name: ";
        is >> sel1.name;
        cout << "Please Enter your E-mail: ";
        is >> sel1.email;
        cout << "Please Enter your store capacity: ";
        is >> sel1.maxItems;
        return is;
    }

    // "<<" overloading operator to print Seller info.
    friend ostream& operator <<(ostream& os, const Seller& obj)
    {
        os << "Seller Name: " << obj.name
            << "\nSeller Email: " << obj.email
            << "\nThe Maximum Capacity: " << obj.maxItems << '\n';
        return os;
    }
    //function to add items to dynamic array
    int cnt;
    bool AddItem(Item itm1, int q) {

        for (int i = 0; i < cnt; i++) {
            if (items[i] == itm1) {
                items[i] += itm1;
                cout << "\nItem added successfully.\n";
                return true;
            }
        }
        if (cnt < maxItems) {

            items[cnt++] = itm1;
            cout << "\nItem added successfully.\n";
            return true;
        }
        else {
            cout << "\nThe capacity is full.\n";

            return false;
        }

    }
    //function to sell items from dynamic array
    bool SellItem(string ItemName, int Quantity) {
        for (int i = 0; i < cnt; i++) {
            if (items[i].getName() == ItemName) {
                if (Quantity <= items[i].getquantity()) {
                    items[i] -= Quantity;
                    cout << "\nItem sold successfully.\n";
                    return true;
                }
                else {
                    cout << "“There is only { " <<
                        items[i].getquantity() <<
                        " } left for this item";
                    return true;
                }
            }
        }
        cout << "There is no item with this name. \n";
        return false;
    }
    //Function to print all items info
    void PrintItems() {
        for (int i = 0; i < cnt; i++) {
            cout << items[i];
        }
    }
    //Function to search item by ID
    Item* FindItem(int ID) {
        for (int i = 0; i < cnt; i++) {
            if (items[i].getID() == ID) {
                return &items[i];
            }
        }
        return nullptr;
    }
    //Destructor
    ~Seller() {
        delete[]items;
        cnt = 0;
    }
};

//Intalizing Static variables
int Item::N_item = 1;



int main()
{
    string name, email;
    int maxCapacity;
    //Ask user to enter his info
    cout << "Please Enter your name: ";
    cin >> name;
    cout << "Please Enter your E-mail: ";
    cin >> email;
    cout << "Please Enter your store capacity: ";
    cin >> maxCapacity;
    Seller seller1(name, email, maxCapacity);
    while (true) {
        int order;
        //Menu table
        cout << '\n' << "1. Print My Info." << '\n'
            << "2. Add An Item." << '\n'
            << "3. Sell An Item." << '\n'
            << "4. Print Items." << '\n'
            << "5. Find an Item by ID." << '\n'
            << "6. Exit" << '\n';

        cin >> order;
        if (order == 1) {
            cout << seller1;
        }
        else if (order == 2) {
            Item item1;
            cin >> item1;
            seller1.AddItem(item1, item1.getquantity());
        }
        else if (order == 3) {
            string name;
            int quantity;
            cout << "Enter the name of item that you want to sell: ";
            cin >> name;
            cout << "Enter the quantity of this item: ";
            cin >> quantity;
            seller1.SellItem(name, quantity);
        }
        else if (order == 4) {
            seller1.PrintItems();
        }
        else if (order == 5) {
            int ID;
            cout << "Enter the ID: ";
            cin >> ID;
            if (seller1.FindItem(ID) == nullptr) {
                cout << "There is no item with this specified ID, Try again\n";
            }
            else {
                cout << *seller1.FindItem(ID) << '\n';
            }
        }
        else if (order == 6) {
            break;
        }
        else {
            cout << "..Invalid number,,Please enter number from 1 to 6.\n";
        }
    }
    return 0;
}
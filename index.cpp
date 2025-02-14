#include <iostream>
#include <vector>
#include <string>
using namespace std;

class MenuItem
{
private:
    string name;
    double price;

public:
    MenuItem(string n, double p) : name(n), price(p) {}
    string getName() const { return name; }
    double getPrice() const { return price; }
    void display() const
    {
        cout << name << " - $" << price << endl;
    }
};

class Order
{
private:
    vector<MenuItem> items;

public:
    void addItem(const MenuItem &item)
    {
        items.push_back(item);
    }
    void displayOrder() const
    {
        cout << "\n--- Order Summary ---\n";
        double total = 0;
        for (const auto &item : items)
        {
            item.display();
            total += item.getPrice();
        }
        cout << "Total: $" << total << endl;
    }
    void clearOrder()
    {
        items.clear();
    }
};

class Cafeteria
{
private:
    vector<MenuItem> menu;

public:
    void addMenuItem(const MenuItem &item)
    {
        menu.push_back(item);
    }
    void displayMenu() const
    {
        cout << "\n--- Cafeteria Menu ---\n";
        for (size_t i = 0; i < menu.size(); ++i)
        {
            cout << i + 1 << ". ";
            menu[i].display();
        }
    }
    const MenuItem &getMenuItem(int index) const
    {
        if (index >= 0 && index < (int)menu.size())
            return menu[index];
        throw out_of_range("Invalid menu item index.");
    }
};

int main()
{
    Cafeteria cafeteria;
    cafeteria.addMenuItem(MenuItem("Burger", 5.99));
    cafeteria.addMenuItem(MenuItem("Pizza", 7.99));
    cafeteria.addMenuItem(MenuItem("Fries", 2.99));
    cafeteria.addMenuItem(MenuItem("Coke", 1.50));

    Order order;
    int choice;

    while (true)
    {
        cafeteria.displayMenu();
        cout << "Enter item number to add to your order (0 to finish, -1 to clear order): ";
        cin >> choice;

        if (choice == 0)
            break;
        if (choice == -1)
        {
            order.clearOrder();
            cout << "Order cleared!\n";
            continue;
        }
        try
        {
            order.addItem(cafeteria.getMenuItem(choice - 1));
            cout << "Item added to order!\n";
        }
        catch (out_of_range &)
        {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    order.displayOrder();
    return 0;
}

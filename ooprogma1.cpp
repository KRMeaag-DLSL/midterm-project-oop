#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

const int WIDTH = 30;

// Stops the program momentarily, asks the user for a letter + enter to proceed
void continueNext() {
    cout << "\nType any key and press enter to continue: ";
    string key;
    cin >> key;
    system("clear");
}

// Checks if wrong type was inputted by the user in int field
bool cinIntCheck() {
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nInvalid input! Please type a number!" << endl;
        return true;
    }

    return false;
}

// Checks if number is negative
bool numValidations(float input) {
    if (input < 1)
    {
        cout << "\nInvalid input! Please put a number greater than 0!";
        return true;
    }

    return false;
}

// Converts string to lowercase for case-insensitive comparison
string stringToLower(string lower) {
    for (int i = 0; i < lower.size(); i++) {
        lower[i] = tolower(lower[i]);
    }

    return lower;
}

// Asks user for input
int menu(int *choice) {
    cout << "\nMenu" << endl;
    cout << "\n1 — Add Item";
    cout << "\n2 - Update Item";
    cout << "\n3 - Remove Item";
    cout << "\n4 - Display Items by Category";
    cout << "\n5 — Display All Items";
    cout << "\n6 - Search Item";
    cout << "\n7 - Sort Items";
    cout << "\n8 - Display Low Stock Items";
    cout << "\n9 - Exit" << endl;
        
    cout << "\nType the number to where you want to go: ";
    cin >> *choice;

    // Checks if proper type
    if (cinIntCheck())
    {
        system("clear");
        cout << "\nInvalid input! Please type a number!" << endl;
        return 3;
    }

    // User wants to exit
    if (*choice == 9)
    {
        return 1;
    }

    if (*choice < 1 || *choice > 9)
    {
        system("clear");
        cout << "\nInvalid input! Please type a number between 1 and 9!" << endl;
        return 2;
    }

    return 0;
}

// Asks user to confirm to exit program
void confirmExit(string &input) {
    system("clear");
    do {
        cout << "Are you sure you want to exit? [Y/N]: ";
        cin >> input;

        if (input.length() > 1) {
            cout << "\nInvalid Input, Try Again!" << endl;
        }

        input = toupper(input[0]);

        if (input != "Y" && input != "N") {
            cout << "\nInvalid Input, Try Again!" << endl;
        }
    } while (input != "Y" && input != "N");

    system("clear");
}

class Item {
    private:
        string id;
        string name;
        int quantity;
        float price;
        string category;

    public:
        // Getters (Encapsulation)
        string getID () {
            return id;
        }

        string getName () {
            return name;
        }

        int getQuantity () {
            return quantity;
        }

        float getPrice () {
            return price;
        }

        string getCategory () {
            return category;
        }

        // Setters (Encapsulation)
        void setID () {  
            string input;
            cin.ignore();
            getline(cin, input);
            id = input;
        }
 
        void setName () {  
            string input;
            getline(cin, input);
            name = input;
        }
        
        void setQuantity () {  
            int input;
            cin >> input;
            quantity = input;
        }
    
        void setPrice () {
            float input;
            cin >> input;
            price = input;
        }

        void setCategory(string input) {
            category = input;
        }

        // Printing Function
        void printDetails () {
            cout << left << setw(WIDTH) << id << setw(WIDTH) << name
             << setw(WIDTH) << quantity << setw(WIDTH) << price;
        }
};

class Category {
    private:
        string productCategory;
        vector<Item> productDetails;
        Item productBuffer;

    public:
        Category(): productCategory("") {}
        Category(string setCategory) : productCategory(setCategory) {}

        // Getters (Encapsulation)
        vector<Item> getItems() {
            return productDetails;
        }

        string getCategory() {
            return productCategory;
        }

        int returnNumOfProds() {
            return getItems().size();
        }

        vector<Item> returnProds() {
            return getItems();
        }

        // Category Related Functions
        void add() {
            system("clear");
            cout << "\nCategory found! You will be adding items under the " << getCategory() << " category." << endl;
            
            cout << "\nWhat is the ID?: ";
            productBuffer.setID();
            cout << "\nWhat is the name of the product?: ";
            productBuffer.setName();

            do {
                cout << "\nHow many items are currently in stock?: ";
                productBuffer.setQuantity();
            }while (cinIntCheck() || numValidations((float) productBuffer.getQuantity()));

            do {
                cout << "\nHow much is the price per item? ";
                productBuffer.setPrice();
            }while (cinIntCheck() || numValidations((productBuffer.getPrice())));

            productBuffer.setCategory(productCategory);

            productDetails.push_back(productBuffer);

            system("clear");

            cout << "\nItem added successfully!" << endl;

            continueNext();
        }

        void update(int index) {
            cout << "\nYou are updating an item under the " << getCategory() << " category." << endl;
            int choice;
            float tempVal;

            cout << "\nWhich field are you updating?" << endl;
            cout << "1. Quantity\n2. Price" << endl;

            do {
                cout << "\nPick between the two numbers: ";
                cin >> choice;

                if (cinIntCheck())
                {
                    continue;
                }

                if (choice < 1 || choice > 2)
                {
                    cout << "Invalid input! Please type a number between 1 and 2!" << endl;
                }
            } while (cinIntCheck() || choice < 1 || choice > 2);

            switch (choice) {
                case 1:
                    do {
                        cout << "\nWhat will be the updated quantity for Item \"" << productDetails[index].getName() << "\"? ";
                        tempVal = productDetails[index].getQuantity();
                        productDetails[index].setQuantity();
                    } while (cinIntCheck());
                    cout << "\nQuantity of Item \"" << productDetails[index].getName() << "\" is updated from " << tempVal << " to " << productDetails[index].getQuantity();
                    break;

                case 2:
                    do {
                        cout << "\nWhat will be the new price for Item \"" << productDetails[index].getName() << "\"? ";
                        tempVal = productDetails[index].getPrice();
                        productDetails[index].setPrice();
                    } while (cinIntCheck());
                    cout << "\nPrice of Item \"" << productDetails[index].getName() << "\" is updated from " << tempVal << " to " << productDetails[index].getPrice();
                    break;
                default:
                    cout << "\nCritical Error!" << endl;
            }
        }

        void remove(int index) {
            cout << "\nYou removed an entry under the " << getCategory() << " category." << endl;
            cout << "\nItem \"" << productDetails[index].getName() << "\" has been removed from the inventory";
            productDetails.erase(productDetails.begin() + index);
        }

        void displayByCategory() {
            vector<Item> categoryItems = getItems();

            if (categoryItems.empty()) {
                cout << "\nNo items added in this category yet!" << endl;
            }
            else {
                cout << "\nHere are the products under the " << getCategory() << " category." << endl;
                cout << left << setw(WIDTH) << "Product ID" << setw(WIDTH) << "Product Name"
                << setw(WIDTH) << "Quantity of Product" << setw(WIDTH) << "Product Price" << endl;
                for (int i = 0, size = categoryItems.size(); i < size; i++)
                {
                    categoryItems[i].printDetails();
                    cout << endl;
                }
            }

            continueNext();
        }

        void searchDisp(int index) {
            vector<Item> categoryItems = getItems();
            
            cout << left << setw(WIDTH) << "Product ID" << setw(WIDTH) << "Product Name" << setw(WIDTH) 
            << "Quantity of Product" << setw(WIDTH) << "Product Price" << setw(WIDTH) << "Category" << endl;

            categoryItems[index].printDetails();
            cout << left << setw(WIDTH) << categoryItems[index].getCategory();
        }

        bool findIDHere(string inputID, int *indexPtr, int *foundHere, int index) {
            *foundHere = index;
            if (productDetails.empty())
            {
                return false;
            }

            for (int i = 0; i < productDetails.size(); i++) {
                if (inputID == productDetails[i].getID())
                {
                    cout << "\nItem Found!" << endl;
                    *indexPtr = i;
                    return true;
                }
            }

            return false;
        }
};

// Primary class that handles every function
class MainInventory {
    private:
        vector<Item> fullList;
        Item tempVal;
        static Category category[3];

    public:
        MainInventory() {
            category[0] = Category("Clothing");
            category[1] = Category("Electronics");
            category[2] = Category("Entertainment");
        }

        static Category returnCategory(int choice) {
            return category[choice];
        }

        static int returnSizeCategory(int chosenCategory) {
            return category[chosenCategory].returnNumOfProds();
        }

        // ID Related Functions
        static void addItemInventory(int chosenCategory) {
            category[chosenCategory].add();
        }

        static void showCategoryInventory(int chosenCategory) {
            category[chosenCategory].displayByCategory();
        }

        // Category Related Functions
        static void updateItemInventory(int chosenCategory, int index) {
            category[chosenCategory].update(index);
        }

        static void removeItemInventory(int chosenCategory, int index) {
            category[chosenCategory].remove(index);
        }

        static void searchItemInventory(int chosenCategory, int index) {
            category[chosenCategory].searchDisp(index);
        }

        // Full List Related Functions
        bool collectAllItems() {
            if (category[0].returnNumOfProds() == 0 && category[1].returnNumOfProds() == 0 && category[2].returnNumOfProds() == 0)
            {
                cout << "\nError! Cannot perform tasks since there are no products!" << endl;
                return true;
            }

            vector<Item> categoryHelper[3];

            for (int i = 0; i < 3; i++)
            {
                categoryHelper[i] = category[i].returnProds();
                fullList.insert(fullList.end(), categoryHelper[i].begin(), categoryHelper[i].end());
            }

            return false;
        }

        int ascendingInt(int a, int b) {
            return a > b;
        }

        int descendingInt(int a, int b) {
            return a < b;
        }

        float ascendingFloat(float a, float b) {
            return a > b;
        }

        float descendingFloat(float a, float b) {
            return a < b;
        }

        void bubbleSortQuantity(int (MainInventory::*compare)(int, int)) {
            for (int i = 0; i < fullList.size() - 1; i++) {
                for (int j = 0; j < fullList.size() - 1; j++) {
                    if ((this->*compare)(fullList[j].getQuantity(), fullList[j+ 1].getQuantity())) {
                        tempVal = fullList[j];
                        fullList[j] = fullList[j + 1];
                        fullList[j + 1] = tempVal;
                    }
                } 
            }
        }

        void bubbleSortPrice(float (MainInventory::*compare)(float, float)) {
            for (int i = 0; i < fullList.size() - 1; i++) {
                for (int j = 0; j < fullList.size() - 1; j++) {
                    if ((this->*compare)(fullList[j].getPrice(), fullList[j + 1].getPrice())) {
                        tempVal = fullList[j];
                        fullList[j] = fullList[j + 1];
                        fullList[j + 1] = tempVal;
                    }
                } 
            }
        }

        void dispSort() {
            if (collectAllItems())
            {
                continueNext();
                return;
            }

            int choice1;
            int choice2;
            string sortedBy[2] = {"quantity", "price"};
            string order[2] = {"ascending", "descending"};

            int (MainInventory::*orderMethodsInt[2])(int, int) = {&MainInventory::ascendingInt, &MainInventory::descendingInt};
            float (MainInventory::*orderMethodsFloat[2])(float, float) = {&MainInventory::ascendingFloat, &MainInventory::descendingFloat};

            cout << "\nHow should the list be sorted?" << endl;
            cout << "1. Quantity\n2. Price" << endl;

            do {
                cout << "\nPick between the two numbers: ";
                cin >> choice1;

                if (cinIntCheck())
                {
                    continue;
                }

                if (choice1 < 1 || choice1 > 2)
                {
                    cout << "Invalid input! Please type a number between 1 and 2!" << endl;
                }
            } while (cinIntCheck() || choice1 < 1 || choice1 > 2);

            cout << "\nWhat order should it be?" << endl;
            cout << "1. Ascending\n2. Descending" << endl;

            do {
                cout << "\nPick between the two numbers: ";
                cin >> choice2;

                if (cinIntCheck())
                {
                    continue;
                }

                if (choice2 < 1 || choice2 > 2)
                {
                    cout << "Invalid input! Please type a number between 1 and 2!" << endl;
                }
            } while (cinIntCheck() || choice2 < 1 || choice2 > 2);

            switch (choice1) {
                case 1:
                    bubbleSortQuantity(orderMethodsInt[choice2 - 1]);
                    break;
                
                case 2:
                    bubbleSortPrice(orderMethodsFloat[choice2 - 1]);
                    break;
            }

            cout << "\nHere are the products sorted by " << sortedBy[choice1 - 1] << " in " << order[choice2 - 1] << " order:" << endl;
 
            cout << left << setw(WIDTH) << "Product ID" << setw(WIDTH) << "Product Name" << setw(WIDTH) 
            << "Quantity of Product" << setw(WIDTH) << "Product Price" << endl;

            for (int i = 0; i < fullList.size(); i++) {
                cout << left << setw(WIDTH) << fullList[i].getID() << setw(WIDTH) << fullList[i].getName() << setw(WIDTH) 
                << fullList[i].getQuantity() << setw(WIDTH) << fullList[i].getPrice() << endl;
            }

            fullList.clear();
            continueNext();
        }

        void dispAll() {
            if (collectAllItems())
            {
                continueNext();
                return;
            }

            cout << "\nHere are the products currently in the inventory right now:" << endl;
 
            cout << left << setw(WIDTH) << "Product ID" << setw(WIDTH) << "Product Name" << setw(WIDTH) 
            << "Quantity of Product" << setw(WIDTH) << "Product Price" << setw(WIDTH) << "Category" << endl;

            for (int i = 0; i < fullList.size(); i++) {
                cout << left << setw(WIDTH) << fullList[i].getID() << setw(WIDTH) << fullList[i].getName() << setw(WIDTH) 
                << fullList[i].getQuantity() << setw(WIDTH) << fullList[i].getPrice() << setw(WIDTH) << fullList[i].getCategory() << endl;
            }

            fullList.clear();
            continueNext();
        }

        void dispLow() {
            bool exists;

            if (collectAllItems())
            {
                continueNext();
                return;
            }

            cout << "\nHere are the products low in quantity right now:" << endl;
 
            cout << left << setw(WIDTH) << "Product ID" << setw(WIDTH) << "Product Name" << setw(WIDTH) 
            << "Quantity of Product" << setw(WIDTH) << "Product Price" << setw(WIDTH) << "Category" << endl;

            for (int i = 0; i < fullList.size(); i++) {
                if (fullList[i].getQuantity() < 6)
                {
                    cout << left << setw(WIDTH) << fullList[i].getID() << setw(WIDTH) << fullList[i].getName() << setw(WIDTH) 
                    << fullList[i].getQuantity() << setw(WIDTH) << fullList[i].getPrice() << setw(WIDTH) << fullList[i].getCategory() << endl;
                    exists = true;
                }
            }

            if (!exists)
            {
                system("clear");
                cout << "\nThere are no low stock items!" << endl;
            }

            fullList.clear();
            continueNext();
        }
};

Category MainInventory::category[3]; // Since I declared a static variable

// Abstract Class
class FindInventory : protected MainInventory {
    public:
        // Virtual Functions (Abstraction)
        virtual void askUser(int choice) = 0;
        virtual bool confirmIfExists(string userInput, int *inCategory, int *inIndex) = 0;
};

// Handler for Category Related Methods
class CategoryMethods : protected FindInventory {
    private:
        int chosenCategory;

    public:
        void askUser(int choice) override {
            string input;

            string categoriesDisp[3] = {"Clothing", "Electronics", "Entertainment"};

            cout << "\nAvailable Categories:" << endl;

            for (int i = 0; i < 3; i++) {
                cout << "— " << categoriesDisp[i] << endl;
            }

            cout << "\nWhat is the category? ";
            cin >> input;

            if (!confirmIfExists(input, &chosenCategory, 0))
            {
                return; // Early Return
            }      

            switch (choice) {
                case 1:
                    addItemInventory(chosenCategory);
                    break;

                case 4:
                    showCategoryInventory(chosenCategory);
                    break;
            }

        }

        bool confirmIfExists(string userInput, int *inCategory, int *inIndex) override {
            string lowerInput;

            lowerInput = stringToLower(userInput);

            string categoriesCmp[3] = {"clothing", "electronics", "entertainment"};

            for (int i = 0; i < 3; i++) {
                if (categoriesCmp[i] == lowerInput) {
                    *inCategory = i;
                    return true;
                }
            }
            
            cout << "\nCategory " << userInput << " does not exist!" << endl;
            continueNext();
            return false;
        }
};

// Handler for ID Related Methods
class IDMethods : protected FindInventory {
    private:
        string chosenID;
        int itemCategory;
        int itemIndex;

    public:
        void askUser(int choice) override {

            if (returnSizeCategory(0) == 0 && 
                returnSizeCategory(1) == 0 && 
                returnSizeCategory(2) == 0) {
                cout << "\nError! Cannot perform tasks since there are no products!" << endl;
                continueNext();
                return;
            }

            cout << "\nWhat is the ID of the product? ";
            cin.ignore();
            getline(cin, chosenID);

            if (!confirmIfExists(chosenID, &itemCategory, &itemIndex))
            {
                return; // Early Return
            }   

            switch (choice) {
                case 2:
                    updateItemInventory(itemCategory, itemIndex);
                    break;

                case 3:
                    removeItemInventory(itemCategory, itemIndex);
                    break;

                case 6:
                    searchItemInventory(itemCategory, itemIndex);
                    break;
            }

            cout << endl;

            continueNext();
        }

        bool confirmIfExists(string userInput, int *inCategory, int *inIndex) override {
            for (int i = 0; i < 3; i++)
            {
                if (returnCategory(i).findIDHere(userInput, inIndex, inCategory, i))
                return true;
            }

            cout << "\nItem not found!" << endl;
            continueNext();
            return false;
        }
};

// Sends the user to the proper method
void choiceHandler(int choice, MainInventory *inventory, IDMethods *ids, CategoryMethods *categories) {
    int chosenCategory = 0;

    system("clear");

    switch(choice)
    {
        case 1: case 4: // Category Related Methods
            categories->askUser(choice);
            break;

        case 2: case 3: case 6: // ID Related Methods
            ids->askUser(choice);
            break;

        case 5: 
            inventory->dispAll();
            break;
        
        case 7:
            inventory->dispSort();
            break;

        case 8: 
            inventory->dispLow();
            break;
    }
}

int main(void) {
    MainInventory inventory;
    IDMethods ids;
    CategoryMethods categories;

    string confirm = "N";
    int choice;

    system("clear");

    do {
        switch (menu(&choice)) {
            case 0: // User picked a choice
                choiceHandler(choice, &inventory, &ids, &categories);
                break;

            case 1: // User wants to exit
                confirmExit(confirm);
                break;

            case 2: case 3: // Error 1: Not in the choices, Error 2: Type is not the same
                continueNext();
                break;
        }
    } while (confirm == "N");

    return 0;
}
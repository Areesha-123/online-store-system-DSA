#include <iostream>
#include <fstream>
 #include <vector> 
 #include <string>
#include <limits> 
// provides std::numeric_limits class

using namespace std;

class Product { 
protected:
    int pcode;
    float price;
    float dis;
    string pname;
    int stock; 

public: // contructor
    Product(int code = 0, float pr = 0.0, float discount = 0.0, string name = "", int st = 0)
        : pcode(code), price(pr), dis(discount), pname(name), stock(st) {}
    // getter, return protected attributes 
    int getCode() const { return pcode; }
    string getName() const { return pname; }
    float getPrice() const { return price; }
    float getDiscount() const { return dis; }
    int getStock() const { return stock; } // Getter for stock
     // setter, update product details 
    void setDetails(int code, string name, float pr, float discount, int st) {
        pcode = code;
        pname = name;
        price = pr;
        dis = discount;
        stock = st;
    }
// Update stock after purchase
    void updateStock(int qty) { stock -= qty; } 
    
 void setRating(float rating) {
     
    }
   
};

class ProductNode {
public:
    Product data;
    ProductNode* next;
    //contructor
    ProductNode(Product product) : data(product), next(NULL) {}
};

class ProductList {
private:
    ProductNode* head;
// constructor
public:
    ProductList() : head(NULL) {
        loadFromFile("products.txt"); // load products from file 
    }

    void clearProducts() { //
        while (head != NULL) {
            ProductNode* temp = head;
            head = head->next;
            delete temp;
        }
        saveToFile("products.txt"); //Save empty list to file
    }

    void addProduct(const Product& product) {
        // it will check for duplicate product code
        ProductNode* temp = head;
        while (temp != NULL) {
            if (temp->data.getCode() == product.getCode()) {
                cout << "Product code already exists. Please use a unique code." << endl;
                return;
            }
            temp = temp->next;
        }

        ProductNode* newNode = new ProductNode(product);
        newNode->next = head;
        head = newNode;
        saveToFile("products.txt"); // Save to file after adding
    }

    bool editProduct(int code) {
        ProductNode* temp = head;
        while (temp != NULL) {
            if (temp->data.getCode() == code) {
                int newCode;
                float price, discount;
                string name;
                int stock;

                cout << "Enter new details (code, name, price, discount, stock): ";
                cin >> newCode >> name >> price >> discount >> stock;

                // input validation
                if (cin.fail() || newCode <= 0 || price < 0 || discount < 0 || stock < 0) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Please enter positive values." << endl;
                    return false;
                }

                temp->data.setDetails(newCode, name, price, discount, stock);
                saveToFile("products.txt"); // Save to file after editing
                return true;
            }
            temp = temp->next;
        }
        cout << "\nProduct not found!";
        return false;
    }

    bool deleteProduct(int code) {
        ProductNode* temp = head;
        ProductNode* prev = NULL;
        while (temp != NULL) {
            if (temp->data.getCode() == code) {
                if (prev) prev->next = temp->next;
                else head = temp->next;
                delete temp;
                saveToFile("products.txt"); // Save to file after deleting
                return true;
            }
            prev = temp;
            temp = temp->next;
        }
        cout << "\nProduct not found!";
        return false;
    }

    void displayProducts() const {
        ProductNode* temp = head;
        if (!temp) {
            cout << "\nNo products available.";
            return;
        }
        cout << "\nCode\tName\tPrice\tDiscount\tStock\n";
        while (temp != NULL) {
            cout << temp->data.getCode() << "\t" << temp->data.getName()
                 << "\t" << temp->data.getPrice() << "\t" << temp->data.getDiscount() << "%\t" << temp->data.getStock() << "\n";
            temp = temp->next;
        }
    }

    ProductNode* getHead() const { return head; }

    void saveToFile(const string& filename) {
        ofstream file(filename.c_str()); // Convert std::string to const char*
        if (!file) {
            cout << "Error opening file for writing!" << endl;
            return;
        }
        ProductNode* temp = head;
        while (temp) {
            file << temp->data.getCode() << " "
                 << temp->data.getName() << " "
                 << temp->data.getPrice() << " "
                 << temp->data.getDiscount() << " "
                 << temp->data.getStock() << "\n";
            temp = temp->next;
        }
        file.close(); // Close the file
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename.c_str()); // Convert std::string to const char*
        if (!file) {
            cout << "Error opening file for reading!" << endl;
            return;
        }
        int code, stock;
        string name;
        float price, discount;
        while (file >> code >> name >> price >> discount >> stock) {
            if (price < 0 || discount < 0 || stock < 0) {
                cout << "Invalid data in file. Skipping entry." << endl;
                continue; // Skip invalid entries
            }
            addProduct(Product(code, price, discount, name, stock));
        }
        file.close();
    }
};
class Order {
public:
    int productCode;
    int quantity;
    float totalPrice;

    Order(int code, int qty, float price) : productCode(code), quantity(qty), totalPrice(price) {}
};

class User {
protected:
    string username;
    string password;

public:
    virtual void menu(ProductList& list) = 0;

    bool login(const string& user, const string& pass) {
        return (username == user && password == pass);
    }

    void setCredentials(const string& user, const string& pass) {
        username = user;
        password = pass;
    }
};

class Administrator : public User {
public:
    Administrator() {
        setCredentials("ASAstore", "12345"); // Set solid username and password
    }

    void menu(ProductList& list) override {
        int choice;
        while (true) {
            cout << "\nADMIN MENU\n1. Add Product\n2. Edit Product\n3. Delete Product\n4. Display Products\n5. Clear All Products\n6. Return to the Main menu\nChoice: ";
            cin >> choice;

            // Input validation for choice
            if (cin.fail()) {
                cin.clear(); // Clear the error state
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the invalid input
                cout << "\nInvalid choice! Please enter a number." << endl;
                continue; // Restart the loop
            }

            switch (choice) {
                case 1: {  //add products
                    int code, stock;
                    float price, discount;
                    string name;
                    cout << "Enter product details (code, name, price, discount, stock): ";
                    cin >> code >> name >> price >> discount >> stock;

                    // Input validation
                    if (cin.fail() || code <= 0 || price < 0 || discount < 0 || stock < 0) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input. Please enter positive values." << endl;
                        continue; // Restart the loop
                    }

                    list.addProduct(Product(code, price, discount, name, stock));
                    break;
                }
                case 2: {  //edit product            
				 int code;
                    cout << "Enter product code to edit: ";
                    cin >> code;

                    // Input validation
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input. Please enter a valid product code." << endl;
                        continue; // Restart the loop
                    }

                    list.editProduct(code);
                    break;
                }
                case 3: { //delete product
                    int code;
                    cout << "Enter product code to delete: ";
                    cin >> code;

                    // Input validation
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input. Please enter a valid product code:)" << endl;
                        continue; // Restart the loop
                    }

                    list.deleteProduct(code);
                    break;
                }
                case 4: // display products
                    list.displayProducts();
                    break;
                case 5: //clear all products
                    list.clearProducts();
                    cout << "All products have been deleted." << endl;
                    break;
                case 6: //return to the main menu
                    return;
                default:
                    cout << "\nInvalid choice!";
            }
        }
    }
};

class Buyer : public User { // inherits user class
private:
    vector<Product> cart;
    float totalAmount;

public: //constructor
    Buyer() : totalAmount(0.0) {}

    void menu(ProductList& list) override {
        int choice;
        while (true) {
            cout << "\nBUYER'S MENU\n1. Search Product\n2. Place Order\n3. View Cart\n4. Rate Product\n5. Display Products\n6. Return to the Main menu\nChoice: ";
            cin >> choice;

            // Input validation for choice
            if (cin.fail()) {
                cin.clear(); // Clear the error state
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the invalid input
                cout << "\nInvalid choice! Please enter a number." << endl;
                continue; // Restart the loop
            }

            switch (choice) {
                case 1:
                    searchProduct(list);
                    break;
                case 2:
                    placeOrder(list);
                    break;
                case 3:
                    viewCart();
                    break;
                case 4:
                    rateProduct(list);
                    break;
                case 5: 
                    list.displayProducts();
                    break;
                case 6:
                    return;
                default:
                    cout << "\nInvalid choice!";
            }
        }
    }

    void searchProduct(const ProductList& list) { // search products from list
        string name;
        cout << "Enter product name to search: ";
        cin >> name;

        ProductNode* temp = list.getHead();
        bool found = false; //Flag to track if any product matching the search was found.
        cout << "\nSearch Results:\n";
        cout << "Code\tName\tPrice\tDiscount\tStock\n";
        while (temp != NULL) {
            if (temp->data.getName() == name) {
                cout << temp->data.getCode() << "\t" << temp->data.getName()
                     << "\t" << temp->data.getPrice() << "\t" << temp->data.getDiscount()
                     << "%\t" << temp->data.getStock() << "\n";
                found = true; //Sets the flag to true if a product is found.
            }
            temp = temp->next;
        }
        if (!found) {
            cout << "No products found with the name: " << name << "\n";
        }
    }

    void placeOrder(ProductList& list) {
        int code, quantity;
        float total = 0.0;
        ProductNode* temp = list.getHead();

        while (true) {
            cout << "\nEnter product code (or -1 to stop);p ";
            cin >> code;
            if (code == -1) break;
            cout << "Enter quantity: ";
            cin >> quantity;

            // Input validation
            if (cin.fail() || quantity <= 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid quantity. Please enter a positive value." << endl;
                continue;
            }
     // product selection and stock validation
            temp = list.getHead(); // Reset temp to head for each product code input
            while (temp != NULL) {
                if (temp->data.getCode() == code) {
                    if (quantity <= temp->data.getStock()) { //Checks if there is enough stock.
                        cart.push_back(temp->data); //Adds the selected product to the cart.
                        totalAmount += quantity * temp->data.getPrice();
                        temp->data.updateStock(quantity); // Update stock
                        cout << "Product added to cart.\n";
                    } else {
                        cout << "Not enough stock available.\n";
                    }
                    break; // Exit the inner loop once the product is found
                }
                temp = temp->next;
            }
        }
        cout << "\nTotal Amount: rupees" << totalAmount << "\n";
    }

    void viewCart() const {
        cout << "\n Products in your Cart:\n";
        cout << "Code\tName\tPrice\tQuantity\n";
        for (const auto& product : cart) {
            cout << product.getCode() << "\t" << product.getName()
                 << "\t" << product.getPrice() << "\t" << 1 << "\n";  //assume quantity as 1
        }
        cout << "\nTotal Amount in Cart: rupees" << totalAmount << "\n";
    }

    void rateProduct(const ProductList& list) { //rate your products here
        int productCode;
        float rating;
        cout << "Enter product code to rate: ";
        cin >> productCode;
        cout << "Enter rating (1 to 10): ";
        cin >> rating;

        // Input validation
        if (cin.fail() || rating < 1 || rating > 10) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid rating:( Please enter a number between 1 and 10." << endl;
            return;
        }

        ProductNode* temp = list.getHead();
        while (temp != NULL) {
            if (temp->data.getCode() == productCode) {
                temp->data.setRating(rating);  // Set product rating
                cout << "Product rated successfully:)\n";
                return;
            }
            temp = temp->next;
        }
        cout << "Product not found:(\n";
    }
};
// main shopping class starts from here
class Shopping {
private:
    ProductList productList; //This holds all the products available in the store.
    User* user; 
	//a pointer to user(admin or buyer) used to dynamically allocate different types of user objects.
public: //constrctor
    Shopping() : user(NULL) {} //no users login yet
    void menu() {
        int choice;
        while (true) {
            cout << "\n\t\t\t\t\t <<< WELCOME TO ASA STORE >>>\n\n---------------\n   MAIN MENU \n---------------\n1. Administrator\n2. Buyer\n3. Exit\n\n Please enter your Choice here: ";
            cin >> choice;

            // Input validation for choice
            if (cin.fail()) {
                cin.clear(); // Clear the error state
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignores any extra characters in the input buffer.
                cout << "\nInvalid choice! Please enter a number." << endl;
                continue; // Restart the loop
            }

            if (choice == 3)
			 break;

            if (choice == 1) { // Administrator Login handling 
                user = new Administrator();
                string username, password;
                cout << "please enter username and password: ";
                cin >> username >> password;
                if (user->login(username, password)) {
                    user->menu(productList);
                } else {
                    cout << "Invalid username or password, Access denied. \n\t\t Plaese try again:)" << endl;
                }
            } else if (choice == 2) {
                user = new Buyer();
                // Removed username and password for Buyer
                user->menu(productList);
            } else {
                cout << "\nInvalid choice!";
            }
            delete user; //free the memory allocated for the Administrator or Buyer.
        }
    }
};
// main menu starts from here:)
int main() {
	// visual setup
	 system("COLOR 60"); // Changes the console background and text colors 
	 system("TITLE MY ONLINE STORE SYSTEM"); //Sets the title of the console window
    Shopping shoppingSystem;
    shoppingSystem.menu();
    return 0;
}


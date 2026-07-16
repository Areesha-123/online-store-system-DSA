# 🛒 ASA Store – Online Shopping Management System

A console-based **Online Shopping Management System** developed in **C++** using Object-Oriented Programming (OOP), Linked Lists, File Handling, and STL. The application simulates an online shopping platform where administrators manage products and buyers can browse, search, purchase, and rate products.

---

# 📖 Overview

The **ASA Store** is a menu-driven shopping management application designed to demonstrate core programming concepts including:

* Object-Oriented Programming (OOP)
* Linked Lists
* File Handling
* Dynamic Memory Allocation
* Input Validation
* Polymorphism
* Inheritance
* Encapsulation
* STL (Vector)
* Console-based User Interface

The system supports two user roles:

* **Administrator**
* **Buyer**

Product information is automatically saved to a text file, allowing data persistence between program executions.

---

# ✨ Features

## 👨‍💼 Administrator

* Secure administrator login
* Add new products
* Edit existing products
* Delete products
* Display all products
* Clear complete product inventory
* Automatic product data saving

---

## 🛍 Buyer

* Search products by name
* Browse available products
* Place orders
* Shopping cart
* Product rating system
* Stock availability checking
* Automatic stock updates
* Total bill calculation

---

# 🚀 Technologies Used

| Technology                  | Purpose                   |
| --------------------------- | ------------------------- |
| C++                         | Programming Language      |
| Object-Oriented Programming | Software Design           |
| STL Vector                  | Shopping Cart             |
| Linked List                 | Product Storage           |
| File Handling               | Persistent Storage        |
| Dynamic Memory              | Runtime Object Management |
| Console Application         | User Interface            |

---

# 📂 Project Structure

```text
ASA-Store/
│
├── main.cpp
├── products.txt
├── README.md
```

---

# 🏗 System Architecture

```text
                User
                  │
      ┌───────────┴───────────┐
      │                       │
Administrator             Buyer
      │                       │
      ▼                       ▼
 Product Management     Shopping Operations
      │                       │
      └───────────┬───────────┘
                  ▼
            Product List
                  │
          Linked List Storage
                  │
                  ▼
           products.txt File
```

---

# 🧩 Main Classes

## Product

Stores product information:

* Product Code
* Product Name
* Price
* Discount
* Stock

Functions include:

* Getters
* Update product details
* Update stock
* Rating function

---

## ProductNode

Represents a node in the linked list.

Contains:

* Product object
* Pointer to next node

---

## ProductList

Manages the complete inventory.

Functions:

* Add Product
* Edit Product
* Delete Product
* Display Products
* Load Products from File
* Save Products to File
* Clear Product List

---

## User (Abstract Class)

Base class for all users.

Functions:

* Login
* Menu (Pure Virtual Function)

---

## Administrator

Derived from User.

Responsibilities:

* Inventory management
* Product maintenance
* Administrator authentication

---

## Buyer

Derived from User.

Responsibilities:

* Search products
* Purchase products
* Manage shopping cart
* Rate products

---

## Shopping

Main controller of the application.

Responsible for:

* Main menu
* User authentication
* Role selection
* Program flow

---

# 🔐 Administrator Login

```text
Username : ASAstore
Password : 12345
```

---

# 📦 Product Information

Each product contains:

* Product Code
* Product Name
* Price
* Discount
* Available Stock

---

# 💾 File Handling

The application automatically stores product information inside:

```text
products.txt
```

Every modification is saved immediately.

Stored operations include:

* Product Addition
* Product Editing
* Product Deletion
* Stock Updates
* Inventory Clearing

---

# 🛒 Shopping Workflow

```text
Start Program
      │
      ▼
Main Menu
      │
      ├───────────────┐
      ▼               ▼
 Administrator      Buyer
      │               │
      ▼               ▼
 Manage Products   Search Products
                        │
                        ▼
                  Place Order
                        │
                        ▼
                  Shopping Cart
                        │
                        ▼
                Stock Updated
                        │
                        ▼
                  Display Total
```

---

# 📚 Concepts Implemented

* Object-Oriented Programming (OOP)
* Inheritance
* Encapsulation
* Polymorphism
* Abstract Classes
* Dynamic Memory Allocation
* Linked Lists
* File Handling
* Input Validation
* STL Vector
* Console Menu System

---

# ⚙️ How to Run

## Clone Repository

```bash
git clone https://github.com/your-username/ASA-Store.git
```

## Compile

Using g++:

```bash
g++ main.cpp -o ASAStore
```

## Run

Windows

```bash
ASAStore.exe
```

Linux / macOS

```bash
./ASAStore
```

---

# 📸 Sample Console

```text
<<< WELCOME TO ASA STORE >>>

1. Administrator
2. Buyer
3. Exit

Enter Choice:
```

---

# 🎯 Learning Outcomes

This project demonstrates practical implementation of:

* Object-Oriented Programming
* Data Structures
* Linked Lists
* File Management
* User Authentication
* Shopping Cart Logic
* Inventory Management
* Runtime Memory Management
* Modular Programming

---

# 🔮 Future Improvements

* GUI using Qt or Java Swing
* MySQL/SQLite database integration
* Customer registration and login
* Multiple administrator accounts
* Product categories
* Order history
* Sales reports
* Invoice generation
* Payment gateway integration
* Product images
* Product reviews
* Discount coupons
* Search by category
* Sorting and filtering
* Binary Search Tree or Hash Map for faster product search

---

# 👩‍💻 Author

**Areesha Raheel**

**BS Information Technology**
Riphah International University

**GitHub:** https://github.com/Areesha-123

---

# 📄 License

This project is created for educational purposes as part of academic coursework.

Feel free to fork, improve, and contribute to the project.

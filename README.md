
# Bank System V2 (C++)

Console-based **Bank Management System** in C++ with **client management, transactions, and file storage**.  
This project is an enhanced version of a previous C++ bank system, allowing you to manage clients, perform deposit/withdraw operations, and keep track of total balances.

---

## Features

- **Client Management**  
  - Add new clients  
  - Update existing clients  
  - Delete clients  
  - Find clients by account number  

- **Transactions Menu**  
  - Deposit money  
  - Withdraw money (with balance validation)  
  - Show total balances of all clients  

- **File-Based Storage**  
  - All client data is stored in `Clients.txt`  
  - Automatic loading and saving of client data  

---

## Purpose

This project is designed to improve skills in **C++ programming**, **file handling**, and **console-based application design**.  
It builds upon a previous version by adding better client management and transaction handling.

---

## How to Run

1. Clone or download the repository.  
2. Make sure `Clients.txt` exists in the same folder as the executable.  
3. Compile the project using a C++ compiler (e.g., g++, Visual Studio).  
4. Run the executable and navigate through the **Main Menu**.  

---

## Sample Menu

**Main Menu:**  
[1] Show Client List  
[2] Add New Client  
[3] Delete Client  
[4] Update Client Info  
[5] Find Client  
[6] Transactions  
[7] Exit  

**Transactions Menu:**  
[1] Deposit  
[2] Withdraw  
[3] Total Balances  
[4] Main Menu  

---

## File Format (`Clients.txt`)

Each client is stored in the following format:  
AccountNumber#//#PinCode#//#Name#//#Phone#//#AccountBalance

Example:  
A150#//#1234#//#Abdulrahman Ramadan#//#01128663647#//#111.000000


---

## Author

**Abdulrahman Ramadan** – Updated version of the C++ Bank System with enhanced features and file management.

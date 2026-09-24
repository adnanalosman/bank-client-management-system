Bank Client Management System (C++)

A console-based Bank Client Management System written in C++. It lets you manage client accounts (add, update, delete, search) and perform basic banking transactions (deposit, withdraw, view total balances), with data persisted to a local text file.

**Features**
Show Clients List — display all registered clients in a formatted table
Add New Client — create a new account (with duplicate-ID protection)
Delete Client — remove a client after confirmation
Update Client — edit PIN, name, phone, and balance
Find Client — search for a client by account ID
Transactions Menu
Deposit funds into an account
Withdraw funds (with balance validation)
View total balances across all clients
💾 Persistent Storage — all data is saved to and loaded from a local text file
🗂️ Data Storage

Client records are stored as pipe-delimited (|) lines in a text file:

AccountID|PIN|FullName|Phone|Balance

By default, the file path is hardcoded in the source code:

cpp
const string Path = "D:\\DataBase.txt";

⚠️ Note: This path is Windows-specific and hardcoded. If you run the project on a different drive or OS, update the Path constant before building, or consider refactoring it to a relative path (see Possible Improvements).

🛠️ Requirements
A C++ compiler supporting C++11 or later (e.g., MSVC / Visual Studio, MinGW g++)
Windows OS — the program uses system("cls") and system("pause>0"), which are Windows-specific console commands
**Getting Started**
Option 1: Visual Studio
Open Visual Studio and create a new Empty C++ Console Project.
Add the source file (e.g., main.cpp) to the project.
Build the solution (Ctrl+Shift+B) and run (Ctrl+F5).
Option 2: Command Line (MinGW / g++)
bash
g++ -std=c++11 -o BankSystem main.cpp
BankSystem.exe
**Usage**

On launch, the program loads existing data (if any) and shows the main menu:

==========================================
        Main Menu
==========================================
    [1] Show Clients List
    [2] Add New Client
    [3] Delete Client
    [4] Update Client
    [5] Find Client
    [6] Transactions
    [7] Exit System
==========================================

Enter a number from 1–7 to navigate. The Transactions menu additionally offers deposit, withdrawal, and total-balance views.

📁 Project Structure
.
├── main.cpp        # Full application source code
└── README.md       # Project documentation
🧭 Possible Improvements
 Make the data file path configurable (e.g., relative path or command-line argument) instead of hardcoded
 Add cross-platform support (replace system("cls") / system("pause>0") with portable alternatives)
 Add input validation (e.g., non-numeric balance/PIN input, empty fields)
 Mask or encrypt the PIN instead of storing it in plain text
 Split the code into multiple files/headers (separation of concerns)
 Add unit tests
 Replace the raw text-file storage with a lightweight database (e.g., SQLite)
📄 License

This project is open source. Consider adding a license (e.g., MIT License) to clarify how others may use your code — add a LICENSE file to the repository root.

👤 Author
Adnan Osman

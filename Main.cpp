#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

const string Path = "D:\\DataBase.txt";
const string delim = "|";

void MainList() {
	system("cls");
	cout << "==========================================\n"
		<< "\t\tMain Menu\n"
		<< "==========================================" << endl
		<< "\t[1] Show Clients List\n"
		<< "\t[2] Add New Client\n"
		<< "\t[3] Delete Client\n"
		<< "\t[4] Update Client\n"
		<< "\t[5] Find Client\n"
		<< "\t[6] Transactions\n"
		<< "\t[7] Exit System\n"
		<< "==========================================\n\n"
		<< "Please type your choice [1 to 7] "
		<< endl;
}

struct stClient {
	string Account_id;
	string PIN;
	string FullName;
	string Phone;
	double Balance;
};

vector <stClient> GetDataBase(string FilePath = Path) {
	vector <stClient> Output;
	fstream File;

	File.open(FilePath, ios::in);
	if (File.is_open())
	{
		string line;
		while (getline(File, line)) {
			size_t pos = 0; short poscount = 0;
			while ((pos = line.find(delim, pos)) != std::string::npos) {
				poscount++; pos += delim.length();
			}
			while ((pos = line.find(delim)) != std::string::npos) {
				if (poscount == 4) {
					stClient Record;
					Record.Account_id = line.substr(0, pos);
					line.erase(0, pos + delim.length());

					pos = line.find(delim);
					Record.PIN = line.substr(0, pos);
					line.erase(0, pos + delim.length());

					pos = line.find(delim);
					Record.FullName = line.substr(0, pos);
					line.erase(0, pos + delim.length());

					pos = line.find(delim);
					Record.Phone = line.substr(0, pos);
					line.erase(0, pos + delim.length());

					Record.Balance = stod(line);
					Output.push_back(Record);
				}
				else
				{
					break;
				}
			}
		}
		File.close();
	}
	return Output;
}

void PrintRecord(const stClient& Input) {
	cout << "| " << setw(18) << left << Input.Account_id
		<< "| " << setw(16) << left << Input.PIN
		<< "| " << setw(24) << left << Input.FullName
		<< "| " << setw(18) << left << Input.Phone
		<< "| " << setw(18) << left << Input.Balance
		<< endl;
}

void PrintClientsList(vector <stClient>& DataBase) {
	cout << "\t\t\t\t\tClients List (" << DataBase.size() << ") Client(s)" << endl;
	cout << "ــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــ" << endl;
	cout << "| " << setw(18) << left << "Account Number"
		<< "| " << setw(16) << left << "PIN"
		<< "| " << setw(24) << left << "Client Name"
		<< "| " << setw(18) << left << "Phone Number"
		<< "| " << setw(18) << left << "Current Balance (USD)\n"
		<< "ــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــ"
		<< endl;
	for (stClient& Record : DataBase) {
		PrintRecord(Record);
	}
}

bool Is_Record(vector <stClient>& DataBase, string& Account_id) {
	for (stClient& line : DataBase) {
		if (line.Account_id == Account_id)
		{
			cout << "This Account Already Existed!" << endl;
			return true;
		}
	}
	return false;
}

void AddRecord(vector <stClient>& DataBase) {
	cout << "======================================\n"
		<< "\tAdding A New Record\n"
		<< "======================================"
		<< endl;
	bool Addmore = 1;
	while (Addmore) {
		stClient Record;
		do
		{
			cout << "\nPlease enter account id: "; getline(cin >> ws, Record.Account_id);
		} while (Is_Record(DataBase, Record.Account_id));

		cout << "PIN code: "; getline(cin, Record.PIN);
		cout << "Client Name: "; getline(cin, Record.FullName);
		cout << "Phone Number: "; getline(cin, Record.Phone);
		cout << "Balance: "; cin >> Record.Balance;
		DataBase.push_back(Record);
		cout << "Record Added Successfully!";
		cout << "Add more Records [Y | N] "; char temp; cin >> temp;
		if (temp == 'Y' || temp == 'y') {
			Addmore = 1;
		}
		else
		{
			Addmore = 0;
		}
	}

}

void DeleteRecord(vector <stClient>& DataBase) {
	cout << "=================================\n"
		<< "\tDelete A Record\n"
		<< "================================="
		<< endl;
	string Account_Id_Delete;
	cout << "\nPlease Enter Account id to delete: "; getline(cin >> ws, Account_Id_Delete);
	bool Found = 0;
	while (!Found) {
		for (stClient& line : DataBase) {
			Found = line.Account_id == Account_Id_Delete;
			if (Found)
			{
				cout << "\nAccount Found!" << endl;
				cout << "\n| " << setw(18) << left << "Account Number"
					<< "| " << setw(16) << left << "PIN"
					<< "| " << setw(24) << left << "Client Name"
					<< "| " << setw(18) << left << "Phone Number"
					<< "| " << setw(18) << left << "Current Balance (USD)\n"
					<< "ــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــ"
					<< endl;
				PrintRecord(line);
				cout << "\nSure to delete? Y|N" << endl; char Yes; cin >> Yes;
				if (Yes == 'Y' || Yes == 'y') {
					swap(line, DataBase[DataBase.size() - 1]);
					DataBase.pop_back();
					cout << "Record (" << Account_Id_Delete << ") deleted Successfully!" << endl;
					return;
				}
				else return;
			}
		}
		cout << "Record not found, please check again! or press 0 to cancel" << endl;
		string User_Response; cin >> User_Response;
		if (User_Response == "0")
		{
			return;
		}
		else Account_Id_Delete = User_Response;
	}
}

void UpdateRecord(vector <stClient>& DataBase) {
	cout << "=========================================\n"
		<< "\tUpdate An Existed Record\n"
		<< "========================================="
		<< endl;
	string Account_Id_Update;
	cout << "\nPlease Enter Account id to update: "; getline(cin >> ws, Account_Id_Update);
	bool Found = 0;
	while (!Found) {
		for (size_t i = 0; i < DataBase.size(); i++) {
			Found = DataBase[i].Account_id == Account_Id_Update;
			if (Found)
			{
				cout << "\nAccount Found!" << endl;
				cout << "\n| " << setw(18) << left << "Account Number"
					<< "| " << setw(16) << left << "PIN"
					<< "| " << setw(24) << left << "Client Name"
					<< "| " << setw(18) << left << "Phone Number"
					<< "| " << setw(18) << left << "Current Balance (USD)\n"
					<< "ــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــ"
					<< endl;
				PrintRecord(DataBase[i]);
				cout << "\nUpdate Details: " << endl;
				cout << "ــــــــــــــ" << endl;
				cout << "New PIN: "; getline(cin >> ws, DataBase[i].PIN);
				cout << "Client Name: "; getline(cin, DataBase[i].FullName);
				cout << "Phone Number: "; getline(cin, DataBase[i].Phone);
				cout << "Current Balance: "; cin >> DataBase[i].Balance;
				cout << "\nRecord Updated Successfully!";
				return;
			}
		}
		cout << "Record not found, please check again! or press 0 to cancel" << endl;
		string User_Response; cin >> User_Response;
		if (User_Response == "0")
		{
			return;
		}
		else Account_Id_Update = User_Response;
	}
}

void FindRecord(vector <stClient>& DataBase) {
	cout << "==============================\n"
		<< "\tRecord Search\n"
		<< "=============================="
		<< endl;
	string Account_Id;
	cout << "\nPlease Enter Account id to search: "; getline(cin >> ws, Account_Id);
	bool Found = 0;
	while (!Found) {
		for (size_t i = 0; i < DataBase.size(); i++) {
			Found = DataBase[i].Account_id == Account_Id;
			if (Found)
			{
				cout << "\nAccount Found!" << endl;
				cout << "\n| " << setw(18) << left << "Account Number"
					<< "| " << setw(16) << left << "PIN"
					<< "| " << setw(24) << left << "Client Name"
					<< "| " << setw(18) << left << "Phone Number"
					<< "| " << setw(18) << left << "Current Balance (USD)\n"
					<< "ــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــ"
					<< endl;
				PrintRecord(DataBase[i]);
				cout << endl;
				return;
			}
		}
		cout << "Record not found, please check again! or press 0 to cancel" << endl;
		string User_Response; cin >> User_Response;
		if (User_Response == "0")
		{
			return;
		}
		else Account_Id = User_Response;
	}
}

void UpdateDataBase(vector <stClient>& DataBase) {
	fstream File;
	File.open(Path, ios::out);
	if (File.is_open())
	{
		for (stClient& line : DataBase) {
			File << line.Account_id << delim
				<< line.PIN << delim
				<< line.FullName << delim
				<< line.Phone << delim
				<< line.Balance << endl;
		}
		File.close();
	}
}

enum MMenu { ClientsList = 1, NewClient, DeleteClient, UpdateClient, FindClient, Transactions, Exit = 7 };

void SystemTrans(short& UserResponse) {
	cout << "Press any key to return to Main Menu...";
	system("pause>0");
	system("cls");
	MainList();
	cin >> UserResponse; system("cls");
}

/// <summary>
/// V2 Trnasactions Extension
/// </summary>
/// <param name="Tansactions addition"></param>

void TansactionsList() {
	system("cls");
	cout << "==========================================\n"
		<< "\t\tTansactions Menu\n"
		<< "==========================================" << endl
		<< "\t[1] Deposit\n"
		<< "\t[2] Withdraw\n"
		<< "\t[3] Total Balances\n"
		<< "\t[4] Main Menu\n"
		<< "==========================================\n\n"
		<< "Please type your choice [1 to 4] "
		<< endl;
}

void SystemTransMini(short& UserResponse2) {
	cout << "Press any key to return to Main Menu...";
	system("pause>0");
	system("cls");
	TansactionsList();
	cin >> UserResponse2; system("cls");
}

enum TansactionsChoices { Deposit = 1, Withdrawt, Total_Balances, Main };

void DepositMenu(vector <stClient>& DataBase) {
	cout << "==============================\n"
		<< "         Deposit Menu\n"
		<< "=============================="
		<< endl;
	string Account_Id;
	cout << "\nPlease Enter Account id: "; getline(cin >> ws, Account_Id);
	bool Found = 0;
	while (!Found) {
		for (size_t i = 0; i < DataBase.size(); i++) {
			Found = DataBase[i].Account_id == Account_Id;
			if (Found)
			{
				cout << "\nAccount Found!" << endl;
				cout << "\n| " << setw(18) << left << "Account Number"
					<< "| " << setw(16) << left << "PIN"
					<< "| " << setw(24) << left << "Client Name"
					<< "| " << setw(18) << left << "Phone Number"
					<< "| " << setw(18) << left << "Current Balance (USD)\n"
					<< "ــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــ"
					<< endl;
				PrintRecord(DataBase[i]);
				cout << endl;
				double depoAm = 0;
				cout << "Deposit ammount: "; cin >> depoAm;
				DataBase[i].Balance += depoAm;
				cout << endl << "Updated Successfully!" << endl;
				return;
			}
		}
		cout << "Record not found, please check again! or press 0 to cancel" << endl;
		string User_Response; cin >> User_Response;
		if (User_Response == "0")
		{
			return;
		}
		else Account_Id = User_Response;
	}
}


void WithdrawtMenu(vector <stClient>& DataBase) {
	cout << "==============================\n"
		<< "        Withdrawt Menu\n"
		<< "=============================="
		<< endl;
	string Account_Id;
	cout << "\nPlease Enter Account id: "; getline(cin >> ws, Account_Id);
	bool Found = 0;
	while (!Found) {
		for (size_t i = 0; i < DataBase.size(); i++) {
			Found = DataBase[i].Account_id == Account_Id;
			if (Found)
			{
				cout << "\nAccount Found!" << endl;
				cout << "\n| " << setw(18) << left << "Account Number"
					<< "| " << setw(16) << left << "PIN"
					<< "| " << setw(24) << left << "Client Name"
					<< "| " << setw(18) << left << "Phone Number"
					<< "| " << setw(18) << left << "Current Balance (USD)\n"
					<< "ــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــ"
					<< endl;
				PrintRecord(DataBase[i]);
				cout << endl;
				double witAm = 0;
				do
				{
					cout << "Withdrawt ammount: "; cin >> witAm;
					if (witAm > DataBase[i].Balance)
					{
						cout << "Ammount exceeds the balance, you can withdraw up to " << DataBase[i].Balance << " USD" << endl;
					}
				} while (witAm > DataBase[i].Balance);
				DataBase[i].Balance -= witAm;
				cout << endl << "Updated Successfully!" << endl;
				return;
			}
		}
		cout << "Record not found, please check again! or press 0 to cancel" << endl;
		string User_Response; cin >> User_Response;
		if (User_Response == "0")
		{
			return;
		}
		else Account_Id = User_Response;
	}
}

void PrintBalance(const stClient& Input) {
	cout << "| " << setw(18) << left << Input.Account_id
		<< "| " << setw(30) << left << Input.FullName
		<< "| " << setw(18) << left << Input.Balance
		<< endl;
}

void TotalBalancesMenu(vector <stClient>& DataBase) {
	cout << "\t\t\tBalances List (" << DataBase.size() << ") Client(s)" << endl;
	cout << "ـــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــ" << endl;
	cout << "| " << setw(18) << left << "Account Number"
		<< "| " << setw(30) << left << "Client Name"
		<< "| " << setw(18) << left << "Current Balance (USD)\n"
		<< "ـــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــ"
		<< endl;
	double TotalBalances = 0;
	for (stClient& Record : DataBase) {
		PrintBalance(Record);
		TotalBalances += Record.Balance;
	}
	cout << "ـــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــ" << endl;
	cout << "Total Balances\t\t\t\t\t      " << TotalBalances << " USD\n" << endl;
}

void MainMenu(vector <stClient>& DataBase);

void TransactionsMenu(vector <stClient>& DataBase) {
	short UserResponse2;
	TansactionsList();
	cin >> UserResponse2; system("cls");
	while (UserResponse2 != TansactionsChoices::Main) {
		switch (UserResponse2) {
			case TansactionsChoices::Deposit:
				UserResponse2 = TansactionsChoices::Main;
				DepositMenu(DataBase);
				UpdateDataBase(DataBase);
				SystemTransMini(UserResponse2);
				break;

			case TansactionsChoices::Withdrawt:
				WithdrawtMenu(DataBase);
				UpdateDataBase(DataBase);
				SystemTransMini(UserResponse2);
				break;

			case TansactionsChoices::Total_Balances:
				TotalBalancesMenu(DataBase);
				SystemTransMini(UserResponse2);
				break;
			default:
				SystemTransMini(UserResponse2);
		}
	}
	return;
}

void CloseScreen() {
	system("cls");
	cout << "closing system...." << endl;
}

void MainMenu(vector <stClient>& DataBase) {
	short UserResponse;
	MainList();
	cin >> UserResponse; system("cls");
	while (UserResponse != MMenu::Exit) {
		switch (UserResponse) {
		case MMenu::ClientsList:
			PrintClientsList(DataBase);
			SystemTrans(UserResponse);
			break;

		case MMenu::NewClient:
			AddRecord(DataBase);
			UpdateDataBase(DataBase);
			SystemTrans(UserResponse);
			break;

		case MMenu::DeleteClient:
			DeleteRecord(DataBase);
			UpdateDataBase(DataBase);
			SystemTrans(UserResponse);
			break;

		case MMenu::UpdateClient:
			UpdateRecord(DataBase);
			UpdateDataBase(DataBase);
			SystemTrans(UserResponse);
			break;

		case MMenu::FindClient:
			FindRecord(DataBase);
			SystemTrans(UserResponse);
			break;

		case MMenu::Transactions:
			TransactionsMenu(DataBase);
			UserResponse = 7;
			MainMenu(DataBase);
			break;
		}
	}
	system("cls");
	cout << "closing system....\nPress any Key to end..." << endl;
	return;
}

int main() {

	vector <stClient> StoredData;
	StoredData = GetDataBase();

	MainMenu(StoredData);

	return 0;
}

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;
const string ClientsFileName = "Clients.txt";
void ShowMainMenue();
void ShowTransactionsMenue();
struct sClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool MarkForDelete = false;
};
void printClientRecord(sClient Client) {
	cout << "| " << left << setw(15) << Client.AccountNumber;
	cout << "| " << left << setw(10) << Client.PinCode;
	cout << "| " << left << setw(40) << Client.Name;
	cout << "| " << left << setw(12) << Client.Phone;
	cout << "| " << left << setw(12) << Client.AccountBalance;
}
void PrintAllClientsData(vector <sClient> vClients) {
	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
	cout << "\n___________________________________________________________________________________________________\n\n";
	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n___________________________________________________________________________________________________\n\n";
	if (vClients.size() == 0)
		cout << "\t\t\t\tNo Clients Available In the System!";
	else
		for (sClient Client : vClients) {
			printClientRecord(Client);
			cout << endl;
	}
	cout << "\n___________________________________________________________________________________________________\n";
}
vector<string> SplitString(string S1, string delim) {
	vector<string> vString;
	short pos = 0;
	string sWord;
	while ((pos = S1.find(delim)) != string::npos)
	{
		sWord = S1.substr(0, pos);
		if (sWord != "")
		{
			vString.push_back(sWord);
		}
		S1.erase(0, pos + delim.length());
	}
	if (S1 != "")
	{
		vString.push_back(S1);
	}
	return vString;
}
sClient convertLineToRecord(string line, string Seperator = "#//#") {
	vector<string>ClientData = SplitString(line, Seperator);
	sClient Client;
	Client.AccountNumber = ClientData[0];
	Client.PinCode = ClientData[1];
	Client.Name = ClientData[2];
	Client.Phone = ClientData[3];
	Client.AccountBalance = stod(ClientData[4]);
	return Client;
}
vector<sClient>LoadCleintsDataFromFile(string FileName) {
	vector <sClient> vClients;
	fstream ClientFile;
	ClientFile.open(FileName, ios::in);
	string line;
	sClient Client;
	if (ClientFile.is_open()) {
		while (getline(ClientFile, line)) {
			Client = convertLineToRecord(line);
			vClients.push_back(Client);

		}
		ClientFile.close();
	}
	return vClients;
}
void printDataClient(sClient Client) {
	cout << "\nThe following are the client details:\n";
	cout << "\n------------------------------------";
	cout << "\nAccount Number  = " << Client.AccountNumber;
	cout << "\nPin Code        = " << Client.PinCode;
	cout << "\nName            = " << Client.Name;
	cout << "\nPhone           = " << Client.Phone;
	cout << fixed << "\nAccount Balance = " << Client.AccountBalance;
	cout << "\n------------------------------------\n";
}
string ConvertRecordToLine(sClient Client, string Seperator = "#//#") {
	string stClientRecord = "";
	stClientRecord += Client.AccountNumber + Seperator;
	stClientRecord += Client.PinCode + Seperator;
	stClientRecord += Client.Name + Seperator;
	stClientRecord += Client.Phone + Seperator;
	stClientRecord += to_string(Client.AccountBalance);

	return stClientRecord;
}
vector <sClient> SaveCleintsDataToFile(string FileName, vector <sClient>& vClients)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out);
	string DataLine;
	if (MyFile.is_open())
	{
		for (sClient& C : vClients)
		{
			if (C.MarkForDelete == false)
			{
				DataLine = ConvertRecordToLine(C);
				MyFile << DataLine << endl;
			}
		}
		MyFile.close();
	}
	return vClients;
}
bool FindClientByAccountNumber(string AccountNumber, vector<sClient> vClients, sClient& Client) {
	for (sClient C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}
	}
	return false;
}
bool ClientExistsByAccountNumber(string AccountNumber, string FileName) {

	fstream MyFile;
	MyFile.open(FileName, ios::in);
	if (MyFile.is_open())
	{
		string Line;
		sClient Client;
		while (getline(MyFile, Line))
		{
			Client = convertLineToRecord(Line);
			if (Client.AccountNumber == AccountNumber)
			{
				MyFile.close();
				return true;
			}

		}
		MyFile.close();
	}

	return false;
}
sClient ReadNewClient() {
	sClient Client;
	cout << "Enter Account Number ? ";
	getline(cin >> ws, Client.AccountNumber);
	while (ClientExistsByAccountNumber(Client.AccountNumber, ClientsFileName)) {
		cout << "\nClient With [" << Client.AccountNumber << "] Already Exists, Enter Another Account Number ? ";
		getline(cin >> ws, Client.AccountNumber);

	}
	cout << "Enter Pin Code ? ";
	getline(cin, Client.PinCode);
	cout << "Enter Name ? ";
	getline(cin, Client.Name);
	cout << "Enter Phone ? ";
	getline(cin, Client.Phone);
	cout << "Enter Account Balance ? ";
	cin >> Client.AccountBalance;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return Client;
}
void AddDataLineToFile(string FileName, string stDataLine)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out | ios::app);
	if (MyFile.is_open())
	{
		MyFile << stDataLine << endl;
		MyFile.close();
	}
}
void AddNewClient()
{
	sClient Client;
	Client = ReadNewClient();
	AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client));
}
void AddClients()
{
	char AddMore = 'Y';
	do
	{
		cout << "Adding New Client:\n\n";
		AddNewClient();
		cout << "\nClient Added Successfully, do you want to add more clients ? Y / N ? ";
		cin >> AddMore;
	} while (toupper(AddMore) == 'Y');
}
void ShowClientListScreen() {
	vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
	PrintAllClientsData(vClients);
}
void GoBackToMianMenue() {
	cout << "\n\nPress any key to go back to Main Menue...";
	system("pause>0");
	ShowMainMenue();
}
void GoBackToTransactionsMenue() {
	cout << "\n\nPress any key to go back to Transactions Menue...";
	system("pause>0");
	ShowTransactionsMenue();
}
void ShowAddNewClientScreen() {
	cout << "\n------------------------------------\n";
	cout << "\tAdd New Client \n";
	cout << "------------------------------------\n\n";
	AddClients();
}
bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{
	for (sClient& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			C.MarkForDelete = true;
			return true;
		}
	}
	return false;
}
bool DeleteClientByAccountNumber(string AccountNumber, vector<sClient>& vClients)
{
	sClient Client;
	char Answer = 'n';
	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		printDataClient(Client);
		cout << "\n\nAre you sure you want delete this client? y/n ? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
			SaveCleintsDataToFile(ClientsFileName, vClients);
			vClients = LoadCleintsDataFromFile(ClientsFileName);
			cout << "\n\nClient Deleted Successfully.";
			return true;
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber
			<< ") is Not Found!";
		return false;
	}
}
string ReadAccountNumber() {
	string AccountNumber = "";
	cout << "please Enter Account Number ? ";
	cin >> AccountNumber;
	return AccountNumber;
}
void ShowDeletClientScreen() {
	vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
	cout << "\n------------------------------------\n";
	cout << "\tDelet Client Screen  \n";
	cout << "------------------------------------\n\n";
	string AccountNumber = ReadAccountNumber();
	DeleteClientByAccountNumber(AccountNumber, vClients);

}
sClient ChangeClientRecord(string AccountNumber)
{
	sClient Client;
	Client.AccountNumber = AccountNumber;
	cout << "\n\nEnter PinCode? ";
	getline(cin >> ws, Client.PinCode);
	cout << "Enter Name? ";
	getline(cin, Client.Name);
	cout << "Enter Phone? ";
	getline(cin, Client.Phone);
	cout << "Enter AccountBalance? ";
	cin >> Client.AccountBalance;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return Client;
}
bool UpdateClientByAccountNumber(string AccountNumber, vector<sClient>& vClients) {

	sClient Client;
	char Answer = 'n';
	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		printDataClient(Client);
		cout << "\n\nAre you sure you want update this client? y/n? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			for (sClient& C : vClients) {
				if (C.AccountNumber == AccountNumber) {
					C = ChangeClientRecord(AccountNumber);
					break;
				}
			}
			SaveCleintsDataToFile(ClientsFileName, vClients);
			cout << "\n\nClient Updated Successfully.";
			return true;
		}
	}
	else {
		cout << "\nClient with Account Number (" << AccountNumber
			<< ") is Not Found!";
		return false;
	}
}
void ShowUpdateClienScreen() {
	cout << "\n------------------------------------\n";
	cout << "\tUpdate Clien Screen  \n";
	cout << "------------------------------------\n\n";
	vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
	string AccountNumber = ReadAccountNumber();
	UpdateClientByAccountNumber(AccountNumber, vClients);
}
void ShowFindClienScreen() {
	sClient Client;
	vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
	cout << "\n------------------------------------\n";
	cout << "\tFind Clien Screen  \n";
	cout << "------------------------------------\n\n";
	string AccountNumber = ReadAccountNumber();
	if (FindClientByAccountNumber(AccountNumber, vClients, Client)) {
		printDataClient(Client);
	}
	else {
		cout << "Client With Account Number [" << AccountNumber << "] is Not Found!";
	}
}
void ShowExitScreen() {
	cout << "\n------------------------------------\n";
	cout << "\tProgram Ends :-)  \n";
	cout << "------------------------------------\n\n";
}
double GetTotalBalances(vector <sClient> vClients) {
	double totalBalance = 0;
	for (sClient& C : vClients) {
		totalBalance += C.AccountBalance;
	}
	return totalBalance;
}
void PrintClientsBalances(vector <sClient> vClients) {
	cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s).";
	cout << "\n___________________________________________________________________________________________________\n\n";
	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n___________________________________________________________________________________________________\n\n";
	for (sClient& Client : vClients) {
		cout << "| " << left << setw(15) << Client.AccountNumber;
		cout << "| " << left << setw(40) << Client.Name;
		cout << "| " << left << setw(12) << Client.AccountBalance;
		cout << endl;
	}
	cout << "\n___________________________________________________________________________________________________\n";

	cout << "\n\t\t\t\t\tTotal Balances = " << GetTotalBalances(vClients) << "\n";
}
short ReadMainMenueOption()
{
	cout << "Choose what do you want to do? [1 to 7]? ";
	short Choice = 0;
	cin >> Choice;
	return Choice;
}
short ReadTransactionsMenueOption()
{
	cout << "Choose what do you want to do? [1 to 4]? ";
	short Choice = 0;
	cin >> Choice;
	return Choice;
}
double ReadDepositAmount()
{
	double DepositAmount = 0;
	cout << "\nPlease enter deposit amount ? ";
	cin >> DepositAmount;
	return DepositAmount;
}
bool DepositBalanceToClientByAccountNumber(string AccountNumber,
	double Amount, vector <sClient>& vClients)
{
	char Answer = 'n';
	cout << "\n\nAre you sure you want perfrom this transaction? y / n ? ";
	cin >> Answer;
	if (Answer == 'y' || Answer == 'Y')
	{
		for (sClient& C : vClients)
		{
			if (C.AccountNumber == AccountNumber)
			{
				C.AccountBalance += Amount;
				SaveCleintsDataToFile(ClientsFileName, vClients);
				cout << "\n\nDone Successfully. New balance is: "
					<< C.AccountBalance;
				return true;
			}
		}
		return false;
	}
}

void ShowDeposit() {
	cout << "\n------------------------------------\n";
	cout << "\tDeposit Screen  \n";
	cout << "------------------------------------\n\n";
	sClient Client;
	vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
	string AccountNumber = ReadAccountNumber();
	while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		cout << "\nClient with [" << AccountNumber << "] does Not exist.\n\n";
		AccountNumber = ReadAccountNumber();
	}
	printDataClient(Client);
	double Amount = 0;
	cout << "\n\nPlease enter deposit amount ? ";
	cin >> Amount;
	DepositBalanceToClientByAccountNumber(AccountNumber, Amount, vClients);
}
void ShowWithdraw() {
	cout << "\n------------------------------------\n";
	cout << "\tWithdraw Screen  \n";
	cout << "------------------------------------\n\n";
	sClient Client;
	vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
	string AccountNumber = ReadAccountNumber();
	while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		cout << "\nClient with [" << AccountNumber << "] does Not exist.\n\n";
		AccountNumber = ReadAccountNumber();
	}
	printDataClient(Client);
	double Amount = 0;
	cout << "\n\nPlease enter deposit amount ? ";
	cin >> Amount;
	while (Amount > Client.AccountBalance)
	{
		cout << "\nAmount Exceeds the balance, you can withdraw upto : " << Client.AccountBalance << endl;
		cout << "Please enter another amount? ";
		cin >> Amount;
	}
	DepositBalanceToClientByAccountNumber(AccountNumber, Amount * -1, vClients);

}
void ShowTotalBalances() {
	vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
	PrintClientsBalances(vClients);
}
enum enTransactionsMenueOption {
	Deposit = 1,
	Withdraw = 2,
	TotalBalances = 3,
	MianMenue = 4
};
void PerformTransactionsMenueOption(enTransactionsMenueOption TransactionsMenueOption) {
	switch (TransactionsMenueOption)
	{
	case enTransactionsMenueOption::Deposit:
		system("cls");
		ShowDeposit();
		GoBackToTransactionsMenue();
		break;
	case enTransactionsMenueOption::Withdraw:
		system("cls");
		ShowWithdraw();
		GoBackToTransactionsMenue();
		break;
	case enTransactionsMenueOption::TotalBalances:
		system("cls");
		ShowTotalBalances();
		GoBackToTransactionsMenue();
		break;
	case enTransactionsMenueOption::MianMenue:
		ShowMainMenue();

	}
}
void ShowTransactionsMenue() {
	system("cls");
	cout << "===============================================\n";
	cout << "\t\Transactions Menue Screen \n";
	cout << "===============================================\n";
	cout << "\t[1] Deposit.   \n ";
	cout << "\t[2] Withdraw.     \n ";
	cout << "\t[3] Total Balances.       \n ";
	cout << "\t[4] Mian Menue. \n ";
	cout << "===============================================\n";
	PerformTransactionsMenueOption(enTransactionsMenueOption(ReadTransactionsMenueOption()));
}
enum enMainMenueOptions
{
	eListClients = 1,
	eAddNewClient = 2,
	eDeleteClient = 3,
	eUpdateClient = 4,
	eFindClient = 5,
	Transactions = 6,
	eExit = 7
};
void PerformMainMenueOption(enMainMenueOptions MainMenueOption) {
	switch (MainMenueOption)
	{
	case enMainMenueOptions::eListClients:
		system("cls");
		ShowClientListScreen();
		GoBackToMianMenue();
		break;
	case  enMainMenueOptions::eAddNewClient:
		system("cls");
		ShowAddNewClientScreen();
		GoBackToMianMenue();
		break;
	case  enMainMenueOptions::eDeleteClient:
		system("cls");
		ShowDeletClientScreen();
		GoBackToMianMenue();
		break;
	case  enMainMenueOptions::eUpdateClient:
		system("cls");
		ShowUpdateClienScreen();
		GoBackToMianMenue();
		break;
	case  enMainMenueOptions::eFindClient:
		system("cls");
		ShowFindClienScreen();
		GoBackToMianMenue();
		break;
	case  enMainMenueOptions::Transactions:
		system("cls");
		ShowTransactionsMenue();
		break;
	case  enMainMenueOptions::eExit:
		system("cls");
		ShowExitScreen();
		break;
	}
}
void ShowMainMenue() {
	system("cls");
	cout << "===============================================\n";
	cout << "\t\tMain Menue Screen \n";
	cout << "===============================================\n";
	cout << "\t[1] Show Client List.   \n ";
	cout << "\t[2] Add New Client.     \n ";
	cout << "\t[3] Delet Client.       \n ";
	cout << "\t[4] Update Client Info. \n ";
	cout << "\t[5] Find Client. \n ";
	cout << "\t[6] Transactions.\n ";
	cout << "\t[7] Exit.\n ";
	cout << "===============================================\n";
	PerformMainMenueOption(enMainMenueOptions(ReadMainMenueOption()));
}

int main() {
	ShowMainMenue();
	system("pause>0");
	return 0;
}

/*
* Student: Soukaina Salihi
* Course: CIT-237
*
*  This project involves writing a C++ program
*  to provide an interactive tool for the user
*  to manage the checking account
*/

#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <string>
#include <iostream> // Have Access to simple input and output
#include <ctime>    // Have access to the current date
#include <iomanip>	
using namespace std;


ofstream outputFile;

// Create class called BankAccount
class BankAccount
{
	// The attributes for this class
private:
	// Private attributes cannot be accessed directly. 
	string date;
	string description;
	int checkNum;
	double balance;
	double depAmount;
	double withdAmount;

	// Methodes for this class
public:
	// constructor to initialize BankAccount objects
	BankAccount();
	void setData(int, string, double, double, double);

	// Accessor methods (getters)
	int getCheckNum(void);
	string getDate(void);
	double getBalance(void);
	string getDescription(void);
	double getDepAmount(void);
	double getWithdAmount();
	void outputToFile(ofstream &, BankAccount);


	// Mutator methods (setters)
	void setDate(string dt);
	void setBalance(double);
	void setCheckNum(int);
	void setDescription(string);
};

// Constractor to initialize the data
BankAccount::BankAccount(){
	checkNum = 1;
	date = "";
	balance = 0.0;
	depAmount = 0.0;
	withdAmount = 0.0;
	description = "starting balance";
}
//Get check number if the user changes the default number
int BankAccount::getCheckNum(void)
{
	return checkNum;
}


string BankAccount::getDate(void)
{
	return date;
}
string BankAccount::getDescription(void)
{
	return description;
}

double BankAccount::getBalance(void)
{
	return balance;
}
double BankAccount::getDepAmount(void)
{
	return depAmount;
}
double BankAccount::getWithdAmount(void)
{
	return withdAmount;
}

void BankAccount::setDate(string st){
	date = st;
}
void BankAccount::setBalance(double bal){

	balance = bal;
}
void BankAccount::setCheckNum(int chk){

	checkNum = chk;
}

void BankAccount::setDescription(string trInfo){

	description = trInfo;
}

// Functions prototypes
void openOutputFile();
void setInitialBalance(BankAccount&, char);
void withdraw(BankAccount &, char);
void deposit(BankAccount &, char);
void writeCheck(BankAccount &);
string findCurrentDate();


void openOutputFile()
{
	string outputFileName;
	// Output file:  prompt for filename, open file for output.
	cout << "Enter name of output file: ";
	getline(cin, outputFileName);
	outputFile.open(outputFileName);


} // (end function openOutputFile)


/************************************************************
* setInitialBalance():				  	     *
* This funtion will set the balance of the account ask for   *
* transaction date, but if the user hits enter only, it will *
* show the current date.The description will be by           *
* default "starting balance". Output data and write it in    *
* a file if the user have already created one.		     *
*							     *
************************************************************/
void setInitialBalance(BankAccount &myAccount, char comand){
	string date;
	double AccountBalance;
	char c; // new line character 

	cout << "Enter the transaction date (default " << findCurrentDate() << " ): ";
	cin.get(c);

	if (c == '\n'){
		date = findCurrentDate();
		myAccount.setDate(date);
	}
	else
	{
		cin.putback(c); cin.clear();
		getline(cin, date);
		myAccount.setDate(date);
	}
	cout << "Enter starting balance : ";
	cin >> AccountBalance; cin.ignore(80, '\n');
	myAccount.setBalance(AccountBalance);

	cout << showpoint << setprecision(2) << fixed
		<< comand << "|" << myAccount.getDate() << "|" << myAccount.getDescription();
	cout << "|||" << myAccount.getBalance() << endl;
	if (outputFile){
		outputFile << showpoint << setprecision(2) << fixed
			<< comand << "|" << myAccount.getDate() << "|" << myAccount.getDescription()
			<< "|||" << myAccount.getBalance() << endl;

	}// end of setInitialBalance();

}



/************************************************************
*withdraw():Passing object by reference and comand by value *
*                                                           *
* This funtion will allow the user to withdraw the money    *
* from the account. ask for transaction date, but if the    *
*  user  hits enter only it will show the current date.     *
* The description will be whatever the user enters. Ask for *
*  withdrawal amount. Output data and write it in a file if *
* the user have already created one.			    *
*							    *
************************************************************/
void withdraw(BankAccount &myAccount, char comand){
	string date, transactionInfo;
	double AccountBalance, newBalance, paymentAmount;
	char c; // new line character 

	cout << "Enter the transaction date (default " << findCurrentDate() << " ): ";
	cin.get(c);

	if (c == '\n'){
		date = findCurrentDate();
		myAccount.setDate(date);
	}
	else
	{
		cin.putback(c); cin.clear();
		getline(cin, date);
		myAccount.setDate(date);
	}
	cout << "Enter withdrawal description: ";
	getline(cin, transactionInfo);
	myAccount.setDescription(transactionInfo);
	cout << "withdrawal amount: ";
	cin >> paymentAmount; cin.ignore(80, '\n');
	newBalance = myAccount.getBalance() - paymentAmount;
	myAccount.setBalance(newBalance);

	cout << showpoint << setprecision(2) << fixed << comand << "|" << myAccount.getDate()
		<< "|" << myAccount.getDescription() << "|" << paymentAmount << "||" << myAccount.getBalance() << endl;

	if (outputFile){

		outputFile << showpoint << setprecision(2) << fixed
			<< comand << "|" << myAccount.getDate() << "|" << myAccount.getDescription()
			<< "|" << paymentAmount << "||" << myAccount.getBalance() << endl;
	}

}//end of withdraw()



/************************************************************
*deposit(): Passing object by reference and comand by value *
*                                                           *
*  This funtion will allow the user to deposit the money    *
*   to the account. ask for transaction date, but if the    *
*  user  hits only enter it will show the current date.     *
*  The description will be whatever the user enters. Ask    *
*  for deposit amount. Output data and write it in a file   *
*  if the user have already created one.		    *
*							    *
************************************************************/
void deposit(BankAccount &myAccount, char comand){
	string date, transactionInfo;
	double AccountBalance, newBalance, depositAmount;
	char c; // new line character 

	cout << "Enter the transaction date (default " << findCurrentDate() << " ): ";
	cin.get(c);

	if (c == '\n'){
		date = findCurrentDate();
		myAccount.setDate(date);
	}
	else
	{
		cin.putback(c); cin.clear();
		getline(cin, date);
		myAccount.setDate(date);
	}
	cout << "Enter deposit description: ";
	getline(cin, transactionInfo);
	myAccount.setDescription(transactionInfo);
	cout << "deposit amount: ";
	cin >> depositAmount; cin.ignore(80, '\n');
	newBalance = myAccount.getBalance() + depositAmount;
	myAccount.setBalance(newBalance);

	cout << showpoint << setprecision(2) << fixed
		<< comand << "|" << myAccount.getDate() << "|" << myAccount.getDescription()
		<< "||" << depositAmount << "|" << myAccount.getBalance() << endl;

	if (outputFile){
		outputFile << showpoint << setprecision(2) << fixed
			<< comand << "|" << myAccount.getDate() << "|" << myAccount.getDescription()
			<< "|" << depositAmount << "||" << myAccount.getBalance() << endl;
	}

}//end of deposit()


/************************************************************
*        writeCheck():Passing object by reference           *
*                                                           *
* This funtion will allow the user to write acheck.choose   *
* the sequential check number. ask for transaction date,    *
* but if the user hits enter it will show the current       *
* date. The the payee info will be whatever the user enters.*
* Output data and write it in a file if the user have       *
*  already created one.					    *
*							    *
************************************************************/
void writeCheck(BankAccount &myAccount){
	int checkNumber, nextCheckNum;
	char yesOrNo;
	char c; // new line character 

	string date, transactionInfo;
	double AccountBalance, newBalance, paymentAmount;
	cout << "Next sequential check number is " << myAccount.getCheckNum() << " correct? ";
	cin >> yesOrNo; cin.ignore(80, '\n');

	while (toupper(yesOrNo) != 'Y' && toupper(yesOrNo) != 'N'){
		cout << "Invalid input " << yesOrNo << ". Please enter Y or N";
		cout << "\ncorrect?";
		cin >> yesOrNo; cin.ignore(80, '\n');
	}

	if (toupper(yesOrNo) == 'N'){

		cout << "Enter next check number: ";
		cin >> checkNumber;  cin.ignore(80, '\n');
		myAccount.setCheckNum(checkNumber);

	}

	cout << "Enter the transaction date (default " << findCurrentDate() << " ): ";
	cin.get(c);

	if (c == '\n'){
		date = findCurrentDate();
		myAccount.setDate(date);
	}
	else
	{
		cin.putback(c); cin.clear();
		getline(cin, date);
		myAccount.setDate(date);
	}
	cout << "Enter the payee info: ";
	getline(cin, transactionInfo);
	myAccount.setDescription(transactionInfo);
	cout << "Input check amount: ";
	cin >> paymentAmount; cin.ignore(80, '\n');
	newBalance = myAccount.getBalance() - paymentAmount;
	myAccount.setBalance(newBalance);

	cout << showpoint << setprecision(2) << fixed
		<< myAccount.getCheckNum() << "|" << myAccount.getDate() << "|"
		<< myAccount.getDescription() << "|" << paymentAmount << "||" << myAccount.getBalance() << endl;
	nextCheckNum = myAccount.getCheckNum() + 1;
	myAccount.setCheckNum(nextCheckNum);

	if (outputFile){
		outputFile << showpoint << setprecision(2) << fixed
			<< myAccount.getCheckNum() << "|" << myAccount.getDate() << "|"
			<< myAccount.getDescription() << "|" << paymentAmount << "||" << myAccount.getBalance() << endl;
	}
}// end of writeCheck()

// function will return the current date as a string 
//using The tm structure and ctime library .
string findCurrentDate() {
	string currentDate = "";
	time_t currentTime;
	struct tm *localTime;

	time(&currentTime);
	localTime = localtime(&currentTime);


	int Day = localTime->tm_mday;
	int Month = localTime->tm_mon + 1;
	int Year = localTime->tm_year + 1900;

	currentDate = to_string(Day) + "/" + to_string(Month) + "/" + to_string(Year);
	return currentDate;
}


int main()
{
	// variables
	char choice;
	int checkNumber;
	BankAccount object;

	cout << " \n======================================================" << endl
		<< "	Welcome to Checking Account Register" << endl
		<< " ======================================================\n\n" << endl
		<< "	 Select Option\n           " << endl
		<< "	 O: Create an output file  " << endl
		<< "	 S: Set initial balance    " << endl
		<< "	 D: Make a Deposit         " << endl
		<< "	 W: Withdrawal	           " << endl
		<< "	 C: Record a new check     " << endl
		<< "	 N: Next check number      " << endl;

	do
	{

		// ask the user to enter the command chosen from the help menu
		cout << "\nCommand: ";
		// get the user input which is the first letter and ignore the rest
		cin >> choice; cin.ignore(80, '\n');

		// switch case to exicute each case separately by calling the desired functions
		switch (toupper(choice))
		{


			// case O: call the function openOuputFile() which prompt for filename and open file for ouput.
		case 'O':
			openOutputFile();
			break;

			// case S :call the function setInitialBalance(object, choice) to set the initial balance
		case 'S':
			setInitialBalance(object, choice);

			break;

			// case N: allow the user the choose a number for the next check
		case 'N':
			cout << "Enter next check number: ";
			cin >> checkNumber;  cin.ignore(80, '\n');
			object.setCheckNum(checkNumber);
			break;

		case 'C':
			// case C: call the function writeCheck(object) to write a check
			writeCheck(object);
			break;

			// case W: call the function withdraw(object, choice) to withdraw money from the account
		case'W':
			withdraw(object, choice);
			break;

			// case D: call the function deposit(object, choice) to deposit money to the account
		case 'D':
			deposit(object, choice);
			break;
		default:
			// error message if the user types something that is not a letter
			cout << "\n Please enter the supported command!!! " << endl;

		}// end of the switch case

		// while loop that keeps looping with any character the user enters but it breaks only with Q (exit)
	} while (toupper(choice) != 'Q');

	outputFile.close();// close the output file

}//end of main()






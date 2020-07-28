// This program creates a daily to do task list and uses to store 
// the to-do list, their due-dates and whether the to-do list is accomplished or not
// Program Name: Daily Task List- Complex Problem
// Programmer Name: Asmeret Jafarzade
// Date last modified: 0721/2020

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

double getNum();
int getPosInt();
int getInt();
string getDate(string&); 
string isLetters(string& n);
bool isDateLessThan(string date1, string date2);
bool isValidDate(string date);
bool checkFormat(string &date);
bool bubbleSort(string array[], string date[], int logic_size);
bool checkFormat(string& date);
void writeTodoFile(ofstream &outputFile, string itemsArray[], string dueDatesArray[], int logic_size);
void printBanner();//
void selectionSort(string dueDatesArray[], string items[], int logic_size);
void swap(string& a, string& b); 
void printArray(const string itemsArray[], const string dueDatesArray[], int size, ostream& os = cout);
void loadArray(string itemsArray[], string dueDatesArray[], int size);

int main()
{
	system("color 5e");
	system("title               Daily Task List   by belinda ");

	printBanner();

	const int SIZE = 100;
	string itemsArray[SIZE];
	string dueDatesArray[SIZE];
	int logic_size;
	ifstream inputFile;
	ofstream outputFile;
	string filename;
	char choice = 0;
	char sortedOrNot;

	cout << "How many items do you have on your to do list? ";

   //Validate the user doesn't input negative numbers/characters/floating numbers
	logic_size = getPosInt();

	//this is the unsorted arrays
	loadArray(itemsArray, dueDatesArray, logic_size);

	// this is the unsorted arrays
	printArray(itemsArray, dueDatesArray, logic_size);


	cout << "\nWould you like your to-do items to be sorted or unsorted?"
		 << "\nPress Y for sorted or press N for unsorted: ";
	 cin >> sortedOrNot;

	if (sortedOrNot == 'y' || sortedOrNot == 'Y') {
		cout << "\nWould you like to sort it alphabetically or by dates ? (A for alphabetically or D for by dates)";
		cin >> choice;
		cin.ignore(100, '\n');
	}
	else if (sortedOrNot == 'n' || sortedOrNot == 'N')
	{
		// Display the unsorted items
		cout << "\nThis is the full unsorted list\n";
		printArray(itemsArray, dueDatesArray, logic_size);
		cout << "    ";
	}

	switch (choice){
	case 'A': case 'a': cout << "This is for the alphabetically sorted";
		//about to call bubble sort function to sort the items 
		//selectionSort(itemsArray, dueDatesArray, logic_size);
		bubbleSort(itemsArray, dueDatesArray,logic_size);
		printArray(itemsArray, dueDatesArray, logic_size);
		break;
	case 'D': case 'd': cout << "This is to sort it by dates";
		selectionSort(dueDatesArray, itemsArray, logic_size);
		printArray(itemsArray, dueDatesArray, logic_size);
		//call selection sort function to sort by dates
		break;
	}

    // write to a todo.txt file
	writeTodoFile(outputFile,itemsArray,dueDatesArray,logic_size);

	return 0;
}

void printBanner()
{
	cout << "               This Program is the Daily Task List                  \n"
		<< "                 by asking the user to input                         \n"
		<< "                     the due-dates and whether                       \n"
		<< "                       and  displays the items                       \n"
		<< "                           their due dates                           \n"
		<< "                        By Asmeret Jafarzade                       \n\n";
}
/************************************************************************
/This function gets the date and confirms it is in the right format and *
/          checks if it is within the valid range                       *
/***********************************************************************/
string getDate(string& date)
{
	while (!(checkFormat(date) && isValidDate(date)))
	{
		system("color b1");
		cout << "\a";
		cout << "\n\nPlease try again: ";
		getline(cin >> ws, date);
	}
	system("color 5e");
	return date;
}
/***********************************************************
/  This function validates the index numbers individually  *
/   in order to make sure they do not go beyond the limit  *
/  of what they should be. Day should be between 1 and 31, *
/  month between 1 and 12, and year between 1970 and 3000. *
/**********************************************************/
bool isValidDate(string date)
{
	// break the date the date by substrings to validate them individually
	string month = date.substr(0, 2);
	string day = date.substr(3, 5);
	string year = date.substr(6);

	if ((stoi(day) >= 1 && stoi(day) <= 31)
		&& (stoi(month) >= 1 && stoi(month) <= 12)
		&& (stoi(year) >= 1970 && stoi(year) <= 3000))
	{
		return true;
	}
	return false;
}
/***********************************************************************************
/This function checkformat checks the length of date doesnt exceed 10 digits,      *
/also if the second index and 5th index are not the backslash character, it returns*
/false and it also returns false if the user inputs anything but numbers,          *
/             and the backslash character                                          *
/**********************************************************************************/
bool checkFormat(string &date)
{
	for (int i = 0; i < 10; i++)
	{
		if (!isdigit(date[i]) && date[2] != '/' && date[5] != '/')
		{
			cout << "\n         *******Your date may only be digits! No other characters allowed.";
			return false;
		}
	}
	if (date.length() != 10)
	{
		cout << "\n         *******The length of the date should have been 10 characters! ";
		return false;
	}

	if (date[2] != '/' && date[5] != '/') //to ignore when the user inputs "/" 
	{
		cout << "\n         ********Please enter / to separate the month/day/year.";
		return false;
	}
	return true;
}
/***********************************************
/  This function validates if the user entered *
/          a positive integer                  *
/**********************************************/
int getPosInt()
{
	int logic_size = getInt();

	while ((logic_size < 1) && (logic_size != 0))
	{
		cout << "\nPlease enter a positive integer that is bigger than 0: ";
		logic_size = getInt();
	}
	return logic_size;
}
/**************************************************
/  This function validates if the user entered an *
/                    integer / no floating number *
/*************************************************/
int getInt() {
	double x = getNum();
	while (int(x) != x) {
		cout << "\nNo decimal numbers! Please enter an integer: ";
		x = getNum();
	}
	return int(x);
}
/**************************************************
/  This function validates if the user entered  *
/             inappropiriate characters           *
/*************************************************/
double getNum() {
	double x;
	while (!(cin >> x)) {
		cin.clear();
		cin.ignore(100, '\n');
		cout << "\nNo inapropriate characters allowed! Please enter numbers only: ";
	}
	return x;
}
//***********************************************
//Definition of function minMaxValues           *
//This funtion swaps the elements of the array  *                                          
//***********************************************
void swap(string& a, string& b)
{
	string temp = a;
	a = b;
	b = temp;
}
//***********************************************
//Definition of function writetodofile          *
//This funtion stores the items in a todo.txt   *
//file                                          *
//***********************************************
void writeTodoFile(ofstream& outputFile, string itemsArray[], string dueDatesArray[], int logic_size)
{
	cout << "\nWe are going to store the items and their due-dates in a todo.txt file \n";
	outputFile.open("todo.txt");
	if (outputFile.fail())
	{
		cout << "FAIL! FILE CAN NOT OPEN!" << endl;
	}
	else 
	{ for (int i = 0; i < logic_size; i++)
		{
			outputFile << itemsArray[i] << dueDatesArray[i] << endl;
		}
	}
	// close the file
	outputFile.close();
	cout << "\nThe items and dude dates have been written to todo.txt\n";
}
//***********************************************
//Definition of function loadArray loads the    *
// array and validates the items and            *
//   their due-dates                            *
//***********************************************
void loadArray(string itemsArray[], string dueDatesArray[], int logic_size)
{
	for (int i = 0; i < logic_size; i++)
	{
		cout << "\tPlease enter your to do-item #: " << i + 1 << " :";
		getline(cin >> ws, itemsArray[i]);
		itemsArray[i] = isLetters(itemsArray[i]);

		cout << "\n\tNow enter the due-dates for those items as MM/DD/YYYY: " << itemsArray[i] << ": ";
		getline(cin >> ws, dueDatesArray[i]);
		dueDatesArray[i] = getDate(dueDatesArray[i]);
	}
}
//*************************************
//Definition of function printArray   *
// this function prints the to-do list*
//*************************************
void printArray(const string itemsArray[], const string dueDatesArray[], int size, ostream& os)
{
	os << "\nThese are the items and their due dates: " << endl;
	os<<"\n*****TO-DO LIST*************************DUE-DATES\n";
	for (int i = 0; i < size; i++)
	{
		os << fixed << showpoint << setprecision(2);
		//call sort function here 		
		os << left << setw(10) << (itemsArray[i]) << "        " << left << setw(10) << (dueDatesArray[i]) << "\n";
	}
}
//***********************************************
//Definition of function selectionSort          *
//This funtion compares the dates and calls the *
// isdateLessthan function to sort the smallest *
// date and proceeds to swap them               *
//***********************************************
void selectionSort(string dueDatesArray[], string items[], int logic_size) //dates
{
	int minIndex;
	string minValue;
	for (int i = 0; i < (logic_size - 1); i++)
	{
		minIndex = i;
		minValue = dueDatesArray[i];
		for (int index = i + 1; index < logic_size; index++)
		{
			if (isDateLessThan(dueDatesArray[index], minValue))
			{
				minValue = dueDatesArray[index];
				minIndex = index;
			}
		}
		swap(dueDatesArray[minIndex], dueDatesArray[i]);
		swap(items[minIndex], items[i]);
	}
}
//**************************************************
//Definition of function bubbleSort. This function *
//This funtion sorts the arrays and                *
//swaps the items and also the dates correspondigly*                                   
//**************************************************

bool bubbleSort(string array[], string date[], int logic_size)
{
	int maxElement;
	int index;
	for (maxElement = logic_size - 1; maxElement; maxElement--)
	{
		for (index = 0; index < maxElement; index++) {
			if (array[index] > array[index + 1])
			{
				swap(array[index], array[index + 1]);
				swap(date[index], date[index + 1]);
			}
		}
	}
	return true;
}
//*************************************************
//Definition of function isDateLessThan           *
//This funtion compares each element of the string*
// and compares them                              *
//*************************************************
bool isDateLessThan(string date1, string date2)
{
	if (date1.substr(6, 9) < date2.substr(6, 9))
	{
		return true;
	}
	if ((date1.substr(6, 9) == date2.substr(6, 9)) && (date1.substr(3, 4) < date2.substr(3, 4)))
	{
		return true;
	}
	if ((date1.substr(6, 9) == date2.substr(6, 9)) && (date1.substr(3, 4) == date2.substr(3, 4)) && date1.substr(0, 1) < date2.substr(0, 1))
	{
		return true;
	}
	return false;
}
//************************************************
//Definition of function isLetters. This function*            
//validates if the user inputs numbers instead of*
//characters                                     *
//***********************************************
string isLetters(string &item)
{
	for (int i = 0; i < item.size(); i++)
	{
		if (!(isalpha(item[i])))
		{
			cout << "Enter characters only!";
		    cin >> item;
			cin.ignore(100, '\n');
			cin.clear();
		}
		return item;
	}
}

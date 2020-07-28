// This is the simple program that creates a daily to-do task list and stores the date in a MM/DD/YYYY format
// It also validates the dates and displays the correct inputted due-dates 
// Program Name: Daily Task List-Simple Problem
// Programmer Name: Asmeret Jafarzade
// Date last modified: 07/21/2020

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

//Function prototypes  
bool isValidDate(string date);
bool checkFormat(string &date);
int getPosInt();
int getInt();
double getNum();
string getDate(string &date);  
void printBanner(); 

int main()
{
	system("color 5e");
	system("title               Daily Task List  by Asmeret Jafarzade");

	printBanner();

	const int SIZE = 100;
	string itemsArray[SIZE];
	string dueDatesArray[SIZE];
	int logic_size=0;

	cout << "\nHow many items do you have on your To-do list? ";
	logic_size = getPosInt();

	//Validate that the user does not input characters/negative numbers/floating numbers
	

	//prompt the user to enter the items and their due-dates
	for (int i = 0; i < logic_size; i++)
	{
		cout << "\tPlease enter your to do-items: " << i + 1 << " : ";
		getline(cin >> ws, itemsArray[i]);
	
		cout << "\tNow enter the due-dates for those items as MM/DD/YYYY: " << itemsArray[i] << ": ";
		getline(cin >> ws, dueDatesArray[i]);
		dueDatesArray[i] = getDate(dueDatesArray[i]);
	}

		//display the items and their due dates
		cout << "These are the items and their due dates: " << endl;
		cout << "\n*****TO-DO LIST*************************DUE-DATES\n";
		for (int i = 0; i < logic_size; i++)
		{
			cout << fixed << showpoint << " " << setw(8) << left << itemsArray[i]
				<< "                  " << fixed << setprecision(5)
				<< setw(8) << dueDatesArray[i] << " \n";
		}

		system("pause");
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
string getDate(string &date)
{
	// it goes to the checkformat and validate function to check the format
	while (!(checkFormat(date) && isValidDate(date)))   
	{
		system("color b1");
		cout << "\a";
		cout << "\n\nPlease try again: ";
		getline(cin >> ws, date);
		checkFormat(date);
		isValidDate(date);
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
			if (!isdigit(date[i]) && date[2] != '/' && date[5]!= '/') 
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
	int logic_size=getInt();

	while( (logic_size < 1) && (logic_size !=0))
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

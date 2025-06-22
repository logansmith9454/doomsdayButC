// doomsday.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <map>
#include <string>
#include <random>


int main()
{
	Quiz q;
	q.generateQuiz();


}

class Quiz {
public:
	int wholeYear;
    int year;
    int month;
	int day;
    int cent;
    int monthValue;
	int yearValue;
	int leapValue;
	int centValue;
	int dayOfWeek;
	std::string userInput;
	int userGuess;
	bool validInput;
	std::string userRepeat;
	bool repeat;
	std::random_device rd;
	std::mt19937 gen{ rd() };
	std::uniform_int_distribution<> dayGen28{ 1, 28 };
	std::uniform_int_distribution<> dayGen29{ 1, 29 };
	std::uniform_int_distribution<> dayGen30{ 1, 30 };
	std::uniform_int_distribution<> dayGen31{ 1, 31 };
	std::uniform_int_distribution<> monthGen{ 1, 12 };
	std::uniform_int_distribution<> yearGen{ 1900, 2100 };
	// Map of how many days in each month
	std::map<int, int> monthDayMap = {
	{1, 31}, {2, 28}, {3, 31}, {4, 30}, {5, 31},
	{6, 30}, {7, 31}, {8, 31}, {9, 30}, {10, 31},
	{11, 30}, {12, 31}
	};
	// Map of the values for each month
	std::map<int, int> monthValueMap = {
	{1, 4}, {2, 0}, {3, 3}, {4, 6}, {5, 1},
	{6, 4}, {7, 6}, {8, 2}, {9, 5}, {10, 0},
	{11, 3}, {12, 5}
	};
	std::map<int, std::string> dayOfWeekMap = {
	{0, "Sunday"}, {1, "Monday"}, {2, "Tuesday"}, {3, "Wednesday"},
	{4, "Thursday"}, {5, "Friday"}, {6, "Saturday"}
	};

	int getRandomYear() {
		return yearGen(gen);
	}

	int getRandomMonth() {
		return monthGen(gen);
	}

	int getRandomDay(int month) {
		if (month == 2) {
			if (leapValue == 1) {
				// Make sure to do 29 days in Feb if leap year
				return dayGen29(gen);
			}
			else {
				return dayGen28(gen);
			}
		}
		else if (monthDayMap[month] == 30) {
			return dayGen30(gen);
		}
		else {
			return dayGen31(gen);
		}
	
	}

	int getCent(int year) {
		return (year % 100) / 100;
	}

	int getYear(int year, int cent) {
		return year - cent;
	}
	
	// Check if the year is a leap year
	int getLeapValue(int year) {
		// Most people don't know that centuries are not leap years unless divisible by 400.
		if ((year % 4 == 0 && year != 0) || (year == 0 && cent % 4 == 0)) {
			return 1; // Leap year
		}
		else {
			return 0; // Not leap year
		}
	}

	int getCentValue(int cent) {
		switch (cent % 4) {
		case 0:
			return 2;
		case 1:
			return 0;
		case 2:
			return 5;
		case 3:
			return 3;
		default:
			return -1; // Invalid case
		}
	}

	int getYearValue(int year) {
		return ((year - (year % 4)) / 4) + year;
	}

	int getMonthValue(int month) {
		return monthValueMap[month];
	}

	int getDayOfWeek(int centValue, int yearValue, int monthValue, int day, int leapValue) {
		return (centValue + yearValue + monthValue + day - leapValue) % 7;
	}

	bool generateQuiz() {
		wholeYear = getRandomYear();
		month = getRandomMonth();
		monthValue = getMonthValue(month);
		day = getRandomDay(month);
		cent = getCent(wholeYear);
		centValue = getCentValue(cent);
		year = getYear(wholeYear, cent);
		yearValue = getYearValue(year);
		leapValue = getLeapValue(wholeYear);
		dayOfWeek = getDayOfWeek(centValue, yearValue, monthValue, day, leapValue);

		validInput = false;
		while (validInput == false) {
			std::cout << month << "/" << day << "/" << year << std::endl;
			std::cin >> userInput;
			try {
				userGuess = std::stoi(userInput);
			}
			catch (...) {
				std::cout << "Invalid input. Please enter an integer." << std::endl;
			}
			if (userGuess < 0 || userGuess > 6) {
				std::cout << "Invalid input. Please enter a number between 0 and 6" << std::endl;
			}
			else {
				validInput = true;
			}
			if (dayOfWeek == userGuess) {
				std::cout << "Correct!" << std::endl;
			}
			else {
				std::cout << "Incorrect. The right answer was " << dayOfWeekMap[dayOfWeek] << "." << std::endl;
			}
			validInput = false;
			while (validInput == false) {
				std::cout << "Try another? (y/n)\n>" << std::endl;
				std::cin >> userRepeat;
				if (userRepeat == "y") {
					repeat = true;
					validInput = true;
				}
				else if (userRepeat == "n") {
					repeat = false;
					validInput = true;
				}
				else {
					std::cout << "Invalid input. Please enter either 'y' or 'n'." << std::endl;
				}
			}
			return repeat;
		}
	}
};

//final random = Random();
//// Generate a random date
//_year0 = (random.nextInt(200) + 1900); // Year is between 1900 and 2100
//_month = random.nextInt(12) + 1; // Month is between 1 and 12
//switch (_month) {
//case 1 || 3 || 5 || 7 || 8 || 10 || 12:
//    _day = random.nextInt(31) + 1;
//    break;
//case 2:
//    _day = random.nextInt(28) + 1;
//    break;
//case 4 || 6 || 9 || 11:
//    _day = random.nextInt(30) + 1;
//    break;
//}
//
//_year = _year0 % 100;
//_cent = ((_year0 - _year) / 100).toInt();
//if ((_year % 4 == 0 && _year != 0) || (_year == 0 && _cent % 4 == 0)) {
//    _leap = true;
//}
//else {
//    _leap = false;
//}
//_yearValue = (((_year - (_year % 4)) / 4) + _year).toInt();
//
//switch (_cent % 4) {
//case 0:
//    _centValue = 2;
//case 1:
//    _centValue = 0;
//case 2:
//    _centValue = 5;
//case 3:
//    _centValue = 3;
//}
//
//switch (_month) {
//case 2 || 3 || 11:
//    _monthValue = 0;
//case 6:
//    _monthValue = 1;
//case 9 || 12:
//    _monthValue = 2;
//case 4 || 7:
//    _monthValue = 3;
//case 1 || 10:
//    _monthValue = 4;
//case 5:
//    _monthValue = 5;
//case 8:
//    _monthValue = 6;
//}
//if (_month < 3 && _leap == true) {
//    _leapValue = 1;
//}
//else {
//    _leapValue = 0;
//}
//
//_correctAnswer =
//((_centValue + _yearValue + _monthValue + _day - _leapValue) % 7)
//.toInt();

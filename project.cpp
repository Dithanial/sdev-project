// project.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TicketMaster.h"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// Prototypes
void requestSelected(TicketMaster&);
void purchase(TicketMaster&, int, int, int);


int main() {

	int choice = 0;
	TicketMaster tm;

	do {
		while (true) {
			cout << "Please select an option:\n1: Display Seating Chart\n2: Request Tickets\n3: Print Sales Report\n4: Exit\n   ";
			cin >> choice;

			if (choice > 0 && choice <= 5)
				break;
			else
				cout << "Invalid entry. Please try again.\n\n";
		}


		switch (choice) {
		case 1: tm.displaySeats();
			break;
		case 2: requestSelected(tm);
			break;
		case 3: tm.salesReport();
			
			
			break;
		case 4: cout << "Goodbye!\n";
			break;
		case 5: tm.clearSeats();
		}
	} while (choice != 4);

	return 0;
}

void requestSelected(TicketMaster &tm) {
	int reqSeats = 0, reqRow = 0, reqStart = 0, retry = 0;

	// Get the Requested number of seats
	while (true) {
		cout << "How many seats would you like (30 max)? ";
		cin >> reqSeats;
		if (reqSeats > 0 && reqSeats <= 30)
			break;
		else
			cout << "Invalid number, please try again.\n";
	}

	// Get the Requested Row
	while (true) {
		cout << "Which Row would you like (1-15)? ";
		cin >> reqRow;
		if (reqRow > 0 && reqRow <= 15)
			break;
		else
			cout << "Invalid number, please try again.\n";
	}

	// Get the Requested Starting Seat
	while (true) {
		bool good = false, enough = false;
		cout << "Which seat would you like to start with (1-" << 31 - reqSeats << ")? ";
		cin >> reqStart;
		if (reqStart > 0 && reqStart <= 30)
			good = true;
		else
			cout << "Invalid number, please try again.\n";
		if (reqSeats + reqStart > 31) {
			cout << "Not enough seats in a row for for you to have " <<
				reqSeats << " seats starting at " << reqStart << ". Please " <<
				"select a lower starting seat number.\n";
		}
		else {
			enough = true;
		}
		if (good && enough)
			break;
	}

	reqRow--;
	reqStart--;

	switch (tm.requestTickets(reqSeats, reqRow, reqStart)) {
	case 0: purchase(tm, reqSeats, reqRow, reqStart);
		break;
	case 1: cout << "One or more of the requested seats is unavailable. Please view the available seats and try again.\n";
		break;
	}
}

void purchase(TicketMaster &tm, int seats, int row, int start) {
	float price = tm.getSeatPrice(row), total = price * seats;
	char buy = ' ';

	cout << "Congratulations, those seats are available! You have requested " <<
		seats << " seats. These seats are $" << fixed << setprecision(2) << price << " each.\nThis brings your total to $" << total << ". Would you like to purchase these tickets? (Y or N) ";
	while (true) {
		cin >> buy;
		if (buy != 'y' && buy != 'Y' && buy != 'n' && buy != 'N') {
			cout << "Invalid answer, please press Y if you would like to buy these tickets or N if you do not want to buy these tickets.\n";
		}
		else if (buy == 'y' || buy == 'Y') {
			cout << "Great!\n";
			cout << tm.purchaseTickets(seats, row, start, total);
			break;
		}
		else {
			cout << "Returning to main menu.\n\n";
			break;
		}
	}
 	
	cout << "Seats sold: " << tm.getSeatsSold() << " Total Money: " << tm.getTotalMoney() << endl;

}

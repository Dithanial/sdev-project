// A semester project for SDEV-240 Fall 2016
// Authors:
//  Jeremy DeHay
//  Demostenes BalbuenaGarcia
//  Stephen Smoogen
#ifdef _WIN32
#include "stdafx.h"
#endif
#include "TicketMaster.h"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// Prototypes
void requestSelected(TicketMaster&);
void purchase(TicketMaster&, int, int, int);
void salesReport(TicketMaster&);
void mapAuditorium(TicketMaster&);

int main() {

	int choice = 0;
	TicketMaster tm;
	string rest;
	
	do {
		while (true) {
		  cout << "Please select an option:" << endl;
		  cout << " 1: Display Seating Chart " << endl;
		  cout << " 2: Request Tickets " << endl;
		  cout << " 3: Print Sales Report" << endl;
		  cout << " 4: Exit" << endl;
		  cout << endl << " 5: Reset Everything" << endl;
		  cin >> choice;
		  if (choice > 0 && choice <= 5)
		    break;
		  else 
		    cout << "Invalid entry. Please try again.\n\n";
		}


		switch (choice) {
		case 1: mapAuditorium(tm);
		  break;
		case 2: requestSelected(tm);
		  break;
		case 3: salesReport(tm);
		  break;
		case 4: cout << "Goodbye!\n";
		  break;
		case 5:
		  cout << "Do you really want to reset everything? (Y/N)" << endl;
		  cin >> rest;
		  if ( rest[0] == 'Y' || rest[0] == 'y') {
		    tm.clearSeats();
		  }
		}
	} while (choice != 4);

	return 0;
}

void requestSelected(TicketMaster &tm) {
  int reqSeats = 0, reqRow = 0, reqStart = 0, retry = 0;

  // Get the Requested number of seats
  while (true) {
    cout << "How many seats would you like (" << Max_Cols << " max)? ";
    cin >> reqSeats;
    if (reqSeats > 0 && reqSeats <= Max_Cols)
      break;
    else
       cout << "Invalid number, please try again.\n";
  }

  // Get the Requested Row
  while (true) {
    cout << "Which Row would you like (1-" << Max_Rows << ")? ";
    cin >> reqRow;
    if (reqRow > 0 && reqRow <= Max_Rows) {
      reqRow--; // our rows are allocated from 0 -> Max_Rows-1
      if (reqSeats > tm.getMaxSeats(reqRow)){
	cout << "The row you are requesting does not have enough available "<< endl;
	cout << "seats in a block. Please try again" << endl;
      } else {
	break;
      }
    } else
       cout << "Invalid number, please try again.\n";
  }

  // Get the Requested Starting Seat
  while (true) {
    cout << tm.printNum();
    cout << tm.printRow(reqRow);
    int first = tm.getFirstSeat(reqRow)+1;
    cout << "Which seat would you like to start with " << first <<
      " -> " << (Max_Cols - reqSeats)+1 <<")? ";
    cin >> reqStart;
    if (reqStart < first || reqStart > Max_Cols)
       cout << "Invalid number, please try again.\n";
    else {
      reqStart--;
      if (tm.requestTickets(reqSeats, reqRow, reqStart)){
	purchase(tm, reqSeats, reqRow, reqStart);
	return;
      } else {
	cout << "One or more of the requested seats is unavailable. " << endl;
	cout << "Please view the available seats and try again.\n";
      }
    }
  }
}


void purchase(TicketMaster &tm, int seats, int row, int start) {
	float price = tm.getSeatPrice(row), total = price * seats;
	char buy = ' ';

	cout << "Congratulations, those seats are available! You have requested " << seats << " seats.\n";
	cout << "These seats are $" << fixed << setprecision(2)  << price << " each.\nThis brings your total to $" << total << ".\n";
	cout <<"Would you like to purchase these tickets? (Y or N) ";
	while (true) {
		cin >> buy;
		if (buy != 'y' && buy != 'Y' && buy != 'n' && buy != 'N') {
			cout << "Invalid answer, please press Y if you would like to buy these tickets or N if you do not want to buy these tickets.\n";
		} else if (buy == 'y' || buy == 'Y'){
			cout << "Great!\n";
			cout << tm.purchaseTickets(seats, row, start, total);
			break;
		} else {
			cout << "Returning to main menu.\n\n";
			break;
		}
	}
	cout << "Seats sold: " << tm.getSeatsSold() << " Total Money: " << tm.getTotalMoney() << endl;
}

void salesReport(TicketMaster &tm){
  cout << tm.getSalesReport(); // return a string
}

void mapAuditorium(TicketMaster &tm){
  cout << tm.displaySeats(); // returned a string.
}

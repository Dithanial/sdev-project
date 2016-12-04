
#ifndef TICKETMASTER_H
#define TICKETMASTER_H
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

const int Max_Rows = 15;
const int Max_Cols = 30;

const char SeatAvail = '#';
const char SeatTaken = '*';

class TicketMaster {
private:

	int seatsSold=0;
	float totalMoney=0;

	struct SeatStructures {
		char  seatstatus;
		float seatprice;
		SeatStructures(char sold = SeatAvail, float price = 0.0) {
			seatstatus = sold;
			seatprice = price;
		};
	};
	SeatStructures auditorium[Max_Rows][Max_Cols];

public:
	TicketMaster();
	~TicketMaster();

	// a getter for seat availability 
	bool isSeatSold(int row, int col) {
		if (auditorium[row][col].seatstatus == SeatAvail) {
			return true;
		}
		else
			return false;
	}

	// a bounds checker
	bool insideSS(int, int); //defined below

							 // get the price of the seat
	float getSeatPrice(int row) {
		return auditorium[row][0].seatprice;
	}

	void setSeatPrice(int row, int col, float price) {
		auditorium[row][col].seatprice = price;
	}

	void markSold(int row, int col) {
		auditorium[row][col].seatstatus = SeatTaken;
	}

	char getSeat(int row, int col) {
		return auditorium[row][col].seatstatus;
	}

	void displaySeats();

	void clearSeats();

	int requestTickets(int, int, int);

	string purchaseTickets(int, int, int, float);

	void salesReport() {// print a sales report 

		int seatsLeft; //variable declaration
		seatsLeft = (Max_Rows * Max_Cols - getSeatsSold());// store in the seatsLeft variable the empty seats

		//Print report 
		cout << "\n\t\t\t   Sales Report";
		cout<<"\n* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n   ";
		cout << "Seats sold: " << getSeatsSold() << "      Total Money: $" << getTotalMoney() << "\t SeatsLeft:  " << seatsLeft << endl;
		cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n:   ";
	}

	int getSeatsSold() {
		return seatsSold;
	}

	void setSeatsSold(int sold) {
		seatsSold += sold;
	}

	void clearSeatsSold() {
		seatsSold = 0;
	}

	float getTotalMoney() {
		return totalMoney;
	}

	void setTotalMoney(float sold) {
		totalMoney += sold;
	}

	void clearTotalMoney() {
		totalMoney = 0.0;
	}
	void reportManagment();

};

TicketMaster::TicketMaster() {

	// Read the price file and fill in data.
	ifstream PriceFile;
	ifstream SeatsFile;
	ifstream ticketSoldFile;// file containing the ticket sales
	ifstream moneyFile;// file containing the total sales

	// Set up the prices for each row of seats.
	float tempPrice = 0.0;
	string tempData = "";
	string displayTempData;
	int row = 0;
	int col = 0;
	PriceFile.open("SeatPrices.dat");
	if (!PriceFile)
		cout << "Not able to read price file";
	else {
		while ((row < Max_Rows) && (PriceFile >> tempPrice)) {
			for (col = 0; col< Max_Cols; col++) {
				setSeatPrice(row, col, tempPrice);
			}
			row++;
		}
	};
	PriceFile.close();

	// Set up the taken seats in auditorium
	row = 0;
	SeatsFile.open("SeatAvailability.dat");
	if (!SeatsFile)
		cout << "Not able to read available seats file";
	else {
		while ((row < Max_Rows) && (SeatsFile >> tempData)) {
			col = 0;
			while (col < Max_Cols) {
				if (char(tempData[col]) == SeatTaken) {
					markSold(row, col);
				}
				col++;
			};
			row++;
		}
	}
	SeatsFile.close();

	
// copying from seatReport.dat  into variable seatSold
	ticketSoldFile.open("seatReport.dat");
	if (!ticketSoldFile)
		cout << "Not able to read price file";
	else {
		
		ticketSoldFile >> seatsSold;
	}
	ticketSoldFile.close();
// copying from moneyReport.dat into variable totalMoney
	moneyFile.open("moneyReport.dat");
	if (!moneyFile)
		cout << "Not able to read price file";
	else {

		moneyFile >> totalMoney;
	}
	moneyFile.close();
}

// Bounds checking
bool TicketMaster::insideSS(int row, int col) {
	if ((row < 0) || (row >= Max_Rows)) { return false; };
	if ((col < 0) || (row >= Max_Cols)) { return false; };
	return true;
}

// Display seating chart
void TicketMaster::displaySeats() {
	cout << "     Seats" << endl;
	int numX = Max_Cols / 10; // work out the number of rows
	int remX = Max_Cols % 10; // work out the left over
	cout << "   ";
	for (int c = 0; c < numX; c++) {
		for (int i = 1; i < 10; i++) {
			cout << i;
		};
		cout << "0";
	}
	for (int i = 1; i <= remX; i++) {
		cout << i;
	};
	cout << endl;
	// print the rows.
	for (int r = 0; r < Max_Rows; r++) {
		cout << setw(2) << (r + 1) << " ";
		for (int c = 0; c < Max_Cols; c++) {
			cout << getSeat(r, c);
		};
		cout << endl;
	};
	cout << endl;
}

// Check if tickets are available
int TicketMaster::requestTickets(int seats, int row, int start) {

	for (int i = start; i < start + seats; i++) {
		if (!isSeatSold(row, i)) {
			return 1;
		}
	}
	return 0;
}

// purchase tickets
string TicketMaster::purchaseTickets(int seats, int row, int start, float price) {
	float payment = 0.0;
	char retry = ' ';

	// Validate and accept money input
	while (true) {
		cout << "How much will you be paying with? $";
		cin >> payment;
		if (payment < price) {
			while (true) {
				cout << "Not enough funds to continue the transaction. Would you like to try again? (Y or N) ";
				cin >> retry;
				if (retry != 'y' && retry != 'Y' && retry != 'n' && retry != 'N') {
					cout << "Invalid entry, please choose Y or N.\n";
				}
				else if (retry == 'N' || retry == 'n')
					return "Transaction Canceled.\n\n";
				else
					break;
			}
		}
		else {
			cout << "You will get $" << fixed << setprecision(2) << payment - price << " in change. Here are your tickets.\n";
			break;
		}
	}

	// Mark seats as sold
	for (int i = start; i < seats + start; i++) {
		markSold(row, i);
	}
	setSeatsSold(seats);
	setTotalMoney(price);

	// String manipulation for return purposes
	string tickets;
	stringstream ssPrice, ssTicket, ssRow, ssStart;
	ssPrice << fixed;
	ssPrice.precision(2);

	// Print Tickets.
	for (int i = 1; i <= seats; i++) {
		tickets += "Ticket ";
		ssTicket.str("");
		ssTicket << i;
		tickets += ssTicket.str();;

		tickets += "\n* * * * * * * * * * * * * * * * * * * * * * *\nRow:   ";
		ssRow.str("");
		ssRow << row + 1;
		tickets += ssRow.str();

		tickets += "\tSeat:   ";
		ssStart.str("");
		ssStart << start + i;
		tickets += ssStart.str();

		tickets += "\tPrice: $";
		ssPrice.str("");
		ssPrice << (price / seats);
		tickets += ssPrice.str();

		tickets += "\n* * * * * * * * * * * * * * * * * * * * * * *\n\n";
	}

	return tickets;
}


TicketMaster::~TicketMaster() {
	string tempData = "";
	ofstream SeatsFile;
	ofstream ticketSoldFile;
	ofstream moneyFile;

	SeatsFile.open("SeatAvailability.dat");
	if (!SeatsFile)
		cout << "Not able to read available seats file.\n";
	else {
		for (int row = 0; row < Max_Rows; row++) {
			for (int col = 0; col < Max_Cols; col++) {
				SeatsFile << getSeat(row, col);
				//cout << getSeat(row, col);
			}
			SeatsFile << endl;
			//cout << endl;
		}
	}
	SeatsFile.close();

//Updating the information of sold tickets
	ticketSoldFile.open("seatReport.dat");
	if (!ticketSoldFile)
		cout << "Not able to read price file";
	else {

		ticketSoldFile << seatsSold;
	}
	ticketSoldFile.close();
//Updating the information of the money from sells
	moneyFile.open("moneyReport.dat");
	if (!moneyFile)
		cout << "Not able to read price file";
	else {

		moneyFile << totalMoney;
	}
	moneyFile.close();
}



void TicketMaster::clearSeats() {

	for (int row = 0; row < Max_Rows; row++) {
		for (int col = 0; col < Max_Cols; col++) {
			auditorium[row][col].seatstatus = SeatAvail;
		}
	}
	clearSeatsSold();
	clearTotalMoney();
}

/*void TicketMaster::reportManagment() {

	// Read the price file and fill in data.
	ofstream ticketSoldFile;
	// Set up the prices for each row of seats.
	int soldSeats = 0;

	ticketSoldFile.open("SalesReport.dat");
	if (!ticketSoldFile)
		cout << "Not able to read price file";
	else {
		ticketSoldFile << getSeatsSold() << endl;
		
	}
	ticketSoldFile.close();

}*/

#endif

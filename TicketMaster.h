// A semester project for SDEV-240 Fall 2016
// Authors:
//  Jeremy DeHay
//  Demostenes BalbuenaGarcia
//  Stephen Smoogen

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


// A class which the menu program interacts with to instantiate an auditorium. 
class TicketMaster {
 private:

  int seatsSold;
  float totalMoney;

  // Our auditorium is an array of SeatStructures. Each Seat stores if
  // the seat is sold and what price would be at that seat.
  struct SeatStructures {
    char  seatstatus;
    float seatprice;
    SeatStructures(char sold=SeatAvail, float price = 0.0){
      seatstatus = sold;
      seatprice = price;
    };
  };
  SeatStructures auditorium[Max_Rows][Max_Cols];

 public:
  TicketMaster();
  ~TicketMaster();
  
  // a getter for seat availability 
  bool isSeatAvail(int row, int col){
    if (auditorium[row][col].seatstatus == SeatAvail){
      return true;
    }
    else
      return false;
  }

  // a bounds checker
  bool insideSS(int ,int ); //defined below

  // get the price of the seat
  float getSeatPrice(int row){
    return auditorium[row][0].seatprice;
  }

  void setSeatPrice(int row, int col,float price){
    auditorium[row][col].seatprice = price;
  }

  void markSold(int row, int col){
    auditorium[row][col].seatstatus = SeatTaken;
  }

  char getSeat(int row, int col){
    return auditorium[row][col].seatstatus;
  }

  // a func to tell us how many seats are in a particular row.
  int getMaxSeats(int row);

  // a func to tell us which is the first available seat in a row.
  int getFirstSeat(int row);

  // a func to output the current auditorium. 
  void displaySeats();
  void printNum();
  void printRow(int);

  void clearSeats();

  bool requestTickets(int, int, int);
  
  string purchaseTickets(int, int, int, float);
  
  void getSimpleSalesReport() {
    cout << endl << "=== Simple Sales Report ===" << endl;; 
    cout << "The auditorium has " << Max_Cols * Max_Rows << " seats." << endl;
    cout << "Seats sold: " << getSeatsSold() << endl;
    cout << "Total Money: " << getTotalMoney() << endl;
    cout << "===========================" << endl << endl;
  }

  int getSeatsSold() {
    return seatsSold;
  }

  void setSeatsSold(int sold) {
    seatsSold += sold;
  }

  void clearSeatsSold(){
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
	
};

TicketMaster::TicketMaster() {

  // Read the price file and fill in data.
  ifstream PriceFile;
  ifstream SeatsFile;

  // Set up the prices for each row of seats.
  float tempPrice = 0.0;
  string tempData ="";
  int row = 0;
  int col = 0;
  PriceFile.open("SeatPrices.dat");
  if (!PriceFile)
    cout << "Not able to read price file";
  else {
    while ((row < Max_Rows) && (PriceFile >> tempPrice)){
      for (col=0; col< Max_Cols; col++){
        setSeatPrice(row,col,tempPrice);
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
    while ((row < Max_Rows) && (SeatsFile >> tempData)){
      col = 0;
      while (col < Max_Cols){
      	if (char(tempData[col]) == SeatTaken) {
      	  markSold(row,col);
      	}
      	col++;
      };
      row++;
    }
  }
  SeatsFile.close();
  // Ok now that we have read in the file we need to reset the amount
  // of seats we have sold and the amount of Money that has been taken.
  seatsSold = 0;
  totalMoney = 0;
  for (int row = 0; row <= Max_Rows; row++){
    for (int col = 0 ; col <= Max_Cols; col++){
      if (auditorium[row][col].seatstatus == SeatTaken){
	totalMoney += auditorium[row][col].seatprice;
	seatsSold++;
      }
    }
  }
}

// Bounds checking
bool TicketMaster::insideSS(int row, int col) {
  if ((row < 0) || (row >= Max_Rows)) {return false;};
  if ((col < 0) || (row >= Max_Cols)) {return false;};
  return true;
}

// Display seating chart
void TicketMaster::displaySeats() {
  printNum();
  // print the rows.
  for (int row = 0; row < Max_Rows; row++){
    printRow(row);
  };
  cout << endl;
}

void TicketMaster::printNum(){
  cout << "     Seats" << endl;
  int numX = Max_Cols / 10; // work out the number of rows
  int remX = Max_Cols % 10; // work out the left over
  cout << "   ";
  for (int col = 0; col < numX; col++){
    for (int i = 1; i < 10; i++){
      cout << i;
    };
    cout << "0";
  }
  for (int i=1; i<=remX; i++){
    cout << i;
  };
  cout << endl;
}

void TicketMaster::printRow(int row){
    cout << setw(2)  << (row+1) << " ";
    for (int col = 0; col < Max_Cols; col++){
      cout << getSeat(row,col);
    };
    cout << endl;
  
}

int TicketMaster::getMaxSeats(int row){
  int max_seats =0, num_seats = 0;
  // loop through the seats in a row. if the seat is available count
  // the num seats in a group. If the seat is sold check to see if the
  // seats avail in that block is more than our previous max. If it is
  // set the max to the num and reset the num until we find a new
  // block
  for (int col = 0; col < Max_Cols ; col++){
    if (isSeatAvail(row,col)){
      num_seats++;
    } else {
      num_seats = 0;
    }
    // so we reset max_seats a lot and could probably be more
    // efficient here.
    if (num_seats > max_seats){
      max_seats = num_seats;
    };
  }
  return max_seats;
}

int TicketMaster::getFirstSeat(int row){
  int first = 0;
  for (int col = 0; col < Max_Cols; col++){
    if (isSeatAvail(row,col)){
      first = col;
      break;
    }
  }
  return first;
  
}

// Check if tickets are available
bool TicketMaster::requestTickets(int seats, int row, int start) {
  for (int i = start; i < start + seats; i++) {
    if (!isSeatAvail(row, i)) {
      return false;
    }
  }
return true;
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
        } else if (retry == 'N' || retry == 'n')
            return "Transaction Canceled.\n\n";
          else 
            break;
      }
    } else {
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

#endif

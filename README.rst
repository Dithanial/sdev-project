===============
 Project Notes
===============

This project was written for Champlain College SDEV 230 by Jeremy
DeHay, Demostenes BalbuenaGarcia, Stephen Smoogen. The project was
setup and created by Jeremy so he is the 'project leader' for
this. Stephen Smoogen wrote parts of the TicketMaster class and did
some testing and cleanup. Detailed reports were written by Demostenes
with additional testing. 

==============
 Requirements
==============

1. The theatre's auditorium has 15 rows with 30 seats. [implemented]
   There will be a TicketManager class [implemented]
   The TicketManager class shall have a 2d
     SeatStructure [implemented]
   SeatStructure will keep track of seat price and sold [implemented]
2. The seat prices should be read from SeatPrices.data [implemented]
    This file contains 15 lines with the price for each row.
   The seat availability should be read from SeatAvailability.data.
    The file contains 450 (15x30) indicating which seats have been
    sold('*') and which are available('#').
   The initial run will be all '#'. However the system needs to keep
    track of the sales [implemented]
3. The client program will have a menu-driven options
     It will accept data from the user [implemented]
     It will validate the data
     It will call appropriate class functions [implemented]
   The menu will display seating chart, request tickets, print a sales
     report, and exit the program [implemented]
4. Display seats a TicketManager function should be called that
     creates and returns a string which is then displayed by the
     client program. [implemented]
5. Request tickets. Client program will pull in data from the user. It
     will then pass this to the class function to order the seats.
     A string is returned with
       lists the number of requested seats
       the price per seat
       total price
     Client program then prints the text
     [implemented]
6. Purchase tickets. Client program asks if the person wants to pay
     for it. The module from the TM class then accepts the money,
     checks that the money is correct, marks the seat as sold, and
     creates and returns a string with the data for the parts listed.
     [implemented]
7. Sales report, a TicketManager report module should be called. This
     module must create and return a string holding a report that
     tells how many seats have been sold, how many are still
     available, and how much money has been collected so far from the
     sold seats. 
8  When the sales are over for a period of time and the quit menu is
     selected the program needs to be able to write the updated seat 
     availability back out to the file. The obvious place to do this
     is in the TicketManager destructor. [implemented]

#include <iostream>
#include <string>
#include <unordered_map>

struct Seat {
    int seatNumber;
    bool isBooked;
    Seat* next;

    Seat(int num) : seatNumber(num), isBooked(false), next(nullptr) {}
};

struct Compartment {
    std::string compartmentName;
    Seat* seats;
    int totalSeats;
    int bookedSeats;
    Compartment* next;

    Compartment(std::string name, int total) 
        : compartmentName(name), seats(nullptr), totalSeats(total), bookedSeats(0), next(nullptr) {
        for (int i = 1; i <= totalSeats; ++i) {
            Seat* newSeat = new Seat(i);
            newSeat->next = seats;
            seats = newSeat;
        }
    }
};

class Train {
public:
    std::string trainName;
    Compartment* compartments;

    Train(std::string name) : trainName(name), compartments(nullptr) {}

    void addCompartment(std::string name, int totalSeats) {
        Compartment* newCompartment = new Compartment(name, totalSeats);
        newCompartment->next = compartments;
        compartments = newCompartment;
        std::cout << "Compartment " << name << " with " << totalSeats << " seats added.\n";
    }

    void bookSeat(std::string compartmentName) {
        Compartment* comp = findCompartment(compartmentName);
        if (!comp) {
            std::cout << "Compartment not found!\n";
            return;
        }
        Seat* seat = findAvailableSeat(comp);
        if (seat) {
            seat->isBooked = true;
            ++comp->bookedSeats;
            std::cout << "Seat " << seat->seatNumber << " in " << comp->compartmentName << " booked successfully.\n";
        } else {
            std::cout << "No available seats in " << comp->compartmentName << ".\n";
        }
    }

    void cancelSeat(std::string compartmentName, int seatNumber) {
        Compartment* comp = findCompartment(compartmentName);
        if (!comp) {
            std::cout << "Compartment not found!\n";
            return;
        }
        Seat* seat = findSeat(comp, seatNumber);
        if (seat && seat->isBooked) {
            seat->isBooked = false;
            --comp->bookedSeats;
            std::cout << "Seat " << seat->seatNumber << " in " << comp->compartmentName << " canceled successfully.\n";
        } else {
            std::cout << "Seat not booked or invalid seat number.\n";
        }
    }

    void checkAvailability(std::string compartmentName) {
        Compartment* comp = findCompartment(compartmentName);
        if (!comp) {
            std::cout << "Compartment not found!\n";
            return;
        }
        std::cout << "Compartment " << comp->compartmentName << ": "
                  << comp->totalSeats - comp->bookedSeats << " seats available out of "
                  << comp->totalSeats << ".\n";
    }

private:
    Compartment* findCompartment(std::string name) {
        Compartment* temp = compartments;
        while (temp) {
            if (temp->compartmentName == name) return temp;
            temp = temp->next;
        }
        return nullptr;
    }

    Seat* findAvailableSeat(Compartment* comp) {
        Seat* seat = comp->seats;
        while (seat) {
            if (!seat->isBooked) return seat;
            seat = seat->next;
        }
        return nullptr;
    }

    Seat* findSeat(Compartment* comp, int seatNumber) {
        Seat* seat = comp->seats;
        while (seat) {
            if (seat->seatNumber == seatNumber) return seat;
            seat = seat->next;
        }
        return nullptr;
    }
};

int main() {
    Train train("Express Train");
    train.addCompartment("First Class", 5);
    train.addCompartment("Second Class", 10);

    train.bookSeat("First Class");
    train.bookSeat("First Class");
    train.bookSeat("Second Class");

    train.checkAvailability("First Class");
    train.checkAvailability("Second Class");

    train.cancelSeat("First Class", 1);
    train.checkAvailability("First Class");

    return 0;
}



/************************************************************************************************************

Output:

[?2004l
Enter the number of task which you want to enter:5 4
Enter the detail in following order: ID, Priority, Execution TimeEnter the detail of 1th task:1
3
2
Enter the detail of 2th task:2
5
1
Enter the detail of 3th task:3
1
3
Enter the detail of 4th task:4
4
2
Task 1 added to the queue.
Task 2 added to the queue.
Task 3 added to the queue.
Task 4 added to the queue.
Task ID: 2, Priority: 5, Execution Time: 1s
Task ID: 4, Priority: 4, Execution Time: 2s
Task ID: 1, Priority: 3, Execution Time: 2s
Task ID: 3, Priority: 1, Execution Time: 3s
Executing Task ID: 2
Completing Task ID: 2
Task ID: 4, Priority: 4, Execution Time: 2s
Task ID: 1, Priority: 3, Execution Time: 2s
Task ID: 3, Priority: 1, Execution Time: 3s
Executing Task ID: 4
Completing Task ID: 4
Task ID: 1, Priority: 3, Execution Time: 2s
Task ID: 3, Priority: 1, Execution Time: 3s
Executing Task ID: 1
Completing Task ID: 1
Task ID: 3, Priority: 1, Execution Time: 3s
Executing Task ID: 3
Completing Task ID: 3
All tasks completed.

******************************************************************************************************************/

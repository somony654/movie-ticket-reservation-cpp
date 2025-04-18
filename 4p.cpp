#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int ROWS = 5;
const int SEATS = 10;
const int MOVIE_COUNT = 3;

struct Reservation {
    string name;
    string phone;
    int movie;
    int row;
    int seat;
};

class MovieTicketSystem {
private:
    string movies[MOVIE_COUNT] = {"Harry Potter", "Little Women", "Spider Man"};
    char seats[MOVIE_COUNT][ROWS][SEATS]; // Separate seat charts for each movie
    vector<Reservation> reservations;

public:
    MovieTicketSystem() {
        // Initialize all seats for all movies as available ('O')
        for (int m = 0; m < MOVIE_COUNT; m++) {
            for (int i = 0; i < ROWS; i++) {
                for (int j = 0; j < SEATS; j++) {
                    seats[m][i][j] = 'O';
                }
            }
        }
    }

    void displayMovies() {
        cout << "\nAvailable Movies:\n";
        for (int i = 0; i < MOVIE_COUNT; i++) {
            cout << i + 1 << ". " << movies[i] << endl;
        }
    }

    int selectMovie() {
        displayMovies();
        int selectedMovie;
        cout << "Select a movie by entering the corresponding number: ";
        cin >> selectedMovie;
        if (selectedMovie < 1 || selectedMovie > MOVIE_COUNT) {
            cout << "Invalid selection. Please try again.\n";
            return selectMovie();
        } else {
            cout << "You selected: " << movies[selectedMovie - 1] << "\n";
            return selectedMovie - 1; // Return 0-based index
        }
    }

    void displaySeats(int movieIndex) {
        cout << "\nSeat Availability for " << movies[movieIndex] << " (O = Available, X = Booked):\n";
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < SEATS; j++) {
                cout << seats[movieIndex][i][j] << " ";
            }
            cout << endl;
        }
    }

    void reserveSeat(int movieIndex) {
        string name, phone;
        int row, seat;

        cout << "Enter your name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter your phone number: ";
        getline(cin, phone);

        displaySeats(movieIndex);
        cout << "Enter the row (1-" << ROWS << ") and seat number (1-" << SEATS << ") to reserve: ";
        cin >> row >> seat;

        // Validate input
        if (row < 1 || row > ROWS || seat < 1 || seat > SEATS) {
            cout << "Invalid seat selection. Please try again.\n";
            reserveSeat(movieIndex);
        } else if (seats[movieIndex][row - 1][seat - 1] == 'X') {
            cout << "Seat already booked. Please choose a different seat.\n";
            reserveSeat(movieIndex);
        } else {
            // Reserve the seat
            seats[movieIndex][row - 1][seat - 1] = 'X';

            // Record reservation
            Reservation res = {name, phone, movieIndex, row, seat};
            reservations.push_back(res);

            cout << "Seat reserved successfully for " << name << "!\n";
        }
    }

    void showReservations() {
        if (reservations.empty()) {
            cout << "No reservations have been made yet.\n";
        } else {
            cout << "\nCurrent Reservations:\n";
            for (const auto &res : reservations) {
                cout << "Name: " << res.name
                     << ", Phone: " << res.phone
                     << ", Movie: " << movies[res.movie]
                     << ", Seat: Row " << res.row << ", Seat " << res.seat << endl;
            }
        }
    }

    void menu() {
        int choice;
        do {
            cout << "\n--- Movie Ticket Reservation System ---\n";
            cout << "1. Book a Ticket\n";
            cout << "2. View Reservations\n";
            cout << "3. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;
            switch (choice) {
                case 1: {
                    int selectedMovie = selectMovie();
                    reserveSeat(selectedMovie);
                    break;
                }
                case 2:
                    showReservations();
                    break;
                case 3:
                    cout << "Thank you for using the Movie Ticket Reservation System!\n";
                    return;
                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 3);
    }
};

int main() {
    MovieTicketSystem system;
    system.menu();
    return 0;
}
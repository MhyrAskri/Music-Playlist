#include <iostream>
#include <list>
#include <string>
#include <cctype>
#include <iomanip>
#include <limits>

using namespace std;

class Song {

    friend std::ostream &operator<<(std::ostream &os , const Song &s);
    string name;
    string artist;
    int rating;
public:

    Song() = default;
    Song(string name , string artist , int rating)
        : name {name} , artist {artist} , rating {rating} {}

    string getName() const {

        return name;

    }

    string getArtist() const {

        return artist;

    }

    int getRating() const {

        return rating;

    }

    bool operator<(const Song &rhs) const {

        return this->name < rhs.name;

    }

    bool operator==(const Song &rhs) const {

        return this->name == rhs.name;

    }

};

std::ostream &operator<<(std::ostream &os , const Song &s) {

    os << setw(20) << left << s.name
       << setw(30) << left << s.artist
       << setw(2) << left << s.rating;

    return os;

}

void displayMenu() {

    cout << "\nF - Play first song." << endl;
    cout << "N - Play next song." << endl;
    cout << "P - Play previous song." << endl;
    cout << "A - Add and play a new song at current location." << endl;
    cout << "L - List the current playlist." << endl;
    cout << "==============================================================" << endl;
    cout << "Enter a selection (Q to quit):";

}

void playCurrentSong(const Song &song) {

    cout << "Playing:" << endl;
    cout << song << endl;

}

void displayPlaylist(const list<Song> &playlist , const Song &currentSong) {

    for (const Song &song : playlist) {

        cout << song << endl;

    }
    cout << "Current song: " << endl;
    cout << currentSong << endl;

}

int main() {

    list<Song> playlist {

        {"God's Plan" , "Drake" , 5},
        {"Never be the same" , "Camila" , 5},
        {"Pray for me" , "K.Lamar" , 4},
        {"The middle" , "Zedd" , 5},
        {"Wait" , "Maroone" , 4},
        {"Whatever it take" , "Imagine" , 3},

    };

    list<Song>::iterator currentSong = playlist.begin();
    displayPlaylist(playlist , *currentSong);

    char selection{};
    do {

        displayMenu();
        cin >> selection;
        if (selection == 'f' || selection == 'F') {

            cout << "Playing first song" << endl;
            currentSong = playlist.begin();
            playCurrentSong(*currentSong);

        } else if (selection == 'n' || selection == 'N') {

            cout << "Playing next song" << endl;
            currentSong++;
            if (currentSong == playlist.end()) {

                cout << "Wrapping to start of playlist" << endl;
                currentSong = playlist.begin();

            }
            playCurrentSong(*currentSong);

        } else if (selection == 'p' || selection == 'P') {

            cout << "Playing previous song" << endl;
            if (currentSong == playlist.begin()) {

                cout << "Wrapping to end of playlist" << endl;
                currentSong = playlist.end();

            }
            currentSong--;
            playCurrentSong(*currentSong);

        } else if (selection == 'a' || selection == 'A') {

            string name , artist;
            int rating;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max() , '\n');
            cout << "Adding and playing new song" << endl;
            cout << "Enter song name:";
            getline(cin , name);
            cout << "Enter song artist:";
            getline(cin , artist);
            cout << "Enter your rating (1-5):";
            cin >> rating;
            playlist.insert(currentSong , Song{name, artist, rating});
            currentSong--;
            playCurrentSong(*currentSong);

        } else if (selection == 'l' || selection == 'L') {

            cout << endl;
            displayPlaylist(playlist , *currentSong);

        } else if (selection == 'q' || selection == 'Q') {

            cout << "Quiting!!!" << endl;

        } else {

            cout << "Illegal choice, try Again...";

        }

    } while (selection != 'Q' && selection != 'q');

    cout << "Thanks for listening!" << endl;

    return 0;
}

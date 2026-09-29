// =====================================================================
// LDCW6123 Group Project - Part 2: Interactive C++ Program
// Title  : Netflix Movie & Series Recommendation Assistant
// Purpose: Inspired by Netflix's shift to Originals and viewer control
//          (Part 1 poster). The user picks a genre and a format and the
//          program suggests a Netflix Original to watch.
// =====================================================================
#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>
#include <ctime>
using namespace std;

// One entry in our small Netflix Originals catalogue
struct Title {
    string name;         // title shown to the user
    string genre;        // one of the 7 genres in the menu
    bool   isSeries;     // true = series (binge), false = movie
    int    year;         // first release year
    string description;  // one-line summary
};

// Sample data (Netflix Originals only - fits the "Originals" stage of the poster)
const Title catalogue[] = {
    // ---- Action ----
    {"Extraction", "Action", false, 2020, "A black-market mercenary is hired to rescue a kidnapped crime lord's son in Dhaka."},
    {"The Old Guard", "Action", false, 2020, "A team of immortal mercenaries protects the world while a new member joins their ranks."},
    {"6 Underground", "Action", false, 2019, "Six vigilantes who faked their own deaths try to take down the world's worst criminals."},
    {"Money Heist", "Action", true, 2017, "A criminal known as the Professor leads a crew in an elaborate heist on the Royal Mint of Spain."},
    {"The Gray Man", "Action", false, 2022, "A CIA operative becomes a target after uncovering a dangerous secret within his own agency."},
    // ---- Comedy ----
    {"Murder Mystery", "Comedy", false, 2019, "A couple's European vacation turns into a whodunit on a billionaire's yacht."},
    {"Glass Onion: A Knives Out Mystery", "Comedy", false, 2022, "Detective Benoit Blanc investigates a murder at a tech billionaire's private-island getaway."},
    {"Unbreakable Kimmy Schmidt", "Comedy", true, 2015, "A woman rescued from a doomsday cult builds a new life in New York City."},
    {"Big Mouth", "Comedy", true, 2017, "Animated comedy about friends surviving the awkwardness of puberty (mature humour)."},
    // ---- Drama ----
    {"Roma", "Drama", false, 2018, "A domestic worker's life in early-1970s Mexico City, seen through a family's upheaval."},
    {"The Irishman", "Drama", false, 2019, "An aging hitman looks back on his mob ties and the disappearance of Jimmy Hoffa."},
    {"House of Cards", "Drama", true, 2013, "A ruthless US politician schemes his way to power in Washington."},
    {"The Crown", "Drama", true, 2016, "The reign of Queen Elizabeth II and the personal cost of duty."},
    // ---- Sci-Fi ----
    {"Okja", "Sci-Fi", false, 2017, "A girl fights to save her giant super-pig from a powerful corporation."},
    {"The Adam Project", "Sci-Fi", false, 2022, "A time-travelling pilot teams up with his 12-year-old self to save the future."},
    {"Stranger Things", "Sci-Fi", true, 2016, "A boy vanishes in a small Indiana town, exposing secret experiments and a supernatural world."},
    {"The Umbrella Academy", "Sci-Fi", true, 2019, "Estranged adopted siblings with superpowers reunite to stop an apocalypse."},
    // ---- Horror & Thriller ----
    {"Bird Box", "Horror & Thriller", false, 2018, "A mother guides her children blindfolded through a world where seeing a mysterious threat means death."},
    {"Fear Street Part One: 1994", "Horror & Thriller", false, 2021, "Teens in Shadyside uncover a curse tied to their town's dark history."},
    {"Squid Game", "Horror & Thriller", true, 2021, "Cash-strapped players risk their lives in deadly children's games for a huge prize."},
    {"Wednesday", "Horror & Thriller", true, 2022, "Wednesday Addams investigates a mystery while attending Nevermore Academy."},
    {"The Haunting of Hill House", "Horror & Thriller", true, 2018, "Siblings confront the haunted mansion that shaped their childhood."},
    // ---- Romance ----
    {"To All the Boys I've Loved Before", "Romance", false, 2018, "A teen's secret love letters get mailed to her crushes, upending her love life."},
    {"Set It Up", "Romance", false, 2018, "Two overworked assistants plot to set up their bosses so they can get their lives back."},
    {"Bridgerton", "Romance", true, 2020, "Romance and scandal among high-society families in Regency-era London."},
    {"Virgin River", "Romance", true, 2019, "A nurse practitioner starts over in a small California town and finds new love."},
    // ---- Documentary ----
    {"The Social Dilemma", "Documentary", false, 2020, "Tech insiders warn how social media platforms shape behaviour and society."},
    {"Our Planet", "Documentary", true, 2019, "Nature series narrated by David Attenborough on Earth's habitats and climate."},
    {"Making a Murderer", "Documentary", true, 2015, "A documentary series following Steven Avery's murder conviction and its legal aftermath."},
    {"Chef's Table", "Documentary", true, 2015, "Profiles of world-renowned chefs and the passion behind their food."}
};

// Number of titles, worked out automatically from the array size
const int TOTAL_TITLES = sizeof(catalogue) / sizeof(catalogue[0]);

// Display one title in a neat block
void printTitle(const Title& t) {
    cout << "\n  ------------------------------------------------\n";
    cout << "  Title : " << t.name << "\n";
    cout << "  Type  : " << (t.isSeries ? "Series" : "Movie") << " (" << t.year << ")\n";
    cout << "  Genre : " << t.genre << "\n";
    cout << "  About : " << t.description << "\n";
    cout << "  ------------------------------------------------\n";
}

// Ask the user for a whole number between low and high.
// Keeps asking until the input is valid (handles letters, symbols, out-of-range).
int readChoice(const string& prompt, int low, int high) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= low && value <= high) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear rest of line
            return value;
        }
        if (cin.eof()) {                        // input stream closed - stop cleanly
            cout << "\nNo more input. Exiting program.\n";
            exit(0);
        }
        cin.clear();                            // reset the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  Invalid input. Please enter a number from " << low << " to " << high << ".\n";
    }
}

// Show the list of genres
void showGenreMenu() {
    cout << "\nChoose a genre:\n";
    cout << "  1. Action\n  2. Comedy\n  3. Drama\n  4. Sci-Fi\n";
    cout << "  5. Horror & Thriller\n  6. Romance\n  7. Documentary\n";
}

// Convert the menu number into a genre name using a switch statement
string genreFromChoice(int choice) {
    switch (choice) {
        case 1: return "Action";
        case 2: return "Comedy";
        case 3: return "Drama";
        case 4: return "Sci-Fi";
        case 5: return "Horror & Thriller";
        case 6: return "Romance";
        case 7: return "Documentary";
        default: return "";   // should never happen because input is validated
    }
}

// Number of suggestions shown in this session (reported when the user exits)
int recommendationsGiven = 0;

// Collect the catalogue positions that match the genre and format.
// format: 1 = movie only, 2 = series only, 3 = either. Returns how many matched.
int findMatches(const string& genre, int format, int matches[]) {
    int count = 0;
    for (int i = 0; i < TOTAL_TITLES; i++) {
        bool genreOk = (catalogue[i].genre == genre);
        bool formatOk;
        if (format == 1) {
            formatOk = !catalogue[i].isSeries;      // movies only
        } else if (format == 2) {
            formatOk = catalogue[i].isSeries;       // series only
        } else {
            formatOk = true;                        // either
        }
        if (genreOk && formatOk) {
            matches[count] = i;
            count++;
        }
    }
    return count;
}

// Shuffle the matches (Fisher-Yates) so suggestions vary and never repeat
void shuffleMatches(int matches[], int count) {
    for (int i = count - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = matches[i];
        matches[i] = matches[j];
        matches[j] = temp;
    }
}

// Ask for genre + format, then show matches one at a time
void recommendByGenre() {
    showGenreMenu();
    int g = readChoice("Pick a genre (1-7): ", 1, 7);
    string genre = genreFromChoice(g);

    cout << "\nWhat do you feel like watching?\n";
    cout << "  1. A movie (one sitting)\n  2. A series (binge-watch)\n  3. Either\n";
    int format = readChoice("Your choice (1-3): ", 1, 3);

    int matches[TOTAL_TITLES];
    int count = findMatches(genre, format, matches);
    if (count == 0) {
        cout << "\nSorry, no titles match that combination.\n";
        return;
    }
    shuffleMatches(matches, count);
    cout << "\nFound " << count << " match(es) in " << genre << ". Here is my pick:\n";

    for (int shown = 0; shown < count; shown++) {
        printTitle(catalogue[matches[shown]]);
        recommendationsGiven++;

        if (shown == count - 1) {                   // no more titles left
            cout << "\nThat's every match for your choices.\n";
            break;
        }
        cout << "\nWant another suggestion?\n  1. Yes\n  2. No, I'll watch this one\n";
        if (readChoice("Your choice (1-2): ", 1, 2) == 2) {
            cout << "\nEnjoy the show!\n";
            break;
        }
    }
}

// Pick any title at random from the whole catalogue
void surpriseMe() {
    int index = rand() % TOTAL_TITLES;
    cout << "\nHere's a surprise pick:\n";
    printTitle(catalogue[index]);
    recommendationsGiven++;
}

// Netflix timeline - mirrors the stages on the Part 1 poster
void showTimeline() {
    cout << "\nNetflix Innovation Timeline (from our Part 1 poster):\n";
    cout << "  1. Founded\n  2. Subscription\n  3. Streaming\n";
    cout << "  4. Originals\n  5. DVD End\n  6. Digital\n  7. Back to main menu\n";
    int stage = readChoice("Pick a stage (1-7): ", 1, 7);

    switch (stage) {
        case 1:
            cout << "\n[1997] Founded on 29 Aug 1997 by Reed Hastings and Marc Randolph.\n"
                 << "  Started as pay-per-rental DVDs by mail, challenging video stores.\n";
            break;
        case 2:
            cout << "\n[1999] Monthly subscription introduced.\n"
                 << "  Unlimited rentals with no due dates and no late fees.\n";
            break;
        case 3:
            cout << "\n[2007] Streaming launched.\n"
                 << "  \"Watch instantly\" let members stream over the internet.\n";
            break;
        case 4:
            cout << "\n[2013] Netflix Originals begin to take off.\n"
                 << "  House of Cards released a whole season at once and popularised binge-watching.\n"
                 << "  Try it: choose Drama > Series in the recommender!\n";
            break;
        case 5:
            cout << "\n[Sep 2023] DVD-by-mail service closed.\n"
                 << "  The final red envelope shipped, completing the move to digital.\n";
            break;
        case 6:
            cout << "\n[Today] Digital-only entertainment platform.\n"
                 << "  On-demand viewing on any device, plus games and live events.\n";
            break;
        case 7:
            return;                                     // back to main menu
    }
}

void printBanner() {
    cout << "==================================================\n";
    cout << "   NETFLIX RECOMMENDATION ASSISTANT (C++)\n";
    cout << "   Inspired by Netflix Originals & viewer control\n";
    cout << "==================================================\n";
}

void showMainMenu() {
    cout << "\nMAIN MENU\n";
    cout << "  1. Find a movie or series by genre\n";
    cout << "  2. Surprise me\n";
    cout << "  3. Netflix timeline (Part 1 poster)\n";
    cout << "  4. Exit\n";
}

int main() {
    srand(static_cast<unsigned>(time(0)));
    printBanner();

    int choice;
    do {
        showMainMenu();
        choice = readChoice("Enter your choice (1-4): ", 1, 4);
        switch (choice) {
            case 1: recommendByGenre(); break;
            case 2: surpriseMe();       break;
            case 3: showTimeline();     break;
            case 4:
                cout << "\nYou viewed " << recommendationsGiven << " recommendation(s) this session.\n";
                cout << "Goodbye and happy streaming!\n";
                break;
        }
    } while (choice != 4);
    return 0;
}

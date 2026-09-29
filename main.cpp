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

int main() {
    cout << "Catalogue loaded: " << TOTAL_TITLES << " titles.\n";
    printTitle(catalogue[0]);          // quick check that the data prints correctly
    return 0;
}

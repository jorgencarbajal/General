#include <iostream>     // Include for input/output operations (e.g., printing to console)
#include <vector>       // Include for using std::vector to store Goblin objects
#include <algorithm>    // Include for using std::sort algorithm

struct Goblin {
    int mHealth;        // Member variable to store the goblin's health points
    int mStrength;      // Member variable to store the goblin's strength

    Goblin(int h, int s) : mHealth(h), mStrength(s) {}  // Constructor to initialize mHealth and mStrength

    bool operator<(const Goblin& rhs) {                 // Overloads the < operator to compare goblins by mHealth
        return this->mHealth < rhs.mHealth;             // Returns true if this goblin's health is less than the other's
    }
};

struct GoblinComparator {
    bool operator()(const Goblin& lhs, const Goblin& rhs) const {  // Overloads () operator to compare goblins by mStrength
        return lhs.mStrength < rhs.mStrength;                      // Returns true if lhs goblin's strength is less than rhs's
    }                                                             // 'const' ensures the comparator doesn't modify objects
};

int main() {
    std::vector<Goblin> goblins{ Goblin(5, 205), Goblin(3, 25) };  // Create a vector and initialize with two Goblins:
                                                                  // First: 5 health, 205 strength; Second: 3 health, 25 strength

    std::sort(goblins.begin(), goblins.end(), GoblinComparator()); // Sort the vector using GoblinComparator (by mStrength)
                                                                  // Result: [Goblin(3, 25), Goblin(5, 205)] since 25 < 205

    for(auto g : goblins) {                                       // Loop through each goblin in the sorted vector
        std::cout << g.mHealth << " " << std::endl;               // Print the health of each goblin on a new line
                                                                  // Output: 3\n5\n (since sorted by strength, not health)
    }
    return 0;                                                    // Indicate successful program completion
}
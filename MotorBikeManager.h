#pragma once

#include <string>
#include <vector>
#include "Motorbike.h" // Include the Motorbike class definition.
using namespace std;

// Class that handles motorbikes' storage in file
class MotorbikeManager {
private:
    string fileName;
    vector<Motorbike> motorbikes;

    // Private method to get the maximum ID among motorbikes.
    int getMaxID() const;

public:
    // Constructor that takes a file name.
    MotorbikeManager(const string& _fileName);

    // Load motorbike data from a file.
    void loadMotorbikesFromFile();

    // Add a motorbike to the manager.
    void addMotorbike(const Motorbike& motorbike);

    // Get the next available member ID.
    int getNextMemberID() const;

    // Update information for a motorbike.
    void updateBike(const Motorbike& bike);

    // Get a motorbike by its ID.
    Motorbike getMotorBikeByID(int id) const;

    // Show motorbikes from a specific city for a user.
    int showMotorbikesFromCity(const User& user, const string& city);

    // Get a motorbike by its index in the manager.
    Motorbike getMotorBikeByIndex(int idx) const;

    // Save motorbike data to a file.
    void saveMotorbikesToFile() const;

    // Show information for all motorbikes in the manager.
    void showAllBikes();

    // Show motorbikes for a specific user.
    int showMotorbikesForUser(const User& user);
};

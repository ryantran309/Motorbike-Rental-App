#include "MotorbikeManager.h"
#include "ReviewManager.h"
#include "RequestManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm> 
#include <iomanip>

int MotorbikeManager::getMaxID() const
{

    // returns max ID among the saved Bikes

    int maxID = -1; 

    for (const Motorbike& obj : motorbikes)
    {
        if (obj.getID() > maxID)
        {
            maxID = obj.getID();
        }
    }

    return maxID;
}

// Constructor
MotorbikeManager::MotorbikeManager(const string& _fileName) : fileName(_fileName)
{
    loadMotorbikesFromFile(); 
}

void MotorbikeManager::loadMotorbikesFromFile() 
{
    // Loads bike data into vector from a file with comma-seperated data

    RequestManager rm("requests.txt");
    ReviewManager reviewM("reviews.txt");
    ifstream file(fileName);
    if (!file.is_open()) {
        cerr << "Error: Unable to open motorbike file." << endl;
        exit(0);
    }

    string line;
    while (getline(file, line)) 
    {
        // Reads each line into stringstream (string which can be used as stream)
        // and makes tokens by delimiting commas and make a motorbike object

        istringstream iss(line);
        vector<string> tokens;
        string token;

        while (getline(iss, token, ','))
        {
            tokens.push_back(token);
        }

        if (tokens.size() == 13) {
            int id = stoi(tokens[0]);
            string model = tokens[1];
            string color = tokens[2];
            int engineSize = stoi(tokens[3]);
            string transmissionMode = tokens[4];
            int yearMade = stoi(tokens[5]);
            string description = tokens[6];
            int consumePointsPerDay = stoi(tokens[7]);
            int minimumRenterRating = stoi(tokens[8]);
            float motorbikeRating = stof(tokens[9]);
            bool isAvailable = (tokens[10] == "1"); 
            string location = tokens[11];
            int ownerID = stoi(tokens[12]);

            Motorbike motorbike(id, model, color, engineSize, transmissionMode, yearMade, description,
                consumePointsPerDay, minimumRenterRating, location, motorbikeRating, isAvailable, ownerID);
            vector<RentalRequest> requests = rm.filterByID(ownerID);
            for (auto i : requests)
                motorbike.addRentalRequest(
                    i.getRequesterID(),
                    i.getRequesterUsername(),
                    i.getStartTime(),
                    i.getEndTime()
                );
            vector<Review> reviews = reviewM.getReviewsByID(id);
            for (auto i : reviews)
                motorbike.addReview(i);
           
            motorbikes.push_back(motorbike);
        }
        else {
            cerr << "Error parsing line: " << line << endl;
        }
    }

    file.close();

}

void MotorbikeManager::addMotorbike(const Motorbike& motorbike) 
{
    // Adds motorbike to the vector list

    motorbikes.push_back(motorbike);
}

int MotorbikeManager::getNextMemberID() const
{
    return getMaxID() + 1;
}

void MotorbikeManager::unlistBikeByID(int ID)
{
    auto it = motorbikes
        .begin();
    while (it != motorbikes.end()) {
        if (it->getID() == ID) {
            it = motorbikes.erase(it);
        }
        else {
            ++it;
        }
    }
}

void MotorbikeManager::updateBike(const Motorbike& bike)
{
    // Updates the bike data which matches with the passed-in bike object

    for (int i = 0; i < motorbikes.size(); i++)
    {
        if (bike.getID() == motorbikes[i].getID())
        {
            motorbikes[i].setModel(bike.getModel());
            motorbikes[i].setColor(bike.getColor());
            motorbikes[i].setEngineSize(bike.getEngineSize());
            motorbikes[i].setTransmissionMode(bike.getTransmissionMode());
            motorbikes[i].setYearMade(bike.getYearMade());
            motorbikes[i].setDescription(bike.getDescription());
            motorbikes[i].setConsumePointsPerDay(bike.getConsumePointsPerDay());
            motorbikes[i].setMinimumRenterRating(bike.getMinimumRenterRating());
            motorbikes[i].setLocation(bike.getLocation());
            motorbikes[i].setMotorbikeRating(bike.getMotorbikeRating());
            motorbikes[i].setAvailable(bike.isAvailableForRent());
            vector<RentalRequest> requests = bike.getRentalRequests();
            vector<Review> reviews = bike.getReviews();
            if (requests.size() == 0)
            {
                motorbikes[i].emptyRequest();
            }
            else
            {
                for (auto r : requests)
                {
                    motorbikes[i].addRentalRequest(
                        r.getRequesterID(),
                        r.getRequesterUsername(),
                        r.getStartTime(),
                        r.getEndTime()
                    );
                }
            }
            for (auto r : reviews)
            {
                motorbikes[i].addReview(r);
            }
        }
    }
}

Motorbike MotorbikeManager::getMotorBikeByID(int id) const
{
    // Returns motorbike object with given ID if it exists

    for (Motorbike obj : motorbikes)
    {
        if (id == obj.getID())
            return obj;
    }
    return Motorbike(-1, "", "", 0, "", 0, "", 0, 0, "");
}

Motorbike MotorbikeManager::getMotorBikeByIndex(int idx) const
{
    if (idx > -1 && idx < motorbikes.size())
    {
        Motorbike bike = motorbikes[idx];
        return bike;
    }
    return Motorbike(-1, "", "", 0, "", 0, "", 0, 0, "");
}

void MotorbikeManager::saveMotorbikesToFile() const 
{
    // Saves bikes' data to the file in comma-seperated format

    ofstream file(fileName);
    if (!file.is_open()) {
        cerr << "Error: Unable to open motorbike file for writing." << endl;
        return;
    }

    for (const Motorbike& motorbike : motorbikes)
    {
        file << motorbike.getID() << ","
            << motorbike.getModel() << ","
            << motorbike.getColor() << ","
            << motorbike.getEngineSize() << ","
            << motorbike.getTransmissionMode() << ","
            << motorbike.getYearMade() << ","
            << motorbike.getDescription() << ","
            << motorbike.getConsumePointsPerDay() << ","
            << motorbike.getMinimumRenterRating() << ","
            << motorbike.getMotorbikeRating() << ","
            << motorbike.isAvailableForRent() << ","
            << motorbike.getLocation() << ","
            << motorbike.getOwnerID() << endl;
    }

    file.close();
}

void MotorbikeManager::showAllBikes() {
    cout << "All Available Motorbikes:" << endl;
    cout << "========================================================================================================================================" << endl;
    cout << left << setw(3) << "ID" << "  "
        << left << setw(10) << "Model" << "  "
        << left << setw(8) << "Color" << "  "
        << left << setw(11) << "Engine Size" << "  "
        << left << setw(13) << "Transmission" << "  "
        << left << setw(9) << "Year Made" << "  "
        << left << setw(12) << "Consume/Day" << "  "
        << left << setw(10) << "Min Rating" << "  " 
        << left << setw(6) << "Rating" << "  " 
        << left << setw(9) << "Available" << "  " 
        << left << setw(10) << "Location" << "  " 
        << left << setw(8) << "Owner ID" << "  " 
        << left << setw(15) << "Description" << endl;
    cout << "========================================================================================================================================" << endl;

    for (const Motorbike& motorbike : motorbikes) {
        cout << left << setw(3) << motorbike.getID() << "  " 
            << left << setw(10) << motorbike.getModel() << "  " 
            << left << setw(8) << motorbike.getColor() << "  " 
            << left << setw(11) << motorbike.getEngineSize() << "  " 
            << left << setw(13) << motorbike.getTransmissionMode() << "  " 
            << left << setw(9) << motorbike.getYearMade() << "  " 
            << left << setw(12) << motorbike.getConsumePointsPerDay() << "  " 
            << left << setw(10) << motorbike.getMinimumRenterRating() << "  " 
            << left << setw(6) << motorbike.getMotorbikeRating() << "  " 
            << left << setw(9) << (motorbike.isAvailableForRent() ? "Yes" : "No") << "  " 
            << left << setw(10) << motorbike.getLocation() << "  " 
            << left << setw(8) << motorbike.getOwnerID() << "  " 
            << left << setw(15) << motorbike.getDescription() << endl;
    }

    cout << "========================================================================================================================================" << endl;
}

int MotorbikeManager::showMotorbikesForUser(const User& user) {
    int count = 0;
    cout << "Motorbikes Available for User: " << user.getUsername() << endl;
    cout << "========================================================================================================================================" << endl;
    cout << left << setw(3) << "ID" << "  " 
        << left << setw(10) << "Model" << "  " 
        << left << setw(8) << "Color" << "  " 
        << left << setw(11) << "Engine Size" << "  " 
        << left << setw(13) << "Transmission" << "  " 
        << left << setw(9) << "Year Made" << "  " 
        << left << setw(12) << "Consume/Day" << "  " 
        << left << setw(10) << "Min Rating" << "  " 
        << left << setw(6) << "Rating" << "  " 
        << left << setw(9) << "Available" << "  " 
        << left << setw(10) << "Location" << "  " 
        << left << setw(8) << "Owner ID" << "  " 
        << left << setw(15) << "Description" << endl;
    cout << "========================================================================================================================================" << endl;

    for (const Motorbike& motorbike : motorbikes) {
        if (user.getCreditPoints() >= motorbike.getConsumePointsPerDay() &&
            user.getRenterRating() >= motorbike.getMinimumRenterRating() &&
            motorbike.isAvailableForRent() &&
            motorbike.getOwnerID() != user.getID()) {
            cout << "Bike no. " << ++count << endl;
            cout << left << setw(3) << motorbike.getID() << "  " 
                << left << setw(10) << motorbike.getModel() << "  " 
                << left << setw(8) << motorbike.getColor() << "  " 
                << left << setw(11) << motorbike.getEngineSize() << "  " 
                << left << setw(13) << motorbike.getTransmissionMode() << "  " 
                << left << setw(9) << motorbike.getYearMade() << "  " 
                << left << setw(12) << motorbike.getConsumePointsPerDay() << "  " 
                << left << setw(10) << motorbike.getMinimumRenterRating() << "  " 
                << left << setw(6) << motorbike.getMotorbikeRating() << "  " 
                << left << setw(9) << (motorbike.isAvailableForRent() ? "Yes" : "No") << "  " 
                << left << setw(10) << motorbike.getLocation() << "  " 
                << left << setw(8) << motorbike.getOwnerID() << "  " 
                << left << setw(15) << motorbike.getDescription() << endl;
            cout << "========================================================================================================================================" << endl;
        }
    }
    return count;
}

int MotorbikeManager::showMotorbikesFromCity(const User& user, const string& city) {
    int count = 0;
    cout << "Motorbikes Available for User: " << user.getUsername() << endl;
    cout << "========================================================================================================================================" << endl;
    cout << left << setw(3) << "ID" << "  "
        << left << setw(10) << "Model" << "  "
        << left << setw(8) << "Color" << "  "
        << left << setw(11) << "Engine Size" << "  "
        << left << setw(13) << "Transmission" << "  "
        << left << setw(9) << "Year Made" << "  "
        << left << setw(12) << "Consume/Day" << "  "
        << left << setw(10) << "Min Rating" << "  "
        << left << setw(6) << "Rating" << "  "
        << left << setw(9) << "Available" << "  "
        << left << setw(10) << "Location" << "  "
        << left << setw(8) << "Owner ID" << "  "
        << left << setw(15) << "Description" << endl;
    cout << "========================================================================================================================================" << endl;

    for (const Motorbike& motorbike : motorbikes) {
        if (user.getCreditPoints() >= motorbike.getConsumePointsPerDay() &&
            user.getRenterRating() >= motorbike.getMinimumRenterRating() &&
            motorbike.isAvailableForRent() &&
            motorbike.getOwnerID() != user.getID() &&
            motorbike.getLocation() == city) {
            cout << "Bike no. " << ++count << endl;
            cout << left << setw(3) << motorbike.getID() << "  "
                << left << setw(10) << motorbike.getModel() << "  "
                << left << setw(8) << motorbike.getColor() << "  "
                << left << setw(11) << motorbike.getEngineSize() << "  "
                << left << setw(13) << motorbike.getTransmissionMode() << "  "
                << left << setw(9) << motorbike.getYearMade() << "  "
                << left << setw(12) << motorbike.getConsumePointsPerDay() << "  "
                << left << setw(10) << motorbike.getMinimumRenterRating() << "  "
                << left << setw(6) << motorbike.getMotorbikeRating() << "  "
                << left << setw(9) << (motorbike.isAvailableForRent() ? "Yes" : "No") << "  "
                << left << setw(10) << motorbike.getLocation() << "  "
                << left << setw(8) << motorbike.getOwnerID() << "  "
                << left << setw(15) << motorbike.getDescription() << endl;
            cout << "========================================================================================================================================" << endl;
        }
    }
    return count;
}

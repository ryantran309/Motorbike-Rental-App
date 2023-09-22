#include "UserManager.h"
#include <fstream>
#include <sstream>
#include <iomanip>

int UserManager::getMaxID() const
{
    int maxID = -1;

    for (const User& obj : users)
    {
        if (obj.getID() > maxID)
        {
            maxID = obj.getID();
        }
    }

    return maxID;
}

UserManager::UserManager(const string& _filename) : fileName(_filename)
{
    loadUsersFromFile();
    loggedInUserID = -1;
}

void UserManager :: loadUsersFromFile() 
{

    // Follows same logic from motorbike manager but with users' data

    ifstream file(fileName);
    if (!file.is_open()) {
        cerr << "Error: Unable to open user file." << endl;
        exit(0);
    }

    string line;
    while (getline(file, line)) 
    {
        istringstream iss(line);
        vector<string> tokens;
        string token;

        while (getline(iss, token, ',')) 
        { 
            tokens.push_back(token);
        }
        if (tokens.size() == 16)
        { 
            int id = stoi(tokens[0]);
            int creditPoints = stoi(tokens[9]);
            int motorbikeID = stoi(tokens[10]);
            float motorbikeRating = stof(tokens[11]);
            float renterRating = stof(tokens[12]);
            bool isMember = (tokens[13] == "1");
            bool hasRented = (tokens[14] == "1");
            int rentedID = stoi(tokens[15]);

            User user(id, tokens[1], tokens[2], tokens[3], tokens[4], tokens[5], tokens[6], tokens[7], tokens[8], creditPoints, motorbikeID, motorbikeRating, renterRating, isMember, hasRented, rentedID);
            users.push_back(user);
        }
        else {
            cerr << "Error parsing line: " << line << endl;
        }
    }

    file.close();
}

bool UserManager::logIn(const string& username, const string& password)
{
    // Logs in the user if given username and password exists

    for (const User& obj : users)
    {
        if (obj.getUsername() == username && obj.checkPassword(password))
        {
            loggedInUserID = obj.getID();
            return true;
        }
    }
    return false;
}

int UserManager::getNextID() const
{
    return getMaxID() + 1;
}

void UserManager::addUser(const User& user)
{
    users.push_back(user);
}

int UserManager::getLoggedInUserID() const
{
    return loggedInUserID;
}

void UserManager::updateUser(const User& user)
{
    // Updates the user object which matches the passed-in user object

    for (int i = 0; i < users.size(); i++)
    {
        if (users[i].getID() == user.getID())
        {
            users[i].setFullName(user.getFullName());
            users[i].setPhoneNumber(user.getPhoneNumber());
            users[i].setIdType(user.getIdType());
            users[i].setIdNumber(user.getIdNumber());
            users[i].setDriverLicenseNumber(user.getDriverLicenseNumber());
            users[i].setLicenseExpiryDate(user.getLicenseExpiryDate());
            users[i].setCreditPoints(user.getCreditPoints());
            users[i].setMotorbikeID(user.getMotorbikeID());
            users[i].setMotorbikeRating(user.getMotorbikeRating());
            users[i].setRenterRating(user.getRenterRating());
            users[i].setHasRented(user.userHasRented());
            users[i].setRentedBikeID(user.getRentedBikeID());
        }
    }
}

User UserManager::getUserByID(int id) const
{
    for (auto obj : users)
    {
        if (id == obj.getID())
            return obj;
    }
    return User(-1, "", "", "", "", "", "", "", "");
}

bool UserManager::logOut()
{
    if (loggedInUserID == -1)
        return false;
    loggedInUserID = -1;
    return true;
}

void UserManager::showAllUsers()
{
    std::cout << "All Available Users:" << std::endl;
    std::cout << "========================================================================================================================================" << std::endl;
    std::cout << std::left << std::setw(5) << "ID" << "  " 
        << std::left << std::setw(8) << "Username" << "  " 
        << std::left << std::setw(10) << "Full Name" << "  " 
        << std::left << std::setw(13) << "Phone No" << "  " 
        << std::left << std::setw(9) << "ID Type" << "  " 
        << std::left << std::setw(15) << "ID number" << "  " 
        << std::left << std::setw(15) << "License No." << "  " 
        << std::left << std::setw(7) << "Credits" << "  " 
        << std::left << std::setw(3) << "MID" << "  " 
        << std::left << std::setw(13) << "Bike Ratings" << "  " 
        << std::left << std::setw(11) << "Has rented" << "  " 
        << std::left << std::setw(11) << "Rented ID" << std::endl;
    std::cout << "========================================================================================================================================" << std::endl;

    for (const User& user : users) {
        std::cout << std::left << std::setw(5) << user.getID() << "  " 
            << std::left << std::setw(8) << user.getUsername() << "  " 
            << std::left << std::setw(10) << user.getFullName() << "  " 
            << std::left << std::setw(13) << user.getPhoneNumber() << "  " 
            << std::left << std::setw(9) << user.getIdType() << "  " 
            << std::left << std::setw(15) << user.getIdNumber() << "  " 
            << std::left << std::setw(15) << user.getDriverLicenseNumber() << "  " 
            << std::left << std::setw(7) << user.getCreditPoints() << "  " 
            << std::left << std::setw(3) << user.getMotorbikeID() << "  " 
            << std::left << std::setw(13) << user.getMotorbikeRating() << "  " 
            << std::left << std::setw(11) << user.userHasRented() << "  " 
            << std::left << std::setw(15) << user.getRentedBikeID() << std::endl;
    }

    std::cout << "========================================================================================================================================" << std::endl;
}

void UserManager :: saveUsersToFile() {
    ofstream file(fileName);
    if (!file.is_open()) {
        cerr << "Error: Unable to open user file for writing." << endl;
        return;
    }

    for (const User& user : users) {
        // Serialize the User object to comma-separated data
        file << user.getID() << ","
            << user.getUsername() << ","
            << user.getPassword() << ","
            << user.getFullName() << ","
            << user.getPhoneNumber() << ","
            << user.getIdType() << ","
            << user.getIdNumber() << ","
            << user.getDriverLicenseNumber() << ","
            << user.getLicenseExpiryDate() << ","
            << user.getCreditPoints() << ","
            << user.getMotorbikeID() << ","
            << user.getMotorbikeRating() << ","
            << user.getRenterRating() << ","
            << user.IsMember() << ","
            << user.userHasRented() << ","
            << user.getRentedBikeID() << endl;
    }

    file.close();
}

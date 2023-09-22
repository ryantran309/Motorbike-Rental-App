#pragma once
#include "User.h"
#include <vector>
#include <string>

// Class that handles users' storage in file
class UserManager {
    string fileName;          // File name for data storage.
    vector<User> users;       // Vector to store user data.
    int loggedInUserID;       // ID of the currently logged-in user.

    // Private method to get the maximum ID among users.
    int getMaxID() const;

public:
    // Constructor to initialize a UserManager object.
    UserManager(const string& _filename);

    // Load user data from a file.
    void loadUsersFromFile();

    // Log in a user given a username and password.
    bool logIn(const string& username, const string& password);

    // Get the next available user ID.
    int getNextID() const;

    // Add a user to the manager.
    void addUser(const User& user);

    // Get the ID of the currently logged-in user.
    int getLoggedInUserID() const;

    // Update user information.
    void updateUser(const User& user);

    // Get a user by their ID.
    User getUserByID(int id) const;

    // Log out the currently logged-in user.
    bool logOut();

    // Display information for all users.
    void showAllUsers();

    // Save user data to a file.
    void saveUsersToFile();
};

#pragma once
#include <iostream>
#include "Motorbike.h"
using namespace std;

class User {
private:
    // Private member variables to store user information.
    int id;
    string username;
    string password;
    string fullName;
    string phoneNumber;
    string idType;
    string idNumber;
    string driverLicenseNumber;
    string licenseExpiryDate;
    int creditPoints;
    int motorbikeID;
    float motorbikeRating;
    float renterRating;
    bool isMember;
    bool hasRented;
    int rentedBikeID;

public:
    // Constructor to initialize a User object.
    User(int id, const string& _username, const string& _password, const string& _fullName,
        const string& _phoneNumber, const string& _idType, const string& _idNumber,
        const string& _driverLicenseNumber, const string& _licenseExpiryDate,
        int _creditPoints = 20, int _motorbikeID = -1, float _motorbikeRating = 0.0,
        float _renterRating = 10.0, bool _isMember = true, bool _hasRented = false,
        int _rentedBikeID = -1);

    // Getters to access the private member variables.
    int getID() const;
    string getUsername() const;
    string getFullName() const;
    string getPassword() const;
    string getPhoneNumber() const;
    string getIdType() const;
    string getIdNumber() const;
    string getDriverLicenseNumber() const;
    string getLicenseExpiryDate() const;
    int getCreditPoints() const;
    int getMotorbikeID() const;
    float getMotorbikeRating() const;
    float getRenterRating() const;
    bool IsMember() const;
    bool userHasRented() const;
    int getRentedBikeID() const;

    // Setters to modify the private member variables.
    void setFullName(const string& _fullName);
    void setPhoneNumber(const string& _phoneNumber);
    void setIdType(const string& _idType);
    void setIdNumber(const string& _idNumber);
    void setDriverLicenseNumber(const string& _driverLicenseNumber);
    void setLicenseExpiryDate(const string& _licenseExpiryDate);
    void setCreditPoints(int _creditPoints);
    void setMotorbikeID(int _motorbikeID);
    void setMotorbikeRating(float _motorbikeRating);
    void setRenterRating(float _renterRating);
    void setHasRented(bool _hasRented);
    void setRentedBikeID(int _id);

    // Method to check if a password matches the user's password.
    bool checkPassword(const string& _password) const;

    // Static method to register a new member.
    static User registerMember(const string& _username, const string& _password,
        const string& _fullName, const string& _phoneNumber,
        const string& _idType, const string& _idNumber,
        const string& _driverLicenseNumber, const string& _licenseExpiryDate);

    // Method to display user information.
    void showUserInformation() const;
};

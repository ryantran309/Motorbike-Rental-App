#include "User.h"
#include "MotorBikeManager.h"
#include "UserManager.h"
#include <iomanip>

// Implement constructor for member users
User::User(int _id,
    const string& _username,
    const string& _password,
    const string& _fullName,
    const string& _phoneNumber,
    const string& _idType,
    const string& _idNumber,
    const string& _driverLicenseNumber,
    const string& _licenseExpiryDate,
    const int _creditPoints,
    const int _motorbikeID,
    const float _motorbikeRating,
    const float _renterRating,
    const bool _isMember,
    const bool _hasRented,
    const int _rentedBikeID)
    : id(_id),
    username(_username),
    password(_password),
    fullName(_fullName),
    phoneNumber(_phoneNumber),
    idType(_idType),
    idNumber(_idNumber),
    driverLicenseNumber(_driverLicenseNumber),
    licenseExpiryDate(_licenseExpiryDate),
    creditPoints(_creditPoints),
    motorbikeID(_motorbikeID),
    motorbikeRating(_motorbikeRating),
    renterRating(_renterRating),
    isMember(_isMember),
    hasRented(_hasRented),
    rentedBikeID(_rentedBikeID){
}

// Getters
string User::getUsername() const {
    return username;
}

string  User::getFullName() const {
    return fullName;
}

string User::getPassword() const
{
    return password;
}

string  User::getPhoneNumber() const {
    return phoneNumber;
}

string  User::getIdType() const {
    return idType;
}

string  User::getIdNumber() const {
    return idNumber;
}

string  User::getDriverLicenseNumber() const {
    return driverLicenseNumber;
}

string  User::getLicenseExpiryDate() const {
    return licenseExpiryDate;
}

int  User::getCreditPoints() const {
    return creditPoints;
}

int User::getMotorbikeID() const {
    return motorbikeID;
}

int User::getID() const {
    return id;
}

float  User::getMotorbikeRating() const {
    MotorbikeManager manager("bikes.txt");
    Motorbike bike = manager.getMotorBikeByID(motorbikeID);
    return bike.getMotorbikeRating();
}

float  User::getRenterRating() const {
    return renterRating;
}

bool User::IsMember() const {
    return isMember;
}

int User::getRentedBikeID() const
{
    return rentedBikeID;
}

bool User::userHasRented() const
{
    return hasRented;
}

// Setters
void  User::setFullName(const string& _fullName) {
    fullName = _fullName;
}

void  User::setPhoneNumber(const string& _phoneNumber) {
    phoneNumber = _phoneNumber;
}

void  User::setIdType(const string& _idType) {
    idType = _idType;
}

void  User::setIdNumber(const string& _idNumber) {
    idNumber = _idNumber;
}

void  User::setDriverLicenseNumber(const string& _driverLicenseNumber) {
    driverLicenseNumber = _driverLicenseNumber;
}

void  User::setLicenseExpiryDate(const string& _licenseExpiryDate) {
    licenseExpiryDate = _licenseExpiryDate;
}

void  User::setCreditPoints(int _creditPoints) {
    creditPoints = _creditPoints;
}

void  User::setMotorbikeID(int _motorbikeID) {
    motorbikeID = _motorbikeID;
}

void  User::setMotorbikeRating(float _motorbikeRating) {
    motorbikeRating = _motorbikeRating;
}

void  User::setRenterRating(float _renterRating) {
    renterRating = _renterRating;
}

void User::setHasRented(bool _hasRented)
{
    hasRented = _hasRented;
}

void User::setRentedBikeID(int _id)
{
    rentedBikeID = _id;
}

bool User::checkPassword(const string& _password) const
{
    return password == _password;
}

User User::registerMember(const string& _username,
    const string& _password,
    const string& _fullName,
    const string& _phoneNumber,
    const string& _idType,
    const string& _idNumber,
    const string& _driverLicenseNumber,
    const string& _licenseExpiryDate) {
    UserManager um("users.txt");
    User user(um.getNextID(), _username, _password, _fullName, _phoneNumber, _idType, _idNumber, _driverLicenseNumber, _licenseExpiryDate);
    return user;
}

void User::showUserInformation() const {
    std::cout << "User Information:" << std::endl;
    std::cout << "------------------" << std::endl;
    std::cout << "Username: " << username << std::endl;
    std::cout << "Full Name: " << fullName << std::endl;
    std::cout << "Phone Number: " << phoneNumber << std::endl;
    std::cout << "ID Type: " << idType << std::endl;
    std::cout << "ID/Passport Number: " << idNumber << std::endl;
    std::cout << "Driver's License Number: " << driverLicenseNumber << std::endl;
    std::cout << "License Expiry Date: " << licenseExpiryDate << std::endl;
    std::cout << "Credit Points: " << creditPoints << std::endl;
    std::cout << "Motorbike ID: " << motorbikeID << std::endl;
    std::cout << "Motorbike Rating: " << std::fixed << std::setprecision(2) << getMotorbikeRating() << std::endl;
    std::cout << "Renter Rating: " << std::fixed << std::setprecision(2) << renterRating << std::endl;
    std::cout << "------------------" << std::endl;
}







#define _CRT_SECURE_NO_WARNINGS
#include "Motorbike.h"
#include "User.h"
#include "UserManager.h"

// Constructor
Motorbike::Motorbike(int _id,
    const string& _model,
    const string& _color,
    int _engineSize,
    const string& _transmissionMode,
    int _yearMade,
    const string& _description,
    int _consumePointsPerDay,
    int _minimumRenterRating,
    string _location,
    float _motorbikeRating,
    bool _isAvailable,      
    int _ownerID)
    : id(_id),
    model(_model),
    color(_color),
    engineSize(_engineSize),
    transmissionMode(_transmissionMode),
    yearMade(_yearMade),
    description(_description),
    consumePointsPerDay(_consumePointsPerDay),
    minimumRenterRating(_minimumRenterRating),
    location(_location),
    motorbikeRating(_motorbikeRating),
    isAvailable(_isAvailable),
    ownerID(_ownerID) {
}

//  Getters and Setters

string Motorbike::getModel() const {
    return model;
}

string Motorbike::getColor() const {
    return color;
}

int Motorbike::getEngineSize() const {
    return engineSize;
}

string Motorbike::getTransmissionMode() const {
    return transmissionMode;
}

int Motorbike::getYearMade() const {
    return yearMade;
}

string Motorbike::getDescription() const {
    return description;
}

int Motorbike::getConsumePointsPerDay() const {
    return consumePointsPerDay;
}

int Motorbike::getMinimumRenterRating() const {
    return minimumRenterRating;
}

float Motorbike::getMotorbikeRating() const
{
    // Returns average of the ratings depending upon the reviews given

    if (!reviews.size())
        return 0.0;
    float ratingsSum = 0.0;
    int i = 0;
    for (i; i < reviews.size(); i++)
    {
        ratingsSum += reviews[i].getRating();
    }
    return ratingsSum / i;
}

bool Motorbike::isAvailableForRent() const 
{
    return isAvailable;
}

int Motorbike::getOwnerID() const {
    return ownerID;
}

int Motorbike::getID() const {
    return id;
}

string Motorbike::getLocation() const
{
    return location;
}

const vector<Review>& Motorbike::getReviews() const {
    return reviews;
}

const vector<RentalRequest>& Motorbike::getRentalRequests() const {
    return rentalRequests;
}

void Motorbike::setModel(const string& _model) {
    model = _model;
}

void Motorbike::setColor(const string& _color) {
    color = _color;
}

void Motorbike::setEngineSize(int _engineSize) {
    engineSize = _engineSize;
}

void Motorbike::setTransmissionMode(const string& _transmissionMode) {
    transmissionMode = _transmissionMode;
}

void Motorbike::setYearMade(int _yearMade) {
    yearMade = _yearMade;
}

void Motorbike::setDescription(const string& _description) {
    description = _description;
}

void Motorbike::setLocation(const string& _location)
{
    location = _location;
}

void Motorbike::setConsumePointsPerDay(int _consumePointsPerDay) {
    consumePointsPerDay = _consumePointsPerDay;
}

void Motorbike::setMinimumRenterRating(int _minimumRenterRating) {
    minimumRenterRating = _minimumRenterRating;
}

void Motorbike::setMotorbikeRating(float _motorbikeRating) {
    motorbikeRating = _motorbikeRating;
}

void Motorbike::setAvailable(bool _isAvailable) {
    isAvailable = _isAvailable;
}

void Motorbike::addReview(const Review& review)
{
    reviews.push_back(review);
}

void Motorbike::showReviews() const {
    if (reviews.empty()) {
        cout << "No reviews available for this motorbike." << endl;
    }
    else {
        cout << "Reviews for Motorbike ID " << id << ":" << endl;
        cout << "------------------------------------------------------" << endl;

        for (const Review& review : reviews) {
            cout << "Reviewer: " << review.getReviewerUsername() << endl;
            cout << "Rating: " << review.getRating() << endl;
            cout << "Comments: " << review.getComments() << endl;
            cout << "------------------------------------------------------" << endl;
        }
    }
}

void Motorbike :: addRentalRequest(int requesterID, const string& requesterUsername, const tm& startTime, const tm& endTime) {
    
    // Adds a request to the list of requests of the bike
    
    UserManager um("users.txt");
    User user = um.getUserByID(ownerID);
    RentalRequest request(requesterID, requesterUsername, user.getUsername(), ownerID, model, startTime, endTime);
    rentalRequests.push_back(request);
}

void Motorbike::showRentalRequests() const
{
    cout << "Rental Requests for Motorbike ID: " << id << endl;
    int count = 1;

    if (rentalRequests.empty()) {
        cout << "No rental requests found for this motorbike." << endl;
        return;
    }

    for (const RentalRequest& request : rentalRequests) {
        tm start = request.getStartTime();
        tm end = request.getEndTime();
        cout << "Request no. " << count++ << endl;
        cout << "Requester Username: " << request.getRequesterUsername() << endl;
        cout << "Motorbike Owner Username: " << request.getMotorbikeOwnerUsername() << endl;
        cout << "Motorbike Model: " << request.getMotorbikeModel() << endl;
        cout << "Start Time: " << start.tm_year << "/" << start.tm_mon << "/" << start.tm_mday << endl;
        cout << "End Time: " << end.tm_year << "/" << end.tm_mon << "/" << end.tm_mday << endl;

        if (request.isRequestAccepted()) {
            cout << "Status: Accepted" << endl;
        }
        else {
            cout << "Status: Pending" << endl;
        }

        cout << endl;
    }
}

void Motorbike::emptyRequest()
{
    // Clears the request list

    rentalRequests.clear();
}

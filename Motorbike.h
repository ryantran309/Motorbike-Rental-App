#pragma once

#include <string>
#include <vector>
#include "User.h"
#include "Review.h"
#include "RentalRequest.h"

class Motorbike {
private:
    // Private member variables.
    int id;
    string model;
    string color;
    int engineSize;
    string transmissionMode;
    int yearMade;
    string description;
    int consumePointsPerDay;
    int minimumRenterRating;
    float motorbikeRating;
    bool isAvailable;
    int ownerID;
    string location;
    vector<Review> reviews;
    vector<RentalRequest> rentalRequests;

public:
    // Constructor with default values.
    Motorbike(int _id, const string& _model, const string& _color, int _engineSize,
        const string& _transmissionMode, int _yearMade, const string& _description,
        int _consumePointsPerDay, int _minimumRenterRating, string _location,
        float _motorbikeRating = 0.0f, bool _isAvailable = true, int _ownerID = -1);

    // Getters for member variables.
    string getModel() const;
    string getColor() const;
    int getEngineSize() const;
    string getTransmissionMode() const;
    int getYearMade() const;
    string getDescription() const;
    int getConsumePointsPerDay() const;
    int getMinimumRenterRating() const;
    float getMotorbikeRating() const;
    bool isAvailableForRent() const;
    int getOwnerID() const;
    int getID() const;
    string getLocation() const;
    const vector<Review>& getReviews() const;
    const vector<RentalRequest>& getRentalRequests() const;

    // Setters
    void setModel(const string& _model);
    void setColor(const string& _color);
    void setEngineSize(int _engineSize);
    void setTransmissionMode(const string& _transmissionMode);
    void setYearMade(int _yearMade);
    void setDescription(const string& _description);
    void setLocation(const string& _location);
    void setConsumePointsPerDay(int _consumePointsPerDay);
    void setMinimumRenterRating(int _minimumRenterRating);
    void setMotorbikeRating(float _motorbikeRating);
    void setAvailable(bool _isAvailable);

    // Methods to add reviews and rental requests.
    void addReview(const Review& review);
    void addRentalRequest(int requesterID, const string& requesterUsername,
        const tm& startTime, const tm& endTime);

    // Methods to display reviews and rental requests.
    void showReviews() const;
    void showRentalRequests() const;

    // Method to empty rental requests.
    void emptyRequest();
};

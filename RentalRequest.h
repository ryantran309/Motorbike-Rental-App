#pragma once
#include <string>
#include <ctime>
using namespace std;

class RentalRequest {
private:
    int requesterID;               // Requester's ID.
    string requesterUsername;      // Requester's username.
    string motorbikeOwnerUsername; // Motorbike owner's username.
    int motorBikeOwnerID;          // Motorbike owner's ID.
    string motorbikeModel;        // Model of the requested motorbike.
    tm startTime;                 // Start time of the request.
    tm endTime;                   // End time of the request.
    bool isAccepted;              // Request acceptance status.

public:
    // Constructor to initialize a RentalRequest object.
    RentalRequest(int _requesterID, const string& _requesterUsername,
        const string& _motorbikeOwnerUsername, int _ownerID,
        const string& _motorbikeModel, const tm& _startTime,
        const tm& _endTime);

    // Getters to access the private member variables.
    int getRequesterID() const;
    string getRequesterUsername() const;
    string getMotorbikeOwnerUsername() const;
    string getMotorbikeModel() const;
    tm getStartTime() const;
    tm getEndTime() const;
    bool isRequestAccepted() const;
    int getOwnerID() const;

    // Setter to modify the request acceptance status.
    void setRequestAccepted(bool _isAccepted);
};

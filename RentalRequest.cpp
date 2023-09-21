#include "RentalRequest.h"

// Constructor
RentalRequest::RentalRequest(int _requesterID,
    const string& _requesterUsername,
    const string& _motorbikeOwnerUsername,
    int _ownerID, 
    const string& _motorbikeModel,
    const tm& _startTime,
    const tm& _endTime)
    : requesterID(_requesterID),
    requesterUsername(_requesterUsername),
    motorbikeOwnerUsername(_motorbikeOwnerUsername),
    motorBikeOwnerID(_ownerID),
    motorbikeModel(_motorbikeModel),
    startTime(_startTime),
    endTime(_endTime),
    isAccepted(false) {
}

// Getters

int RentalRequest::getRequesterID() const
{
    return requesterID;
}

string RentalRequest::getRequesterUsername() const {
    return requesterUsername;
}

string RentalRequest::getMotorbikeOwnerUsername() const {
    return motorbikeOwnerUsername;
}

string RentalRequest::getMotorbikeModel() const {
    return motorbikeModel;
}

tm RentalRequest::getStartTime() const {
    return startTime;
}

tm RentalRequest::getEndTime() const {
    return endTime;
}

bool RentalRequest::isRequestAccepted() const {
    return isAccepted;
}

int RentalRequest::getOwnerID() const
{
    return motorBikeOwnerID;
}

// Setter
void RentalRequest::setRequestAccepted(bool _isAccepted) {
    isAccepted = _isAccepted;
}

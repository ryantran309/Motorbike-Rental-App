#include "Review.h"

// Constructor
Review::Review(int _bikeID,
    const string& _reviewerUsername,
    const string& _targetUsername,
    int _rating,
    const string& _comments)
    : bikeID(_bikeID),
    reviewerUsername(_reviewerUsername),
    targetUsername(_targetUsername),
    rating(_rating),
    comments(_comments) {
}

// Getters

int Review::getBikeID() const
{
    return bikeID;
}

string Review::getReviewerUsername() const {
    return reviewerUsername;
}

string Review::getTargetUsername() const {
    return targetUsername;
}

int Review::getRating() const {
    return rating;
}

string Review::getComments() const {
    return comments;
}

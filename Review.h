#pragma once
#include <string>
using namespace std;

class Review {
private:
    int bikeID;
    string reviewerUsername;
    string targetUsername;
    int rating;
    string comments;

public:
    Review(
        int _bikeID,
        const string& _reviewerUsername,
        const string& _targetUsername,
        int _rating,
        const string& _comments);

    // Getters
    int getBikeID() const;
    string getReviewerUsername() const;
    string getTargetUsername() const;
    int getRating() const;
    string getComments() const;
};

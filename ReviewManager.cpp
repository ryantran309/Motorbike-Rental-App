#include "ReviewManager.h"
#include <fstream>
#include <sstream>

ReviewManager::ReviewManager(const string& filename) : filename(filename)
{
	loadReviewsFromFile();
}

void ReviewManager::loadReviewsFromFile() 
{
    // Follows same logic from motorbike manager but here with reviews

    ifstream file(filename);
    string line;

    if (!file.is_open())
    {
        cout << "Couldn't open the file." << endl;
        exit(0);
    }

    while (getline(file, line)) 
    {
        istringstream iss(line);
        vector<string> tokens;
        string token;

        while (getline(iss, token, ',')) 
        { 
            tokens.push_back(token);
        }

        if (tokens.size() == 5) 
        {
            int bikeID = stoi(tokens[0]);
            string reviewerUsername = tokens[1];
            string targetUsername = tokens[2];
            int rating = stoi(tokens[3]);
            string comments = tokens[4];

            Review review(bikeID, reviewerUsername, targetUsername, rating, comments);
            reviews.push_back(review);
        }
    }

    file.close();
}

void ReviewManager::addReview(const Review& review)
{
    reviews.push_back(review);
}

vector<Review> ReviewManager::getReviewsByID(int id)
{
    vector<Review> targetReviews;

    for (const Review& review : reviews) {
        if (review.getBikeID() == id) {
            targetReviews.push_back(review);
        }
    }

    return targetReviews;
}

void ReviewManager::saveReviewsToFile() 
{
    // Saves comma-seperated reviews' data into file

    ofstream file(filename);

    for (const Review& review : reviews)
    {
        file << review.getBikeID() << ","
            << review.getReviewerUsername() << ","
            << review.getTargetUsername() << ","
            << review.getRating() << ","
            << review.getComments() << endl;
    }

    file.close();
}



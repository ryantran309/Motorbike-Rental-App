#pragma once
#include <iostream>
#include <vector>
#include "Review.h"

// Class that handles reviews' storage in file
class ReviewManager {
    string filename;        // File name for data storage.
    vector<Review> reviews; // Vector to store reviews.

public:
    // Constructor to initialize a ReviewManager object.
    ReviewManager(const string& filename);

    // Load reviews data from a file.
    void loadReviewsFromFile();

    // Add a review to the manager.
    void addReview(const Review& review);

    // Get reviews by bike's ID and return as a vector.
    vector<Review> getReviewsByID(int id);

    // Save reviews data to a file.
    void saveReviewsToFile();
};

#pragma once
#include <vector>
#include "RentalRequest.h"

// Class that handles storage handling of Rental Requests
class RequestManager {
    vector<RentalRequest> requests; // Vector to store rental requests.
    string filename;               // File name for data storage.

public:
    // Constructor to initialize a RequestManager object.
    RequestManager(const string& filename);

    // Load rental requests data from a file.
    void loadRequestsData();

    // Remove rental requests by owner's ID.
    void removeRequestsByOwnerID(int ownerID);

    // Add a rental request to the manager.
    void addRequest(const RentalRequest& request);

    // Filter rental requests by owner's ID and return as a vector.
    vector<RentalRequest> filterByID(int id);

    // Save rental requests data to a file.
    void saveRequestsInFile();
};

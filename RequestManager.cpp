#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <ctime>
#include "RequestManager.h"


RequestManager::RequestManager(const string& _filename) : filename(_filename)
{
    loadRequestsData();
}

void RequestManager::loadRequestsData()
{
    // Follows same logic from Motorbike manager but this time with requests

    ifstream file(filename);
    string line;

    if (!file.is_open())
    {
        cout << "Couldn't open Requests file." << endl;
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

        if (tokens.size() == 11)
        {
            int requesterID = stoi(tokens[0]);
            string requesterUsername = tokens[1];
            string motorbikeOwnerUsername = tokens[2];
            int motorBikeOwnerID = stoi(tokens[3]);
            string motorbikeModel = tokens[4];
            tm startTime;
            startTime.tm_year = stoi(tokens[5]);
            startTime.tm_mon = stoi(tokens[6]);
            startTime.tm_mday = stoi(tokens[7]);
            tm endTime;
            endTime.tm_year = stoi(tokens[8]);
            endTime.tm_mon = stoi(tokens[9]);
            endTime.tm_mday = stoi(tokens[10]);


            RentalRequest request(
                requesterID,
                requesterUsername,
                motorbikeOwnerUsername,
                motorBikeOwnerID,
                motorbikeModel,
                startTime,
                endTime
            );
            requests.push_back(request);
        }
    }

    file.close();
}

vector<RentalRequest> RequestManager::filterByID(int id) {
    vector<RentalRequest> filteredRequests;
    for (const RentalRequest& request : requests) {
        if (request.getOwnerID() == id) {
            filteredRequests.push_back(request);
        }
    }
    return filteredRequests;
}

void RequestManager::removeRequestsByOwnerID(int ownerID) {
    auto it = requests.begin();
    while (it != requests.end()) {
        if (it->getOwnerID() == ownerID) {
            it = requests.erase(it);
        }
        else {
            ++it;
        }
    }
}

void RequestManager::addRequest(const RentalRequest& request)
{
    requests.push_back(request);
}

void RequestManager::saveRequestsInFile() 
{
    // Saves requests' data into file in comma-seperated format

    ofstream file(filename);

    for (const RentalRequest& request : requests) {
        file << request.getRequesterID() << ","
            << request.getRequesterUsername() << ","
            << request.getMotorbikeOwnerUsername() << ","
            << request.getOwnerID() << ","
            << request.getMotorbikeModel() << ","
            << request.getStartTime().tm_year << ","
            << request.getStartTime().tm_mon << ","
            << request.getStartTime().tm_mday << ","
            << request.getEndTime().tm_year << ","
            << request.getEndTime().tm_mon << ","
            << request.getEndTime().tm_mday << endl;
    }

    file.close();
}

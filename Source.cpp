#include "User.h"
#include "Motorbike.h"
#include "UserManager.h"
#include "MotorBikeManager.h"
#include "Review.h"
#include "RentalRequest.h"
#include "ReviewManager.h"
#include "RequestManager.h"

int calculateDateDifference(tm& date1, tm& date2);

int main()
{
	// Reading the data beforehand from files to avoid multiple file lookups
	UserManager userData("users.txt");
	MotorbikeManager motorbikeData("bikes.txt");
	RequestManager requestsData("requests.txt");
	ReviewManager reviewData("reviews.txt");
	int choice, entityChoice;

	cout << "EEET2482/COSC2082 ASSIGNMENT" << endl
		<< "MOTORBIKE RENTAL APPLICATION" << endl << endl
		<< "Intructor: Dr. Ling Huo Chong" << endl
		<< "Group: Group No.21" << endl
		<< "S3821266, Tran Anh Bao" << endl
		<< "S3894433, Nguyen Phat Dat" << endl
		<< "S3915085, Le Anh Dung" << endl
		<< "S3879524, Duong Hoang Dang Khoi" << endl;
	while (true)
	{
		cout << "Use the app as:" << endl
			<< "1. Guest" << endl
			<< "2. Member" << endl
			<< "3. Admin" << endl
			<< "or enter any other number to exit: ";
		cin >> choice;
		if (choice == 1)
		{
			// Using app as Guest

			while (true)
			{
				cout << "\nMOTORBIKE RENTAL APPLICATION - Guest Menu" << endl;
				cout << "1. Register as a Member" << endl;
				cout << "2. View Motorbike Details" << endl;
				cout << "Any other number to exit" << endl;
				cout << "Enter your choice: ";
				cin >> entityChoice;
				if (entityChoice == 1)
				{
					// Member registration of a non-member

					cout << "You have chosen to register as a Member." << endl;

					string username, password, fullName, phoneNumber, idType, idNumber, driverLicenseNumber, licenseExpiryDate;

					cout << "Enter username: ";
					cin >> username;

					cout << "Enter password: ";
					cin >> password;

					cout << "Enter full name: ";
					cin.ignore();
					getline(cin, fullName);

					cout << "Enter phone number: ";
					cin >> phoneNumber;

					cout << "Enter ID type (CitizenID/Passport): ";
					cin >> idType;
					while (idType != "CitizenID" && idType != "Passport")
					{
						cout << "Enter valid ID type (CitizenID/Passport): ";
						cin >> idType;
					}

					cout << "Enter ID/Passport number: ";
					cin >> idNumber;

					cout << "Enter driver's license number: ";
					cin >> driverLicenseNumber;

					cout << "Enter license expiry date: ";
					cin >> licenseExpiryDate;

					User newMember = User::registerMember(username, password, fullName, phoneNumber, idType, idNumber, driverLicenseNumber, licenseExpiryDate);
					userData.addUser(newMember);
					cout << "\nCongrats! You have successfully registered as a member.\nNow you can login as a member after exiting guest mode." << endl;
				}
				else if (entityChoice == 2)
				{
					// View all motorbike details

					cout << "You have chosen to see the motorbikes' details." << endl;
					motorbikeData.showAllBikes();
				}
				else
				{
					cout << "Exiting as guest.." << endl;
					break;
				}
			}
		}
		else if (choice == 2)
		{
			// Using app as Member and logging in first

			string username, password;
			cout << "***** Sign in as a member *****" << endl << endl;
			cout << "Enter username: ";
			cin >> username;
			cout << "Enter Password: ";
			cin >> password;
			if (userData.logIn(username, password))
			{
				// Successfull Authentication

				User user = userData.getUserByID(userData.getLoggedInUserID());
				int userChoice;
				cout << "Welcome " << user.getUsername() << "!" << endl;
				while (true)
				{
					cout << "\nMOTORBIKE RENTAL APPLICATION - Member Menu" << endl;
					cout << "1. View My Information" << endl;
					cout << "2. List My Motorbike for Rent" << endl;
					cout << "3. View Requests for My Motorbike" << endl;
					cout << "4. Accept a request to rent your Motorbike" << endl;
					cout << "5. Rate a Rented Motorbike" << endl;
					cout << "6. Request a Motorbike" << endl;
					cout << "7. View Reviews for my bike" << endl;
					cout << "8. Add credits" << endl;
					cout << "9. Request bike by city" << endl;
					cout << "10. Unlist my Bike" << endl;
					cout << "11. Rate a renter" << endl;
					cout << "Any other number to exit" << endl;
					cout << "Enter your choice: ";
					cin >> userChoice;
					if (userChoice == 1)
					{
						user.showUserInformation();
					}
					else if (userChoice == 2)
					{
						if (user.getMotorbikeID() == -1)
						{
							// Lists the bike if only the list is empty as user can only list a single bike

							string model, color, transmissionMode, description, location;
							int engineSize, yearMade, consumePointsPerDay, minimumRenterRating;
							cout << "You have opted to list your bike." << endl;
							cout << "Enter model: ";
							cin >> model;
							cout << "Enter color: ";
							cin >> color;
							cout << "Enter transmission Mode (A/M): ";
							cin >> transmissionMode;
							while (transmissionMode != "A" && transmissionMode != "M")
							{
								cout << "Enter transmission mode either A (auto) or M (manual): ";
								cin >> transmissionMode;
							}
							cin.ignore();
							cout << "Enter description: ";
							getline(cin, description);
							cout << "Enter location (Ha Noi/Sai Gon): ";
							getline(cin, location);
							while (location != "Ha Noi" && location != "Sai Gon")
							{
								// Input validation
								cout << "Enter either Ha Noi or Sai Gon for location: ";
								getline(cin, location);
							}

							cout << "Enter engine size: ";
							cin >> engineSize;
							cout << "Enter year made: ";
							cin >> yearMade;
							cout << "Enter consume points per day: ";
							cin >> consumePointsPerDay;
							while (consumePointsPerDay < 1)
							{
								cout << "Enter greater than 1: ";
								cin >> consumePointsPerDay;
							}
							cout << "Enter minimum renter rating: ";
							cin >> minimumRenterRating;
							while (minimumRenterRating < 0 || minimumRenterRating > 10)
							{
								// Input validation
								cout << "Enter between 0-10: ";
								cin >> minimumRenterRating;
							}
							Motorbike newBike(
								motorbikeData.getNextMemberID(),
								model,
								color,
								engineSize,
								transmissionMode,
								yearMade,
								description,
								consumePointsPerDay,
								minimumRenterRating,
								location,
								(0.0f),
								true,
								user.getID()
							);
							// Adding new bike data to the manager and updating the user data as well
							motorbikeData.addMotorbike(newBike);
							user.setMotorbikeID(newBike.getID());
							userData.updateUser(user);

							cout << "CONGRATS! You have successfully listed the motorbike." << endl;
						}
						else
						{
							cout << "You can only list one motorbike!" << endl;
						}
					}
					else if (userChoice == 3)
					{
						// Shows rental requests currently available for your bike

						cout << "You have opted to see rental requests for your bike." << endl << endl;

						Motorbike myBike = motorbikeData.getMotorBikeByID(user.getMotorbikeID());
						if (myBike.getID() != -1)
							myBike.showRentalRequests();
						else
							cout << "You haven't registered a bike yet!" << endl;
					}
					else if (userChoice == 4)
					{
						// Shows rental requests and lets you opt for a rental request to accept and
						// reject others

						int requestChoice;
						cout << "You have opted to rent your bike." << endl << endl;
						Motorbike myBike = motorbikeData.getMotorBikeByID(user.getMotorbikeID());
						if ((myBike.getID() != -1) && myBike.isAvailableForRent())
						{
							myBike.showRentalRequests();
							vector<RentalRequest> requests = myBike.getRentalRequests();
							if (requests.size() > 0)
							{
								cout << "Enter the request number to accept: ";
								cin >> requestChoice;
								while (requestChoice < 1 || requestChoice > requests.size())
								{
									cout << "Enter a valid request number: ";
									cin >> requestChoice;
								}
								tm startTime = requests[requestChoice - 1].getStartTime();
								tm endTime = requests[requestChoice - 1].getEndTime();
								int creditsRequired = user.getCreditPoints() - calculateDateDifference(startTime, endTime);
								if (creditsRequired > user.getCreditPoints())
								{
									// If credit points aren't enough depending upon the days, it doesn't accept the request
									cout << "User has insufficient credits. Can't accept request." << endl;
									continue;
								}
								
								// Updates the request and updates bike and user data accordingly

								requests[requestChoice - 1].setRequestAccepted(true);
								myBike.setAvailable(false);
								User user = userData.getUserByID(requests[requestChoice - 1].getRequesterID());
								user.setHasRented(true);
								user.setRentedBikeID(myBike.getID());
								user.setCreditPoints((user.getCreditPoints() - creditsRequired) >= 0 ? (user.getCreditPoints() - creditsRequired) : 0);
								userData.updateUser(user);
								requestsData.removeRequestsByOwnerID(user.getRentedBikeID());
								myBike.emptyRequest();
								cout << "Request accepted!" << endl;
								motorbikeData.updateBike(myBike);
							}
						}
						else
							cout << "Your bike is not available for rent!" << endl;
					}
					else if (userChoice == 5)
					{
						cout << "You have opted to rate a rented motorbike!" << endl;
						if (user.userHasRented())
						{
							// Rate a motorbike only if a user is in possession of a rented bike and updates 
							// data accordingly

							user.setHasRented(false);
							Motorbike rentedBike = motorbikeData.getMotorBikeByID(user.getRentedBikeID());
							user.setRentedBikeID(-1);
							string reviewer = user.getUsername();
							string targetUsername = userData.getUserByID(rentedBike.getOwnerID()).getUsername();
							int ratings;
							cout << "Enter ratings (0-10) for the review of the bike: ";
							cin >> ratings;
							while (ratings < 0 || ratings > 10)
							{
								cout << "Enter between 0 and 10: " << endl;
								cin >> ratings;
							}
							string comments;
							cout << "Enter your comments about the ride: ";
							cin.ignore();
							getline(cin, comments);
							Review review(rentedBike.getID(), reviewer, targetUsername, ratings, comments);
							rentedBike.setAvailable(true);
							rentedBike.addReview(review);
							reviewData.addReview(review);
							cout << "Review added successfully!" << endl;
							motorbikeData.updateBike(rentedBike);
						}
						else
						{
							cout << "You haven't rented a bike to rate!" << endl;
						}
					}
					else if (userChoice == 6)
					{
						// User can make a request for a bike from the list of available bikes for the user

						int requestChoice;
						cout << "You have opted to request a bike!" << endl;
						cout << "Below is the list of available bikes: " << endl;
						int count = motorbikeData.showMotorbikesForUser(user);
						if (count > 0)
						{
							cout << "Enter the ID to request that bike: ";
							cin >> requestChoice;
							Motorbike bike = motorbikeData.getMotorBikeByID(requestChoice);
							if (bike.getID() == -1)
							{
								cout << "Bike with the given ID doesn't exist." << endl;
							}
							else
							{
								tm startTime, endTime;

								cout << "Enter start time components:" << endl;
								cout << "Year: ";
								cin >> startTime.tm_year;
								while (startTime.tm_year < 2000 || startTime.tm_year > 2023)
								{
									cout << "Enter year (2000-2023): ";
									cin >> startTime.tm_year;
								}
								cout << "Month (1-12): ";
								cin >> startTime.tm_mon;
								while (startTime.tm_mon < 1 || startTime.tm_mon > 12)
								{
									cout << "Invalid month. Enter a month between 1 and 12: ";
									cin >> startTime.tm_mon;
								}
								cout << "Day of the month: ";
								cin >> startTime.tm_mday;
								while (startTime.tm_mday < 1 || startTime.tm_mday > 31) {
									cout << "Invalid day. Enter a day between 1 and 31: ";
									cin >> startTime.tm_mday;
								}

								cout << "Enter end time components:" << endl;
								cout << "Year: ";
								cin >> endTime.tm_year;
								while (endTime.tm_year < 2000 || endTime.tm_year > 2023)
								{
									cout << "Enter year (2000-2023): ";
									cin >> endTime.tm_year;
								}
								cout << "Month (1-12): ";
								cin >> endTime.tm_mon;
								while (endTime.tm_mon < 1 || endTime.tm_mon > 12)
								{
									cout << "Invalid month. Enter a month between 1 and 12: ";
									cin >> endTime.tm_mon;
								}
								cout << "Day of the month: ";
								cin >> endTime.tm_mday;
								while (endTime.tm_mday < 1 || endTime.tm_mday > 31) {
									cout << "Invalid day. Enter a day between 1 and 31: ";
									cin >> endTime.tm_mday;
								}

								// Initiates rental request and update the bike data accordingly

								RentalRequest rr(
									user.getID(),
									user.getUsername(),
									userData.getUserByID(bike.getOwnerID()).getUsername(),
									bike.getOwnerID(),
									bike.getModel(),
									startTime,
									endTime
								);
								bike.addRentalRequest(
									user.getID(),
									user.getUsername(),
									startTime,
									endTime
								);
								requestsData.addRequest(rr);
								motorbikeData.updateBike(bike);
								cout << "Request submitted successfully!" << endl;
							}
						}
					}
					else if (userChoice == 7)
					{
						if (user.getMotorbikeID() == -1)
						{
							cout << "You haven't listed a bike!" << endl;
						}
						else
						{
							// Displays reviews of current user's bike

							Motorbike myBike = motorbikeData.getMotorBikeByID(user.getMotorbikeID());
							myBike.showReviews();
						}
					}
					else if (userChoice == 8)
					{
						// Add credit points according to the top-up verified by the password

						int credits;
						string password;
						cout << "You have opted to add credit points." << endl;
						cout << "Enter how many credits do you want to add (1$ = 1 Credit Point): ";
						cin >> credits;
						while (credits < 1)
						{
							cout << "Enter credits greater than 1: ";
							cin >> credits;
						}
						cout << "Enter your password to verify transaction: ";
						cin >> password;
						if (user.getPassword() == password)
						{
							user.setCreditPoints(user.getCreditPoints() + credits);
							cout << "Account credited!" << endl;
							userData.updateUser(user);
						}
						else
						{
							cout << "You entered wrong password, heading back." << endl;
						}
							

					}
					else if (userChoice == 9)
					{
						// Lets user make a requests for the bikes filtered by the city

						string city;
						int requestChoice;
						cin.ignore();
						cout << "Enter location (Ha Noi/Sai Gon): ";
						getline(cin, city);
						while (city != "Ha Noi" && city != "Sai Gon")
						{
							cout << "Enter either Ha Noi or Sai Gon for city: ";
							getline(cin, city);
						}
						cout << "Below is the list of available bikes: " << endl;
						int count = motorbikeData.showMotorbikesFromCity(user, city);
						if (count > 0)
						{
							cout << "Enter the ID to request that bike: ";
							cin >> requestChoice;
							Motorbike bike = motorbikeData.getMotorBikeByID(requestChoice);
							if (bike.getID() == -1)
							{
								cout << "Bike with the given ID doesn't exist." << endl;
							}
							else
							{
								tm startTime, endTime;

								cout << "Enter start time components:" << endl;
								cout << "Year: ";
								cin >> startTime.tm_year;
								while (startTime.tm_year < 2000 || startTime.tm_year > 2023)
								{
									cout << "Enter year (2000-2023): ";
									cin >> startTime.tm_year;
								}
								cout << "Month (1-12): ";
								cin >> startTime.tm_mon;
								while (startTime.tm_mon < 1 || startTime.tm_mon > 12)
								{
									cout << "Invalid month. Enter a month between 1 and 12: ";
									cin >> startTime.tm_mon;
								}
								cout << "Day of the month: ";
								cin >> startTime.tm_mday;
								while (startTime.tm_mday < 1 || startTime.tm_mday > 31) {
									cout << "Invalid day. Enter a day between 1 and 31: ";
									cin >> startTime.tm_mday;
								}

								cout << "Enter end time components:" << endl;
								cout << "Year: ";
								cin >> endTime.tm_year;
								while (endTime.tm_year < 2000 || endTime.tm_year > 2023)
								{
									cout << "Enter year (2000-2023): ";
									cin >> endTime.tm_year;
								}
								cout << "Month (1-12): ";
								cin >> endTime.tm_mon;
								while (endTime.tm_mon < 1 || endTime.tm_mon > 12)
								{
									cout << "Invalid month. Enter a month between 1 and 12: ";
									cin >> endTime.tm_mon;
								}
								cout << "Day of the month: ";
								cin >> endTime.tm_mday;
								while (endTime.tm_mday < 1 || endTime.tm_mday > 31) {
									cout << "Invalid day. Enter a day between 1 and 31: ";
									cin >> endTime.tm_mday;
								}
								RentalRequest rr(
									user.getID(),
									user.getUsername(),
									userData.getUserByID(bike.getOwnerID()).getUsername(),
									bike.getOwnerID(),
									bike.getModel(),
									startTime,
									endTime
								);
								bike.addRentalRequest(
									user.getID(),
									user.getUsername(),
									startTime,
									endTime
								);
								requestsData.addRequest(rr);
								motorbikeData.updateBike(bike);
								cout << "Request submitted successfully!" << endl;
							}
						}
					}
					else if (userChoice == 10)
					{
						// Unlists the bike for a user only if the bike is listed or he has not rented or 
						
						if (user.getMotorbikeID() == -1)
						{
							cout << "You haven't listed a bike." << endl;
						}
						else if (motorbikeData.getMotorBikeByID(user.getMotorbikeID()).isAvailableForRent())
						{
							cout << "You have chosen to unlist your Motorbike." << endl;
							cout << "..." << endl;
							motorbikeData.unlistBikeByID(user.getMotorbikeID());
							user.setMotorbikeID(-1);
							user.setMotorbikeRating(0.0);
							userData.updateUser(user);
							cout << "You have unlisted your bike.";
						}
						else
						{
							cout << "Your motorbike has been rented to a user and you cannot unlist it now.." << endl
								<< "Wait for the user to return your bike first." << endl;
						}
					}
					else if (userChoice == 11)
					{
						int input;
						cout << "You have opted to rate a renter." << endl;
						cout << "Here is the list of users: " << endl;
						userData.showAllUsers();
						cout << "Enter ID of the user to rate: " << endl;
						cin >> input;
						while (input < 0)
						{
							cout << "Enter ratings greater than 1: ";
							cin >> input;
						}
						User user = userData.getUserByID(input);
						if (user.getID() == -1)
						{
							cout << "No user with this ID exists.." << endl;
						}
						else
						{
							cout << "Enter ratings for this user: ";
							cin >> input;
							if (input < 0 || input > 10)
							{
								cout << "Enter ratings between 0 to 10: ";
								cin >> input;
							}
							user.setRenterRating(input);
							userData.updateUser(user);
							cout << "Renter rated successfully." << endl;
						}
					}
					else
					{
						break;
					}
				}
			}
			else
			{
				cout << "Invalid credentials. Going back to main menu!" << endl;
				
			}
			userData.logOut();
		}
		else if (choice == 3)
		{
			// Using app as admin and loggin in with pre-defined credentials for admin (hard-coded)

			int adminChoice;
			string username, password;
			cout << "Enter admin username: ";
			cin >> username;
			cout << "Enter admin password: ";
			cin >> password;
			if (username == "admin" && password == "admin123")
			{
				while (true)
				{
					cout << "\nMOTORBIKE RENTAL APPLICATION - Admin Menu" << endl;
					cout << "1. See all user details" << endl;
					cout << "2. View all Motorbike Details" << endl;
					cout << "Any other number to exit" << endl;
					cout << "Enter your choice: ";
					cin >> adminChoice;
					if (adminChoice == 1)
					{
						userData.showAllUsers();
					}
					else if (adminChoice == 2)
					{
						motorbikeData.showAllBikes();
					}
					else
					{
						cout << "Exiting Admin mode." << endl;
						break;
					}
				}
			}
			else
			{
				cout << "Invalid Credentials! Heading back to main menu.." << endl;
			}
		}
		else
		{
			break;
		}
	}
	reviewData.saveReviewsToFile();
	requestsData.saveRequestsInFile();
	userData.saveUsersToFile();
	motorbikeData.saveMotorbikesToFile();
	cout << "Exiting..";

	return 0;
}
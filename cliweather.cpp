#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <sstream>
#include <cmath>
#include "nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;

int ctof(double kTemp) {
	double cTemp = kTemp - 273;
	double fTemp = cTemp * 1.8 + 32;

	return round(fTemp);
}

string wind(double speed, double degree) {
	speed = speed * 2.23694;
	speed = round(speed);

	stringstream windSpeed;

	windSpeed << speed << " mph ";

	if (degree == 0) {
		windSpeed << "N";
	} else if (0 < degree && degree < 90) {
		windSpeed << "NE";
	} else if (degree == 90) {
		windSpeed << "E";
	} else if (90 < degree && degree < 180) {
		windSpeed << "SE";
	} else if (degree == 180) {
		windSpeed << "S";
	} else if (180 < degree && degree < 270) {
		windSpeed << "SW";
	} else if (degree == 270) {
		windSpeed << "W";
	} else if (270 < degree && degree < 360) {
		windSpeed << "NW";
	}

	return windSpeed.str();
}

pair<string, string> readUserData(ifstream& dataFile) {
	string apiKey;
	string defaultLocation;

	dataFile >> apiKey;
	dataFile.ignore();
	getline(dataFile, defaultLocation);

	return {apiKey, defaultLocation};
}

void createUserData(ofstream& dataFile) {
	string apiKey;
	string defaultLocation;

	cout << "Enter OpenWeatherMap API key: ";
	cin >> apiKey;
	cout << endl;
	dataFile << apiKey << endl;
	
	cout << "Enter default location: ";
	cin.ignore();
	getline(cin, defaultLocation);
	if (defaultLocation.find(' ') != defaultLocation.npos) {
		defaultLocation[defaultLocation.find(' ')] = '+';
	}
	cout << endl;
	dataFile << defaultLocation;
}

void makeRequest(pair<string,string> userData) {
	stringstream buildCommand;
	buildCommand << "curl -s -o weatherData.json "<< "\"http://api.openweathermap.org/data/2.5/weather?q=" << userData.second << "&appid=" << userData.first << "\" > /dev/null";
	string command = buildCommand.str();

	system(command.c_str());
}

void processWeatherData(ifstream& json_in) {
	json weather;
	json_in >> weather;

	// Name
	string name = *weather.find("name");

	// description
	json descObject = *weather.find("weather");
	string description = *descObject[0].find("description");

	// Temp
	json tempObject = *weather.find("main");
	double temp = *tempObject.find("temp");

	// Wind
	json windObject = *weather.find("wind");
	double windSpeed = *windObject.find("speed");
	double windDeg = *windObject.find("deg");

	// Clouds
	json cloudObject = *weather.find("clouds");
	int clouds = *cloudObject.find("all");

	
	cout << "                                 Weather in " << name << ": " << description << endl; // Orig 30 spaces
	cout << "              Temperature: " << ctof(temp) << '\370' << " F"; 
	cout << "              Wind: " << wind(windSpeed, windDeg);
	cout << "              Cloud Coverage: " << clouds;

	cout << endl << endl << endl;
}


int main() {
	// Reading user data
	ifstream dataFileTest;
	ofstream dataFileWrite;
	ifstream dataFileRead;

	// Testing for existing user file, creating if necessary
	dataFileTest.open("userData.txt");
	if (dataFileTest.fail()) {
		dataFileWrite.open("userData.txt");
		createUserData(dataFileWrite);
		dataFileWrite.close();
	}
	dataFileTest.close();

	// Reading user data file
	dataFileRead.open("userData.txt");
	pair<string,string> userData;
	userData = readUserData(dataFileRead);	

	// Making request
	makeRequest(userData);

	// Parsing and displaying data
	ifstream json_in;
	json_in.open("weatherData.json");
	processWeatherData(json_in);

	dataFileRead.close();
	dataFileWrite.close();
	json_in.close();
}

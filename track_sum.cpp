#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

// Function to add time stamps
std::string addTimes(const std::string& time1, const std::string& time2) {
	std::istringstream iss1(time1);
	std::istringstream iss2(time2);
	char colon;
	int minutes1, seconds1, milliseconds1;
	int minutes2, seconds2, milliseconds2;

	iss1 >> minutes1 >> colon >> seconds1 >> colon >> milliseconds1;
	iss2 >> minutes2 >> colon >> seconds2 >> colon >> milliseconds2;

	int totalMinutes = minutes1 + minutes2;
	int totalSeconds = seconds1 + seconds2;
	int totalMilliseconds = milliseconds1 + milliseconds2;

	if (totalMilliseconds >= 1000) {
		totalSeconds += totalMilliseconds / 1000;
		totalMilliseconds %= 1000;
	}

	if (totalSeconds >= 60) {
		totalMinutes += totalSeconds / 60;
		totalSeconds %= 60;
	}

	std::ostringstream oss;
	oss << std::setfill('0') << std::setw(2) << totalMinutes << ":" << std::setw(2) << totalSeconds
		<< "." << std::setw(3) << totalMilliseconds;
	return oss.str();
}

int main() {
	std::ifstream inputFile("input.txt"); // File name containing time stamps

	if (!inputFile.is_open()) {
		std::cerr << "Error opening the file." << std::endl;
		return 1;
	}

	std::vector<std::string> tracks;
	std::string line;

	while (std::getline(inputFile, line)) {
		tracks.push_back(line);
	}

	inputFile.close();

	std::string total_time = "0:00.000";
	std::ofstream outputFile("output.txt"); // File name for outputting results

	if (!outputFile.is_open()) {
		std::cerr << "Error opening the output file." << std::endl;
		return 1;
	}

	for (const std::string& track : tracks) {
		total_time = addTimes(total_time, track);
		std::cout << total_time << std::endl; // Display on screen
		outputFile << total_time << std::endl; // Write to the file
	}

	outputFile.close();

	return 0;
}

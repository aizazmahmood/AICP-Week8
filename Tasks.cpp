#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>

using namespace std;

class Boat {
private:
    int boatNumber;
    float hourlyRate;
    float halfHourlyRate;
    float moneyTaken;
    float totalHoursHired;
    string returnTime;

public:
    Boat(int number, float hrRate, float halfHrRate)
        : boatNumber(number), hourlyRate(hrRate), halfHourlyRate(halfHrRate),
          moneyTaken(0.0), totalHoursHired(0.0), returnTime("") {}

    void hireBoat(float hours) {
        if (validateTime()) {
            if (hours >= 0.5 && hours <= 8.0) {
                moneyTaken += calculateCost(hours);
                totalHoursHired += hours;
                updateReturnTime();
                cout << "Boat " << boatNumber << " hired for " << hours << " hours." << endl;
            } else {
                cout << "Invalid duration. Please hire for at least 0.5 hours and at most 8 hours." << endl;
            }
        } else {
            cout << "Boat can only be hired between 10:00 and 17:00." << endl;
        }
    }

    void displayDaySummary() const {
        cout << "Boat " << boatNumber << " - Money taken: $" << moneyTaken
             << ", Total hours hired: " << totalHoursHired << " hours." << endl;
    }

    float getMoneyTaken() const {
        return moneyTaken;
    }

    float getTotalHoursHired() const {
        return totalHoursHired;
    }

    int getBoatNumber() const {
        return boatNumber;
    }

    string getReturnTime() const {
        return returnTime;
    }

    static bool compareReturnTimes(const Boat& boat1, const Boat& boat2) {
        return boat1.returnTime < boat2.returnTime;
    }

    static bool compareReturnTimesEqual(const Boat& boat1, const Boat& boat2) {
        return boat1.returnTime == boat2.returnTime;
    }

    static bool compareBoatNumbers(const Boat& boat1, const Boat& boat2) {
        return boat1.boatNumber < boat2.boatNumber;
    }

    static bool compareBoatNumbersEqual(const Boat& boat1, const Boat& boat2) {
        return boat1.boatNumber == boat2.boatNumber;
    }

    static bool compareBoats(const Boat& boat1, const Boat& boat2) {
        return (boat1.totalHoursHired == boat2.totalHoursHired) ? compareBoatNumbers(boat1, boat2) : (boat1.totalHoursHired > boat2.totalHoursHired);
    }

    static bool compareBoatsEqual(const Boat& boat1, const Boat& boat2) {
        return boat1.totalHoursHired == boat2.totalHoursHired && boat1.boatNumber == boat2.boatNumber;
    }

private:
    float calculateCost(float hours) const {
        if (hours >= 1.0) {
            return hours * hourlyRate;
        } else {
            return hours * halfHourlyRate;
        }
    }

    bool validateTime() const {
        
        int currentHour = 12; // Set a sample current hour for testing
        return currentHour >= 10 && currentHour <= 17;
    }

    void updateReturnTime() {
        
        int currentHour = 12; // Set a sample current hour for testing
        int returnHour = currentHour + static_cast<int>(totalHoursHired);
        returnTime = to_string(returnHour) + ":00";
    }
};

int main() {
    vector<Boat> boats;

    
    for (int i = 1; i <= 10; ++i) {
        boats.push_back(Boat(i, 20.0, 12.0));
    }

    for (int i = 0; i < 10; ++i) {
        boats[i].hireBoat(2.0);
    }

    
    for (const auto& boat : boats) {
        boat.displayDaySummary();
    }

    time_t currentTime = time(0); // Get current time
    struct tm* now = localtime(&currentTime);
    int currentHour = now->tm_hour;

    sort(boats.begin(), boats.end(), Boat::compareReturnTimes);

    int availableBoats = 0;
    for (const auto& boat : boats) {
        if (currentHour >= 10 && currentHour <= 17 && boat.getTotalHoursHired() == 0.0) {
            cout << "Boat " << boat.getBoatNumber() << " is available for hire now." << endl;
            availableBoats++;
        }
    }

    if (availableBoats == 0) {
        sort(boats.begin(), boats.end(), Boat::compareReturnTimesEqual);
        cout << "No boats are available. The earliest available time is: " << boats[0].getReturnTime() << endl;
    }


    float totalMoneyTaken = 0.0;
    float totalHoursHired = 0.0;
    int unusedBoats = 0;
    Boat mostUsedBoat = boats[0];

    sort(boats.begin(), boats.end(), Boat::compareBoats);

    for (const auto& boat : boats) {
        totalMoneyTaken += boat.getMoneyTaken();
        totalHoursHired += boat.getTotalHoursHired();

        if (boat.getTotalHoursHired() == 0.0) {
            unusedBoats++;
        }

        if (Boat::compareBoats(mostUsedBoat, boat)) {
            mostUsedBoat = boat;
        }
    }

   
    cout << "\n=== End of Day Report ===" << endl;
    cout << "Total money taken: $" << totalMoneyTaken << endl;
    cout << "Total hours hired: " << totalHoursHired << " hours" << endl;
    cout << "Number of boats not used: " << unusedBoats << endl;
    cout << "Boat used the most: Boat " << mostUsedBoat.getBoatNumber() << " - " << mostUsedBoat.getTotalHoursHired() << " hours" << endl;

    return 0;
}

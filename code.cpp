#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <tuple>
#include <iomanip>
#include <algorithm>
using namespace std;
class Team
{
public:
    string name;
    int points;
    double nrr;
    double prob;
    Team()
    {
        name = "";
        points = 0;
        nrr = 0;
        prob = 1;
    }
    Team(string &teamName, int teamPoints, double runRate)
    {
        name = teamName;
        points = teamPoints;
        nrr = runRate;
        prob = 1;
    }
    static bool compareTeams(Team team1, Team team2)
    {
        // First, compare by points
        if (team1.points > team2.points)
        {
            return true;
        }
        else if (team1.points < team2.points)
        {
            return false;
        }

        // If points are equal, compare by NRR
        return team1.nrr > team2.nrr;
    }
    bool operator<(const Team &other) const
    {
        // First, compare by points
        if (points > other.points)
        {
            return true;
        }
        else if (points < other.points)
        {
            return false;
        }

        // If points are equal, compare by NRR
        return nrr > other.nrr;
    }
};
class Match
{
public:
    Team home;
    Team away;
    int match_no;
    Match(Team &a, Team &b, int matchno)
    {
        home = a;
        away = b;
        match_no = matchno;
    }
};
// bool compareMatches(tuple<Team, Team, int> &match1, tuple<Team, Team, int> &match2)
// {
//     // Compare based on match number
//     return get<2>(match1) < get<2>(match2);
// }
void check(vector<Team> teams, vector<tuple<Team, Team, int>> upcoming_matches, map<string, vector<double>> &prob_matrix, double p)
{
    for (int i = 0; i < teams.size(); i++)
    {
        teams[i].prob *= p;
        // i.prob *= p;
    }
    if (upcoming_matches.size() == 0)
    {
        int index = 0;
        for (auto i : teams)
        {
            // Team x = teams[i];
            // prob_matrix[teams[i]][i] += teams[i].prob;

            prob_matrix[i.name][index] += i.prob;
            // cout << i.prob << " is added to " << i.name << " at " << index << endl;
            index++;
        }

        return;
    }
    // printf("hehe\n");
    Team t1 = get<0>(upcoming_matches.at(0));
    Team t2 = get<1>(upcoming_matches.at(0));
    // else recurse;

    double pnew = 0.5;

    vector<Team> hehe(teams);
    vector<Team> what(teams);
    // t1.points += 2;
    for (int i = 0; i < hehe.size(); i++)
    {
        if (t1.name.compare(hehe[i].name) == 0)
        {
            hehe[i].points += 2;
            break;
        }
    }
    std::sort(hehe.begin(), hehe.end(), Team::compareTeams);
    upcoming_matches.erase(upcoming_matches.begin());

    // for (int i = 0 ; i < teams.size() ; i++) cout << teams[i].points <<teams[i].name << endl;
    check(hehe, upcoming_matches, prob_matrix, pnew);

    // t1.points -= 2;
    // t2.points += 2;

    for (int i = 0; i < what.size(); i++)
    {
        if (t2.name.compare(what[i].name) == 0)
        {
            what[i].points += 2;
            break;
        }
    }
    std::sort(what.begin(), what.end(), Team::compareTeams);

    check(what, upcoming_matches, prob_matrix, 1 - pnew);
}
int main()
{

    vector<Team> teams;
    map<string, Team> teamMap;
    vector<tuple<Team, Team, int>> upcoming_matches;

    // Read data from the file
    ifstream inputFile("points_table.txt");
    if (!inputFile.is_open())
    {
        cout << "Failed to open the file." << endl;
        return 1;
    }

    string line;
    while (getline(inputFile, line))
    {
        string teamName;
        int teamPoints;
        double runRate;

        // Extract the values from the line
        istringstream iss(line);
        if (getline(iss, teamName, ',') &&
            iss >> teamPoints &&
            iss.ignore(1) &&
            iss >> runRate)
        {
            // Create a Team object and add it to the vector
            teams.push_back(Team(teamName, teamPoints, runRate));
        }
    }

    // Close the file
    inputFile.close();

    // Adding teams to MAP
    for (Team &team : teams)
    {
        teamMap[team.name] = team;
    }
    ifstream matchFile("upcoming.txt");
    if (!matchFile.is_open())
    {
        cout << "Failed to open file." << endl;
        return 1;
    }

    while (getline(matchFile, line))
    {
        // Parse the line to extract team names and match number
        string team1Name, team2Name;
        int matchNumber;
        // Example line format: "Lucknow Super Giants, Mumbai Indians, 63"
        size_t commaPos1 = line.find(",");
        size_t commaPos2 = line.find(",", commaPos1 + 1);
        if (commaPos1 != string::npos && commaPos2 != string::npos)
        {
            team1Name = line.substr(0, commaPos1);
            team2Name = line.substr(commaPos1 + 2, commaPos2 - commaPos1 - 2);
            matchNumber = stoi(line.substr(commaPos2 + 2));
        }
        else
        {
            cout << "Invalid line format: " << line << endl;
            continue;
        }

        // Create Team objects
        Team team1 = teamMap[team1Name];
        Team team2 = teamMap[team2Name];

        // Add the match tuple to the vector
        upcoming_matches.emplace_back(team1, team2, matchNumber);
    }

    map<string, vector<double>> prob_matrix;
    // Iterate over the teams vector
    for (Team &team : teams)
    {
        // Initialize a vector of zeroes with size equal to the size of the teams vector
        vector<double> zeroes(teams.size(), 0);

        // Assign the vector of zeroes to the team in prob_matrix
        prob_matrix[team.name] = zeroes;
    }
    check(teams, upcoming_matches, prob_matrix, 1);
    for (auto entry : prob_matrix)
    {
        string team = entry.first;            // Access the key (Team)
        vector<double> values = entry.second; // Access the value (vector<int>)

        // Print the team
        cout << "Team: " << team << endl;

        // Print the vector of values
        cout << "Values: ";
        for (double value : values)
        {
            cout << value << "     ";
        }
        cout << endl;
    }
    return 0;
}
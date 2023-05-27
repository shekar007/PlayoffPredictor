
# IPL Playoff Predictor

The IPL Playoff Predictor is a C++ program that predicts the probabilities of teams qualifying for the playoffs based on their current standings, upcoming matches, and a set of rules. <br/>
(It predicts the 3 teams which would mostly face CSK in the finals :) )


## Input
The program expects two input files in a specific format:

testpoints.txt: This file contains the current standings of teams in the IPL. Each line represents a team and should have the following format:
```
TeamName, Points, NRR
```
testmatches.txt: This file contains information about upcoming matches. Each line represents a match and should have the following format:
```
Team1Name, Team2Name, MatchNumber
```
## Program Logic
Read team standings from testpoints.txt and store them in a vector of Team objects.
Read upcoming matches from testmatches.txt and store them in a vector of tuples (Team, Team, int).
Create a probability matrix, which is a map of Team objects to a vector of integers.
Use the check function to calculate the probabilities recursively, simulating match outcomes and updating the probabilities.
Display the results by iterating over the probability matrix and printing the team names with their corresponding probabilities.
## Run Locally

To run the program, follow these steps:

1. Create two input files: testpoints.txt and testmatches.txt, following the specified formats.
2. Save the C++ code in a file with the .cpp extension (e.g., ipl_playoff_predictor.cpp).

3. Compile the code using a C++ compiler
 ```
g++ code.cpp -o code
```

Run the compiled program  
```
./code
```
4. The program will display the predicted probabilities of teams qualifying for the playoffs based on the provided inputs.
5. PS : Note: Make sure to have the input files and the names are same in the code and in the same directory as the compiled program.

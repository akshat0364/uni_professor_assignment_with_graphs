#include <bits/stdc++.h>

using namespace std;

void readFile(vector<vector<string>>& data,const string csvFilePath)
{
    // Open the CSV file for reading
    ifstream file(csvFilePath);
    // Check if the file is successfully opened
    if (!file.is_open()) cerr << "Error opening file: " << csvFilePath << endl;
    // Read each line from the file
    string line;
    while (getline(file, line)) 
    {
        // Use a stringstream to split the line into individual values
        stringstream ss(line);
        string value;
        vector<string> row;
        while (getline(ss, value, ',')) row.push_back(value);
        // Add the row to the data vector
        data.push_back(row);
    }
    // Close the file
    file.close();
}
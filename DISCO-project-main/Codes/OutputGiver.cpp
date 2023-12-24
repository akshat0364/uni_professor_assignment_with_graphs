#include <bits/stdc++.h>

using namespace std;

void makeOutputFile(vector<array<string,4>> v, string filename)
{
    ofstream outData;
    // Open the CSV file in append mode
    outData.open(filename, ios::app);
    // Check if the file is successfully opened
    if (!outData.is_open()) cout << "Error opening file." << endl;

    for(auto i : v)
    {
        for(int j=0;j<4;j++)
        {
            // Write the string and integer to the CSV file in separate columns
            outData<<i[j]<<",";
        }
        outData<<endl;
    }
    
    // Close the file
    outData.close();
}
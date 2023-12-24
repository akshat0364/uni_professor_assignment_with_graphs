#include <bits/stdc++.h>
#include "Graph.cpp"
#include "InputReader.cpp"

using namespace std;

typedef struct
{
    string name;
    double remSlot;
    double category;
} Professor;

typedef struct 
{
    string name;
    double distributed;
} Course;

string dataFile="random_data.csv";

bool isCourseAdded(vector<Course> v,Course c)
{
    for(auto i:v)
    {
        if(i.name==c.name) return 0;
    }
    return 1;
}

void distribute(vector<Course>& v,string c, int distributed)
{
    for(auto& i:v)
    {
        if(i.name==c) 
        {
            i.distributed=distributed;
        }
    }
}

int getDistribute(vector<Course>& v,string c)
{
    for(auto& i:v)
    {
        if(i.name==c) 
        {
            return i.distributed;
        }
    }
}

void getData(Graph& preference, vector<Professor>& professors, vector<Course>& cdc, vector<Course>& elec)
{
    vector<vector<string>> data;
    readFile(data,dataFile);

    int r=0,c=0;
    for(auto row : data)
    {
        if(r==0) {r++;continue;}
        int pref=1;
        for(auto cell : row)
        {
            string profName=row.front();
            if(c==0)
            {
                string s=row.back();
                double category=(s=="X1")?0.5:((s=="X2")?1.0:1.5);
                professors.push_back({cell,category,category});
            }
            else if(c==5) continue;
            else if(c==1||c==2)
            {
                int prev=0;
                for(int i=0;i<cell.length();i++)
                {
                    if(cell[i]==';')
                    {
                        string courseName=cell.substr(prev,i-prev);
                        Course c={courseName,0};
                        if(isCourseAdded(cdc,c))
                        cdc.push_back(c);
                        if(!preference.checkEdge(profName,courseName))
                        preference.addEdge(profName,courseName,pref++);
                        prev=i+1;
                    }
                }             
            }
            else if(c==3||c==4)
            {
                int prev=0;
                for(int i=0;i<cell.length();i++)
                {
                    if(cell[i]==';')
                    {
                        string courseName=cell.substr(prev,i-prev);
                        Course c={courseName,0};
                        if(isCourseAdded(elec,c))
                        elec.push_back(c);
                        if(!preference.checkEdge(profName,courseName))
                        preference.addEdge(profName,courseName,pref++);
                        prev=i+1;
                    }
                }             
            }
            c++;
        }
        c=0;
        r++;
    }
}
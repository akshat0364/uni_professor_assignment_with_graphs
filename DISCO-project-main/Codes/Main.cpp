#include <bits/stdc++.h>
#include <windows.h>
#include <chrono>
#include "DataReader.cpp"
#include "OutputGiver.cpp"

using namespace std;

Graph preference;
vector<Professor> professors;  
vector<Course> cdc,elec;
vector<Graph> optimalGraphs, lessOptimalGraphs;
const char* pyCommand = "python random_1.py";
int x1=0,x2=0,x3=0;

void generatePreferenceList()
{
    // Using the system() function to run the command
    int result = system(pyCommand);

    // Check the result
    if (result != 0)
    cerr << "Error executing Python script." <<endl;
}

bool isValidOutput(Graph& allotment) // To check if an output is valid
{
    for(auto i : cdc)
    {
        if(i.distributed==0) return 0;
    }
    for(auto i : optimalGraphs)
    {
        if(allotment.equalTo(i)) return 0;
    }
    return 1;
}

void randomiseVectors(int t) //Randomising the data for different possibilities
{
    srand(t+time(0));
    shuffle(professors.begin(), professors.end(), default_random_engine(rand()));
    shuffle(cdc.begin(), cdc.end(), default_random_engine(rand()));
    shuffle(elec.begin(), elec.end(), default_random_engine(rand()));
}

void assignCourses(Graph& allotment) //Logic to assign different courses to professsors 
{
    //Alloting cp course to 3 professors
    string cp="CS F11";
    int count=3;
    for(int pref=1;pref<=4;pref++)
    {
        if(count==0) break;
        for(auto& i : professors)
        {
            if(count==0) break;
            if(i.remSlot>=1 && ((preference.getCourses(i.name))[pref-1]).first==cp)
            {
                allotment.addEdge(cp, i.name, 1);
                i.remSlot--;
                distribute(cdc, cp, 1);
                count--;
            }
        }
    }

    //Alloting entire cdcs to X2,X3 professors according to preference
    for(int pref=1;pref<=6;pref++)
    {
        for(auto& i : cdc)
        {
            for(auto& j : professors)
            {
                if(j.remSlot>=1 && ((preference.getCourses(j.name))[pref-1]).first==i.name && i.distributed==0)
                {
                    allotment.addEdge(i.name, j.name, 1);
                    j.remSlot--;
                    i.distributed=1;
                    break;
                }
            }
        }
    }
    
    //Alloting full cdcs to remaining X2,X3 professors irrespective of preference order
    for(auto& i : professors)
    {
        if(i.remSlot>=1)
        {
            for(auto& j : preference.getCourses(i.name))
            {
                if(getDistribute(cdc, j.first)==0)
                {
                    allotment.addEdge(j.first, i.name, 1);
                    i.remSlot--;
                    distribute(cdc, j.first, 1);
                    break;
                }
            }
        }
    }

    // Alloting half cdcs to two X1 professors
    for(auto& i : cdc)
    {
        if(i.distributed==0)
        {
            for(auto& j : professors)
            {
                if(preference.checkEdge(j.name,i.name) && i.distributed==0 && j.remSlot>=0.5 & j.category==0.5)
                {
                    for(auto& k : professors)
                    {
                        if(j.name!=k.name && preference.checkEdge(k.name,i.name) && k.remSlot>=0.5 && i.distributed==0 &&k.category==0.5)
                        {
                            allotment.addEdge(i.name, j.name, 0.5);
                            allotment.addEdge(i.name, k.name, 0.5);
                            j.remSlot-=0.5;
                            k.remSlot-=0.5;
                            i.distributed=1;
                            break;
                        }
                    }
                }
            }
        }
    }

    // Alloting half cdcs to one x1 professor and another professor
    for(auto& i : cdc)
    {
        if(i.distributed==0)
        {
            for(auto& j : professors)
            {
                if(preference.checkEdge(j.name,i.name) && i.distributed==0 && j.remSlot>=0.5 && j.category==0.5)
                {
                    for(auto& k : professors)
                    {
                        if(j.name!=k.name && preference.checkEdge(k.name,i.name) && k.remSlot>=0.5 && i.distributed==0)
                        {
                            allotment.addEdge(i.name, j.name, 0.5);
                            allotment.addEdge(i.name, k.name, 0.5);
                            j.remSlot-=0.5;
                            k.remSlot-=0.5;
                            i.distributed=1;
                            break;
                        }
                    }
                }
            }
        }
    }

    //Allocating half cdcs to X1,X3 professors irrespective of preference order
    for(auto& i : cdc)
    {
        if(i.distributed==0)
        {
            for(auto& j : professors)
            {
                if(preference.checkEdge(j.name,i.name) && i.distributed==0 && j.remSlot>=0.5)
                {
                    for(auto& k : professors)
                    {
                        if(j.name!=k.name && preference.checkEdge(k.name,i.name) && k.remSlot>=0.5 && i.distributed==0)
                        {
                            allotment.addEdge(i.name, j.name, 0.5);
                            allotment.addEdge(i.name, k.name, 0.5);
                            j.remSlot-=0.5;
                            k.remSlot-=0.5;
                            i.distributed=1;
                            break;
                        }
                    }
                }
            }
        }
    }

    //Alloting full elecs to remaining X2,X3 professors with preference order
    for(int pref=7;pref<=12;pref++)
    {
        for(auto& i : elec)
        {
            for(auto& j : professors)
            {
                if(j.remSlot>=1 && ((preference.getCourses(j.name))[pref-1]).first==i.name && i.distributed==0)
                {
                    allotment.addEdge(i.name, j.name, 1);
                    j.remSlot--;
                    i.distributed=1;
                    break;
                }
            }
        }
    }

    //Alloting as much half elec to X1,X3 irrespective of preference order
    for(auto& i : elec)
    {
        if(i.distributed==0)
        {
            for(auto& j : professors)
            {
                if(preference.checkEdge(j.name,i.name) && i.distributed==0 && j.remSlot>=0.5)
                {
                    for(auto& k : professors)
                    {
                        if(j.name!=k.name && preference.checkEdge(k.name,i.name) && k.remSlot>=0.5 && i.distributed==0)
                        {
                            allotment.addEdge(i.name, j.name, 0.5);
                            allotment.addEdge(i.name, k.name, 0.5);
                            j.remSlot-=0.5;
                            k.remSlot-=0.5;
                            i.distributed=1;
                            break;
                        }
                    }
                }
            }
        }
    }
}

void reset()
{
    for(auto& i : cdc) i.distributed=0;
    for(auto& i : elec) i.distributed=0;
    for(auto& i : professors) i.remSlot=i.category;
}

void outputGraphs() // Creates the output files
{
    int optimalCount=1, lessOptimalCount=1;
    srand(time(0));
    string Folder = "Outputs"+to_string(rand());
    string optimalFolder="Optimal_Outputs";
    string lessOptimalFolder="Less_Optimal_Outputs";
    if(CreateDirectory((Folder).c_str(), NULL)) cout<<"Folder "<<Folder<<" created succesfully."<<endl;
    else if(system(("mkdir "+Folder).c_str())==0) cout<<"Folder "<<Folder<<" created succesfully."<<endl;
    else Folder="";
    if(CreateDirectory((Folder+"\\"+optimalFolder).c_str(), NULL)){}
    else if(system(("mkdir "+Folder+"\\"+optimalFolder).c_str())==0){}
    else optimalFolder="";

    for(auto i : optimalGraphs) // To output the optimal solutins
    {
        vector<array<string,4>> v;
        v.push_back({"Course","Professor 1","Professor 2","Professor 3"});
        for(auto j : i.adjacencyList)
        {
            array<string,4> s={"","","",""};
            s[0]=j.first;
            int p=1;
            for(auto k : j.second)
            {
                string n=(k.second==0.5)?"0.5":"1";
                s[p++]=k.first+" ("+n+")";
            }
            v.push_back(s);
        }   
        makeOutputFile(v,Folder+"\\"+optimalFolder+"\\out"+to_string(optimalCount++)+".csv");
    }

    if(CreateDirectory((Folder+"\\"+lessOptimalFolder).c_str(), NULL)){}
    else if(system(("mkdir "+Folder+"\\"+lessOptimalFolder).c_str())==0){}
    else lessOptimalFolder="";
    for(auto i : lessOptimalGraphs) // To output the less optimal solutions
    {
        vector<array<string,4>> v;
        v.push_back({"Course","Professor 1","Professor 2","Professor 3"});
        for(auto j : i.adjacencyList)
        {
            array<string,4> s={"","","",""};
            s[0]=j.first;
            int p=1;
            for(auto k : j.second)
            {
                string n=(k.second==0.5)?"0.5":"1";
                s[p++]=k.first+" ("+n+")";
            }
            v.push_back(s);
        }   
        makeOutputFile(v,Folder+"\\"+lessOptimalFolder+"\\out"+to_string(lessOptimalCount++)+".csv");
    }
}

void checkStatistics(Graph allotment,
    int* x11, int* x21, int* x22, int* x31, int* x32, int* x33, 
    int* firstPref, int* secPref, int* cdcGiven, int* elecGiven) // 
{
    for(auto i : professors)
    {
        if(i.category==0.5&&i.remSlot==0.5) (*x11)++;
        else if(i.category==1&&i.remSlot==1) (*x21)++;
        else if(i.category==1&&i.remSlot==0.5) (*x22)++;
        else if(i.category==1.5&&i.remSlot==1.5) (*x31)++;
        else if(i.category==1.5&&i.remSlot==1) (*x32)++;
        else if(i.category==1.5&&i.remSlot==0.5) (*x33)++;
        if(allotment.checkEdge((preference.getCourses(i.name))[0].first,i.name)) (*firstPref)++;
        else if(allotment.checkEdge((preference.getCourses(i.name))[1].first,i.name)) (*secPref)++;
    }
    for(auto i : cdc)
    {
        if(i.distributed==1) (*cdcGiven)++;
    }
    for(auto i : elec)
    {
        if(i.distributed==1) (*elecGiven)++;
    }
}

void countProfs()
{
    for(auto i : professors)
    {
        if(i.category==0.5) x1++;
        else if(i.category==1) x2++;
        else if(i.category==1.5) x3++;
    }
}

void printStatistics(int runs,int x11, int x21, int x22, int x31, int x32, int x33, 
    int firstPref, int secPref, int cdcGiven, int elecGiven)
    {
        cout<<(int)((1.0*x11/(runs*x1))*100.0)<<"% X1 Professors were alloted 0 course."<<endl;
        cout<<(int)((1.0*x21/(runs*x2))*100.0)<<"% X2 Professors were alloted 0 course."<<endl;
        cout<<(int)((1.0*x22/(runs*x2))*100.0)<<"% X2 Professors were alloted 0.5 course."<<endl;
        cout<<(int)((1.0*x31/(runs*x3))*100.0)<<"% X3 Professors were alloted 0 course."<<endl;
        cout<<(int)((1.0*x32/(runs*x3))*100.0)<<"% X3 Professors were alloted 0.5 course."<<endl;
        cout<<(int)((1.0*x33/(runs*x3))*100.0)<<"% X3 Professors were alloted 1 course."<<endl;
        cout<<(int)((1.0*firstPref/(runs*professors.size()))*100.0)<<"% Professors were alloted their First preference."<<endl;
        cout<<(int)((1.0*secPref/(runs*professors.size()))*100.0)<<"% Professors were alloted their Second preference."<<endl;
        cout<<(int)((1.0*cdcGiven/(runs*cdc.size()))*100.0)<<"% CDCs were alloted."<<endl;
        cout<<(int)((1.0*elecGiven/(runs*elec.size()))*100.0)<<"% Electives were alloted."<<endl;
    }

    void printStatistics(int x11, int x21, int x22, int x31, int x32, int x33, 
    int firstPref, int secPref, int cdcGiven, int elecGiven)
    {
        cout<<(int)((1.0*x11/(x1))*100.0)<<"% X1 Professors were alloted 0 course."<<endl;
        cout<<(int)((1.0*x21/(x2))*100.0)<<"% X2 Professors were alloted 0 course."<<endl;
        cout<<(int)((1.0*x22/(x2))*100.0)<<"% X2 Professors were alloted 0.5 course."<<endl;
        cout<<(int)((1.0*x31/(x3))*100.0)<<"% X3 Professors were alloted 0 course."<<endl;
        cout<<(int)((1.0*x32/(x3))*100.0)<<"% X3 Professors were alloted 0.5 course."<<endl;
        cout<<(int)((1.0*x33/(x3))*100.0)<<"% X3 Professors were alloted 1 course."<<endl;
        cout<<(int)((1.0*firstPref/(professors.size()))*100.0)<<"% Professors were alloted their First preference."<<endl;
        cout<<(int)((1.0*secPref/(professors.size()))*100.0)<<"% Professors were alloted their Second preference."<<endl;
        cout<<(int)((1.0*cdcGiven/(cdc.size()))*100.0)<<"% CDCs were alloted."<<endl;
        cout<<(int)((1.0*elecGiven/(elec.size()))*100.0)<<"% Electives were alloted."<<endl;
    }

int main()
{
    // Run this main function to get the desirable outputs
    // NOTE : Separate output folder might not be created depending on the platform where the code is run
    auto start = chrono::high_resolution_clock::now();
    ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL);
    int counter=1;
    generatePreferenceList();
    preference.adjacencyList.clear();professors.clear();cdc.clear();elec.clear();
    //Storing data from input files 
    getData(preference, professors, cdc, elec);
    x1=0,x2=0,x3=0;countProfs();
    int runs=100;
    for(int t=0;t<runs;t++)
    {   
        int x11=0,x21=0,x22=0,x31=0,x32=0,x33=0,firstPref=0,secPref=0,cdcGiven=0,elecGiven=0;
        Graph allotment; 

        randomiseVectors(t);

        assignCourses(allotment);    

        if(isValidOutput(allotment)) 
        {
            cout<<endl;
            cout<<"Graph "<<counter<<" : "<<endl;
            checkStatistics(allotment,&x11,&x21,&x22,&x31,&x31,&x33,&firstPref,&secPref,&cdcGiven,&elecGiven);
            printStatistics(x11,x21,x22,x31,x31,x33,firstPref,secPref,cdcGiven,elecGiven);
            if(x33==0) optimalGraphs.push_back(allotment);
            else if(x11==0&&x21==0&&x22==0&&x31==0&&x32==0) lessOptimalGraphs.push_back(allotment);
            cout<<endl;
        }
        
        reset();
        counter++;
    }

    outputGraphs();
    
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "Execution time: " << duration << " ms" <<endl;

    getchar();
    return 0;
}
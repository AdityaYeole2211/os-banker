#include <iostream>
#include <vector>
using namespace std;
const int num_resources = 3;
const int num_process = 5;
void calculateNeed(int allocate[][num_resources], int maxNeed[][num_resources], vector<vector<int>>& remNeed)
{
    for (int i = 0; i < num_process; i++)
    {
        for (int j = 0; j < num_resources; j++)
        {
            remNeed[i][j] = maxNeed[i][j] - allocate[i][j];
        }
    }
}
bool isSafe(int allocate[][num_resources], int maxNeed[][num_resources], int available[])
{
    vector<vector<int>> remNeed;
    calculateNeed(allocate, maxNeed, remNeed);
    vector<bool> finished(num_process, false);
    vector<int> ans;
    int count = 0;
    while (count < num_process)
    {
        bool found = false;
        for (int i = 0; i < num_process; i++)
        {
            if (!finished[i])
            {
                cout<<"checkign for prciess "<<i<<endl;
                int j;
                for (j = 0; j < num_resources; j++)
                {
                    if (remNeed[i][j] > available[j])
                    {
                        break;
                    }
                }
                if (j == num_resources)
                {
                    for (int k = 0; k < num_resources; k++)
                    {
                        available[k] += allocate[i][k];
                    }
                    cout<<"entering in ans : "<<i+1<<endl;
                    ans.push_back(i + 1);
                    
                    found = true;
                    count++;
                    finished[i] = true;
                }
            }
        }

        if (!found)
        {
            cout << "not in safe sequence" << endl;
            return false;
        }
    }
    cout << "system in safe state" << endl;
    cout << "safe sequence: " << endl;
    for (int i = 0; i < ans.size(); i++)
    {
        cout << "P" << ans[i] << " " << "->" << " ";
    }
    return true;
}
int main()
{

    int total[] = {10, 5, 7};

    // allocate matrix
    int allocate[num_process][num_resources] = {{0, 1, 0},
                                                {2, 0, 0},
                                                {3, 0, 2},
                                                {2, 1, 1},
                                                {0, 0, 2}};

    int maxNeed[num_process][num_resources] = {{7, 5, 3},
                                               {3, 2, 2},
                                               {9, 0, 2},
                                               {4, 2, 2},
                                               {5, 3, 3}};

    int available[num_resources];
    int num1, num2, num3 = 0;
    for (int i = 0; i < num_process; i++)
    {
        num1 += allocate[i][0];
    }
    for (int i = 0; i < num_process; i++)
    {
        num2 += allocate[i][1];
    }
    for (int i = 0; i < num_process; i++)
    {
        num3 += allocate[i][2];
    }

    available[0] = total[0] - num1;
    available[1] = total[1] - num2;
    available[2] = total[2] - num3;
    bool ans = isSafe(allocate, maxNeed, available);
}
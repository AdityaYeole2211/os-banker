#include <iostream>
#include <vector>
using namespace std;

const int num_resources = 3;
const int num_process = 5;

void calculateNeed(int allocate[][num_resources], int maxNeed[][num_resources], vector<vector<int>> &remNeed)
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
    vector<vector<int>> remNeed(num_process, vector<int>(num_resources, 0));
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
                    ans.push_back(i + 1);
                    found = true;
                    count++;
                    finished[i] = true;
                }
            }
        }

        if (!found)
        {
            cout << "System is not in a safe state" << endl;
            return false;
        }
    }
    cout << "System is in a safe state" << endl;
    cout << "Safe sequence: ";
    for (int i = 0; i < ans.size(); i++)
    {
        cout << "P" << ans[i] << " ";
    }
    cout << endl;
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

    for (int i = 0; i < num_resources; i++)
    {
        int total_alloc = 0;
        for (int j = 0; j < num_process; j++)
        {
            total_alloc += allocate[j][i];
        }
        available[i] = total[i] - total_alloc;
    }

    isSafe(allocate, maxNeed, available);
}

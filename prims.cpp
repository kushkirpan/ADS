#include <iostream>
#include <climits>
using namespace std;
#define V 5
int main()
{
    string dept[V] = {"CSE", "IT", "MECH", "CIVIL", "ENTC"};
    int Graph[V][V] = {
        {0, 4, 0, 5, 2},
        {4, 0, 1, 3, 0},
        {0, 1, 0, 8, 0},
        {5, 3, 8, 0, 2},
        {2, 0, 0, 2, 0}};
    int visited[V] = {0};
    visited[0] = 1;
    int totalCost = 0, no_edges = 0;
    while (no_edges < V - 1)
    {
        int min = INT_MAX, row = 0, col = 0;
        for (int i = 0; i < V; i++)
        {
            if (visited[i])
            {
                for (int j = 0; j < V; j++)
                {
                    if (!visited[j] && Graph[i][j] != 0 && Graph[i][j] < min)
                    {
                        min = Graph[i][j];
                        row = i;
                        col = j;
                    }
                }
            }
        }
        cout << dept[row] << " - " << dept[col] << " : " << min << endl;
        visited[col] = 1;
        totalCost += min;
        no_edges++;
    }
    cout << "Total edges: " << no_edges << endl;
    cout << "Total cost: " << totalCost;
    return 0;
}
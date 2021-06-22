#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

int best_index[2];
int population[4][9];
int offspring[2][8];
int generation = 0;
int elite;
int previ = 65536, curr = 65536;

int pow(int x, int y)
{
    int ans = 1;
    for (int i = 0; i < y; i++)
        ans *= x;
    return ans;
}

void initial()
{
    //srand(time(NULL)); // 以時間作為種子防止 rand() 產生出得亂數都為相同。

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            population[i][j] = rand() % 2;
        }
    }
}

void fitness()
{
    for (int i = 0; i < 4; i++)
    {
        population[i][8] = 0;
        for (int j = 0; j < 8; j++)
            population[i][8] += population[i][7 - j] * pow(2, j);
        curr = population[0][8];
        elite = 0;
        if (population[i][8] < curr)
        {
            curr = population[i][8];
            elite = i;
        }
    }
    cout << "Generations: " << generation << "; Best fitness: " << curr << endl;
}

void find_best()
{
    int point1, point2;
    int prepoint1, prepoint2;
    int min1 = population[0][8], min2 = population[0][8];
    best_index[0] = 0;
    best_index[1] = 0;

    point1 = rand() % 4;
    point2 = rand() % 4;
    while (point1 == point2)
        point2 = rand() % 4;

    prepoint1 = point1;
    prepoint2 = point2;

    if (population[point1][8] < population[point2][8])
        best_index[0] = point1;
    else
        best_index[0] = point2;

    while (prepoint1 == point1)
        point1 = rand() % 4;
    while (prepoint2 == point2)
        point2 = rand() % 4;

    if (population[point1][8] < population[point2][8])
        best_index[1] = point1;
    else
        best_index[1] = point2;

    // for (int i = 0; i < 4; i++)
    // {
    //     if (population[i][8] < min1)
    //     {
    //         // swap
    //         int temp = best_index[0];
    //         best_index[1] = temp;
    //         min2 = population[temp][8];

    //         best_index[0] = i;
    //         min1 = population[i][8];
    //     }

    //     else if (best_index[0] == best_index[1])
    //     {
    //         best_index[1] = i + 1;
    //         min2 = population[i + 1][8];
    //     }

    //     else if (population[i][8] < min2)
    //     {
    //         best_index[1] = i;
    //         min2 = population[i][8];
    //     }
    // }
}

void crossover()
{
    int z = 0;
    find_best();

    for (int j = 0; j < 4; j++)
    {
        offspring[0][j] = population[best_index[0]][j];
        offspring[1][j] = population[best_index[1]][j];
    }
    for (int j = 4; j < 8; j++)
    {
        offspring[0][j] = population[best_index[1]][j];
        offspring[1][j] = population[best_index[0]][j];
    }

    for (int i = 0; i < 4; i++)
    {
        if (i != best_index[0] && i != best_index[1])
        {
            for (int j = 0; j < 8; j++)
                population[i][j] = offspring[z][j];
            z++;
        }
    }
}

void mutation()
{
    int point1, point2, temp;
    point1 = rand() % 8;
    point2 = rand() % 8;
    while (point1 == point2)
        point2 = rand() % 8;
    temp = population[elite][point1];
    population[elite][point1] = population[elite][point2];
    population[elite][point2] = temp;
}

void print_population()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 8; j++)
            cout << population[i][j];
        cout << endl;
    }
}

int main()
{
    initial();
    fitness();
    previ = curr;
    while (curr != 0)
    {
        crossover();
        fitness();
        if (curr == previ)
            mutation();
        print_population();
        previ = curr;
        generation++;
    }
    cout << "Generations: " << generation << "; Best ftiness: " << curr;

    return 0;
}
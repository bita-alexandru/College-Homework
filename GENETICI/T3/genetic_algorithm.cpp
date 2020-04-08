#include <bits/stdc++.h>
#define RUN_TIMES 10
#define GENERATIONS 1000

using namespace std;
using Clock = chrono::high_resolution_clock;

string Title;

int BestKnown;
int N;

vector<vector<int>> CData;
vector<vector<int>> Population;
vector<int> Fitness;

int BestValue;
double AvgValue, StDev, PError;
int FitnessSum;
double FitnessAvg;

vector<int> Results;

chrono::duration<double> AvgTime;
default_random_engine Generator;

void readData()
{
    ifstream in("ga_input.txt");

    in >> Title;
    in >> BestKnown;

    in >> N;

    CData.resize(N,vector<int>(N));
    Fitness.resize(N);
    Results.resize(N);

    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++) in >> CData[i][j];

    in.close();

    Generator.seed(Clock::now().time_since_epoch().count());
}

void displayResults()
{
    ofstream out("ga_output.txt", ios::out | ios::app);

    out << "----------------------------------------------------------------------------------------------------------------------------------------\n";
    out << "Problem: " << Title << '\n';

    out << fixed << setprecision(2);

    out << "Best Known: " << BestKnown << '\n';
    out << "Best Value: " << BestValue << '\n';
    out << "Average Value: " << AvgValue << '\n';
    out << "Standard Deviation: " << StDev << '\n';
    out << "Precision Error: " << PError << "%\n";
    out << "Average Time: " << AvgTime.count() << '\n';

    out.close();
}

int computeLength(vector<int> &Tour)
{
    int Length = 0;

    for(int i = 0; i < N; i++) Length += CData[Tour[i]][Tour[(i+1)%N]];

    return Length;
}

void generateSolution(vector<int> &Tour)
{
    for(int i = 0; i < N; i++) Tour[i] = i;
    random_shuffle(Tour.begin(), Tour.end());
}

void initPopulation()
{
    Population.clear();

    vector<int> X(N);
    generateSolution(X);
    Population.push_back(X);

    int IndexElite = 0;
    int LengthElite = computeLength(X);
    Fitness[0] = LengthElite;

    for(int i = 1; i < N; i++)
    {
        generateSolution(X);
        Population.push_back(X);

        int Length = computeLength(X);
        Fitness[i] = Length;

        if(Length < LengthElite)
        {
            LengthElite = Length;
            IndexElite = i;
        }
    }

    swap(Population[0],Population[IndexElite]);
    swap(Fitness[0],Fitness[IndexElite]);
}

void selection()
{
    vector<vector<int>> PopulationNew;
    PopulationNew.push_back(Population[0]);

    vector<double> Probs;
    for(int i = 0; i < N; i++) Probs.push_back(1.*Fitness[i]/FitnessSum);

    uniform_real_distribution<double> DisP(0,1);

    int cnt = 1;

    for(int i = 1; i < N; i++)
    {
        double r = DisP(Generator);

        if(r > Probs[i])
        {
            PopulationNew.push_back(Population[i]);
            Fitness[cnt++] = Fitness[i];
            if(cnt == N) break;
        }

        if(i == N-1) i = -1;
    }

    Population = PopulationNew;
}

void crossover()
{
    uniform_real_distribution<double> DisX(0,1);
    uniform_int_distribution<int> DisPMX(0,N-1);

    int EliteLength = computeLength(Population[0]);

    FitnessSum = 0;
    FitnessAvg = 0;

    for(int i = 1; i < N; i++)
    {
        double r = DisX(Generator);

        if(r < 0.4)
        {
            int a = DisPMX(Generator);
            int b = DisPMX(Generator);

            if(a > b) swap(a,b);

            vector<int> Offspring = Population[0];

            int pos1, pos2;

            for(int j = a; j <= b; j++)
            {
                int A = Population[0][j];
                int B = Population[i][j];

                for(int k = 0; k < N; k++)
                {
                    if(Offspring[k] == A) pos1 = k;
                    else if(Offspring[k] == B) pos2 = k;
                }

                if(A != B)
                {
                    Offspring[pos1] = B;
                    Offspring[pos2] = A;
                }
            }

            Population[i] = Offspring;

            int Length = computeLength(Population[i]);

            if(Length < EliteLength)
            {
                EliteLength = Length;
                Population[0] = Population[i];
                Fitness[0] = Length;
            }

            FitnessSum += Length;
            Fitness[i] = Length;
        }
        else
        {
            Fitness[i] = computeLength(Population[i]);
            FitnessSum += Fitness[i];
        }
    }

    FitnessSum += Fitness[0];
    FitnessAvg = FitnessSum / N;
}

void mutation()
{
    int EliteLength = Fitness[0];
    int Sum = 0;

    for(int i = 0; i < N; i++)
    {
        double p;

        if(Fitness[i] > FitnessAvg) p = 0.05*(Fitness[0]-Fitness[i])/(Fitness[0]-FitnessAvg);
        else p = 0.05;

        uniform_real_distribution<double> DisMut(0,1);
        uniform_int_distribution<int> DisSwap(0,N-1);

        for(int j = 0; j < N; j++)
        {
            double r = DisMut(Generator);

            if(r < p)
            {
                int k = DisSwap(Generator);
                swap(Population[i][j],Population[i][k]);
            }
        }

        Fitness[i] = computeLength(Population[i]);
        if(i > 0) Sum += Fitness[i];

        if(Fitness[i] < EliteLength)
        {
            Population[0] = Population[i];
            EliteLength = Fitness[i];
            Fitness[0] = EliteLength;
        }
    }

    Sum += Fitness[0];

    FitnessSum = Sum;
    FitnessAvg = Sum / N;
}

void reversal()
{
    vector<int> EliteVector = Population[0];
    uniform_int_distribution<int> DisRev(0,N-1);

    int a = DisRev(Generator);
    int b = a;

    for(int i = 1; i < N; i++) swap(Population[i][a],Population[i][b]);
}

void runAlgorithm()
{
    Clock::time_point StartPoint = Clock::now();

    for(int it = 0; it < RUN_TIMES; it++)
    {
        Clock::time_point StartIt = Clock::now();

        initPopulation();
        for(int i = 0; i < GENERATIONS; i++)
        {
            crossover();
            mutation();
            selection();
            reversal();
        }

        int LocalBest = computeLength(Population[0]);
        AvgValue += LocalBest;
        Results[it] = LocalBest;

        if(it == 0) BestValue = LocalBest;
        else if(BestValue > LocalBest) BestValue = LocalBest;

        Clock::time_point EndIt = Clock::now();
        chrono::duration<double> ItDuration = EndIt - StartIt;
        cout << it << '\t' << ItDuration.count() << '\n';
    }

    AvgValue /= RUN_TIMES;

    for(int i = 0; i < RUN_TIMES; i++) StDev += pow(Results[i]-AvgValue, 2);
    StDev = sqrt(StDev/RUN_TIMES);

    PError = (AvgValue - BestKnown) / BestKnown * 100;

    AvgTime = (Clock::now() - StartPoint) / RUN_TIMES;
}

int main()
{
    readData();
    runAlgorithm();
    displayResults();

    return 0;
}

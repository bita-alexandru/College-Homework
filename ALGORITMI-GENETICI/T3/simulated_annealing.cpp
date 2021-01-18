#include <bits/stdc++.h>
#define RUN_TIMES 30

using namespace std;
using Clock = chrono::high_resolution_clock;

string Title;

int BestKnown;
int N, M, K;

const int LSize = 120;

const double P0 = 0.05;

priority_queue<double> LData;
vector<vector<int>> CData;

int BestValue;
double AvgValue, StDev, PError;
chrono::duration<double> AvgTime;
vector<int> Results;
default_random_engine Generator;

void readData()
{
    ifstream in("input.txt");

    in >> Title;
    in >> BestKnown;

    in >> N; M = N;
    K = 1000;

    CData.resize(N,vector<int>(N));
    Results.resize(N);

    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++) in >> CData[i][j];

    in.close();

    Generator.seed(Clock::now().time_since_epoch().count());
}

void displayResults()
{
    ofstream out("output.txt", ios::out | ios::app);

    out << "----------------------------------------------------------------------------------------------------------------------------------------\n";
    out << "Problem: " << Title << '\n';

    out << fixed << setprecision(2);

    out << "Best Known: " << BestKnown << '\n';
    out << "Best Value: " << BestValue << '\n';
    out << "Average Value: " << AvgValue << '\n';
    out << "Standard Deviation: " << StDev << '\n';
    out << "Precision Error: " << PError << '\n';
    out << "Average Time: " << AvgTime.count() << '\n';

    out.close();
}

int computeLength(vector<int> &Tour)
{
    int Length = 0;

    for(int i = 0; i < N; i++) Length += CData[Tour[i]][Tour[(i+1)%N]];

    return Length;
}

pair<int,vector<int>> inverseOperator(int a, int b, vector<int> Tour)
{
    vector<int> Temp;

    if(a > b) swap(a,b);

    for(int i = 0; i < a; i++) Temp.push_back(Tour[i]);
    for(int i = b; i >= a; i--) Temp.push_back(Tour[i]);
    for(int i = b+1; i < N; i++) Temp.push_back(Tour[i]);

    return {computeLength(Temp), Temp};
}

pair<int,vector<int>> insertOperator(int a, int b, vector<int> Tour)
{
    vector<int> Temp;

    if(a < b)
    {
        for(int i = 0; i < a; i++) Temp.push_back(Tour[i]);
        Temp.push_back(Tour[b]);
        Temp.push_back(Tour[a]);

        for(int i = a+1; i < N; i++)
            if(i != b) Temp.push_back(Tour[i]);
    }
    else if(a > b)
    {
        for(int i = 0; i < b; i++) Temp.push_back(Tour[i]);
        for(int i = b+1; i < a; i++) Temp.push_back(Tour[i]);
        Temp.push_back(Tour[a]);
        Temp.push_back(Tour[b]);
        for(int i = a+1; i < N; i++) Temp.push_back(Tour[i]);
    }
    else Temp = Tour;

    return {computeLength(Temp), Temp};
}

pair<int,vector<int>> swapOperator(int a, int b, vector<int> Tour)
{
    swap(Tour[a], Tour[b]);

    return {computeLength(Tour), Tour};
}

vector<int> generateSolution()
{
    vector<int> Tour(N);
    for(int i = 0; i < N; i++) Tour[i] = i;

    random_shuffle(Tour.begin(), Tour.end());

    return Tour;
}

vector<int> createNeighbour(vector<int> Tour)
{
    uniform_int_distribution<int> DisAB(0,N-1);
    int a = (DisAB(Generator) + 1) % N;
    int b = DisAB(Generator);

    vector<pair<int,vector<int>>> Tours = {inverseOperator(a,b,Tour), insertOperator(a,b,Tour), swapOperator(a,b,Tour)};
    sort(Tours.begin(), Tours.end());

    return Tours[0].second;
}

vector<int> initLData()
{
    priority_queue<double> ClearLData;
    swap(LData,ClearLData);

    vector<int> X = generateSolution();

    while(LData.size() < LSize)
    {
        vector<int> Y = createNeighbour(X);

        int LenX = computeLength(X);
        int LenY = computeLength(Y);

        if(LenY < LenX) X = Y;

        double T = (-abs(1.*LenY-LenX))/log(P0);
        LData.push(T);
    }

    return X;
}

void runAlgorithm()
{
    Clock::time_point StartPoint = Clock::now();

    for(int it = 0; it < RUN_TIMES; it++)
    {
        Clock::time_point StartIt = Clock::now();

        vector<int> X = initLData();

        for(int k = 0; k < K; k++)
        {
            int c = 0;
            double t = 0;
            double TMax = LData.top();

            for(int m = 0; m < M; m++)
            {
                vector<int> Y = createNeighbour(X);

                int LenX = computeLength(X);
                int LenY = computeLength(Y);

                if(LenY < LenX) X = Y;
                else
                {
                    double p = exp(-(1.*LenY-LenX)/TMax);

                    uniform_real_distribution<double> DisR(0,1);
                    double r = DisR(Generator);

                    if(r < p)
                    {
                        t += ((-(LenY - LenX)) / log(r));
                        c++;

                        X = Y;
                    }
                }

                if(LenX == BestKnown)
                {
                    m = M;
                    k = K;
                }
            }

            if(c != 0)
            {
                LData.pop();
                LData.push(t/c);
            }
        }

        int LocalBest = computeLength(X);
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

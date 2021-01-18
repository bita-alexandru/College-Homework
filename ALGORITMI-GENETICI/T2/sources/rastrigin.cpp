#include <iostream>
#include <fstream>
#include <iomanip>
#include <bitset>
#include <vector>
#include <chrono>
#include <random>
#include <cmath>

#define DEBUG chrono::duration<double> timer = Clock::now() - clk; \
              cout << i << '\t' << timer.count() << '\n';

using namespace std;
using Clock = chrono::high_resolution_clock;

ofstream out;

const double MIN = -5.12;
const double MAX = 5.12;
const double EPSILON = 0.00001;
const double PM = 0.01;
const double PC = 0.3;

int N;
const int SIZE = 100;
const int BITS = 20;
const int GENERATIONS = 1000;
const double PI = 3.14159;
const double E = 2.71828;

bitset<BITS> LOWEST, HIGHEST;
vector<vector<bitset<BITS>>> pop;
vector<double> fitness;
vector<double> results;

double fmx, avg_fit;
double stdev;

Clock::time_point clk;
chrono::duration<double> avg_time;

default_random_engine generator;
uniform_int_distribution<int> i01(0,1);
uniform_real_distribution<double> d01(0.,1.);

double to_real(string bitstring)
{
    bitset<BITS> bs(bitstring);

    double X = static_cast<double>(bs.to_ulong());
    double x = MIN + (MAX-MIN)/(pow(2.0,BITS)-1) * X;

    return x;
}

void display()
{
    avg_fit /= 30.;
    for(int i = 0; i < 30; i++) stdev += pow(results[i]-avg_fit, 2.);
    stdev = sqrt(stdev/30.);

    out << "----------------------------------------------------------------------------------------------------------------------------------------\n";
    out << "N:\t" << N << '\n';

    out << '\n';
    out << fixed << setprecision(5);

    out << "AVG_FIT:\t" << avg_fit << '\n';
    out << "STDEV:\t" << stdev << '\n';
    out << "AVG_TIME:\t" << avg_time.count() / 30. << '\n';
    out << '\n';
    out << "BEST[30]:\t"; for(int i = 0; i < 30; i++) out << results[i] << ' ';
    out << '\n';
}

double evaluate(vector<bitset<BITS>> &v)
{
    double fitness = 10.*N;

    for(int i = 0; i < N; i++)
    {
        double x = to_real(v[i].to_string());
        fitness += (x*x - 10.*cos(2.*PI*x));
    }

    return 1/fitness;
}

void init()
{
    generator.seed(Clock::now().time_since_epoch().count());

    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < N; j++)
            for(int k = 0; k < BITS; k++)
                pop[i][j][k] = i01(generator);

        fitness[i] = evaluate(pop[i]);
    }
}

void mutate()
{
    for(int i = 0; i < SIZE; i++)
        for(int j = 0; j < N; j++)
            for(int k = 0; k < BITS; k++)
                if(d01(generator) < PM)
                    pop[i][j][k] = !pop[i][j][k];
}

void crossover()
{
    for(int i = 0; i < SIZE-1; i+=2)
        for(int j = 0; j < N; j++)
            if(d01(generator) < PC)
                for(int k = 0; k < BITS; k++)
                {
                    int mask = i01(generator);
                    mask == 0 ? pop[i][j][k] = pop[i+1][j][j] : pop[i+1][j][k] = pop[i][j][k];
                }
}

void select()
{
    double sum = 0;

    for(int i = 0; i < SIZE; i++) sum += fitness[i];

    vector<vector<bitset<BITS>>> new_pop(SIZE, vector<bitset<BITS>>(N));
    uniform_real_distribution<double> d0sum(0,sum);

    for(int i = 0; i < SIZE; i++)
    {
        double r = d0sum(generator);
        double S = 0.;
        int k = 0;

        while(S <= r)
        {
            S += fitness[k];
            k++;
        }

        new_pop[i] = pop[k-1];
    }

    pop = new_pop;

    for(int i = 0; i < SIZE; i++) fitness[i] = evaluate(pop[i]);
}

void checkfit()
{
    fmx = fitness[0];

    for(int i = 1; i < SIZE; i++)
        if(fmx < fitness[i]) fmx = fitness[i];

    avg_fit += pow(fmx,-1);
}

void run()
{
    clk = Clock::now();
    out.open("rastrigin.txt", ios::out | ios::app);

    for(int i = 0; i < 30; i++)
    {
        init();

        for(int gen = 1; gen <= GENERATIONS; gen++)
        {
            mutate();
            crossover();
            select();
        }

        checkfit(); results[i] = pow(fmx,-1);
//        DEBUG;
    }

    avg_time = Clock::now() - clk;
    display();
}

int main()
{
    cout << "N: "; cin >> N;
    pop.resize(SIZE, vector<bitset<BITS>>(N)); fitness.resize(SIZE); results.resize(30);
    HIGHEST.set();

    run();
    return 0;
}

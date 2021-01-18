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

double fmx, favg;
double best_fit, avg_fit;
double stdev;

Clock::time_point clk;
chrono::duration<double> avg_time;

default_random_engine generator;
uniform_int_distribution<int> i01(0,1);
uniform_real_distribution<double> d01(0,1);

double bin_to_real(string bin)
{
    bitset<BITS> bs(bin);

    double X = static_cast<double>(bs.to_ulong());
    double x = MIN + (MAX-MIN)/(pow(2.0,BITS)-1) * X;

    return x;
}

char xorc(char a, char b) { return (a == b) ? '0' : '1'; }
char flip(char c) { return (c == '0') ? '1' : '0'; }

string bin_to_gray(string bin)
{
    string gray = "";
    gray += bin[0];

    for(int i = 1; i < BITS; i++) gray[i] = xorc(bin[i-1], bin[i]);

    return gray;
}

string gray_to_bin(string gray)
{
    string bin = "";
    bin += gray[0];

    for (int i = 1; i < BITS; i++)
        if (gray[i] == '0') bin += bin[i-1];
        else bin += flip(bin[i - 1]);

    return bin;
}

void display()
{
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
    double fitness = 0.;

    for(int i = 0; i < N; i++)
    {
        double x = bin_to_real(gray_to_bin(v[i].to_string()));
        fitness += (x*x);
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

        if(i == 0)
        {
            fmx = fitness[0];
            favg = 0;
        }

        favg += fitness[i];
        if(fmx < fitness[i]) fmx = fitness[i];
    }

    favg /= SIZE;
}

void mutate()
{
    for(int i = 0; i < SIZE; i++)
        for(int j = 0; j < N; j++)
        {
            double pm;

            if(fitness[i] > favg) pm = 0.5 * (fmx - fitness[i]) / (fmx - favg);
            else pm = 0.5;

            for(int k = 0; k < BITS; k++)
                if(d01(generator) < pm)
                    pop[i][j][k] = !pop[i][j][k];
        }
}

void crossover()
{
    for(int i = 0; i < SIZE-1; i+=2)
        for(int j = 0; j < N; j++)
        {
            double pc;
            double f = max(fitness[i], fitness[i+1]);

            if(f > favg) pc = (fmx - f) / (fmx - favg);
            else pc = 1;

            if(d01(generator) < pc)
                for(int k = 0; k < BITS; k++)
                {
                    int mask = i01(generator);
                    mask == 0 ? pop[i][j][k] = pop[i+1][j][j] : pop[i+1][j][k] = pop[i][j][k];
                }
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
        double S = 0;
        int k = 0;

        while(S <= r)
        {
            S += fitness[k];
            k++;
        }

        new_pop[i] = pop[k-1];
    }

    pop = new_pop;

    for(int i = 0; i < SIZE; i++)
    {
        fitness[i] = evaluate(pop[i]);

        if(i == 0)
        {
            fmx = fitness[0];
            favg = 0;
        }

        favg += fitness[i];
        if(fmx < fitness[i]) fmx = fitness[i];
    }

    favg /= SIZE;
}

void findbest()
{
    int poz = 0;
    fmx = fitness[0];

    for(int i = 1; i < SIZE; i++)
        if(fmx < fitness[i])
        {
            fmx = fitness[i];
            poz = i;
        }

    for(int i = 0; i < N; i++)
    {
        bool local = false;
        int it = 0;

        while(!local && it++ < 1000)
        {
            local = true;

            for(int j = 0; j < BITS; j++)
                if(pop[poz][i][j] == 0)
                {
                    pop[poz][i][j] = 1;

                    double f = evaluate(pop[poz]);

                    if(f > fmx)
                    {
                        fmx = f;
                        local = false;
                        break;
                    }
                    else pop[poz][i][j] = 0;
                }
                else
                {
                    pop[poz][i][j] = 0;

                    double f = evaluate(pop[poz]);

                    if(f > fmx)
                    {
                        fmx = f;
                        local = false;
                        break;
                    }
                    else pop[poz][i][j] = 1;
                }
        }
    }
}

void run()
{
    clk = Clock::now();
    out.open("sphere.txt", ios::out | ios::app);

    for(int i = 0; i < 30; i++)
    {
        init();

        for(int gen = 1; gen <= GENERATIONS; gen++)
        {
            mutate();
            crossover();
            select();
        }

        findbest(); results[i] = pow(fmx,-1); avg_fit += results[i];
        DEBUG;
    }

    avg_fit /= 30;
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

#include <algorithm>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <bitset>
#include <vector>
#include <chrono>
#include <random>
#include <cmath>
#include <map>

#define FUNC(x) (x*x*x - 60.*x*x + 900.*x + 100)
#define DEBUG chrono::duration<double> timer = Clock::now() - clk; \
              cout << i << '\t' << timer.count() << '\n';

using namespace std;
using Clock = chrono::high_resolution_clock;

ofstream out;

const double MIN = 0;
const double MAX = 31;
const double EPSILON = 1;

int N, O;
const int BITS = 5;
const int ITERATIONS = 100;

bitset<BITS> LOWEST, HIGHEST;
vector<bitset<BITS>> x_curr;
map<string,pair<vector<string>,vector<string>>> x_nhood;
vector<double> results;

double best_fit = 1.*INT_MIN;
double avg_fit = 0.;
double worst_fit = 1.*INT_MAX;
double stdev = 0.;

vector<pair<double,int>> landscape(MAX-MIN+1);
int csv[32][32];

Clock::time_point clk;
chrono::duration<double> avg_time;

default_random_engine generator;
uniform_int_distribution<int> distribution(0,1);

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
    out << "EPSILON:\t" << EPSILON << '\n';
    out << "ITERATIONS:\t" << ITERATIONS << '\n';

    out << '\n';

    out << "BEST_FIT:\t" << best_fit << '\n';
    out << "AVG_FIT:\t" << avg_fit << '\n';
    out << "WORST_FIT:\t" << worst_fit << '\n';
    out << '\n';
    out << "STDEV:\t" << stdev << '\n';
    out << '\n';

    vector<pair<double,int>> aux = landscape; sort(aux.begin(), aux.end());
    for(int i = 0; i < landscape.size(); i++)
    {
        int row = 0;

        for(int j = 0; j < aux.size(); j++)
            if(landscape[i].first == aux[j].first) break;
            else row++;

        csv[row][i] = landscape[i].second;
    }

    for(int i = 0; i < 32; i++, out << '\n')
        for(int j = 0; j < 32; j++)
            if(csv[i][j]) out << csv[i][j] << ',';
            else out << ',';

    out << '\n';
    out << fixed << setprecision(6);
    out << "AVG_TIME:\t" << avg_time.count() / 30. << '\n';
    out << "TOTAL_TIME:\t" << avg_time.count() << '\n';
    out << '\n';
}

double evaluate(vector<bitset<BITS>> &v)
{
    double fitness = 0.;

    for(int p = 0; p < N; p++)
    {
        double number = to_real(v[p].to_string());
        fitness += FUNC(number);
    }

    return fitness;
}

void NAHC()
{
    for(int i = 0; i < 30; i++)
    {
        double best_now = 1.*INT_MIN;
        for(int it = 0; it < ITERATIONS; it++)
        {
            // select x_curr[] at random
            for(int p = 0; p < N; p++)
                for(int q = 0; q < BITS; q++) x_curr[p][q] = distribution(generator);

            double fitness = evaluate(x_curr);

            for(int p = 0; p < N; p++)
            {
                bool local = false;
                bool keep_left = true, keep_right = true;
                while(!local)
                {
                    string curr_string = x_curr[p].to_string();
                    double curr_number = to_real(curr_string);
                    string bttr_string;
                    double new_fitness = fitness - FUNC(curr_number);

                    bool found = false;
                    vector<string> *left = &x_nhood[curr_string].first;
                    vector<string> *right = &x_nhood[curr_string].second;

                    int index = static_cast<int>(curr_number);
                    landscape[index].first = fitness;
                    landscape[index].second++;

                    int j = 0;
                    while(j < left->size() || j < right->size())
                    {
                        if(keep_left && j < left->size()) // left neighbours available
                        {
                            double number = to_real(left->at(j));
                            if(new_fitness + FUNC(number) > fitness)
                            {
                                found = true;
                                keep_right = false;
                                bttr_string = left->at(j);
                                fitness = new_fitness + FUNC(number);
                                break;
                            }
                        }

                        if(keep_right && j < right->size()) // right neighbours available
                        {
                            double number = to_real(right->at(j));
                            if(new_fitness + FUNC(number) > fitness)
                            {
                                found = true;
                                keep_left = false;
                                bttr_string = right->at(j);
                                fitness = new_fitness + FUNC(number);
                                break;
                            }
                        }

                        j++;
                    }

                    if(found)
                    {
                        bitset<BITS> bttr_nghbr(bttr_string);
                        x_curr[p] = bttr_nghbr;
                    }
                    else local = true;
                }
            }

            if(fitness > best_now) best_now = fitness;
        }

        results[i] = best_now;
        avg_fit += best_now;
        if(best_now > best_fit) best_fit = best_now;
        if(best_now < worst_fit) worst_fit = best_now;
        distribution.reset();
//        DEBUG;
    }
}

void SAHC()
{
    for(int i = 0; i < 30; i++)
    {
        double best_now = 1.*INT_MIN;
        for(int it = 0; it < ITERATIONS; it++)
        {
            // select x_curr[] at random
            for(int p = 0; p < N; p++)
                for(int q = 0; q < BITS; q++) x_curr[p][q] = distribution(generator);

            double fitness = evaluate(x_curr);

            for(int p = 0; p < N; p++)
            {
                bool local = false;
                bool keep_left = true, keep_right = true;
                while(!local)
                {
                    string curr_string = x_curr[p].to_string();
                    double curr_number = to_real(curr_string);
                    string bttr_string;
                    double new_fitness = fitness - FUNC(curr_number);

                    bool found = false;
                    vector<string> *left = &x_nhood[curr_string].first;
                    vector<string> *right = &x_nhood[curr_string].second;

                    int index = static_cast<int>(curr_number);
                    landscape[index].first = fitness;
                    landscape[index].second++;

                    int j = 0;
                    while(j < left->size() || j < right->size())
                    {
                        if(keep_left && j < left->size()) // left neighbours available
                        {
                            double number = to_real(left->at(j));
                            if(new_fitness + FUNC(number) > fitness)
                            {
                                found = true;
                                keep_right = false;
                                bttr_string = left->at(j);
                                fitness = new_fitness + FUNC(number);
                            }
                        }

                        if(keep_right && j < right->size()) // right neighbours available
                        {
                            double number = to_real(right->at(j));
                            if(new_fitness + FUNC(number) > fitness)
                            {
                                found = true;
                                keep_left = false;
                                bttr_string = right->at(j);
                                fitness = new_fitness + FUNC(number);
                            }
                        }

                        j++;
                    }

                    if(found)
                    {
                        bitset<BITS> bttr_nghbr(bttr_string);
                        x_curr[p] = bttr_nghbr;
                    }
                    else local = true;
                }
            }

            if(fitness > best_now) best_now = fitness;
        }

        results[i] = best_now;
        avg_fit += best_now;
        if(best_now > best_fit) best_fit = best_now;
        if(best_now < worst_fit) worst_fit = best_now;
        distribution.reset();
//        DEBUG;
    }
}

void inc_bitstring(string &bitstring)
{
    for(int i = bitstring.size()-1; i >= 0; i--)
    {
        if(bitstring[i] == '0')
        {
            bitstring[i] = '1';
            break;
        }

        bitstring[i] = '0';
    }
}

void dec_bitstring(string &bitstring)
{
    for(int i = bitstring.size()-1; i >= 0; i--)
    {
        if(bitstring[i] == '1')
        {
            bitstring[i] = '0';
            break;
        }

        bitstring[i] = '1';
    }
}

void init()
{
    N = 1;

    generator.seed(Clock::now().time_since_epoch().count());

    x_curr.resize(N);
    results.resize(30);

    HIGHEST.set();

    string curr = LOWEST.to_string(), neighbour;

    Clock::time_point start_timer = Clock::now();
    while(true)
    {
        vector<string> left, right;

        neighbour = curr;
        while(neighbour != LOWEST.to_string()) // left neighbours
        {
            dec_bitstring(neighbour);

            int diff = 0;
            for(int i = 0; i < BITS; i++)
            {
                if(curr[i] != neighbour[i]) diff++;
                if(diff > 1) break;
            }
            if(diff == 1) left.push_back(neighbour);
        }

        neighbour = curr;
        while(neighbour != HIGHEST.to_string()) // right neighbours
        {
            inc_bitstring(neighbour);

            int diff = 0;
            for(int i = 0; i < BITS; i++)
            {
                if(curr[i] != neighbour[i]) diff++;
                if(diff > 1) break;
            }
            if(diff == 1) right.push_back(neighbour);
        }

        x_nhood.insert({curr,{left,right}});

        if(curr == HIGHEST.to_string()) break;
        inc_bitstring(curr);
    }
    Clock::time_point end_timer = Clock::now();
    chrono::duration<double> dur = end_timer - start_timer;
//    cout << "Neighbourhood creation finished in " << dur.count() << " seconds." << '\n' << '\n';
}

void run()
{
    cout << "NAHC[1]/SAHC[2]: "; cin >> O;

    clk = Clock::now();

    if(O == 1)
    {
        out.open("f_NAHC.txt", ios::out | ios::app);
        NAHC();
        avg_time = Clock::now() - clk;
        display();
        return;
    }

    if(O == 2)
    {
        out.open("f_SAHC.txt", ios::out | ios::app);
        SAHC();
        avg_time = Clock::now() - clk;
        display();
        return;
    }
}

int main()
{
    init();
    run();
    return 0;
}

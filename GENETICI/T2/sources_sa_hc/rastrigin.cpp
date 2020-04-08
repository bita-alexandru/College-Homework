#include <iostream>
#include <fstream>
#include <iomanip>
#include <bitset>
#include <vector>
#include <chrono>
#include <random>
#include <cmath>
#include <map>

#define FUNC(x) (x*x - 10.*cos(2.*PI*x))
#define DEBUG chrono::duration<double> timer = Clock::now() - clk; \
              cout << i << '\t' << timer.count() << '\n';

using namespace std;
using Clock = chrono::high_resolution_clock;

ofstream out;

const double MIN = -5.12;
const double MAX = 5.12;
const double EPSILON = 0.0001;

int N, O;
const int BITS = 17;
const int ITERATIONS = 10000;
const double PI = 3.1415;
const double E = 2.7182;

bitset<BITS> LOWEST, HIGHEST;
vector<bitset<BITS>> x_curr;
map<string,pair<vector<string>,vector<string>>> x_nhood;
vector<double> results;

double best_fit = 1.*INT_MAX;
double avg_fit = 0.;
double worst_fit = 1.*INT_MIN;
double stdev = 0.;

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

    out << '\n';
    out << fixed << setprecision(4);

    out << "BEST_FIT:\t" << best_fit << '\n';
    out << "AVG_FIT:\t" << avg_fit << '\n';
    out << "WORST_FIT:\t" << worst_fit << '\n';
    out << '\n';
    out << "STDEV:\t" << stdev << '\n';
    out << '\n';
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
        double number = to_real(v[i].to_string());
        fitness += FUNC(number);
    }

    return fitness;
}

void NAHC()
{
    for(int i = 0; i < 30; i++)
    {
        double best_now = 1.*INT_MAX;
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
                    string bttr_string = curr_string;
                    double new_fitness = fitness - FUNC(curr_number);

                    bool found = false;
                    vector<string> *left = &x_nhood[curr_string].first;
                    vector<string> *right = &x_nhood[curr_string].second;

                    int j = 0;
                    while(j < left->size() || j < right->size())
                    {
                        if(keep_left && j < left->size()) // left neighbours available
                        {
                            double number = to_real(left->at(j));
                            if(new_fitness + FUNC(number) < fitness)
                            {
                                found = true;
                                bttr_string = left->at(j);
                                fitness = new_fitness + FUNC(number);
                                break;
                            }
                        }

                        if(keep_right && j < right->size()) // right neighbours available
                        {
                            double number = to_real(right->at(j));
                            if(new_fitness + FUNC(number) < fitness)
                            {
                                found = true;
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

            if(fitness < best_now) best_now = fitness;
        }

        results[i] = best_now;
        avg_fit += best_now;
        if(best_now < best_fit) best_fit = best_now;
        if(best_now > worst_fit) worst_fit = best_now;
        distribution.reset();
//        DEBUG;
    }
}

void SAHC()
{
    for(int i = 0; i < 30; i++)
    {
        double best_now = 1.*INT_MAX;
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
                    string bttr_string = curr_string;
                    double new_fitness = fitness - FUNC(curr_number);

                    bool found = false;
                    vector<string> *left = &x_nhood[curr_string].first;
                    vector<string> *right = &x_nhood[curr_string].second;

                    int j = 0;
                    while(j < left->size() || j < right->size())
                    {
                        if(keep_left && j < left->size()) // left neighbours available
                        {
                            double number = to_real(left->at(j));
                            if(new_fitness + FUNC(number) < fitness)
                            {
                                found = true;
                                bttr_string = left->at(j);
                                fitness = new_fitness + FUNC(number);
                            }
                        }

                        if(keep_right && j < right->size()) // right neighbours available
                        {
                            double number = to_real(right->at(j));
                            if(new_fitness + FUNC(number) < fitness)
                            {
                                found = true;
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

            if(fitness < best_now) best_now = fitness;
        }

        results[i] = best_now;
        avg_fit += best_now;
        if(best_now < best_fit) best_fit = best_now;
        if(best_now > worst_fit) worst_fit = best_now;
        distribution.reset();
//        DEBUG;
    }
}

void SA()
{
    for(int i = 0; i < 30; i++)
    {
        double best_now = 1.*INT_MAX;

        // select x_curr[] at random
        for(int p = 0; p < N; p++)
            for(int q = 0; q < BITS; q++) x_curr[p][q] = distribution(generator);

        double temperature = 1000.;
        while(temperature > EPSILON)
        {
            for(int it = 0; it < ITERATIONS/100; it++)
            {
                for(int p = 0; p < N; p++)
                {
                    string curr_string = x_curr[p].to_string();
                    double curr_number = to_real(curr_string);
                    double curr_fitness = evaluate(x_curr);

                    vector<string> *left = &x_nhood[curr_string].first;
                    vector<string> *right = &x_nhood[curr_string].second;

                    uniform_int_distribution<int> nghbrs_distribution(-left->size(),right->size());
                    int rand_nghbr = nghbrs_distribution(generator);

                    string nghbr_string;
                    if(rand_nghbr < 0) nghbr_string = left->at(-rand_nghbr-1);
                    else if(rand_nghbr > 0) nghbr_string = right->at(rand_nghbr-1);
                    else
                    {
                        if(left->empty() && !right->empty()) nghbr_string = right->at(0);
                        else if(!left->empty() && right->empty()) nghbr_string = left->at(0);
                        else nghbr_string = distribution(generator) == 0 ? left->at(0) : right->at(0);
                    }
                    double nghbr_number = to_real(nghbr_string);
                    double nghbr_fitness = curr_fitness - FUNC(curr_number) + FUNC(nghbr_number);

                    if(nghbr_fitness < curr_fitness)
                    {
                        bitset<BITS> bttr_nghbr(nghbr_string);
                        x_curr[p] = bttr_nghbr;
                    }
                    else
                    {
                        uniform_real_distribution<double> real_distribution(0.,1.);
                        double rand = real_distribution(generator);
                        double probability = pow(E,-abs(nghbr_fitness-curr_fitness)/temperature);

                        if(rand <= probability)
                        {
                            bitset<BITS> bttr_nghbr(nghbr_string);
                            x_curr[p] = bttr_nghbr;
                        }
                    }
                }

                double fitness = evaluate(x_curr);
                if(fitness < best_now) best_now = fitness;
            }

            temperature *= 0.90;
        }

        results[i] = best_now;
        avg_fit += best_now;
        if(best_now < best_fit) best_fit = best_now;
        if(best_now > worst_fit) worst_fit = best_now;
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
    cout << "N: "; cin >> N;

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

        for(int i = 0; i < BITS; i++)
            if(neighbour[i] == '0')
            {
                neighbour[i] = '1';
                right.push_back(neighbour);
                neighbour[i] = '0';
            }
            else
            {
                neighbour[i] = '0';
                left.push_back(neighbour);
                neighbour[i] = '1';
            }

        x_nhood.insert({curr,{left,right}});

        if(curr == HIGHEST.to_string()) break;
        inc_bitstring(curr);
    }
    Clock::time_point end_timer = Clock::now();
    chrono::duration<double> dur = end_timer - start_timer;
    cout << "Neighbourhood creation finished in " << dur.count() << " seconds." << '\n' << '\n';
}

void run()
{
    cout << "NAHC[1]/SAHC[2]/SA[3]: "; cin >> O;

    clk = Clock::now();

    if(O == 1)
    {
        out.open("rastrigin_NAHC.txt", ios::out | ios::app);
        NAHC();
        avg_time = Clock::now() - clk;
        display();
        return;
    }

    if(O == 2)
    {
        out.open("rastrigin_SAHC.txt", ios::out | ios::app);
        SAHC();
        avg_time = Clock::now() - clk;
        display();
        return;
    }

    if(O == 3)
    {
        out.open("rastrigin_SA.txt", ios::out | ios::app);
        SA();
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

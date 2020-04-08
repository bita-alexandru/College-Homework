#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <random>
#include <chrono>

using namespace std;
using Clock = chrono::high_resolution_clock;

ofstream out;

const double MIN = -10.;
const double MAX = 10.;
double PRECIZIE = MAX;

int N;
const int ITERATII = 10000000;

double global_best_y = 1.*INT_MAX;
double global_avg_y = 0.;
double global_worst_y = 1.*INT_MIN;

chrono::duration<double> global_best_time = chrono::seconds(INT_MAX);
chrono::duration<double> global_avg_time = chrono::seconds(0);
chrono::duration<double> global_worst_time = chrono::seconds(INT_MIN);

vector<double> x_act, x_best;
vector<pair<double,double>> x_lim;

void afisare()
{
    out << "----------------------------------\n";
    out << "N: " << N << '\n';
    out << fixed << setprecision(6);

    out << "global_best_y: " << global_best_y << '\n';
    out << "global_worst_y: " << global_worst_y << '\n';
    out << "global_avg_y: " << global_avg_y << '\n';
    out << '\n';
    out << "global_best_time: " << global_best_time.count() << '\n';
    out << "global_worst_time: " << global_worst_time.count() << '\n';
    out << "global_avg_time: " << global_avg_time.count() << '\n';
}

void det(int k = 0)
{
    if(k == N)
    {
        if(global_avg_y < global_best_y)
        {
            global_best_y = global_avg_y;

            x_best = x_act;
        }

        return;
    }

    for(double i = x_lim[k].first; i <= x_lim[k].second; i += PRECIZIE)
    {
        x_act[k] = i;
        global_avg_y += ((k+1)*(x_act[k]*x_act[k]));

        det(k+1);

        global_avg_y -= ((k+1)*(x_act[k]*x_act[k]));
    }
}

void nedet()
{
    auto t1 = Clock::now();

    for(int i = 1; i <= 30; i++)
    {
        double local_best_y = 1.*INT_MAX;

        default_random_engine e(Clock::now().time_since_epoch().count());
        uniform_real_distribution<double> d(MIN,MAX);

        vector<double> x(N);

        auto time_start = Clock::now();

        for(int it = 1; it <= ITERATII; it++)
        {
            double y = 0.;

            for(int s = 0; s < x.size(); s++)
            {
                x[s] = d(e);
                y += ((s+1)*(x[s]*x[s]));
            }

            if(y < local_best_y) local_best_y = y;
        }

        chrono::duration<double> local_time = Clock::now() - time_start;
        global_avg_time += local_time;
        if(local_time > global_worst_time) global_worst_time = local_time;
        if(local_time < global_best_time) global_best_time = local_time;

        global_avg_y += local_best_y;
        if(local_best_y > global_worst_y) global_worst_y = local_best_y;
        if(local_best_y < global_best_y) global_best_y = local_best_y;

        auto t2 = Clock::now();
        chrono::duration<double> dur = t2 - t1;
        cout << "i: " << i << '\t' << dur.count() << '\n';
    }

    global_avg_y /= 30.;
    global_avg_time /= 30;
}

int main()
{
    cout << "N: "; cin >> N;

    int o;
    cout << "DET[0]/NEDET[1]: "; cin >> o;

    switch(o)
    {
    case 0:
        {
            out.open("sumsquares_det.txt", ios::out | ios::app);
            auto time_start = Clock::now();
            x_act.resize(N); x_best.resize(N); x_lim.resize(N);

            for(int it = 1; it <= 16; it++)
            {
                for(int i = 0; i < N; i++) x_lim[i] = {max(MIN,x_best[i]-PRECIZIE), min(MAX,x_best[i]+PRECIZIE)};
                det();
                PRECIZIE /= 2.;

                auto t = Clock::now();
                chrono::duration<double> dur = t - time_start;
                cout << "i: " << it << '\t' << dur.count() << '\n';
            }
            global_best_time = global_avg_time = global_worst_time = Clock::now() - time_start;
            global_worst_y = global_avg_y = global_best_y;
            afisare();
            break;
        }
    case 1:
        {
            out.open("sumsquares_nedet.txt", ios::out | ios::app);
            nedet();
            afisare();
            break;
        }
    default: break;
    }

    return 0;
}

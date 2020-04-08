#include <bits/stdc++.h>

using namespace std;

int main()
{
    ifstream in("data-raw.in");
    ofstream out("data-fmt.out");

    string s;
    in >> s; out << s << '\n';

    int N;
    in >> N; out << N << '\n';

    vector<vector<int>> v(N,vector<int>(N));
    vector<pair<int,int>> d;

    for(int i = 0; i < N; i++)
    {
        int k;
        in >> k;

        float x, y;
        in >> x >> y;

        d.push_back({x,y});
    }

    for(int m = 0; m < N; m++)
    {
        for(int n = 0; n <= m; n++)
        {
            int i;
            in >> i;
            v[n][m] = v[m][n] = round(sqrt((d[n].first-d[m].first)*(d[n].first-d[m].first) + (d[n].second-d[m].second)*(d[n].second-d[m].second)));
        }
    }

    for(int m = 0; m < N; m++)
    {
        for(int n = 0; n < N; n++) out << v[m][n] << ' ';
        out << '\n';
    }

    return 0;
}

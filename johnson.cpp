#include <fstream>
#include <queue>
#include <vector>
#include <algorithm>
#include <cstring>
#include <bitset>
#include <stack>
#include <unordered_map>
#include <map>
#include <cmath>
#include <chrono>
#include <set>
#include <iomanip>
#include <list>
#include <sstream>
#include <functional>
#include <numeric>
#include <string>
#include <unordered_set>
#include <random>
#include <time.h>
#include <Windows.h>

using namespace std;
using namespace chrono;
#define Inf 0x3f3f3f3f
#define MAX 2000000000000000000LL
#define MOD 1000000007
#define MODC 984162946217979097
#define lsb(i) (i & -i)
#define pii pair<int,int>
#define pll pair<ll,ll>
#define tup tuple<int,int,int>
#define ll long long
#define fastio ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

///__builtin_popcount(x)

ifstream cin("input2.in");
ofstream cout("date.out");

vector<vector<pair<int,int>>> G;
int x,y,z;
vector<int> InQueue;
vector<int> Vizita;
vector<int> d;
vector<vector<int>> distances;
int n,m,nodes;

int bellman_ford(){

    InQueue[0] = 0;
    queue<int> q;
    q.push(0);
    d[0] = 0;
    while(!q.empty()){

        int x = q.front();
        q.pop();

        InQueue[x] = 0;

        for(auto i : G[x]){
            if(d[i.first] > d[x] + i.second){
                d[i.first] = d[x] + i.second;
                if(InQueue[i.first] == 0){
                    InQueue[i.first] = 1;
                    q.push(i.first);
                    if(++Vizita[i.first] > 4 * n)
                        return 1;
                    
                }
            }
        }
    }
    return 0;
}

void dijkstra(int nod){

    priority_queue<pii,vector<pii>,greater<pii> > q;
    
    distances[nod][nod] = 0;

    q.push({0,nod});

    while(!q.empty()){

        int x = q.top().second;
        q.pop();
        for(auto i : G[x]){
            if(distances[nod][i.first] > distances[nod][x] + i.second){
                distances[nod][i.first] = distances[nod][x] + i.second;
                q.push({distances[nod][i.first],i.first});
            }
        }
    }
}
void johnson(){


    /*
    
    Algoritmul calculeaza "All pairs shorthest paths" adica toate perechile de forma
    i - j - cost => intr-un graf ponderat (suporta costuri negative)

    Algoritmul da "reweight" la graf folosind bellman_ford iar apoi ruleaza dijkstra pe costuri pozitive
    La final reactualizeaza costul final (scade reweigth-ul pentru a afisa corect costul)
    
    */
    for(int i = 1 ; i <= n ; ++i)
        G[0].push_back({i,0});

    if(!bellman_ford()){
        for(int i = 1 ; i <= n ; ++i)
            for(auto &j : G[i])
                j.second = j.second + d[i] - d[j.first];
    
    for(int i = 1 ; i <= n ; ++i)
        dijkstra(i);

    for(int i = 1 ; i <= n ; ++i)
        for(int j = i + 1 ; j <= n ; ++j)
            if(distances[i][j] != Inf)
                cout << i << ' ' << j << ' ' << distances[i][j] - d[i] + d[j] << '\n';

    }
    else
        cout << "Ciclu negativ\n";
    

}

static inline int64_t GetTicks() {

    LARGE_INTEGER ticks;
    if (!QueryPerformanceCounter(&ticks)){
        // Handle error (you can throw an exception or handle it differently)
        // For example, using WinRT's throw_last_error():
        // winrt::throw_last_error();
    }
    return ticks.QuadPart;
}

int main(){

    fastio;

    int64_t start = GetTicks();

    cin >> n;

    G.resize(n + 1);
    InQueue.resize(n + 1,0);
    Vizita.resize(n + 1,0);
    d.resize(n + 1,Inf);
    distances.resize(n + 1,vector<int>(n + 1,Inf));

    while(cin >> x >> y >> z){

        G[x].push_back({y,z}); 

    }

    johnson();

    int64_t end = GetTicks();

    cout << "\n\n";

    cout << "CPU Clocks start : " << start << '\n';
    cout << "CPU Clocks final : " << end << '\n';
    cout << "Difference : " << end - start << '\n';

    double elapsedTimeSeconds = (double)(end - start);

    cout << "Elapsed time: " << fixed << setprecision(3) << elapsedTimeSeconds / 1e4 << " miliseconds";




    return 0;
}

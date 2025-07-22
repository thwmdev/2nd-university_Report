#include <iostream>
using namespace std;
const int maxn = 10005;
int g[maxn][maxn];    
int degree[maxn];      
int matchl[maxn], matchr[maxn];
int dist[maxn];
int queue_[maxn];
bool bfs(int n) {
    int front = 0, back = 0;
    for (int u = 1; u <= n; ++u) {
        if (matchl[u] == 0) {  
            dist[u] = 0;
            queue_[back++] = u;
        } else {
            dist[u] = -1;
        }
    }
    bool found = false;
    while (front < back) {
        int u = queue_[front++];
        for (int i = 0; i < degree[u]; ++i) {
            int v = g[u][i];
            if (matchr[v] != 0 && dist[matchr[v]] == -1) {
                dist[matchr[v]] = dist[u] + 1;
                queue_[back++] = matchr[v];
            }
            if (matchr[v] == 0) found = true; 
        }
    }
    return found;
}
bool dfs(int u) {
    for (int i = 0; i < degree[u]; ++i) {
        int v = g[u][i];
        if (matchr[v] == 0 || (dist[matchr[v]] == dist[u] + 1 && dfs(matchr[v]))) {
            matchl[u] = v;
            matchr[v] = u;
            return true;
        }
    }
    return false;
}
int hopcroft_karp(int n, int m) {
    for (int i = 1; i <= n; ++i) matchl[i] = 0;
    for (int i = 1; i <= m; ++i) matchr[i] = 0;
    int result = 0;
    while (bfs(n)) {
        for (int u = 1; u <= n; ++u) {
            if (matchl[u] == 0 && dfs(u)) {
                result++;
            }
        }
    }
    return result;
}
int main() {
    int n, m, e;
    cout << "Nhap so dinh tap trai (x) va tap phai (y): ";
    cin >> n >> m;
    cout << "Nhap so canh: ";
    cin >> e;
    for (int i = 0; i < e; ++i) {
        int u, v;
        cin >> u >> v;
        g[u][degree[u]++] = v;
    }
    int res = hopcroft_karp(n, m);
    cout << "So luong cap ghep cuc dai la: " << res << endl;
    cout << "Cac cap ghep:" << endl;
    for (int u = 1; u <= n; ++u) {
        if (matchl[u] != 0) {
            cout << u << " - " << matchl[u] << endl;
        }
    }
    return 0;
}
/*1 1
1 2
2 2
2 3
2 6
3 3
3 4
3 5
3 7
4 4
4 5
5 6
5 7*/

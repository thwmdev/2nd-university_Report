#include <iostream>
using namespace std;
const int MAXN = 1000;
int ke[MAXN][MAXN];
int ghep[MAXN], goc[MAXN], cha[MAXN];
bool tronghangdoi[MAXN], trongblossom[MAXN];
int hangdoi[MAXN], dau = 0, cuoi = 0;
int sodinh, socanh;
void dayvaohangdoi(int x) {
    hangdoi[cuoi++] = x;
    tronghangdoi[x] = true;
}
int layrahangdoi() {
    return hangdoi[dau++];
}
int timlca(int a, int b) {
    bool datham[MAXN] = {false};
    while (true) {
        a = goc[a];
        datham[a] = true;
        if (ghep[a] == -1) break;
        a = cha[ghep[a]];
    }
    while (true) {
        b = goc[b];
        if (datham[b]) return b;
        if (ghep[b] == -1) break;
        b = cha[ghep[b]];
    }
    return -1;
}
void danhdaublossom(int u, int v, int lca) {
    while (goc[u] != lca) {
        trongblossom[goc[u]] = trongblossom[goc[ghep[u]]] = true;
        cha[u] = v;
        v = ghep[u];
        u = cha[v];
    }
}
void rutgonblossom(int u, int v) {
    int lca = timlca(u, v);
    for (int i = 1; i <= sodinh; ++i) trongblossom[i] = false;
    danhdaublossom(u, v, lca);
    danhdaublossom(v, u, lca);
    for (int i = 1; i <= sodinh; ++i) {
        if (trongblossom[goc[i]]) {
            goc[i] = lca;
            if (!tronghangdoi[i]) dayvaohangdoi(i);
        }
    }
}
bool bfs(int gocr) {
    for (int i = 1; i <= sodinh; ++i) {
        cha[i] = -1;
        tronghangdoi[i] = false;
        goc[i] = i;
    }
    dau = cuoi = 0;
    dayvaohangdoi(gocr);
    while (dau < cuoi) {
        int u = layrahangdoi();
        for (int v = 1; v <= sodinh; ++v) {
            if (ke[u][v] == 0 || goc[u] == goc[v] || ghep[u] == v) continue;
            if (v == gocr || (ghep[v] != -1 && cha[ghep[v]] != -1)) {
                rutgonblossom(u, v);
            } else if (cha[v] == -1) {
                cha[v] = u;
                if (ghep[v] == -1) {
                    while (v != -1) {
                        int pv = cha[v], mv = ghep[pv];
                        ghep[v] = pv;
                        ghep[pv] = v;
                        v = mv;
                    }
                    return true;
                } else {
                    cha[ghep[v]] = v;
                    dayvaohangdoi(ghep[v]);
                }
            }
        }
    }
    return false;
}
int edmonds() {
    for (int i = 1; i <= sodinh; ++i) ghep[i] = -1;
    int dem = 0;
    for (int i = 1; i <= sodinh; ++i) {
        if (ghep[i] == -1) {
            if (bfs(i)) dem++;
        }
    }
    return dem;
}
int main() {
    cout << "Nhap so dinh va so canh: ";
    cin >> sodinh >> socanh;
    for (int i = 0; i < socanh; ++i) {
        int u, v;
        cin >> u >> v;
        ke[u][v] = ke[v][u] = 1;
    }
    int ketqua = edmonds();
    cout << "So cap ghep cuc dai: " << ketqua << endl;
    for (int i = 1; i <= sodinh; ++i) {
        if (ghep[i] != -1 && i < ghep[i])
            cout << i << " - " << ghep[i] << endl;
    }
    return 0;
}
/*
10 11
1 2
1 6
2 4
2 8
3 4
3 6
5 6
5 9
5 10
7 8
7 9
*/

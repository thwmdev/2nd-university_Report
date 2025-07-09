#include <iostream>
#include <cstring>
using namespace std;
const int MAX = 100;
bool a[MAX+1][MAX+1]; 
int match[MAX+1], Queue[MAX+1], b[MAX+1], T[MAX+1];
bool InQueue[MAX+1];
int n;
int first, last, start, finish;
void Enter() {
    int m, u, v;
    cin >> n >> m;
    memset(a, false, sizeof(a));
    for (int i = 0; i < m; ++i) {
        cin >> u >> v;
        a[u][v] = a[v][u] = true;
    }
}
void Init() {
    memset(match, 0, sizeof(match));
}
void InitBFS() {
    first = 1; last = 1;
    Queue[1] = start;
    memset(InQueue, false, sizeof(InQueue));
    InQueue[start] = true;
    memset(T, 0, sizeof(T));
    for (int i = 1; i <= n; ++i) b[i] = i;
    finish = 0;
}
void Push(int v) {
    Queue[++last] = v;
    InQueue[v] = true;
}
int Pop() {
    return Queue[first++];
}
int FindCommonAncestor(int p, int q) {
    bool InPath[MAX+1] = {false};
    while (true) {
        p = b[p];
        InPath[p] = true;
        if (p == start) break;
        p = T[match[p]];
    }
    while (true) {
        q = b[q];
        if (InPath[q]) return q;
        q = T[match[q]];
    }
    return -1;
}

void ResetTrace(int x, int NewBase, bool Mark[]) {
    int v = x;
    while (b[v] != NewBase) {
        int u = match[v];
        Mark[b[v]] = true;
        Mark[b[u]] = true;
        v = T[u];
        if (b[v] != NewBase)
            T[v] = u;
    }
}
void BlossomShrink(int p, int q) {
    bool Mark[MAX+1];
    memset(Mark, false, sizeof(Mark));
    int NewBase = FindCommonAncestor(p, q);
    ResetTrace(p, NewBase, Mark);
    ResetTrace(q, NewBase, Mark);
    if (b[p] != NewBase) T[p] = q;
    if (b[q] != NewBase) T[q] = p;

    for (int i = 1; i <= n; ++i)
        if (Mark[b[i]])
            b[i] = NewBase;

    for (int i = 1; i <= n; ++i)
        if (!InQueue[i] && b[i] == NewBase)
            Push(i);
}
void FindAugmentingPath() {
    InitBFS();
    while (first <= last) {
        int u = Pop();
        for (int v = 1; v <= n; ++v) {
            if (T[v] == 0 && a[u][v] && b[u] != b[v]) {
                if (match[v] == 0) {
                    T[v] = u;
                    finish = v;
                    return;
                }
                if (v == start || T[match[v]] != 0)
                    BlossomShrink(u, v);
                else {
                    T[v] = u;
                    Push(match[v]);
                }
            }
        }
    }
}
void Enlarge() {
    int v = finish;
    while (v != 0) {
        int u = T[v];
        int w = match[u];
        match[v] = u;
        match[u] = v;
        v = w;
    }
}
void Solve() {
    for (int u = 1; u <= n; ++u) {
        if (match[u] == 0) {
            start = u;
            FindAugmentingPath();
            if (finish != 0)
                Enlarge();
}
    }
}
void Result() {
    int count = 0;
    for (int u = 1; u <= n; ++u) {
        if (match[u] > u) {
            ++count;
            cout << count << ") " << u << " " << match[u] << "\n";
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    Enter();
    Init();
    Solve();
    Result();
    return 0;
}

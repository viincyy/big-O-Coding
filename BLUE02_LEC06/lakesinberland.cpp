#include <bits/stdc++.h>
#define MAX 51
using namespace std;

const int dr[] = {0, 0, 1, -1};
const int dc[] = {1, -1, 0, 0};
int n, m, k;
bool visited[MAX][MAX];
string table[MAX];

struct Cell {
    int r, c;
};

vector<vector<Cell>> lakes;

bool sortBySize(const vector<Cell> &a, const vector<Cell> &b) {
    return a.size() < b.size();
}

bool isValid(int r, int c) {
    return r >= 0 && c >= 0 && r < n && c < m;
}

bool onBorder(int r, int c) {
    return r == 0 || c == 0 || r == n - 1 || c == m - 1;
}

void DFS(Cell scr) {
    stack<Cell> s;
    visited[scr.r][scr.c] = true;
    s.push(scr);
    
    bool isOcean = false;
    vector<Cell> temp;

    while (!s.empty()) {
        Cell u = s.top();
        temp.push_back(u);
        s.pop();

        if (onBorder(u.r, u.c)) {
            isOcean = true;
        }

        for (int i = 0; i < 4; i++) {
            int r = u.r + dr[i];
            int c = u.c + dc[i];

            if (isValid(r, c) && table[r][c] == '.' && !visited[r][c]) {
                visited[r][c] = true;
                s.push((Cell) {r, c});
            }
        }
    }

    if (!isOcean) {
        lakes.push_back(temp);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m >> k;

    for (int i = 0; i < n; i++) {
        cin >> table[i];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!visited[i][j] && table[i][j] == '.') {
                DFS((Cell) {i, j});
            }
        }
    }

    sort(lakes.begin(), lakes.end(), sortBySize);

    int sum_cell = 0;

    for (int i = 0; i < lakes.size() - k; i++) {
        sum_cell += lakes[i].size();
        
        for (int j = 0; j < lakes[i].size(); j++) {
            Cell u = lakes[i][j];
            table[u.r][u.c] = '*';
        }
    }

    cout << sum_cell << endl;

    for (int i = 0; i < n; i++) {
        cout << table[i] << endl;
    }

    return 0;
}
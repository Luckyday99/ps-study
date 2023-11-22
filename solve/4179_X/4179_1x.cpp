#include <bits/stdc++.h>
using namespace std;

/*
4179 불!
https://www.acmicpc.net/problem/4179

bfs

불, 사람 위치에서 bfs 돌려서 최단거리 구하고 비교
=> 그 위치의 최단거리가 불에서 출발시 x -> 불 출발은 음수로 해서 비교했음
*/

int r, c, cnt[1004][1004], visited[1004][1004];
char arr[1004][1004];
const int dy[4] = { 0, 1, 0, -1 };
const int dx[4] = { 1, 0, -1, 0 };
pair<int, int> human;
vector<pair<int, int>> fire;

bool in(int y, int x)
{
    return 0 <= y && y < r && 0 <= x && x < c;
}

void bfs(int y, int x, char inp)
{
    if (inp == 'F') cnt[y][x] = -1;
    else if (inp == 'J') cnt[y][x] = 1;
    queue<pair<int, int>> q;
    q.push(make_pair(y, x));
    while (q.size())
    {
        pair<int, int> here = q.front();
        q.pop();
        for (int i = 0; i < 4; i++)
        {
            int ny = here.first + dy[i];
            int nx = here.second + dx[i];
            if (!in(ny, nx)) continue;
            if (arr[ny][nx] == '#' || visited[ny][nx] != 0) continue;
            if (inp == 'F')
            {
                if (cnt[ny][nx] != 0 && cnt[ny][nx] >= cnt[here.first][here.second] - 1) continue;
                cnt[ny][nx] = cnt[here.first][here.second] - 1;
            }
            else if (inp == 'J')
            {
                if (0 <= cnt[ny][nx] + cnt[here.first][here.second] + 1) continue;
                cnt[ny][nx] = cnt[here.first][here.second] + 1;
            }
            visited[ny][nx] = true;
            q.push(make_pair(ny, nx));
        }
    }
}

int main()
{
    cin >> r >> c;
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            cin >> arr[i][j];
            if (arr[i][j] == 'J') human = make_pair(i, j);
            else if (arr[i][j] == 'F') fire.push_back(make_pair(i, j));
        }
    }
    for (pair<int, int> yx : fire)
    {
        bfs(yx.first, yx.second, 'F');
        memset(visited, 0, sizeof(visited));
    }
    bfs(human.first, human.second, 'J');
    int ret = max({
        cnt[0][1], cnt[0][c-2], cnt[1][0], cnt[1][c-1],
        cnt[r-2][0], cnt[r-2][c-1], cnt[r-1][1], cnt[r-1][c-2]
    });

    if (ret <= 0) cout << "IMPOSSIBLE \n";
    else cout << ret << "\n";

    return 0;
}
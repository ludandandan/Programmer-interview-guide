#include <cstdio>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <unordered_map>
#include <sstream>
#include <queue>
#include <cstring>
using namespace std;
 
 
struct Node {
    int x;//横坐标
    int y;//纵坐标
    int k;//key状态
    int step;//从起始位置到当前位置的步数
    Node(int x, int y, int k, int step): x(x), y(y), k(k), step(step){}
};
 
int main()
{
    int M, N;
    cin >> M >> N;
    vector<vector<char>> matrix(M, vector<char>(N));
    //先找到2的位置和3出口的位置
    int starti = 0;
    int startj = 0;
    int endi = 0;
    int endj = 0;
    for (int i = 0; i < M; i++)
    {
        string s;
        cin >> s;
        for (int j = 0; j < N; j++)
        {
            if (s[j] == '2')
            {
                starti = i;
                startj = j;
            }
            else if (s[j] == '3')
            {
                endi = i;
                endj = j;
            }
            matrix[i][j] = s[j];
        }
    }
 
    //visited[x][y][key]表示横坐标为x，纵坐标为y，钥匙状态为Key的点是否被访问过
    //钥匙的状态有10种，用二进制表示是1024,比如用第二吧钥匙和第4把钥匙就是0101000000=320
    vector<vector<vector<int>>> visited(M, vector<vector<int>>(N, vector<int>(1200)));
    //visited初始化为0，被访问过的点被设置为1，比如横坐标3，纵坐标7，
    //钥匙状态为320(有第二把钥匙和第4把钥匙)被访问过，那么visited[3][7][320]=1
    //开始位置visited[starti][startj][0]设置为1
    for (int i = 0; i < M; i++)for (int j = 0; j < N; j++)for (int k = 0; k < 1200; k++) visited[i][j][k] = 0;
    visited[starti][startj][0] = 1;
 
    queue<Node> q;
    q.push(Node(starti, startj, 0, 0));
    vector<int> dx{ -1, 1, 0, 0};
    vector<int> dy{0, 0, -1, 1};
 
    while (!q.empty())
    {
        Node cur = q.front();
        q.pop();
        //若是到出口了就输出并跳出
        if (cur.x == endi && cur.y == endj)
        {
            cout << cur.step << endl;
            break;
        }
        for (int i = 0; i < 4; i++)
        {
            int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];
            if (nx < 0 || nx >= M || ny < 0 || ny >= N || matrix[nx][ny]=='0') continue;
            int key = cur.k;
            if (matrix[nx][ny] >= 'a' && matrix[nx][ny] <= 'z') key = key | (1 << (matrix[nx][ny] - 'a'));
            if (matrix[nx][ny] >= 'A' && matrix[nx][ny] <= 'Z' && (key & (1 << (matrix[nx][ny] - 'A'))) == 0) continue;
            if (!visited[nx][ny][key])
            {
                q.push(Node(nx, ny, key, cur.step + 1));
                visited[nx][ny][key] = 1;
            }
        }
    }
    return 0;
}
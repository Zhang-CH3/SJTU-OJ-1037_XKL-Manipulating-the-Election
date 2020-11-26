#include <iostream>
#include <cmath>
#include <queue>
#include <cstdio>
using namespace std;
const int MAXN = 104;
int m, n, st[MAXN][MAXN], cost[MAXN][MAXN];
const int dx[]={1, -1, 0, 0};
const int dy[]={0, 0, 1, -1};

struct Node{
	int x, y, cost;
}node, top;

bool swing(int x, int y){
	if(st[x][y]==2||st[x][y]==3||st[x][y]==4)return true;
	else return false;
}

void bfs(int x, int y){
	int t, st0;
	cost[x][y] = 0;
	queue<Node> q;
	node.x = x;
	node.y = y;
	node.cost = 0;
	q.push(node);
	while(!q.empty()){
		top = q.front();
		q.pop();
		for(int i=0;i<4;i++){
//			0=4=red; 1=3=blue; 2=swing;
			int nx = top.x + dx[i];
			int ny = top.y + dy[i];
			st0 = st[nx][ny];
			if(nx<1||nx>m||ny<1||ny>m) continue;
			if(swing(top.x, top.y) && swing(nx, ny))continue;
			t = cost[top.x][top.y];
			if(st[top.x][top.y] == 1 && swing(nx, ny)){
				st[nx][ny] = 3;
				t += 2;
			}//When this cell is 1 and the lower cell is a swing one, change the lower cell to 3/ retain the swing state attribute 
			if(st[top.x][top.y] == 0 && swing(nx, ny)){
				st[nx][ny] = 4; 
				t += 2;
			}//When this cell is 1 and the lower cell is a swing one, change the lower cell to 3/ retain the swing state attribute 
			if(st[top.x][top.y] == 1 && (st[nx][ny] == 0 || st[nx][ny]==4)) t += 1;
			if(st[top.x][top.y] == 0 && (st[nx][ny] == 1 || st[nx][ny]==3)) t += 1;
			if(st[top.x][top.y] == 3 && st[nx][ny] == 0) t += 1;
			if(st[top.x][top.y] == 4 && st[nx][ny] == 1) t += 1;
			if(t >= cost[nx][ny]) st[nx][ny] = st0;
			if(t < cost[nx][ny]){
				cost[nx][ny] = t;
				node.x = nx;
				node.y = ny;
				node.cost = t;
				q.push(node);
			}
		}
	}
}

int main(){
	cin >> m >> n;
	int x, y, c;
	for(int i=1;i<=m;i++){
		for(int j=1;j<=m;j++){
			st[i][j] = 2;
			cost[i][j] = 2147483646;
		}
	}
	for(int i=0;i<n;i++){
		scanf("%d%d%d", &x, &y, &c);
		st[x][y] = c;
	}
	bfs(1, 1);
	if(cost[m][m] == 2147483646) cost[m][m] = -1;
	cout << cost[m][m] << endl;
}

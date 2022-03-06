#include"bits/stdc++.h"
#include<random>
using namespace std;
typedef long long int llint;
typedef pair<int, int> pint;
typedef pair<llint, llint> pllint;
typedef vector<int> vint;
typedef vector<pint> vpint;
typedef vector<vector<int>> vvint;
#define rep(i,n) for(int i=0;i<n;i++)
#define drep(i,n) for(int i=n-1;0<=i;i--)
#define all(x) x.begin(),x.end()

/*
0 6  13 20 27
1 7  14 21 28 33
2 8  15 22 29 34
3 9  16 23 30 35
4 10 17 24 31 36
5 11 18 25 32 37
  12 19 26
*/

pint chairs[38] = {};
vvint friends(38);
int p[38];
int NowScore;
int PairNumber;
int TheoMax;
//乱数の種を蒔く
random_device seed_gun;
mt19937 get_rand_mt(seed_gun());

//Pair_Numberとchairsを初期化する
void Set() {
	PairNumber = 0;
	chairs[0] = { 0,0 };
	chairs[6] = { 0,1 };
	chairs[13] = { 0,2 };
	chairs[20] = { 0,3 };
	chairs[27] = { 0,4 };
	chairs[33] = { 1,5 };
	rep(i, 38) {
		p[i] = i;
		if (i != 0 && chairs[i] == make_pair(0, 0)) {
			chairs[i] = { chairs[i - 1].first + 1,chairs[i - 1].second };
		}
	}
	return;
}

//近くを望まれている各ペアについて
//一番近い場合は10点、
//その他は{3-マンハッタン距離}点として総和を出す
int Score(int (&p)[38]) {
	int S = 0;
	rep(i, 38) {
		for (auto j : friends[i]) {
			int dis = abs(chairs[p[i]].first - chairs[p[j]].first) + abs(chairs[p[i]].second - chairs[p[j]].second);
			//一番近い場合をすごく強く評価する
			if (dis == 1)S += 10;
			else S += 3 - dis;
		}
	}
	return S;
}

void Generator() {
	rep(i, 38) {
		int k = get_rand_mt() % 5;
		vint tmp;
		sample(p, p + 38, back_inserter(tmp), k, get_rand_mt);
		for (auto j : tmp) {
			if (j != i) {
				PairNumber++; friends[i].push_back(j);
			}
		}
	}
	return;
}

int main() {
	Set();
	/*cout << "生徒の友達情報を入力" << endl;
	cout << "0で終了" << endl;
	while (1) {
		string s;
		cin >> s;
		if (s == "0")break;
		int nowend = 0;
		int num = 0;
		int you = -1;
		rep(i, s.size()) {
			if (s[i] == '_') {
				you = num - 1;
				num = 0;
			}
			else if (s[i] == ',') {
				friends[you].push_back(num - 1);
				PairNumber++;
				num = 0;
			}
			else {
				num *= 10;
				num += s[i] - '0';
			}
		}
	}*/

	double Ave = 0;
	int q[38];
	int cnt = 0;
	int S;
	Generator();

	NowScore = Score(p);

	TheoMax = PairNumber * 10;

	//ランダムにたくさん回すぜ！！！
	clock_t Start = clock();
	cnt = 0;
	while (((double)clock() - Start) / CLOCKS_PER_SEC < 1000) {
		cnt++;
		rep(i, 38)q[i] = p[i];
		rep(i, (get_rand_mt() % 10)) {
			swap(q[get_rand_mt() % 38], q[get_rand_mt() % 38]);
		}
		S = Score(q);
		if (S > NowScore) {
			rep(i, 38)p[i] = q[i];
			NowScore = S;
		}
		if (NowScore == TheoMax)break;
	}
	cout << cnt << "回調べました" << endl;
	//マンハッタン距離が2以下の場合に望みがかなったとみなして、
	//望みがかなったペアの割合を出力
	int GoodPair = 0;
	rep(i, 38) {
		for (auto j : friends[i]) {
			if (abs(chairs[p[i]].first - chairs[p[j]].first) + abs(chairs[p[i]].second - chairs[p[j]].second) <= 2) {
				GoodPair++;
			}
		}
	}
	//Ave += (double)GoodPair * 100.0 / (double)PairNumber;

	cout << GoodPair * 100 / PairNumber << "%" << endl;
	rep(i, 38)cout << p[i] << " "; cout << endl;

	vvint table(7, vint(6, -1));
	rep(i, 38)table[chairs[p[i]].first][chairs[p[i]].second] = i;
	rep(i, 7) {
		rep(j, 6)cout << table[i][j] << " "; cout << endl;
	}
	//cout << Ave << "%" << endl;
	return 0;
}
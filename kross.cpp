#include <bits/stdc++.h>

using namespace std;

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

const int INF = 1e9;

struct Cord {
	int x, y;
	Cord(int x1 = 0, int y1 = 0): x(x1), y(y1) {};

	bool operator <(Cord a) {
		return x < a.x || (x == a.x && y < a.y);
	}

	Cord operator -(Cord a) {
		return Cord(x - a.x, y - a.y);
	}

	Cord operator +(Cord a) {
                return Cord(x + a.x, y + a.y);
        }

	int operator %(Cord a) {
		return a.x * x + a.y * y;
	}

	int operator *(Cord a) {
		return x * a.y - y * a.x;
	}
};

bool Inter(Cord a, Cord b, Cord a1, Cord b1) {
	return ((b - a) * (b1 - a)) * ((b - a) * (a1 - a)) <= 0 && ((b1 - a1) * (b - a1)) * ((b1 - a1) * (a - a1)) <= 0;
}

//for input some words
bool input(int &n, vector<string> &words, int &k) {
	cin >> n;
	words.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> words[i];
	}
	cin >> k;
	return true;
}

int GetRndBefore(int n) {
	return abs((int) rnd()) % n;
}

int GetWord(const vector<vector<int>> &ForChar, const vector<bool>used, const vector<string> &words) {
	while (true) {
		int now = GetRndBefore(words.size());
		if (used[now]) continue;
		return now;
	}
}

bool CheckIfInter(Cord beg, Cord ed, vector<pair<Cord, Cord>> Cords, int need) {
	int cnt = 0;
	for (auto [begn, beged] : Cords) {
		if (need == cnt) {
			cnt++;
			continue;
		}
		if (Inter(beg + Cord(1, 0), ed + Cord(1, 0), begn, beged) || Inter(beg - Cord(1, 0), ed - Cord(1, 0), begn, beged) || Inter(beg + Cord(0, 1), ed + Cord(0, 1), begn, beged) || Inter(beg - Cord(0, 1), ed - Cord(0, 1), begn, beged)) {
			return false;
		}
		cnt++;
	}
	return true;
}

int main() {
	int n;
	vector<string> words;
	int k;
	bool OkInput = input(n, words, k);
	if (!OkInput) {
		cout << -1 << endl;
		return -1;
	}
	
	vector<vector<int>> ForChar(26);//array of words for each letter, which contain that letter
	vector<bool> used(n, false);//usedd words
	int start = GetRndBefore(n);//first word
	vector<pair<Cord, Cord>> Cords;//Cords of words
	vector<int> KrossWords;//indexes taken words
	vector<vector<bool>> UsedForKross;
	
	KrossWords.push_back(start);
	used[start] = true;
	Cords.push_back({Cord(0, 0), Cord(words[start].size() - 1, 0)});
	UsedForKross.push_back(vector<bool>(words[start].size()));

	for (int i = 0; i < n; i++) {
		for (char j : words[i]) {
			ForChar[j - 'a'].push_back(i);
		}
	}
	
	for (int _ = 1; _ < k; _++) {
		bool ok = true;
		int cnt = 0;
		while (ok) {
			if (cnt > 1e6) break;
			int id = GetRndBefore(KrossWords.size());

			bool hor = false;
			if (Cords[id].first.y == Cords[id].second.y) {
				hor = true;
			}
			
			for (int i = 0; i < words[KrossWords[id]].size(); i++) {
				if (UsedForKross[id][i] || (i > 0 && UsedForKross[id][i - 1]) || (i < n - 1 && UsedForKross[id][i + 1])) continue;
			       	bool Norm = false;


				int now = GetWord(ForChar, used, words);
				for (int j = 0; j < words[now].size(); j++) {
					if (words[now][j] != words[KrossWords[id]][i]) continue;
					
					Cord Bgn, Edn;
					if (hor) {
						Bgn = Cord(Cords[id].first.x + i, Cords[id].first.y + j);
						Edn = Cord(Cords[id].first.x + i, Cords[id].first.y - (words[now].size() - j - 1));
					} else {
						Bgn = Cord(Cords[id].first.x - j, Cords[id].first.y - i);
                                                Edn = Cord(Cords[id].first.x + (words[now].size() - j - 1), Cords[id].first.y - i);
					}

					if (!CheckIfInter(Bgn, Edn, Cords, id)) continue;
					ok = false;

					Cords.push_back({Bgn, Edn});
					used[now] = true;
					KrossWords.push_back(now);
					UsedForKross.push_back(vector<bool> (words[now].size(), false));
					UsedForKross[UsedForKross.size() - 1][j] = true;
					UsedForKross[id][i] = true;
					break;
				}
				if (!ok) break;
			}
			cnt++;
		}
	}
	
	cout << Cords.size() << "\n";
	for (int i = 0; i < Cords.size(); i++) {
		cout << words[KrossWords[i]] << " " << Cords[i].first.x << " " << Cords[i].first.y << " " << Cords[i].second.x << " " << Cords[i].second.y << "\n";
	}

	return 0;
}

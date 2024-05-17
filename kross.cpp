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
bool input(int &n, vector<wstring> &words, int &k) {
	std::locale l(getenv("LANG"));
    std::locale::global(l);
	wcin >> n;
	words.resize(n);
	for (int i = 0; i < n; i++) {
		wcin >> words[i];
	}
	wcin >> k;
	return true;
}

int GetRndBefore(int n) {
	return abs((int) rnd()) % n;
}

int GetWord(const vector<bool>used, const vector<wstring> &words) {
	std::locale l(getenv("LANG"));
    std::locale::global(l);
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

void WordKross(vector<wstring> &words, vector<pair<Cord, Cord>> &Cords, vector<int> &KrossWords) {
	
	std::locale l(getenv("LANG"));
    std::locale::global(l);
	int n;
	int k;

	bool OkInput = input(n, words, k);
	if (!OkInput) {
		cout << -1 << endl;
		return;
	}
	
	vector<bool> used(n, false);//usedd words
	int start = GetRndBefore(n);//first word
	vector<vector<bool>> UsedForKross;
	
	KrossWords.push_back(start);
	used[start] = true;
	Cords.push_back({Cord(0, 0), Cord(words[start].size() - 1, 0)});
	UsedForKross.push_back(vector<bool>(words[start].size()));
	
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


				int now = GetWord(used, words);
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
	

	return;
}

void Error(int i, int j) {
	std::locale l(getenv("LANG"));
    std::locale::global(l);
    wcout << "\nWE HAVE AN ERROR IN " << i + 1 << ' ' << j + 1;
    exit(0);
}

void solve() {
	std::locale l(getenv("LANG"));
    std::locale::global(l);
	vector<pair<Cord, Cord>> one;
	vector<wstring> two;
	vector<int> KrossWords;
	WordKross(two, one, KrossWords);

    int n = one.size();
    vector<pair<wstring, vector<int>>> words(n);
    int mnH = 1e9, mnN = 1e9, mxH = 0, mxN;
    for (int i = 0; i < n; ++i) {
        words[i].first = two[KrossWords[i]];
        vector<int> b = {one[i].first.x, one[i].first.y, one[i].second.x, one[i].second.y};
	mnH = min(mnH, min(one[i].first.x, one[i].second.x));
	mnN = min(mnN, min(one[i].first.y, one[i].second.y));
        words[i].second = b;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (j % 2 == 0) words[i].second[j] -= mnH, mxH = max(mxH, words[i].second[j]);
            else words[i].second[j] -= mnN, mxN = max(mxN, words[i].second[j]);
        }
    }
    wchar_t base[mxH + 1][mxN + 1];
    for (int i = 0; i < mxH + 1; ++i) {
        for (int j = 0; j < mxN + 1; ++j) {
            base[i][j] = ' ';
        }
    }
    for (auto [s, m] : words) {
        if (m[0] == m[2]) {
            for (int i = m[1]; i <= m[3]; ++i) {
                if (base[m[0]][i] == ' ' || base[m[0]][i] == s[i - m[1]]) {
                    base[m[0]][i] = s[i - m[1]];
                } else {
                    Error(m[0], i);
                }
            }
            reverse(s.begin(), s.end());
            for (int i = m[3]; i <= m[1]; ++i) {
                if (base[m[0]][i] == ' ' || base[m[0]][i] == s[i - m[3]]) {
                    base[m[0]][i] = s[i - m[3]];
                } else {
                    Error(m[0], i);
                }
            }
        } else {
            for (int i = m[0]; i <= m[2]; ++i) {
                if (base[i][m[1]] == ' ' || base[i][m[1]] == s[i - m[0]]) {
                    base[i][m[1]] = s[i - m[0]];
                } else {
                    Error(i, m[1]);
                }
            }
            reverse(s.begin(), s.end());
            for (int i = m[2]; i <= m[0]; ++i) {
                if (base[i][m[1]] == ' ' || base[i][m[1]] == s[i - m[2]]) {
                    base[i][m[1]] = s[i - m[2]];
                } else {
                    Error(i, m[1]);
                }
            }
        }
    }

    for (int i = 0; i < mxH + 1; ++i) {
        for (int j = mxN; j >= 0; --j) {
            wcout << base[i][j] << " ";
        }
        wcout << '\n';
    }
}

int main() {
	std::locale l(getenv("LANG"));
    std::locale::global(l);
	solve();
	return 0;
}

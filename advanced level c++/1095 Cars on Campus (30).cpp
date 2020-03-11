#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <map>
using namespace std;
struct node {
	char id[8];
	int tm, flag;
};
bool cmp1(node &a, node &b) {
	int r = strcmp(a.id, b.id);
	return r != 0 ? r < 0 : a.tm < b.tm;
}
bool cmp2(node &a, node &b) {
	return a.tm < b.tm;
}
int main() {
	int n, k, maxtm = -1, tmpidx = 0;
	scanf("%d%d\n", &n, &k);
	vector<node> v(n), car;
	for (int i = 0; i < n; i++) {
		char tmp[5];
		int h, m, s;
		scanf("%s %d:%d:%d %s\n", v[i].id, &h, &m, &s, tmp);
		v[i].tm = 3600 * h + 60 * m + s;
		v[i].flag = strcmp(tmp, "in") == 0 ? 1 : -1;
	}
	sort(v.begin(), v.end(), cmp1);
	map<string, int> mp;
	for (int i = 0; i < n - 1; i++)
		if (strcmp(v[i].id, v[i+1].id) == 0 && v[i].flag == 1 && v[i+1].flag == -1) {
			car.push_back(v[i]);
			car.push_back(v[i+1]);
			mp[v[i].id] += (v[i+1].tm - v[i].tm);
			if (maxtm < mp[v[i].id]) maxtm = mp[v[i].id];
		}
	sort(car.begin(), car.end(), cmp2);
	vector<int> cnt(car.size());
	for (int i = 0; i < car.size(); i++)
		if (i == 0) cnt[i] += car[i].flag;
		else cnt[i] = cnt[i - 1] + car[i].flag;
	for (int i = 0; i < k; i++) {
		int h, m, s;
		scanf("%d:%d:%d", &h, &m, &s);
		int j = tmpidx, tmptm = 3600 * h + 60 * m + s;
		for ( ; j < car.size(); j++)
			if (car[j].tm > tmptm) {
				if (j == 0) printf("0\n");
				else printf("%d\n", cnt[j - 1]);
				break;
			} else if (j == car.size() - 1)
				printf("%d\n", cnt[j]);
		tmpidx = j;
	}
	for (auto it = mp.begin(); it != mp.end(); it++)
		if (it->second == maxtm) printf("%s ", it->first.c_str());
	printf("%02d:%02d:%02d", maxtm / 3600, (maxtm % 3600) / 60, maxtm % 60);
	return 0;
}

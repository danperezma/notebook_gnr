#include <bits/stdc++.h>
#include <cstdio>
#define ld long double
#define ll long long
#define ii pair<int, int>
#define pb push_back
#define vii vector<ii>
#define ss second
#define ff first
#define vi vector<int>
#define iii pair<int, ii>
#define fast_io                                                                \
  ios_base::sync_with_stdio(0);                                                \
  cin.tie(0);                                                                  \
  cout.tie(0);
using namespace std;
 
template <typename T> ostream &operator<<(ostream &os, const vector<T> &v) {
  for (auto const &i : v) {
    os << i << " ";
  }
  os << '\n';
  return os;
}
struct stLazyC {
  int l, r, mid;
  ll sum = 0;
  stLazyC *right = NULL, *left = NULL;
  stLazyC(int l, int r) : l(l), r(r), sum(0) { mid = (l + r) >> 1; }
  ll prop = 0;
  void propagate() {
    if (!prop || l == r)
      return;
    if (left == NULL)
      left = new stLazyC(l, mid);
    if (right == NULL)
      right = new stLazyC(mid + 1, r);
    left->prop += prop;
    right->prop += prop;
 
    int hl = left->r - left->l + 1;
    int hr = right->r - right->l + 1;
    left->sum += hl * prop;
    right->sum += hr * prop;
    prop = 0;
  }
  void update(int a, int b, ll v) {
    // no sirve
    if (a > r || b < l)
      return;
    if (a <= l && r <= b) {
      int h = r - l + 1;
      prop += v;
      sum += (h * v);
      return;
    }
    if (left == NULL) {
      left = new stLazyC(l, mid);
    }
    if (right == NULL) {
      right = new stLazyC(mid + 1, r);
    }
    left->update(a, b, v);
    right->update(a, b, v);
    sum = left->sum + right->sum;
  }
 
  ll query(int a, int b) {
    propagate();
    // sirve
    if (a <= l && r <= b)
      return sum;
    // no sirve
    if (b < l || r < a)
      return 0;
    if (right == NULL && left == NULL)
      return 0;
    if (right == NULL)
      return left->query(a, b);
    if (left == NULL)
      return right->query(a, b);
    return left->query(a, b) + right->query(a, b);
  }
};
int32_t main() {
  int n, q;
  cin >> n >> q;
  vi nums(n);
  stLazyC tree(1, n);
  for (int i = 0; i < n; i++){
    cin >> nums[i];
    tree.update(i + 1, i + 1, nums[i]);
  }
  while (q--) {
    int type;
    cin >> type;
    if (type == 1) {
      int a, b, u;
      cin >> a >> b >> u;
      tree.update(a, b, u);
    } else {
      int k;
      cin >> k;
      cout << tree.query(k, k) << endl;
    }
  }
  return 0;
}

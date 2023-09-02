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


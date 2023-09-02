struct segtree{
    int l, r;
    segtree *left = nullptr, *right = nullptr;
    ll value = 0, lazy = 0;
    segtree(int l, int r, vl &v) : l(l), r(r){
        if(l == r){
            value = v[l];
            return;
        }
        int m = (l + r) / 2;
        left = new segtree(l, m, v);
        right = new segtree(m + 1, r, v);
        
        value = left->value + right->value;
    }
    void propagate(){
        if(!lazy || l == r) return;
        left->value += lazy * (left->r - left->l + 1);
        right->value += lazy * (right->r - right->l + 1);
        left->lazy += lazy;
        right->lazy += lazy;
        
        lazy = 0;
    }
    
    void update(int lx, int rx, ll v){
        propagate();
        if(l > rx || r < lx) return;
        if(l >= lx && r <= rx){
            value += v * (r - l + 1);
            lazy += v;
            return;
        }
        left->update(lx, rx, v);
        right->update(lx, rx, v);
        
        value = left->value + right->value;
    }
    
    ll query(int lx, int rx){
        propagate();
        if(l > rx || r < lx) return 0;
        if(l >= lx && r <= rx) return value;
        
        return left->query(lx, rx) + right->query(lx, rx);
    }
};
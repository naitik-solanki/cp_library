struct node {
	ll mn = INF, mx = -INF, val = 0;
	node() : mn(INF), mx(-INF), val(0) {};
};
struct SegTree {
	ll N;
	vector<node> st;
	vector<bool> cLazy;
	vector<ll> lazy;
	void init(ll n) {
		N = n;
		st.resize(4 * N + 5);
		cLazy.assign(4 * N + 5, false);
		lazy.assign(4 * N + 5, 0);
	}
	void merge(node &cur, node &l, node &r) {
		cur.mn = min(l.mn, r.mn), cur.mx = max(l.mx, r.mx), cur.val = l.val + r.val; // this is the normal function which you want to do for parents using left and right child
	}
	void propagate(ll ver, ll L, ll R) {
		if(L != R) {
			cLazy[ver * 2] = cLazy[ver * 2 + 1] = 1;
			lazy[ver * 2] += lazy[ver], lazy[ver * 2 + 1] += lazy[ver]; 
		}   
		st[ver].mn += lazy[ver], st[ver].mx += lazy[ver], st[ver].val += (R - L + 1) * lazy[ver]; // during lazy propagation you have to chg this line according to the condition
		cLazy[ver] = lazy[ver] = 0;
	}
	void build(ll ver, ll L, ll R, vector<ll> &a) {
		if(L > R) return;
		if(L == R) {
			st[ver].mn = a[L - 1], st[ver].mx = a[L - 1], st[ver].val = a[L - 1];
			return;
		}
		ll M = (L + R) / 2;
		build(ver * 2, L, M, a), build(ver * 2 + 1, M + 1, R, a);
		merge(st[ver], st[ver * 2], st[ver * 2 + 1]);
	}
	node Query(ll ver, ll L, ll R, ll i, ll j) {
		if(cLazy[ver]) propagate(ver, L, R);
		if(j < L || i > R) return node();
		if(i <= L && R <= j) return st[ver];
		ll M = (L+R) / 2;
		node left = Query(ver * 2, L, M, i, j), right = Query(ver * 2 + 1, M + 1, R, i, j), cur;
		merge(cur, left, right);
		return cur;
	}
	void Update(ll ver, ll L, ll R, ll i, ll j, ll val) {
		if(cLazy[ver]) propagate(ver, L, R);
		if(j < L || i > R) return;
		if(i <= L && R <= j) {
			cLazy[ver] = 1, lazy[ver] += val;
			propagate(ver, L, R);
			return;
		}
		ll M = (L + R) / 2;
		Update(ver * 2, L, M, i, j, val), Update(ver * 2 + 1, M + 1, R, i, j, val);
		merge(st[ver], st[ver * 2],st[ver * 2 + 1]);
	}
};

struct Node {
  int fa, ch[2];
};

class LinkCutTree {
 public:
  LinkCutTree(int n) : s(n + 1) {
    for (int i = 1; i <= n; ++i) {
      s[i].fa = s[i].ch[0] = s[i].ch[1] = 0;
    }
  }

  void link(int u, int v) {
    make_root(u);
    s[u].ch[1] = v;
    s[v].fa = u;
  }

  void cut(int u, int v) {
    access(u);
    make_root(v);
    s[v].fa = s[u].ch[1] = 0;
  }

  int find_root(int u) {
    access(u);
    while (s[u].ch[0]) {
      u = s[u].ch[0];
    }
    splay(u);
    return u;
  }

 private:
  std::vector<Node> s;

  void rotate(int x) {
    int y = s[x].fa;
    int z = s[y].fa;
    int k = (s[y].ch[1] == x);
    s[y].ch[k] = s[x].ch[1 - k];
    s[s[x].ch[1 - k]].fa = y;
    s[x].ch[1 - k] = y;
    s[y].fa = x;
    s[x].fa = z;
    if (z) s[z].ch[s[z].ch[1] == y] = x;
  }

  void splay(int x) {
    while (s[x].fa) {
      int y = s[x].fa;
      int z = s[y].fa;
      if (z) {
        if ((s[z].ch[0] == y) == (s[y].ch[0] == x)) rotate(y);
        else rotate(x);
      }
      rotate(x);
    }
  }

  void access(int u) {
    int v = 0;
    while (u) {
      splay(u);
      s[u].ch[1] = v;
      v = u;
      u = s[u].fa;
    }
  }

  void make_root(int u) {
    access(u);
    splay(u);
    if (s[u].ch[0]) {
      s[s[u].ch[0]].fa = 0;
      s[u].ch[0] = 0;
    }
  }
};

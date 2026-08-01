int parent[100005];
int color[100005];   // 0 = same team as my boss, 1 = opposite team of my boss

void make(int n) {
    for (int i = 1; i <= n; i++) { parent[i] = i; color[i] = 0; }
}

// find my top boss, and fix my color to be "relative to the top boss"
int find(int x) {
    if (parent[x] == x) return x;
    int boss = find(parent[x]);              // 1. find the real boss
    color[x] = color[x] ^ color[parent[x]];  // 2. my flip + my parent's flip-to-boss
    parent[x] = boss;                        // 3. point straight at the boss
    return boss;
}

// tell the DSU: x and y are on "d" teams. d = 0 means SAME, d = 1 means OPPOSITE.
// returns false if this clue CONTRADICTS what we already know.
bool unite(int x, int y, int d) {
    int bx = find(x), by = find(y);
    if (bx == by) {                          // already connected → just check
        return (color[x] ^ color[y]) == d;   // do the known flips agree with d?
    }
    color[by] = color[x] ^ color[y] ^ d;     // hook y's boss under x's boss with the right flip
    parent[by] = bx;
    return true;
}
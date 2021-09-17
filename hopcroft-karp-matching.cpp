struct bipartite_matching {
    int n_left, n_right, flow = 0, cur=0;
    vector<vector<int>> g;
    vector<int> match_from_left, match_from_right;

    bipartite_matching(int _n_left, int _n_right)
            : n_left(_n_left),
              n_right(_n_right),
              g(_n_left),
              match_from_left(_n_left, -1),
              match_from_right(_n_right, -1),
              dist(_n_left) {}

    void add(int u, int v) { g[u].push_back(v); }

    vector<int> dist;

    void bfs() {
        int q[N], sz=0;
        for (int u = 0; u < n_left; ++u) {
            if (match_from_left[u] == -1)
                q[sz++]=u, dist[u] = 0;
            else
                dist[u] = -1;
        }
        for(int i=0; i < sz; i++) {
            int u = q[i];
            for (auto v : g[u])
                if (match_from_right[v] != -1 and dist[match_from_right[v]] == -1) {
                    dist[match_from_right[v]] = dist[u] + 1;
                    q[sz++] = match_from_right[v];
                }
        }
    }

    bool dfs(int u) {
        int cnt = 0;
        for (auto v : g[u]) {
            if (match_from_right[v] == -1) {
                match_from_left[u] = v, match_from_right[v] = u;
                return true;
            } else if(dist[match_from_right[v]] == dist[u]+1 and dfs(match_from_right[v])) {
                match_from_left[u] = v, match_from_right[v] = u;
                return true;
            }
        }
        return false;
    }

    int get_max_matching() {
        while (true) {
            bfs();
            int augment = 0;
            for (int u = 0; u < n_left; ++u)
                if (!~match_from_left[u]) augment += dfs(u);
            if (!augment) break;
            flow += augment;
        }
        return flow;
    }

    pair<vector<int>, vector<int>> minimum_vertex_cover() {
        vector<int> L, R;
        for (int u = 0; u < n_left; ++u) {
            if (!~dist[u])
                L.push_back(u);
            else if (~match_from_left[u])
                R.push_back(match_from_left[u]);
        }
        return {L, R};
    }

    vector<pair<int, int>> get_edges() {
        vector<pair<int, int>> ans;
        for (int u = 0; u < n_left; ++u)
            if (match_from_left[u] != -1)
                ans.emplace_back(u, match_from_left[u]);
        return ans;
    }
};
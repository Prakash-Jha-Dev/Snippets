/// Name: AhoCorasick
/// Description: String automata to find occurences of patterns in a string
/// Detail: String, Automata, Pattern matching
/// Guarantee: } // AhoCorasick

// Reference : https://discuss.codechef.com/t/twostrs-editorial/64199


template<int ALPHABET_SIZE, unsigned char MINIMAL_CHAR>
struct AhoCorasick {
    static constexpr int NON_EXISTENT_NODE_ID = -1;
    static constexpr int FAKE_NODE_ID = 0;
    static constexpr int ROOT_ID = 1;

    int currentNode;

    vector<array<int, ALPHABET_SIZE>> edges;
    vector<int> suffixLink;

    vector<long long> sum;

    explicit AhoCorasick(const vector<pair<string, int>> &a) : currentNode(ROOT_ID), edges(2),
                                                               suffixLink(2, FAKE_NODE_ID), sum(2, 0) {
        edges[FAKE_NODE_ID].fill(ROOT_ID);
        edges[ROOT_ID].fill(NON_EXISTENT_NODE_ID);

        for (const auto &p : a) {
            int node = ROOT_ID;
            for (unsigned char c : p.first) {
                c -= MINIMAL_CHAR;
                if (edges[node][c] == -1) {
                    edges[node][c] = edges.size();
                    edges.emplace_back();
                    edges.back().fill(NON_EXISTENT_NODE_ID);
                    suffixLink.push_back(NON_EXISTENT_NODE_ID);
                    sum.push_back(0);
                }
                node = edges[node][c];
            }
            sum[node] += p.second;
        }

        queue<int> q;
        q.push(ROOT_ID);
        while (!q.empty()) {
            int node = q.front();
            if (suffixLink[node] != NON_EXISTENT_NODE_ID) {
                sum[node] += sum[suffixLink[node]];
            }
            q.pop();
            for (int i = 0; i < ALPHABET_SIZE; i++) {
                int child = edges[node][i];
                if (child == NON_EXISTENT_NODE_ID) {
                    edges[node][i] = edges[suffixLink[node]][i];
                } else {
                    suffixLink[child] = edges[suffixLink[node]][i];
                    q.push(child);
                }
            }
        }
    }

    void setNode(int node) {
        currentNode = node;
    }

    void resetNode() {
        setNode(ROOT_ID);
    }

    long long getCurrentNodeSum() {
        return sum[currentNode];
    }

    void move(unsigned char c) {
        c -= MINIMAL_CHAR;
        currentNode = edges[currentNode][c];
    }
};  // AhoCorasick
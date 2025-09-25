#include <iostream>
#include <vector>
#include <random>
#include <climits>
using namespace std;
using i64 = long long;


static bool check(const vector<long long>& D, int M, long long maxJump) {
    int removed = 0;
    size_t cur = 0;
    size_t sz = D.size();
    for (size_t i = 1; i < sz; ++i) {
        if (D[i] - D[cur] < maxJump) {
            if (++removed > M) return false;
        } else {
            cur = i;
        }
    }
    return true;
}


long long solve(const vector<long long>& D, int M, long long L) {
    long long low = 0, high = 0;
    for (size_t i = 1; i < D.size(); ++i) {
        high = max(high, D[i] - D[i - 1]);
    }
    long long ans = high;
    while (low <= high) {
        long long mid = (low + high) / 2;
        if (check(D, M, mid)) {
            ans = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return ans;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int Y;
    if (!(cin >> Y)) return 0;

    long long minValue = LLONG_MAX;

    for (int y = 0; y < Y; ++y) {
        long long L; int N, M; long long s, P;
        cin >> L >> N >> M >> s >> P;

        // Generate D[1..N] via MT19937_64(seed=s)
        std::mt19937_64 rng((unsigned long long)s);
        vector<long long> D((size_t)N + 2, 0); // 1-based, D[0] = 0
        for (int j = 1; j <= N; ++j) {
            long long gap = (rng() % P) + 1ULL;
            D[j] = D[j- 1] + (long long)gap;
        }
        D[N + 1] = L;
        // Guaranteed: 0 < D[1] < ... < D[N] < L
        long long result = solve(D, M, L);
        minValue = min(minValue, result);

    }

    cout << minValue << '\n';

    return 0;
}
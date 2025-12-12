#include <iostream>
#include <vector>
#include <random>
#include <climits>
#include <chrono>
using namespace std;
using i64 = long long;


bool check(const vector<long long>& D, int M, long long maxJump) {
    int removed = 0;
    int cur = 0;
    int sz = D.size();
    for (int i = 1; i < sz; ++i) {
        if (D[i] - D[cur] < maxJump) {
            if (++removed > M) return false;
        } else {
            cur = i;
        }
    }
    return true;
}


long long solve(const vector<long long>& D, int M, long long L) {
    long long low = 1;
    long long high = L;

    if (M >= (int)D.size() - 2) return L;

    long long ans = 0;
    while (low <= high) {
        long long mid = (low + high) >> 1;
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
    auto start = chrono::high_resolution_clock::now();

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int Y;
    if (!(cin >> Y)) return 0;

    long long minValue = LLONG_MAX;

    vector<long long> D;
    D.reserve(10002);

    for (int y = 0; y < Y; ++y) {
        long long L; int N, M; long long s, P;
        cin >> L >> N >> M >> s >> P;

        D.clear();
        D.resize(N + 2);

        // Generate D[1..N] via MT19937_64(seed=s)
        std::mt19937_64 rng((unsigned long long)s);
        for (int j = 1; j <= N; ++j) {
            long long gap = (rng() % P) + 1ULL;
            D[j] = D[j - 1] + (long long)gap;
        }
        D[N + 1] = L;
        // Guaranteed: 0 < D[1] < ... < D[N] < L
        long long result = solve(D, M, L);
        minValue = min(minValue, result);

    }

    printf("%lld\n", minValue);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    cerr << "Elapsed time: " << elapsed.count() << " seconds\n";

    return 0;
}
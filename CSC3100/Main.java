import java.io.*;
import java.util.*;

public class Main {
    static final class MT19937_64 {
        static final int NN = 312, MM = 156, RR = 31;
        static final long AA = 0xB5026F5AA96619E9L;
        static final int UU = 29, SS = 17, TT = 37, LL = 43;
        static final long DD = 0x5555555555555555L;
        static final long BB = 0x71D67FFFEDA60000L;
        static final long CC = 0xFFF7EEE000000000L;
        static final long FF = 6364136223846793005L;
        static final long MASK = -1L, LOWER = ((1L << RR) - 1), UPPER = (MASK ^ LOWER);
        long[] mt = new long[NN];
        int idx = NN;

        MT19937_64(long seed) {
            seed(seed);
        }

        void seed(long seed) {
            mt[0] = seed;
            for (int i = 1; i < NN; ++i) {
                long x = mt[i - 1] ^ (mt[i - 1] >>> 62);
                mt[i] = FF * x + i;
            }
            idx = NN;
        }

        void twist() {
            for (int i = 0; i < NN; ++i) {
                long xA = (mt[i] & UPPER) | (mt[(i + 1) % NN] & LOWER);
                long xA_ = xA >>> 1;
                if ((xA & 1) != 0)
                    xA_ ^= AA;
                mt[i] = mt[(i + MM) % NN] ^ xA_;
            }
            idx = 0;
        }

        long nextLong() {
            if (idx == NN)
                twist();
            long y = mt[idx++];
            y ^= (y >>> UU) & DD;
            y ^= (y << SS) & BB;
            y ^= (y << TT) & CC;
            y ^= (y >>> LL);
            return y;
        }
    }

    private static boolean check(long[] D, int M, long maxJump) {
        int removed = 0;
        int cur = 0;
        for (int i = 1; i < D.length; i++) {
            if (D[i] - D[cur] < maxJump) {
                removed++;
                if (removed > M) return false;
            } else {
                cur = i;
            }
        }
        return true;
    }
    
    private static long solve(long[] D, int M, long L) {
        long low = 1, high = L, ans = 1;
        if (M >= D.length - 2) return L;
        while (low <= high) {
            long mid = (low + high) >>> 1;
            if (check(D, M, mid)) {
                ans = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return ans;
    }

    public static void main(String[] args) throws Exception {

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String sLine = br.readLine();
        if (sLine == null || sLine.isEmpty())
            return;
        int Y = Integer.parseInt(sLine.trim());
        long minValue = Long.MAX_VALUE;
        for (int t = 0; t < Y; ++t) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            long L = Long.parseLong(st.nextToken());
            int N = Integer.parseInt(st.nextToken());
            int M = Integer.parseInt(st.nextToken());
            long s = Long.parseLong(st.nextToken());
            long P = Long.parseLong(st.nextToken());
            
            MT19937_64 rng = new MT19937_64(s);
            long[] D = new long[N + 2]; // 1-based, D[0]=0
            for (int j = 1; j <= N; ++j) {
                long gap = Long.remainderUnsigned(rng.nextLong(), P) + 1L;
                D[j] = D[j - 1] + gap;
            }
            D[N + 1] = L;    
            
            long result = solve(D, M, L);
            if (result < minValue) {
                minValue = result;
            }
        }
        System.out.println(minValue);
    }
}
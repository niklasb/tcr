import java.lang.*;
import java.util.*;
import java.io.*;
import java.math.*;

class Main {
    final static int MAX = 255;
    static BigInteger[] fac;
    static void initFac() {
        BigInteger bi = BigInteger.ONE;
        fac = new BigInteger[MAX + 1];
        fac[0] = BigInteger.ONE;
        for (int i = 1; i <= MAX; ++i) {
            fac[i] = fac[i - 1].multiply(bi);
            bi = bi.add(BigInteger.ONE);
        }
    }
    public static void main(String[] args) {
        Scanner sc = new Scanner(new BufferedReader(new InputStreamReader(System.in)));
        while (sc.hasNextInt()) {
            int total = sc.nextInt();
            BigInteger rank = sc.nextBigInteger();
        }
    }
}

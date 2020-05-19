
// bit solution
import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();
        for (int times = 0; times < t; times++) {
            int n = sc.nextInt();
            int k = sc.nextInt();
            int x = sc.nextInt();
            int[] a = new int[n];
            List<Integer> vec = new ArrayList<Integer>();
            for (int i = 0; i < n; i++)
                a[i] = sc.nextInt();
            for (int i = 0; i < (1 << n); i++) {
                int sum = 0, cnt = 0;
                for (int j = 0; j < n; ++j)
                    if ((i >> j) % 2 == 1) {
                        sum += a[j];
                        cnt++;
                    }
                if (cnt == k)
                    vec.add(sum);
            }
            Collections.sort(vec, Comparator.reverseOrder());
            System.out.println(vec.get(x - 1));
        }
    }
}

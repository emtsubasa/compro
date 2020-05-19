import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();
        for (int times = 0; times < t; times++) {
            int k = sc.nextInt();
            int[] a = new int[k + 1];
            Boolean res = true;
            for (int i = 0; i < k; ++i)
                a[i + 1] = sc.nextInt();
            int n = sc.nextInt();
            for (int i = 0; i < n; i++)
                if (a[sc.nextInt()]-- == 0)
                    res = false;
            if (res)
                System.out.println("wa-i");
            else
                System.out.println("e-n");
        }
    }
}

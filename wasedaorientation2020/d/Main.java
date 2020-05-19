import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();
        for (int times = 0; times < t; times++) {
            int n = sc.nextInt();
            int k = sc.nextInt();
            int sum = n;
            while (true) {
                int now = n / k;
                if (now == 0)
                    break;
                sum += now;
                n -= now * (k - 1);
            }
            System.out.println(sum);
        }
    }
}

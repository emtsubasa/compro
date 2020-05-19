import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();
        for (int times = 0; times < t; times++) {
            int n = sc.nextInt(), res = 0;
            for (int i = 0; i < n; i++)
                res += sc.nextInt();
            System.out.println(res);
        }
    }
}

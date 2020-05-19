import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();
        for (int times = 0; times < t; times++) {
            int n = sc.nextInt(), win = 0, lose = 0, draw = 0;
            int[] y = new int[n], k = new int[n];
            for (int i = 0; i < n; i++)
                y[i] = sc.nextInt();
            for (int i = 0; i < n; i++)
                k[i] = sc.nextInt();
            for (int i = 0; i < n; i++) {
                if (y[i] == k[i])
                    ++draw;
                else if ((y[i] - k[i] + 3) % 3 == 2)
                    ++win;
                else
                    ++lose;
            }
            System.out.println(win + " " + lose + " " + draw);
        }
    }
}

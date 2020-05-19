import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();
        for (int times = 0; times < t; times++) {
            int n = sc.nextInt();
            String s = sc.next();
            String target = "2520";
            Boolean res = false;
            for (int i = 0; i < n - 3; i++)
                if (s.substring(i, i + 4).equals(target))
                    res = true;
            System.out.println(res ? "Yes" : "No");
        }
    }
}

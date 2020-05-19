import java.util.*;
public class Main{
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();
        for(int times = 0;times < t;times++){
            int d = sc.nextInt();
            int w = sc.nextInt();
            int a = sc.nextInt();
            if(a * w * 2 == d) 
                System.out.println("Yes");
            else
                System.out.println("No");
        }
    }
}

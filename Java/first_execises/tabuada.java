import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));

        int N = Integer.parseInt(bufferedReader.readLine().trim());

        for (int i = 1; i < 11; i++) {
            System.out.println(N + " x " + i + " = " + N*i);
        }

        bufferedReader.close();
    }
}

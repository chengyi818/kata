import java.util.Scanner;
import test.Post;

public class HelloWorld {
	private static void foo() throws Exception {
        int x = 5 / 0;
        System.out.println(x);
    }

	public static void main(String[] args) {
        try {
            foo();
        } catch (Exception e) {
            e.printStackTrace();
        }
        System.out.println("program is still running here!");
	}
}

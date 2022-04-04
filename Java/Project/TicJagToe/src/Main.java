import java.util.Scanner;

public class App {
    static Scanner scan = new Scanner(System.in);
    public static void main(String[] args) throws Exception {
        Menu();
    }

    static void Menu(){
        System.out.println("===============");
        System.out.println("| Tic-Jag-Toe |");
        System.out.println("===============");
        System.out.println("| 1. Login    |");
        System.out.println("| 2. Register |");
        System.out.println("| 3. Exit     |");
        System.out.println("===============");
        System.out.print("Choose [1-3] >> ");
        int input = scan.nextInt();scan.nextLine();
        switch (input) {
            case 1:
                // login()
                break;
            case 2:
                // register()
                break;
            case 3:
                // system.exit(1);
                break;
            default:
                break;
        }
    }
}

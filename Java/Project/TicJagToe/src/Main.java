import java.util.Scanner;

public class Main {
    Scanner scan = new Scanner(System.in);
    Player player = new Player();
    Main(){
        Menu();
    }

    void Menu(){
        System.out.println("===============");
        System.out.println("| Tic-Jag-Toe |");
        System.out.println("===============");
        System.out.println("| 1. Login    |");
        System.out.println("| 2. Register |");
        System.out.println("| 3. Exit     |");
        System.out.println("===============");
        System.out.print("Choose [1-3] >> ");
        int input = 0;
        try {
            input = scan.nextInt();scan.nextLine();
        } catch (Exception e) {
            System.out.println("Invalid input");
        }
        switch (input) {
            case 1:
                login();
                break;
            case 2:
                register();
                break;
            case 3:
                System.exit(1);
                break;
            default:
                break;
        }
        Menu();
    }
    
    void login(){
        // input validation
        if(player.name.isEmpty()){
            System.out.println("no account to login");
            return;
        }
        String name , password;
        System.out.println("Input name [type '0' to go back] : ");
        name = scan.nextLine();
        System.out.println(name.equals("0"));
        if (name.equals("0")){
            return;
        }
        System.out.println("Input password [type '0' to go back] : ");
        password = scan.nextLine();
        System.out.println(password.equals("0"));
        if (password.equals("0")){
            return;
        }
        boolean password_false = false,name_false = false;
        if(!player.name.equals(name)){
            System.out.println("Wrong username!");
            name_false = true;
        }
        if(!player.password.equals(password)){
            System.out.println("Wrong password!");
            password_false = true;
        }

        if(name_false == true || password_false == true){
            login();
        }
        else if (name_false == false && password_false == false){
            gamemenu();
        }
        return;
    }

    void register(){
        if(!player.name.isEmpty()){
            System.out.println("You already have an account!");
            return;
        }

        String name;
        do{
            System.out.print("Input name to play [more than 3 and less than 15 characters] : ");
            name = scan.nextLine();scan.nextLine();
            if(name.length() > 3 && name.length() < 15){
                break;
            }
        }while(true);
        player.setName(name);
        
        String password;
        // doesn't have alphanumeric character validation
        do {
            System.out.print("Input password [alphanumeric & more than 5 characters] : ");
            password = scan.nextLine();scan.nextLine();
            if (password.length()>5){
                break;
            }
        } while (true);
        player.setPassword(password);
    }

    void gamemenu(){
        System.out.println("=================");
        System.out.println("|  Tic-Jag-Toe  |");
        System.out.println("=================");
        System.out.println("| 1. Play       |");
        System.out.println("| 2. Scoreboard |");
        System.out.println("| 3. Back       |");
        System.out.println("=================");
        System.out.print("Choose [1-3] >> ");
        int input = 0;
        try {
            input = scan.nextInt();scan.nextLine();
        } catch (Exception e) {
            System.out.println("Invalid input");
        }
        switch (input) {
            case 1:
                // plaly();
                break;
            case 2:
                // Scoreboard();
                break;
            case 3:
                return;
                break;
            default:
                System.out.println("invalid input");
                break;
        }
        gamemenu();
    }

    public static void main(String[] args) throws Exception {
        new Main();
    }
}

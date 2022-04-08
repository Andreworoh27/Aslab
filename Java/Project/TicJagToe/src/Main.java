import java.util.Random;
import java.util.Scanner;

public class Main {
    Scanner scan = new Scanner(System.in);
    Player player = new Player();
    Character[][] map = {{'1','2','3'},{'4','5','6'},{'7','8','9'}};
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
        if(player.getName().isEmpty()){
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
        if(!player.getName().equals(name)){
            System.out.println("Wrong username!");
            name_false = true;
        }
        if(!player.getPassword().equals(password)){
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
        if(!player.getName().isEmpty()){
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
            boolean number = false,alphabet= false,logo = false;
            for(int i=0;i<password.length();i++){
                if((password.charAt(i)>='a' && password.charAt(i)<= 'z') || (password.charAt(i)>='A' && password.charAt(i)<= 'Z')){
                    alphabet = true;
                }
                else if(password.charAt(i)>='0' && password.charAt(i)<='9'){
                    number = true;
                }
                else if (password.charAt(i)!=' '){
                    logo = true;
                }
            }
            System.out.println(number +" "+alphabet +" "+logo);
            if (password.length()>5 && number == true && alphabet == true && logo == false){
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
                play();
                break;
            case 2:
                // Scoreboard();
                break;
            case 3:
                return;
            default:
                System.out.println("invalid input");
                break;
        }
        gamemenu();
    }

    void play(){
        System.out.println("Player Detail :");
        System.out.println("Name    : " + player.getName());
        System.out.println("Score   : " + player.getScore());
        System.out.println("=================================");
        System.out.println("Select difficulty :");
        System.out.println("1. Easy");
        System.out.println("2. Hard");
        System.out.println("3. PvP");
        System.out.println("4. Back");
        System.out.println("=================================");
        System.out.print("Choose [1-4] >> ");
        int input = 0;
        try {
            input=scan.nextInt();
        } catch (Exception e) {
            System.out.println("Invalid Input");
        }
        scan.nextLine();
        switch (input) {
            case 1:
                // turn = 1 -> player move first
                // turn = 2 -> bot move first
                if(generate_random(3, 1) == 2){
                    turn = 2;
                }
                else{
                    turn = 1;
                }
                easy();
                break;
            case 4:
                return;
            default:
                break;
        }
        play();
    }

    int turn ;
    void easy(){
        printboard();
        System.out.println("");
        System.out.println("Your move : ");
        System.out.println("Enemy moves :");
        int input,x=0,y=0;
        if(turn==1){
            System.out.println("Choose [1-9] >>");
            input = scan.nextInt();scan.nextLine();
            if(input>=1 && input<=3){
                x=0;
                y=input-1;
            }
            else if (input>=4 && input<=6){
                x=1;
                y=input-4;
            }
            else if (input>=7 && input<=9){
                x=2;
                y=input-7;
            }
            move(x,y,turn);
            turn = 2;
        }
        else{
            System.out.print("Computer choose ");
            delay(1000);
            input = generate_random(10, 1);
            System.out.println(input);
            if(input>=1 && input<=3){
                x=0;
                y=input-1;
            }
            else if (input>=4 && input<=6){
                x=1;
                y=input-4;
            }
            else if (input>=7 && input<=9){
                x=2;
                y=input-7;
            }
            move(x,y,turn);
            turn = 1;
            delay(2000);
        }
        easy();
        return;
    }

    void move(int x,int y,int turn){
        if(turn ==1){
            map[x][y]='X';
        }
        else{
            map[x][y]='O';
        }
        return;
    }

    void printboard(){
        cls();
        System.out.printf(" %c | %c | %c |\n",map[0][0],map[0][1],map[0][2]);
        System.out.println("---|---|---|");                                     
        System.out.printf(" %c | %c | %c |\n",map[1][0],map[1][1],map[1][2]);   
        System.out.println("---|---|---|");                                     
        System.out.printf(" %c | %c | %c |\n",map[2][0],map[2][1],map[2][2]);   
    }
    int generate_random(int max,int min){
        return (int)(Math.random()*(max - min) + min);
    }
    void delay(int time){
        try {
            Thread.sleep(time);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    void cls(){
        System.out.print("\033[H\033[2J");  
        System.out.flush();  
    }
    public static void main(String[] args) throws Exception {
        new Main();
    }
}

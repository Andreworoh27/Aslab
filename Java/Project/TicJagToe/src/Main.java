import java.util.ArrayList;
import java.util.Random;
import java.util.Scanner;

public class Main {
    Scanner scan = new Scanner(System.in);
    Player player = new Player();
    Character[][] mapawal = {{'1','2','3'},{'4','5','6'},{'7','8','9'}};
    Character[][] map = {{'1','2','3'},{'4','5','6'},{'7','8','9'}};
    int playeridx=0;
    int player1=-1,player2=-1;
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
        if(playeridx == 0){
            System.out.println("no account to login");
            return;
        }
        String name , password;
        System.out.println("Input name [type '0' to go back] : ");
        name = scan.nextLine();
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
        for (int i = 0; i < playeridx; i++) {
            password_false = false;name_false = false;
            if(!player.getName(i).equals(name)){
                name_false = true;
            }
            if(!player.getPassword(i).equals(password)){
                password_false = true;
            }
            if(name_false == false && password_false == false){
                player1 = i;
                break;
            }
        }

        if(name_false == true || password_false == true){
            System.out.println("Wrong username or password");
            login();
        }
        else if (name_false == false && password_false == false){
            gamemenu();
        }
        return;
    }

    void register(){
        String name;
        do{
            System.out.print("Input name to play [more than 3 and less than 15 characters] : ");
            name = scan.nextLine();
            if(name.length() > 3 && name.length() < 15){
                break;
            }
        }while(true);
        player.addName(name);;
        
        String password;
        do {
            System.out.print("Input password [alphanumeric & more than 5 characters] : ");
            password = scan.nextLine();
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
        player.addPassword(password);;;
        player.addScore(0);
        playeridx++;
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
        System.out.println("Name    : " + player.getName(player1));
        System.out.println("Score   : " + player.getScore(player1));
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
                reset();
                break;
            case 2:
                if(generate_random(3, 1) == 2){
                    turn = 2;
                }
                else{
                    turn = 1;
                }
                hard();
                reset();
                break;
            case 3:
                if(generate_random(3, 1) == 2){
                    turn = 2;
                }
                else{
                    turn = 1;
                }
                pvp();
                reset();
                break;
            case 4:
                return;
            default:
                break;
        }
        play();
    }

    int turn=0;
    int winner=0;
    ArrayList<Integer> move1 = new ArrayList<>();
    ArrayList<Integer> move2 = new ArrayList<>();

    void easy(){
        printboard();
        movehistory();
        int input,x=0,y=0;
        if(turn==1){
            do{
                System.out.println("Your move : ");
                System.out.println("Choose [1-9] >>");
                input = scan.nextInt();scan.nextLine();
                if(movevalidation(input)){
                    break;
                }
                System.out.println("Invalid move");
            }while(true);

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
            move1.add(input);
            move(x,y,turn);
            turn = 2;
        }
        else{
            System.out.println("Enemy moves :");
            System.out.print("Computer choose ");
            delay(1000);
            do{
                input = generate_random(10, 1);
                if(movevalidation(input)){
                    break;
                }
            }while(true);
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
            move2.add(input);
            move(x,y,turn);
            turn = 1;
            delay(2000);
        }

        if(wincondition()){
            if (winner == -1) {
                System.out.println("Draw");
            }
            else if(winner == 1){
                System.out.println("[*] Player Wins!");
                System.out.println("Press enter to continue...");scan.nextLine();
                int score = player.getScore(player1);
                player.setScore((score+10), player1);
            }
            else if(winner == 2){
                System.out.println("[*] Computer Wins!");
                System.out.println("Press enter to continue...");scan.nextLine();
                int score = player.getScore(player1);
                player.setScore((score-10), player1);
            }
            return;
        }
        easy();
        return;
    }

    void hard(){
        printboard();
        movehistory();
        int input,x=0,y=0;
        if(turn==1){
            do{
                System.out.println("Your move : ");
                System.out.println("Choose [1-9] >>");
                input = scan.nextInt();scan.nextLine();
                if(movevalidation(input)){
                    break;
                }
                System.out.println("Invalid move");
            }while(true);

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
            move1.add(input);
            move(x,y,turn);
            turn = 2;
        }
        else{
            System.out.println("Enemy moves :");
            System.out.print("Computer choose ");
            delay(1000);
            input = bothardmove();
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
            move2.add(input);
            move(x,y,turn);
            turn = 1;
            delay(2000);
        }

        if(wincondition()){
            if (winner == -1) {
                System.out.println("Draw");
            }
            else if(winner == 1){
                System.out.println("[*] Player Wins!");
                System.out.println("Press enter to continue...");scan.nextLine();
                int score = player.getScore(player1);
                player.setScore((score+100), player1);
            }
            else if(winner == 2){
                System.out.println("[*] Computer Wins!");
                System.out.println("Press enter to continue...");scan.nextLine();
                int score = player.getScore(player1);
                player.setScore((score-10), player1);
            }
            return;
        }
        hard();
        return;
    }

    int bothardmove(){
        int x=0,y=0,input;
        if(map[1][1]=='X' && move1.size()==1){
            do {
                input = generate_random(10, 1);
                if(input%2==1 && input!=5 && movevalidation(input)){
                    return input;
                }
            } while (true);
        }
        else if ((map[1][1]=='X'&& map[1][1]!='O') && move1.size()==1){
            return 5;
        }
        else{
            do{
                input = generate_random(10, 1);
                if(movevalidation(input)){
                    break;
                }
            }while(true);
            return input;
        }
    }
    
    void pvp(){

    }

    void movehistory(){
        System.out.println("Player moves :");
        for (int i=0;i<move1.size();i++){
            System.out.println("X on "+move1.get(i));
        }

        System.out.printf("\n\n");
        System.out.println("Enemy moves :");
        for (int i=0;i<move2.size();i++){
            System.out.println("O on "+move2.get(i));
        }
        System.out.printf("\n\n");
        return;
    }

    boolean movevalidation(int input){
        int x=0,y=0;
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
        if (map[x][y]!='X' && map[x][y]!='O') {
            return true;
        }
        else{
            return false;
        }
    }

    boolean wincondition(){
        int full=0;
        for (int i = 0; i < 3; i++) {
            for(int j = 0 ;j < 3 ; j++){
                if (map[i][j]=='X' || map[i][j]=='X') {
                    full+=1;
                }
            }
        }
        if(full == 9){
            winner= -1;
            return true;
        }
        // horizontal
        for (int i = 0; i < 3; i++) {
            int counterx=0,countery=0;
            for(int j = 0 ;j < 3 ; j++){
                if(map[i][j]=='X'){
                    counterx+=1;
                }
                else if (map[i][j]=='O'){
                    countery+=1;
                }
            }
            if(counterx == 3){
                winner = 1;
                return true;
            }
            if(countery == 3){
                winner = 2;
                return true;
            }
        }

        // vertical
        for (int i = 0; i < 3; i++) {
            int counterx=0,countery=0;
            for(int j = 0 ;j < 3 ; j++){
                if(map[j][i]=='X'){
                    counterx+=1;
                }
                else if (map[j][i]=='O'){
                    countery+=1;
                }
            }
            if(counterx == 3){
                winner = 1;
                return true;
            }
            if(countery == 3){
                winner = 2;
                return true;
            }
        }

        // diagonal
        if(map[0][0]=='X' && map[1][1]=='X' && map[2][2]=='X'){
            winner = 1;
            return true;
        }
        else if(map[2][0]=='X' && map[1][1]=='X' && map[0][2]=='X'){
            winner = 1;
            return true;
        }

        if(map[0][0]=='O' && map[1][1]=='O' && map[2][2]=='O'){
            winner = 2;
            return true;
        }
        else if(map[2][0]=='O' && map[1][1]=='O' && map[0][2]=='O'){
            winner = 2;
            return true;
        }

        return false;
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

    void reset(){
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                mapawal[i][j] = map[i][j];
            }
        }
        move1.removeAll(move1);
        move2.removeAll(move2);
        winner = 0;
        turn = 0;
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

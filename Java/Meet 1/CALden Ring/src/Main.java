import java.util.Scanner;
import javax.swing.plaf.TextUI;

public class Main {
    static Scanner scan = new Scanner(System.in);
    static Player player = new Player();
    static Enemy enemy = new Enemy();
    static int stage;

    static void cls(){
        System.out.print("\033[H\033[2J");
        System.out.flush();
    }

    public static void main(String[] args){
        Menu();
    }

    static void Menu(){
        cls();
        System.out.println("CALden Ring");
        System.out.println("======================");
        System.out.println("1. Play");
        System.out.println("2. Quit");
        int input = scan.nextInt();scan.nextLine();
        switch (input) {
            case 1:
                cls();
                Play();
                player.MaxHealth = player.health = 50;
                player.NormalAttack = player.attack = 10;
                player.potion = "";
                player.money = 20;
                enemy.DefautHealth = enemy.health = 20;
                enemy.attack = 10;
                break;
            case 2:
                cls();
                System.out.println("Thank you");
                System.exit(1);
                return;
            default:
                cls();
                System.out.println("input invalid");
                Menu();
                break;
        }
        return;
    }

    static void Play(){
        System.out.println("1. Easy");
        System.out.println("2. Normal");
        System.out.println("3. Hard");
        System.out.print(">> ");
        int input = scan.nextInt();scan.nextLine();
        switch (input) {
            case 1:
                cls();
                Easy();
                return;
            case 2:
                cls();
                Normal();
                return;
            case 3:
                cls();
                Hard();
                return;
            default:
                cls();
                System.out.println("Invalid input");
                Play();
                break;
        }
        return;
    }

    static void Easy(){
        player.NormalAttack = player.attack = 1.2 * player.attack;
        enemy.health=enemy.DefautHealth = 0.8 * enemy.DefautHealth;
        stage = 3;
        Battle(1);
        return;
    }

    static void Normal(){
        player.NormalAttack = player.attack = 1 * player.attack;
        enemy.health=enemy.DefautHealth = 1 * enemy.DefautHealth;
        stage = 4;
        Battle(1);
        return;
    }

    static void Hard(){
        player.NormalAttack = player.attack = 0.8 * player.attack;
        enemy.health=enemy.DefautHealth = 1.2 * enemy.DefautHealth;
        stage = 5;
        Battle(1);
        return;
    }

    static boolean Escape=false,Attack=false,exit=false;

    static void Battle(int StageNow){
        if(exit == true){
            exit = false;
            Menu();
            return;
        }
        cls();
        System.out.println("Stage " + StageNow);
        System.out.println("Enemy health : " + enemy.health);
        System.out.println("Your Current Health : " + player.health);
        System.out.println("1. Attack");
        if(player.potion.isEmpty()){
            System.out.println("2. Use Item (No Item)");
        }
        else{
            System.out.println("2. Use Item " + "(" + player.potion + ")");
        }
        System.out.println("3. Escape");
        System.out.print(">> ");
        int input = scan.nextInt();scan.nextLine();
        switch (input) {
            case 1:
                enemy.health -= player.attack;
                System.out.println("The Warrior deals " + player.attack +" damage to the enemy!");
                if(Attack == true){
                    Attack = false;
                    player.attack = player.NormalAttack;
                }
                scan.nextLine();
                break;
            case 2:
                if(player.potion.isEmpty()){
                    System.out.println("You have no item to use");
                    Battle(StageNow);
                }
                else if (player.potion.equals("Health Potion")){
                    if(player.health + player.MaxHealth * 0.5 > player.MaxHealth){
                        player.health = player.MaxHealth;
                    }
                    else{
                        player.health += player.MaxHealth*0.5;
                        Attack = true;
                    }
                    System.out.println("Health Potion Used!");
                    player.potion = "";
                }
                else if (player.potion.equals("Attack Potion")){
                    player.attack += player.NormalAttack*0.5;
                    Attack = true;
                    System.out.println("Attack Potion Used!");
                    player.potion = "";
                }
                break;
            case 3:
                int random = (int)(Math.random() * ((100 - 1) +1));
                if (random <= 30) {
                    Escape = true;
                    System.out.println("Escape Success!");
                }
                else {
                    Escape = false;
                    System.out.println("Escape Failed!");
                }
                break;
            default:
                System.out.println("input invalid");
                Battle(StageNow);
                break;
        }

        if(enemy.health <=0 || Escape == true){
            if(StageNow+1 > stage){
                System.out.println("You won");
                Menu();
                return;
            }
            Escape = false;
            enemy.health=enemy.DefautHealth+=3;
            player.money+=10;
            rest();
            Battle(StageNow +=1);
            return;
        }
        else{
            player.health-=enemy.attack;
            System.out.println("The Enemy deals "+ enemy.attack +" damage to the Warior!");scan.nextLine();
            if(player.health<=0){
                System.out.println("You have died");
                return;
            }
            else{
                Battle(StageNow);
            }
        }
        return;
    }

    static void rest(){
        cls();
        System.out.println("You have arrives at the Site of Grace! Choose an option!");
        System.out.println("===============================================");
        System.out.println("1. Enter Shop");
        System.out.println("2. Continue");
        System.out.println("3. Quit Game");
        System.out.print(">> ");
        int input = scan.nextInt();scan.nextLine();
        switch (input) {
            case 1:
                do{
                    cls();
                    System.out.println("Your Current Money : "+player.money);
                    System.out.println("You have arrived at a shop! Choose what to do: ");
                    System.out.println("============================================");
                    System.out.println("1. Buy Health Potion (add 50% health) (10 money)");
                    System.out.println("2. Buy Attack Potion (add 50% attack) (20 money)");
                    System.out.println("3. Exit Shop");
                    System.out.print(">> ");
                    int input2 = scan.nextInt();scan.nextLine();
                    if(input2 == 1){
                        if(player.potion.isEmpty()){
                            if(player.money<10){
                                System.out.println("You can't buy this potion...");
                            }
                            else{
                                player.potion = "Health Potion";
                                player.money-=10;
                                System.out.println("Health Potion Bought!");
                            }
                        }
                        else{
                            System.out.println("You are already holding a potion!");
                        }
                    }
                    else if (input2 == 2){
                        if(player.potion.isEmpty()){
                            if(player.money<20){
                                System.out.println("You can't buy this potion...");
                                break;
                            }
                            else{
                                player.potion = "Attack Potion";
                                player.money-=20;
                                System.out.println("Attack potion bought");
                            }
                        }
                        else{
                            System.out.println("You are already holding a potion!");
                        }
                    }
                    else{
                        break;
                    }

                }while(true);
                rest();
                break;
            case 2:
                return;
            case 3:
                exit = true;
                return;
            default:
                System.out.println("Invalid input");
                rest();
                break;
        }
        return;
    }
}
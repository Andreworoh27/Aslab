import java.util.Scanner;

public class Main {
    int x;
    Scanner scan = new Scanner(System.in);
    Player player = new Player(0,2,1,1,0,0);

    public Main(){
        menu();
    }
    
    void menu(){
        cls();
        System.out.println("Your money is " + player.getMoney());
        System.out.println("1. Hire Handyman");
        System.out.println("2. Produce Automobile");
        System.out.println("3. Upgrade Production line");
        System.out.println("4. Sell Automobile");
        System.out.println("5. Exit");
        System.out.print(">> ");
        int input = scan.nextInt();scan.nextLine();
        switch (input) {
            case 1:
                cls();
                hire();
                break;
            case 2:
                cls();
                produce();
                break;
            case 3:
                cls();
                upgrade();
                break;
            case 4:
                cls();
                sell();
            case 5:
                System.out.println("Thankyou for playing");
                System.exit(1);
            default:
                System.out.println("Invalid Input");
                break;
        }
        menu();
    }

    void hire(){
        System.out.println("Your money is " + player.getMoney());
        System.out.println("You have " + player.getHandyman() + " handymans");
        int price = player.getHandyman() * 150;
        System.out.println("1. Hire Handyman for " + price);
        System.out.println("2. Back");
        System.out.print(">> ");
        int input = scan.nextInt();scan.nextLine();
        switch (input) {
            case 1:
                if(player.getMoney()<price){
                    System.out.println("You don't have enough money");
                }
                else{
                    player.hire(price);
                }
                break;
            case 2:
                return;
            default:
                System.out.println("Input invalid");
                break;
        }
        System.out.printf("\n\n\n\n");
        hire();
        return;
    }

    void produce(){
        System.out.println("You have "+player.getCar()+" cars");
        System.out.println("You have "+player.getMtr()+" motorcycles");
        System.out.println("1. Produce Cars with Level "+player.getCar_prdct_level() + " production line");
        System.out.println("2. Produce Motorcycles with Level "+player.getMtr_prdct_lvl() + " production line");
        System.out.println("3. Back");
        System.out.print(">> ");
        int input = scan.nextInt();scan.nextLine();
        int produced ;
        switch (input) {
            case 1:
                produced = player.produce_car();
                System.out.println("Produced car : "+produced);
                break;
            case 2:
                produced = player.produce_mtr();
                System.out.println("Produced motorcycles : "+produced);
                break;
            case 3:
                return;
            default:
                System.out.println("Invalid input");
                break;
        }
        System.out.printf("\n\n\n\n");
        produce();
        return;
    }

    void upgrade(){
        int price_car = player.upgrade_price_car(),price_mtr = player.upgrade_price_mtr();
        System.out.println("Your money is "+player.getMoney());
        System.out.println("You have level "+player.getCar_prdct_level()+" car production line");
        System.out.println("You have level "+player.getMtr_prdct_lvl()+" motorcycle production line");
        System.out.println("1. Upgrade Car Production Line for " + price_car);
        System.out.println("2. Upgrade Motorcycle Production line for " + price_mtr);
        System.out.println("3. Back");
        int input = scan.nextInt();scan.nextLine();
        switch (input) {
            case 1:
                if(player.getMoney() < price_car){
                    System.out.println("You don't have enogh money");
                }
                else{
                    player.upgrade_car_lvl(price_car);
                    System.out.println("upgrade successfull...");
                }
                break;
            case 2:
                if(player.getMoney() < price_mtr){
                    System.out.println("You don't have enogh money");
                }
                else{
                    player.upgrade_mtr_lvl(price_mtr);
                    System.out.println("upgrade successfull...");
                }
                break;
            case 3:
                return;
            default:
                System.out.println("Invalid input");
                break;
        }
        System.out.printf("\n\n\n\n");
        upgrade();
        return;
    }

    void sell(){
        System.out.println("Your money is "+player.getMoney());
        System.out.println("You have "+ player.getCar()+" cars");
        System.out.println("You have "+ player.getMtr()+" motorcycles");
        System.out.println("1. Sell cars");
        System.out.println("2. Sell motorcycles");
        System.out.println("3. Back");
        System.out.print(">> ");
        int input = scan.nextInt();scan.nextLine();
        switch (input) {
            case 1:
                System.out.println("Input number of car to sale :");
                int car=scan.nextInt();scan.nextLine();
                if(car>player.getCar()){
                    System.out.println("Invalid car input");
                }
                else if(car == 0){
                    System.out.println("Nothing to sell");
                }
                else if(car>0 && car<=player.getCar()){
                    player.sellcar(car);
                }
                break;
            case 2:
                System.out.println("Input number of motorcycle to sale :");
                int mtr=scan.nextInt();scan.nextLine();
                if(mtr>player.getMtr()){
                    System.out.println("Invalid motorcycle input");
                }
                else if(mtr == 0){
                    System.out.println("Nothing to sell");
                }
                else if(mtr>0 && mtr<=player.getMtr()){
                    player.sellmtr(mtr);
                }
                break;
            case 3:
                return;
            default:
                System.out.println("Invalid input");
                break;
        }
        System.out.printf("\n\n\n\n");
        sell();
        return;
    }

    void cls(){
        System.out.print("\033[H\033[2J");
        System.out.flush();
    }

    public static void main(String[] args){
        new Main();
    }
}

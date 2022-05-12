import java.util.ArrayList;
import java.util.Scanner;

public class Main {
    Scanner scan = new Scanner(System.in);
    ArrayList<Dog> dog = new ArrayList<>();
    Main(){
        menu();
    }

    void menu(){
        cls();
        System.out.println("Welcome to Doge Pet Store");
        System.out.println("=========================");
        System.out.println("1. Insert new dog");
        System.out.println("2. Do some actions to dogs");
        System.out.println("3. View dogs");
        System.out.println("4. Somebody wants to buy a new dog");
        System.out.println("5. Exit");
        System.out.print("choose : ");
        int input=0;
        try {
            input = scan.nextInt();
        } catch (Exception e) {
            System.out.println("invalid input");
        }
        scan.nextLine();
        switch (input) {
            case 1:
                insert();
                break;
            case 2:
                actions();
                break;
            case 3:
                viewdogs();
                break;
            case 4:
                buy();
                break;
            case 5:
                System.out.println("Thank you for visiting to Doge Pet Store...");
                System.exit(1);
                break;
            default:
                break;
        }
        menu();
    }

    void insert(){
        cls();
        System.out.println("Insert New Dog");
        System.out.println("==============");
        String name;
        int price=0;
        int age=0;

        do {
            System.out.print("Dog Name [more than 3 characters] : ");
            name = scan.nextLine();
            if(name.length() > 3){
                break;
            }
        } while (true);
        
        do {
            System.out.print("Dog Price [Price must be a multiple of 100] : ");
            try {
                price = scan.nextInt();
            } catch (Exception e) {
                System.out.println("Invalid input");
                continue;
            }
            scan.nextLine();
            if(price%100 == 0){
                break;
            }
        } while (true);

        do {
            System.out.print("Dog Age [0 - 14] : ");
            try {
                age = scan.nextInt();
            } catch (Exception e) {
                System.out.println("Invalid input");
                continue;
            }
            scan.nextLine();
            if(age>=0 && age<=14){
                break;
            }
        } while (true);
        dog.add(new Dog(name, price, age));
        scan.nextLine();
    }

    void actions(){
        cls();
        System.out.println("What are you going to do with these dogs ?");
        System.out.println("==========================================");
        System.out.println("1. Feed all of them");
        System.out.println("2. Playing with all of them");
        System.out.println("3. Back");
        System.out.print("Choose : ");
        int input = 0;
        try {
            input = scan.nextInt();
        } catch (Exception e) {
            System.out.println("Input invalid");
        }
        scan.nextLine();
        switch (input) {
            case 1:
                feedall();
                break;
            case 2:
                playall();
                break;
            case 3:
                return;
            default:
                break;
        }
        actions();
    }

    void feedall(){
        cls();
        if(checkarraylist()==false){
            return;
        }

        for(int i=0;i<dog.size();i++){
            if (dog.get(i).checkowner() == false && dog.get(i).getStatus()=="Alive"){
                int poison = randomizer(1,11);
                if (poison<=3) {
                    dog.get(i).reduce_health(10);
                    System.out.println(dog.get(i).getName() +" has food poisoning");
                } 
                else {
                    dog.get(i).increase_health(20);
                    System.out.println(dog.get(i).getName() +" likes the food");
                }
            }
            delay(1000);
        }
        System.out.println("Feeding done");
        System.out.println("Press enter to continue...");scan.nextLine();
    }

    void playall(){
        cls();
        if(checkarraylist()==false){
            return;
        }

        for(int i=0;i<dog.size();i++){
            if (dog.get(i).checkowner() == false && dog.get(i).getStatus()=="Alive"){
                int rock = randomizer(1, 11);
                if (rock<=5) {
                    dog.get(i).reduce_health(5);
                    System.out.println(dog.get(i).getName() +" stumbled upon a rock");
                } 
                else {
                    dog.get(i).increase_health(10);
                    System.out.println(dog.get(i).getName() +" has an amazing playing experience");
                }
            }
            delay(1000);
        }
        System.out.println("playtime is over !");
        System.out.println("Press enter to continue...");scan.nextLine();
    }

    void viewdogs(){
        cls();
        System.out.println("View Dogs");
        System.out.println("==========");
        System.out.println("1. View all dogs in PetStore");
        System.out.println("2. View all dogs in History");
        System.out.println("3. back");
        System.out.print("Choose : ");
        int input =0;
        try {
            input=scan.nextInt();
        } catch (Exception e) {
            System.out.println("Invalid Input");
        }
        scan.nextLine();
        switch (input) {
            case 1:
                viewall(1);
                break;
            case 2:
                viewhistory();
                break;
            case 3:
                return;
            default:
                break;
        }
        viewdogs();
    }

    void viewall(int x){
        cls();
        if(checkarraylist()==false){
            return;
        }
        if(x==1) sortdogname();
        else sortdogprice();
        System.out.println("All Dog in PetStore ");
        int idx=1;
        for(int i=0;i<dog.size();i++){
            if(dog.get(i).getStatus()=="Alive" && dog.get(i).checkowner()==false){
                System.out.println("===========================");
                System.out.println(idx+ ". Name     : " +dog.get(i).getName());
                System.out.println("   Price    : $" +dog.get(i).getPrice());
                System.out.println("   Age      : " +dog.get(i).getAge());
                System.out.println("   Health   : " +dog.get(i).getHealth());
                System.out.println("   Status   : " +dog.get(i).getStatus());
                idx++;
            }
        }
        System.out.println("===========================");
        System.out.println("Press enter to continue...");scan.nextLine();
    }

    void viewhistory(){
        cls();
        if(checkarraylist()==false){
            return;
        }
        sortdogname();
        System.out.println("All Dog in History ");
        for(int i=0;i<dog.size();i++){
            System.out.println("===========================");
            System.out.println(i+ ". Name     : " +dog.get(i).getName());
            System.out.println("   Price    : $" +dog.get(i).getPrice());
            System.out.println("   Age      : " +dog.get(i).getAge());
            System.out.println("   Health   : " +dog.get(i).getHealth());
            System.out.println("   Status   : " +dog.get(i).getStatus());
            if(dog.get(i).checkowner()==true){
                System.out.println("  Owner     : "+dog.get(i).getOwnerName()+" - "+dog.get(i).getOwnerEmail());
            }
        }
        System.out.println("===========================");
        System.out.println("Press enter to continue...");scan.nextLine();
    }

    void buy(){
        cls();
        if(checkarraylist()==false){
            return;
        }
        viewall(2);
        System.out.println("Which dog do you want to buy [1 - "+dog.size()+"]: ");
        int input = -1;
        try {
            input=scan.nextInt();
        } catch (Exception e) {
        }
        scan.nextLine();
        input-=1;
        if(!(input>=0 && input < dog.size())){
            System.out.println("Invalid input");
            buy();
        }
        String OwnerName,OwnerEmail;
        do {
            System.out.print("Input your name [Must be more than 1 words] : ");
            OwnerName = scan.nextLine();
            if(OwnerName.contains(" ")){
                break;
            }
        } while (true);

        do {
            System.out.print("Input your email [Must contain '@' and Ends with '.com'] : ");
            OwnerEmail = scan.nextLine();
            if(OwnerEmail.endsWith(".com") && OwnerEmail.contains("@")){
                break;
            }
        } while (true);

        dog.get(input).setOwnerName(OwnerName);
        dog.get(input).setOwnerEmail(OwnerEmail);
        System.out.println("Transaction Success !");
        System.out.println("Press enter to continue...");scan.nextLine();
    }

    // utilities
    boolean checkarraylist(){
        if(dog.isEmpty()){
            System.out.println("=================");
            System.out.printf("\nNo Dogs Available\n\n");
            System.out.println("=================");
            System.out.println("Press enter to continue...");scan.nextLine();
            return false;
        }
        else{
            return true;
        }
    }
    int randomizer(int min,int max){
        return (int)(Math.random()*(max - min) + min);
    }

    void delay(int time){
        try {
            Thread.sleep(time);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    void sortdogname(){
        for(int i = 0; i < dog.size(); i++){
            for(int j = 0; j < dog.size() - 1 - i; j++){
                String name1 = dog.get(j).getName();
                String name2 = dog.get(j+1).getName();
                if(name1.compareTo(name2) > 0){
                    Dog tempdog = dog.get(j+1);
                    dog.set(j+1, dog.get(j));
                    dog.set(j, tempdog);
                }
            }
        }
    }

    void sortdogprice(){
        for(int i = 0; i < dog.size(); i++){
            for(int j = 0; j < dog.size() - 1 - i; j++){
                if(dog.get(j).getPrice() > dog.get(j+1).getPrice()){
                    Dog tempdog = dog.get(j+1);
                    dog.set(j+1, dog.get(j));
                    dog.set(j, tempdog);
                }
            }
        }
    }

    void cls(){
        System.out.print("\033[H\033[2J");
        System.out.flush();
    }

    public static void main(String[] args){
        new Main();
    }
}
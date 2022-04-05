import java.util.ArrayList;
import java.util.Scanner;

public class Main {
    Scanner scan = new Scanner(System.in);
    ArrayList<String> Name = new ArrayList<>();
    ArrayList<Integer> Quantity = new ArrayList<>();
    ArrayList<Integer> Price = new ArrayList<>();
    ArrayList<String> Categories = new ArrayList<>();
    int total = 0;

    public Main(){
        menu();
    }

    void menu(){
        cls();
        System.out.println("|======================|");
        System.out.println("|        JaGMart       |");
        System.out.println("|======================|");
        System.out.println("|  1. Add new product  |");
        System.out.println("|  2. Show all product |");
        System.out.println("|  3. Remove product   |");
        System.out.println("|  4. Edit product     |");
        System.out.println("|  5. Exit             |");
        System.out.println("|======================|");
        System.out.print(">> ");
        int input = scan.nextInt();scan.nextLine();
        System.out.println(input);
        switch (input) {
            case 1:
                addnew();
                total++;
                break;
            case 2:
                showall();
                System.out.println("Press enter to continue...");scan.nextLine();
                break;
            case 3:
                remove();
                total--;
                break;
            case 4:
                edit();
                break;
            case 5:
                System.exit(1);
                break;
            default:
                System.out.println("invalid input");
                menu();
                break;
        }
        menu();
    }

    void addnew(){
        cls();
        String name;
        do{
            System.out.print("Input product name (more than 3 characters) : ");
            name = scan.nextLine();scan.nextLine();
            if(name.length()<=3){
                System.out.println("[!] Name must be more than 3 characters");
            }
        }while(name.length()<=3);
        Name.add(name);

        int quantity;
        do{
            System.out.print("Input product quantity : ");
            quantity = scan.nextInt();scan.nextLine();
            if(quantity<=0){
                System.out.println("[!] Product must be at least 1");
            }
        }while(quantity<=0);
        Quantity.add(quantity);
        
        int price;
        do{
            System.out.print("Input product price : ");
            price = scan.nextInt();scan.nextLine();
            if(price%500 != 0){
                System.out.println("[!] Price must be a multiple of 500");
            }
        }while(price%500 != 0);
        Price.add(price);

        String categories;
        do{
            System.out.print("Input Product categories [Drink | Food] (case sensitive) : ");
            categories = scan.nextLine();scan.nextLine();
            if(categories.equals("Drink")||categories.equals("Food")){
                break;
            }
            else{
                System.out.println("[!] Categories must be Drink or Food");
            }
        }while(true);
        Categories.add(categories);
        return;
    }

    void showall(){
        cls();
        if(Name.isEmpty()){
            System.out.println("There is no product");
            System.out.println("Press enter to continue...");scan.nextLine();
            return;
        }
        System.out.println("========================================================================");
        System.out.println("|| No || Name            || Quantity || Price      || Categories      ||");
        System.out.println("========================================================================");
        for(int i=0;i<total;i++){
            System.out.printf("|| %-2d || %-15s || %-8d || %-10s || %-15s ||\n",i+1,Name.get(i),Quantity.get(i),Price.get(i),Categories.get(i));
        }
        System.out.println("========================================================================");
        return;
    }

    void remove(){
        cls();
        if(Name.isEmpty()){
            System.out.println("There is no product");
            System.out.println("Press enter to continue...");scan.nextLine();
            return;
        }
        showall();
        System.out.println("Input product Number to be removed [1 - "+total+" ] (type '0' to go back) :");
        int input = scan.nextInt();scan.nextLine();
        if(input == 0){
            return;
        }
        else if (input > total || total < 0){
            System.out.println("invalid input");
            remove();
            return;
        }
        else{
            Name.remove(input-1);
            Quantity.remove(input-1);
            Price.remove(input-1);
            Categories.remove(input-1);
            System.out.println("Successfully removed product");
            System.out.println("Press enter to continue...");
            return;
        }
    }

    void edit(){
        cls();
        if(Name.isEmpty()){
            System.out.println("There is no product");
            System.out.println("Press enter to continue...");scan.nextLine();
            return;
        }
        showall();
        System.out.println("Input product number to be edited [1 - "+total+" ] (type 0 to go back) : ");
        int input = scan.nextInt();scan.nextLine();
        if(input == 0){
            return;
        }
        else if (input > total || total < 0){
            System.out.println("invalid input");
            edit();
            return;
        }
        else{
            String name;
            do{
                System.out.print("Input product name (more than 3 characters) : ");
                name = scan.nextLine();scan.nextLine();
                if(name.length()<=3){
                    System.out.println("[!] Name must be more than 3 characters");
                }
            }while(name.length()<=3);
            Name.set(input-1, name);

            int quantity;
            do{
                System.out.print("Input product quantity : ");
                quantity = scan.nextInt();scan.nextLine();
                if(quantity<=0){
                    System.out.println("[!] Product must be at least 1");
                }
            }while(quantity<=0);
            Quantity.set(input-1, quantity);
            
            int price;
            do{
                System.out.print("Input product price : ");
                price = scan.nextInt();scan.nextLine();
                if(price%500 != 0){
                    System.out.println("[!] Price must be a multiple of 500");
                }
            }while(price%500 != 0);
            Price.set(input-1,price);

            String categories;
            do{
                System.out.print("Input Product categories [Drink | Food] (case sensitive) : ");
                categories = scan.nextLine();scan.nextLine();
                if(categories.equals("Drink")||categories.equals("Food")){
                    break;
                }
                else{
                    System.out.println("[!] Categories must be Drink or Food");
                }
            }while(true);
            Categories.set(input-1,categories);
            System.out.println("Successfully edited product");
            System.out.println("Press enter to continue...");scan.nextLine();
            return;
        }
    }

    static void cls(){
        System.out.print("\033[H\033[2J");
        System.out.flush();
    }

    public static void main(String[] args){
        new Main();
    }
}

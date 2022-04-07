import java.util.Scanner;

public class Main {
    Scanner scan = new Scanner(System.in);
    Admin admin = new Admin();
    User user = new User();

    Main(){
        menu();
    }

    void menu(){
        cls();
        System.out.println("gramENdia");
        System.out.println("");
        System.out.println("Login as");
        System.out.println("1. User");
        System.out.println("2. Admin");
        System.out.println("3. Exit");
        System.out.print(">> ");
        int input=0;
        try {
            input = scan.nextInt();
        } catch (Exception e) {
            System.out.println("Invalid input");
        }
        scan.nextLine();
        switch (input) {
            case 1:
                cls();
                usermenu();
                break;
            case 2:
                cls();
                adminmenu();
                break;
            case 3:
                System.exit(1);
            default:
                System.out.println("Invalid input");
                break;
        }
        cls();
        menu();
    }

    // User
    void usermenu(){
        System.out.println("Welcome user,");
        System.out.println("1. Add Book to Cart");
        System.out.println("2. Show Book list");
        System.out.println("3. Show Cart");
        System.out.println("4. Exit");
        System.out.print(">> ");
        int input=0;
        try {
            input = scan.nextInt();
        } catch (Exception e) {
            System.out.println("Invalid input");
        }
        scan.nextLine();
        switch (input) {
            case 1:
                cls();
                addbook();
                break;
            case 2:
                cls();
                showbook();
                break;
            case 3:
                cls();
                showcart();
                break;
            case 4:
                return;
            default:
                System.out.println("Invalid input");
                break;
        }
        cls();
        usermenu();
    }

    void addbook(){
        if(!admin.checklist()){
            System.out.println("There's No Book!");
            System.out.println("Press Enter to Continue!"); scan.nextLine();
            return;
        }
        showbook();
        System.out.printf("\n\n");

        int idx= -1;
        do {
            if(admin.getTotal_book()==1){
                System.out.println("Choose The Book Number [ 1 ] : ");
            }
            else{
                System.out.println("Choose The Book Number [ 1 - "+ admin.getTotal_book() + " ] : ");
            }
            idx = scan.nextInt();
            if(idx-1>=0 && idx-1 <admin.getTotal_book()){
                idx -=1;
                break;
            }
            scan.nextLine();
        } while (true);
        
        Integer quantity=0;
        do {
            System.out.println("Input Number of Books Do You Want to Add [ 1 - " + admin.getBook_stock(idx) + " ] : ");
            quantity = scan.nextInt();
            if(quantity>0 && quantity <= admin.getBook_stock(idx)){
                break;
            }
            scan.nextLine();
        } while (true);
        System.out.println(idx);
        user.add(idx,quantity);
        user.update(idx,quantity);
        System.out.println("Cart is Updated!");
        System.out.println("Press Enter to COntinue!");
        return;
    }

    void showcart(){
        if (!user.checklist()){
            System.out.println("There's No Book!");
            System.out.println("Press Enter to Continue!"); scan.nextLine();
            return;
        }
        System.out.println("Cart");
        System.out.println("=====================================================================");
        System.out.println("| No. | Name                   | Genre      | Price        | Stock  |");
        System.out.println("=====================================================================");
        user.sort();
        for(int i=0;i<user.getTotal_book_user();i++){
            System.out.printf("| %-3d | %-22s | %-10s | %-12d | %-6d |\n",i+1,user.getBook_name_user(i),user.getBook_genre_user(i),user.getBook_price_user(i),user.getBook_quantity_user(i));
        }
        System.out.println("=====================================================================");
        System.out.println("Total Price : " + user.totalprice());
        System.out.println("Total Quantity : " + user.totalquantitiy());
        System.out.println("Press Enter to Continue!");
        System.out.print("\n\n");
        System.out.println("1. Checkout");
        System.out.println("2. Exit");
        System.out.print(">> ");
        int input = 0;
        try {
            input = scan.nextInt();
        } catch (Exception e) {
            System.out.println("Invalid input");
        }
        scan.nextLine();
        switch (input) {
            case 1:
                cls();
                checkout();
                return;
            case 2:
                return;
            default:
                System.out.println("Input invalid");
                break;
        }
        cls();
        showcart();
        return;
    }

    void checkout(){
        int totalprice = user.totalprice();
        if(user.totalquantitiy() > 20 && user.totalquantitiy() <=50){
            totalprice *= 0.9;
            System.out.println("Total Price : "+totalprice);
        }
        if(user.totalquantitiy() > 50 && user.totalquantitiy() <=10){
            totalprice *= 0.8;
            System.out.println("Total Price : "+totalprice);
        }
        if(user.totalquantitiy() > 100){
            totalprice *= 0.6;
            System.out.println("Total Price : "+totalprice);
        }
        user.reset();
        System.out.println("Successfully Checkout!");
        System.out.println("Press Enter to Continue!");scan.nextLine();
    }

    // Admin
    void adminmenu(){
        System.out.println("Welcome Admin,");
        System.out.println("1. Insert book");
        System.out.println("2. Show book");
        System.out.println("3. exit");
        int input=0;
        try {
            input = scan.nextInt();
        } catch (Exception e) {
            System.out.println("Invalid input");
        }
        scan.nextLine();
        switch (input) {
            case 1:
                cls();
                insertbook();
                break;
            case 2:
                cls();
                showbook();
                break;

            case 3:
                return;
            default:
                System.out.println("Invalid input");
                break;
        }
        cls();
        adminmenu();
    }

    void insertbook(){
        String name;
        do {
            System.out.print("Input Book's Name [ More than 1 words ] : ");
            name = scan.nextLine();
            if(name.contains(" ")){
                break;
            }
            scan.nextLine();
        } while (true);

        String genre;
        do {
            System.out.print("Input Book's genre [ Romance | Action | Fantasy ] : ");
            genre = scan.nextLine();
            if(genre.equals("Romance") || genre.equals("Action") || genre.equals("Fantasy")){
                break;
            }
            scan.nextLine();
        } while (true);

        Integer price;
        do{
            System.out.print("Input Book's Price [ more than 100.000 ] : ");
            price = scan.nextInt();scan.nextLine();
            if(price > 100000){
                break;
            }
        }while(true);

        Integer stock;
        do {
            System.out.print("Input Book's Stock [ More than 0 ] : ");
            stock = scan.nextInt();scan.nextLine();
            if(stock > 0){
                break;
            }
        } while (true);
        admin.AddBookName(name);
        admin.AddBookGenre(genre);
        admin.AddBookPrice(price);
        admin.AddBookStock(stock);
        admin.AddTotalBook();
        return;
    }

    void showbook(){
        if (!admin.checklist()){
            System.out.println("There's No Book!");
            System.out.println("Press Enter to Continue!"); scan.nextLine();
            return;
        }
        System.out.println("List of book");
        System.out.println("=====================================================================");
        System.out.println("| No. | Name                   | Genre      | Price        | Stock  |");
        System.out.println("=====================================================================");
        admin.sort();
        for(int i=0;i<admin.getTotal_book();i++){
            System.out.printf("| %-3d | %-22s | %-10s | %-12d | %-6d |\n",i+1,admin.getBook_name(i),admin.getBook_genre(i),admin.getBook_price(i),admin.getBook_stock(i));
        }
        System.out.println("=====================================================================");
        System.out.println("Press enter to continue...");scan.nextLine();
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

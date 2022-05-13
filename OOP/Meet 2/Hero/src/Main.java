import java.util.ArrayList;
import java.util.Scanner;
import Hero.*;
import Item.*;

public class Main {
    Scanner scan = new Scanner(System.in);
    ArrayList<Weapon> weapons = new ArrayList<>();
    ArrayList<Armor> armors = new ArrayList<>();
    ArrayList<Hero> heros = new ArrayList<>();

    Main(){
         // weapon 
         weapons.add(new Weapon("Harbringer Of Down", 0, 0, 30, 5, 15, 0));
         weapons.add(new Weapon("Staff Of Homeless", 20, 0, 35, 0, 25, 0));
         weapons.add(new Weapon("Blood Of Despair", -20, -5, 50, 0, 35, 0));
         weapons.add(new Weapon("Excalibur", 30, 30, 30, 30, 30, 30));
         weapons.add(new Weapon("Blade", 0, 0, 10, 0, 10, 0));
 
         // armor
         armors.add(new Armor("Armor Of Infinite", 30, 20, 0, 35, 0, 15));
         armors.add(new Armor("Guard Of Dishonor", 20, 25, 0, 45, 0, 25));
         armors.add(new Armor("Diamond Armor", 0, 0, 0, 50, 0, 50));
         armors.add(new Armor("Holy Armor", 20, 20, 20, 20, 0, 20));
         armors.add(new Armor("Leather Cuirass", 0, 0, 0, 10, 0, 10));
        menu();
    }

    void menu(){
        cls();
        System.out.println("Design Your Hero !!!");
        System.out.println("====================");
        System.out.println("1. Create your own hero");
        System.out.println("2. View created Hero");
        System.out.println("3. Delete created Hero");
        System.out.println("4. Exit");
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
                create();
                break;
            case 2:
                viewhero();
                break;
            case 3:
                deletehero();
                break;
            case 4:
                System.exit(1);
            default:
                break;
        }
        menu();
    }

    void create(){
        cls();
        String name,gender;
        do {
            System.out.print("Input Hero Name [min 5 characters | unique | Contains both letter and number | contain capitalize letter] : ");
            name = scan.nextLine();
            boolean valid = namevalidation(name);
            if(valid == true){
                break;
            }
        } while (true);

        do {
            System.out.print("Input Hero Gender [Male | Female] : ");
            gender = scan.nextLine();
            if(gender.compareToIgnoreCase("male")==0 || gender.compareToIgnoreCase("female")==0){
                break;
            }
        } while (true);
        heros.add(new Hero(name, gender));

        System.out.println("=============================================================");
        System.out.println("|No.|Armor Name          |HP   |MP   |STR  |VIT  |BONUS ATK |");
        System.out.println("=============================================================");
        for (int i=0;i<armors.size();i++){
            System.out.printf("|%-2d.|%-20s|+%-4d|+%-4d|+%-4d|+%-4d|+%-9d|\n",i+1,armors.get(i).name,armors.get(i).HP,armors.get(i).MP,armors.get(i).Strength,armors.get(i).Vitality,armors.get(i).BAttack);
        }
        System.out.println("=============================================================");

        System.out.println("Choose the armor ");
        int armorinput = 0;
        do {
            System.out.print(">> ");
            try {
                armorinput = scan.nextInt();
            } catch (Exception e) {
                System.out.println("Invalid Input");
            }
            scan.nextLine();
            if (armorinput >=1 && armorinput<=5){
                armorinput-=1;
                break;
            }
        } while (true);
        
        System.out.println("=============================================================");
        System.out.println("|No.|Weapon Name         |HP   |MP   |STR  |VIT  |BONUS DEF |");
        System.out.println("=============================================================");
        for (int i=0;i<weapons.size();i++){
            System.out.printf("|%-2d.|%-20s|+%-4d|+%-4d|+%-4d|+%-4d|+%-9d|\n",i+1,weapons.get(i).name,weapons.get(i).HP,weapons.get(i).MP,weapons.get(i).Strength,weapons.get(i).Vitality,weapons.get(i).BDefense);
        }
        System.out.println("=============================================================");

        System.out.println("Choose the weapon ");
        int weaponinput = 0;
        do {
            System.out.print(">> ");
            try {
                weaponinput = scan.nextInt();
            } catch (Exception e) {
                System.out.println("Invalid Input");
            }
            scan.nextLine();
            if (weaponinput >=1 && weaponinput<=5){
                weaponinput-=1;
                break;
            }
        } while (true);
        System.out.println(heros.size());
        heros.get((heros.size()-1)).addstatus(armors.get(armorinput), weapons.get(weaponinput));
        System.out.println("Create success !");
        delay(1500);
    }

    void viewhero(){
        cls();
        if(heros.isEmpty()){
            System.out.println("You haven't created your hero!");
            delay(1500);
            return;
        }
        System.out.println("List hero");
        System.out.println("=========");
        for(int i=0;i<heros.size();i++){
            System.out.println((i+1) + " ."+heros.get(i).getName());
        }
        System.out.println("[0 to back] >> ");
        int input = 0;
        try {
            input = scan.nextInt();
        } catch (Exception e) {
            System.out.println("Invalid Input");
        }
        scan.nextLine();
        if(input == 0){
            return;
        }
        else{
            if(input>=1 && input<=heros.size()){
                input-=1;
                showherodetail(input);
            }
        }
    }

    void deletehero(){
        cls();
        if(heros.isEmpty()){
            System.out.println("You haven't created your hero!");
            delay(1500);
            return;
        }
        System.out.println("List hero");
        System.out.println("=========");
        for(int i=0;i<heros.size();i++){
            System.out.println((i+1) + " ."+heros.get(i).getName());
        }
        System.out.println(">> ");
        int input = 0;
        try {
            input = scan.nextInt();
        } catch (Exception e) {
            System.out.println("Invalid Input");
        }
        scan.nextLine();
        if(input == 0){
            return;
        }
        else{
            if(input>=1 && input<=heros.size()){
                input-=1;
                heros.remove(input);
                System.out.println("Delete success !");
                System.out.println("Press enter to continue...");scan.nextLine();
            }
        }
    }

    // utilities
    void showherodetail(int idx){
        System.out.println("Name : "+heros.get(idx).getName());
        System.out.println("Gender : "+heros.get(idx).getGender());
        System.out.println("=========================");
        System.out.println("|Status     |Value      |");
        System.out.println("=========================");
        System.out.printf("|HP         |%-11d|\n",heros.get(idx).HP);
        System.out.printf("|MP         |%-11d|\n",heros.get(idx).MP);
        System.out.printf("|ATK        |%-5d(+%-3d)|\n",heros.get(idx).getATK(),heros.get(idx).BAttack);
        System.out.printf("|DEF        |%-5d(+%-3d)|\n",heros.get(idx).getDEF(),heros.get(idx).BDefense);
        System.out.println("=========================");
        System.out.println("Weapon : "+heros.get(idx).getWeapon());
        System.out.println("Armor : "+heros.get(idx).getArmor());
        System.out.println("Press enter to continue...");scan.nextLine();
        return;
    }

    void cls(){
        System.out.print("\033[H\033[2J");
        System.out.flush();
    }

    void delay(int time){
        try {
            Thread.sleep(time);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    boolean namevalidation(String name){
        if (name.length()<5){
            return false;
        }

        for(int i=0;i< heros.size();i++){
            if(heros.get(i).getName().compareTo(name)==0){
                return false;
            }
        }

        boolean letter=false, number=false, capitalize=false;
        
        for (int j=0;j<name.length();j++){
            if(name.charAt(j)>='a'&& name.charAt(j)<='z'){
                letter = true;
            }
            else if(name.charAt(j)>='0' && name.charAt(j)<='9'){
                number = true;
            }
            else if(name.charAt(j)>='A' && name.charAt(j)<='Z'){
                capitalize = true;
            }
        }

        if(letter == false || capitalize == false || number == false){
            return false;
        }
        return true;
    }

    void generate(){
        // weapon 
        weapons.add(new Weapon("Harbringer Of Down", 0, 0, 30, 5, 15, 0));
        weapons.add(new Weapon("Staff Of Homeless", 20, 0, 35, 0, 25, 0));
        weapons.add(new Weapon("Blood Of Despair", -20, -5, 50, 0, 35, 0));
        weapons.add(new Weapon("Excalibur", 30, 30, 30, 30, 0, 30));
        weapons.add(new Weapon("Blade", 0, 0, 10, 0, 10, 0));

        // armor
        armors.add(new Armor("Armor Of Infinite", 30, 20, 0, 35, 0, 15));
        armors.add(new Armor("Guard Of Dishonor", 20, 25, 0, 45, 0, 25));
        armors.add(new Armor("Diamond Armor", 0, 0, 0, 50, 0, 50));
        armors.add(new Armor("Holy Armor", 20, 20, 20, 20, 0, 20));
        armors.add(new Armor("Leather Cuirass", 0, 0, 0, 10, 0, 10));
    }

    public static void main(String[] args){
        new Main();
    }
}

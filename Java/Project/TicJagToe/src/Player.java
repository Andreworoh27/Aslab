import java.util.Scanner;

import javax.lang.model.element.Name;

public class Player {
    private String name = "";
    private String password = "";
    Player(){
        // Scanner scan = new Scanner(System.in);
        // name = scan.nextLine();
        // System.out.println(name);
        // System.out.println(name.matches("[A-Za-z0-9]+"));
        // System.out.println(name.matches("[0-9]+"));
    }

    // setter
    public void setName(String name) {
        this.name = name;
    }
    public void setPassword(String password) {
        this.password = password;
    }
}

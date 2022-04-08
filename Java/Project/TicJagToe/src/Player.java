import java.util.Scanner;

import javax.lang.model.element.Name;

public class Player {
    private String name = "";
    private String password = "";
    private int score = 0;
    Player(){}

    // setter
    public void setName(String name) {
        this.name = name;
    }
    public void setPassword(String password) {
        this.password = password;
    }
    public void setScore(int score) {
        this.score = score;
    }

    // getter
    public String getName() {
        return name;
    }
    public String getPassword() {
        return password;
    }
    public int getScore() {
        return score;
    }
}

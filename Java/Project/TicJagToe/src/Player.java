import java.util.ArrayList;
public class Player {
    private ArrayList <String> name = new ArrayList<>();
    private ArrayList <String> password = new ArrayList<>();
    private ArrayList <Integer> score = new ArrayList<>();
    Player(){}

    // setter
    public void setName(String name,int i) {
        this.name.set(i, name);
    }
    public void setPassword(String password,int i) {
        this.password.set(i, password);
    }
    public void setScore(int score,int i) {
        if(score <0){
            score = 0;
        }
        this.score.set(i, score);
    }

    // getter
    public String getName(int i) {
        return name.get(i);
    }
    public String getPassword(int i) {
        return password.get(i);
    }
    public int getScore(int i) {
        return score.get(i);
    }

    // add
    public void addName(String name) {
        this.name.add(name);
    }
    public void addPassword(String password) {
        this.password.add(password);
    }
    public void addScore(int score) {
        this.score.add(score);
    }
}

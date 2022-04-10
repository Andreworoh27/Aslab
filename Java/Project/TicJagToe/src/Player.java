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

    void quicksort(int left,int right){
        if (left > right){
            return;
        }
        Integer pivot=score.get(right);
        int idx=left;
        for (int i=left;i<right;i++){
            if (score.get(i)>=pivot){
                String tempString;
                Integer tempInteger;
                // name
                tempString = name.get(i);
                name.set(i, name.get(idx));
                name.set(idx, tempString);

                // score
                tempInteger = score.get(i);
                score.set(i, score.get(idx));
                score.set(idx, tempInteger);

                // passworrd
                tempString = password.get(i);
                password.set(i, password.get(idx));
                password.set(idx, tempString);

                idx+=1;
            }
        }
        String tempString;
        Integer tempInteger;
        // name
        tempString = name.get(idx);
        name.set(idx, name.get(right));
        name.set(right, tempString);

        // score
        tempInteger = score.get(idx);
        score.set(idx, score.get(right));
        score.set(right, tempInteger);

        // passworrd
        tempString = password.get(idx);
        password.set(idx, password.get(right));
        password.set(right, tempString);
        quicksort(left,(idx-1));
        quicksort((idx+1),right);
    }
}

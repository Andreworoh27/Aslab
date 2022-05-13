package Item;
import Hero.*;

public class Armor extends InitialStatus{
    public Armor(String name, int hp, int mp,int Strength,int Vitality,int BAttack,int BDefense){
        this.name = name;
        this.HP = hp;
        this.MP = mp;
        this.Strength = Strength;
        this.Vitality = Vitality;
        this.BAttack = BAttack;
        this.BDefense = BDefense;
    }
}

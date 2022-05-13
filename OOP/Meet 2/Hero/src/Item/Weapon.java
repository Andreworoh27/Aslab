package Item;
import Hero.*;

public class Weapon extends InitialStatus{
    public Weapon(String name, int hp, int mp,int Strength,int Vitality,int BAttack,int BDefense){
        this.name = name;
        this.HP = hp;
        this.MP = mp;
        this.Strength = Strength;
        this.Vitality = Vitality;
        this.BAttack = BAttack;
        this.BDefense = BDefense;
    }
    
}

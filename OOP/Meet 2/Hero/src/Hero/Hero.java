package Hero;
import Item.*;
public class Hero extends InitialStatus{
    private String Weapon,Armor,Gender;
    private int ATK,DEF;
    public Hero(String name,String Gender){
        this.name = name;
        this.Gender = Gender;
        this.HP = 100;
        this.MP = 100;
        this.Strength = 10;
        this.Vitality = 10;
    }

    // getter
    public int getATK() {
        return ATK;
    }
    public int getDEF() {
        return DEF;
    }
    public String getName() {
        return this.name;
    }
    public String getGender() {
        return Gender;
    }
    public String getArmor() {
        return Armor;
    }
    public String getWeapon() {
        return Weapon;
    }

    public void addstatus(Armor armor, Weapon weapon){
        this.Weapon = weapon.name;
        this.Armor = armor.name;
        this.HP+= armor.HP + weapon.HP;
        this.MP+= armor.MP + weapon.MP;
        this.ATK = (this.Strength + weapon.Strength + armor.Strength)/2;
        this.DEF+= (this.Vitality + weapon.Vitality + armor.Vitality)/2;
        this.BDefense+= armor.BDefense + weapon.BDefense;
        this.BAttack+= armor.BAttack + weapon.BAttack;
    }
}
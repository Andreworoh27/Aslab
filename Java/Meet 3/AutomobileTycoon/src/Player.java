public class Player {
    private int money,handyman,car_prdct_level,mtr_prdct_lvl,car,mtr;
    private int upgrade_price_car,upgrade_price_mtr;
    Player(int money,int handyman,int car_prdct_level,int mtr_prdct_lvl,int car,int mtr){
        this.money = money;
        this.handyman = handyman;
        this.car_prdct_level = car_prdct_level;
        this.mtr_prdct_lvl = mtr_prdct_lvl;
        this.car = car;
        this.mtr = mtr;
    }

    // getter
    public int getMoney() {
        return money;
    }
    public int getHandyman() {
        return handyman;
    }
    public int getCar_prdct_level() {
        return car_prdct_level;
    }
    public int getMtr_prdct_lvl() {
        return mtr_prdct_lvl;
    }
    public int getCar() {
        return car;
    }
    public int getMtr() {
        return mtr;
    }

    void hire(int price){
        this.money-=price;
        this.handyman += 1;
    }

    int produce_car(){
        int produce = this.car_prdct_level * this.handyman * 100;
        this.car += produce;
        return produce;
    }

    int produce_mtr(){
        int produce = this.mtr_prdct_lvl * this.handyman * 100;
        this.mtr += produce;
        return produce;
    }

    int upgrade_price_car(){
        int price;
        if(this.car_prdct_level==1){
            this.upgrade_price_car = 200;
            return price = 200;
        }
        else{
            price = 250 + upgrade_price_car;
            this.upgrade_price_car = price;
            return price;
        }
    }

    int upgrade_price_mtr(){
        int price;
        if(this.mtr_prdct_lvl==1){
            upgrade_price_mtr = 200;
            return price = 200;
        }
        else{
            price = 250 + upgrade_price_mtr;
            this.upgrade_price_mtr = price;
            return price;
        }
    }

    void upgrade_car_lvl(int price){
        this.money-=price;
        this.car_prdct_level += 1;
    }

    void upgrade_mtr_lvl(int price){
        this.money-=price;
        this.mtr_prdct_lvl += 1;
    }

    void sellcar(int amount){
        car-=amount;
        money+=amount*10;
    }

    void sellmtr(int amount){
        mtr-=amount;
        money+=amount*10;
    }
}

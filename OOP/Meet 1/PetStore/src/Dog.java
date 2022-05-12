public class Dog {
    private String name;
    private String status;
    private String OwnerName="";
    private String OwnerEmail="";
    private int health,price,age;

    Dog(String name,int price,int age){
        this.name = name;
        this.price = price;
        health = 50;
        this.age = age;
        status = "Alive";
        System.out.println("==========================");
        System.out.println("        Dog Detail        ");
        System.out.println("==========================");
        System.out.println("Name    : "+ this.name);
        System.out.println("Price   : $"+ this.price);
        System.out.println("Age     : "+ this.age);
        System.out.println("Health  : "+ this.health);
        System.out.println("Status  : "+ this.status);
        System.out.println("==========================");
        System.out.println("Press enter to Continue...");
    }

    // getter
    public String getStatus() {
        return status;
    }
    public String getName() {
        return name;
    }
    public int getHealth() {
        return health;
    }
    public int getPrice() {
        return price;
    }
    public int getAge() {
        return age;
    }
    public String getOwnerName() {
        return OwnerName;
    }
    public String getOwnerEmail() {
        return OwnerEmail;
    }

    // setter 
    public void setStatus(String status) {
        this.status = status;
    }
    public void setOwnerName(String ownerName) {
        OwnerName = ownerName;
    }
    public void setOwnerEmail(String ownerEmail) {
        OwnerEmail = ownerEmail;
    }

    public boolean checkowner(){
        return OwnerName.isBlank() ? false : true ;
    }
    public void reduce_health(int health){
        if(this.health-health <=0){
            setStatus("Dead");
            this.health = 0;
        }
        else this.health-=health;
    }

    public void increase_health(int health){
        if(this.health+health >=100){
            this.health = 100;
        }
        else this.health+=health;
    }
    
}

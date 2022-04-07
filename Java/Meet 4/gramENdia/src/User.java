import java.util.ArrayList;

public class User {
    Admin admin = new Admin();
    private int total_book_user=0;
    private ArrayList<String> book_name_user = new ArrayList<>();
    private ArrayList <String> book_genre_user = new ArrayList<>();
    private ArrayList <Integer> book_price_user = new ArrayList<>();
    private ArrayList <Integer> book_quantity_user = new ArrayList<>();

    private void AddTotalBook(){
        total_book_user+=1;
    }

    private void AddBookName(String book_name){
        this.book_name_user.add(book_name);
    }

    private void AddBookGenre(String book_genre){
        this.book_genre_user.add(book_genre);
    }

    private void AddBookPrice(Integer book_price){
        this.book_price_user.add(book_price);
    }

    private void AddBookQuantity(Integer book_quantity){
        this.book_quantity_user.add(book_quantity);
    }

    // getter
    public int getTotal_book_user() {
        return total_book_user;
    }
    public String getBook_name_user(int i) {
        return book_name_user.get(i);
    }
    public String getBook_genre_user(int i) {
        return book_genre_user.get(i);
    }
    public Integer getBook_price_user(int i) {
        return book_price_user.get(i);
    }
    public Integer getBook_quantity_user(int i) {
        return book_quantity_user.get(i);
    }

    boolean checklist(){
        if(book_name_user.size()>0){
            return true;
        }
        return false;
    }

    void sort(){
        for (int i=0;i<total_book_user-1;i++){
            for (int j=0;j<total_book_user-1-i;j++){
                if(book_name_user.get(j).compareTo(book_name_user.get(j+1)) > 0){
                    String temp;
                    Integer tmp;
                    // name
                    temp = book_name_user.get(j+1);
                    book_name_user.set(j+1, book_name_user.get(j));
                    book_name_user.set(j, temp);

                    // genre
                    temp = book_genre_user.get(j+1);
                    book_genre_user.set(j+1, book_genre_user.get(j));
                    book_genre_user.set(j, temp);

                    // price
                    tmp = book_price_user.get(j+1);
                    book_price_user.set(j+1, book_price_user.get(j));
                    book_price_user.set(j, tmp);

                    // stock
                    tmp = book_quantity_user.get(j+1);
                    book_quantity_user.set(j+1, book_quantity_user.get(j));
                    book_quantity_user.set(j, tmp);

                }
            }
        }
    }

    void add(int i,Integer quantity){
        String book_name = admin.getBook_name(i);
        AddBookName(book_name);

        String book_genre = admin.getBook_genre(i);
        AddBookGenre(book_genre);

        Integer book_quantity = quantity;
        AddBookQuantity(book_quantity);

        Integer book_price = admin.getBook_price(i);
        AddBookPrice(book_price);
        
        AddTotalBook();
    }

    int totalquantitiy(){
        int sum=0;
        for(int i=0;i<total_book_user;i++){
            sum+= getBook_quantity_user(i);
        }
        return sum;
    }

    int totalprice(){
        int sumprice=0;
        int sumquantity = totalquantitiy();
        for(int i=0;i<total_book_user;i++){
            sumprice += getBook_price_user(i);
        }
        return sumprice * sumquantity;
    }

    void reset(){
        for(int i=0;i<total_book_user;i++){
            book_name_user.remove(i);
            book_genre_user.remove(i);
            book_price_user.remove(i);
            book_quantity_user.remove(i);
        }
    }

    void update(int i,Integer quanitity){
        Admin.setStock_book(i,quanitity);
    }
}

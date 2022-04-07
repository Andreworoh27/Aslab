import java.util.ArrayList;

public class Admin {
    // book arraylist
    private static int total_book = 0;
    private static ArrayList<String> book_name = new ArrayList<>();
    private static ArrayList <String> book_genre = new ArrayList<>();
    private static ArrayList <Integer> book_price = new ArrayList<>();
    private static ArrayList <Integer> book_stock = new ArrayList<>();

    static void AddTotalBook(){
        total_book+=1;
    }
    static void AddBookName(String name){
        book_name.add(name);
    }

    static void AddBookGenre(String genre){
        book_genre.add(genre);
    }

    static void AddBookPrice(Integer price){
        book_price.add(price);
    }

    static void AddBookStock(Integer stock){
        book_stock.add(stock);
    }

    // getter
    public static int getTotal_book() {
        return total_book;
    }
    public static String getBook_name(int i) {
        return book_name.get(i);
    }
    public static String getBook_genre(int i) {
        return book_genre.get(i);
    }
    public static Integer getBook_price(int i) {
        return book_price.get(i);
    }
    public static Integer getBook_stock(int i) {
        return book_stock.get(i);
    }

    // setter
    public static void setStock_book(int i,Integer quantity) {
        Integer book = (Admin.getBook_stock(i)) - quantity;
        if(book<=0){
            delete_book(i);
        }
        else{
            Admin.book_stock.set(i, book);
        }
    }


    static boolean checklist(){
        if(book_name.size()>0){
            return true;
        }
        return false;
    }

    static void sort(){
        for (int i=0;i<total_book-1;i++){
            for (int j=0;j<total_book-1-i;j++){
                if(book_name.get(j).compareTo(book_name.get(j+1)) > 0){
                    String temp;
                    Integer tmp;
                    // name
                    temp = book_name.get(j+1);
                    book_name.set(j+1, book_name.get(j));
                    book_name.set(j, temp);

                    // genre
                    temp = book_genre.get(j+1);
                    book_genre.set(j+1, book_genre.get(j));
                    book_genre.set(j, temp);

                    // price
                    tmp = book_price.get(j+1);
                    book_price.set(j+1, book_price.get(j));
                    book_price.set(j, tmp);

                    // stock
                    tmp = book_stock.get(j+1);
                    book_stock.set(j+1, book_stock.get(j));
                    book_stock.set(j, tmp);

                }
            }
        }
    }

    static void delete_book(int i){
        book_name.remove(i);
        book_genre.remove(i);
        book_price.remove(i);
        book_stock.remove(i);
        total_book -=1;
    }
}

public class DictionaryTest{

   public static void main(String[] args){
      String v;
      Dictionary T = new Dictionary();
      T.insert("1","a");
      T.insert("2","b");
      T.insert("3","c");
      T.insert("4","d");
      T.insert("5","e");
      T.insert("6","f");
      T.insert("7","g");
      System.out.println(T);

      v = T.lookup("1");
      System.out.println("key=1 "+(v==null?"not found":("value="+v)));
      v = T.lookup("3");
      System.out.println("key=3 "+(v==null?"not found":("value="+v)));
      v = T.lookup("7");
      System.out.println("key=7 "+(v==null?"not found":("value="+v)));
      v = T.lookup("8");
      System.out.println("key=8 "+(v==null?"not found":("value="+v)));
      System.out.println();
	  
	  

      // A.insert("2","f");  // causes KeyCollisionException

      T.delete("1");
	  System.out.println(T);
      T.delete("3");
	  System.out.println(T);
      //T.delete("7");
      //System.out.println(T);

      // A.delete("8");  // causes KeyNotFoundException

      System.out.println(T.isEmpty());
      System.out.println(T.size());
      T.makeEmpty();
      System.out.println(T.isEmpty());
      System.out.println(T);

   }
}
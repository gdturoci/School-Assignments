//Galen Turoci
//gturoci
//Class CMPS 12B
//February 20th, 2018
//This program was used to test various functions in the Queue ADT before implementing them
//into the Queue ADT.
//QueueTest.java

public class QueueTest {
	
	public static void main(String[] args) {
        Queue QT = new Queue();
		
		System.out.println(QT.isEmpty());
		
		System.out.println(QT.length());
		
		//t = QT.dequeue(); - throws "QueueEmptyException"
		
		QT.enqueue("1");
		System.out.println(QT.peek());
		
		QT.enqueue("2");
		System.out.println(QT.peek());
		
		QT.enqueue("3");
		System.out.println(QT.peek());
		
		QT.enqueue("t4");
		System.out.println(QT);
        //Everytime QT.peek is called it prints the same Object, as it should since peek() returns the head.
		
		System.out.println(QT.isEmpty());
		
		System.out.println(QT.length());
        
		System.out.println(QT.dequeue());
		
		System.out.println(QT.length());
		
		System.out.println(QT.dequeue());
		
		System.out.println(QT.isEmpty());
		
		System.out.println(QT.length());
		
		QT.dequeueAll();
		
		System.out.println(QT.isEmpty());
	}
}

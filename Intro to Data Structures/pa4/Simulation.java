//Galen Turoci
//gturoci
//Class CMPS 12B
//February 20th, 2018
//Simulation is a client that utilizes two different ADTs - Job.java and Queue.java.
//Simulation takes a series of jobs and processes them, and in doing so
//figures out their arrival times, waiting times, processing times, and finishing times.
//Simulation.java

import java.io.*;
import java.util.Scanner;

public class Simulation {
	
	public static Job getJob(Scanner in) {
		String[] s = in.nextLine().split(" ");
		int a = Integer.parseInt(s[0]);
		int d = Integer.parseInt(s[1]);
		return new Job(a, d);
	}
	
	public static void main(String[] args) throws IOException {
		
		int i;
		int m;
		int n;
		int time = 0;
		int totalwait = 0;
		int maxwait = 0;
		double avgwait = 0.00;
		int arrtime;
		int durtime;
		Object X;

//    1.  check command line arguments
		if (args.length != 1) {
			System.err.println("Usage: Simulation inputfile");
			System.exit(1);
		}
//
//    2.  open files for reading and writing
		Scanner in = new Scanner(new File(args[0]));
		PrintWriter outrpt = new PrintWriter(new FileWriter(args[0]+".rpt"));
		PrintWriter outtrc = new PrintWriter(new FileWriter(args[0]+".trc"));
		
		outrpt.println("Report file: " + args[0] + ".rpt");
		outtrc.println("Trace file: " + args[0] + ".trc");
		
//
//    3.  read in m jobs from input file
		m = in.nextInt();
		
		outrpt.println(m + " Jobs:\n");
		outtrc.println(m + " Jobs:\n");
//
//    4.  run simulation with n processors for n=1 to n=m-1  {
		for (n=1; n<m; n++) {
//
//    5.      declare and initialize an array of n processor Queues and any 
//            necessary storage Queues
			Queue[] Processors = new Queue[n];
			for (i=0; i<Processors.length; i++)
				Processors[i] = new Queue();
				
			while (in.hasNextLine()) {
				Processors[0].enqueue(in.nextLine());
				outrpt.print(Processors[0].peek());
				outtrc.print(Processors[0].peek());
			}
			
            Queue FinishedJobs = new Queue();
            
            if (n == 1)
				outrpt.println("***********************************************************");
			
			if (n == 1) {
					outtrc.println("*****************************\n"+
									n+" processor:\n"+
									"*****************************");
			}
			else { //n<1
					outtrc.println("*****************************\n"+
									n+" processors:\n"+
									"*****************************");
			}
//
//    6.      while unprocessed jobs remain  {
			while (FinishedJobs.length() < m) {
				outtrc.println("time="+time+"\n");
				
				time++;
				
				for (i=0; i<=n; i++) {
					outtrc.print(i+": ");
					for (int j=0; j<Processors.length; j++) {
						if (!Processors[j].isEmpty())
							outtrc.print(Processors[j].peek()+" ");
					}
				}
				
//
//    7.          determine the time of the next arrival or finish event and 
//                update time
				Job J;
				J = (Job)Processors[0].peek();
//
//    8.          complete all processes finishing now
				for (i=1; i<Processors.length; i++) {
					J.computeFinishTime(time);
					if (J.getFinish() == time) {
						//Move J to FinishedJobs
						X = Processors[i].dequeue();
						FinishedJobs.enqueue(X);
					}
				}
				
				for (i=0; i<=n; i++) {
					outtrc.print(i+": ");
					for (int j=0; j<=Processors[i].length(); j++)
						outtrc.print(Processors[j].peek()+" ");
				}
				
//
//    9.          if there are any jobs arriving now, assign them to a processor 
//                Queue of minimum length and with lowest index in the queue array.
				if (J.getArrival() == time) {
					int[] x = new int[Processors.length-1];
					int j = 0;
					int k = 0;
					for (i=1; i<Processors.length; i++) {
						x[j] = Processors[i].length();
						j++;
					}
					for (i=0; i<x.length; i++) {
						if (x[i]<x[k]) {
							//Move J to Processors[++k]
							X = Processors[0].dequeue();
							Processors[++k].enqueue(X);
						}
						else {
							//Move J to Processors[1]
							X = Processors[0].dequeue();
							Processors[1].enqueue(X);
						}
					}
				}
				
				for (i=0; i<=n; i++) {
					outtrc.print(i+": ");
					for (int j=0; j<=Processors[i].length(); j++)
						outtrc.print(Processors[j].peek()+" ");
				}				
            }
//
//    11.     compute the total wait, maximum wait, and average wait for 
//            all Jobs, then reset finish times

			//Computing the times
			Job F;
			//Computing total wait and maxWait
			for (i=0; i<FinishedJobs.length(); i++) {
				F = (Job)FinishedJobs.dequeue();
				totalwait += F.getWaitTime();
				if (F.getWaitTime() > maxwait)
					maxwait = F.getWaitTime();
			}
			//Computing average wait
			avgwait = totalwait/i;
			
			//Writing the times to the output files
			if (n == 1) {
				outrpt.println(n+" processor: totalWait="+totalwait+
								", maxWait="+maxwait+", averageWait="
								+avgwait);
			}
			else { //n<1
				outrpt.println(n+" processors: totalWait="+totalwait+
								", maxWait="+maxwait+", averageWait="
								+avgwait);
			}
			time=0;
        }

		in.close();
		outrpt.close();
		outtrc.close();

   }
}

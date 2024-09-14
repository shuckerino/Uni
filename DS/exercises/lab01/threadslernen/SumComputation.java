package threadslernen;

import java.util.Date;

public class SumComputation {

	final static int SIZE = 100000;
	private int sum = 0;
	private int[] sa1 = new int[SIZE];
	private int[] sa2 = new int[SIZE];
	private long starttime;
	private long endtime;

	public static void main(String[] args) {
		SumComputation program = new SumComputation();
		program.execute(args);
	}

	// Methode zum Zugriff auf Sum
	void addToSum(int i) {
		sum = sum + i;
	}

	private void execute(String[] args) {
		System.out.println("Starte Programm SumComputation");

		// Initialise sa1 with 1s and sa2 with 2s
		for (int i = 0; i < SIZE; i++) {
			sa1[i] = 1;
		}
		for (int i = 0; i < SIZE; i++) {
			sa2[i] = 2;
		}

		// Erzeuge Worker Threads
		Thread wt1 = new Thread(new WorkerThread(1));
		Thread wt2 = new WorkerThread(2);

		// Starte Worker Threads
		wt1.runThread();
		wt2.runThread();

		// Warte auf Ende von Worker Threads


		System.out.println("Programm: sum " + sum);
		System.out.println("Beende Programm SumComputation");

	}

	private class WorkerThread implements Runnable {

		private int id;

		public WorkerThread(int id) {
			this.id = id;
		}

		public void runThread() throws InterruptedException {
			System.out.println("Starte worker " + id + " der Klasse " + getClass().getName());

			// Sleep 1 s
			Thread.sleep(1000);
			

		}

	}
}

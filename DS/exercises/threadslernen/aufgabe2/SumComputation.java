package threadslernen.aufgabe2;


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
			sa2[i] = 2;
		}

		// Erzeuge Worker Threads
		Thread wt1 = new Thread(new WorkerThread(1, sa1));
		Thread wt2 = new Thread(new WorkerThread(2, sa2));

		// Starte Worker Threads
		wt1.run();
		wt2.run();

		try {
			// Warte auf Ende von Worker Threads
			wt1.join();
			wt2.join();
		} catch (Exception e) {
		}

		System.out.println("Programm: sum " + sum);
		System.out.println("Beende Programm SumComputation");

	}

	private class WorkerThread implements Runnable {

		private int id;
		private int[] threadArray;

		public WorkerThread(int id, int[] threadArray) {
			this.id = id;
			this.threadArray = threadArray;
		}

		@Override public void run() {
			System.out.println("Starte worker " + id + " der Klasse " + getClass().getName());

			try {
				// Sleep 1 s
				Thread.sleep(1000);
			} catch (Exception e) {
			}

			for (int i : this.threadArray) {
				addToSum(i);
			}

			System.out.println("Worker " + id + ": sum = " + sum);
			System.out.println("Beende worker " + id + " der Klasse " + getClass().getName());
			

		}

	}
}

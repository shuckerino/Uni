
import dp.composite.DepartmentManager;
import dp.composite.NormalWorker;
import dp.composite.WorkerComponent;

public class CompositePatternTest {
   
    public static void main(String[] args) {
		WorkerComponent manager = new DepartmentManager("Egon", "REICH", "258762",
				"MANAGEMENT", "CEO", 40239.39);
		WorkerComponent medien = new DepartmentManager("Lars", "FAUL", "204909",
				"MEDIEN", "Leiter Medienabteilung", 4020.03);

		WorkerComponent schmitt = new NormalWorker("Konrad", "Schmitt", "30000",
				"Sachbearbeiter", 2020.0);
		WorkerComponent meyer = new  NormalWorker("Peter", "Meyer", "32000",
				"Sachbearbeiter", 2000.0);
		
		try {
			manager.add(medien);
			medien.add(schmitt);
			medien.add(meyer);
			System.out.println(manager);
		} catch (UnsupportedOperationException e) {
			System.out.println(e.toString());
		}

	}
}

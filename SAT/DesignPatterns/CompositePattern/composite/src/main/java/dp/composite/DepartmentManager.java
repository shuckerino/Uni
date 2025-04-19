package dp.composite;

import java.util.ArrayList;

public class DepartmentManager extends WorkerComponent {

    // Member
    private ArrayList<WorkerComponent> listOfWorkers = new ArrayList<>();

    // Constructor
    public DepartmentManager(String _firstName, String _lastName, String _id, String _department, String _jurisdiction,
            Double _salary) {
        super(_firstName, _lastName, _id, _jurisdiction, _salary);
        this.setDepartment(_department);
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("Name: ").append(this.getFirstName()).append(" ").append(this.getLastName()).append(" Personalnummer: ").append(this.getWorkerId())
                .append(" Abteilung: ").append(this.getDepartment()).append(" Zuständigkeit: ").append(this.getJurisdiction())
                .append(" Gehalt: ").append(this.getSalary());
        if (!listOfWorkers.isEmpty()) {
            sb.append(" Zugeordnete Mitarbeiter: [ ");
            for (WorkerComponent wc : listOfWorkers) {
                sb.append(wc.toString()).append(" ");
            }
            sb.append("]");
        }
        return sb.toString();
    }

    @Override
    public void add(WorkerComponent wc) {
        listOfWorkers.add(wc);
    }

    @Override
    public void remove(WorkerComponent wc) {
        listOfWorkers.remove(wc);
    }

    @Override
    public ArrayList<WorkerComponent> getWorkerList() {
        return listOfWorkers;
    }

}

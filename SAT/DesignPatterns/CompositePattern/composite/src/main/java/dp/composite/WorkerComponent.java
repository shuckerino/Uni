package dp.composite;

import java.util.ArrayList;

public abstract class WorkerComponent {

   // This is the common interface class when using the Composite Pattern 
    // Member
   private String firstName;
   private String lastName;
   private String workerId;
   private String department;
   private String jurisdiction;
   private Double salary;

   // Constructor
   public WorkerComponent(String _firstName, String _lastName, String _id, String _juridiction, Double _salary){
        this.firstName = _firstName;
        this.lastName = _lastName;
        this.workerId = _id;
        this.jurisdiction = _juridiction;
        this.salary = _salary;
    }

    // toString method needs to be abstract, because the implementation differs for the different calsses
    @Override
    public String toString() {
		StringBuffer sb = new StringBuffer();
		
		sb.append("\nName:\t" + firstName + " " + lastName + " ");
		sb.append("Personalnummer: " + workerId + " ");
		sb.append("Abteilung: " + department  + " ");
		sb.append("Zuständigkeit: " + jurisdiction + " ");
		sb.append("Gehalt: " + salary + "\n");

        return sb.toString();
    }

   public String getFirstName() {
       return firstName;
   }

   public void setFirstName(String firstName) {
       this.firstName = firstName;
   }

   public String getLastName() {
       return lastName;
   }

   public void setLastName(String lastName) {
       this.lastName = lastName;
   }

   public String getWorkerId() {
       return workerId;
   }

   public void setWorkerId(String workerId) {
       this.workerId = workerId;
   }

   public String getDepartment(){
    return this.department;
   }

   public void setDepartment(String department){
    this.department = department;
   }

   public String getJurisdiction() {
       return jurisdiction;
   }

   public void setJurisdiction(String jobDescription) {
       this.jurisdiction = jobDescription;
   }

   public Double getSalary() {
       return salary;
   }

   public void setSalary(Double salary) {
       this.salary = salary;
   }

   // Here are the methods for managing the workerList for managers
   // Why do we put it into the common interface instead of directly in the DepartmentManager class?
   // Well, this is because we want to treat our leaf nodes and other nodes equally. If we differentiate between those two, then we would need to 
   // check any time which node we have. In this way, we can just call the method anyway

   public void add(WorkerComponent m) {
        throw new UnsupportedOperationException();
    }

    public void remove(WorkerComponent m) {
        throw new UnsupportedOperationException();
    }

    public ArrayList<WorkerComponent> getWorkerList() {
        throw new UnsupportedOperationException();
    }
}

package dp.composite;

import java.util.ArrayList;

public class Person {

    // Member
    private String firstName;
    private String lastName;
    private String workerId;
    private String jobDescription;
    private Float salary;
    private ArrayList<Department> listOfSubDepartments;

    // Constructor
    public Person(String _firstName, String _lastName, String _id, String _jobDescription, Float _salary){
        this.firstName = _firstName;
        this.lastName = _lastName;
        this.workerId = _id;
        this.jobDescription = _jobDescription;
        this.salary = _salary;
    }

    

    @Override
    public String toString() {
        return String.format("Name: %s %s Personalnummer: %s Abteilung: %s Zuständigkeit: %s Gehalt: %s", lastName, firstName, workerId, jobDescription, salary);
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

    public String getJobDescription() {
        return jobDescription;
    }

    public void setJobDescription(String jobDescription) {
        this.jobDescription = jobDescription;
    }

    public Float getSalary() {
        return salary;
    }

    public void setSalary(Float salary) {
        this.salary = salary;
    }
    
}

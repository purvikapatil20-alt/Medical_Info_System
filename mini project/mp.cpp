#include <iostream>
#include <iomanip>   // for setw() - to make table neat
#include <string>
using namespace std;

// Structure to store patient details
struct Patient {
    int id;
    string name;
    int age;
    string gender;
    string disease;
    string medicines;
    string nextAppointment;
    Patient* next; // pointer to next patient (for linked list)
};

// Head pointer of linked list
Patient* head = NULL;

// Function to create a new patient node
Patient* createPatient(int id, string name, int age, string gender, string disease, string medicines, string nextAppointment) {
    Patient* newPatient = new Patient;
    newPatient->id = id;
    newPatient->name = name;
    newPatient->age = age;
    newPatient->gender = gender;
    newPatient->disease = disease;
    newPatient->medicines = medicines;
    newPatient->nextAppointment = nextAppointment;
    newPatient->next = NULL;
    return newPatient;
}

//  Add Patient
void addPatient() {
    int id, age;
    string name, gender, disease, medicines, nextAppointment;

    cout << "\nEnter Patient ID: ";
    cin >> id;
    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, name);
    cout << "Enter Age: ";
    cin >> age;
    cin.ignore();
    cout << "Enter Gender (Male/Female): ";
    getline(cin, gender);
    cout << "Enter Disease: ";
    getline(cin, disease);
    cout << "Enter Medicines prescribed: ";
    getline(cin, medicines);
    cout << "Enter Next Appointment Date: ";
    getline(cin, nextAppointment);

    Patient* newPatient = createPatient(id, name, age, gender, disease, medicines, nextAppointment);

    // Insert at end of linked list
    if (head == NULL)
        head = newPatient;
    else {
        Patient* temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newPatient;
    }

    cout << "\nPatient added successfully!\n";
}

//  Display Patients in tabular form
void displayPatients() {
    if (head == NULL) {
        cout << "\nNo patient records found!\n";
        return;
    }

    cout << "\n-------------------------------------------------------------\n";
    cout << left << setw(5) << "ID"
         << setw(15) << "Name"
         << setw(5) << "Age"
         << setw(10) << "Gender"
         << setw(15) << "Disease"
         << setw(20) << "Medicines"
         << setw(15) << "Next Appt\n";
    cout << "-------------------------------------------------------------\n";

    Patient* temp = head;
    while (temp != NULL) {
        cout << left << setw(5) << temp->id
             << setw(15) << temp->name
             << setw(5) << temp->age
             << setw(10) << temp->gender
             << setw(15) << temp->disease
             << setw(20) << temp->medicines
             << setw(15) << temp->nextAppointment << endl;
        temp = temp->next;
    }
}

//  Search Patient (by ID or Name)
void searchPatient() {
    if (head == NULL) {
        cout << "\nNo records to search!\n";
        return;
    }

    int choice;
    cout << "\nSearch by:\n1. ID\n2. Name\nEnter choice: ";
    cin >> choice;
    cin.ignore();

    if (choice == 1) {
        int id;
        cout << "Enter Patient ID: ";
        cin >> id;

        Patient* temp = head;
        while (temp != NULL) {
            if (temp->id == id) {
                cout << "\nPatient Found!\n";
                cout << "Name: " << temp->name << "\nAge: " << temp->age
                     << "\nGender: " << temp->gender
                     << "\nDisease: " << temp->disease
                     << "\nMedicines: " << temp->medicines
                     << "\nNext Appointment: " << temp->nextAppointment << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "\nNo patient found with that ID.\n";
    } 
    else if (choice == 2) {
        string name;
        cout << "Enter Patient Name: ";
        getline(cin, name);

        Patient* temp = head;
        while (temp != NULL) {
            if (temp->name == name) {
                cout << "\nPatient Found!\n";
                cout << "ID: " << temp->id << "\nAge: " << temp->age
                     << "\nGender: " << temp->gender
                     << "\nDisease: " << temp->disease
                     << "\nMedicines: " << temp->medicines
                     << "\nNext Appointment: " << temp->nextAppointment << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "\nNo patient found with that Name.\n";
    } 
    else {
        cout << "\nInvalid choice!\n";
    }
}

//  Delete Patient (by ID)
void deletePatient() {
    if (head == NULL) {
        cout << "\nNo records to delete!\n";
        return;
    }

    int id;
    cout << "Enter Patient ID to delete: ";
    cin >> id;

    Patient* temp = head;
    Patient* prev = NULL;

    // If first node is to be deleted
    if (temp != NULL && temp->id == id) {
        head = temp->next;
        delete temp;
        cout << "\nPatient record deleted successfully!\n";
        return;
    }

    // Search for the patient
    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        cout << "\nPatient not found!\n";
        return;
    }

    prev->next = temp->next;
    delete temp;
    cout << "\nPatient record deleted successfully!\n";
}

//  Sort Patients by Age or Name (Simple Bubble Sort)
void sortPatients() {
    if (head == NULL || head->next == NULL) {
        cout << "\nNot enough records to sort!\n";
        return;
    }

    int choice;
    cout << "\nSort by:\n1. Age\n2. Name\nEnter choice: ";
    cin >> choice;

    for (Patient* i = head; i->next != NULL; i = i->next) {
        for (Patient* j = head; j->next != NULL; j = j->next) {
            bool swapNeeded = false;
            if (choice == 1 && j->age > j->next->age)
                swapNeeded = true;
            else if (choice == 2 && j->name > j->next->name)
                swapNeeded = true;

            if (swapNeeded) {
                // Swap data (not links, for simplicity)
                swap(j->id, j->next->id);
                swap(j->name, j->next->name);
                swap(j->age, j->next->age);
                swap(j->gender, j->next->gender);
                swap(j->disease, j->next->disease);
                swap(j->medicines, j->next->medicines);
                swap(j->nextAppointment, j->next->nextAppointment);
            }
        }
    }

    cout << "\nPatients sorted successfully!\n";
}

// Main Function
int main() {
    int choice;
    do {
        cout << "\n\n===== MEDICAL INFORMATION SYSTEM =====\n";
        cout << "1. Add Patient\n";
        cout << "2. Display Patients\n";
        cout << "3. Search Patient\n";
        cout << "4. Delete Patient\n";
        cout << "5. Sort Patients\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: addPatient(); break;
            case 2: displayPatients(); break;
            case 3: searchPatient(); break;
            case 4: deletePatient(); break;
            case 5: sortPatients(); break;
            case 6: cout << "\nExiting program... Thank you!\n"; break;
            default: cout << "\nInvalid choice! Try again.\n";
        }
    } while (choice != 6);

    return 0;
}
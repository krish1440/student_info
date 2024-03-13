#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100  //BY default ITS FIX 

struct Student {
    int id;
    char name[50];
    int age;
    float gpa;
};

/*FUNCTION DEFINATION*/
void addStudent(struct Student students[], int *numStudents);
void updateStudent(struct Student students[], int numStudents);
void deleteStudent(struct Student students[], int *numStudents);
void displayAllStudents(struct Student students[], int numStudents);
void saveDataToCSV(struct Student students[], int numStudents);
void rewriteFile(struct Student students[], int numStudents, FILE *file);

int main() {
    struct Student students[MAX_STUDENTS];  
    int numStudents = 0;
    int choice;
/*CHOICE TO CHOOSE THE SERVICE*/
    do {
        printf("\nMenu:\n");
        printf("1. Add Student\n");
        printf("2. Update Student\n");
        printf("3. Delete Student\n");
        printf("4. Display All Students\n");
        printf("5. Save Data to CSV\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent(students, &numStudents);
                break;
            case 2:
                updateStudent(students, numStudents);
                break;
            case 3:
                deleteStudent(students, &numStudents);
                break;
            case 4:
                displayAllStudents(students, numStudents);
                break;
            case 5:
                saveDataToCSV(students, numStudents);
                break;
            case 6:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}

/*DECLARATION OF VARIOUS FUNCTION*/
void addStudent(struct Student students[], int *numStudents) {
    if (*numStudents < MAX_STUDENTS) {
        struct Student newStudent;

        printf("Enter student ID: ");
        scanf("%d", &newStudent.id);

        // Clear the input buffer
        while (getchar() != '\n');

        printf("Enter student name: ");
        scanf("%[^\n]", newStudent.name);
        
        printf("Enter student age: ");
        scanf("%d", &newStudent.age);
        printf("Enter student GPA: ");
        scanf("%f", &newStudent.gpa);

        students[*numStudents] = newStudent;
        (*numStudents)++;

        printf("Student added successfully.\n");
    } else {
        printf("Maximum number of students reached.\n");
    }
}

void updateStudent(struct Student students[], int numStudents) {
    int id, found = 0;

    printf("Enter the ID of the student to update: ");
    scanf("%d", &id);

    for (int i = 0; i < numStudents; i++) {
        if (students[i].id == id) {
            printf("Enter updated information for student %d:\n", id);
            printf("Enter student name: ");
            scanf("%s", students[i].name);
            printf("Enter student age: ");
            scanf("%d", &students[i].age);
            printf("Enter student GPA: ");
            scanf("%f", &students[i].gpa);

            printf("Student updated successfully.\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Student with ID %d not found.\n", id);
    }
}

void deleteStudent(struct Student students[], int *numStudents) {
    int id, found = 0;

    printf("Enter the ID of the student to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < *numStudents; i++) {
        if (students[i].id == id) {
            for (int j = i; j < *numStudents - 1; j++) {
                students[j] = students[j + 1];
            }
            (*numStudents)--;
            printf("Student with ID %d deleted successfully.\n", id);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Student with ID %d not found.\n", id);
    }
}

void displayAllStudents(struct Student students[], int numStudents) {
    if (numStudents > 0) {
        printf("\nAll Students:\n");
        printf("ID\tName\tAge\tGPA\n");
        for (int i = 0; i < numStudents; i++) {
            printf("%d\t%s\t%d\t%.2f\n", students[i].id, students[i].name, students[i].age, students[i].gpa);
        }
    } else {
        printf("No students to display.\n");
    }
}

void saveDataToCSV(struct Student students[], int numStudents) {
    FILE *file = fopen("students.csv", "w");

    if (file != NULL) {
        fprintf(file, "ID,Name,Age,GPA\n");

        for (int i = 0; i < numStudents; i++) {
            fprintf(file, "%d,%s,%d,%.2f\n", students[i].id, students[i].name, students[i].age, students[i].gpa);
        }

        fclose(file);
        printf("Student data saved to students.csv successfully.\n");
    } else {
        printf("Error opening file for writing.\n");
    }
}

void rewriteFile(struct Student students[], int numStudents, FILE *file) {
    fprintf(file, "ID,Name,Age,GPA\n");

    for (int i = 0; i < numStudents; i++) {
        fprintf(file, "%d,%s,%d,%.2f\n", students[i].id, students[i].name, students[i].age, students[i].gpa);
    }
}

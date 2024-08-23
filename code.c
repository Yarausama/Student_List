/*************************************************************************
 * code.c
 *
 *  Created on: Aug 8, 2024
 *      Author: yara osama mohtady
 *      description:student_list
 **************************************************************************/

#include <stdio.h>
#include <stdlib.h>
struct student {      //declare the structure student
	int id;
	char name[50];
	int age;
	float gpa;
};
// functions prototypes
void addStudent(const struct student *const ptr);
void displayStudents(void);
void searchStudentByID(int id);
void updateStudent(int id);
float calculateAverageGPA(void);
void searchHighestGPA(void);
void deleteStudent(int id);
int not_repeated(int id);
void strcopy(char *ptr1,const char *ptr2);

struct node {
	struct student data;     //create node structure
	struct node *next;
};

struct node *head = NULL;
struct node *current = NULL;
int studentno;     //declaration to define number of student
int student_id;
struct student st1;
const struct student *const ptr = &st1;  //create structure pointer to point to the structure created

int main() {
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	int case_select;
	//display menu and execute the required function

	do {
		printf(
				"-------------------------------------------------------------------\n1: Add a student\n"
				"2: Display all students\n"
				"3: Search for a Student by ID\n"
				"4: Update Student Information\n"
				"5: Calculate Average GPA\n"
				"6: Find Student with Highest GPA\n"
				"7: Delete a Student\n"
				"8: Exit\n"
				"Choose your proper function:\n----------------------------------------------------\n");
		scanf("%d", &case_select);

		switch (case_select) {
		case 1:
			printf("Enter the data of the student you want to add:\n");
			printf("ID: ");
			scanf("%d", &st1.id);

			printf("Name: ");
			scanf(" %[^\n]", st1.name); // This handles strings with spaces
			printf("Age: ");
			scanf("%d", &st1.age);
			printf("GPA: ");
			scanf("%f", &st1.gpa);
			if(!(not_repeated(st1.id)))
			{
				printf("the id is repeated , please try again!\n"); //to ensure that the id is not repeated
				break;
			}
			//if condition to ensure that GPA is in correct manner
			if (st1.gpa < 0.0 || st1.gpa > 4.0) {
				printf("Invalid GPA score!\n");
				break;
			}
			addStudent(ptr);
			break;
		case 2:
			displayStudents();
			break;
		case 3:
			printf("Enter the ID you want to search for: ");
			scanf("%d", &student_id);
			searchStudentByID(student_id);
			break;
		case 4:
			printf("Enter the ID you want to update: ");
			scanf("%d", &student_id);
			updateStudent(student_id);
			break;
		case 5:
			printf("Average GPA: %.1f\n", calculateAverageGPA());
			break;
		case 6:
			searchHighestGPA();
			break;
		case 7:
			printf("Enter the ID you want to delete: ");
			scanf("%d", &student_id);
			deleteStudent(student_id);
			break;
		case 8:
			printf("you exit program!");
			break;
		default:
			printf("Undefined case! Please try again.\n");
		}
	} while (case_select != 8);

	return 0;
}
// functions definitions
void addStudent(const struct student *const ptr) {
	struct node *link = (struct node*)malloc(sizeof(struct node));

	if (link == NULL) {
		printf("Memory allocation failed!\n");
		return;
	}

	link->data.id = ptr->id;
	link->data.age = ptr->age;
	strcopy(link->data.name, ptr->name); // Use strcpy to copy 2nd in 1st string
	link->data.gpa = ptr->gpa;
	link->next = NULL;

	if (head == NULL) {
		head = link;
		current = head;
	} else {
		current = head;
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = link;
	}
	printf("The list after addition is:\n");
	displayStudents();

}

int not_repeated(int id)
{
	struct node *temp=head;
	while(temp!=NULL)
	{
		if(temp->data.id==id)
		{

			return 0;
		}
temp=temp->next;
	}
	return 1;
}

void strcopy(char *ptr1,const char *ptr2)
{
	while(*ptr2!='\0')
	{
		*ptr1=*ptr2;
		ptr1++;
		ptr2++;
	}
	*ptr1='\0';
	return;
}
void displayStudents(void) {
	studentno = 1;
	current = head;

	if (head == NULL) {
		printf("The list is empty!\n");
		return;
	}

	while (current != NULL) {
		printf("Student %d information: ID: %d, Name: %s, Age: %d, GPA: %.1f\n",
				studentno, current->data.id, current->data.name, current->data.age, current->data.gpa);
		current = current->next;
		studentno++;
	}
}

void searchStudentByID(int id) {
	current = head;

	while (current != NULL) {
		if (current->data.id == id) {
			printf("Student found: Name: %s, Age: %d, GPA: %.1f\n",
					current->data.name, current->data.age, current->data.gpa);
			return;
		}
		current = current->next;
	}

	printf("ID not found!\n");
}

void updateStudent(int id) {
	current = head;
	int id_check;             // to check first if itis repeated in update function
	if (head == NULL) {
		printf("The list is empty!\n");
		return;
	}

	while (current != NULL) {
		if (current->data.id == id) {
			printf("Update the student information:\n");
			printf("Update ID: ");
			scanf("%d", &id_check);
			if(!(not_repeated(id_check)))
			{
				//to ensure that the id is not repeated
				printf("the id is repeated , please try again!\n");
				current->data.id=id;
				return;
			}
			current->data.id=id_check;
			printf("Update Name: ");
			scanf(" %[^\n]", current->data.name);
			printf("Update Age: ");
			scanf("%d", &current->data.age);
			gpa:
			printf("Update GPA: ");
			scanf("%f", &current->data.gpa);

						//if condition to ensure that GPA is in correct manner
						if (current->data.gpa < 0.0 || current->data.gpa > 4.0) {
							printf("Invalid GPA score!\n");
							goto gpa;
							return;
						}
			printf("successfully update,The updated list is:\n");
			displayStudents();
			return;
		}
		current = current->next;
	}

	printf("Student not found, try again!\n");
}

float calculateAverageGPA(void) {
	current = head;
	int count = 0;
	float sum_gpa = 0;

	if (head == NULL) {
		printf("The list is empty!\n");
		return 0;
	}

	while (current != NULL) {
		sum_gpa += current->data.gpa;
		current = current->next;
		count++;
	}

	return (count > 0) ? sum_gpa / count : 0;
}

void searchHighestGPA(void) {
	current = head;

	if (head == NULL) {
		printf("The list is empty!\n");
		return;
	}

	float max_gpa = head->data.gpa;
	struct student *top_student = &head->data;

	while (current != NULL) {
		if (current->data.gpa > max_gpa) {
			max_gpa = current->data.gpa;
			top_student = &current->data;
		}
		current = current->next;
	}

	printf("The student with the highest GPA is %s with a GPA of %.1f\n", top_student->name, max_gpa);
}

void deleteStudent(int id) {
	current = head;
	struct node *prev = NULL;

	if (head == NULL) {
		printf("The list is empty!\n");
		return;
	}

	if (current != NULL && current->data.id == id) {
		head = current->next;
		free(current);
		printf("Student deleted successfully!\n");
		displayStudents();
		return;
	}

	while (current != NULL && current->data.id != id) {
		prev = current;
		current= current->next;
	}

	if (current == NULL) {
		printf("Student not found, try again!\n");
		return;
	}

	prev->next = current->next;
	free(current);
	printf("Student deleted successfully!\n");
	displayStudents();
}

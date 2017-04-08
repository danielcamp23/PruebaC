#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct person {
	int record;
	char name[10];
	int birth_year;
	int birth_month;
	int birth_day;
	struct person *nextPerson;
};

struct count{
	int current_year;
	int current_month;
	int current_day;
};

struct current{
	int current_year;
	int current_month;
	int current_day;
};

struct next_birthday{
	int passed_days;
	int comming_days;
	int age;
};

/*
struct tm *localtime(const time_t *timer)

struct tm {
   int tm_sec;         // seconds,  range 0 to 59          
   int tm_min;         // minutes, range 0 to 59           
   int tm_hour;        // hours, range 0 to 23             
   int tm_mday;        // day of the month, range 1 to 31  
   int tm_mon;         // month, range 0 to 11             
   int tm_year;        // The number of years since 1900   
   int tm_wday;        // day of the week, range 0 to 6    
   int tm_yday;        // day in the year, range 0 to 365  
   int tm_isdst;       // daylight saving time             	
};
*/

typedef struct person s_person;
typedef struct count s_count;
typedef struct next_birthday s_nbirth;
typedef struct current s_current;

void insert_person (s_person **Head, char name[], int year, int month, int day);
void get_person (s_person **);
void assign_current_day (s_current *current_date, struct tm m_tyme); 
void get_nex_birth(int record, s_person *person,s_current, s_nbirth *next_birth); 


int main (void){


s_person *s_perHeadNode = NULL;
s_current S_current;
s_nbirth N_birth;
int tyear, tmonth, tday;
char tname[20] = {0};
int conf=0;
int option = 0;
unsigned int sub;

time_t t = time(NULL);
struct tm my_time = *localtime(&t);
assign_current_day(&S_current, my_time);


do {
	puts("    **MENU**");
	puts("1) Ingresar nodo");
	puts("2) Calcular nodo");
	puts("3) Salir") ;
	scanf("%d", &option);
	memset(tname, '\0', sizeof(tname));

	switch(option){
		case 1:	printf("Nombre: ");
			scanf("%7s", tname);
			printf("Anio: ");
			scanf("%d", &tyear);
			printf("Mes: ");
			scanf("%d", &tmonth);
			printf("Dia: ");
			scanf("%d", &tday);
			insert_person(&s_perHeadNode, tname, tyear, tmonth, tday);
			break;

		case 2: puts("");
			get_person (&s_perHeadNode);
			printf("Ingrese el subindice a revisar: ");
			scanf("%d", &sub);
			puts("");
			get_nex_birth(sub, s_perHeadNode,S_current, &N_birth);
			
			break;	

		case 3:	//Exit
			break;

		default:
			break;
	}


}while (option != 3);
	
return 0;
}



void insert_person (s_person **Head, char tname[], int year, int month, int day){


	
	if(*Head == NULL){//Primer elemento
		s_person *next = malloc(sizeof(s_person));
		if(next == NULL){
			puts("No se pudo reservar la memoria");
			return;
		}

		strcpy(next->name, tname);
		next->record = 1;
		next->birth_year = year;
		next->birth_month = month;
		next->birth_day = day;

		next->nextPerson = NULL;
		*Head = next;
		
	}
	else{//inserta despues del primer elemento
	s_person *actual = *Head;
		while(actual != NULL){//while(actual->nextPerson != NULL){
			if(actual->nextPerson == NULL){
				s_person *next = malloc(sizeof(s_person));	
			if(next == NULL){
				puts("No se pudo reservar la memoria memoria");
				return;
			}
				next->record = actual->record + 1;
				strcpy(next->name, tname);
				next->birth_year = year;
				next->birth_month = month;
				next->birth_day = day;
				actual->nextPerson = next;
				return; 	
			}
			else{
				actual = (actual->nextPerson);
			}			
		}


		
}
}		
	
void get_person (s_person **Headd){
	s_person *current = *Headd;
	unsigned int cont = 0;
	int a=0;

	while(current != NULL){
		printf("Record: %d\nName: %s \nYear: %d \nMonth: %d \nDay: %d",current->record, current->name, current->birth_year, 			current->birth_month, current->birth_day);
		puts("");
		puts("");
		current = current->nextPerson;
	}


}

void assign_current_day(s_current *current_date, struct tm my_time){
	current_date->current_year = my_time.tm_year + 1900;
	current_date->current_month = my_time.tm_mon + 1;
	current_date->current_day = my_time.tm_mday;
}

void get_nex_birth(int record, s_person *person,s_current date, s_nbirth *next_birth){
		
		if(person == NULL){
			puts("Aun no hay entradas en la lista");
			return;
}
		s_person entry = *person;
		unsigned int cont = 0;
		int cur_y, cur_m, cur_d, u_y, u_m, u_d, p_y, p_m, p_d;
	
		cur_y = date.current_year; //Store current date
		cur_m = date.current_month;
		cur_d = date.current_day;

		while(cont++<record-1){
			entry = *(entry.nextPerson);
		}

		u_y = entry.birth_year;//Store user data
		u_m = entry.birth_month;
		u_d = entry.birth_day;


		p_y = cur_y - u_y;//Store after birthday (passed date)
		p_m = cur_m - u_m;
		p_d = cur_d - u_d;

		if((p_m<0) || (p_m==0 && p_d<0)){//Birthyday month has not come yet or it came but not the day
			p_y--;
		}

		if(p_m<0){
			p_m += 12;		
		}

		if(p_m==0 && p_d<0){
			p_m = 12;
		}

		 												
		next_birth->age = p_y;		
		next_birth->passed_days = p_d + p_m*30;
		next_birth->comming_days = 365 - next_birth->passed_days;

		printf("Record: %d\nName: %s \nYear: %d \nMonth: %d \nDay: %d",entry.record, entry.name, entry.birth_year, 			entry.birth_month, entry.birth_day);
		puts("");
		puts("");

		printf("Edad: %d\npassed days: %d \ncomming days: %d \n",next_birth->age, next_birth->passed_days, next_birth->comming_days);
		puts("");
		puts("");		

}


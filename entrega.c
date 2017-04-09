#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define ERR_INPUT -1

struct person {//Almacena información principal
	int record;
	char name[20];
	int birth_year;
	int birth_month;
	int birth_day;
	struct person *nextPerson;
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


typedef struct person s_person;
typedef struct next_birthday s_nbirth;
typedef struct current s_current;


void insert_person (s_person **Head, char name[], int year, int month, int day);
int get_person (s_person **);
void assign_current_day (s_current *current_date, struct tm m_tyme); 
void get_nex_birth(int record, s_person *person,s_current, s_nbirth *next_birth); 
int validate_num(const char *num, int min, int max);
char* validate_str(char *array, int size);


int main (void){


s_person *s_perHeadNode = NULL;
s_current S_current;
s_nbirth N_birth;
int tyear, tmonth, tday;
char tname[20] = {0};
int conf=0;
int entradas;
int option = 0;
int sub;
char user_input[80] = {'\0'};

time_t t = time(NULL);
struct tm my_time = *localtime(&t);
assign_current_day(&S_current, my_time);


do {
	printf("\n\n");
	puts("    **MENU**");
	puts("1) Ingresar nodo");
	puts("2) Calcular nodo");
	puts("3) Salir");
	
	memset(user_input, '\0', sizeof(tname));//Limpia string
	scanf("%s", user_input);
	option = validate_num(user_input, 1, 3);

	switch(option){
		case 1:	printf("Nombre: ");
			memset(user_input, '\0', sizeof(user_input));//Limpia string
			scanf("%s", tname);
			
			printf("Anio de nacimiento (1900-%d): ", my_time.tm_year+1900);
			memset(user_input, '\0', sizeof(user_input));//Limpia string
			scanf("%s", user_input);
			if((tyear = validate_num(user_input, 1900, my_time.tm_year+1900)) == ERR_INPUT)
				break;

			printf("Mes de nacimiento (1-12): ");
			memset(user_input, '\0', sizeof(user_input));
			scanf("%s", user_input);
			if((tmonth = validate_num(user_input, 1, 12)) == ERR_INPUT)
				break;

			printf("Dia de nacimiento(1-30): ");
			memset(user_input, '\0', sizeof(user_input));
			scanf("%s", user_input);
			if((tday = validate_num(user_input, 1, (tyear==my_time.tm_year+1900&&tmonth==my_time.tm_mon+1)?			my_time.tm_mday:30))==ERR_INPUT)
				break;

			insert_person(&s_perHeadNode, tname, tyear, tmonth, tday);//Almacena los datos ingresados
			break;

		case 2: puts("");
			if(!(entradas = get_person(&s_perHeadNode))){//Lista los registros almacenados y retorna el num de entradas
				printf("No hay registros en la lista\n");
				break;
			}

			printf("Ingrese el subindice a revisar: ");
			memset(user_input, '\0', sizeof(user_input));
			scanf("%s", user_input);
			if((sub = validate_num(user_input, 1, entradas))==ERR_INPUT){
				break;
			}
			
			get_nex_birth(sub, s_perHeadNode,S_current, &N_birth);			
			break;	

		case 3:	puts("Hasta luego");
			break;

		default:puts("Opcion invalida");
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
	
int get_person (s_person **Headd){
	s_person *current = *Headd;
	unsigned int cont = 0;
	int total = 0;

	while(current != NULL){
		printf("Entrada: %10d\nNombre: %11s \nAño de nac: %7d \nMes de nac: %7d \nDia de nac: %7d",current->record, current->name, 				current->birth_year,current->birth_month, current->birth_day);
		puts("");
		puts("");
		current = current->nextPerson;
		total++;
	}
	
	return total;
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

		printf("\nRecord: %15d\nNombre: %15s \nAño: %18d \nMes: %18d \nDia: %18d\n",entry.record, entry.name, entry.birth_year, 			entry.birth_month, entry.birth_day);
		printf("Edad: %17d\nDias desde ultimo: %4d \nDias para proximo: %4d \n",next_birth->age, next_birth->passed_days, next_birth->comming_days);
		puts("");
}


int validate_num(const char *num, int min, int max) {
	int val;
	if(sscanf(num, "%d", &val)){//Formato de entrada válido
		if(min<=val && val<=max){
			return val;
		}
		else{
			puts("Ingresaste un valor invalido");
			return ERR_INPUT;		
		}
			

	}
	else{
		puts("Ingresaste un valor incorrecto");
		return ERR_INPUT;
	}
}


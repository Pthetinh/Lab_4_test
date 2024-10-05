#define _CRT_SECURE_NO_WARNINGS
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <string.h>
#include <locale.h>
#define SIZE 100

struct date
{
	int month;
	int year;
}date;

struct car
{
	char stamp[50];
	char state_room[50];
	char name[50];
	struct date release_date;
	struct date date_of_last_inspection;
}car;

void format_time(int* month, int* year);
int menu1();
int menu2();
void print_data(struct car my_car[], int count);
void read_data(struct car my_car[], int* count);
void sort_data(struct car my_car[], int count);
void check_data(struct car my_car[], int* count, int month, int year);
void add_record(struct car my_car[], int& count);
void delete_record(struct car my_car[], int& count);
void working_data(struct car my_car[], int& count);

int main()
{
	setlocale(LC_ALL, " ");
	struct car* my_car = (struct car*)malloc(SIZE * (sizeof(struct car)));
	int count = 0;
	while (true)
	{
		int m1 = menu1();

		switch (m1)
		{
		case 1:
			system("cls");
			read_data(my_car, &count);
			break;
		case 2:
			system("cls");
			working_data(my_car, count);
			break;
		case 3:
			return 0;
		}
	}
	free(my_car);
	return 0;
}


void format_time(int* month, int* year)
{
	time_t rawtime;
	struct tm* timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	*month = timeinfo->tm_mon + 1;
	*year = timeinfo->tm_year + 1900;
}
int menu1()
{
	printf("\n");
	printf(" 1-Загрузить данные из файла\n");
	printf(" 2-Работа с данными\n");
	printf(" 3-Выход\n");
	printf("Выберите : ");

	int key;
	scanf_s("%d", &key);
	return key;
}
int menu2()
{
	printf("\n  1-Добавить запись\n ");
	printf(" 2-Удалить запись\n ");
	printf(" 3-Просмотреть содержимое запись\n ");
	printf(" 4-Проверить данных\n ");
	printf(" 5-Назад\n ");
	printf(" Выберите: ");
	int key2;
	scanf_s("%d", &key2);
	return key2;
}
void print_data(struct car my_car[], int count)
{
	system("cls");
	printf("\n");
	printf("\t%-20s%-23s%-22s%-26s%-17s\n", "МАСКА", "ГОС. НОМЕР", "ФАМИЛИЯ ", "ДАТА ВЫПУСКА", "ДАТА ПОСЛЕДНЕГО ТЕХОСМОТРА");

	for (int i = 0; i < count; i++)
	{
		printf("\t%-15s%-15s%-15s%-15d%-2d/%d\n", my_car[i].stamp,
			my_car[i].state_room, 
			my_car[i].name, 
			my_car[i].release_date.year, 
			my_car[i].date_of_last_inspection.month, 
			my_car[i].date_of_last_inspection.year);
	};
	printf("\n");
}
void read_data(struct car my_car[], int* count)
{
	FILE* fp;
	fp = fopen("input.docx", "r");
	if (fp == NULL)
	{
		printf("Error! File null!!!");
		return;
	}
	//int count = 0;
	while (!feof(fp))
	{
		fscanf(fp, "%40[^,],%40[^,],%40[^,],%d,%d/%d\n", my_car[*count].stamp, 
			my_car[*count].state_room, 
			my_car[*count].name, 
			&my_car[*count].release_date.year, 
			&my_car[*count].date_of_last_inspection.month, 
			&my_car[*count].date_of_last_inspection.year);
		*(count) += 1;
	};
	fclose(fp);
	printf("\nВы успешно прочитали данные из файла\n ");
	//return count;
};
void sort_data(struct car my_car[], int count)
{
	int i, j;
	for (int i = 0; i < count; i++)
		for (int j = count - 1; j > i; j--)
		{
			if (strcmp(my_car[j].name, my_car[j - 1].name) < 0)
			{
				struct car temp = my_car[j];
				my_car[j] = my_car[j - 1];
				my_car[j - 1] = temp;
			}
		}
}
void check_data(struct car my_car[], int* count, int real_month, int real_year)
{
	sort_data(my_car, *count);
	FILE* fp;
	fp = fopen("output1.docx", "w");
	if (fp == NULL)
	{
		printf("Error opening file!!!");
		return;
	}
	fprintf(fp, "%-20s%-22s%-22s%-25s%-17s\n", "МАСКА", "ГОС. НОМЕР", "ФАМИЛИЯ ", "ДАТА ВЫПУСКА", "ДАТА ПОС. ТЕХОСМОТРА");
	bool check;
	for (int i = 0; i < *count; i++)
	{
		check = false;
		int H1 = (real_year - my_car[i].release_date.year);
		int H2 = (real_month - my_car[i].date_of_last_inspection.month);
		int H3 = (real_year - my_car[i].date_of_last_inspection.year);

		if (H1 < 3)
		{
			check = true;
		}
		else if ((H1 == 3) && (H2 < 0)) // Через 3 года и текущий месяц < пос. месяц 
		{
			check = true;
		}
		else if ((H1 < 5) && (H3 < 2))
		{
			check = true;
		}
		else if ((H1 == 5) && (H2 < 0) && (H3 == 2)) // Через 2 года
		{
			check = true;
		}
		else if ((H1 > 5) && (((H2 < 0) && (H3 == 1)) || H3 == 0)) // Каждый год
		{
			check = true;
		};

		if (check == false)
		{
			fprintf(fp, "%-15s %-15s %-15s %-15d %-2d/%d\n", my_car[i].stamp, my_car[i].state_room, my_car[i].name, my_car[i].release_date.year, my_car[i].date_of_last_inspection.month, my_car[i].date_of_last_inspection.year);
		}
	}
	printf("\nВы проверили данные\n ");
	fclose(fp);
};
void add_record(struct car my_car[], int& count)
{
	printf("\tВВЕДИТЕ ВАШИ ДАННЫЕ НИЖЕ:\n");
	printf("\tВведите марка: ");
	getchar();
	fgets(my_car[count].stamp, SIZE, stdin);
	int len = strlen(my_car[count].stamp);
	my_car[count].stamp[len - 1] = '\0';
	printf("\tВведите гос. номер: ");
	scanf("%s", &my_car[count].state_room);
	printf("\tВведите фамилия владельца: ");
	scanf("%s", &my_car[count].name);
	printf("\tВведите дата выпуска автомобиля (год): ");
	scanf_s("%d", &my_car[count].release_date.year);
	printf("\tВведите дата прохождения последнего техосмотра (месяц/год): ");
	scanf_s("%d/%d", &my_car[count].date_of_last_inspection.month, &my_car[count].date_of_last_inspection.year);
	count++;
};
void delete_record(struct car my_car[], int& count)
{
	char* temp = (char*)malloc(SIZE * sizeof(char));
	int count_copy = count;
	printf("\tВведите гос номер, который вы хотите удалить: ");
	scanf("%s", temp);
	for (int i = 0; i < count; i++)
	{
		if (strcmp(temp, my_car[i].state_room) == 0)
		{
			for (int j = i; j < count - 1; j++)
			{
				strcpy(my_car[j].stamp, my_car[j + 1].stamp);
				strcpy(my_car[j].state_room, my_car[j + 1].state_room);
				strcpy(my_car[j].name, my_car[j + 1].name);
				my_car[j].release_date.year = my_car[j + 1].release_date.year;
				my_car[j].date_of_last_inspection.month = my_car[j + 1].date_of_last_inspection.month;
				my_car[j].date_of_last_inspection.year = my_car[j + 1].date_of_last_inspection.year;
			};
			count--;
		}
	};
	if (count < count_copy)
		printf("\nВы успешно удалили данные \n  ");
	else
		printf("\nНе найти автомобиль, который вы хотите удалить!\n");
	free(temp);
};
void working_data(struct car my_car[], int& count)
{
	while (true)
	{
		int m2 = menu2();
		switch (m2)
		{
		case 1:
			system("cls");
			add_record(my_car, count);
			break;
		case 2:
			system("cls");
			delete_record(my_car, count);
			break;
		case 3:
			system("cls");
			print_data(my_car, count);
			break;
		case 4:
			system("cls");
			int real_month, real_year;
			format_time(&real_month, &real_year);
			check_data(my_car, &count, real_month, real_year);
			break;
		case 5:
			system("cls");
			return;
		}
	}
};

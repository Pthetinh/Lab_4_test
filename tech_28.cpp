#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<locale.h>
#include<time.h>
#include<math.h>
#include<conio.h>
#include<string.h>
#include<windows.h>
#define SIZE 100

struct date
{
	int day;
	int month;
	int year;
}date;

struct product
{
	char name[50];
	int price;
	int quantity;
	struct date production_date;
	struct date expiry_date;
}product;


void format_time(int* month, int* year);
int menu1();
int menu2();
void print_data(struct product your_product[], int count);
void read_data(struct product your_product[], int* count);
void  sort_data(struct product your_product[], int count);
void check_data(struct product your_product[], int* count, int real_day, int real_month, int real_year);
void working_data(struct product your_product[], int& count);
void add_record(struct product your_product[], int& count);
void delete_record(struct product your_product[], int& count);





int main()
{
	setlocale(LC_ALL, " ");

	struct product* your_product = (struct product*)malloc(sizeof(struct product));

	int count = 0;
	while (1)
	{
		int m1 = menu1();

		switch (m1)
		{
		case 1:
			system("cls");
			read_data(your_product, &count);
			break;
		case 2:
			system("cls");
			working_data(your_product, count);
			break;
		case 3:
			return 0;
		}
	}

	free(your_product);
	return 0;
}

int menu1()
{
	printf("\n");
	printf(" 1-Загрузить данные из файла\n");
	printf(" 2-Работа с данными\n");
	printf(" 3-Выход\n");
	printf("Выберите : ");

	int key1;
	scanf_s("%d", &key1);
	return key1;
}

int menu2()
{
	printf("\n");
	printf(" 1-Добавить запись\n");
	printf(" 2-Удалить запись\n");
	printf(" 3-Просмотреть содержимое запись\n");
	printf(" 4-Проверить данных\n");
	printf(" 5-Назад\n");
	printf(" 6-\n");
	printf("Выберите:");
	int key2;
	scanf("%d", &key2);
	return key2;
}

void format_time(int* day, int* month, int* year)
{
	time_t rawtime;
	struct tm* timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	*day = timeinfo->tm_mday;
	*month = timeinfo->tm_mon + 1;
	*year = timeinfo->tm_year + 1900;
}

void print_data(struct product your_product[], int count)
{
	system("cls");
	printf("\n");
	printf("\t%-25s %-15s %-12s %-20s %-17s\n", "НАЗВАНИЕ.ПРОДУКТА    ", "ЦЕНА", "КОЛИЧЕСТВО  ", "ДАТА.ПРОИЗВОДСТВА  ", "СРОК.ГОДНОСТИ");
	for (int i = 0; i < count; i++)
	{
		printf("\t%-25s %-15d %-12d %-20d/%d/%d %-17d/%d/%d%\n", your_product[i].name, your_product[i].price, your_product[i].quantity, your_product[i].production_date.day, your_product[i].production_date.month, your_product[i].production_date.year, your_product[i].expiry_date.day, your_product[i].expiry_date.month, your_product[i].expiry_date.year);
	}
	printf("\n");
}
void read_data(struct product your_product[], int* count)
{
	FILE* f;
	f = fopen("input.txt", "r");
	if (f == NULL)
	{
		printf("Cannot open file!!!\n");
		return;
	}

	while (fscanf(f, "%49[^,], %d, %d, %d/%d/%d, %d/%d/%d\n",
		your_product[*count].name,
		&your_product[*count].price,
		&your_product[*count].quantity,
		&your_product[*count].production_date.day,
		&your_product[*count].production_date.month,
		&your_product[*count].production_date.year,
		&your_product[*count].expiry_date.day,
		&your_product[*count].expiry_date.month,
		&your_product[*count].expiry_date.year) == 9) // Kiểm tra có đọc đủ 9 giá trị
	{
		(*count)++;
	}
	//while (!feof(f))
	//{
	//	fscanf(f, "%40[^,],%d,%d,%d-%d-%d,%d-%d-%d\n", your_product[*count].name);
	//}
	
	fclose(f);
	printf("\nВы успешно прочитали данные из файла\n ");
}

void  sort_data(struct product your_product[], int count)
{
	if (count <= 0) return;

	int i, j;
	for (int i = 0; i < count - 1; i++)
	{
		for (int j = 0; j < count - i - 1; j++)
		{
			if (strcmp(your_product[j + 1].name, your_product[j].name) < 0)
			{
				struct product temp = your_product[j + 1];
				your_product[j + 1] = your_product[j];
				your_product[j] = temp;
			}
		}
	}
}

void check_data(struct product your_product[], int* count, int real_day, int real_month, int real_year)
{
	sort_data(your_product, *count);
	FILE* f;
	f = fopen("output.txt", "w");
	if (f == NULL)
	{
		printf("Cannot open file!!!\n");
		return;
	}
	fprintf(f, "So luong phan tu trong file la: %d\n", *count);
	fprintf(f, "%-15s %-5s %-5s %-20s %-17s\n", "НАЗВАНИЕ.ПРОДУКТА", "ЦЕНА     ", "КОЛИЧЕСТВО", "ДАТА.ПРОИЗВОДСТВА", "СРОК.ГОДНОСТИ");
	int check = 1;
	for (int i = 0; i < *count; i++)
	{
		int check;
		int x1 = real_year - your_product[i].expiry_date.year;
		int x2 = real_month - your_product[i].expiry_date.month;
		int x3 = real_day - your_product[i].expiry_date.day;

		if (x1 == 0)
		{
			if (x2 == 0)
			{
				if (x3 > 0)
				{
					check = 0;
				}
				else
				{
					check = 1;
				}
			}
			else if (x2 > 0)
			{
				check = 0;
			}
			else check = 1;
		}
		else if (x1 > 0)
		{
			check = 0;
		}
		else {
			check = 1;
		}

		if (check == 0) {
			fprintf(f, "\t%-25s %-15d %-12d %-20d/%d/%d %-17d/%d/%d%\n", your_product[i].name, your_product[i].price, your_product[i].quantity, your_product[i].production_date.day, your_product[i].production_date.month, your_product[i].production_date.year, your_product[i].expiry_date.day, your_product[i].expiry_date.month, your_product[i].expiry_date.year);
		}
	}
	printf("\nВы проверили данные\n ");
	fclose(f);
}

void working_data(struct product your_product[], int& count)
{
	while (1)
	{
		int temp = menu2();

		switch (temp)
		{
		case 1:
			system("cls");
			break;
		case 2:
			system("cls");
			break;
		case 3:
			system("cls");
			print_data(your_product, count);
			break;
		case 4:
			system("cls");
			int real_day, real_month, real_year;
			format_time(&real_day, &real_month, &real_year);
			check_data(your_product, &count, real_day, real_month, real_year);
			break;
		case 5:
			system("cls");
			return;
		}
	}
}

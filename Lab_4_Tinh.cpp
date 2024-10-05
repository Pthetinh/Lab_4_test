#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<locale.h>
#include<time.h>
#include<math.h>
#include<conio.h>
#include<string.h>
#include<windows.h>
#define SIZE 100
int sum_money = 0;

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

void add_record(struct product your_product[], int& count);
void delete_record(struct product your_product[], int& count);

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
	printf("Выберите:");
	int key2;
	scanf("%d", &key2);
	return key2;
}

void format_time(int *day, int* month, int* year)
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
	printf("\t%-12s %-8s %-5s %-15s %-15s\n ", "Name", "Price", "Quantity", "ProductionDate", "ExpiryDate");

	for (int i = 0; i < count; i++)
	{
		printf("\t%-12s %-8d %-5d    %02d/%02d/%d      %02d/%02d/%d\n",
			your_product[i].name,
			your_product[i].price,
			your_product[i].quantity,
			your_product[i].production_date.day,
			your_product[i].production_date.month,
			your_product[i].production_date.year,
			your_product[i].expiry_date.day,
			your_product[i].expiry_date.month,
			your_product[i].expiry_date.year);
	}
	printf("\n");
}

void read_data(struct product your_product[], int* count) {
	FILE* f;
	f = fopen("input.txt", "r");
	if (f == NULL) {
		printf("Error! Cannot open file.\n");
		return;
	}

	while (!feof(f))
	{
		int r = fscanf(f, "%s\t%d\t%d\t%d/%d/%d\t%d/%d/%d\n",
			your_product[*count].name,
			&your_product[*count].price,
			&your_product[*count].quantity,
			&your_product[*count].production_date.day,
			&your_product[*count].production_date.month,
			&your_product[*count].production_date.year,
			&your_product[*count].expiry_date.day,
			&your_product[*count].expiry_date.month,
			&your_product[*count].expiry_date.year);
		if (r == 9)
		{
			++*count;
		}
	}

	fclose(f);
	printf("Данные успешно прочитаны из файла\n");
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

void check_data(struct product your_product[], int* count)
{
	sort_data(your_product, *count);
	FILE* f;
	f = fopen("output.txt", "w");
	if (f == NULL)
	{
		printf("Cannot open file!!!\n");
		return;
	}
	fprintf(f, "\t%-12s %-8s %-5s %-15s %-15s\n ", "Name", "Price", "Quantity", "ProductionDate", "ExpiryDate");
	for (int i = 0; i < *count; i++)
	{
		int real_day, real_month, real_year;
		format_time(&real_day, &real_month, &real_year);
		int x1 = real_year - your_product[i].expiry_date.year;
		int x2 = real_month - your_product[i].expiry_date.month;
		int x3 = real_day - your_product[i].expiry_date.day;
		int check;


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

		if (check == 0)
		{
			sum_money += (long long)your_product[i].price * your_product[i].quantity;
			fprintf(f, "\t%-12s %-8d %-5d    %02d/%02d/%d      %02d/%02d/%d\n",
				your_product[i].name,
				your_product[i].price,
				your_product[i].quantity,
				your_product[i].production_date.day,
				your_product[i].production_date.month,
				your_product[i].production_date.year,
				your_product[i].expiry_date.day,
				your_product[i].expiry_date.month,
				your_product[i].expiry_date.year);
		}
	}
	fprintf(f, "Total amount lost: %lld", sum_money);
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
				add_record(your_product, count);
				break;
			case 2:
				system("cls");
				delete_record(your_product, count);
				break;
			case 3:
				system("cls");
				print_data(your_product, count);
				break;
			case 4:
				system("cls");
				int real_day, real_month, real_year;
				format_time(&real_day, &real_month, &real_year);
				check_data(your_product, &count);
				break;
			case 5:
				system("cls");
				return;
		}
	}
}

int main()
{
	setlocale(LC_ALL, " ");
	struct product* your_product = (struct product*)malloc(SIZE * sizeof(struct product));
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
			sum_money = 0;
			working_data(your_product, count);
			break;
		case 3:
			return 0;
		}
	}

	free(your_product);
	return 0;
}

void add_record(struct product  your_product[], int& count)
{
	printf("ВВЕДИТЕ ВАШИ ДАННЫЕ НИЖЕ:\n");
	printf("Введите Название товара: ");
	getchar();
	fgets(your_product[count].name, SIZE, stdin);
	int length = strlen(your_product[count].name);
	your_product[count].name[length - 1] = '\0';
	printf("Введите Цена за единницу:");
	scanf("\t%d", &your_product[count].price);
	printf("Введите Количество: ");
	scanf("\t%d", &your_product[count].quantity);
	printf("Введите Дата изготовления(ДД.ММ.ГГ): ");
	scanf("\t%d/%d/%d", 
		&your_product[count].production_date.day,
		&your_product[count].production_date.month, 
		&your_product[count].production_date.year);
	printf("Введите Срок Годности(ДД.ММ.ГГ): ");
	scanf("\t%d/%d/%d",
		&your_product[count].expiry_date.day,
		&your_product[count].expiry_date.month,
		&your_product[count].expiry_date.year);
	++count;
}

void delete_record(struct product your_product[], int& count)
{
	char* temp = (char*)malloc(SIZE * sizeof(char));
	int count_copy = count;
	printf("\tВведите Название товара, который хотите удалить: ");
	scanf("%s", temp);
	for (int i = 0; i < count; i++)
	{
		if (strcmp(temp, your_product[i].name) == 0)
		{
			for (int j = i; j < count - 1; j++)
			{
				strcpy(your_product[j].name, your_product[j + 1].name);
				your_product[j].price = your_product[j + 1].price;
				your_product[j].quantity = your_product[j + 1].quantity;
				your_product[j].production_date.day = your_product[j + 1].production_date.day;
				your_product[j].production_date.month = your_product[j + 1].production_date.month;
				your_product[j].production_date.year = your_product[j + 1].production_date.year;
				your_product[j].expiry_date.day = your_product[j + 1].expiry_date.day;
				your_product[j].expiry_date.month = your_product[j + 1].expiry_date.month;
				your_product[j].expiry_date.year = your_product[j + 1].expiry_date.year;
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
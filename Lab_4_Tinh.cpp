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
	char name[100];
	int price;
	int quantity;
	struct date production_date;
	struct date expiry_date;
};

typedef struct product product;

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

void print_data(product your_product[], int count)
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
void read_data(product your_product[], int *count)
{
	FILE* f;
	f = fopen("Products.docx", "r");

	fclose(f);
}

int main()
{
	setlocale(LC_ALL, " ");
	FILE* f;

	f = fopen("Products.docx", "r");
	if (f == NULL)
	{
		printf("Cannot open file!");
	}
	else
	{
		FILE* f2;
		product a[1000];
		int n = 0;
		f2 = fopen("Output_products.docx", "w");

		while (true)
		{
			char name[100];
			if (fgets(name, 100, f2) == NULL)
			{
				break;
			}
			name[strlen(name) - 1] = '\0';
			fscanf(f, "%s", name);
			int price, quantity;
			fscanf(f, "%d%d", &price, &quantity);
			fgetc(f);
			strcpy(a[n].name, name);
			a[n].price = price;
			a[n].quantity = quantity;
			++n;
		}

	}


	fclose(f);
	return 0;
}
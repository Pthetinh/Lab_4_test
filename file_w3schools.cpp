#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<locale.h>
#include<time.h>
#include<math.h>
#include<conio.h>
#include<string.h>
#include<windows.h>
#define SIZE 100

struct date {
	int day;
	int month;
	int year;
}date;

struct product {
	char name[50];
	int price;
	int quantity;
	struct date production_date;
	struct date expiry_date;
}product;

void format_time(int* day,int* month, int* year);

int main()
{
	setlocale(LC_ALL, " ");
	struct product* your_product = (struct product*)malloc(SIZE * sizeof(struct product));

	FILE* f;
	f = fopen("input.txt", "r");
	if (f == NULL)
	{
		printf("Cannot open file!!!\n");
		free(your_product);
		getchar();
		return 0;
	}
	int count = 0;
	
	while (!feof(f))
	{
		int r = fscanf(f, "%s\t%d\t%d\t%d/%d/%d\t%d/%d/%d\n",
		your_product[count].name,
		&your_product[count].price,
		&your_product[count].quantity,
		&your_product[count].production_date.day,
		&your_product[count].production_date.month,
		&your_product[count].production_date.year,
		&your_product[count].expiry_date.day,
		&your_product[count].expiry_date.month,
		&your_product[count].expiry_date.year);
		if (r == 9)
		{
			++count;
		}
	}



	for (int i = 0; i < count; i++)
	{
		printf("%s  %d  %d  %d/%d/%d  %d/%d/%d\n",
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

	FILE* fp;
	fp = fopen("output.txt", "w");
	if (fp == NULL)
	{
		printf("Cannot open file!!!\n");
		return 0;
	}

	fprintf(fp, "\t%-12s %-8s %-5s %-15s %-15s\n ", "Name", "Price", "Quantity","Production_date", "Expiry_date");
	long long sum_money = 0;
	for (int i = 0; i < count; i++)
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
			fprintf(fp, "\t%-12s %-8d %-5d    %d/%d/%d        %d/%d/%d\n",
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
	fprintf(fp,"Total amount lost: %lld", sum_money);
	fclose(fp);

	free(your_product);
	fclose(f);
	return 0;
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
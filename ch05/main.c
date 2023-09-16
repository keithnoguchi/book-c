/* SPDX-License-Identifier: GPL-2.0 */
#include <stdio.h>

static char daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
};

static int day_of_year(int, int, int);
static void month_day(int, int, int *, int *);

int main(void)
{
	int year, month, day;
	int ret, *rmonth, *rday;

	year = 2023;
	month = 9;
	day = 15;

	ret = day_of_year(year, month, day);
	printf("%04d/%02d/%02d is %d days of the year.\n",
	       year, month, day, ret);

	rmonth = &month;
	rday = &day;
	month_day(year, ret, rmonth, rday);
	printf("%d days of year %04d is %04d/%02d/%02d\n",
	       ret, year, year, *rmonth, *rday);

	return 0;
}

static int day_of_year(int year, int month, int day)
{
	int i, leap;

	leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
	for (i = 1; i < month; i++)
		day += daytab[leap][i];

	return day;
}

static void month_day(int year, int day_of_year, int *month, int *day)
{
	int i, leap;

	leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
	for (i = 1; day_of_year > daytab[leap][i]; i++)
		day_of_year -= daytab[leap][i];

	*month = i;
	*day = day_of_year;
}

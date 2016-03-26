/*
OVERVIEW: You are given a bank statement where transactions are ordered by date. Write a function that finds the number of transactions in that statement after a given date.
-- find the count of numbers greater than a given number in a sorted array.
E.g.: Input: A[3] = { { 10, "09-10-2003", "First" }, { 20, "19-10-2004", "Second" }, { 30, "03-03-2005", "Third" } };
date = "19-10-2004"
Output: 1 (as there is only one transaction { 30, "03-03-2005", "Third" })

INPUTS: One bank statement (array of transactions) and date.

OUTPUT: Return the number of transactions in that statement after a given date.

ERROR CASES: Return NULL for invalid inputs.

NOTES:
*/
int isOlder(char*, char*);
int datecheck(int, int, int);
int valid(char*, char*);
struct transaction {
	int amount;
	char date[11];
	char description[20];
};

int countGreaterNumbers(struct transaction *Arr, int len, char *date) {
	int i,count=0,check;
	for (i = 0; i < len; i++)
	{
		check = isOlder(Arr[i].date, date);
		if (check == -1)
			return -1;
		if (check == 2)
			count++;
	}
	return count;
}
int isOlder(char *dob1, char *dob2) {
	if ((dob1[2] != '-') || (dob2[2] != '-') || (dob1[5] != '-') || (dob2[5] != '-'))
		return -1;
	else{
		return(valid(dob1, dob2));
	}
}
int valid(char *d1, char *d2)
{
	int i = 9, a1[3], a2[3], k = 0, t = 1, p = 0, c = 0;
	while (i >= 0)
	{
		if (d1[i] != '-')
		{
			if ((d1[i] >= 48 && d1[i] <= 57) && (d2[i] >= 48 && d2[i] <= 57))
			{
				if (t == 1)
				{
					k = k + ((int)d1[i] - 48);
					p = p + ((int)d2[i] - 48);
					t++;

				}
				else if (t == 2)
				{
					k = k + 10 * ((int)d1[i] - 48);
					p = p + 10 * ((int)d2[i] - 48);
					t++;
				}
				else if (t == 3)
				{
					k = k + 100 * ((int)d1[i] - 48);
					p = p + 100 * ((int)d2[i] - 48);
					t++;
				}
				else{
					k = k + 1000 * ((int)d1[i] - 48);
					p = p + 1000 * ((int)d2[i] - 48);
					t++;
				}
			}
			else
				return -1;
		}
		else{
			a1[c] = k;
			a2[c] = p;
			c++;
			k = 0; p = 0;
			t = 1;
		}
		i--;
	}
	a1[c] = k;
	a2[c] = p;
	c = datecheck(a1[2], a1[1], a1[0]);
	if (c == 0)
		return -1;
	c = datecheck(a2[2], a2[1], a2[0]);
	if (c == 0)
		return -1;
	for (c = 0; c <3; c++)
	{
		if (a2[c] > a1[c])
			return 1;
		if (a1[c] > a2[c])
			return 2;
	}
	return 0;
}
int datecheck(int date, int month, int year)
{
	if (date<1 || date>31 || month<1 || month>12 || year<0)
		return 0;
	else if (((month == 4) || (month == 6) || (month == 9) || (month == 11)) && (date <= 30))
	{
		return 1;
	}
	else if ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && (date <= 31))
	{
		return 1;
	}
	else if (month == 2)
	{
		if (year % 4 != 0 && date <= 28)
			return 1;
		else if (year % 4 == 0 && date <= 29)
			return 1;
		else return 0;
	}
	else return 0;
}

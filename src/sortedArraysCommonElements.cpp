/*
OVERVIEW: You are given 2 bank statements that are ordered by date. 
Write a function that returns dates common to both statements
(ie both statements have transactions in these dates).
E.g.: Input: A[3] = { { 10, "09-10-2003", "First" }, { 20, "19-10-2004", "Second" }, { 30, "03-03-2005", "Third" } };
B[3] = { { 10, "09-10-2003", "First" }, { 220, "18-01-2010", "Sixth" }, { 320, "27-08-2015", "Seventh" } };
Output: { { 10, "09-10-2003", "First" } }

INPUTS: Two bank statements (array of transactions).

OUTPUT: Transactions having same dates.


ERROR CASES: Return NULL for invalid inputs.

NOTES:
*/

#include <iostream>
int Older1(char*, char*);
int dateCheck1(int, int, int);
int Valid1(char*, char*);
struct transaction {
	int amount;
	char date[11];
	char description[20];
};

struct transaction * sortedArraysCommonElements(struct transaction *A, int ALen, struct transaction *B, int BLen) {
	int n, i=0,equal,j=0,k=0;
	struct transaction *result;
	if (A == NULL || B == NULL || ALen <= 0 || BLen <= 0)
		return NULL;
	result = (struct transaction*)malloc((ALen + BLen)*sizeof(struct transaction));
	//result = NULL;
	if (ALen <= BLen)
		n = ALen;
	else
		n = BLen;
	for (j = 0; j < n;)
	{
		if (Older1(A[j].date, B[k].date) == 1)
			j++;
		else if (Older1(A[j].date, B[k].date) == 2)
			k++;
		else{
			result[i] = A[j];
			i++;
			j++; k++;
		}
	}
	if (i == 0)
		return NULL;
	return result;
}
int Older1(char *dob1, char *dob2) {
	if ((dob1[2] != '-') || (dob2[2] != '-') || (dob1[5] != '-') || (dob2[5] != '-'))
		return -1;
	else{
		return(Valid1(dob1, dob2));
	}
}
int Valid1(char *d1, char *d2)
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
	c = dateCheck1(a1[2], a1[1], a1[0]);
	if (c == 0)
		return -1;
	c = dateCheck1(a2[2], a2[1], a2[0]);
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
int dateCheck1(int date, int month, int year)
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

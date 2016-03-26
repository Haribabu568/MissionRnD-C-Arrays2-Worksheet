/*
OVERVIEW: You are given 2 bank statements that are ordered by date - 
Write a function that produces a single merged statement ordered by dates.
E.g.: Input: A[3] = { { 10, "09-10-2003", "First" }, { 20, "19-10-2004", "Second" }, { 30, "03-03-2005", "Third" } };
B[2] = { { 10, "09-10-2003", "First" }, { 220, "18-01-2010", "Sixth" } };
Output: { { 10, "09-10-2003", "First" }, { 10, "09-10-2003", "First" }, { 20, "19-10-2004", "Second" },  30, "03-03-2005", "Third" }, { 220, "18-01-2010", "Sixth" } }

INPUTS: Two bank statements (array of transactions).

OUTPUT: Combined statement ordered by transaction date.

ERROR CASES: Return NULL for invalid inputs.

NOTES:
*/

#include <iostream>
int Older(char*, char*);
int dateCheck(int, int, int);
int Valid(char*, char*);
struct transaction {
	int amount;
	char date[11];
	char description[20];
};

struct transaction * mergeSortedArrays(struct transaction *A, int ALen, struct transaction *B, int BLen) {
	int i=0, j=0, k=0,small=0;
	struct transaction *result;
	if (A == NULL || B == NULL || ALen <= 0 || BLen <= 0)
		return NULL;
	result = (struct transaction*)malloc((ALen + BLen)*sizeof(struct transaction));
	while (i < ALen + BLen)
	{
		if (j < ALen && k < BLen)
		{
			small = Older(A[j].date, B[k].date);
			if (small == -1)
				return NULL;
			else if (small == 1)
			{
				result[i] = A[j];
				j++;
			}
			else if (small == 0)
			{
				result[i] = A[j]; 
				j++;
				i++;
				result[i] = B[k];
				k++;
			}
			else
			{
				result[i] = B[k];
				k++;
			}
			i++;
		}
		else if (j >= ALen)
		{
			for (; k < BLen;)
			{
				result[i] = B[k];
				i++;
				k++;
			}
		}
		else if(k>=BLen){
			for (; j < ALen;)
			{
				result[i] = A[j];
				i++;
				j++;
			}
		}
	}
	return result;
}
int Older(char *dob1, char *dob2) {
	if ((dob1[2] != '-') || (dob2[2] != '-') || (dob1[5] != '-') || (dob2[5] != '-'))
		return -1;
	else{
		return(Valid(dob1, dob2));
	}
}
int Valid(char *d1, char *d2)
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
	c = dateCheck(a1[2], a1[1], a1[0]);
	if (c == 0)
		return -1;
	c = dateCheck(a2[2], a2[1], a2[0]);
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
int dateCheck(int date, int month, int year)
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

/* FinanceCalculator.c -- C implementation of FinanceCalculator.java
 *
 * Prompts the user for desired financial formulas and relevent data and 
 * calculates the present value, future value, interest, and annuity payments.
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float simpleInterestCalc(float, float, float);
float compInterestCalc(char, float, float, float, float);
void annuitiesCalc(void);
void menu(void);
void flush(void);
float getfloat(void);

int main(void)
{
	char choice;
	unsigned i;
	const int compChoices[7] = {1,2,4,12,26,56,365};
	float investment, rate, years, interest, comp;
	_Bool isComp = 0;

	puts("FINANCE CALCULATOR\n");

	menu();
	while ((choice = getchar()) != 'q')
	{
		flush();

		switch(choice)
		{
			case '1' : puts("\nSIMPLE INTEREST CALCULATOR\n");

				   puts("Enter value of money to invest: ");
				   investment = getfloat();
				   puts("Enter annual interest rate percentage: ");
				   rate = getfloat();
				   puts("Enter number of years to invest: ");
				   years = getfloat();

				   interest = simpleInterestCalc(investment, rate, years);
				   printf("\nFuture value = $%.2f\nInterest = $%.2f\n\n",
						   investment + interest, interest);
				   flush();
				   break;
			case '2' : puts("\nCOMPOUND INTEREST CALCULATOR\n");

				   puts("Choose a calculation:\n"	// prompt for calculation
				   	"1. Find the future value of money invested now.\n"
					"2. Find the initial value of money that has been invested.");
				   while ((choice = getchar()) < '1' || choice > '2')
				   {
					   puts("Invalid selection. Choose 1 or 2:");
					   flush();
				   }
				   getchar();

				   if (choice == '1')		// prompt for investment
					   puts("Amount to invest:");
				   else
					   puts("Money after investment:");
				   investment = getfloat();

				   puts("Rate percentage:");
				   rate = getfloat();

				   puts("Compound period:\n"
					"Annually      -   1\n"
					"Semi-Annually -   2\n"
					"Quarterly     -   4\n"
					"Monthly       -  12\n"
					"Bi-Weekly     -  26\n"
					"Weekly        -  52\n"
					"Daily         - 365");
				   while (scanf("%f", &comp) != 1 || !isComp)
				   {
					   for (i = 0; i < sizeof compChoices / sizeof(int); i++)
						   if (comp == compChoices[i])
							   isComp = 1;
					   if (isComp)
						   break;
					   puts("Invalid selection.");
					   flush();
				   }

				   if (choice == '1')
					   puts("Years to invest:");
				   else
					   puts("Years invested:");
				   years = getfloat();

				   interest = compInterestCalc(choice, investment, rate, comp, years);
				   if (choice == '1')
					   printf("\nFuture value: $%.2f\n"
						  "Interest:     $%.2f\n\n", investment + interest, interest);
				   else
					   printf("\nPresent value: $%.2f\n"
						  "Interest:     $%.2f\n\n", interest, investment - interest);
				   flush();
				   break;
			case '3' : annuitiesCalc();
				   break;
			default  : puts("\nInvalid selection.\n");
		}
		menu();
	}
	puts("\nDone");

	return 0;
}

float simpleInterestCalc(float investment, float intRate, float years)	// simple interest formula
{
	return investment * (intRate / 100) * years;
}

float compInterestCalc(char choice, float inv, float rate, float cmpPeriod, float years)	// compound interest formula
{
	float i = (rate / 100) / cmpPeriod;
	float n = cmpPeriod * years;
	float z = pow(i+1, n);

	if (choice == '1')
		return inv * z;
	else if (choice == '2')
		return inv / z;
	else
	{
		puts("Programming error in comInterestCalc()!");
		exit(EXIT_FAILURE);
	}
}

void annuitiesCalc(void)	// annuity payments formula
{
	puts("\nANNUITY PAYMENT CALCULATOR\n");
	return;
}

void menu(void)
{
	puts("Pick a formula (q to quit):\n"
	     "1. Simple Interest\t2. Compound Interest\t3. Annuities");

	return;
}	

void flush(void)		// flush input buffer
{
	while (getchar() != '\n')
		continue;

	return;
}

float getfloat()
{
	float fl;
	char ch;

	while (scanf("%f", &fl) != 1)
	{
		while ((ch = getchar()) != '\n')
			putchar(ch);
		puts(" is not a number.");
	}

	return fl;
}

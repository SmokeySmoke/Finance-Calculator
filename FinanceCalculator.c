/* FinanceCalculator.c -- C implementation of FinanceCalculator.java
 *
 * Prompts the user for desired financial formulas and relevent data and 
 * calculates the present value, future value, interest, and annuity payments.
 */
#include <stdio.h>

float simpleInterestCalc(float, float, float);
void compInterestCalc(void);
void annuitiesCalc(void);
void menu(void);
void flush(void);
float getfloat(void);

int main(void)
{
	char choice;
	float toInvest, rate, years, interest;

	puts("FINANCE CALCULATOR\n");

	menu();
	while ((choice = getchar()) != 'q')
	{
		switch(choice)
		{
			case '1' : puts("\nSIMPLE INTEREST CALCULATOR\n");

				   puts("Enter value of money to invest: ");
				   toInvest = getfloat();
				   puts("Enter annual interest rate percentage: ");
				   rate = getfloat();
				   puts("Enter number of years to invest: ");
				   years = getfloat();

				   interest = simpleInterestCalc(toInvest, rate, years);
				   printf("\nInvestment = %.2f\nInterest Rate = %.2f%%\nYears to Invest = %.2f\n\n",
						   toInvest, rate, years);
				   printf("Future value = %.2f\nInterest = %.2f\n\n",
						   toInvest + interest, interest);
				   break;
			case '2' : compInterestCalc();
				   break;
			case '3' : annuitiesCalc();
				   break;
			default  : puts("\nInvalid selection.\n");
		}
		flush();
		menu();
	}
	puts("\nDone");

	return 0;
}

float simpleInterestCalc(float investment, float intRate, float years)	// simple interest formula
{
	return investment * (intRate / 100) * years;
}

void compInterestCalc(void)	// compound interest formula
{
	puts("\nCOMPOUND INTEREST CALCULATOR\n");
	return;
}

void annuitiesCalc(void)	// annuity payments formula
{
	puts("\nANNUITY PAYMENT CALCULATOR\n");
	return;
}

void menu(void)
{
	puts("Choose a calculation (q to quit):\n"
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

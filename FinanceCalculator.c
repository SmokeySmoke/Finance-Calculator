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
float annuitiesCalc(char, char, float, float, float, float);
void menu(void);
void flush(void);
float getfloat(void);

int main(void)
{
	char choice;
	unsigned i;
	const int compChoices[7] = {1,2,4,12,26,56,365};
	float investment, rate, years, interest, comp, pay, value;
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
			case '3' : puts("ANNUITY PAYMENT CALCULATOR\n"
					"1. What an annuity will be worth in the future\n"
					"2. What the principle value of an annuity is worth\n"
					"3. What regular payments in an annuity will cost per payment\n");
				   while ((choice = getchar()) < '1' || choice > '3')
				   {
					   puts("Invalid selection. Choose 1, 2 or 3:");
					   flush();
				   }
				   getchar();

			           char valchoice;
				   if (choice == '3')
				   {
					   puts("Choose the value you have available:\n"
					        "1. Future value\n"
						"2. Present value");
					   while ((valchoice = getchar()) != '1' && valchoice != '2')
					   {
						   puts("Invalid selection. Choose 1 or 2:");
						   flush();
					   }
					   if (valchoice == '1')
						   printf("Future value: $");
					   else if (valchoice == '2')
						   printf("Present value: $");
					   else
					   {
						   puts("Programming error in Annuity value choice!");
						   exit(EXIT_FAILURE);
					   }
				   } else 
				   {
					valchoice = '0';
				   	puts("Cost per payment:");
				   }
				   pay = getfloat();

				   puts("Rate:");
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


				   value = annuitiesCalc(choice, valchoice, pay, rate, comp, years);
				   putchar('\n');
				   if (choice == '1')
					   printf("Future value: $%.2f\n", value);
				   else if (choice == '2')
					   printf("Present value: $%.2f\n", value);
				   else if (choice == '3')
					   printf("Payment cost: $%.2f\n", value);
				   else
					   exit(EXIT_FAILURE);
				   putchar('\n');
				   flush();
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

float annuitiesCalc(char choice, char valchoice, float pay, float rate, float compP, float years)	// annuity payments formula
{
	float i = (rate/100) / compP;
	float n = compP * years;
	float c = pow(i+1, choice == '2' || valchoice == '2' ? -n : n);

	if (choice == '3')
		return pay * (i / (valchoice == '1' ? c-1 : 1-c));
	else
		return pay * ((choice == '1' ? c-1 : 1-c) / i);
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

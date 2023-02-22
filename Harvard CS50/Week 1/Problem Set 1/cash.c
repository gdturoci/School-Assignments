#include <cs50.h>
#include <stdio.h>

int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);

int main(void) {
    // Ask how many cents the customer is owed
    int cents = get_cents();

    // Calculate the number of quarters to give the customer
    int quarters = calculate_quarters(cents);
    cents -= quarters*25;

    // Calculate the number of dimes to give the customer
    int dimes = calculate_dimes(cents);
    cents -= dimes*10;

    // Calculate the number of nickels (and subsequently pennies) to give the customer
    int nickels = calculate_nickels(cents);
    cents -= nickels*5;
    int pennies = cents;
    
    // Sum coins
    int coins = quarters + dimes + nickels + pennies;

    // Print total number of coins to give the customer
    printf("%i\n", coins);
}

int get_cents(void) {
    int cents = -1;
    while (cents < 0)
        cents = get_int("Change owed: ");
    
    return cents;
}

int calculate_quarters(int cents) {

    int quarters = 0;
    if (cents > 24)
        quarters = cents/25;
    
    return quarters;
}

int calculate_dimes(int cents) {
    int dimes = 0;
    if (cents > 9)
        dimes = cents/10;
    
    return dimes;
}

int calculate_nickels(int cents) {
    int nickels = 0;
    if (cents > 4)
        nickels = cents/5;
   
    return nickels;
}
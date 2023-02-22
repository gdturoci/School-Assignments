#include <cs50.h>
#include <stdio.h>

int main(void) {
    //Prompt for start size
    int start_pop = 0;
    while (start_pop < 9) {
        start_pop = get_int("Start size: ");
    }

    //Prompt for end size
    int end_pop = 0;
    while (end_pop < start_pop) {
        end_pop = get_int("End size: ");
    }

    //Calculate number of years until we reach threshold
    int curr_pop = start_pop;
    int num_years = 0;
    int llamas_born;
    int llamas_die;
    while (curr_pop < end_pop) {
        //Llamas born
        llamas_born = curr_pop/3;

        //Llamas die
        llamas_die = curr_pop/4;

        //New current population
        curr_pop += llamas_born - llamas_die;

        //Iterate year
        ++num_years;
    }


    //Print number of years
    printf("Years: %d\n", num_years);

    return 0;
}

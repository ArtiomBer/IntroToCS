/***********
* Artiom Berengard
* ass01
***********/

#include <stdio.h>
#include <math.h>

void hello() {
    printf("\"hello \\/\\/orld %%d\\n\"\n");
}

void distance() {
    int x1, y1, x2, y2;
    printf("Enter x1:\n");
    scanf("%d", &x1);
    printf("Enter y1:\n");
    scanf("%d", &y1);
    printf("Enter x2:\n");
    scanf("%d", &x2);
    printf("Enter y2:\n");
    scanf("%d", &y2);

    int conculateX = ((x2 - x1)*(x2 - x1));
    int conculateY = ((y2 - y1)*(y2 - y1));
    int addition = (conculateX + conculateY);
    double rootConculation = sqrt(addition);
    printf("The distance between the points is: %.4lf\n", rootConculation);
}


void conversions() {
    double number;
    printf("Please enter nm:\n");
    scanf("%lf", &number);

    printf("%010.4lf km\n%010.4lf m\n%010.4lf dm\n%010.4lf cm\n%010.4lf mm\n%010.0lf nm\n", \
        number * 1e-12, number * 1e-9, number * 1e-8, number * 1e-7, number * 1e-6, number);
}

void baking() {
    int enterHour, enterMinutes, enterSeconds;
    int secondsInAMinute, MinutesInAnHour = 60;

    printf("Please enter the baking time: [hh:mm:ss]\n");
    scanf("%02d:%02d:%02d",&enterHour,&enterMinutes, &enterSeconds);
    int bakeHour, bakeMinutes, bakeSeconds;

    printf("When did you put the cake into the oven? [hh:mm:ss]\n");
    scanf("%02d:%02d:%02d", &bakeHour, &bakeMinutes, &bakeSeconds);
    /*Conculating the time given and printing the time you will need to take the cake out*/
    int endSeconds = (enterSeconds+bakeSeconds)%60;
    int endMinutes = (((enterMinutes + bakeMinutes) % 60 + ((enterSeconds+bakeSeconds)/60))%60);
    int endHour = ((((enterHour + bakeHour) % 24) + ((enterMinutes + bakeMinutes+ ((enterSeconds + bakeSeconds) / 60)) / 60))%24);
    printf("The cake will be ready at %02d:%02d:%02d o'clock.",endHour,endMinutes,endSeconds);
}

void main() {
    hello();
    distance();
    conversions();
    baking();
}

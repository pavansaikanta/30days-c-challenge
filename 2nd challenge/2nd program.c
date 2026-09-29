//TripCalc: A student is planning a road trip. Write a C program to read the total distance to be travelled (in kilometres), the vehicle's mileage (kilometres per litre), and the current fuel price per litre. Calculate and display the amount of fuel required for the trip and the total fuel cost
#include <stdio.h>
int main()
{
float distance, mileage, price,fuel, cost;
printf("Enter distance in km: ");
scanf("%f", &distance);

printf("Enter mileage in km/litre: ");
scanf("%f", &mileage);

printf("Enter fuel price per litre: ");
scanf("%f", &price);

fuel = distance / mileage;
cost = fuel * price;

printf("Fuel required = %.2f litres\n", fuel);
printf("Total fuel cost = Rs. %.2f\n", cost);

return 0;
}

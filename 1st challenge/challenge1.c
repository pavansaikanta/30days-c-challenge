//a student has marks for five subjects.write a c program to read the marks of all five subjects and calculate total marks,average,percentage.display all three results clearly
#include<stdio.h>
int main(){
int m1,m2,m3,m4,m5;
float total,average,percentage;
printf("Enter the marks for 5 subjects: ");
scanf("%d %d %d %d %d",&m1, &m2, &m3, &m4, &m5);
total =m1+m2+m3+m4+m5;
average = total/5;
percentage = (total/500)*100;
printf("Total marks = %f\n",total);
printf("Average marks = %f\n",average);
printf("percentage = %f\n",percentage);
return 0;
}

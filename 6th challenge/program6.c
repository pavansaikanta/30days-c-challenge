//6th challenge
#include<stdio.h>
int main(){
int n,a[12],i,j;
int sum=0,max,min,secondmax,peaks=0,longest=1,current=1,k,k1,temp,r,d,divcount=0;
float average;
do
{
printf("Enter the no of readings (5 to 12): ");
scanf("%d",&n);

if (n<5 || n>12)
printf("Invalid input.Try again.\n");
}
while(n<5 || n>12);

printf("Enter %d readings:\n",n);
for(i=0;i<n;i++)
{
printf("Enter readings %d: ",i+1);
scanf("%d",&a[i]);
while(a[i]<0 || a[i]>1000)
{
printf("INVALID READINGS.Enter again: ");
scanf("%d",&a[i]);
}
}
printf("\nORIGINAL readings: ");
for(i=0;i<n;i++)
{
printf("%d ",a[i]);
}
printf("\n");
max =a[0];
min=a[0];
for(i=0;i<n;i++)
{
sum=sum+a[i];
if(a[i]>max)
max=a[i];
if(a[i]<min)
min=a[i];
}
average=(float)sum/n;
printf("\nSum=%d\n",sum);
printf("Average=%.2f\n",average);
printf("Maximum=%d\n",max);
printf("Minimum=%d\n",min);

secondmax=-1;
for(i=0;i<n;i++)
{
if(a[i]<max && a[i]>secondmax)
{
secondmax=a[i];
}
}
if(secondmax== -1)
printf("there is no second largest distinct value\n");
else
printf("SECOND largest distinct value is %d\n",secondmax);

for(i=1;i<n-1;i++)
{
if(a[i]>a[i-1] && a[i]>a[i+1])
{
peaks++;
}
}
printf("number of local peaks=%d\n",peaks);
for(i=1;i<n;i++)
{
if(a[i]>a[i-1])
{
current++;
if(current>longest)
{
longest=current;
}
}
else
{current=1;
}
}
printf("longest increasing run=%d\n",longest);

printf("\nEnter rotation amount:");
scanf("%d",&k);
k1=((k%n)+n)%n;
for(i=0;i<k1;i++)
{
temp=a[n-1];
for(int j=n-1;j>0;j--)
{
a[j]=a[j-1];
}
a[0]=temp;
}
printf("\nRotated array:");
for(i=0;i<n;i++)
{
printf("%d",a[i]);
}
printf("\n");
printf("Enter the last two digits of your registration number: ");
scanf("%d", &r);
d=(r%9)+1;
for(i=0;i<n;i++)
{
if(a[i]%d==0){
divcount++;
}
}
printf("Divisor=%d\n",d);
printf("Number of divisible values=%d\n",divcount);
return 0;
}

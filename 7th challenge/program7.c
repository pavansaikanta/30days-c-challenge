#include<stdio.h>
int main(){
int n,a[15],i,j,count,missingnum=0,duplicatenum=0,misscount=0,duplicatecount=0,outoforder=0,target,tcount=0,r,valid=1;
do{
printf("Enter the no of tickets (5 to 15): ");
scanf("%d",&n);
if(n<5 || n>15){
printf("INVALID INPUT.\nEnter again:");
}
}while(n<5 || n>15);

for(i=0;i<n;i++){
do{
printf("Enter ticket num %d: ",i+1);
scanf("%d",&a[i]);
if(a[i]<1 || a[i]>n){
printf("you entered invalid ticket num.try again.\n");
}
}while(a[i]<1 || a[i]>n);
}
printf("Original sequence: ");
for(i=0;i<n;i++){
printf("%d ",a[i]);
}
printf("\n");
for(i=1;i<=n;i++){
count=0;
for(j=0;j<n;j++){
if(a[j]==i){
count++;
}
}
if(count==0){
missingnum=i;
misscount++;
}
else if(count==2){
duplicatenum=i;
duplicatecount++;
}
else if(count!=1){
valid=0;
}
}
if(misscount!=1||duplicatecount!=1)
{
valid=0;
}
if(valid==0)
{
printf("Invalid scan log.\n");
return 0;
}
printf("Duplicated ticket ID: %d\n",duplicatenum);
printf("Missing ticket ID: %d\n",missingnum);
for(i=0;i<n;i++)
{
for(j=i+1;j<n;j++)
{
if(a[i]>a[j])
{
outoforder++;
}
}
}
printf("Total outoforder pairs: %d\n",outoforder);
printf("Enter last two digits of registration number: ");
scanf("%d",&r);
target=(r%n)+1;
printf("Target ticket num: %d\n",target);
printf("Target num positions: ");
for(i=0;i<n;i++)
{
if(a[i]==target)
{
printf("%d ",i+1);
tcount++;
}
}
printf("Target num occurrence count: %d\n",tcount);
return 0;
}

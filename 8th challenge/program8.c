#include <stdio.h>
int main(){
int a[6][6],n,t,i,j,sum;
int mr=-1,mc=-1,max=0;
int d1=0,d2=0,b=0,count=0,hot=0;
printf("Enter grid size: ");
scanf("%d",&n);
while(n<3 || n>6){
printf("Enter size between 3 and 6: ");
scanf("%d",&n);
}
printf("Enter risk scores:\n");
for(i=0;i<n;i++){
for(j=0;j<n;j++){
scanf("%d",&a[i][j]);
while(a[i][j]<0 || a[i][j]>100){
printf("Enter score between 0 and 100: ");
scanf("%d",&a[i][j]);
}
}
}
printf("Enter threshold: ");
scanf("%d",&t);
while(t<1 || t>100){
printf("Enter threshold between 1 and 100: ");
scanf("%d",&t);
}
printf("\nGrid:\n");
for(i=0;i<n;i++){
for(j=0;j<n;j++){
printf("%4d",a[i][j]);
}
printf("\n");
}
for(i=0;i<n;i++){
sum=0;
for(j=0;j<n;j++){
sum=sum+a[i][j];
}
if(sum>mr){
mr=sum;
}
}
printf("\nHighest row total: %d\nRows: ",mr);
for(i=0;i<n;i++){
sum=0;
for(j=0;j<n;j++){
sum=sum+a[i][j];
}
if(sum==mr){
printf("%d ",i+1);
}
}
for(j=0;j<n;j++){
sum=0;
for(i=0;i<n;i++){
sum=sum+a[i][j];
}
if(sum>mc){
mc=sum;
}
}
printf("\nHighest column total: %d\nColumns: ",mc);
for(j=0;j<n;j++){
sum=0;
for(i=0;i<n;i++){
sum=sum+a[i][j];
}
if(sum==mc){
printf("%d ",j+1);
}
}
for(i=0;i<n;i++){
for(j=0;j<n;j++){
if(a[i][j]>max){
max=a[i][j];
}
if(a[i][j]>=t){
count++;
}
}
}
printf("\nHighest score: %d\n",max);
printf("Positions:\n");
for(i=0;i<n;i++){
for(j=0;j<n;j++){
if(a[i][j]==max){
printf("Row %d Column %d\n",i+1,j+1);
}
}
}
printf("Cells meeting threshold: %d\n",count);
for(i=0;i<n;i++){
d1=d1+a[i][i];
d2=d2+a[i][n-1-i];
}
printf("Main diagonal: %d\n",d1);
printf("Secondary diagonal: %d\n",d2);
if(d1==d2){
printf("Diagonals are balanced.\n");
}
else{
printf("Diagonals are not balanced.\n");
}
for(i=0;i<n;i++){
for(j=0;j<n;j++){
if(i==0 || i==n-1 || j==0 || j==n-1){
b=b+a[i][j];
}
}
}
printf("Boundary total: %d\n",b);
printf("Local hotspots:\n");
for(i=1;i<n-1;i++){
for(j=1;j<n-1;j++){
if(a[i][j]>=t && a[i][j]>a[i-1][j] && a[i][j]>a[i+1][j] && a[i][j]>a[i][j-1] && a[i][j]>a[i][j+1]){
printf("Row %d Column %d Score %d\n",i+1,j+1,a[i][j]);
hot++;
}
}
}
if(hot==0){
printf("No local hotspots found.\n");
}
printf("Final decision: ");
if(hot>0){
printf("CRITICAL\n");
}
else if(count>=n){
printf("WARNING\n");
}
else{
printf("NORMAL\n");
}
return 0;
}

//SEATSMART
#include <stdio.h>
#define ROWS 5
#define COLS 8

void initializeSeats(int seats[ROWS][COLS]);
void displaySeats(int seats[ROWS][COLS]);
int bookSeat(int seats[ROWS][COLS],int r,int c);
int cancelSeat(int seats[ROWS][COLS],int r,int c);
int reserveGroup(int seats[ROWS][COLS],int n);
void displayReport(int seats[ROWS][COLS]);

int main(){
int seats[ROWS][COLS];
int choice,row,seat,size;
initializeSeats(seats);
do{
printf("\n**** SeatSmart ****\n");
printf("1. Display Seats\n");
printf("2. Book One Seat\n");
printf("3. Cancel Booking\n");
printf("4. Group Reservation\n");
printf("5. Occupancy Report\n");
printf("6. Exit\n");
printf("Enter your choice: ");
scanf("%d",&choice);
switch(choice){
case 1:
displaySeats(seats);
break;
case 2:
printf("Enter row (1-5): ");
scanf("%d",&row);
printf("Enter seat (1-8): ");
scanf("%d",&seat);
if(bookSeat(seats,row,seat))
printf("Seat booked successfully!\n");
else
printf("Invalid seat or seat already booked.\n");
break;
case 3:
printf("Enter row (1-5): ");
scanf("%d",&row);
printf("Enter seat (1-8): ");
scanf("%d",&seat);
if(cancelSeat(seats,row,seat))
printf("Booking cancelled successfully!\n");
else
printf("Invalid seat or seat is not booked.\n");
break;
case 4:
printf("Enter group size (2-8): ");
scanf("%d",&size);
if(reserveGroup(seats,size))
printf("Group reservation successful!\n");
else
printf("Invalid group size or no consecutive seats available.\n");
break;
case 5:
displayReport(seats);
break;
case 6:
printf("Thank you for using SEATSMART!\n");
break;
default:
printf("Invalid choice. Try again.\n");
}
}while(choice!=6);
return 0;
}

void initializeSeats(int seats[ROWS][COLS]){
int i,j;
for(i=0;i<ROWS;i++){
for(j=0;j<COLS;j++)
seats[i][j]=0;
}
}

void displaySeats(int seats[ROWS][COLS]){
int i,j;
printf("\nSeating Arrangement:\n");
for(i=0;i<ROWS;i++){
for(j=0;j<COLS;j++)
printf("%d ",seats[i][j]);
printf("\n");
}
printf("0 = Available, 1 = Booked\n");
}

int bookSeat(int seats[ROWS][COLS],int r,int c){
if(r<1||r>ROWS||c<1||c>COLS)
return 0;
if(seats[r-1][c-1]==1)
return 0;
seats[r-1][c-1]=1;
return 1;
}
int cancelSeat(int seats[ROWS][COLS],int r,int c){
if(r<1||r>ROWS||c<1||c>COLS)
return 0;
if(seats[r-1][c-1]==0)
return 0;
seats[r-1][c-1]=0;
return 1;
}
int reserveGroup(int seats[ROWS][COLS],int n){
int i,j,k;
if(n<2||n>COLS)
return 0;
for(i=0;i<ROWS;i++){
for(j=0;j<=COLS-n;j++){
for(k=0;k<n;k++){
if(seats[i][j+k]==1)
break;
}
if(k==n){
for(k=0;k<n;k++)
seats[i][j+k]=1;
printf("Reserved Row %d, Seats %d to %d.\n",i+1,j+1,j+n);
return 1;
}
}
}
return 0;
}

void displayReport(int seats[ROWS][COLS]){
int i,j,booked=0,available,rowCount[ROWS],highest=0;
for(i=0;i<ROWS;i++){
rowCount[i]=0;
for(j=0;j<COLS;j++){
if(seats[i][j]==1){
booked++;
rowCount[i]++;
}
}
if(rowCount[i]>highest)
highest=rowCount[i];
}
available=ROWS*COLS-booked;
printf("\n===== OCCUPANCY REPORT =====\n");
printf("Total seats: %d\n",ROWS*COLS);
printf("Booked seats: %d\n",booked);
printf("Available seats: %d\n",available);
printf("Occupancy: %.2f%%\n",booked*100.0/(ROWS*COLS));
printf("Rows with highest bookings:\n");
for(i=0;i<ROWS;i++){
if(rowCount[i]==highest)
printf("Row %d: %d bookings\n",i+1,rowCount[i]);
}
}

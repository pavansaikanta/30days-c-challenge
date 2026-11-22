#include <stdio.h>
#include <stdlib.h>
#define ZONES 5
#define DAYS 7
int readValue(char prompt[],int low,int high)
{
int n,ch;
while(1)
{
printf("%s",prompt);
if(scanf("%d",&n)!=1)
{
if(feof(stdin)) exit(0);
while((ch=getchar())!='\n'&&ch!=EOF);
printf("Invalid input. Enter a number.\n");
continue;
}
if(n<low||n>high)
{
printf("Enter a value between %d and %d.\n",low,high);
continue;
}
return n;
}
}
char *getZoneName(int z)
{
switch(z)
{
case 0:return "Academic Block";
case 1:return "Hostel";
case 2:return "Library";
case 3:return "Cafeteria";
default:return "Sports Complex";
}
}
void inputWaterData(int usage[ZONES][DAYS],int dailyTarget[ZONES])
{
int i,j;
char prompt[100];
printf("\nEnter water usage in litres (0-50000):\n");
for(i=0;i<ZONES;i++)
{
printf("\n%s\n",getZoneName(i));
for(j=0;j<DAYS;j++)
{
sprintf(prompt,"Day %d usage: ",j+1);
usage[i][j]=readValue(prompt,0,50000);
}
sprintf(prompt,"Daily target for %s: ",getZoneName(i));
dailyTarget[i]=readValue(prompt,100,50000);
}
}
void displayWaterData(int usage[ZONES][DAYS],int dailyTarget[ZONES])
{
int i,j;
printf("\n%-18s","Zone");
for(j=0;j<DAYS;j++) printf("%10s","Day");
printf("%12s\n","Target");
for(i=0;i<ZONES;i++)
{
printf("%-18s",getZoneName(i));
for(j=0;j<DAYS;j++) printf("%10d",usage[i][j]);
printf("%12d\n",dailyTarget[i]);
}
}
void calculateZoneStats(int *zoneUsage,int *total,float *average,int *peakUsage,int *peakDay)
{
int i;
*total=0;
*peakUsage=*zoneUsage;
*peakDay=1;
for(i=0;i<DAYS;i++)
{
*total+=*(zoneUsage+i);
if(*(zoneUsage+i)>*peakUsage)
{
*peakUsage=*(zoneUsage+i);
*peakDay=i+1;
}
}
*average=(float)*total/DAYS;
}
void detectWaterAlerts(int *zoneUsage,int dailyTarget,int *overLimitDays,int *totalExcess,int *spikeDays,int *alertDays)
{
int i,over,spike;
*overLimitDays=0;
*totalExcess=0;
*spikeDays=0;
*alertDays=0;
for(i=0;i<DAYS;i++)
{
over=(*(zoneUsage+i)>dailyTarget);
spike=(i>0&&(*(zoneUsage+i))*10>(*(zoneUsage+i-1))*14);
if(over)
{
(*overLimitDays)++;
*totalExcess+=*(zoneUsage+i)-dailyTarget;
}
if(spike) (*spikeDays)++;
if(over||spike) (*alertDays)++;
}
}
void generateAuditReport(int usage[ZONES][DAYS],int dailyTarget[ZONES],int excessByZone[ZONES],int overLimitByZone[ZONES],int spikeByZone[ZONES],int alertByZone[ZONES])
{
int i,total,peak,day;
float average;
int greatest=0;
printf("\n========== WATER AUDIT REPORT ==========\n");
for(i=0;i<ZONES;i++)
{
calculateZoneStats(&usage[i][0],&total,&average,&peak,&day);
detectWaterAlerts(&usage[i][0],dailyTarget[i],&overLimitByZone[i],&excessByZone[i],&spikeByZone[i],&alertByZone[i]);
printf("\n%s\n",getZoneName(i));
printf("Weekly total: %d L\n",total);
printf("Daily average: %.2f L\n",average);
printf("Peak usage: %d L (Day %d)\n",peak,day);
printf("Over-limit days: %d\n",overLimitByZone[i]);
printf("Total excess: %d L\n",excessByZone[i]);
printf("Spike days: %d\n",spikeByZone[i]);
printf("Unique alert days: %d\n",alertByZone[i]);
if(excessByZone[i]>greatest) greatest=excessByZone[i];
}
printf("\nZone(s) with greatest excess (%d L):\n",greatest);
for(i=0;i<ZONES;i++)
if(excessByZone[i]==greatest) printf("%s\n",getZoneName(i));
}
void rankZones(int excessByZone[ZONES])
{
int order[ZONES],i,j,temp,rank;
for(i=0;i<ZONES;i++) order[i]=i;
for(i=0;i<ZONES-1;i++)
for(j=i+1;j<ZONES;j++)
if(excessByZone[order[j]]>excessByZone[order[i]])
{
temp=order[i];
order[i]=order[j];
order[j]=temp;
}
printf("\n======= ZONE RANKING BY EXCESS =======\n");
for(i=0;i<ZONES;i++)
{
rank=1;
for(j=0;j<ZONES;j++)
if(excessByZone[j]>excessByZone[order[i]]) rank++;
printf("Rank %d: %-18s %d L\n",rank,getZoneName(order[i]),excessByZone[order[i]]);
}
}
void displayConservationActions(int overLimitByZone[ZONES],int spikeByZone[ZONES],int excessByZone[ZONES])
{
int i;
printf("\n======= CONSERVATION ACTIONS =======\n");
for(i=0;i<ZONES;i++)
{
printf("\n%s:\n",getZoneName(i));
if(spikeByZone[i]>0)
printf("- Check for leaks or unexpected usage around spike days.\n");
if(overLimitByZone[i]>=3)
printf("- Conduct a water audit and prepare a reduction plan.\n");
else if(overLimitByZone[i]>0)
printf("- Monitor over-limit days and inspect taps and valves.\n");
if(overLimitByZone[i]==0&&spikeByZone[i]==0)
printf("- Maintain good water conservation practices.\n");
}
}
int main()
{
int usage[ZONES][DAYS],dailyTarget[ZONES];
int excessByZone[ZONES]={0},overLimitByZone[ZONES]={0};
int spikeByZone[ZONES]={0},alertByZone[ZONES]={0};
int choice,reportReady=0;
printf("========== WATERWISE ==========\n");
printf("Track. Detect. Conserve.\n");
printf("\nEnter water data for 5 campus zones and 7 days.\n");
inputWaterData(usage,dailyTarget);
while(1)
{
printf("\n========== MAIN MENU ==========\n");
printf("1. Display Water Data\n");
printf("2. Generate Audit Report\n");
printf("3. Rank Zones by Excess\n");
printf("4. Conservation Actions\n");
printf("5. Exit\n");
choice=readValue("Enter your choice: ",1,5);
switch(choice)
{
case 1:
displayWaterData(usage,dailyTarget);
break;
case 2:
generateAuditReport(usage,dailyTarget,excessByZone,overLimitByZone,spikeByZone,alertByZone);
reportReady=1;
break;
case 3:
if(reportReady) rankZones(excessByZone);
else printf("Generate the audit report first.\n");
break;
case 4:
if(reportReady) displayConservationActions(overLimitByZone,spikeByZone,excessByZone);
else printf("Generate the audit report first.\n");
break;
case 5:
printf("Thank you for using WATERWISE!\n");
return 0;
}
}
}

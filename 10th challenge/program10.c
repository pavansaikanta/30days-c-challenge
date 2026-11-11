#include <stdio.h>

#define ZONES 5
#define DAYS 7

void clearInput(void);
void inputData(float temp[ZONES][DAYS], float humidity[ZONES][DAYS], int aqi[ZONES][DAYS]);
void displayData(float temp[ZONES][DAYS], float humidity[ZONES][DAYS], int aqi[ZONES][DAYS]);
void calculateAverages(float temp[ZONES][DAYS], float humidity[ZONES][DAYS], int aqi[ZONES][DAYS], float avgTemp[ZONES], float avgHumidity[ZONES], float avgAQI[ZONES]);
void detectRiskZones(float temp[ZONES][DAYS], float humidity[ZONES][DAYS], int aqi[ZONES][DAYS], int riskDays[ZONES]);
void computeGreenIndex(float avgTemp[ZONES], float avgHumidity[ZONES], float avgAQI[ZONES], float greenIndex[ZONES]);
void displayRanking(float greenIndex[ZONES]);
void displayRecommendations(float avgTemp[ZONES], float avgHumidity[ZONES], float avgAQI[ZONES], int riskDays[ZONES]);

int main(void) {
    float temp[ZONES][DAYS], humidity[ZONES][DAYS];
    int aqi[ZONES][DAYS], riskDays[ZONES] = {0};
    float avgTemp[ZONES], avgHumidity[ZONES], avgAQI[ZONES];
    float greenIndex[ZONES]; int dataReady = 0, choice, i;

    do {
        printf("\n========== ECOGUARD MENU ==========\n");
        printf("1. Input / Update Data\n");
        printf("2. Display Data\n");
        printf("3. Zone-wise Averages\n");
        printf("4. Detect Risk Days\n");
        printf("5. Green Index and Ranking\n");
        printf("6. Recommendations\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid menu choice. Enter a number from 1 to 7.\n");
            choice = 0; clearInput(); continue;
        }

        switch (choice) {
            case 1:
                inputData(temp, humidity, aqi);
                dataReady = 1;
                break;

            case 2:
                if (!dataReady)
                    printf("Please enter the readings first using option 1.\n");
                else
                    displayData(temp, humidity, aqi);
                break;

            case 3:
                if (!dataReady)
                    printf("Please enter the readings first using option 1.\n");
                else {
                    calculateAverages(temp, humidity, aqi, avgTemp, avgHumidity, avgAQI);
                    printf("\nZONE-WISE AVERAGES\n");
                    for (i = 0; i < ZONES; i++)
                        printf("Zone %d: Temperature %.2f C, Humidity %.2f%%, AQI %.2f\n",
                               i + 1, avgTemp[i], avgHumidity[i], avgAQI[i]);
                }
                break;

            case 4:
                if (!dataReady)
                    printf("Please enter the readings first using option 1.\n");
                else
                    detectRiskZones(temp, humidity, aqi, riskDays);
                break;

            case 5:
                if (!dataReady)
                    printf("Please enter the readings first using option 1.\n");
                else {
                    calculateAverages(temp, humidity, aqi, avgTemp, avgHumidity, avgAQI);
                    computeGreenIndex(avgTemp, avgHumidity, avgAQI, greenIndex);
                    displayRanking(greenIndex);
                }
                break;

            case 6:
                if (!dataReady)
                    printf("Please enter the readings first using option 1.\n");
                else {
                    calculateAverages(temp, humidity, aqi, avgTemp, avgHumidity, avgAQI);
                    computeGreenIndex(avgTemp, avgHumidity, avgAQI, greenIndex);
                    detectRiskZones(temp, humidity, aqi, riskDays);
                    displayRecommendations(avgTemp, avgHumidity, avgAQI, riskDays);
                }
                break;

            case 7:
                printf("Exiting EcoGuard. Thank you!\n");
                break;

            default:
                printf("Invalid choice. Please select from 1 to 7.\n");
        }
    } while (choice != 7);

    return 0;
}

void clearInput(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;
}

void inputData(float temp[ZONES][DAYS], float humidity[ZONES][DAYS], int aqi[ZONES][DAYS]) {
    int z, d, valid;

    printf("\nEnter readings for five zones and seven days.\n");
    printf("Zones: 1 Academic Block, 2 Hostel, 3 Library, 4 Cafeteria, 5 Sports Area\n");

    for (z = 0; z < ZONES; z++) {
        printf("\n--- Zone %d ---\n", z + 1);
        for (d = 0; d < DAYS; d++) {
            do {
                printf("Day %d temperature (10 to 50 C): ", d + 1);
                valid = scanf("%f", &temp[z][d]);
                if (valid != 1 || temp[z][d] < 10 || temp[z][d] > 50) {
                    printf("Invalid temperature. Enter a value from 10 to 50.\n");
                    clearInput(); valid = 0;
                }
            } while (valid != 1);

            do {
                printf("Day %d humidity (0 to 100%%): ", d + 1);
                valid = scanf("%f", &humidity[z][d]);
                if (valid != 1 || humidity[z][d] < 0 || humidity[z][d] > 100) {
                    printf("Invalid humidity. Enter a value from 0 to 100.\n");
                    clearInput(); valid = 0;
                }
            } while (valid != 1);

            do {
                printf("Day %d AQI (0 to 500): ", d + 1);
                valid = scanf("%d", &aqi[z][d]);
                if (valid != 1 || aqi[z][d] < 0 || aqi[z][d] > 500) {
                    printf("Invalid AQI. Enter an integer from 0 to 500.\n");
                    clearInput(); valid = 0;
                }
            } while (valid != 1);
        }
    }
    printf("\nAll readings have been saved successfully.\n");
}

void displayData(float temp[ZONES][DAYS], float humidity[ZONES][DAYS], int aqi[ZONES][DAYS]) {
    int z, d;

    printf("\nTEMPERATURE MATRIX (C)\n");
    for (z = 0; z < ZONES; z++) {
        printf("Zone %d: ", z + 1);
        for (d = 0; d < DAYS; d++)
            printf("%7.1f", temp[z][d]);
        printf("\n");
    }

    printf("\nHUMIDITY MATRIX (%%)\n");
    for (z = 0; z < ZONES; z++) {
        printf("Zone %d: ", z + 1);
        for (d = 0; d < DAYS; d++)
            printf("%7.1f", humidity[z][d]);
        printf("\n");
    }

    printf("\nAQI MATRIX\n");
    for (z = 0; z < ZONES; z++) {
        printf("Zone %d: ", z + 1);
        for (d = 0; d < DAYS; d++)
            printf("%7d", aqi[z][d]);
        printf("\n");
    }
}

void calculateAverages(float temp[ZONES][DAYS], float humidity[ZONES][DAYS], int aqi[ZONES][DAYS], float avgTemp[ZONES], float avgHumidity[ZONES], float avgAQI[ZONES]) {
    int z, d;
    float sumT, sumH, sumA;

    for (z = 0; z < ZONES; z++) {
        sumT = 0; sumH = 0; sumA = 0;
        for (d = 0; d < DAYS; d++) {
            sumT += temp[z][d];
            sumH += humidity[z][d];
            sumA += aqi[z][d];
        }
        avgTemp[z] = sumT / DAYS;
        avgHumidity[z] = sumH / DAYS;
        avgAQI[z] = sumA / DAYS;
    }
}

void detectRiskZones(float temp[ZONES][DAYS], float humidity[ZONES][DAYS], int aqi[ZONES][DAYS], int riskDays[ZONES]) {
    int z, d, found;

    printf("\nRISK DAY REPORT\n");
    for (z = 0; z < ZONES; z++) {
        riskDays[z] = 0; found = 0;
        printf("Zone %d: ", z + 1);
        for (d = 0; d < DAYS; d++) {
            if (aqi[z][d] > 150 || temp[z][d] > 35 || humidity[z][d] > 80) {
                riskDays[z]++;
                printf("Day %d ", d + 1);
                found = 1;
            }
        }
        if (!found)
            printf("No risk days");
        printf("| Total risk days: %d\n", riskDays[z]);
    }
}

void computeGreenIndex(float avgTemp[ZONES], float avgHumidity[ZONES], float avgAQI[ZONES], float greenIndex[ZONES]) {
    int z;
    float aqiScore, tempScore, humidityScore, difference;

    for (z = 0; z < ZONES; z++) {
        aqiScore = 100 - (avgAQI[z] / 5);

        difference = avgTemp[z] - 25;
        if (difference < 0)
            difference = -difference;
        tempScore = 100 - (4 * difference);

        difference = avgHumidity[z] - 50;
        if (difference < 0)
            difference = -difference;
        humidityScore = 100 - (2 * difference);

        if (aqiScore < 0) aqiScore = 0;
        if (tempScore < 0) tempScore = 0;
        if (humidityScore < 0) humidityScore = 0;

        greenIndex[z] = (0.4 * aqiScore) + (0.3 * tempScore) + (0.3 * humidityScore);
    }
}

void displayRanking(float greenIndex[ZONES]) {
    int z, other, rank, currentRank;
    printf("\nGREEN INDEX RANKING (HIGHEST TO LOWEST)\n");
    for (currentRank = 1; currentRank <= ZONES; currentRank++)
        for (z = 0; z < ZONES; z++) {
            rank = 1;
            for (other = 0; other < ZONES; other++)
                if (greenIndex[other] > greenIndex[z]) rank++;
            if (rank == currentRank) printf("Zone %d: Green Index = %.2f, Rank = %d\n", z + 1, greenIndex[z], rank);
        }
}

void displayRecommendations(float avgTemp[ZONES], float avgHumidity[ZONES], float avgAQI[ZONES], int riskDays[ZONES]) {
    int z, issue;
    printf("\nZONE-WISE RECOMMENDATIONS\n");
    for (z = 0; z < ZONES; z++) {
        issue = 0; printf("Zone %d: ", z + 1);

        if (avgAQI[z] > 150) {
            printf("Reduce vehicle idling and improve ventilation. ");
            issue = 1;
        }
        if (avgTemp[z] > 35) {
            printf("Provide shade or increase green cover. ");
            issue = 1;
        }
        if (avgHumidity[z] > 80) {
            printf("Check ventilation and possible stagnant-water sources. ");
            issue = 1;
        }
        if (!issue && riskDays[z] > 0)
            printf("Review the dates flagged as risk days. ");
        if (!issue && riskDays[z] == 0)
            printf("Continue regular environmental monitoring. ");

        printf("(Risk days: %d)\n", riskDays[z]);
    }
}

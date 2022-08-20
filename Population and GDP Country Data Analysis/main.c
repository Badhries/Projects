#include <stdio.h>
#include <string.h>

const int NUM_COUNTRIES = 186;
   
typedef struct Country_struct {
   char code[4];
   char name[40];
   double pop; //total population, averaged over 2012-2016
   double gdp; //gross domestic product, averaged over 2012-2016
} Country;

//insertion sort
void sortData(double data[], int size){
    for (int i = 0; i < size; ++i){
        double temp = data[i];
        for (int j = i-1; j >= 0; --j){
            if (data[j] < temp ){
                data[j+1] = data[j];
            } else {
                data[j+1] = temp;
                break;
            }
            if (j == 0){
                data[j] = temp;
            }
        }
    }
    return;
}

void sortCountriesByPop(Country data[], int size){
   for (int i = 0; i < size; ++i){
        Country temp = data[i];
        for (int j = i-1; j >= 0; --j){
            if (data[j].pop < temp.pop ){
                data[j+1] = data[j];
            } else {
                data[j+1] = temp;
                break;
            }
            if (j == 0){
                data[j] = temp;
            }
        }
    }
    return;
}

void sortCountriesByGDP(Country data[], int size){
   for (int i = 0; i < size; ++i){
        Country temp = data[i];
        for (int j = i-1; j >= 0; --j){
            if (data[j].gdp < temp.gdp ){
                data[j+1] = data[j];
            } else {
                data[j+1] = temp;
                break;
            }
            if (j == 0){
                data[j] = temp;
            }
        }
    }
    return;
}

void sortCountriesByGDPperCap(Country data[], int size){
   for (int i = 0; i < size; ++i){
        Country temp = data[i];
        for (int j = i-1; j >= 0; --j){
            if (data[j].gdp/data[j].pop < temp.gdp/temp.pop ){
                data[j+1] = data[j];
            } else {
                data[j+1] = temp;
                break;
            }
            if (j == 0){
                data[j] = temp;
            }
        }
    }
    return;
}

int main() {

   Country allData[NUM_COUNTRIES];
   
   FILE* myFile = fopen("countryData.txt","r");
   char titles[30];
   fscanf(myFile, "%s %s %s %s", titles, titles, titles, titles);
   fscanf(myFile, "%s %s %s %s", titles, titles, titles, titles);
   fscanf(myFile, "%s %s %s %s", titles, titles, titles, titles);
   fscanf(myFile, "%s %s %s %s", titles, titles, titles, titles);
   
   double garbage;
   for (int i = 0; i < NUM_COUNTRIES; ++i) {
      fscanf(myFile,"%s %s %lf %lf", allData[i].code, allData[i].name, &garbage, &garbage);
      fscanf(myFile,"%lf %lf %lf %lf", &garbage, &garbage, &allData[i].pop, &allData[i].gdp);
      fscanf(myFile,"%lf %lf %lf %lf", &garbage, &garbage, &garbage, &garbage);
      fscanf(myFile,"%lf %lf %lf %lf", &garbage, &garbage, &garbage, &garbage);
   }
   
   //FIRST, SORT BY POPULATION & REPORT THE TOP 10
   sortCountriesByPop(allData, NUM_COUNTRIES);
   printf("The 10 countries with the largest population are:\n");
   for (int i = 0; i<10;  i++) {
      printf("#%d %s: %.0lf \n",i+1,allData[i].name,allData[i].pop);
   }
   printf("\n");
   
   //THEN, SORT BY GDP & REPORT THE TOP 10
   sortCountriesByGDP(allData, NUM_COUNTRIES);
   printf("The 10 countries with the highest GDP are:\n");
   for (int i = 0; i<10;  i++) {
      printf("#%d %s: %.0lf USD\n",i+1,allData[i].name,allData[i].gdp);
   }
   printf("\n");

   //LAST, SORT BY GDP PER CAPITA & REPORT THE TOP 10
   sortCountriesByGDPperCap(allData, NUM_COUNTRIES);
   printf("The 10 countries with the highest GDP per capita are:\n");
   for (int i = 0; i<10;  i++) {
      printf("#%d %s: %.2lf USD\n",i+1,allData[i].name,allData[i].gdp/allData[i].pop);
   }
   printf("\n");

   return 0;
}
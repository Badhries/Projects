#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

const double RADIUS_EARTH = 6368.0; //in km

typedef struct Location_struct {
   double latitude;
   double longitude;
   double elevation;
   struct Location_struct* next; //pointer to the next Location
} Location;

//Location Constructor
void LocCreate(Location* thisLoc, double thisLat, double thisLong, double thisElev, Location* nextLoc) {
    thisLoc->latitude = thisLat;
    thisLoc->longitude = thisLong;
    thisLoc->elevation = thisElev;
    thisLoc->next = nextLoc;
}

void LocAdd(Location* headLoc, double newLat, double newLong, double newElev){
   Location* newLocation = (Location*)malloc(sizeof(Location));//allocates memory and gives pointer
   LocCreate(newLocation, newLat, newLong, newElev,NULL);
   Location* updateLoc = headLoc;
   while (updateLoc->next != NULL) {//while not the has block, keeps on looping
      updateLoc = updateLoc->next;
   }
   updateLoc->next = newLocation; //upday=tes the location
}

int countLocs(Location* headLoc){ //finding number of nodes
   int count = 0;
   Location* updateLoc = headLoc;
   while (updateLoc != NULL) {//while not the last one keep on looping until it reaches the last one
      updateLoc = updateLoc->next;
      count++; //increasing count each time
   }
   return count; //returns the value of count
}

double findMaxElev(Location* headLoc){//finding max elevation
   double max = 0;//initializing the variable max
   Location* updateLoc = headLoc;
   while (updateLoc != NULL) { 
      if (updateLoc->elevation>max) {
         max = updateLoc->elevation;
      }
      updateLoc = updateLoc->next;
   }
   return max; //returning the value of max
}

double LocsToDist(double lat1, double long1, double lat2, double long2){ //finding the distance between the two points
   double d = 0;
   lat1 = lat1 * M_PI/180.0;//convert from degree to radians
   lat2 = lat2 * M_PI/180.0;
   d = RADIUS_EARTH* acos( cos(lat1)*cos(lat2)*cos((long2 - long1) * M_PI / 180.0) + sin(lat1)*sin(lat2) ); //finding distance in radians
   return d; //returns that value from previous line
}
void convertTime(int total_seconds, int* hours, int* minutes, int* seconds) {//finding time
   *hours = total_seconds/3600; //formula to find the hours
   *minutes = (total_seconds- *hours * 3600) / 60; //formula to find the minutes
   *seconds = total_seconds - *hours * 3600 - *minutes * 60; //formula to find the seconds
}
int main() {
   char filename[25];
   printf("Enter the filename: \n");
   scanf("%s", filename); //getting user input
   FILE* myFile = fopen(filename, "r"); //opening the requested file 
   if(myFile == NULL) { //if it cannot find the file
      printf("Could not open file.\n");
      return -1;
   }
   char str[20]; //declaring variable
   double latitude, longitude, elevation; //declaring variables
   double latitude_previous, longitude_previous;
   int hours;//declaring variables
   int minutes;
   int seconds;
   fscanf(myFile, "%s" "%s" "%s", str, str, str); //scanning data from the file(latitude, longitude, and elevation)
   Location* new_Location = (Location*)malloc(sizeof(Location)); //allocates the memory
   int i = 0;
   double totGain = 0;
   double valOld;
   double j = 0;
   while (!feof(myFile)) {
      fscanf(myFile, "%lf %lf %lf", &latitude, &longitude, &elevation); //scanning in values
      if ( i == 0) {
         LocCreate(new_Location, latitude, longitude, elevation, NULL);
      }
      else {
         LocAdd(new_Location, latitude, longitude, elevation); //calls the function with the given parameters
         j += LocsToDist(latitude_previous, longitude_previous, latitude, longitude);//finding the value of the 2 distances
      }
      if (i > 0 && elevation>valOld) { //to find the elevation gained(on the fly calculation)
         totGain += elevation-valOld;
      }
      valOld = elevation;
      latitude_previous = latitude;//storing the values 
      longitude_previous = longitude;
      i++; //increases the value of i each time
   }
   printf("On-the-Fly Total GPS Datapoints: %d \n", i); //based on the calculations in main, it finds the total datapoints
   printf("On-the-Fly Elevation Gained: %0.1lf m\n",totGain); //based on the calculations done in main, it finds the elevation gained
   printf("On-the-Fly Distance Biked: %0.1lf km\n",j); //based on the calculations done in main, it finds the biked distance
   printf("Linked List Total GPS Datapoints: %d \n", countLocs(new_Location) ); //calls the function to find the total datapoints recorded
   printf("Linked List Max Elevation: %0.1lf m\n", findMaxElev(new_Location) ); //calls the function with 0.1lf decimal format
   printf("Total Time: %d s\n", i);//calculation done in main to find the total time it took
   convertTime(i, &hours, &minutes, &seconds); //calls the function
   printf("Formatted Total Time: %02d:%02d:%02d\n", hours, minutes, seconds); //finds the time in the correct format
   return 0;
}

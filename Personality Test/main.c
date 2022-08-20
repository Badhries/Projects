#include <stdio.h>
#include <string.h>
int main() {
   char question_1[10]; //declaring variables needed for project
   char question_2[10];
   char question_3[10];
   int question_4;
   char house_name[20];
   char match[20];
   int total_points=0; //setting the inital values to 0 to not confuse the program for the starting value
   int score_g = 0;
   int score_h = 0;
   int score_r = 0;
   int score_s = 0;
   printf("Welcome to the Hogwarts House Sorting Quiz\n\n");
   printf("Question 1:\n"); //asking the first question
   printf("You have a decision to make. How do you make your decision?\n");
   printf("a. After briefly weighing all options, I go with my gut and choose the answer that intuitively feels right to me in the moment.\n");
   printf("b. I analyze each of the options carefully and pick the one that will have the best outcome or have the fewest drawbacks.\n");
   scanf("%s", question_1);//taking user input
   if (strcmp(question_1, "a")==0) { //if a certain character is typed in
      score_g = score_g + 4; //add points to the corresponding houses
      score_h = score_h + 4;
   }
   else if (strcmp(question_1, "b")==0) { 
         score_r = score_r + 4;
         score_s = score_s + 4;
   }
   else {
      printf("\nInvalid response. House sorting cannot be completed.\n\n"); //if other buttons are pressed, program ends and invalid message shows up
      return 1;
   }
   printf("\n");
   printf("Question 2:\n");
   printf("You walk into a room to find someone berating your best friend, when your friend didn't do anything wrong! The person yelling at your friend has been unkind to you and your friend in the past. The two people are angry, but leave the room through separate doors. Who is the FIRST person you follow?\n");
   printf("a. My friend\n");
   printf("b. The unkind person\n");
   scanf("%s", question_2);
   if (strcmp(question_2, "a")==0) {
      score_h = score_h + 4;
      score_r = score_r + 4;
   }
   else if (strcmp(question_2, "b")==0) {
      score_g = score_g + 4; 
      score_s = score_s + 4;
   }
   else {
      printf("\nInvalid response. House sorting cannot be completed.\n\n");
      return 1;
   }
   printf("\n");
   if (  ( (strcmp(question_1, "a")==0 && (strcmp(question_2, "b")==0) ) ) ){ //based on the respone of the first two quesions, a preliminary house is chosen
      printf("After two questions, your preliminary house match is Gryffindor!\n");
   }
   else if (  ( (strcmp(question_1, "a")==0 && (strcmp(question_2, "a")==0) ) ) ){
      printf("After two questions, your preliminary house match is Hufflepuff!\n");
   }
   
   else if (  ( (strcmp(question_1, "b")==0 && (strcmp(question_2, "a")==0) ) ) ){
      printf("After two questions, your preliminary house match is Ravenclaw!\n");
   }
   
   else if (  ( (strcmp(question_1, "b")==0 && (strcmp(question_2, "b")==0) ) ) ){
      printf("After two questions, your preliminary house match is Slytherin!\n");
   }
   else {
      printf("Invalid response. House sorting cannot be completed.\n\n");
      return 1;
   }
   printf("\n");
   printf("Question 3:\n");
   printf("Which of the following animals fits your personality best?\n");
   printf("a. lion\n");
   printf("b. eagle\n");
   printf("c. snake\n");
   printf("d. badger\n\n");
   scanf("%s", question_3);
   if (strcmp(question_3, "a")==0) {
      score_g = score_g + 7;
   }
   else if (strcmp(question_3, "b")==0) {
      score_r = score_r + 7;  
   }
   else if (strcmp(question_3, "c")==0) {
      score_s = score_s + 7;  
   }
   else if (strcmp(question_3, "d")==0) {
      score_h = score_h + 7;  
   }
   else {
      printf("Invalid response. House sorting cannot be completed.\n\n");
      return 1;
   }
   printf("Questions 4:\n");
   printf("What is your birthdate? (e.g. if you were born on October 12th, then enter 12; if your birthday is April 28th, then enter 28; etc.)\n\n");
   scanf("%d", &question_4);
   if ( (question_4>0) && (question_4<32)  ) { //making sure the days fall in to the correct day
      if (question_4 % 4 == 1) { //if days have a certain remainder when divided by 4, certain house scores increase
         score_g = score_g + 5;
      }
      if (question_4 % 4 == 2) {
         score_h = score_h + 5;
      }
      if (question_4 % 4 == 3) {
         score_r = score_r + 5;
      }
      if (question_4 % 4 == 0) {
         score_s = score_s + 5;
      }
   }
   else {
      printf("Invalid response. House sorting cannot be completed.\n\n");
      return 1;
   }
     
   if  (score_g == score_h && score_h == score_r && score_r == score_s) {
       total_points= score_g;
       strcpy(house_name, "Gryffindor");
   } 
   if (score_g > score_h && score_h>score_r && score_r>score_s) {
      total_points = score_g;
      strcpy(house_name, "Gryffindor");
   } 
   if(score_h<score_r) { 
      total_points = score_r;
      strcpy(house_name, "Hufflepuff");
   }
   if (score_r<score_s) {
      total_points = score_s;
      strcpy(house_name, "Slytherin");
   }
   else {
      total_points = score_h;
      strcpy(house_name, "Ravenclaw");
     }
   printf("You have been sorted into %s!\n", house_name);
   if ( (total_points > 0) && (total_points<7) ) {
      strcpy(match, "not a match");
   }
   else if ( (total_points >= 8) && (total_points<=12) ) {
      strcpy(match, "moderate match");
   }
   else if ( (total_points >= 13) && (total_points<=19) ) {
      strcpy(match, "close match");
   }
   else if (total_points == 20)  {
      strcpy(match, "perfect match");
   }
   printf("Your match score is %d, which is a %s.\n\n", total_points, match);

   return 0;
}
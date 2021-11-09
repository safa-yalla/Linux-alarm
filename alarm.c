#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

int main()
{
  int hour, minute, second, year, month, day, x = 0;
  int flag = 0, i = 0;
  time_t t, rawtime, y;
  time(&t); //update time
  hour = minute = second = 0;
  printf("*********\n");
  printf("**ALARM CLOCK**\n");
  printf("*********\n");
  printf("Current time %s", ctime(&t));
  struct tm *timeinfo;

  /* prompt user for date */

  printf("Enter year: ");
  fflush(stdout);
  scanf("%d", &year);

  printf("Enter month: ");
  fflush(stdout);
  scanf("%d", &month);

  printf("Enter day: ");
  fflush(stdout);
  scanf("%d", &day);

  printf("Enter hour: ");
  fflush(stdout);
  scanf("%d", &hour);

  printf("Enter minute: ");
  fflush(stdout);
  scanf("%d", &minute);

  /* get current timeinfo */

  struct tm *c = localtime(&t);
  int years2 = c->tm_year + 1900;
  int mons2 = c->tm_mon + 1;
  int days2 = c->tm_mday;
  int hours2 = c->tm_hour;
  int minutes2 = c->tm_min;
  int seconds2 = 0;
  int wkday = c->tm_wday;
  /* get current timeinfo and modify it to the user's choice */

  time(&rawtime);
  timeinfo = localtime(&rawtime);
  timeinfo->tm_year = year - 1900;
  timeinfo->tm_mon = month - 1;
  timeinfo->tm_mday = day;
  timeinfo->tm_hour = hour;
  timeinfo->tm_min = minute;
  mktime(timeinfo);
  printf("Alarm time: %s", asctime(timeinfo));
  time(&t);

  while (years2 != year || month != mons2 || days2 != day || hour != hours2 || minutes2 != minute)
  {
    time(&t);          //update time
    c = localtime(&t); //convert seconds to time structure c
    years2 = c->tm_year + 1900;
    mons2 = c->tm_mon + 1;
    days2 = c->tm_mday;
    hours2 = c->tm_hour;
    minutes2 = c->tm_min;
    printf("The current time is %s", ctime(&t));
    sleep(60);
  }

  if (years2 == year && month == mons2 && days2 == day && hour == hours2 && minutes2 == minute) //if the times match, the alarm rings
  {
    for (i = 0; i < 10; i++)
    {
      printf("\a");
      printf("WAKE UP\n");
    }
  }
  printf("Enter the number of days you want the alarm to be repeated: ");

  scanf("%d", &x);
  if (x == 0)
  {
    exit(0);
  }

  int s[x];
  printf("Enter the days for repetition (0 for Sunday till 6 for Saturday):\n");
  for (i = 0; i < x; i++)
  {
    scanf("%d", &s[i]);
    if (wkday == s[i])
      flag = 1;
  }

  while (flag == 0)
  {
    time(&t);
    c = localtime(&t);
    wkday = c->tm_wday;
    printf("Alarm will not ring today");
    sleep(86400); //make the processor wait for a day to see if the alarm should go of again
  }

  while (hour != hours2 || minutes2 != minute)
  {
    time(&t);          //update time
    c = localtime(&t); //convert seconds to time structure c
    days2 = c->tm_mday;
    hours2 = c->tm_hour;
    minutes2 = c->tm_min;
    printf("The current time is %s", ctime(&t));
    sleep(60);
  }
  time(&t);          //update time
  c = localtime(&t); //convert seconds to time structure c
  hours2 = c->tm_hour;
  minutes2 = c->tm_min;
  if (hour == hours2 && minutes2 == minute) //if the times match, the alarm rings
  {
    for (i = 0; i < 10; i++)
    {
      printf("\a");
      printf("WAKE UP\n");
    }
  }

  return 0;
}
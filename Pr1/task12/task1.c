#include <stdio.h>
#include <time.h>

int main() {
    time_t t = 1;
    time_t prev = 0;
    unsigned long counter = 0;
    
    printf("Starting...\n");
    
    while (t>prev) {
    prev = t;
    t++;
    counter++;
    
    if (counter % 1000000000000 == 0)
    printf("Progress: t = %ld\n", t);
    }
    
    printf("Size of time_t: %lu bytes\n", sizeof(time_t));
    printf("MAX time_t: %ld\n", prev);
    printf("Time of overflow: %s", ctime(&prev));
    
    return 0;
  }  
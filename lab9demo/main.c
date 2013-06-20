/**
 * Demo for CS35L Assignment 9.
 *
 * @author Caleb Leak
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int g_stop = 0;

/**
 * Continually increments a given int*
 *
 * @param arguments the int* (as a void*) to increment.
 */

void* demoThread(void* arguments)
{
  int* position = (int*)arguments;
  while(!g_stop)
    {
      *position += 1;
    }
  return NULL;
}

/**
 * Program entry point.
 *
 */

int main()
{
  pthread_t thread1;
  pthread_t thread2;

  const int ITERATIONS = 2000;
  const int YIELDS = 0x1000;

  int i;
  int j;
  const int LOCATIONS = 70;
  const int SCALE = 0xF00000;

  unsigned int pos1 = 0;
  unsigned int pos2 = 0;

  unsigned int scaledPos1;
  unsigned int scaledPos2;

  // Start our two threads
  pthread_create(&thread1, NULL, (void*)&demoThread, &pos1);
  pthread_create(&thread2, NULL, (void*)&demoThread, &pos2);

  // Print out the locations
  for(i = 0; i < ITERATIONS; i++)
    {
      // Print out the grid.
      // "\r" returns us to the start of the line.
      printf("\r[");
      for(j = 0; j < LOCATIONS; j++)
	{
	  scaledPos1 = pos1 / SCALE % LOCATIONS;
	  scaledPos2 = pos2 / SCALE % LOCATIONS;
	  if(scaledPos1 == j && scaledPos2 == j)
	    printf("+");
	  else if(scaledPos1 == j)
	    printf("|");
	  else if(scaledPos2 == j)
	    printf("-");
	  else
	    printf(" ");
	}
      printf("]");
      
      // Yield a bunch of times to slow ourselves down. In 
      // the real world you would use priorities to do this
      // or sleep() when available.
      for(j = 0; j < YIELDS; j++)
	pthread_yield();
    }
  
  // Stop the threads and wait for them to finish
  g_stop = 1;
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
  printf("\n");

  return 0;
}

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

//take this out
#include <stdio.h>

//LAB SIX 6
char* readstdin(char *rec, int soa);
int compare(const void *a, const void *b);
long n;
int type;
int norecords; // number of records
long comparisons;

int main(int argc, char **argv)
{
  //set n to be the first argument
  n = strtoul(argv[1], NULL, 0);

  //get the size of the input... this works
  struct stat st;
  fstat(0, &st);
  int size = 1;

  if (S_ISREG(st.st_mode))
  {
	type = 1;
  	int s = st.st_size; // size of file
  	size = (s + (n - (s % n))); // size multiple of n
  }
  else {
	type = 0;
 	size = n;
  }

  //REMOVE// this is to make sure fstat worked
  //printf("%d\n", size);

  //character array
  char *records = malloc(size);

  //change the pointer of records to that of the function
  records = readstdin(records, size);

  //free memory
  free(records);

  //output the stuff we need
  fprintf(stderr, "Number of comparisons: %ld\n", comparisons);

  return 0;
}
char* readstdin(char* rec, int soa)// size of array
{
  char c;
  int a = 1;
  int offset = 0;
  if (type != 0)
  {
	//for the first read
	offset = -n;
	soa -=n;
 	do
  	{
		rec = realloc(rec, soa += n);
		offset += n;
 	} while ((a = read(0, rec + offset, soa)) >= n);
  }
  else{
	offset -= 1; //offset for the first character
	do
	{
		rec = realloc(rec, soa += 1);
		a = read(0, rec + (offset += 1), 1);
	} while (a != 0);
	//to undo the last extra character
	rec[offset] = '\0';
	soa -= 1;
  }

  //padding
  while (soa - (n - a) < soa)
  {
	rec[soa - (n - a)] = '\0';
	a++;
  }

  //find the number of records by diving size by n
  norecords = soa / n;

  //sort
  qsort(rec, norecords, n, compare);

  //print the first string no matter what
  //print the rest only if it's not the same as previous
  int index, b;
  for (index = n; index < soa-1; index += n)
	if(memcmp(rec+index, rec+index-n, n))
		write(1, rec+index, n);

  return rec;
}
int compare(const void *a, const void *b)
{
  comparisons++;
  return (memcmp(a, b, n));
}

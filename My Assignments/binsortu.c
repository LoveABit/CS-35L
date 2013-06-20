#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char* readstdin(char *rec, int soa);
int compare(const void *a, const void *b);
long n;
int count = 0; // number of characters
int norecords; // number of records
int main(int argc, char **argv)
{
  n = strtoul(argv[1], NULL, 0);
  int sizeofarray = 1;
  char *records = malloc(sizeofarray * n);
  records = readstdin(records, sizeofarray);
  free(records);
  return 0;
}
char* readstdin(char* rec, int soa)
{
  char c;
  do 
  {
	c = fgetc(stdin);
	if (count >= soa)
	{
		soa *= 2;
		rec = realloc(rec, soa);
	}
	if (c != EOF)
		rec[count] = c;
        count++;
  } while (c != EOF);
  //padding
  if ((count-1) % n != 0)
  {
	while ((count - 1) % n != 0)
	{
		rec[count] = '\0';
		count ++;
	}
  }
  norecords = count / n;
  //sort
  qsort(rec, norecords, n, compare);
  int a, b, unique = 1;
  //print the first string no matter what
  for (b = 0; b < n; b++)
  {
	printf("%c", rec[b]);
  }
  //print the rest only if it's not the same as previous
  int index;
  for (index = n; index < count-1; index += n)
	if(memcmp(rec+index, rec+index-n, n))
		for (b = 0; b < n; b++)
			printf("%c", rec[index+b]);
  return rec;
}
int compare (const void *a, const void *b)
{
  return (memcmp(a, b, n));
}

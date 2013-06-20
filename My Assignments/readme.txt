While doing this homework assignment, I found it challenging to use the pthread_create
	command (mostly because of it's 3rd and 4th argument). 
Also, I had to figure out that I couldn't print everything out when it was rendering.
Instead, I put it all in a 3-D array and then outputted it at the end. 
Once I was able to understand those, the rest of the homework was pretty straight forward.

From my tests, I got the following results:

time ./srt 1-test.ppm >1-test.ppm.tmp && mv 1-test.ppm.tmp 1-test.ppm

real	1m25.025s
user	1m25.006s
sys	0m0.003s
time ./srt 2-test.ppm >2-test.ppm.tmp && mv 2-test.ppm.tmp 2-test.ppm

real	0m42.593s
user	1m24.924s
sys	0m0.003s
time ./srt 4-test.ppm >4-test.ppm.tmp && mv 4-test.ppm.tmp 4-test.ppm

real	0m21.444s
user	1m25.140s
sys	0m0.001s
time ./srt 8-test.ppm >8-test.ppm.tmp && mv 8-test.ppm.tmp 8-test.ppm

real	0m11.343s
user	1m28.425s
sys	0m0.001s
for file in 1-test.ppm 2-test.ppm 4-test.ppm 8-test.ppm; do \
	  diff -u 1-test.ppm $file || exit; \
	done

From this, I can see that the real time decreases as there are more threads, and it decreases
almost proportionally to the number of threads. Overall, I feel like my implementation 
improved the performance greatly.

# PI_Calculation_with_multhreading
Calculation PI with Multi-threading by using of Taylor Series

Write a multithreaded code in either C or Java that computes the pi number using
Taylor series. Each compute-node will compute the part of the Pi number.
Shortly you should decide on the decomposition of the following task.
Pi/4 = +1/1 - 1/3 + 1/5 - 1/7 + 1/9 -...


## Create a thread:
pthread_created(&workers[i],NULL,runner,&rng);
pthread_join(workers[i],NULL);

## Thread Runner:
Each runner calculates partial sum of Talyor series
*void runner(void*args);

## Determine dominator:
int denominator = (idx *2 + 1) * (int)pow(-1.0 , (double)idx);

## Build:
gcc -pthread -o output pi.c –lm

## Run :
./output

## Environment: (vmware 15 ubuntu 16.04)
processors 2
cores 2


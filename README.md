# multithreading_in_c_problem_2

### A. Problem Statement

Write  a  multithreaded  program  that  calculates  various  statistical  values  for  a  list  of numbers. This program will be passed a series of numbers on the command line and will then  create  three  separate  worker  threads.  One  thread  will  determine  the  average  of  the numbers, the second will determine the maximum value, and the third will determine the minimum value.

For example,

1. Suppose your program is passed the integers 90 81 78 95 79 72 85
2. The program will report : 

    > *The average value is 82*<br/>
    > *The minimum value is 72*<br/>
    > *The maximum value is 95*<br/>

3. The  variables  representing  the  average,  minimum,  and  maximum  values  will  be  stored globally.  The  worker  threads  will  set these values,  and  the  parent  thread  will  output  the values once the workers have exited.

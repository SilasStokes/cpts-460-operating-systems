int total;                // global int total

int A[10] = {1,2,3,4,5,6,7,8,9,10};

extern int sum(int *a, int b);  // function prototype 

int main()
{
  total = sum(A, 10);

  while(1);
}

  

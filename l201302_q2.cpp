#include<iostream>
using namespace std;

struct PrimeArr {
	int* primeNumbers;
	int size;
};

bool isPrime(int number)
{
     
      if(number == 1 || number == 0) return false;
    
      for(int index = 2; index < number; index++)
      {
       	 if(number % index == 0) return false;
      }

      return true;
}

void* findPrimeNumber(void* num){
	int number = *(int*) num;

	struct PrimeArr* primeNum = new PrimeArr;
	primeNum->size = 0;
	for(int index = 1; index <= number; index++)
      	{

          if(isPrime(index)) 
          {
		primeNum->size++;
          }
    	}
    	
    	primeNum->primeNumbers = new int [primeNum->size];
    	
    	int count = 0;
    	for (int index =1; index <= number; index++) {
    		if (isPrime(index)){
    			primeNum->primeNumbers[count] = index;
    			count++;
    		}
    	}
    	
    	pthread_exit( (void*) primeNum);
	
	 
}	

void printPrimeNum(PrimeArr* primeNum){
	for (int index = 0; index < primeNum->size; cout << primeNum-> primeNumbers[index] << " ", index++);
}

int main (int argc, char* argv[] ){

	if (argc <= 1 )
	{
		cout << "Zero command line argument" << endl;
	}	
	

	int number = atoi (argv[1]);
	
	pthread_t id;
	
	int num = 33;
	pthread_create (&id, NULL, &findPrimeNumber, &num);
	
	PrimeArr* primeArr;
	
	pthread_join  (id, (void**) &primeArr);
	cout << "Hello " << endl;
	printPrimeNum(primeArr);
	
	return 0;
}	

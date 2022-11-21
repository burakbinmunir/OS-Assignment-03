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

PrimeArr findPrimeNumber(int number){
	struct PrimeArr primeNum;
	primeNum.size = 0;
	for(int index = 1; index <= number; index++)
      	{

          if(isPrime(index)) 
          {
		primeNum.size++;
          }
    	}
    	
    	primeNum.primeNumbers = new int [primeNum.size];
    	
    	int count = 0;
    	for (int index =1; index <= number; index++) {
    		if (isPrime(index)){
    			primeNum.primeNumbers[count] = index;
    			count++;
    		}
    	}
    	
    	return primeNum;
	 
}	

void printPrimeNum(PrimeArr primeNum){
	for (int index = 0; index < primeNum.size;cout << primeNum.primeNumbers[index] << " ", index++);
}
int main (int argc, char* argv[] ){

	int number = atoi (argv[1]);
	PrimeArr primeNum = findPrimeNumber(number);
	printPrimeNum(primeNum);
	return 0;
}	

#include<iostream>
using namespace std;

int maximum = 0;
int minimum = 0;
int average = 0;

struct ArrInfo {
	int* arr;
	int size;
};

ArrInfo extractArr(int size, char* argv[]){

	struct ArrInfo array;
	array.size = size;
	array.arr = new int [size];
	
	int c = 0;
	for (int index = 1; index <= size; index++)
	{
		array.arr[c] = atoi (argv[index]);
		c++;
	}
	return array;
}

void printArray(struct ArrInfo array){
	for (int index =0; index < array.size; cout << array.arr[index] << " " , index++);
}


void* findMin (void* arr){
	struct ArrInfo* array = (ArrInfo*) arr;
	
	if (array->size > 0)
	{
		minimum = array->arr[0];
		
		for (int index = 0; index < array->size; index++)
			if (array->arr[index] < minimum )
				minimum = array->arr[index];
	}
	else{
		cout << "Given array is empty" << endl;
		return nullptr;
	}
	
	pthread_exit((void*) array);
}

void* findMax(void* arg){
	struct ArrInfo* array = (ArrInfo*) arg;
	
	if (array->size <= 0) {
		cout << "Given array is empty" << endl;
		return nullptr;
	}
	
	maximum = array->arr[0];
	for (int index = 0; index < array->size; index++)
		if (array->arr[index] > maximum)
			maximum = array->arr[index];
	
	pthread_exit ( (void*) array);		
}

void* finAvg(void* arg){

	ArrInfo* array = (ArrInfo*) arg;
	
	if (array->size <= 0) {
		cout << "Given array is empty" << endl;
		return nullptr;
	}
	
	int sum = 0;
	for (int index = 0; index < array->size; sum += array->arr[index], index++); // calculating sum
	average  = sum / array->size;
	
	pthread_exit( (void**) array);
}

int main (int argc, char* argv[]){

	if (argc <= 1) {
		cout << "Zero command line argument" << endl;
		return -1;
	}	
	int arrSize = argc - 1;
	
	struct ArrInfo array = extractArr(arrSize, argv);	
	struct ArrInfo* res1;
	
	pthread_t id1;
	pthread_create(&id1 , NULL, &findMin,&array);
	pthread_join(id1, (void**) &res1);
	cout << "Minimum is : " << minimum << endl;
	
	pthread_t id2;
	struct ArrInfo* res2;
	pthread_create(&id2, NULL, &findMax, &array);
	pthread_join(id2, (void**) &res2);
	cout << "Maximum is: " << maximum << endl;
	
	pthread_t id3;
	struct ArrInfo* res3;
	pthread_create(&id3, NULL, &finAvg, &array);
	pthread_join(id3, (void**) &res3);
	cout << "Average is: " << average << endl;
	
	return 0;	
}

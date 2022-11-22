#include<iostream>
using namespace std;

struct FBSeries {
	int* series;
	int size;
};

void* generateSeries (void* number){
	
	FBSeries* fbSeries = new FBSeries;

	fbSeries-> size = *(int*) number;
	
	fbSeries-> series = new int [fbSeries->size];
	
	fbSeries-> series[0] = 0;
	fbSeries-> series[1] = 1;

	
	for (int index = 2; index < fbSeries->size;  fbSeries->series[index] = fbSeries->series[index - 1] + fbSeries->series[index - 2], index++);
	
	pthread_exit ( (void*) fbSeries);
}

void printSeries (FBSeries* fbSeries){
	if (fbSeries->size <=0 ) 	return;
	
	for (int index = 0; index < fbSeries->size; cout << fbSeries->series[index]<<" ", index++);
}

int main (int argc, char* argv[]) {
	int size = argc - 1;
	
	if (size <= 0){
		cout << "No Command Line argument passed" << endl;
		return -1;
	}
	
	int number = atoi (argv[1]);
	pthread_t id;
	
	pthread_create (&id, NULL, &generateSeries, &number);
	
	FBSeries* res;
	pthread_join (id, (void**) &res);
	printSeries(res);
}	

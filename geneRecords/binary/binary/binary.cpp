#include <iostream>
#include <fstream>
#include <string.h>
#include <exception>
#include "customErrorClass.h"

using namespace std;


void swap(int& array1, int& array2)
{
	int temp = array1;
	array1 = array2;
	array2 = temp;
}


int partition(int array[], int p, int r)
{
	int x = array[r], i = p-1;
	for(int j = p; j <= r-1; j++)
	{
		if(array[j] <= x)
		{
			i++;
			swap(array[i], array[j]);
		}
	}
	swap(array[i+1], array[r]);
	
	return i+1;
}


void quickSort(int array[], int p, int r)
{
	if (p < r)
	{
		int q = partition(array, p, r);
		quickSort(array, p, q-1);
		quickSort(array, q+1, r);
	}
}


int main(int argc, char *argv[]){

    fstream inputFile;
    fstream binaryFile;
    int num;
    int inputArray[2000000];
    int indexArray[40];


    if (argc != 2)
    {
        cout<<"ERROR!!"<<endl;
        cout<<"Usage: ./a.out fileName"<<endl;
        exit(0);
    }

    inputFile.open(argv[1], ios::in);
    binaryFile.open("outputBinary.dat", ios::out|ios::binary);

    //Reading from a file
    if (inputFile.is_open())
    {
        int i = 0;
        while (!inputFile.eof())
        {
            inputFile >> inputArray[i];
            i++;
        }
    } else{
        throw MyException("Unable to open file!");
    }

    inputFile.close(); 

    //Sorting the numbers using quicksort
    quickSort(inputArray, 0, 1999999);

    //Writing sorted numbers into a binary file
    binaryFile.write((char*)inputArray, sizeof(int)*2000000);

    //indexing in increments of 50,000
    binaryFile.seekg(ios::beg);

    binaryFile.close();

    indexArray[0] = 0;
    int changeLoc = 50000;
    for (int j = 1; j < 40; j++)
    {

        int swap = 0, index = 0;
        do {
            if(inputArray[index] >= changeLoc){
                swap = inputArray[index];
            } else {
                index++;
            }
        }while (swap == 0);

        indexArray[j] = index;
        changeLoc += 50000;
    }


    binaryFile.open("outputBinary.dat", ios::in|ios::binary);

    //printing retrieved numbers
    int offset, numPosition;
    //The 102nd number from the 1st index
    offset = indexArray[1]*sizeof(int);
    numPosition = 101*sizeof(int);
  
    binaryFile.seekg(ios::beg+offset+numPosition);

    binaryFile.read((char*)&num, sizeof(int));

    cout<<"The 102nd number from the 1 index is "<<num<<endl;

	//The 31st number from the 10th index 
    offset = indexArray[10]*sizeof(int);
    numPosition = 30*sizeof(int);
  
    binaryFile.seekg(ios::beg+offset+numPosition);

    binaryFile.read((char*)&num, sizeof(int));

    cout<<"The 31st number from the 10 index is "<<num<<endl;

	//The 3,105th number from the 34th index
    offset = indexArray[34]*sizeof(int);
    numPosition = 3104*sizeof(int);
  
    binaryFile.seekg(ios::beg+offset+numPosition);

    binaryFile.read((char*)&num, sizeof(int));

    cout<<"The 3105th number from the 34 index is "<<num<<endl;

	//The 431st number from the 21st index
    offset = indexArray[21]*sizeof(int);
    numPosition = 430*sizeof(int);
  
    binaryFile.seekg(ios::beg+offset+numPosition);

    binaryFile.read((char*)&num, sizeof(int));

    cout<<"The 431st number from the 21 index is "<<num<<endl;


	//The 42,971 number from the 18th index
    offset = indexArray[18]*sizeof(int);
    numPosition = 42970*sizeof(int);
  
    binaryFile.seekg(ios::beg+offset+numPosition);

    binaryFile.read((char*)&num, sizeof(int));

    cout<<"The 42971st number from the 18 index is "<<num<<endl;

    //Using user input
    int uIndex, uPos;
    cout<<"Enter the index between 0 and 39: "<<endl;
    cin>>uIndex;
    cout<<"Enter the position between 1st and 2,000,000th: "<<endl;
    cin>>uPos;

    if (uIndex < 0 || uIndex > 39){
        throw MyException("Invalid Index!");
    }
    if (uPos < 1 || uPos > 2000000){
        throw MyException("Invalid Index!");
    }

    try{
    uIndex = indexArray[uIndex]*sizeof(int);
    uPos = (uPos-1) * sizeof(int);

    binaryFile.seekg(ios::beg+uIndex+uPos);

    binaryFile.read((char*)&num, sizeof(int));

    cout<<"The "<<(uPos/4)+1<<" number from the "<<(uIndex/(4*50000))<<" index is "<<num<<endl;
    } catch(MyException &e){
        cout<<e.what()<<endl;
    }
   
    binaryFile.close();

    return 0;
}
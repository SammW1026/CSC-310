#ifndef GENEBANK_MANAGER_H
#define GENEBANK_MANAGER_H

#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>
#include <exception>
#include <algorithm>
#include "customErrorClass.h"

const int MAX_RESEARCHER_NAME = 20;

// Gene sample structure 
struct Sample 
{
    int sampleID;       // Unique sample ID
    int speciesCode;    // 5 unique Species codes 0-4
    float purityScore;                     // Purity score between 0.0 and 1.0
    char researcher[MAX_RESEARCHER_NAME];  // Collected by / researcher name
};

class GENE_BANK
{
    public:
        GENE_BANK();  
        ~GENE_BANK(); 

        void sort(Sample array[], int fileSize);

        void indexSamples(Sample array[], int indexArray[]); 
        void displayResearcher(int speciesCode, int offset, char* filename);  
        bool searchSample(int speciesCode, int offset, char* filename);      // COMPLETE THIS
        void updateResearcher(int speciesCode, int offset, char* newName, char* filename); 
        void deleteSample(int speciesCode, int offset, char* filename);      
        void printSampleRange(int speciesCode, int startIndex, int endIndex, char* filename); 

        int fileSize;
        int entryByte;

    private: // COMPLETE THESE PRIVATE FUNCTIONS BELOW

        // your sorting algorithm - choose the right one
        void quicksort(Sample array[], int low, int high);
        int partition(Sample array[], int low, int high);
    
        void p_index(Sample array[], int indexArray[]);

        void p_displayResearcher(int speciesCode, int offset, char* filename);
        void p_updateResearcher(int speciesCode, int offset, char* newName, char* filename);
        void p_deleteSample(int speciesCode, int offset, char* filename);
        void p_printRange(int speciesCode, int startIndex, int endIndex, char* filename);

        int indexArray[5];

};

#endif 

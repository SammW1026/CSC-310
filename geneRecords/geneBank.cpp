#include "geneBank.h"

using namespace std;

// =================================== PUBLIC FUNCTIONS =======================================================

GENE_BANK::GENE_BANK()
{
    this->fileSize = 0;
    this->entryByte = sizeof(Sample);
    for(int i = 0; i < 5; i++) this->indexArray[i] = 0;
}

GENE_BANK::~GENE_BANK()
{
    cout << "Destructing ..." << endl;
}

// Public sort entry point: kicks off the chosen sorting algorithm (quicksort)
void GENE_BANK::sort(Sample array[], int n)
{
    quicksort(array, 0, n - 1);
}

// Public indexer: builds the species-code index, then caches it inside the class
void GENE_BANK::indexSamples(Sample array[], int indexArray[])
{
    this->p_index(array, indexArray);
    for(int i = 0; i < 5; i++) this->indexArray[i] = indexArray[i];
}

void GENE_BANK::displayResearcher(int speciesCode, int offset, char* filename)
{
    bool checkSample;

    checkSample = searchSample(speciesCode, offset, filename);

    if(checkSample){
        p_displayResearcher(speciesCode, offset, filename);
    } else {
        cout << "Sample record doesn't exist! Can't display researcher name." << endl;
    }
}

// Task 1: searchSample
// NOTE on parameter semantics: main() passes indexArray[sCode] (the absolute
// starting index of a species partition) as the first argument, not the
// species code 0-4. The parameter name "speciesCode" is preserved from the
// header but is treated here as a starting index into the sorted file.
// A record is considered to "exist" if (a) its position is within the file
// and (b) its sampleID is not the deletion sentinel (-1).
bool GENE_BANK::searchSample(int speciesCode, int offset, char* filename)
{
    fstream file(filename, ios::in | ios::binary);
    if(!file) return false;

    int pos = speciesCode + offset;          // absolute record index
    if(pos < 0 || pos >= this->fileSize){
        file.close();
        return false;
    }

    file.seekg(pos * this->entryByte, ios::beg);
    Sample s;
    file.read((char*)&s, this->entryByte);
    file.close();

    // sampleID == -1 marks a deleted record
    if(s.sampleID == -1) return false;

    return true;
}


void GENE_BANK::updateResearcher(int speciesCode, int offset, char* newName, char* filename)
{
    bool checkSample;

    checkSample = this->searchSample(speciesCode, offset, filename);

    if(checkSample){
        p_updateResearcher(speciesCode, offset, newName, filename);
    } else {
        cout << "Sample record to be updated doesn't exist!" << endl;
    }
}

void GENE_BANK::deleteSample(int speciesCode, int offset, char* filename)
{
    bool checkSample;

    checkSample = this->searchSample(speciesCode, offset, filename);

    if(checkSample){
        p_deleteSample(speciesCode, offset, filename);
    } else {
        cout << "Sample record to be deleted doesn't exist!" << endl;
    }
}

void GENE_BANK::printSampleRange(int speciesCode, int startIndex, int endIndex, char* filename)
{
    if(startIndex >= endIndex)
        throw MyException("ERROR: start index is larger than end index!");
    else
        this->p_printRange(speciesCode, startIndex, endIndex, filename);
}

// =================================== PRIVATE FUNCTIONS =======================================================

// Task 2: chosen sorting algorithm -- quicksort over the speciesCode field.
// Quicksort is in-place and runs in O(n log n) on average, which is well
// suited for sorting all samples by species code.
void GENE_BANK::quicksort(Sample array[], int low, int high)
{
    if(low < high){
        int pi = partition(array, low, high);
        quicksort(array, low, pi - 1);
        quicksort(array, pi + 1, high);
    }
}

int GENE_BANK::partition(Sample array[], int low, int high)
{
    Sample pivot = array[high];
    int i = low - 1;
    for(int j = low; j < high; j++){
        if(array[j].speciesCode <= pivot.speciesCode){
            i++;
            std::swap(array[i], array[j]);
        }
    }
    std::swap(array[i + 1], array[high]);
    return i + 1;
}

// Task 3: p_index
// After the array is sorted by speciesCode, the records for each species form
// a contiguous block. indexArray[k] stores the index of the FIRST record
// whose speciesCode == k. If a particular species has no records, its entry
// is left equal to the entry of the next non-empty species (so sizes still
// compute correctly when subtracted).
void GENE_BANK::p_index(Sample array[], int indexArray[])
{
    // initialize: -1 means "not yet seen"
    for(int i = 0; i < 5; i++) indexArray[i] = -1;

    for(int i = 0; i < this->fileSize; i++){
        int code = array[i].speciesCode;
        if(code >= 0 && code < 5 && indexArray[code] == -1){
            indexArray[code] = i;
        }
    }

    // Patch any species that never appeared so that boundaries still work.
    // Walk from the right: any unseen species is treated as starting where
    // the next species starts (or fileSize for the last one).
    int next = this->fileSize;
    for(int i = 4; i >= 0; i--){
        if(indexArray[i] == -1) indexArray[i] = next;
        else next = indexArray[i];
    }
}

// Task 4: p_displayResearcher
// Reads the record at (speciesCode + offset) and prints its researcher name.
// (As noted above, "speciesCode" here is the absolute starting index that
// main() supplies via indexArray[sCode].)
void GENE_BANK::p_displayResearcher(int speciesCode, int offset, char* filename)
{
    /* Species codes:
         0 - H_SAP   (Homo sapiens)
         1 - M_MUS   (Mus musculus)
         2 - D_MEL   (Drosophila melanogaster)
         3 - E_COL   (Escherichia coli)
         4 - A_THA   (Arabidopsis thaliana)
    */
    fstream file(filename, ios::in | ios::binary);
    if(!file){
        cout << "ERROR: cannot open file " << filename << endl;
        return;
    }

    int pos = speciesCode + offset;
    file.seekg(pos * this->entryByte, ios::beg);

    Sample s;
    file.read((char*)&s, this->entryByte);
    file.close();

    cout << "Researcher: " << s.researcher << endl;
}

// Task 5: p_updateResearcher
// Overwrites the researcher field of the target record in place. Seeks to the
// researcher field using offsetof so the rest of the record is untouched.
void GENE_BANK::p_updateResearcher(int speciesCode, int offset, char* newName, char* filename)
{
    fstream file(filename, ios::in | ios::out | ios::binary);
    if(!file){
        cout << "ERROR: cannot open file " << filename << endl;
        return;
    }

    int pos = speciesCode + offset;

    // Build a fixed-width buffer so we always write exactly MAX_RESEARCHER_NAME bytes.
    char buf[MAX_RESEARCHER_NAME];
    for(int i = 0; i < MAX_RESEARCHER_NAME; i++) buf[i] = '\0';
    strncpy(buf, newName, MAX_RESEARCHER_NAME - 1);
    buf[MAX_RESEARCHER_NAME - 1] = '\0';

    file.seekp(pos * this->entryByte + offsetof(Sample, researcher), ios::beg);
    file.write(buf, MAX_RESEARCHER_NAME);
    file.close();
}

// Task 6: p_deleteSample
// Performs a tombstone delete: writes -1 into the sampleID field of the
// target record. searchSample treats sampleID == -1 as "no longer exists".
void GENE_BANK::p_deleteSample(int speciesCode, int offset, char* filename)
{
    fstream file(filename, ios::in | ios::out | ios::binary);
    if(!file){
        cout << "ERROR: cannot open file " << filename << endl;
        return;
    }

    int pos = speciesCode + offset;
    int del = -1;

    file.seekp(pos * this->entryByte + offsetof(Sample, sampleID), ios::beg);
    file.write((char*)&del, sizeof(int));
    file.close();
}

// Task 7: p_printRange
// Prints every record in the inclusive range [startIndex, endIndex] within
// the species partition that begins at speciesCode (an absolute starting
// index supplied by main via indexArray[sCode]). Deleted records are noted.
void GENE_BANK::p_printRange(int speciesCode, int startIndex, int endIndex, char* filename)
{
    fstream file(filename, ios::in | ios::binary);
    if(!file){
        cout << "ERROR: cannot open file " << filename << endl;
        return;
    }

    for(int i = startIndex; i <= endIndex; i++){
        int pos = speciesCode + i;
        file.seekg(pos * this->entryByte, ios::beg);

        Sample s;
        file.read((char*)&s, this->entryByte);

        if(s.sampleID == -1){
            cout << "[deleted record at offset " << i << "]" << endl;
        } else {
            cout << "ID: "        << s.sampleID
                 << ", Species: " << s.speciesCode
                 << ", Purity: "  << s.purityScore
                 << ", Researcher: " << s.researcher
                 << endl;
        }
    }
    file.close();
}

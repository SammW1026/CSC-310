#include "geneBank.h"

using namespace std;

int main(int argc, char *argv[])
{

    GENE_BANK mySample;

    fstream inputBinary;
    fstream sortedBinary;

    int entryByte = sizeof(Sample), fileSize = 0;
    int choice = 1, sCode, offset, rangeStart, rangeEnd;
    Sample* smpl;
    Sample temp;

    int indexArray[5];
    char newName[20];
    char fileStr[25];
    
    MyException excp("ERROR!!");
    

    if (argc != 2)
    {
        cout<<"ERROR!!"<<endl;
        cout<<"Usage: ./a.out samples.bin"<<endl;
        exit(0);
    }

    
    inputBinary.open("samples.bin", ios::in|ios::binary);
    //get the file size here COMPLETE THIS .......
    inputBinary.seekg(0, ios::end);
    fileSize = inputBinary.tellg() / sizeof(Sample);
    mySample.fileSize = fileSize;

    smpl = new Sample[fileSize];

    //Reading a binary file into a struct array here COMPLETE THIS .....
    inputBinary.seekg(0, ios::beg);
    inputBinary.read((char*)smpl, fileSize * sizeof(Sample));

    inputBinary.close();


    //Sorting the struct array
    mySample.sort(smpl, fileSize);

    //Writing sorted file to a new binary file here COMPLETE THIS
    sortedBinary.open("sorted_samples.bin", ios::out | ios::binary);
    sortedBinary.write((char*)smpl, fileSize * sizeof(Sample));
    sortedBinary.close();


    //Indexing a file
    mySample.indexSamples(smpl, indexArray);


    //Find the size in each species code here COMPLETE THIS
    int size0, size1, size2, size3, size4;
    size0 = indexArray[1] - indexArray[0];
    size1 = indexArray[2] - indexArray[1];
    size2 = indexArray[3] - indexArray[2];
    size3 = indexArray[4] - indexArray[3];
    size4 = fileSize - indexArray[4];

    strcpy(fileStr, "sorted_samples.bin");



    //-----printing some outputs---------

    //printing the 53rd Sample from each species code
    cout<<"-----------Printing the 53rd Sample from each species code"<<endl;
    mySample.displayResearcher(indexArray[0], 53, fileStr);
    mySample.displayResearcher(indexArray[1], 53, fileStr);
    mySample.displayResearcher(indexArray[2], 53, fileStr);
    mySample.displayResearcher(indexArray[3], 53, fileStr);
    mySample.displayResearcher(indexArray[4], 53, fileStr);
    cout<<endl;

    //printing the 102nd Sample from each species code
    cout<<"-----------Printing the 102nd Sample from each species code"<<endl;
    mySample.displayResearcher(indexArray[0], 102, fileStr);
    mySample.displayResearcher(indexArray[1], 102, fileStr);
    mySample.displayResearcher(indexArray[2], 102, fileStr);
    mySample.displayResearcher(indexArray[3], 102, fileStr);
    mySample.displayResearcher(indexArray[4], 102, fileStr);
    cout<<endl;

    //printing each record with the name updated to "Carol"
    cout<<"----------------------Printing each record with the researcher name updated to 'Carol'"<<endl;
    char newName1[20] = "Carol";
    mySample.updateResearcher(indexArray[0], 102, newName1, fileStr);
    mySample.updateResearcher(indexArray[1], 102, newName1, fileStr);
    mySample.updateResearcher(indexArray[2], 102, newName1, fileStr);
    mySample.updateResearcher(indexArray[3], 102, newName1, fileStr);
    mySample.updateResearcher(indexArray[4], 102, newName1, fileStr);

    mySample.displayResearcher(indexArray[0], 102, fileStr);
    mySample.displayResearcher(indexArray[1], 102, fileStr);
    mySample.displayResearcher(indexArray[2], 102, fileStr);
    mySample.displayResearcher(indexArray[3], 102, fileStr);
    mySample.displayResearcher(indexArray[4], 102, fileStr);

    cout<<endl;    
    //printing the 13th Sample from each species code
    cout<<"-----------Printing the 13th Sample from each species code"<<endl;
    mySample.displayResearcher(indexArray[0], 13, fileStr);
    mySample.displayResearcher(indexArray[1], 13, fileStr);
    mySample.displayResearcher(indexArray[2], 13, fileStr);
    mySample.displayResearcher(indexArray[3], 13, fileStr);
    mySample.displayResearcher(indexArray[4], 13, fileStr);
    cout<<endl;

    //printing after deletion
    cout<<"----------------------Printing after deletion"<<endl;
    mySample.deleteSample(indexArray[0], 13, fileStr);
    mySample.deleteSample(indexArray[1], 13, fileStr);
    mySample.deleteSample(indexArray[2], 13, fileStr);
    mySample.deleteSample(indexArray[3], 13, fileStr);
    mySample.deleteSample(indexArray[4], 13, fileStr);

    mySample.displayResearcher(indexArray[0], 13, fileStr);
    mySample.displayResearcher(indexArray[1], 13, fileStr);
    mySample.displayResearcher(indexArray[2], 13, fileStr);
    mySample.displayResearcher(indexArray[3], 13, fileStr);
    mySample.displayResearcher(indexArray[4], 13, fileStr);
    cout<<endl;

    //printing the last 20 records from each species code
    cout<<"-----------Printing the last 20 records from each species code"<<endl;
    mySample.printSampleRange(indexArray[0], size0-20, size0-1, fileStr);
    cout<<endl;
    mySample.printSampleRange(indexArray[1], size1-20, size1-1, fileStr);
    cout<<endl;
    mySample.printSampleRange(indexArray[2], size2-20, size2-1, fileStr);
    cout<<endl;
    mySample.printSampleRange(indexArray[3], size3-20, size3-1, fileStr);
    cout<<endl;
    mySample.printSampleRange(indexArray[4], size4-20, size4-1, fileStr);
    //-----------------------------------
    cout<<endl<<endl;

    try{

        while(choice != 0)
        {
            //Display choice options
            cout<<endl<<endl;
            cout<<"---------------- Please choose from 1 - 4 for Sample Records ---------------- "<<endl;
            cout<<"1: Print Researcher Name"<<endl;
            cout<<"2. Update Researcher Name"<<endl;
            cout<<"3. Delete Sample Record"<<endl;
            cout<<"4. Print certain range of Samples"<<endl;
            cout<<"0. Exit"<<endl;

            cin>>choice;

        if(choice == 1|| choice == 2 | choice == 3)
        {
            cout<<"H_SAP species(0) offset range is: 0-"<<size0-1<<endl;
            cout<<"M_MUS species(1) offset range is: 0-"<<size1-1<<endl;
            cout<<"D_MEL species(2) offset range is: 0-"<<size2-1<<endl;
            cout<<"E_COL species(3) offset range is: 0-"<<size3-1<<endl;
            cout<<"A_THA species(4) offset range is: 0-"<<size4-1<<endl<<endl<<endl;

            cout<<"Enter Sample's species code (0, 1, 2, 3 or 4): ";
            cin>>sCode;

                if(sCode >=0 &&  sCode <= 4)
                {
                    if(sCode == 0)
                    {
                        cout<<"Enter the offset: ";
                        cin>>offset;
                        if(offset < 0 || offset > size0-1)
                            throw MyException("ERROR: Invalid offset");

                    } else if(sCode == 1){
                        cout<<"Enter the offset: ";
                        cin>>offset;
                        if(offset < 0 || offset > size1-1)
                            throw MyException("ERROR: Invalid offset");

                    }else if(sCode == 2){
                        cout<<"Enter the offset: ";
                        cin>>offset;
                        if(offset < 0 || offset > size2-1)
                            throw MyException("ERROR: Invalid offset");

                    }else if(sCode == 3){
                        cout<<"Enter the offset: ";
                        cin>>offset;
                        if(offset < 0 || offset > size3-1)
                            throw MyException("ERROR: Invalid offset");

                    }else{
                        cout<<"Enter the offset: ";
                        cin>>offset;
                        if(offset < 0 || offset > size4-1)
                            throw MyException("ERROR: Invalid offset");
                    }

                } else{
                    cout<<"ERROR: Invalid species code"<<endl;
                    throw MyException("Error: Invalid species No!");
                }
        }
        if(choice == 4)
        {
            cout<<"H_SAP species(0) offset range is: 0-"<<size0-1<<endl;
            cout<<"M_MUS species(1) offset range is: 0-"<<size1-1<<endl;
            cout<<"D_MEL species(2) offset range is: 0-"<<size2-1<<endl;
            cout<<"E_COL species(3) offset range is: 0-"<<size3-1<<endl;
            cout<<"A_THA species(4) offset range is: 0-"<<size4-1<<endl<<endl<<endl;

            cout<<"Enter Sample's species code (0, 1, 2, 3 or 4): ";
            cin>>sCode;

            if(sCode >= 0 && sCode <= 4)
            {
                cout<<"Enter the start of range: ";
                cin>>rangeStart;
                cout<<"Enter the end of range: ";
                cin>>rangeEnd;
                int maxOff;
                if(sCode == 0) maxOff = size0 - 1;
                else if(sCode == 1) maxOff = size1 - 1;
                else if(sCode == 2) maxOff = size2 - 1;
                else if(sCode == 3) maxOff = size3 - 1;
                else maxOff = size4 - 1;
                while (rangeStart < 0 || rangeEnd > maxOff || rangeStart > rangeEnd) 
                {
                    cout<<"Please re-enter a valid range"<<endl;
                    cout<<"Enter the start of range: ";
                    cin>>rangeStart;
                    cout<<"Enter the end of range: ";
                    cin>>rangeEnd;
                }
            }else{
                cout<<"ERROR: Invalid species code"<<endl;
                throw MyException("Error: Invalid species code!");
            }
            
        }
        
            //options to choose from
            switch(choice)
            {
                case 1: 
                    mySample.displayResearcher(indexArray[sCode], offset, fileStr);
                    break;
                case 2:
                    cout<<"Enter a 20 char name to update record: ";
                    cin>>newName;
                    mySample.updateResearcher(indexArray[sCode], offset, newName, fileStr);
                    break;
                case 3:
                    mySample.deleteSample(indexArray[sCode], offset, fileStr);
                    break;
                case 4:
                    mySample.printSampleRange(indexArray[sCode], rangeStart, rangeEnd, fileStr);
                    break;
                case 0: 
                    return 0;
                    break;
                default:
                    cout<<"Invalid choice!"<<endl;

            };

        }

    }catch(MyException &e){
        cout<<e.what()<<endl;
    }catch(exception &e){
        cout<<e.what()<<endl;
    }

    return 0;
}
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Record {
    int id;
    char name[20];
};

void writeRecord(fstream& file, Record& rec) {
    file.write(reinterpret_cast<char*>(&rec), sizeof(Record));
}

Record readRecord(fstream& file) {
    Record rec;
    file.read(reinterpret_cast<char*>(&rec), sizeof(Record));
    return rec;
}

void printRecord(Record& rec) {
    cout << "ID: " << rec.id << ", Name: " << rec.name << endl;
}

int main() 
{
    fstream file("records.bin", ios::in | ios::out | ios::binary | ios::trunc); // trunc to clear the file

    if (!file) {
        cerr << "Error opening file.\n";
        return 1;
    }

    // Create and write 3 sample records
    
    Record r1 = {1, "Alice"};
    Record r2 = {2, "Bob"};
    Record r3 = {3, "Charlie"};


    writeRecord(file, r1);
    writeRecord(file, r2);
    writeRecord(file, r3);

    // seekg tellg (read) seekp tellp (write)

    // Get current put pointer position (should be end of file)
    streampos endPos = file.tellp();
    cout << "Put pointer after writing 3 records: " << endPos << endl;

    // Move get pointer to beginning of file
    file.seekg(0, ios::beg);

    // Read first record
    Record first = readRecord(file);
    cout << "First record read: ";
    printRecord(first);

    // Get current get pointer position
    streampos posAfterFirst = file.tellg();
    cout << "Get pointer after reading 1st record: " << posAfterFirst << endl;

    // Jump to 3rd record using seekg
    file.seekg(sizeof(Record) * 2, ios::beg);  // 0-based index: 2 = 3rd record
    Record third = readRecord(file);
    cout << "Third record read by seeking: ";
    printRecord(third);

    // Modify 2nd record in-place using seekp
    file.seekp(sizeof(Record) * 1, ios::beg);  // 2nd record
    Record r2_updated = {2, "Bobby"};
    writeRecord(file, r2_updated);
    cout << "Updated 2nd record in-place.\n";

    // Verify the updated record
    file.seekg(sizeof(Record) * 1, ios::beg);
    Record second = readRecord(file);
    cout << "Read updated 2nd record: ";
    printRecord(second);

    file.close();
    return 0;
}

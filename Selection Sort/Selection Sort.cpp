#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include "Person.h"
#include <sstream>

using namespace std;
vector<Person> record;
int comparisons;

// Match the attributes of Person class to the method parameters.
Person::Person(string n, int i, int a, string j, int h) {
    name = n;
    id = i;
    age = a;
    job = j;
    hireyear = h;
}

// A helper function that prints the ID to show the Bubble Sort process.
void printIdOnly() {
    for (Person person : record)
    {
        cout << person.getId() << " ";
    }
    cout << endl;
}

// Selection Sort algorithm
void selectionSort() {
    // starting from the first index down to the second last index. First index starts out as the smallest element.
    for (int i = 0; i < record.size()-1; i++) {
        int minIndex = i;
        // starting from the second index to the last index. 
        for (int j = i+1; j < record.size(); j++) {
            // increment of comparison counter by 1.
            comparisons += 1;
            // Compare the second index with the first index.Make it the minIndex if it is smaller the the previous element.
            if (record[j].getId() < record[minIndex].getId()) {
                minIndex = j;
            }
        }
        // swaps the minIndex to the leftmost side of the vector.
        swap(record[minIndex], record[i]);
        //printIdOnly();
    }
}


// writes the sorted record to a .txt file
void writeToFile() {
    ofstream ofs;
    ofs.open("C:/Users/Jason Tan/OneDrive - Brigham Young University Hawaii/Documents/output.txt");
    for (Person person : record) {
        ofs << person.getName() << "|" << person.getId() << "|" << person.getAge() << "|" << person.getJob() << "|" << person.getHireYear() << endl;
    }
}

// agrc = total argument count, argv = the arguments passed into the function
int main(int argc, char** argv) {
    // check for errors: missing argument or file not found
    if (argc == 1) {
        cout << "You forgot the command line parameter" << endl;
        exit(0);
    }
    ifstream ifs;
    ifs.open(argv[1], ios::in);
    if (!ifs) {
        cout << "could not find file " << argv[1] << endl;
        exit(0);
    }

    // checks the first line of the file to determine the number of records in the file, and the number of times to be looped.
    string firstLine;
    // getline gets the first line from the ifstream and stores it into a string variable
    getline(ifs, firstLine);
    // Convert firstLine into an int
    int recordNum = stoi(firstLine);


    for (int i = 0; i < recordNum; i++)
    {
        string nextLine;
        // gets the nextline
        getline(ifs, nextLine);

        string name;
        int id;
        int age;
        string job;
        int hireyear;

        char delimiter = '|';
        string words;
        stringstream ss(nextLine);
        // gets the next word until it spots a pipe "|" delimeter
        // initializing each object's fields with data from the file
        getline(ss, words, delimiter);
        name = words;
        getline(ss, words, delimiter);
        id = stoi(words);
        getline(ss, words, delimiter);
        age = stoi(words);
        getline(ss, words, delimiter);
        job = words;
        getline(ss, words, delimiter);
        hireyear = stoi(words);

        // instantiating a new object for each record in the file
        Person employee(name, id, age, job, hireyear);
        record.push_back(employee);
    }
    selectionSort();
    cout << "It took " << comparisons << " comparisons to sort this list.";
    //writeToFile();
}

// Big O of Selection Sort is O(n^2) because it has a nested loop.
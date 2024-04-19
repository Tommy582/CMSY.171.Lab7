// Written by Tommy Trinh
// April 18, 2024
// This program simulates a database that can read and write to
// text and binary files using linked lists
#include <iostream>
#include <iomanip>
#include <fstream>
#include <list>
#include <cstring>
#include <string>
#include <array>
#include <vector>
#include <cctype>
using namespace std;

// declare constants
const char ANIMAL_FILE[] = "c:\\test\\animal.dat",
SPECIES_FILE[] = "c:\\test\\species.txt";
const int
MIN_COUNT = 0,				// minimum number of animals
ADD_CHOICE = 1,				// choice to add an animal
DISPLAY_CHOICE = 2,			// choice to display animals
SEARCH_CHOICE = 3,			// choice to search animals
ENDANGERED_CHOICE = 4,		// choice to display endangered animals
QUIT_CHOICE = 5,			// choice to quit program
MENU_CHOICE_SIZE = 1,		// size of the menu choice field
ENDANGERED_POP = 100,		// population considered endangered
TYPE_SIZE = 25;				// size of the animal type field

// define structures
struct species
{
	char typeAnimal[TYPE_SIZE] = "none";	// stores type of animal
	char typeSpecies[TYPE_SIZE] = "none";	// species of animal
	int numAnimal = 0;						// stores number of animals
	bool endangered = false;				// flag for endangered
};

// function prototypes
void readAnimal(list<species>&, fstream&);

int main()
{
	// create an empty list of species
	list<species> myList;


	// Open the animal.dat file for read/write/binary mode
	fstream animalFile(ANIMAL_FILE, ios::in | ios::out | ios::binary);

	// if the file was opened, read the contents of the animal.dat file
	// otherwise give an error and end the program
	if (animalFile.fail())
	{
		cout << "Error - could not open animal.dat. Closing the program.";
		return 0;
	}
	else
	{
		readAnimal(myList, animalFile);
	}



	// display the values
	if (myList.empty())
		cout << "You have not entered any data, returning to menu.\n\n";
	else
	{
		for (auto it = myList.begin(); it != myList.end(); it++)
		{
			cout << "\nAnimal: " << it->typeAnimal << endl;
			cout << "The species is: " << it->typeSpecies << endl;
			cout << "Has a count of: " << it->numAnimal << endl;
			if (it->endangered)
				cout << "This animal is endangered!\n\n";
			else
				cout << "This animal is not endangered!\n\n";
		}
	}

	myList.clear();
	return 0;
}



void readAnimal(list<species>& myList, fstream& animalFile)
{
	species tempAnimal = { "","",0,false },
		tempFile;
	// read the first record
	animalFile.read(reinterpret_cast<char*>(&tempFile), sizeof(tempFile));
	while (!animalFile.eof())
	{
		// c strings are arrays so go through them one index at a time
		for (int index = 0; index < strlen(tempFile.typeAnimal); index++)
			tempAnimal.typeAnimal[index] = tempFile.typeAnimal[index];
		// same for species, one index at a time
		for (int index = 0; index < strlen(tempFile.typeSpecies); index++)
			tempAnimal.typeSpecies[index] = tempFile.typeSpecies[index];
		// copy over the ocunt and endangered flag
		tempAnimal.numAnimal = tempFile.numAnimal;
		tempAnimal.endangered = tempFile.endangered;
		// now that temp animal has all the info we need, we figure out where 
		// to put it.
		// Start with finding out if the list is empty or not
		if (myList.empty())
		{
			// if it is, then add the object 
			myList.push_back(tempAnimal);
		}
		else
		{   //else, figure out where to put it so that the list is in order when created
			auto test = myList.begin();	// set the value to the beginning
			bool flag = true;			// temp bool
			// test if the avalue is lower than the first, if it is, insert in the front
			if (strcmp(tempAnimal.typeAnimal, test->typeAnimal) < 0)
			{
				myList.push_front(tempAnimal);
				cout << tempAnimal.typeAnimal << " inside front " << test->typeAnimal << endl;
			}
			else
			{
				while (flag)
				{
					if (strcmp(tempAnimal.typeAnimal, test->typeAnimal) > 0)
					{
						myList.insert(test, tempAnimal);
						cout << tempAnimal.typeAnimal << " inside insert " << test->typeAnimal << endl;
						flag = false;
					}
					test++;
					// test if the value is greater than the last element, if it is, add it to the end
					if (test == myList.end())
					{
						myList.push_back(tempAnimal);
						cout << tempAnimal.typeAnimal << " inside back " << test->typeAnimal << endl;
						flag = false;
					}
				}
			}
		}
		// clear temp structure in preparation for the next loop
		tempAnimal = { "","",0,false };
		// read the next record
		animalFile.read(reinterpret_cast<char*>(&tempFile), sizeof(tempFile));
	}
}
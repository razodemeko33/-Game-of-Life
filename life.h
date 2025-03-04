/****************************************************
Name: Komal Adhikari
Date: 03/01/2025
Problem Number: 3
Hours spent solving the problem: around 24 hours
Instructor: Komogortsev, TSU
*****************************************************/

// This header file provides the prototypes for all functions
// used in the implementation of the Game of Life.

#ifndef LIFE_H
#define LIFE_H

#include <iostream>
#include <fstream>

using namespace std;

// Global variables
extern int ROWS;
extern int COLUMNS;
extern bool **GRID;

// Function prototypes
void populateWorld(const char *file);
void showWorld();
int countLiveNeighbors(bool **grid, int ROWS, int COLUMNS, int i, int j);
void iterateGeneration();


#endif
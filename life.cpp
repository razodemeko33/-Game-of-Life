/****************************************************
Name: Komal Adhikari
Date: 03/01/2025
Problem Number: 3
Hours spent solving the problem: around 24 hours
Instructor: Komogortsev, TSU
*****************************************************/

//This file provides the implementation of the life.h header file.
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

// GLOBAL VARIABLES
int ROWS = 0;
int COLUMNS = 0;
//dynamic allocation of memory
bool **GRID = nullptr;

// This function reads the input file for subsequent processing
void populateWorld(const char *file) {
    ifstream inFile(file);
    if (!inFile) {
        cerr << "Unable to open file " << file << endl;
        exit(1);
    }

    string line;
    // gets line and calculates the number of rows and columns
    while (getline(inFile, line)) {
        if (COLUMNS == 0) {
            COLUMNS = line.length(); // Get the length of the line
        }
        ROWS++;
    }

    //  to allocate memory for the grid
    GRID = new bool *[ROWS];
    for (int i = 0; i < ROWS; i++) {
        GRID[i] = new bool[COLUMNS];
    }

    // to reset file pointer to the beginning
    inFile.clear();
    inFile.seekg(0, ios::beg);

    // Populate the grid
    for (int i = 0; i < ROWS; i++) {
        getline(inFile, line);
        for (int j = 0; j < COLUMNS; j++) {
            //check if line[j] is 1 i.e alive and send true if 1 and 0 if false
            GRID[i][j] = (line[j] == '1');
        }
    }

    inFile.close();
}

// This function counts the number of live neighbors for a given cell
int countLiveNeighbors(bool **grid, int ROWS, int COLUMNS, int i, int j) {
    int count_alive = 0;

    if ((i > 0 && i < ROWS - 1) && (j > 0 && j < COLUMNS - 1)) { // Interior cells
        if (grid[i + 1][j + 1]) count_alive++; // Bottom right
        if (grid[i - 1][j - 1]) count_alive++; // Top left
        if (grid[i][j + 1]) count_alive++; // Right
        if (grid[i][j - 1]) count_alive++; // Left
        if (grid[i + 1][j]) count_alive++; // Bottom
        if (grid[i - 1][j]) count_alive++; // Top
        if (grid[i + 1][j - 1]) count_alive++; // Bottom left
        if (grid[i - 1][j + 1]) count_alive++; // Top right
    } else if (i == 0 || j == 0 || i == ROWS - 1 || j == COLUMNS - 1) { // Edge cells
        if (j < COLUMNS - 1 && grid[i][j + 1]) count_alive++; // Right
        if (j > 0 && grid[i][j - 1]) count_alive++; // Left
        if (i < ROWS - 1 && grid[i + 1][j]) count_alive++; // Bottom
        if (i > 0 && grid[i - 1][j]) count_alive++; // Top

        if (i < ROWS - 1 && j < COLUMNS - 1 && grid[i + 1][j + 1]) count_alive++; // Bottom-right
        if (i > 0 && j > 0 && grid[i - 1][j - 1]) count_alive++; // Top-left
        if (i < ROWS - 1 && j > 0 && grid[i + 1][j - 1]) count_alive++; // Bottom-left
        if (i > 0 && j < COLUMNS - 1 && grid[i - 1][j + 1]) count_alive++; // Top-right
    }

    return count_alive;
}

// This function outputs the grid for the current generation
void showWorld() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            //it checkts if GRID[i][j] is true or false if true prints 1 if not prints 0
            cout << (GRID[i][j] ? '1' : '0');
        }
        cout << endl;
    }
}
// This function creates a new generation grid from the old generation grid
void iterateGeneration() {
    bool **newGrid = new bool *[ROWS];
    for (int i = 0; i < ROWS; i++) {
        newGrid[i] = new bool[COLUMNS];
    }

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            int liveNeighbors = countLiveNeighbors(GRID, ROWS, COLUMNS, i, j);

            // Apply Conway's Game of Life rules
            if (GRID[i][j] && (liveNeighbors < 2 || liveNeighbors > 3)) {
                newGrid[i][j] = false; // Cell dies
            } else if (!GRID[i][j] && liveNeighbors == 3) {
                newGrid[i][j] = true; // Cell is born
            } else {
                newGrid[i][j] = GRID[i][j]; // Cell remains the same
            }
        }
    }

    // Copy the new grid back to the original grid
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            GRID[i][j] = newGrid[i][j];
        }
    }

    // Free memory allocated for newGrid
    for (int i = 0; i < ROWS; i++) {
        delete[] newGrid[i];
    }
    delete[] newGrid;
}
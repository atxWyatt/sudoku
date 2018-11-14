#include <iostream>
#include <fstream>

// Wyatt Turner
// jwt160030
// CS 1337 Section 001

using namespace std;

#define BOX_UL 0
#define BOX_UM 1
#define BOX_UR 2
#define BOX_ML 3
#define BOX_MM 4
#define BOX_MR 5
#define BOX_LL 6
#define BOX_LM 7
#define BOX_LR 8

using namespace std;

string getBoxName(int boxNumber) { // gets which name of the 3 by 3 is invalid.
    string ret;
    switch (boxNumber) {
        case 0:
            ret = "upper left";
            break;
        case 1:
            ret = "upper middle";
            break;
        case 2:
            ret = "upper right";
            break;
        case 3:
            ret = "middle left";
            break;
        case 4:
            ret = "middle";
            break;
        case 5:
            ret = "middle right";
            break;
        case 6:
            ret = "lower left";
            break;
        case 7:
            ret = "lower middle";
            break;
        case 8:
            ret = "lower right";
            break;
    }
    return ret;
}

int breakBox(int puzzleNumber, int boxNumber, int duplicate, ofstream &out) { // if a 3 by 3 is broken
    out << puzzleNumber << " \tinvalid \t" << "multiple " <<  duplicate << " in " << getBoxName(boxNumber) << endl; // gets the puzzle number, then which 3 by3 is invalid and writes it to the output file
    return 0;
}

int valid(int puzzleNumber, ofstream &out) { // if the puzzle is valid
    out << puzzleNumber << " \tvalid" << endl; // prints out valid
    return 0;
}

int invalidRow(int rowNumber, int puzzleNumber, int duplicate, ofstream &out) { // if a row has a duplicate
    out << puzzleNumber << " \tinvalid \t" << "multiple " << duplicate << " in row " << rowNumber << endl;
    return 0;
}

int invalidColumn(int columnNumber, int puzzleNumber, int duplicate, ofstream &out) { // if a column has a duplicate
    out << puzzleNumber << " \tinvalid \t" << "multiple " << duplicate << " in column " << columnNumber << endl;
    return 0;
}


int getBoxNumber(int column, int row) { // gets us which 3 by 3 is invalid, pretty self-explanatory
    switch (column) {
        case 0:
        case 1:
        case 2:
            switch (row) {
                case 0:
                case 1:
                case 2:
                    return BOX_UL;
                case 3:
                case 4:
                case 5:
                    return BOX_UM;
                case 6:
                case 7:
                case 8:
                    return BOX_UR;
            }
            break;
        case 3:
        case 4:
        case 5:
            switch (row) {
                case 0:
                case 1:
                case 2:
                    return BOX_ML;
                case 3:
                case 4:
                case 5:
                    return BOX_MM;
                case 6:
                case 7:
                case 8:
                    return BOX_MR;
            }
            break;
        case 6:
        case 7:
        case 8:
            switch (row) {
                case 0:
                case 1:
                case 2:
                    return BOX_LL;
                case 3:
                case 4:
                case 5:
                    return BOX_LM;
                case 6:
                case 7:
                case 8:
                    return BOX_LR;

            }
    }
    return 0;
}

bool validate3by3(int **puzzle, int puzzleNumber, int size, ofstream &out) {

    int position = 0;

    for(int i = 0; i < size; i+=3) { // starts to validate the puzzle, row by row, column by column, then 3 by 3
        int modColumn = i%3; // gets the box position
        for(int j = 0; j < size; j++) { // loops through the rows
            position = *(*(puzzle+i)+j);

            int modRow = j%3;

            if(modColumn == 0) {
                if(modRow == 0) {
                    if (*(*(puzzle+i+1)+j+1) == position) {
                        breakBox(puzzleNumber, getBoxNumber(i + 1, j + 1), position,out); // invalid 3 by 3
                        return false;
                    }

                    if (*(*(puzzle+i+1)+j+2) == position) {
                        breakBox(puzzleNumber, getBoxNumber(i + 1, j + 2), position,out);
                        return false;
                    }

                    if (*(*(puzzle+i+2)+j+1) == position) {
                        breakBox(puzzleNumber, getBoxNumber(i + 2, j + 1), position,out);
                        return false;
                    }


                    if (*(*(puzzle+i+2)+j+2) == position) {
                        breakBox(puzzleNumber, getBoxNumber(i + 2, j + 2), position,out);
                        return false;
                    }

                } else if(modRow == 1) {
                    if(*(*(puzzle+i+1)+j-1) == position) {
                        breakBox(puzzleNumber, getBoxNumber(i + 1, j + 1), position,out); // invalid 3 by 3
                        return false;
                    }


                    if(*(*(puzzle+i+1)+j+1) == position) {
                        breakBox(puzzleNumber, getBoxNumber(i+1,j+2), position,out);
                        return false;
                    }


                    if(*(*(puzzle+i+2)+j-1) == position) {
                        breakBox(puzzleNumber, getBoxNumber(i + 2, j + 1), position,out);
                        return false;
                    }

                    if(*(*(puzzle+i+2)+j+1) == position) {
                        breakBox(puzzleNumber, getBoxNumber(i + 2, j + 2), position,out);
                        return false;
                    }


                }else if(modRow == 2){
                    if(*(*(puzzle+i+1)+j-1) == position) {
                        breakBox(puzzleNumber, getBoxNumber(i + 1, j + 1), position,out); // invalid 3 by 3
                        return false;
                    }


                    if(*(*(puzzle+i+1)+j-2) == position) {
                        breakBox(puzzleNumber, getBoxNumber(i + 1, j + 2), position,out);
                        return false;
                    }

                    if(*(*(puzzle+i+2)+j-1) == position) {
                        breakBox(puzzleNumber, getBoxNumber(i + 2, j + 1), position,out);
                        return false;
                    }

                    if(*(*(puzzle+i+2)+j-2) == position) {
                        breakBox(puzzleNumber, getBoxNumber(i + 2, j + 2), position,out);
                        return false;
                    }

                }

            }

            if(modColumn == 1) {
                if(modRow == 0) {
                    if (*(*(puzzle+i-1)+j+1) == position) { // changed this from +1 +1 to -1 +1 cause it was redundant, might be an error
                        breakBox(puzzleNumber, getBoxNumber(i + 1, j + 1), position,out); // invalid 3 by 3
                        return false;
                    }

                    if (*(*(puzzle+i-1)+j+2) == position) {
                        breakBox(puzzleNumber, getBoxNumber(i + 1, j + 2), position,out);
                        return false;
                    }

                    if (*(*(puzzle+i+1)+j+1) == position) {
                        breakBox(puzzleNumber, getBoxNumber(i + 2, j + 1), position,out);
                        return false;
                    }

                    if (*(*(puzzle+i+1)+j+2) == position) {
                        breakBox(puzzleNumber, getBoxNumber(i + 2, j + 2), position,out);
                        return false;
                    }
                }else if(modRow == 1) {
                    if(*(*(puzzle+i-1)+j-1) == position) {
                        breakBox(puzzleNumber, getBoxNumber(i + 1, j + 1), position,out); // invalid 3 by 3
                        return false;
                    }

                    if(*(*(puzzle+i-1)+j+1) == position) {
                        breakBox(puzzleNumber, getBoxNumber(i + 1, j + 2), position,out);
                        return false;
                    }

                    if(*(*(puzzle+i+1)+j-1) == position) {
                        breakBox(puzzleNumber, getBoxNumber(i + 2, j + 1), position,out);
                        return false;
                    }

                    if(*(*(puzzle+i+1)+j+1) == position) {
                        breakBox(puzzleNumber, getBoxNumber(i + 2, j + 2), position,out);
                        return false;
                    }


                }else if(modRow == 2){
                    if(*(*(puzzle+i-1)+j-1) == position) {
                        breakBox(puzzleNumber, getBoxNumber(i + 1, j + 1), position,out); // invalid 3 by 3
                        return false;
                    }

                    if(*(*(puzzle+i-1)+j+1) == position) {
                        breakBox(puzzleNumber, getBoxNumber(i + 1, j + 2), position,out);
                        return false;
                    }

                    if(*(*(puzzle+i-1)+j-2) == position) {
                        breakBox(puzzleNumber, getBoxNumber(i + 2, j + 1), position,out);
                        return false;
                    }

                    if(*(*(puzzle+i+1)+j-2) == position) {
                        breakBox(puzzleNumber, getBoxNumber(i + 2, j + 2), position,out);
                        return false;
                    }

                }
            }

            if(modColumn == 2) {
                if(modRow == 0) {
                    if (*(*(puzzle+i-1)+j+1) == position) {
                        breakBox(puzzleNumber, getBoxNumber(i + 1, j + 1), position,out); // invalid 3 by 3
                        return false;
                    }

                    if (*(*(puzzle+i-1)+j+2) == position) {
                        breakBox(puzzleNumber, getBoxNumber(i + 1, j + 2), position,out);
                        return false;
                    }

                    if (*(*(puzzle+i-2)+j+1) == position) {
                        breakBox(puzzleNumber, getBoxNumber(i + 2, j + 1), position,out);
                        return false;
                    }

                    if (*(*(puzzle+i-2)+j+2) == position) {
                        breakBox(puzzleNumber, getBoxNumber(i + 2, j + 2), position,out);
                        return false;
                    }
                }else if(modRow == 1) {
                    if(*(*(puzzle+i-1)+j-1) == position) {
                        breakBox(puzzleNumber, getBoxNumber(i + 1, j + 1), position,out); // invalid 3 by 3
                        return false;
                    }

                    if(*(*(puzzle+i-1)+j+1) == position) {
                        breakBox(puzzleNumber, getBoxNumber(i + 1, j + 2), position,out);
                        return false;
                    }

                    if(*(*(puzzle+i-2)+j-1) == position) {
                        breakBox(puzzleNumber, getBoxNumber(i + 2, j + 1), position,out);
                        return false;
                    }

                    if(*(*(puzzle+i-2)+j+1) == position) {
                        breakBox(puzzleNumber, getBoxNumber(i + 2, j + 2), position,out);
                        return false;
                    }


                }else if(modRow == 2){
                    if(*(*(puzzle+i-1)+j-1) == position) {
                        breakBox(puzzleNumber, getBoxNumber(i + 1, j + 1), position,out); // invalid 3 by 3
                        return false;
                    }

                    if(*(*(puzzle+i-2)+j-1) == position) {
                        breakBox(puzzleNumber, getBoxNumber(i + 1, j + 2), position,out);
                        return false;
                    }

                    if(*(*(puzzle+i-1)+j-2) == position) {
                        breakBox(puzzleNumber, getBoxNumber(i + 2, j + 1), position,out);
                        return false;
                    }

                    if(*(*(puzzle+i-2)+j-2) == position) {
                        breakBox(puzzleNumber, getBoxNumber(i + 2, j + 2), position,out);
                        return false;
                    }

                }
            }
        }
    }
    valid(puzzleNumber,out); // if the puzzle is valid, we go to the valid method
    return true;

}

bool validate9by9(int **puzzle, int puzzleNumber, int size, ofstream &out) { // this bool validates the rows and columns

    int positionRow;
    int positionColumn;

    for (int i = 0; i < size; i++) { // starts to validate the puzzle, row by row, column by column, then 3 by 3
        for (int j = 0; j < size; j++) {     // loops through the rows
            positionRow = *(*(puzzle+i)+j);
            positionColumn = *(*(puzzle+i)+j);
            for (int k = i + 1; k < size; k++) { // loops through the columns
                if (positionColumn == *(*(puzzle+k)+j)) { // if the column has a duplicate
                    invalidColumn(j+1, puzzleNumber, positionColumn,out); // invalid column
                    return false;
                }
            }
            for (int k = j + 1; k < size; k++) {
                if (positionRow == *(*(puzzle+i)+k)) { // if the row has a duplicate
                    invalidRow(i+1, puzzleNumber, positionRow,out); // invalid row
                    return false;
                }
            }

        }
    }
            validate3by3(puzzle, puzzleNumber, size, out); // if the rows and colums are valid, we move onto 3 by 3's
            return true;
}


int main()
{
    int puzzleNumber = 0; // number placeholder
    int size = 9; // the size of the dimensions of the array
    char digit; // character placeholder
    int **puzzle; // array initializer
    puzzle = new int *[size]; // array initializer
    ifstream in("puzzles.txt"); // creates in the input file
    ofstream out("solutions.txt"); // creates the output file

    while(in.peek() != EOF) {

        in >> puzzleNumber;


        for(int i = 0; i <= size; i++) { // instantiates the other dimension of the array
            puzzle[i] = new int[size];
        }

        for(int column = 0; column < size; column++) { // reads in columns
            for(int row = 0; row < size; row++) { // reads in rows
                in >> digit;
                puzzle[column][row] = digit - '0'; // reads in the array from the fule
            }
        }

        validate9by9(puzzle,puzzleNumber,size,out); // validates the rows and columns

    }

    return 0;
}

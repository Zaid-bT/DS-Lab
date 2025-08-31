#include <iostream>
using namespace std;

class DynamicMatrix{
    int** matrix;
    int rows, cols;

public:
    // constructor
    DynamicMatrix(int r, int c) {
        rows = r;
        cols = c;
        allocateMatrix();
    }

    // Allocate memory for matrix
    void allocateMatrix(){
        matrix = new int*[rows];
        for (int i = 0; i < rows; ++i)
            matrix[i] = new int[cols]();
    }

    // Deallocate memory
    void deallocateMatrix() {
        for (int i = 0; i < rows; ++i)
            delete[] matrix[i];
        delete[] matrix;
    }


    // destructor 
    ~DynamicMatrix(){
        deallocateMatrix();
    }
    
    // resizing
    void resizeMatrix(int newRows, int newCols, int initVal = 0) {
        int** newMatrix = new int*[newRows];
        for (int i = 0; i < newRows; ++i)
            newMatrix[i] = new int[newCols];

        for (int i = 0; i < newRows;++i) {
            for (int j = 0; j < newCols; ++j) {
                if (i < rows && j < cols)
                    newMatrix[i][j]=matrix[i][j];
                else
                    newMatrix[i][j]=initVal;
            }
        }
        // Deallocate old matrix
        deallocateMatrix();

        // Update pointers and size
        matrix = newMatrix;
        rows = newRows;
        cols = newCols;
    }

    // Transpose
    void transposeMatrix() {
        int** transposed = new int*[cols];
        for (int i = 0; i < cols; ++i)
            transposed[i] = new int[rows];
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                transposed[j][i]=matrix[i][j];

        // Deallocate old matrix
        deallocateMatrix();

        // Update matrix, rows, and cols
        matrix = transposed;
        swap(rows, cols);
    }

    // Fill the matrix with user input
    void fillMatrix() {
        cout << "Enter elements (" << rows << "x" << cols << "):\n";
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                cin >> matrix[i][j];
    }

    // add 2 to each odd index
    void addTwoToOddIndex(){
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                if ((i + j) % 2 == 1)
                    matrix[i][j] += 2;
    }

    // display matrix
    void printMatrix(){
        cout << "Matrix (" << rows << "x" << cols << "):\n";
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j)
                cout << matrix[i][j] << "\t";
            cout << endl;
        }
    }
};

int main() {
    int rows, cols;
    cout << "Enter initial matrix size (rows cols): ";
    cin >>rows>>cols;

    DynamicMatrix arr(rows, cols);
    arr.fillMatrix();

    cout <<"\nOriginal Matrix:\n";
    arr.printMatrix();

    // Resize
    int newRows, newCols, initVal;
    cout << "\nEnter new size (rows cols) and initial value for new cells: ";
    cin >> newRows >> newCols >> initVal;
    arr.resizeMatrix(newRows, newCols, initVal);

    cout << "\nMatrix after resizing:\n";
    arr.printMatrix();

    // Transpose
    arr.transposeMatrix();
    cout << "\nMatrix after transposition:\n";
    arr.printMatrix();

    // Add 2 to odd indices
    arr.addTwoToOddIndex();
    cout << "\nMatrix after adding 2 to odd indices:\n";
    arr.printMatrix();

    arr.deallocateMatrix(); //freeing memory space
    return 0;
}


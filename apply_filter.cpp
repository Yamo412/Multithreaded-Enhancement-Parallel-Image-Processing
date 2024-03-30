#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

void applyKernel(int *image[], int *mask[], int mask_size, int image_row, int image_column)
{

    int border = 0;
    for (int i = border; i < image_row - border; i++)
    {
        for (int j = border; j < image_column - border; j++)
        {
            int sum = 0;
            for (int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    sum += image[(i + k - border) % image_row][(j + l - border) % image_column] * mask[k][l];
                }
            }
            image[i][j] = sum;
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        cerr << argv[0] << " Error argv " << endl;
        return 1;
    }

    string inputFile = argv[1];
    string maskFile = argv[2];
    string outputFile = argv[3];

    ifstream input(inputFile);
    int row, column;
    input >> row;
    input >> column;

    int **Input = new int *[row];
    for (int i = 0; i < row; i++)
        Input[i] = new int[column];

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
            input >> Input[i][j];
    }
    input.close();

    ifstream mask(maskFile);
    int size;
    mask >> size;
    int **Mask = new int *[size];
    for (int i = 0; i < size; i++)
        Mask[i] = new int[size];
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
            mask >> Mask[i][j];
    }

    applyKernel(Input, Mask, size, row, column);

    ofstream output(outputFile);
    // output<<row;//y
    // output<<column;//x
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
            output << Input[i][j] << " ";
        output << "\n";
    }
    output.close();

    for (int i = row - 1; i >= 0; i--)
        delete[] Input[i];
    for (int i = size - 1; i >= 0; i--)
        delete[] Mask[i];
    delete[] Input;
    delete[] Mask;
    Input = NULL;
    Mask = NULL;
    cout << "Execute End";
    return 0;
}

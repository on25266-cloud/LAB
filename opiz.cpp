#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;
void checkValidInput()
{
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(10000, '\n');
        throw "Incorrect input! A number was expected.";
    }
}
void checkValidParams(int n)
{
    if (n <= 4)
    {
        throw "Input correct data! n must be > 4.";
    }
}

double calculate(double x, int n)
{
    double y;

    if (x <= 0)
    {
        y = 1.0;
        for (int i = 1; i < n; i++)
        {
            y *= (i + i);
        }
    }
    else
    {
        y = 0.0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                y += (x + j) / double(i + j + 1);
            }
        }
    }

    return y;
}

void checkFileOpen(const ofstream& file)
{
    if (!file.is_open())
        throw "Error: Cannot open file for writing!";
}

void checkFileOpen(const ifstream& file)
{
    if (!file.is_open())
        throw "Error: Cannot open file for reading!";
}

void printResult(double x, int n, double y, ofstream* outputFile = nullptr)
{
    cout << fixed << setprecision(6);
    cout << "\nResult:\n";
    cout << "x = " << x << ", n = " << n << "  ->  y = " << y << "\n";

    if (outputFile && outputFile->is_open())
    {
        *outputFile << fixed << setprecision(6);
        *outputFile << "x = " << x
                    << ", n = " << n
                    << "  ->  y = " << y << "\n";
    }
}

int main()
{
    double x;
    int    n;
    bool   saveToFile;
    int    inputMode;

    cout << "Program: calculate y(x, n)\n\n";

    cout << "Save result to file? (1 = Yes, 0 = No): ";
    cin  >> saveToFile;
    checkValidInput();   

    cout << "\nInput mode:\n";
    cout << "   1 — Manual input (keyboard)\n";
    cout << "   2 — Read from file\n";
    cout << "Choose (1 or 2): ";
    cin  >> inputMode;
    checkValidInput();

    ofstream resultFile;

    try
    {
        if (inputMode == 1)
        {
            cout << "\nEnter x: ";
            cin >> x;
            checkValidInput();

            cout << "Enter n (integer > 4): ";
            cin >> n;
            checkValidInput();
        }
        else if (inputMode == 2)
        {
            string filename;
            cout << "\nEnter filename with parameters (x n): ";
            cin >> filename;

            ifstream in(filename);
            checkFileOpen(in);

            in >> x >> n;
            if (in.fail())
            {
                throw "Incorrect data format in input file!";
            }
            in.close();

            cout << "Parameters loaded successfully:\n";
            cout << "x = " << x << ", n = " << n << "\n\n";
        }
        else
        {
            throw "Invalid input mode!";
        }

        checkValidParams(n);

        if (saveToFile)
        {
            string filename;
            cout << "Enter filename to save result (e.g. result.txt): ";
            cin >> filename;

            resultFile.open(filename);
            checkFileOpen(resultFile);

            cout << "Result will be saved to: " << filename << "\n\n";
        }

        double y = calculate(x, n);    
        printResult(x, n, y, saveToFile ? &resultFile : nullptr);

        if (resultFile.is_open())
        {
            resultFile.close();
            cout << "\nResult successfully saved to file!\n";
        }

        cout << "\nProgram finished successfully.\n";
    }
    catch (const char* msg)
    {
        cerr << "\nERROR: " << msg << endl;
        return 1;
    }
    catch (...)
    {
        cerr << "\nFATAL: Unknown error occurred.\n";
        return 1;
    }

    return 0;
}

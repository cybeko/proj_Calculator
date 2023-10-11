using namespace std;
#include <iostream>

class Exception
{
protected:
    char m_message[30];
public:
    Exception(const char* message)
    {
        strcpy_s(m_message, message);
    }
    const char* GetMessage() const
    {
        return m_message;
    }
};
class ArraySizeException : public Exception
{
public:
    ArraySizeException(const char* message) : Exception(message) {}
};
class ArrayDataException: public Exception
{
public:
    ArrayDataException(const char* message) : Exception(message) {}
};

class ArrayValueCalculator
{
public:
    int doCalc(const char* array[4][4])
    {
        int sum = 0;
        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                try
                {
                    int value = parseInt(array[i][j]);
                    sum += value;
                }
                catch (ArrayDataException exception)
                {
                    cout << "Error. Row: [" << i << "], col: [" << j << "]: ";
                    throw;
                }
            }
        }
        return sum;
    }
    int parseInt(const char* value)
    {
        char* ch;
        int result = strtol(value, &ch, 10);
        if (*ch != '\0')
        {
            throw ArrayDataException("Invalid data");
        }
        return result;
    }
};
int main()
{
    const char* array[5][4] =
    {
        {"?", "1", "1", "1"},
        {"2", "2", "2", "2"},
        {"3", "3", "3", "3"},
        {"4", "4", "4", "4"}
    };
    try
    {
        if (sizeof(array) / sizeof(array[0]) != 4)
        {
            throw ArraySizeException("Error. Invalid array size");
        }

        ArrayValueCalculator calculator;
        int res = calculator.doCalc(array);
        cout << "Result: " << res << endl;
    }
    catch (ArraySizeException exception)
    {
        cout << exception.GetMessage() << endl;
    }
    catch (ArrayDataException exception)
    {
        cout << exception.GetMessage() << endl;
    }
    return 0;
}
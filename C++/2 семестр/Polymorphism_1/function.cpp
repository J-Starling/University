#include "function.h"

ostream& operator<<(ostream& output, const Function& function)
{
    function.print(output);
    return output;
}

istream& operator>>(istream& input, Function& function)
{
    function.manualInput(input);
    return input;
}

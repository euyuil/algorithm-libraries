#include <cmath>
#include <cstdio>
#include <cctype>
#include <cassert>
#include <cstring>
#include <cstdlib>

using namespace std;

const long double PI = 3.14159265358979323846264338327950288L;

long double calc_function(char **expr)
{
    long double buf = 0.0;
    long double calc_sum(char **expr);

    if (**expr)
    {
        if (isdigit(**expr) || **expr == '+' || **expr == '-')
            buf = strtod(*expr, expr);
        else if (!strncmp(*expr, "pi", 2))
            *expr += 2, buf = PI;
        else if (**expr == '(')
            ++(*expr), buf = calc_sum(expr), ++(*expr);
        else if (!strncmp(*expr, "sin", 3))
            *expr += 3, buf = sin(calc_function(expr));
        else if (!strncmp(*expr, "cos", 3))
            *expr += 3, buf = cos(calc_function(expr));
        else if (!strncmp(*expr, "tan", 3))
            *expr += 3, buf = tan(calc_function(expr));
        else
            assert(!"Syntax error.");
        while (**expr == ' ')
            ++(*expr);
    }

    return buf;
}

long double calc_product(char **expr)
{
    long double buf = 1.0; char sign = '*';

    while (**expr)
    {
        long double res = calc_function(expr);
        if (sign == '*')
            buf *= res;
        else if (sign == '/')
            buf /= res;
        else
            assert(!"Please contact support staff.");
        sign = **expr;
        if (**expr != '*' && **expr != '/')
            break;
        while (*(++(*expr)) == ' ');
    }

    return buf;
}

long double calc_sum(char **expr)
{
    long double buf = 0.0, sign = 1.0;

    while (**expr)
    {
        long double res = calc_product(expr);
        buf += sign * res;
        if (**expr == '+')
            sign = 1.0;
        else if (**expr == '-')
            sign = -1.0;
        else
            break;
        while (*(++(*expr)) == ' ');
    }

    return buf;
}

inline long double calc(char *expr)
{
    while (*expr == ' ')
        ++expr;
    return calc_sum(&expr);
}

char buffer[1024];
char test_cases[][1024] =
{
    "tan(pi/2)",
    "2 + cospi",
    "2+sin(pi/2)",
    "2+tan(0)",
    "1+1",
    "1+(2+3)*4"
};
const size_t N = sizeof(test_cases) / sizeof(*test_cases);

int main()
{
    printf("Preset test cases:\n");
    for (int i = 0; i < N; ++i)
        printf("%s = %Lg\n", test_cases[i], calc(test_cases[i]));
    printf("\nEnter your manual test cases:\n");
    while (gets(buffer))
        printf("%Lg\n", calc(buffer));
    return 0;
}


#include <stdbool.h>

#define DIMS 9
bool    recursive_propagation(int **arr, int x, int y);

bool    next_xy(int **arr, int x, int y)
{
    if (x < DIMS - 1)
        ++x;
    else
        x = 0;
    if (x)
        ++y;
    else
        y = 0;
    return recursive_propagation(arr, x, y);
}

bool    recursive_propagation(int **arr, int x, int y)
{
    int    temp;
    int    i;
    int    status;
    
    if (!arr[y][x])
        return (false);
    else if (x == DIMS - 1 && y == DIMS - 1)
        return (true);
    temp = arr[y][x];
    while (arr[y][x]) {
        while ((arr[y][x] & (1UL << i)) == 0 && i < DIMS)
            i++;
        if (propagate_constraints(arr, x, y, i) == false) {
            arr[y][x] &= ~(1UL << i);
            continue ;
        }
        if (next_xy(arr, x, y) == true)
            return true;
    }
    arr[y][x] = temp;
    return (false);
}

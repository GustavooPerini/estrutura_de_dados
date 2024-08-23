
#include <stdio.h>

#include "list.h"

int main()
{
    int n, val;

    List *l = list_construct();

    // fill the list by adding values to the end
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &val);
        list_push_back(l, val);
    }

    // uses the back iterator to double the values
    ListIterator *it = list_back_iterator(l);

    while (!list_iterator_is_over(it))
    {
        data_type *data = list_iterator_previous(it);
        (*data) *= 2;
    }

    list_iterator_destroy(it);

    // use the front iterator to print the values
    it = list_front_iterator(l);

    while (!list_iterator_is_over(it))
    {
        data_type *data = list_iterator_next(it);
        printf("%d\n", *data);
    }

    // test the destroy function
    list_iterator_destroy(it);
    list_destroy(l);

    return 0;
}
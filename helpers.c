/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */

bool search(int value, int values[], int n)
{
    
    int polovina=n/2;
    int marker=n-1;
// бинарный поиск    
    while (values[marker]!=value)// пока маркер не искомое число
    {
        if (values[0]>value || values[n-1]<value)// если число не в диапазоне
            return false;
        if (marker==0 && values[marker]<value && values[marker+1]>value)// если число больше [0] и меньше [1]
            return false;
        if (marker!=0 && values[marker]>value && values[marker-1]<value)// если число меньше текущего и больше соседнего слева
            return false;
        
        if (values[marker]<value)// если число больше текущего берем правую половину
        {
            marker=marker+polovina;
        }
        else// иначе левую
        {
            marker=marker-polovina;
        }
        polovina=polovina/2;// срез половины
        if (polovina==0)// если (1/2) половина равна нулю
        {
            polovina=1;
        }
    }
    return true;// ура, нашли
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
// пузырьковая сортировка
    int bufer;
    
    for (int i=0;i!=n-1;n--)
    {
        for (int j=0;j<n-1;j++)
        {
            if (values[j]>values[j+1])
            {
                bufer=values[j],values[j]=values[j+1];
                values[j+1]=bufer;
            }
        }
    }
    
    return;
}


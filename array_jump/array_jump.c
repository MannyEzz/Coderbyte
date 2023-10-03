# -*- coding: utf-8 -*-
"""
Have the function ArrayJumping(arr) take the array of numbers stored in arr
and first determine the largest element in the array,
and then determine whether or not you can reach that same element within
the array by moving left or right continuously according to whatever integer
is in the current spot. If you can reach the same spot within the array,
then your program should output the least amount of jumps it took.

For example: if the input is [2, 3, 5, 6, 1] you'll start at the spot where
6 is and if you jump 6 spaces to the right while looping around the array you
end up at the last element where the 1 is. Then from here you jump 1 space to
the left and you're back where you started, so your program should output 2.
If it's impossible to end up back at the largest element in the array your
program should output -1. The largest element in the array will never equal
the number of elements in the array. The largest element will be unique. 

Input:1,2,3,4,2
Output:3

Input:1,7,1,1,1,1
Output:2
"""
/**
  ******************************************************************************
  * @file    array_jump.c
  * @author  Mamdouh Ezzeldin - Embedded Systems Engineer
  * @version V1.0.0
  * @date    2-october-2023
  * @brief   This file contains all the functions implementation for the array jump problem.
   ******************************************************************************
  */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
  * @addtogroup array_jump_Global_variables
  * @{
  */
int right_left_array[6][2];
int step_array[6];
int counter=0;

/**
  * @brief  jump left and return the index after the jump.
  * @param  arr_lenght: lenght of the array given.
  * @param  index: the index of number in the array provided.
  * @param  number: number in the array.
  * @retval return the index after the jump.
  */
int left(int arr_lenght,int index, int number)
{
    int left = number % arr_lenght;
    if (left>index)
    {
        left = arr_lenght + index - left;
    }
    else
    {
        left = index - left;
    }
    return left;
}

/**
  * @brief  jump right and return the index after the jump.
  * @param  arr_lenght: lenght of the array given.
  * @param  index: the index of number in the array provided.
  * @param  number: number in the array.
  * @retval return the index after the jump.
  */
int right(int arr_lenght,int index, int number)
{
    int right = number % arr_lenght;
    if(right>arr_lenght-index-1)
    {
        right = right + index - arr_lenght;
    }
    else
    {
        right = index + right;
    }
    return right;
}

/**
  * @brief  Check if a member is inserted in the array or not.
  * @param  step_array: Array to check if the member in or not.
  * @param  value: member need to check on.
  * @retval return 1 or 0 depend whether the member is in the array or not.
  */
bool is_member(int *step_array,int value)
{
    for (int i=0; i<counter;i++)
    {
        if(step_array[i]==value)
        {
            return 1;
        }
    }
    return 0;
}

/**
  * @brief  determine whether or not you can reach that same largest element within the array by moving left or right continuously.
  * @param  arr: array of numbers stored.
  * @param  arr_lenght: length of the array provided.
  * @retval return least amount of jumps it took to return to the same spot.
  */
int array_jump(int *arr, int arr_lenght)
{
    int maxnumber=-1,maxindex=-1;
    
    /*get the maxnumber and its index*/
    for(int i=0;i<arr_lenght;i++)
    {
        if(arr[i]>maxnumber)
        {
            maxnumber = arr[i];
            maxindex = i;
        }
    }
    //printf("%d %d \n",maxnumber,index);
    
    /*check if the arr_lenght is equal to the maxnumber*/
    if( maxnumber == arr_lenght)
    {
        return 1;
    }
    
    /*move left and right and save in 2D array*/
    for(int i=0; i<arr_lenght; i++)
    {
        right_left_array[i][0]=right(arr_lenght,i, arr[i]);
        right_left_array[i][1]=left(arr_lenght,i, arr[i]);
        //printf("%d ",i);
        //printf("%d ",right_left_array[i][0]);
        //printf("%d \n",right_left_array[i][1]);
    }
    
    /*add the right and left jump of the maxnumber to the step array*/
    step_array[0] = right_left_array[maxindex][0];
    step_array[1]  = right_left_array[maxindex][1];
    /*increment the counter with the two as two value are added*/
    counter = 2;
    
    for(int i=2;i<arr_lenght+1;i++)
    {
        int temp_counter = counter;
        /*loop to add the next index jump and check to prevent repeated index*/
        for(int j=0; j< temp_counter; j++)
        {
            if (!is_member(step_array,right_left_array[step_array[j]][0]))
            {
                step_array[counter] = right_left_array[step_array[j]][0];
                counter = counter+1;
            }
            if (!is_member(step_array,right_left_array[step_array[j]][1]))
            {
                step_array[counter] = right_left_array[step_array[j]][1];
                counter = counter+1;
            }
        }
        /*loop on the step array and check if the index of the max value is found in it*/
        for(int x=2;x<counter;x++)
        {
            if(step_array[x]==maxindex)
            {
                return i;
            }
        }
    }
    /*return -1 if there is no way to return to the same index*/
    return -1;
}

int main()
{
    int number_of_jumbs=0;
    int arr_lenght = 6;
    int arr[6] = {2,3,5,4,7,1};
    //int arr[2] = {2,3};
    //int arr[6] = {1,7,1,1,1,1};
    number_of_jumbs = array_jump(arr,arr_lenght);
    printf("%d \n",number_of_jumbs);
    return 0;
}

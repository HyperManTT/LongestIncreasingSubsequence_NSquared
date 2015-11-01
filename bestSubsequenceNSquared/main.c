//
//  main.c
//  bestSubsequenceNSquared
//
//  Created by Randy Ram on 9/20/15.
//  Copyright (c) 2015 Randy Ram. All rights reserved.
//

#include <stdio.h>

//Model each array entry as a node structure
struct node
{
    int value;
    int longestSequence;
    struct node* next;
};


/*
 Function to reverse print a linkedlist
 */
void reversePrint(struct node* tail)
{
    if (tail == NULL)
    {
        return;
    }
    reversePrint(tail->next);
    printf("%d ", tail->value);
}


/*
 Find the longest subseqence of an array 
 of integers in time proportional to O(n^2)
 */
void findLongestSubseq(int* arr, int size)
{
    //Store each item as a struct in an array.
    struct node nodeArray[size];
    int itr;
    for (itr = 0; itr < size; itr++) {
        nodeArray[itr].value = arr[itr];
        nodeArray[itr].next = NULL;
        nodeArray[itr].longestSequence = 1;
    }
    
    int i, j, startingIndex, currentSubseq, longestCurrentSubseq = 1;
    int longestOverallSubsequence = 0, indexOfLongestOverall = 0;
    for (i = 1; i < size; i++)
    {
        // Set the starting index to the value being evaluated
        startingIndex = i;
        for (j = 0; j < i; j++)
        {
            if (nodeArray[i].value > nodeArray[j].value)
            {
                currentSubseq = nodeArray[i].longestSequence + nodeArray[j].longestSequence;
                if (currentSubseq > longestCurrentSubseq)
                {
                    longestCurrentSubseq = currentSubseq;
                    startingIndex = j;
                    
                    //If we have found the longest subsequence, save it and it's index.
                    if(longestCurrentSubseq > longestOverallSubsequence)
                    {
                        longestOverallSubsequence = longestCurrentSubseq;
                        indexOfLongestOverall = i;
                    }
                }
                
            }
        }
        /*
         If the starting index has changed to another number other than i,
         that means we've found a larger subsequence. Make the necessary changes
         now.
         */
        if (startingIndex != i)
        {
            nodeArray[i].longestSequence = longestCurrentSubseq;
            nodeArray[i].next = &nodeArray[startingIndex];
        }
        
        longestCurrentSubseq = 1; //Reset this value before next iteration begins
    }
    
    
    //Print the greatest increasing subsequence
    reversePrint(&nodeArray[indexOfLongestOverall]);
    
}

int main(int argc, const char * argv[]) {
    int size = 0;
    int numberReadIn;
    int arr[100]; // Cater for max of 100 numbers
    
    //Xcode runs exe file from a temp directory, so I have to specify full path
    FILE* in = fopen("/Users/randy/Developer/bestSubsequenceNSquared/bestSubsequenceNSquared/input.txt", "r");
    if (in == NULL) {
        printf("Could not open file");
        return -1;
    }
    while (fscanf(in, "%d", &numberReadIn) != EOF && size < 100) {
        if (numberReadIn == -9999) //Check for another termination condition
        {
            break;
        }
        else
        {
            arr[size] = numberReadIn;
            size++;
        }
    }
    fclose(in);
    findLongestSubseq(arr, size);
}

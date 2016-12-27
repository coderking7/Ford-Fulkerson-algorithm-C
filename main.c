//
//  main.c
//  AAA
//
//  Created by Андрей Рычков on 15.12.14.
//  Copyright (c) 2014 Андрей Рычков. All rights reserved.
//

#include <stdio.h>
#include <memory.h>

int findFlow(int n, int c[n][n], int f[n][n], int anc[n], int que[n], int flow[n])
{
    int qCurrent = 0; // Number of the first element in the queue
    int qNumber = 1; // Number of items in the queue
    que[0] = 0; // The first peak - source
    
    anc[n-1] = -1; // There is no flow of ancestors
    
    memset(flow, 0, sizeof(int) * n); //Zeroing all streams
    flow[0] = INT32_MAX; // The source is not limitedен
    
    int curV; // CurrentVertex
    
    // Until we get to the end or not to end the top of queue
    while (anc[n-1] == -1 && qCurrent < qNumber)
    {
        curV = *(que + qCurrent); // Removing the top of the queue
        for (int i = 0; i < n; ++i)
        {
            if ( ( c[curV][i] - f[curV][i] > 0 ) && ( flow[i] == 0 ) )
            {
                que[qNumber] = i; // Adding to all the current vertex
                qNumber++; // Increment number of items
                
                anc[i] = curV; // Current peak - ancestor found
                if ( c[curV][i] - f[curV][i] < flow[curV] )
                {
                    flow[i] = c[curV][i];
                } else
                {
                    flow[i] = flow[curV];
                }
            }
        }
        qCurrent++;
    }
    
    if ( anc[n-1] == -1 )
    {
        return 0; // If there is no flow of ancestors, the increasing path was not found
    }
    
    curV = n - 1;
    
    while (curV != 0)
    {
        // We go from drain to source back, adding flows
        f[anc[curV]][curV] += flow[n-1];
        curV = anc[curV];
    }
    
    return *(flow + n - 1);
}

int findMaxFlow(int n, int c[n][n])
{
    int f[n][n]; // The flow from the vertex i to j
    memset(f, 0, sizeof(int) * n * n);
    
    int ancestors[n]; // An array that contains the ancestors of vertices
    int queue[n]; //The queue of vertices
    int flow[n]; // Streams
    
    int maxFlow = 0; //Maximum Flow
    int augPathFlow; // The flow at an increasing way
    
    do
    {
        augPathFlow = findFlow(n, c, f, ancestors, queue, flow);
        maxFlow += augPathFlow;
    } while (augPathFlow > 0);
    
    return maxFlow;
}

int main(int argc, const char * argv[])
{
        int n;
    
        printf("Enter number of vertices: ");
        scanf("%d", &n);
        printf("Enter matrix\n");
    
        int c[n][n];
    
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                scanf("%d", &c[i][j]);
            }
        }
    
    printf("\nMaxFlow: %d\n", findMaxFlow(n, c));
    
    return 0;
}

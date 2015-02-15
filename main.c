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
    int qCurrent = 0; // Номер первого элемента в очереди
    int qNumber = 1; // Кол-во элементов в очереди
    que[0] = 0; // Первая вершина – источник
    
    anc[n-1] = -1; // У стока пока нет предков
    
    memset(flow, 0, sizeof(int) * n); // Обнуляем все потоки
    flow[0] = INT32_MAX; // У источника не ограничен
    
    int curV; // CurrentVertex
    
    // Пока не дойдем до конца или не закончатся вершины в очереди
    while (anc[n-1] == -1 && qCurrent < qNumber)
    {
        curV = *(que + qCurrent); // Извлекаем вершину из очереди
        for (int i = 0; i < n; ++i)
        {
            if ( ( c[curV][i] - f[curV][i] > 0 ) && ( flow[i] == 0 ) )
            {
                que[qNumber] = i; // Добавляем в очередь текущую вершину
                qNumber++; // Инкрементируем кол-во элементов
                
                anc[i] = curV; // Текущая вершина – предок найденной
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
        return 0; // Если у стока нет предков, то увеличивающий путь не найден
    }
    
    curV = n - 1;
    
    while (curV != 0)
    {
        // Идем от стока к истоку обратно, прибавляя потоки
        f[anc[curV]][curV] += flow[n-1];
        curV = anc[curV];
    }
    
    return *(flow + n - 1);
}

int findMaxFlow(int n, int c[n][n])
{
    int f[n][n]; // Поток из вершины i в j
    memset(f, 0, sizeof(int) * n * n);
    
    int ancestors[n]; // Массив, содержащий предков вершин
    int queue[n]; // Очередь вершин
    int flow[n]; // Потоки
    
    int maxFlow = 0; // Максимальный поток
    int augPathFlow; // Поток по увеличивающему пути
    
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

/* Eco OS */
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"
#include "IdEcoInterfaceBus1.h"
#include "IdEcoFileSystemManagement1.h"

#include "IdEcoLab1.h"
#include "IEcoCalculatorY.h"
#include "IEcoCalculatorX.h"

#include "IdEcoLab2.h"

#include <stdio.h>

int __cdecl comp_int(const void* left, const void* right) {
    const int l = *(int*)left;
    const int r = *(int*)right;
    if (l == r) {
        return 0;
    } else if (l < r) {
        return -1;
    }
    return 1;
}


void* generate_int_full_random(IEcoMemoryAllocator1 *pIMem, size_t size) {
    size_t i = 0;
    int* arr_ptr = 0;
    arr_ptr = (int*)pIMem->pVTbl->Alloc(pIMem, size * sizeof(int));
    // arr_ptr = (int*)malloc(size * sizeof(int));
    if (arr_ptr == 0) {
        printf("\n\nNo data was allocated\nTerminating\n\n");
        return NULL;
    }
    
    for (; i < size; ++i) {
        arr_ptr[i] = (rand() % 200010 - 5000);
    }

    return (void*)arr_ptr;
}

void print_int_arr(int* arr, size_t arr_size) {
    size_t i;

    if (arr_size > 1000) {
        return;
    }

    printf("Array of size %ld:\n", arr_size);
    for (i = 0; i < arr_size; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}


// Функция EcoMain - точка входа
int16_t EcoMain(IEcoUnknown* pIUnk) {
    int16_t result = -1;
    /* Указатель на системный интерфейс */
    IEcoSystem1* pISys = 0;
    /* Указатель на интерфейс работы с системной интерфейсной шиной */
    IEcoInterfaceBus1* pIBus = 0;
    /* Указатель на интерфейс работы с памятью */
    IEcoMemoryAllocator1* pIMem = 0;
    /* Указатель на тестируемый интерфейс */
    IEcoLab1* pIEcoLab1Rec = 0;
    IEcoCalculatorY* pIY = 0;
    IEcoCalculatorX* pIX = 0;

    IEcoLab1* pIEcoLab1 = 0;
    void *int_arr = NULL;
    size_t int_arr_size = 10;

    /* Проверка и создание системного интерфейса */
    result = pIUnk->pVTbl->QueryInterface(pIUnk, &GID_IEcoSystem1, (void **)&pISys);
    if (result != 0 && pISys == 0) {
        printf("Could not create system interface\n");
        goto Release;
    }

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);
    if (result != 0 || pIBus == 0) {
        printf("Could not get system bus interface\n");
        goto Release;
    }

    /* Получение интерфейса управления памятью */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoMemoryManager1, 0, &IID_IEcoMemoryAllocator1, (void**) &pIMem);
    if (result != 0 || pIMem == 0) {
        printf("Could not get memory interface\n");
        goto Release;
    }

    /* Получение тестируемого интерфейса */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab1, 0, &IID_IEcoLab1, (void**) &pIEcoLab1Rec);
    if (result != 0 || pIEcoLab1Rec == 0) {
        printf("Could not get EcoLab1 component\n");
        goto Release;
    }
    printf("Check IEcoLab1 component\n");

    /* запрос интерфейса IEcoCalculatorY через IEcoLab1 */
    result = pIEcoLab1Rec->pVTbl->QueryInterface(pIEcoLab1Rec, &IID_IEcoCalculatorY, (void **) &pIY);
    if (result != 0 || pIY == 0) {
        printf("Could not get IEcoCalculatorY interface\n");
        goto Release;
    }
    printf("Check IEcoCalculatorY interface\n");

    /* запрос интерфейса IEcoCalculatorX через IEcoLab1 */
    result = pIEcoLab1Rec->pVTbl->QueryInterface(pIEcoLab1Rec, &IID_IEcoCalculatorX, (void **) &pIX);
    if (result != 0 || pIX == 0) {
        printf("Could not get IEcoCalculatorX interface\n");
        goto Release;
    }
    printf("Check IEcoCalculatorX interface\n");

    printf("Addition 17 + 3 = %d\n", pIX->pVTbl->Addition(pIX, 17, 3));
    printf("Substraction -5 - 95 = %d\n", pIX->pVTbl->Subtraction(pIX, -5, 95));
    pIX->pVTbl->Release(pIX);

    printf("Multipling 11 * 8 = %d\n", pIY->pVTbl->Multiplication(pIY, 11, 8));
    printf("Division 256 / 16 = %d\n", pIY->pVTbl->Division(pIY, 256, 16));
    pIY->pVTbl->Release(pIY);

    printf("\nCheck component properties:\n");

    result = pIEcoLab1Rec->pVTbl->QueryInterface(pIEcoLab1Rec, &IID_IEcoCalculatorX, (void **) &pIX);
    if (result == 0) {
        printf("Got IX from ILab1\n");
        pIX->pVTbl->Release(pIX);
    }
    result = pIEcoLab1Rec->pVTbl->QueryInterface(pIEcoLab1Rec, &IID_IEcoCalculatorY, (void **) &pIY);
    if (result == 0) {
        printf("Got IY from ILab1\n");
        pIY->pVTbl->Release(pIY);
    }
    result = pIEcoLab1Rec->pVTbl->QueryInterface(pIEcoLab1Rec, &IID_IEcoLab1, (void **) &pIEcoLab1Rec);
    if (result == 0) {
        printf("Got ILab1 from ILab1\n");
        pIEcoLab1Rec->pVTbl->Release(pIEcoLab1Rec);
    }

    result = pIX->pVTbl->QueryInterface(pIX, &IID_IEcoCalculatorX, (void **) &pIX);
    if (result == 0) {
        printf("Got IX from IX\n");
        pIX->pVTbl->Release(pIX);
    }
    result = pIX->pVTbl->QueryInterface(pIX, &IID_IEcoCalculatorY, (void **) &pIY);
    if (result == 0) {
        printf("Got IY from IX\n");
        pIY->pVTbl->Release(pIY);
    }
    result = pIX->pVTbl->QueryInterface(pIX, &IID_IEcoLab1, (void **) &pIEcoLab1Rec);
    if (result == 0) {
        printf("Got ILab1 from IX\n");
        pIEcoLab1Rec->pVTbl->Release(pIEcoLab1Rec);
    }

    result = pIY->pVTbl->QueryInterface(pIY, &IID_IEcoCalculatorX, (void **) &pIX);
    if (result == 0) {
        printf("Got IX from IY\n");
        pIX->pVTbl->Release(pIX);
    }
    result = pIY->pVTbl->QueryInterface(pIY, &IID_IEcoCalculatorY, (void **) &pIY);
    if (result == 0) {
        printf("Got IY from IY\n");
        pIY->pVTbl->Release(pIY);
    }
    result = pIY->pVTbl->QueryInterface(pIY, &IID_IEcoLab1, (void **) &pIEcoLab1Rec);
    if (result == 0) {
        printf("Got ILab1 from IY\n");
        pIEcoLab1Rec->pVTbl->Release(pIEcoLab1Rec);
    }

    printf("\nCheck aggregated sorting interface:\n");
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab2, 0, &IID_IEcoLab1, (void**) &pIEcoLab1);
    if (result == 0) {
        printf("Got IEcoLab1 interface aggregated from CEcoLab2\n");
    }

    int_arr = generate_int_full_random(pIMem, int_arr_size);
    print_int_arr(int_arr, int_arr_size);
    printf("Sotring\n");
    pIEcoLab1->pVTbl->qsort(pIEcoLab1, int_arr, int_arr_size, sizeof(int), comp_int);
    printf("Sorting done\n");
    print_int_arr(int_arr, int_arr_size);

    pIMem->pVTbl->Free(pIMem, int_arr);


Release:

    printf("\nStart release procedure");

    /* Освобождение интерфейса для работы с интерфейсной шиной */
    if (pIBus != 0) {
        pIBus->pVTbl->Release(pIBus);
    }

    /* Освобождение интерфейса работы с памятью */
    if (pIMem != 0) {
        pIMem->pVTbl->Release(pIMem);
    }

    /* Освобождение тестируемого интерфейса */
    if (pIEcoLab1Rec != 0) {
        pIEcoLab1Rec->pVTbl->Release(pIEcoLab1Rec);
    }

    if (pIEcoLab1 != 0) {
        pIEcoLab1->pVTbl->Release(pIEcoLab1);
    }
    /* Освобождение системного интерфейса */
    if (pISys != 0) {
        pISys->pVTbl->Release(pISys);
    }

    return result;
}

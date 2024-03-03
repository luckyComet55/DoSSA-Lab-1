/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   EcoLab1
 * </сводка>
 *
 * <описание>
 *   Данный исходный файл является точкой входа
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */


/* Eco OS */
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"
#include "IdEcoInterfaceBus1.h"
#include "IdEcoFileSystemManagement1.h"
#include "IdEcoLab1.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    size_t arr_size;
    bool_t arr_type;
    double qsort_internal_res;
    double qsort_custom_res;
} test_result;

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

void copy_int_arr(int* src, int* dst, size_t size) {
    size_t i;
    for (i = 0; i < size; ++i) {
        dst[i] = src[i];
    }
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

bool_t assert_int_arrs_equal(int* l, int* r, size_t size) {
    size_t i;
    for (i = 0; i < size; ++i) {
        if (l[i] != r[i]) {
            printf("\nASSERTION FAILED:\n%d != %d\nARRAY INDEX %ld\nPRINTING OUT ARRAYS:\n", l[i], r[i], i);
            print_int_arr(l, size);
            print_int_arr(r, size);
            return FALSE;
        }
    }
    return TRUE;
}

void* generate_int_full_random(IEcoMemoryAllocator1 *pIMem, size_t size) {
    size_t i = 0;
    int* arr_ptr = 0;
    arr_ptr = (int*)pIMem->pVTbl->Alloc(pIMem, size * sizeof(int));
    // arr_ptr = (int*)malloc(size * sizeof(int));
    if (arr_ptr == 0) {
        printf("\n\nNo data was allocated\nTerminating\n\n");
        return -13;
    }
    
    for (; i < size; ++i) {
        arr_ptr[i] = (rand() % 200010 - 5000);
    }

    return (void*)arr_ptr;
}

void* generate_int_sequential(IEcoMemoryAllocator1 *pIMem, size_t size) {
    size_t i;
    int to_be_sequence, up_down;
    int sequence_len;
    int base;
    int* arr_ptr = 0;
    arr_ptr = (int*)pIMem->pVTbl->Alloc(pIMem, size * sizeof(int));
    // arr_ptr = malloc(size * sizeof(int));
    if (arr_ptr == 0) {
        printf("\n\nNo data was allocated\nTerminating\n\n");
        return -13;
    }
    
    for (i = 0; i < size; ++i) {
        to_be_sequence = rand() % 10;
        if (to_be_sequence == 0) {
            sequence_len = rand() % (size * 2 / 10) + 5;
            base = (rand() % 200010) - 5000;
            up_down = rand() % 2;
            for (; i < sequence_len && i < size; ++i) {
                arr_ptr[i] = base;
                if (up_down == 0) {
                    base += (rand() % 150);
                } else {
                    base -= (rand() % 150);
                }
            }
        } else {
            arr_ptr[i] = ((rand() % 200010) - 5000);
        }
    }

    return (void*)arr_ptr;
}

void* generate_int_arr(IEcoMemoryAllocator1 *pIMem, size_t size, bool_t full_random) {
    if (full_random) {
        return generate_int_full_random(pIMem, size);
    }
    return generate_int_sequential(pIMem, size);
}

test_result run_int_tests(IEcoLab1 *this, IEcoMemoryAllocator1 *pIMem, size_t size, bool_t is_full_random) {
    test_result res = {0, 0, 0, 0};
    clock_t before, after;
    double res_sec_custom, res_sec_internal;
    int16_t err_code = 0;
    void* data_custom = 0;
    void* data_internal = 0;

    printf("generating arr of size %ld (%ld bytes)\n\n", size, size * sizeof(int));
    data_custom = generate_int_arr(pIMem, size, is_full_random);
    data_internal = pIMem->pVTbl->Alloc(pIMem, size * sizeof(int));
    if (data_custom == 0 || data_internal == 0) {
        printf("\n\nNo data was allocated\nTerminating\n\n");
        exit(-13);
    }
    copy_int_arr(data_custom, data_internal, size);
    
    printf("sorting lab qsort\n\n");
    before = clock();
    err_code = this->pVTbl->qsort(this, data_custom, size, sizeof(int), comp_int);
    after = clock();

    if (err_code != 0) {
        printf("\n\nRuntime error occured: %d\n\n", err_code);
        exit(err_code);
    }

    res_sec_custom = (double)(after - before) / CLOCKS_PER_SEC;
    printf("\n\nBefore: %ld\nAfter: %ld\n\n", before, after);

    printf("sorting std qsort\n\n");
    before = clock();
    qsort(data_internal, size, sizeof(int), comp_int);
    after = clock();
    res_sec_internal = (double)(after - before) / CLOCKS_PER_SEC;

    printf("\nAssert both sorting returned same result\n");
    assert(assert_int_arrs_equal(data_custom, data_internal, size));

    printf("wiping arrays data (%d bytes)\n\n", size * sizeof(int));
    pIMem->pVTbl->Free(pIMem, data_internal);
    pIMem->pVTbl->Free(pIMem, data_custom);

    res.arr_size = size;
    res.arr_type = is_full_random;
    res.qsort_custom_res = res_sec_custom;
    res.qsort_internal_res = res_sec_internal;

    return res;
}

void print_result_terminal(test_result res) {
    if (res.arr_type == TRUE) {
        printf("%d,%lf,%lf,RAND\n", res.arr_size, res.qsort_internal_res, res.qsort_custom_res);
    } else {
        printf("%d,%lf,%lf,SEQ\n", res.arr_size, res.qsort_internal_res, res.qsort_custom_res);
    }
}

void print_result(FILE *out_file, test_result res) {
    if (res.arr_type == TRUE) {
        fprintf(out_file, "%d,%lf,%lf,RAND\n", res.arr_size, res.qsort_internal_res, res.qsort_custom_res);
    } else {
        fprintf(out_file, "%d,%lf,%lf,SEQ\n", res.arr_size, res.qsort_internal_res, res.qsort_custom_res);
    }
}

void print_res_to_file(FILE *out_file, test_result *res, size_t res_size) {
    size_t i;
    fprintf(out_file, "size,standard qsort,lab qsort,array type\n");
    for (i = 0; i < res_size; ++i) {
        print_result(out_file, res[i]);
    }
}

void print_res_to_terminal(test_result *res, size_t res_size) {
    size_t i;
    printf("size,standard qsort,lab qsort,array type\n");
    for (i = 0; i < res_size; ++i) {
        print_result_terminal(res[i]);
    }
}

int16_t test_toplevel(IEcoLab1 *this, IEcoMemoryAllocator1 *pIMem, FILE *out_file) {
    size_t sizes[6] = {64, 15002, 61234, 120000, 1012322, 32700121};
    test_result results[9];
    size_t i;

    printf("start test\n\n");
    
    for (i = 0; i < 6; ++i) {
        printf("test #%d\n", i + 1);
        results[i] = run_int_tests(this, pIMem, sizes[i], TRUE);
    }
    for (i = 3; i < 6; ++i) {
        printf("test #%d\n", i + 4);
        results[i + 3] = run_int_tests(this, pIMem, sizes[i], FALSE);
    }

    printf("\nend tests\nprint result data\n\n");

    print_res_to_terminal(results, 9);

    printf("end print data\n\n");

    return 0;
}

/*
 *
 * <сводка>
 *   Функция EcoMain
 * </сводка>
 *
 * <описание>
 *   Функция EcoMain - точка входа
 * </описание>
 *
 */
int16_t EcoMain(IEcoUnknown* pIUnk) {
    int16_t result = -1;
    /* Указатель на системный интерфейс */
    IEcoSystem1* pISys = 0;
    /* Указатель на интерфейс работы с системной интерфейсной шиной */
    IEcoInterfaceBus1* pIBus = 0;
    /* Указатель на интерфейс работы с памятью */
    IEcoMemoryAllocator1* pIMem = 0;
    char_t* copyName = 0;
    FILE* out_file;
    errno_t err_code = 0;
    /* Указатель на тестируемый интерфейс */
    IEcoLab1* pIEcoLab1 = 0;

    /* Проверка и создание системного интрефейса */
    if (pISys == 0) {
        result = pIUnk->pVTbl->QueryInterface(pIUnk, &GID_IEcoSystem1, (void **)&pISys);
        if (result != 0 && pISys == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
            goto Release;
        }
    }

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);
    if (result != 0 || pIBus == 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
#ifdef ECO_LIB
    /* Регистрация статического компонента для работы со списком */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoLab1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_1F5DF16EE1BF43B999A434ED38FE8F3A);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
#endif
    /* Получение интерфейса управления памятью */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoMemoryManager1, 0, &IID_IEcoMemoryAllocator1, (void**) &pIMem);

    /* Проверка */
    if (result != 0 || pIMem == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
        goto Release;
    }


    /* Получение тестируемого интерфейса */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab1, 0, &IID_IEcoLab1, (void**) &pIEcoLab1);
    if (result != 0 || pIEcoLab1 == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }

    // утановка ГПСЧ
    srand(time(0));

    //err_code = fopen_s(&out_file, "./out/out.csv", "w");
    out_file = fdopen(1, "w");
    if (out_file == NULL) {
        printf("\n\nCould not open stdout file\nTerminating\n\n");
        goto Release;
    }
    if (err_code != 0) {
        printf("\n\nCould not open out file\nTerminating\n\n");
        goto Release;
    }

    err_code = test_toplevel(pIEcoLab1, pIMem, out_file);
    if (err_code != 0) {
        fclose(out_file);
        goto Release;
    }
    fclose(out_file);
    result = 0;

Release:

    /* Освобождение интерфейса для работы с интерфейсной шиной */
    if (pIBus != 0) {
        pIBus->pVTbl->Release(pIBus);
    }

    /* Освобождение интерфейса работы с памятью */
    if (pIMem != 0) {
        pIMem->pVTbl->Release(pIMem);
    }

    /* Освобождение тестируемого интерфейса */
    if (pIEcoLab1 != 0) {
        pIEcoLab1->pVTbl->Release(pIEcoLab1);
    }


    /* Освобождение системного интерфейса */
    if (pISys != 0) {
        pISys->pVTbl->Release(pISys);
    }

    return result;
}


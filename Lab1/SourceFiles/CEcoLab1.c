/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoLab1
 * </сводка>
 *
 * <описание>
 *   Данный исходный код описывает реализацию интерфейсов CEcoLab1
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#include "IEcoSystem1.h"
#include "IEcoInterfaceBus1.h"
#include "IEcoInterfaceBus1MemExt.h"
#include "CEcoLab1.h"
#include "IdEcoCalculatorD.h"
#include "IdEcoCalculatorE.h"
#include "IdEcoCalculatorB.h"
#include "IdEcoCalculatorA.h"
#include "CEcoLab2.h"
#include <stdlib.h>


/*
    Свапает заданное число байт
*/
void swap_bytes(
    char* elem1,
    char* elem2,
    size_t type_size
) {
    size_t i = 0;
    char tmp;
    for (; i < type_size; ++i) {
        tmp = elem1[i];
        elem1[i] = elem2[i];
        elem2[i] = tmp;
    }
}

/*
    Копирует заданное число байт
*/
void copy_bytes(
    char* src,
    char* dst,
    size_t type_size
) {
    size_t i = 0;
    for (; i < type_size; ++i) {
        dst[i] = src[i];
    }
}

typedef struct {
    size_t size;
    bool_t direction_flag;
} sorted_sub_array_return_pair_t;


/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция QueryInterface для интерфейса IEcoLab1
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoLab1_QueryInterface(/* in */ struct IEcoLab1* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoLab1* pCMe = (CEcoLab1*)me;
    IEcoUnknown* nonDelegating = (IEcoUnknown*)&pCMe->m_pVTblINondelegatingUnk;
    int16_t result = 0;

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return -1;
    }

    result = nonDelegating->pVTbl->QueryInterface(nonDelegating, riid, ppv);
    if (result != 0 && pCMe->m_pIUnkOuter != 0) {
        result = pCMe->m_pIUnkOuter->pVTbl->QueryInterface(pCMe->m_pIUnkOuter, riid, ppv);
    }

    return result;
}

/*
 *
 * <сводка>
 *   Функция AddRef
 * </сводка>
 *
 * <описание>
 *   Функция AddRef для интерфейса IEcoLab1
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoLab1_AddRef(/* in */ struct IEcoLab1* me) {
    CEcoLab1* pCMe = (CEcoLab1*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    return pCMe->m_pVTblINondelegatingUnk->AddRef((IEcoUnknown*)&pCMe->m_pVTblINondelegatingUnk);
}

/*
 *
 * <сводка>
 *   Функция Release
 * </сводка>
 *
 * <описание>
 *   Функция Release для интерфейса IEcoLab1
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoLab1_Release(/* in */ struct IEcoLab1* me) {
    CEcoLab1* pCMe = (CEcoLab1*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    return pCMe->m_pVTblINondelegatingUnk->AddRef((IEcoUnknown*)&pCMe->m_pVTblINondelegatingUnk);
}

int16_t ECOCALLMETHOD CEcoLab1_IEcoCalculatorY_QueryInterface(/* in */ struct IEcoCalculatorY* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoLab1* pCMe = (CEcoLab1 *)((uint64_t)me - sizeof(struct IEcoLab1*));
    IEcoUnknown * nonDelegating = (IEcoUnknown *)&pCMe->m_pVTblINondelegatingUnk;
    int16_t result;

    if (me == 0 || ppv == 0) {
        return -1;
    }

    result = nonDelegating->pVTbl->QueryInterface(nonDelegating, riid, ppv);
    if (result != 0 && pCMe->m_pIUnkOuter != 0) {
        result = pCMe->m_pIUnkOuter->pVTbl->QueryInterface(pCMe->m_pIUnkOuter, riid, ppv);
    }
    return result;
}

uint32_t ECOCALLMETHOD CEcoLab1_IEcoCalculatorY_AddRef(/* in */ struct IEcoCalculatorY* me) {
    CEcoLab1* pCMe = (CEcoLab1*)((uint64_t)me - sizeof(struct IEcoLab1*));

    if (me == 0 ) {
        return -1;
    }

    return pCMe->m_pVTblINondelegatingUnk->AddRef((IEcoUnknown *)&pCMe->m_pVTblINondelegatingUnk);
}

uint32_t ECOCALLMETHOD CEcoLab1_IEcoCalculatorY_Release(/* in */ struct IEcoCalculatorY* me) {
    CEcoLab1* pCMe = (CEcoLab1*)((uint64_t)me - sizeof(struct IEcoLab1*));

    if (me == 0 ) {
        return -1;
    }

    return pCMe->m_pVTblINondelegatingUnk->Release((IEcoUnknown *)&pCMe->m_pVTblINondelegatingUnk);
}

int32_t ECOCALLMETHOD CEcoLab1_Multiplication(/* in */ struct IEcoCalculatorY* me, /* in */ int16_t a, /* in */ int16_t b) {
    CEcoLab1* pCMe = (CEcoLab1*)((uint64_t)me - sizeof(struct IEcoLab1*));
    int32_t result = 0;

    printf("\n=========Inside CEcoLab1_Multiplication=========\n");

    if (me == 0 ) {
        return -1;
    }

    if (pCMe->m_pIY != 0) {
        result = pCMe->m_pIY->pVTbl->Multiplication(pCMe->m_pIY, a, b);
    }

    return result;
}

int16_t ECOCALLMETHOD CEcoLab1_Division(/* in */ struct IEcoCalculatorY* me, /* in */ int16_t a, /* in */ int16_t b) {
    CEcoLab1* pCMe = (CEcoLab1*)((uint64_t)me - sizeof(struct IEcoLab1*));
    int16_t result = 0;

    printf("\n=========Inside CEcoLab1_Division=========\n");

    if (me == 0 ) {
        return -1;
    }

    if (pCMe->m_pIY != 0) {
        result = pCMe->m_pIY->pVTbl->Division(pCMe->m_pIY, a, b);
    }

    return result;
}


int16_t ECOCALLMETHOD CEcoLab1_IEcoCalculatorX_QueryInterface(/* in */ struct IEcoCalculatorX* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoLab1* pCMe = (CEcoLab1 *)((uint64_t)me - sizeof(struct IEcoLab1*) - sizeof(struct IEcoCalculatorY*));
    IEcoUnknown * nonDelegating = (IEcoUnknown *)&pCMe->m_pVTblINondelegatingUnk;
    int16_t result;

    if (me == 0 || ppv == 0) {
        return -1;
    }

    result = nonDelegating->pVTbl->QueryInterface(nonDelegating, riid, ppv);
    if (result != 0 && pCMe->m_pIUnkOuter != 0) {
        result = pCMe->m_pIUnkOuter->pVTbl->QueryInterface(pCMe->m_pIUnkOuter, riid, ppv);
    }
    return result;
}

uint32_t ECOCALLMETHOD CEcoLab1_IEcoCalculatorX_AddRef(/* in */ struct IEcoCalculatorX* me) {
    CEcoLab1* pCMe = (CEcoLab1 *)((uint64_t)me - sizeof(struct IEcoLab1*) - sizeof(struct IEcoCalculatorY*));

    if (me == 0 ) {
        return -1;
    }

    return pCMe->m_pVTblINondelegatingUnk->AddRef((IEcoUnknown *)&pCMe->m_pVTblINondelegatingUnk);
}

uint32_t ECOCALLMETHOD CEcoLab1_IEcoCalculatorX_Release(/* in */ struct IEcoCalculatorX* me) {
    CEcoLab1* pCMe = (CEcoLab1 *)((uint64_t)me - sizeof(struct IEcoLab1*) - sizeof(struct IEcoCalculatorY*));

    if (me == 0 ) {
        return -1;
    }

    return pCMe->m_pVTblINondelegatingUnk->Release((IEcoUnknown *)&pCMe->m_pVTblINondelegatingUnk);
}

int32_t ECOCALLMETHOD CEcoLab1_Addition(/* in */ struct IEcoCalculatorX* me, /* in */ int16_t a, /* in */ int16_t b) {
    CEcoLab1* pCMe = (CEcoLab1 *)((uint64_t)me - sizeof(struct IEcoLab1*) - sizeof(struct IEcoCalculatorY*));
    int32_t result = 0;

    printf("\n=========Inside CEcoLab1_Addition=========\n");

    if (me == 0 ) {
        return -1;
    }

    if (pCMe->m_pIX != 0) {
        result = pCMe->m_pIX->pVTbl->Addition(pCMe->m_pIX, a, b);
    }

    return result;
}

int16_t ECOCALLMETHOD CEcoLab1_Subtraction(/* in */ struct IEcoCalculatorX* me, /* in */ int16_t a, /* in */ int16_t b) {
    CEcoLab1* pCMe = (CEcoLab1 *)((uint64_t)me - sizeof(struct IEcoLab1*) - sizeof(struct IEcoCalculatorY*));
    int16_t result = 0;

    printf("\n=========Inside CEcoLab1_Substraction=========\n");

    if (me == 0 ) {
        return -1;
    }

    if (pCMe->m_pIX != 0) {
        result = pCMe->m_pIX->pVTbl->Subtraction(pCMe->m_pIX, a, b);
    }

    return result;
}


int16_t ECOCALLMETHOD CEcoLab1_NondelegatingQueryInterface(/* in */ struct IEcoUnknown * me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoLab1* pCMe = (CEcoLab1*)((uint64_t)me - sizeof(struct IEcoLab1*) - sizeof(struct IEcoCalculatorY*) - sizeof(struct IEcoCalculatorX*));
    int16_t result;
    if (me == 0 || ppv == 0) {
        return -1;
    }
    if ( IsEqualUGUID(riid, &IID_IEcoLab1) ) {
        *ppv = &pCMe->m_pVTblIEcoLab1;
        ++pCMe->m_cRef;
    }
    else if (IsEqualGUID(riid, &IID_IEcoCalculatorY)) {
        *ppv = &pCMe->m_pVTblIY;
        ++pCMe->m_cRef;
    }
    else if (IsEqualGUID(riid, &IID_IEcoCalculatorX)) {
        if (pCMe->m_pInnerUnknown != 0) {
            result = pCMe->m_pInnerUnknown->pVTbl->QueryInterface(pCMe->m_pInnerUnknown, riid, ppv);
            return result;
        }
        else {
            *ppv = &pCMe->m_pVTblIX;
            ++pCMe->m_cRef;
        }
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblINondelegatingUnk;
        ++pCMe->m_cRef;
    }
    else {
        *ppv = 0;
        return -1;
    }
    return 0;
}

uint32_t ECOCALLMETHOD CEcoLab1_NondelegatingAddRef(/* in */ struct IEcoUnknown* me) {
    CEcoLab1* pCMe = (CEcoLab1*)((uint64_t)me - sizeof(struct IEcoLab1*) - sizeof(struct IEcoCalculatorY*) - sizeof(struct IEcoCalculatorX*));

    if (me == 0 ) {
        return -1;
    }

    return ++pCMe->m_cRef;
}

uint32_t ECOCALLMETHOD CEcoLab1_NondelegatingRelease(/* in */ struct IEcoUnknown* me) {
    CEcoLab1* pCMe = (CEcoLab1*)((uint64_t)me - sizeof(struct IEcoLab1*) - sizeof(struct IEcoCalculatorY*) - sizeof(struct IEcoCalculatorX*));

    if (me == 0 ) {
        return -1;
    }

    --pCMe->m_cRef;

    if ( pCMe->m_cRef == 0 ) {
        if (pCMe->m_pInnerUnknown != 0) {
            if (pCMe->m_pInnerUnknown->pVTbl->Release(pCMe->m_pInnerUnknown) == 0) {
                pCMe->m_pInnerUnknown = 0;
            } else {
                pCMe->m_cRef = 1;
            }
        }
        if (pCMe->m_cRef == 0) {
            deleteCEcoLab1((IEcoLab1*)pCMe);
        }
        return 0;
    }
    return pCMe->m_cRef;
}

/*
    Вычисляет служебное значение min_run
*/
int16_t get_min_run(size_t n) {
    int16_t r = 0;
    while (n >= 64) {
        r |= n & 1;
        n >>= 1;
    }
    return n + r;
}

/*
    Разворачивает отсортированный
    подмассив (применяется в том случае,
    если найденный подмассив отсортирован
     в порядке невозрастания)
*/
void reverse_sorted_array(
    void* data,
    size_t elem_count,
    size_t elem_size
) {
    size_t i = 0;
    size_t j = elem_count - 1;

    if (elem_count < 2) {
        return;
    }

    for (; i < elem_count / 2; ++i, --j) {
        swap_bytes(
            (char*) data + i * elem_size,
            (char*) data + j * elem_size,
            elem_size
        );
    }
}

/*
    Возвращает размер найденного
    отсортированного подмассива,
    указатель data становится на его начало.
*/
sorted_sub_array_return_pair_t get_sorted_sub_array(
    void* data,
    size_t elem_count,
    size_t start_ptr,
    size_t elem_size,
    int (__cdecl *comp)(const void*, const void*)
) {
    size_t i = start_ptr / elem_size;
    int cmp_prev = 0;
    int cmp_cur;
    size_t sub_sorted_size = 1;
    sorted_sub_array_return_pair_t res = {sub_sorted_size, TRUE};

    do {
        cmp_cur = comp((char*)data + i * elem_size, (char*)data + (i + 1) * elem_size);
        cmp_prev = cmp_cur;
        i++;
        sub_sorted_size++;
    } while (cmp_prev == 0 && elem_count > i + 1);
    
    for (; i < elem_count - 1; ++i) {
        cmp_cur = comp((char*)data + i * elem_size, (char*)data + (i + 1) * elem_size);
        if (cmp_cur == 0 || cmp_cur == cmp_prev) {
            sub_sorted_size++;
        } else {
            break;
        }
    }
    res.size = sub_sorted_size;
    res.direction_flag = cmp_prev != 1;
    return res;
}

/*
    Проводит сортировку вставками.
    Используется для подмассивов размером
    min_run или больше. Зачем используется?
    Алгоритм предполагает, что поступающие
    на вход подмассивы либо очень малы
    (min_run выбирается из диапазона [32, 65)),
    либо частично отсортированны. В общем случае,
    подмассивы размера min_run буду частично отсортированны,
    подмассивы больших размеров будут отсортированны полностью.
*/
void insertion_sort(
    void* data,
    size_t elem_count,
    size_t elem_size,
    int (__cdecl *comp)(const void *, const void*)
) {
    size_t i = 0;
    size_t prev;
    size_t j;
    
    for (; i < elem_count - 1; ++i) {
        j = i + 1;
        prev = i;
        while (
            comp((char*)data + prev * elem_size, (char*)data + j * elem_size) > 0
            &&
            /* Это условие никогда не будет невыполнено, поскольку тип данных такой,
                но я решил добавить его для явности, проверка всё равно осуществляется
                в блоке 
            */ prev >= 0
        ) {
            swap_bytes(
                (char*)data + prev * elem_size,
                (char*)data + j * elem_size,
                elem_size
            );
            j--;
            if (prev == 0) {
                break;
            }
            prev--;
        }
    }
}

/*
    Сортировка слиянием двух
    отсортированных подмассивов.
    Необходимо небольшое объяснение
    касательно передаваемых аргументов:
    в принципе, нужды передавать
    указатель data нет - это,
    по сути, и есть left_sub_arr.
    Однако, семантически left_sub_arr
    является только левым подмассивом и ограничен
    размером left_size. В ходе функции
    есть необходимость последовательно копировать
    элементы из массивов buffer (копия left_sub_arr) и
    right_sub_arr в общий массив данных. Это можно
    сделать с использованием одного указателя
    left_sub_arr, однако при этом указатель выйдет
    за те рамки, которые были заданы переменной left_size.
    А это просто выглядит плохо, будто мы
    выходми в память, которая нам не
    принадлежит. По этой причине, просто
    ради читаемости, решено было дополнительно
    передавать указатель data. Конечно,
    тогда копирование из left_sub_arr в buffer
    выглядит лишним, но, по-моему, это гораздо лучше,
    чем что-то похожее на предрекающее SEGFAULT.
*/
void merge_sorted_subarrays(
    void* data,
    void* left_sub_arr,
    size_t left_size,
    void* right_sub_arr,
    size_t right_size,
    size_t elem_size,
    int (__cdecl *comp)(const void *, const void*),
    void* buffer
) {
    size_t left_ptr, right_ptr, buffer_ptr, data_ptr;
    size_t buffer_size = left_size + right_size;
    char* tmp_src_ptr;

    for (left_ptr = 0, right_ptr = 0, buffer_ptr = 0; left_ptr < left_size && right_ptr < right_size; ++buffer_ptr) {
        if (comp(
            (char*)left_sub_arr + left_ptr * elem_size, (char*)right_sub_arr + right_ptr * elem_size) <= 0
        ) {
            copy_bytes(
                (char*)left_sub_arr + left_ptr * elem_size,
                (char*)buffer + buffer_ptr * elem_size,
                elem_size
            );
            left_ptr++;
        } else {
            copy_bytes(
                (char*)right_sub_arr + right_ptr * elem_size,
                (char*)buffer + buffer_ptr * elem_size,
                elem_size
            );
            right_ptr++;
        }
    }

    for(; left_ptr < left_size; ++left_ptr, ++buffer_ptr) {
        copy_bytes(
            (char*)left_sub_arr + left_ptr * elem_size,
            (char*)buffer + buffer_ptr * elem_size,
            elem_size
        );
    }

    for (; right_ptr < right_size; ++right_ptr, ++buffer_ptr) {
        copy_bytes(
            (char*)right_sub_arr + right_ptr * elem_size,
            (char*)buffer + buffer_ptr * elem_size,
            elem_size
        );
    }

    for (buffer_ptr = 0, data_ptr = 0; buffer_ptr < buffer_size; ++buffer_ptr, ++data_ptr) {
        copy_bytes(
            (char*)buffer + buffer_ptr * elem_size,
            (char*)data + data_ptr * elem_size,
            elem_size
        );
    }
}

int16_t timsort_actual(
    void* data,
    size_t elem_count,
    size_t elem_size,
    int (__cdecl *comp)(const void *, const void*),
    void* buffer_copy
) {
    int16_t min_run = get_min_run(elem_count);
    size_t sub_sorted_arr_size = 0;
    size_t data_ptr = 0, data_bytes = elem_count * elem_size, stack_idx = 0;
    size_t sub_arr_size = min_run, last_arr_size = elem_count % min_run == 0 ? min_run : elem_count % min_run;
    size_t arr_idx = 0;
    size_t arrs_left = elem_count / min_run + (elem_count % min_run != 0);

    if (elem_count < 2) {
        return 0;
    }

    if (elem_count <= 64) {
        insertion_sort(
            data,
            elem_count,
            elem_size,
            comp
        );
        return 0;
    }

    while (data_ptr < data_bytes) {
        if (min_run * elem_size + data_ptr < data_bytes) {
            sub_sorted_arr_size = min_run;
        } else {
            sub_sorted_arr_size = (data_bytes - data_ptr) / elem_size;
        }

        insertion_sort(
            (char*)data + data_ptr,
            sub_sorted_arr_size,
            elem_size,
            comp
        );

        data_ptr += (sub_sorted_arr_size * elem_size);
    }

    while (arrs_left > 1) {
        for (arr_idx = 0; arr_idx < arrs_left - 2; arr_idx += 2) {
            merge_sorted_subarrays(
                (char*)data + arr_idx * sub_arr_size * elem_size,
                (char*)data + arr_idx * sub_arr_size * elem_size,
                sub_arr_size,
                (char*)data + (arr_idx + 1) * sub_arr_size * elem_size,
                sub_arr_size,
                elem_size,
                comp,
                buffer_copy
            );
        }

        if (arrs_left % 2 == 0) {
            merge_sorted_subarrays(
                (char*)data + (elem_count - last_arr_size - sub_arr_size) * elem_size,
                (char*)data + (elem_count - last_arr_size - sub_arr_size) * elem_size,
                sub_arr_size,
                (char*)data + (elem_count - last_arr_size) * elem_size,
                last_arr_size,
                elem_size,
                comp,
                buffer_copy
            );
            last_arr_size += sub_arr_size;
        }
        arrs_left = arrs_left / 2 + (arrs_left % 2 != 0);
        sub_arr_size *= 2;
    }
    
    return 0;
}

int16_t ECOCALLMETHOD CEcoLab1_qsort(
    struct IEcoLab1* me,
    void* pData,
    size_t elem_count,
    size_t elem_size,
    int (__cdecl *comp)(const void *, const void*)
) {
    CEcoLab1* pCMe = (CEcoLab1*) me;
    void* buffer_copy = 0;
    int16_t err_code = 0;

    if (me == 0 || pData == 0 || comp == 0) {
        return -1;
    }

    buffer_copy = pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, elem_count * elem_size);
    if (buffer_copy == 0) {
        printf("\n\nNo data was allocated\nTerminating\n\n");
        return -13;
    }

    err_code = timsort_actual(
        pData,
        elem_count,
        elem_size,
        comp,
        buffer_copy
    );

    pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, buffer_copy);

    return err_code;
}




/*
 *
 * <сводка>
 *   Функция Init
 * </сводка>
 *
 * <описание>
 *   Функция инициализации экземпляра
 * </описание>
 *
 */
int16_t ECOCALLMETHOD initCEcoLab1(/*in*/ struct IEcoLab1* me, /* in */ struct IEcoUnknown *pIUnkSystem) {
    CEcoLab1* pCMe = (CEcoLab1*)me;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoUnknown* pOuterUnknown = (IEcoUnknown*) me;
    int16_t result = -1;

    /* Проверка указателей */
    if (me == 0 ) {
        return result;
    }

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = (IEcoSystem1*)pIUnkSystem;

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pCMe->m_pISys->pVTbl->QueryInterface(pCMe->m_pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);

    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorD, 0, &IID_IEcoCalculatorY, (void**) &pCMe->m_pIY);
    if (result != 0 || pCMe->m_pIY == 0) {
        result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorE, 0, &IID_IEcoCalculatorY, (void**) &pCMe->m_pIY);
    }

    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorB, pOuterUnknown, &IID_IEcoUnknown, (void**) &pCMe->m_pInnerUnknown);
    if (result != 0 || pCMe->m_pInnerUnknown == 0) {
        result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorA, 0, &IID_IEcoCalculatorX, (void**) &pCMe->m_pIX);
    }

    /* Проверка указателей */
    if (me == 0 ) {
        return result;
    }

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = (IEcoSystem1*)pIUnkSystem;



    /* Освобождение */
    pIBus->pVTbl->Release(pIBus);
	
    return result;
}

/* Create Virtual Table IEcoLab1 */
IEcoLab1VTbl g_x277FC00C35624096AFCFC125B94EEC90VTbl = {
    CEcoLab1_QueryInterface,
    CEcoLab1_AddRef,
    CEcoLab1_Release,
    CEcoLab1_qsort
};

IEcoCalculatorYVTbl g_xBD6414C29096423EA90C04D77AFD1CADVTblLab1 = {
    CEcoLab1_IEcoCalculatorY_QueryInterface,
    CEcoLab1_IEcoCalculatorY_AddRef,
    CEcoLab1_IEcoCalculatorY_Release,
    CEcoLab1_Multiplication,
    CEcoLab1_Division
};

IEcoCalculatorXVTbl g_x9322111622484742AE0682819447843DVTblLab1 = {
        CEcoLab1_IEcoCalculatorX_QueryInterface,
        CEcoLab1_IEcoCalculatorX_AddRef,
        CEcoLab1_IEcoCalculatorX_Release,
        CEcoLab1_Addition,
        CEcoLab1_Subtraction
};

IEcoUnknownVTbl g_x000000000000000000000000000000AAVTblLab1 = {
        CEcoLab1_NondelegatingQueryInterface,
        CEcoLab1_NondelegatingAddRef,
        CEcoLab1_NondelegatingRelease
};


/*
 *
 * <сводка>
 *   Функция Create
 * </сводка>
 *
 * <описание>
 *   Функция создания экземпляра
 * </описание>
 *
 */
int16_t ECOCALLMETHOD createCEcoLab1(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoUnknown* pIUnkOuter, /* out */ IEcoLab1** ppIEcoLab1) {
    int16_t result = -1;
    IEcoSystem1* pISys = 0;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoInterfaceBus1MemExt* pIMemExt = 0;
    IEcoMemoryAllocator1* pIMem = 0;
    CEcoLab1* pCMe = 0;
    UGUID* rcid = (UGUID*)&CID_EcoMemoryManager1;
	
    /* Проверка указателей */
    if (ppIEcoLab1 == 0 || pIUnkSystem == 0) {
        return result;
    }

    /* Получение системного интерфейса приложения */
    result = pIUnkSystem->pVTbl->QueryInterface(pIUnkSystem, &GID_IEcoSystem1, (void **)&pISys);

    /* Проверка */
    if (result != 0 && pISys == 0) {
        return result;
    }

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);

	/* Получение идентификатора компонента для работы с памятью */
    result = pIBus->pVTbl->QueryInterface(pIBus, &IID_IEcoInterfaceBus1MemExt, (void**)&pIMemExt);
    if (result == 0 && pIMemExt != 0) {
        rcid = (UGUID*)pIMemExt->pVTbl->get_Manager(pIMemExt);
        pIMemExt->pVTbl->Release(pIMemExt);
    }

    /* Получение интерфейса распределителя памяти */
    pIBus->pVTbl->QueryComponent(pIBus, rcid, 0, &IID_IEcoMemoryAllocator1, (void**) &pIMem);

    /* Проверка */
    if (result != 0 && pIMem == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
        pISys->pVTbl->Release(pISys);
        return result;
    }

    /* Выделение памяти для данных экземпляра */
    pCMe = (CEcoLab1*)pIMem->pVTbl->Alloc(pIMem, sizeof(CEcoLab1));

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = pISys;

    /* Сохранение указателя на интерфейс для работы с памятью */
    pCMe->m_pIMem = pIMem;

    /* Установка счетчика ссылок на компонент */
    pCMe->m_cRef = 1;

    /* Создание таблицы функций интерфейса IEcoLab1 */
    pCMe->m_pVTblIEcoLab1 = &g_x277FC00C35624096AFCFC125B94EEC90VTbl;

    pCMe->m_pVTblIY = &g_xBD6414C29096423EA90C04D77AFD1CADVTblLab1;

    pCMe->m_pVTblIX = &g_x9322111622484742AE0682819447843DVTblLab1;

    pCMe->m_pVTblINondelegatingUnk = &g_x000000000000000000000000000000AAVTblLab1;

    pCMe->m_pIUnkOuter = 0;
    if (pIUnkOuter != 0) {
        pCMe->m_pIUnkOuter = pIUnkOuter;
    } else {
        pCMe->m_pIUnkOuter = (IEcoUnknown*)&pCMe->m_pVTblINondelegatingUnk;
    }

    /* Инициализация данных */
    pCMe->m_Name = 0;

    pCMe->m_pIY = 0;

    pCMe->m_pIX = 0;

    pCMe->m_pInnerUnknown = 0;

    /* Возврат указателя на интерфейс */
    *ppIEcoLab1 = (IEcoLab1*)pCMe;

    /* Освобождение */
    pIBus->pVTbl->Release(pIBus);

    return 0;
}

/*
 *
 * <сводка>
 *   Функция Delete
 * </сводка>
 *
 * <описание>
 *   Функция освобождения экземпляра
 * </описание>
 *
 */
void ECOCALLMETHOD deleteCEcoLab1(/* in */ IEcoLab1* pIEcoLab1) {
    CEcoLab1* pCMe = (CEcoLab1*)pIEcoLab1;
    IEcoMemoryAllocator1* pIMem = 0;

    if (pIEcoLab1 != 0 ) {
        pIMem = pCMe->m_pIMem;
        /* Освобождение */
        if ( pCMe->m_Name != 0 ) {
            pIMem->pVTbl->Free(pIMem, pCMe->m_Name);
        }
        if ( pCMe->m_pIY != 0) {
            pCMe->m_pIY->pVTbl->Release(pCMe->m_pIY);
        }
        if ( pCMe->m_pIX != 0 ) {
            pCMe->m_pIX->pVTbl->Release(pCMe->m_pIX);
        }
        if ( pCMe->m_pISys != 0 ) {
            pCMe->m_pISys->pVTbl->Release(pCMe->m_pISys);
        }
        pIMem->pVTbl->Free(pIMem, pCMe);
        pIMem->pVTbl->Release(pIMem);
    }
}

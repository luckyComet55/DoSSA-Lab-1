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


typedef struct {
    size_t size;
    bool_t direction_flag;
} sorted_sub_array_return_pair_t;

typedef struct {
    void* segment_ptr;
    size_t segment_size;
} start_size_stack_elem_t;

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

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return -1;
    }

    /* Проверка и получение запрошенного интерфейса */
    if ( IsEqualUGUID(riid, &IID_IEcoLab1) ) {
        *ppv = &pCMe->m_pVTblIEcoLab1;
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIEcoLab1;
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
    }
    else {
        *ppv = 0;
        return -1;
    }
    return 0;
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

    return ++pCMe->m_cRef;
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

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        deleteCEcoLab1((IEcoLab1*)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция MyFunction
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */



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
    Свапает заданное число байт
*/
void swap_bytes(
    char* elem1,
    char* elem2,
    size_t type_size
) {
    size_t i = 0;
    char* tmp;
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
        src[i] = dst[i];
    }
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
    size_t i = start_ptr;
    int cmp_prev = 0;
    int cmp_cur;
    size_t sub_sorted_size = 2;
    sorted_sub_array_return_pair_t res = {0, TRUE};

    do {
        cmp_cur = comp((char*)data + i * elem_size, (char*)data + (i + 1) * elem_size);
        cmp_prev = cmp_cur;
        i++;
    } while (cmp_prev != 0 && elem_count > i + 1);
    
    for (; i < elem_count - 1; ++i) {
        cmp_cur = comp((char*)data + i * elem_size, (char*)data + (i + 1) * elem_size);
        if (cmp_cur == 0 || cmp_cur == cmp_prev) {
            sub_sorted_size++;
        } else {
            break;
        }
    }
    res.size = sub_sorted_size;
    res.direction_flag = cmp_prev == 1;
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
    size_t left_ptr = 0, right_ptr = 0, buffer_ptr = 0, data_ptr = 0;
    size_t buffer_size = left_size;
    char* tmp_src_ptr;
    void* alive_src;
    size_t alive_src_ptr, alive_src_size;
    
    for (; left_ptr < left_size; ++left_ptr) {
        copy_bytes(
            (char*) left_sub_arr + left_ptr * elem_size,
            (char*) buffer + left_ptr * elem_size,
            elem_size
        );
    }

    for (; buffer_ptr < left_size && right_ptr < right_size;) {
        if (comp(
            (char*)buffer + buffer_ptr * elem_size, (char*)right_sub_arr + right_ptr * elem_size) <= 0
        ) {
            tmp_src_ptr = (char*)buffer + buffer_ptr * elem_size;
            buffer_ptr++;
        } else {
            tmp_src_ptr = (char*)right_sub_arr + right_ptr * elem_size;
            right_ptr++;
        }
        copy_bytes(
            tmp_src_ptr,
            (char*)data + data_ptr * elem_size,
            elem_size
        );
        data_ptr++;
    }

    if (buffer_ptr == left_size - 1) {
        alive_src = right_sub_arr;
        alive_src_ptr = right_ptr;
        alive_src_size = right_size;
    } else {
        alive_src = buffer;
        alive_src_ptr = buffer_ptr;
        alive_src_size = left_size;
    }

    for (; alive_src_ptr < alive_src_size; ++alive_src_ptr, ++data_ptr) {
        copy_bytes(
            (char*)alive_src + alive_src_ptr * elem_size,
            (char*)data + data_ptr * elem_size,
            elem_size
        );
    }
}

int16_t ECOCALLMETHOD CEcoLab1_qsort(
    struct IEcoLab1* me,
    void* pData,
    size_t elem_count,
    size_t elem_size,
    int (__cdecl *comp)(const void *, const void*)
) {
    int16_t min_run = get_min_run(elem_count);
    size_t sub_sorted_size = 0;

    if (elem_count < 2) {
        return 0;
    }

    return 0;
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
    int16_t result = -1;

    /* Проверка указателей */
    if (me == 0 ) {
        return result;
    }

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = (IEcoSystem1*)pIUnkSystem;

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pCMe->m_pISys->pVTbl->QueryInterface(pCMe->m_pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);

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

    /* Инициализация данных */
    pCMe->m_Name = 0;

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
        if ( pCMe->m_pISys != 0 ) {
            pCMe->m_pISys->pVTbl->Release(pCMe->m_pISys);
        }
        pIMem->pVTbl->Free(pIMem, pCMe);
        pIMem->pVTbl->Release(pIMem);
    }
}

#include "IEcoSystem1.h"
#include "IEcoInterfaceBus1.h"
#include "IEcoInterfaceBus1MemExt.h"
#include "CEcoLab2.h"
#include "IdEcoCalculatorD.h"
#include "IdEcoCalculatorE.h"
#include "IdEcoCalculatorB.h"
#include "IdEcoCalculatorA.h"
#include "IdEcoLab1.h"


int16_t ECOCALLMETHOD CEcoLab2_QueryInterface(/* in */ struct IEcoCalculatorY* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoLab2* pCMe = (CEcoLab2*)me;
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

uint32_t ECOCALLMETHOD CEcoLab2_AddRef(/* in */ struct IEcoCalculatorY* me) {
    CEcoLab2* pCMe = (CEcoLab2*)me;

    if (me == 0 ) {
        return -1;
    }

    return pCMe->m_pVTblINondelegatingUnk->AddRef((IEcoUnknown *)&pCMe->m_pVTblINondelegatingUnk);
}

uint32_t ECOCALLMETHOD CEcoLab2_Release(/* in */ struct IEcoCalculatorY* me) {
    CEcoLab2* pCMe = (CEcoLab2*)me;

    if (me == 0 ) {
        return -1;
    }

    return pCMe->m_pVTblINondelegatingUnk->Release((IEcoUnknown *)&pCMe->m_pVTblINondelegatingUnk);
}

int16_t ECOCALLMETHOD CEcoLab2_IEcoCalculatorX_QueryInterface(/* in */ struct IEcoCalculatorX* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoLab2* pCMe = (CEcoLab2 *)((uint64_t)me - sizeof(struct IEcoCalculatorY*));
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

uint32_t ECOCALLMETHOD CEcoLab2_IEcoCalculatorX_AddRef(/* in */ struct IEcoCalculatorX* me) {
    CEcoLab2* pCMe = (CEcoLab2*)((uint64_t)me - sizeof(struct IEcoCalculatorY*));

    if (me == 0 ) {
        return -1;
    }

    return pCMe->m_pVTblINondelegatingUnk->AddRef((IEcoUnknown *)&pCMe->m_pVTblINondelegatingUnk);
}

uint32_t ECOCALLMETHOD CEcoLab2_IEcoCalculatorX_Release(/* in */ struct IEcoCalculatorX* me) {
    CEcoLab2* pCMe = (CEcoLab2*)((uint64_t)me - sizeof(struct IEcoCalculatorY*));

    if (me == 0 ) {
        return -1;
    }

    return pCMe->m_pVTblINondelegatingUnk->Release((IEcoUnknown *)&pCMe->m_pVTblINondelegatingUnk);
}

int32_t ECOCALLMETHOD CEcoLab2_Multiplication(/* in */ struct IEcoCalculatorY* me, /* in */ int16_t a, /* in */ int16_t b) {
    CEcoLab2* pCMe = (CEcoLab2*)me;
    int32_t result = 0;

    if (me == 0 ) {
        return -1;
    }

    if (pCMe->m_pIY != 0) {
        result = pCMe->m_pIY->pVTbl->Multiplication(pCMe->m_pIY, a, b);
    }

    return result;
}

int16_t ECOCALLMETHOD CEcoLab2_Division(/* in */ struct IEcoCalculatorY* me, /* in */ int16_t a, /* in */ int16_t b) {
    CEcoLab2* pCMe = (CEcoLab2*)me;
    int16_t result = 0;

    if (me == 0 ) {
        return -1;
    }

    if (pCMe->m_pIY != 0) {
        result = pCMe->m_pIY->pVTbl->Division(pCMe->m_pIY, a, b);
    }

    return result;
}

int32_t ECOCALLMETHOD CEcoLab2_Addition(/* in */ struct IEcoCalculatorX* me, /* in */ int16_t a, /* in */ int16_t b) {
    CEcoLab2* pCMe = (CEcoLab2 *)((uint64_t)me - sizeof(struct IEcoCalculatorY*));
    int32_t result = 0;

    if (me == 0 ) {
        return -1;
    }

    if (pCMe->m_pIX != 0) {
        result = pCMe->m_pIX->pVTbl->Addition(pCMe->m_pIX, a, b);
    }

    return result;
}

int16_t ECOCALLMETHOD CEcoLab2_Subtraction(/* in */ struct IEcoCalculatorX* me, /* in */ int16_t a, /* in */ int16_t b) {
    CEcoLab2* pCMe = (CEcoLab2 *)((uint64_t)me - sizeof(struct IEcoCalculatorY*));
    int16_t result = 0;

    if (me == 0 ) {
        return -1;
    }

    if (pCMe->m_pIX != 0) {
        result = pCMe->m_pIX->pVTbl->Subtraction(pCMe->m_pIX, a, b);
    }

    return result;
}


// Функция QueryInterface для интерфейса IEcoLab2
int16_t ECOCALLMETHOD CEcoLab2_NondelegatingQueryInterface(/* in */ struct IEcoUnknown * me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoLab2* pCMe = (CEcoLab2*)((uint64_t)me - sizeof(struct IEcoCalculatorY*) - sizeof(struct IEcoCalculatorX*));
    int16_t result;
    if (me == 0 || ppv == 0) {
        return -1;
    }


    if ( IsEqualUGUID(riid, &IID_IEcoCalculatorY) ) {
        *ppv = &pCMe->m_pVTblIY;
        ++pCMe->m_cRef;
    }
    else if (IsEqualGUID(riid, &IID_IEcoCalculatorX)) {
        if (pCMe->m_pInnerUnknownB != 0) {
            result = pCMe->m_pInnerUnknownB->pVTbl->QueryInterface(pCMe->m_pInnerUnknownB, riid, ppv);
            return result;
        }
        else {
            *ppv = &pCMe->m_pVTblIX;
            ++pCMe->m_cRef;
        }
    }
    else if ( IsEqualGUID(riid, &IID_IEcoLab1) ) {
        if (pCMe->m_pInnerUnknownLab1 != 0) {
            result = pCMe->m_pInnerUnknownLab1->pVTbl->QueryInterface(pCMe->m_pInnerUnknownLab1, riid, ppv);
            return result;
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

// Функция AddRef для интерфейса IEcoLab2
uint32_t ECOCALLMETHOD CEcoLab2_NondelegatingAddRef(/* in */ struct IEcoUnknown* me) {
    CEcoLab2* pCMe = (CEcoLab2*)((uint64_t)me - sizeof(struct IEcoCalculatorY*) - sizeof(struct IEcoCalculatorX*));

    if (me == 0 ) {
        return -1;
    }

    return ++pCMe->m_cRef;
}

// Функция Release для интерфейса IEcoLab2
uint32_t ECOCALLMETHOD CEcoLab2_NondelegatingRelease(/* in */ struct IEcoUnknown* me) {
    CEcoLab2* pCMe = (CEcoLab2*)((uint64_t)me - sizeof(struct IEcoCalculatorY*) - sizeof(struct IEcoCalculatorX*));

    if (me == 0 ) {
        return -1;
    }

    --pCMe->m_cRef;

    if ( pCMe->m_cRef == 0 ) {
        deleteCEcoLab2((IEcoCalculatorY*)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}


IEcoCalculatorYVTbl g_xBD6414C29096423EA90C04D77AFD1CADVTblLab2 = {
    CEcoLab2_QueryInterface,
    CEcoLab2_AddRef,
    CEcoLab2_Release,
    CEcoLab2_Multiplication,
    CEcoLab2_Division
};

IEcoCalculatorXVTbl g_x9322111622484742AE0682819447843DVTblLab2 = {
        CEcoLab2_IEcoCalculatorX_QueryInterface,
        CEcoLab2_IEcoCalculatorX_AddRef,
        CEcoLab2_IEcoCalculatorX_Release,
        CEcoLab2_Addition,
        CEcoLab2_Subtraction
};

IEcoUnknownVTbl g_x000000000000000000000000000000AAVTblLab2 = {
        CEcoLab2_NondelegatingQueryInterface,
        CEcoLab2_NondelegatingAddRef,
        CEcoLab2_NondelegatingRelease
};


// Функция инициализации экземпляра
int16_t ECOCALLMETHOD initCEcoLab2(/*in*/ struct IEcoCalculatorY * me, /* in */ struct IEcoUnknown *pIUnkSystem) {
    CEcoLab2* pCMe = (CEcoLab2*)me;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoUnknown * pOuterUnknown = (IEcoUnknown *)me;
    int16_t result = -1;

    if (me == 0 ) {
        return result;
    }

    result = pCMe->m_pISys->pVTbl->QueryInterface(pCMe->m_pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);

    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab1, pOuterUnknown, &IID_IEcoUnknown, (void**)&pCMe->m_pInnerUnknownLab1);

    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorD, 0, &IID_IEcoCalculatorY, (void**) &pCMe->m_pIY);
    if (result != 0 || pCMe->m_pIY == 0) {
        result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorE, 0, &IID_IEcoCalculatorY, (void**) &pCMe->m_pIY);
    }

    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorB, (IEcoUnknown *)pCMe->m_pVTblINondelegatingUnk, &IID_IEcoUnknown, (void**) &pCMe->m_pInnerUnknownB);
    if (result != 0 || pCMe->m_pInnerUnknownB == 0) {
        result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorA, 0, &IID_IEcoCalculatorX, (void**) &pCMe->m_pIX);
    }

    pIBus->pVTbl->Release(pIBus);
	
    return result;
}

//  Функция создания экземпляра
int16_t ECOCALLMETHOD createCEcoLab2(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoUnknown* pIUnkOuter, /* out */ IEcoCalculatorY** ppIEcoCalculatorY) {
    int16_t result = -1;
    IEcoSystem1* pISys = 0;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoInterfaceBus1MemExt* pIMemExt = 0;
    IEcoMemoryAllocator1* pIMem = 0;
    CEcoLab2* pCMe = 0;
    UGUID* rcid = (UGUID*)&CID_EcoMemoryManager1;
	
    if (ppIEcoCalculatorY == 0 || pIUnkSystem == 0) {
        return result;
    }

    result = pIUnkSystem->pVTbl->QueryInterface(pIUnkSystem, &GID_IEcoSystem1, (void **)&pISys);

    if (result != 0 && pISys == 0) {
        return result;
    }

    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);

    result = pIBus->pVTbl->QueryInterface(pIBus, &IID_IEcoInterfaceBus1MemExt, (void**)&pIMemExt);
    if (result == 0 && pIMemExt != 0) {
        rcid = (UGUID*)pIMemExt->pVTbl->get_Manager(pIMemExt);
        pIMemExt->pVTbl->Release(pIMemExt);
    }

    pIBus->pVTbl->QueryComponent(pIBus, rcid, 0, &IID_IEcoMemoryAllocator1, (void**) &pIMem);

    if (result != 0 && pIMem == 0) {
        pISys->pVTbl->Release(pISys);
        return result;
    }

    pCMe = (CEcoLab2*)pIMem->pVTbl->Alloc(pIMem, sizeof(CEcoLab2));

    pCMe->m_pISys = pISys;

    pCMe->m_pIMem = pIMem;

    pCMe->m_cRef = 1;

    pCMe->m_pVTblIY = &g_xBD6414C29096423EA90C04D77AFD1CADVTblLab2;

    pCMe->m_pVTblIX = &g_x9322111622484742AE0682819447843DVTblLab2;

    pCMe->m_pVTblINondelegatingUnk = &g_x000000000000000000000000000000AAVTblLab2;

    pCMe->m_pIUnkOuter = 0;
    if (pIUnkOuter != 0) {
        pCMe->m_pIUnkOuter = pIUnkOuter;
    } else {
        pCMe->m_pIUnkOuter = (IEcoUnknown*)&pCMe->m_pVTblINondelegatingUnk;
    }

    pCMe->m_Name = 0;

    pCMe->m_pIY = 0;

    pCMe->m_pIX = 0;

    pCMe->m_pInnerUnknownLab1 = 0;

    pCMe->m_pInnerUnknownB = 0;

    *ppIEcoCalculatorY = (IEcoCalculatorY *)pCMe;

    pIBus->pVTbl->Release(pIBus);

    return 0;
}

//  Функция освобождения экземпляра
void ECOCALLMETHOD deleteCEcoLab2(/* in */ IEcoCalculatorY* pIEcoCalculatorY) {
    CEcoLab2* pCMe = (CEcoLab2*)pIEcoCalculatorY;
    IEcoMemoryAllocator1* pIMem = 0;

    if (pIEcoCalculatorY != 0 ) {
        pIMem = pCMe->m_pIMem;
        if ( pCMe->m_Name != 0 ) {
            pIMem->pVTbl->Free(pIMem, pCMe->m_Name);
        }
        if ( pCMe->m_pIY != 0) {
            pCMe->m_pIY->pVTbl->Release(pCMe->m_pIY);
        }
        if ( pCMe->m_pISys != 0 ) {
            pCMe->m_pISys->pVTbl->Release(pCMe->m_pISys);
        }
        pIMem->pVTbl->Free(pIMem, pCMe);
        pIMem->pVTbl->Release(pIMem);
    }
}
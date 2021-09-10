#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc, free */

/* global functions and variables */

int s_count;

void print_count()
{
    printf("s_count: %d\n", s_count);
}

void print_info()
{
    print_count();
}

/* PublicTrasport */

void PTdisplayVT(void* PT);

struct PTvtable
{
    void (*display)(void*);

} PTvtable = {&PTdisplayVT};

typedef struct
{
    void* vptr;
    int m_license_plate;

} PublicTransport;

void PTctor(PublicTransport* PT)
{
    (void*)PT = &PTvtable;

    ++s_count;
    PT->m_license_plate = s_count;

    printf("PublicTransport::Ctor()%d\n", PT->m_license_plate);
}

void PTdtor(PublicTransport* PT)
{
    (void*)PT = &PTvtable;

    --s_count;

    printf("PublicTransport::Dtor()%d\n", PT->m_license_plate);
}

void PTcctor(PublicTransport* PT, const PublicTransport* other)
{
    (void*)PT = &PTvtable;

    ++s_count;
    PT->m_license_plate = s_count;

    printf("PublicTransport::CCtor() %d\n", PT->m_license_plate);
}

void PTdisplayVT(void* PT)
{
    printf("PublicTransport::display(): %d\n", ((PublicTransport*)PT)->m_license_plate);
}

int get_ID(PublicTransport* PT)
{
    return PT->m_license_plate;
}

void print_info_PT(PublicTransport* PT)
{
    ((struct PTvtable*)(PT->vptr))->display(PT);
}

/* Minibus */

void MBdisplayVT(void* MB);
void MBwashVT(void* MB, int minutes);

struct MBvtable
{
    void (*display)(void*);
    void (*wash)(void*, int minutes);

} MBvtable = {&MBdisplayVT, &MBwashVT};

typedef struct
{
    PublicTransport PT;
    int m_numSeats;

} Minibus;

void MBctor(Minibus* MB)
{
    PTctor(&MB->PT);
    
    (void*)MB = &MBvtable;
    
    MB->m_numSeats = 20;

    printf("Minibus::Ctor()\n");
}

void MBdtor(Minibus* MB)
{
    (void*)MB = &MBvtable;

    printf("Minibus::Dtor()\n");

    PTdtor(&MB->PT);
}

void MBcctor(Minibus* MB, const Minibus* other)
{
    PTcctor(&MB->PT, &other->PT);

    MB->m_numSeats = other->m_numSeats;
    (void*)MB = &MBvtable;

    printf("Minibus::CCtor()\n");
}

void MBdisplayVT(void* MB)
{
    printf("Minibus::display() ID:%d", get_ID(&((Minibus*)MB)->PT));
    printf(" num seats:%d\n", ((Minibus*)MB)->m_numSeats);
}

void MBwashVT(void* MB, int minutes)
{
    printf("Minibus::wash(%d) ID:%d\n", minutes, get_ID(&((Minibus*)MB)->PT));
}

void print_info_MB(Minibus* MB)
{
   ((struct MBvtable*)(MB->PT.vptr))->wash(MB, 3);
}

void print_info_INT_and_cpy(int i, PublicTransport* to_cpy_to)
{
    Minibus ret;
    MBctor(&ret);
    printf("print_info(int i)\n");
    ((struct MBvtable*)(ret.PT.vptr))->display(&ret);
    PTcctor(to_cpy_to, &ret.PT);
    MBdtor(&ret);
}

/* Taxi */

void TXdisplayVT(void* TX);

struct TXvtable
{
    void (*display)(void*);

} TXvtable = {&TXdisplayVT};

typedef struct
{
    PublicTransport PT;

} Taxi;

void TXctor(Taxi* TX)
{
    PTctor(&TX->PT);
    
    (void*)TX = &TXvtable;

    printf("Taxi::Ctor()\n");
}

void TXdtor(Taxi* TX)
{
    (void*)TX = &TXvtable;

    printf("Taxi::Dtor()\n");
    PTdtor(&TX->PT);
}

void TXcctor(Taxi* TX, const Taxi* other)
{
    PTcctor(&TX->PT, &other->PT);

    (void*)TX = &TXvtable;

    printf("Taxi::CCtor()\n");
}

void TXdisplayVT(void* TX)
{
    printf("Taxi::display() ID:%d\n", get_ID(&((Taxi*)TX)->PT));
}

void taxi_display(Taxi s)
{
    ((struct TXvtable*)(s.PT.vptr))->display(&s);
}

/* special taxi */

void STXdisplayVT(void* STX);

struct STXvtable
{
    void (*display)(void*);

} STXvtable = {&STXdisplayVT};

typedef struct
{
    Taxi TX;

} SpecialTaxi;

void STXctor(SpecialTaxi* STX)
{
    TXctor(&STX->TX);
    
    (void*)STX = &STXvtable;

    printf("SpecialTaxi::Ctor()\n");
}

void STXdtor(SpecialTaxi* STX)
{
    (void*)STX = &STXvtable;

    printf("SpecialTaxi::Dtor()\n");

    TXdtor(&STX->TX);
}

void STXcctor(SpecialTaxi* STX, const SpecialTaxi* other)
{
    TXcctor(&STX->TX, &other->TX);

    (void*)STX = &STXvtable;

    printf("SpecialTaxi::CCtor()\n");
}

void STXdisplayVT(void* STX)
{
    printf("SpecialTaxi::display() ID:%d", get_ID(&((SpecialTaxi*)STX)->TX.PT));
}

/* public convoy */

void PCdisplayVT(void* PC);

struct PCvtable
{
    void (*display)(void*);

} PCvtable = {&PCdisplayVT};

typedef struct 
{
    PublicTransport PT;
    PublicTransport* m_pt1;
    PublicTransport* m_pt2;
    Minibus m_m;
    Taxi m_t;

} PublicConvoy;

void PCctor(PublicConvoy* PC)
{
    PTctor(&PC->PT);
    (void*)PC = &PCvtable;

    PC->m_pt1 = malloc(sizeof(Minibus));
    MBctor((Minibus*)PC->m_pt1);
    PC->m_pt2= malloc(sizeof(Taxi));
    TXctor((Taxi*)PC->m_pt2);
    MBctor(&PC->m_m);
    TXctor(&PC->m_t);
}

void PCcctor(PublicConvoy* PC, const PublicConvoy* other)
{
    PTcctor(&PC->PT, &other->PT);
    PC->m_pt1 = other->m_pt1;
    PC->m_pt2 = other->m_pt2;
    MBcctor(&PC->m_m, &other->m_m);
    TXcctor(&PC->m_t, &other->m_t);

    (void*)PC = &PCvtable;
}

void PCdtor(PublicConvoy* PC)
{
    (void*)PC = &PCvtable;

    MBdtor((Minibus*)PC->m_pt1);
    free(PC->m_pt1);
    TXdtor((Taxi*)PC->m_pt2);
    free(PC->m_pt2);
    TXdtor(&PC->m_t);
    MBdtor(&PC->m_m);

    PTdtor(&PC->PT);
}

void PCdisplayVT(void* PC)
{
    ((struct MBvtable*)(((PublicConvoy*)PC)->m_pt1->vptr))->display(((PublicConvoy*)PC)->m_pt1);
    ((struct TXvtable*)(((PublicConvoy*)PC)->m_pt2->vptr))->display(((PublicConvoy*)PC)->m_pt2);
    ((struct MBvtable*)(((PublicConvoy*)PC)->m_m.PT.vptr))->display(&((PublicConvoy*)PC)->m_m);
    ((struct TXvtable*)(((PublicConvoy*)PC)->m_t.PT.vptr))->display(&((PublicConvoy*)PC)->m_t);
}

/* main */

int main()
{
    Minibus m;
    MBctor(&m);

    print_info_MB(&m);

    {
        PublicTransport tmp;
        print_info_INT_and_cpy(3, &tmp);
        ((struct PTvtable*)(tmp.vptr))->display(&tmp);
        PTdtor(&tmp);
    }

    PublicTransport* array[3];
    array[0] = (PublicTransport*)malloc(sizeof(Minibus));
    MBctor((Minibus*)array[0]);
    array[1] = (PublicTransport*)malloc(sizeof(Taxi));
    TXctor((Taxi*)array[1]);
    array[2] = (PublicTransport*)malloc(sizeof(Minibus));
    
    MBctor((Minibus*)array[2]);
    ((struct MBvtable*)(array[0]->vptr))->display(array[0]);
    ((struct TXvtable*)(array[1]->vptr))->display(array[1]);
    ((struct MBvtable*)(array[2]->vptr))->display(array[2]);    
    MBdtor((Minibus*)array[0]);
    free(array[0]);
    TXdtor((Taxi*)array[1]);
    free(array[1]);
    MBdtor((Minibus*)array[2]);
    free(array[2]);

    PublicTransport arr2[3];

    {
        Minibus tmp2;
        MBctor(&tmp2);
        PTcctor(&arr2[0], &tmp2.PT);
        MBdtor(&tmp2);
    }

    {
        Taxi tmp3;
        TXctor(&tmp3);
        PTcctor(&arr2[1], &tmp3.PT);
        TXdtor(&tmp3);
    }

    PTctor(&arr2[2]);
    ((struct PTvtable*)(arr2[0].vptr))->display(&arr2[0]);
    ((struct PTvtable*)(arr2[1].vptr))->display(&arr2[1]);
    ((struct PTvtable*)(arr2[2].vptr))->display(&arr2[2]);

    print_info_PT(&arr2[0]);
    print_count();
    Minibus m2;
    MBctor(&m2);
    print_count();

    Minibus arr3[4];
    for (int i = 0; i < 4; ++i)
    {
        MBctor(&arr3[i]);
    }
    
    Taxi* arr4 = (Taxi*)malloc(sizeof(Taxi) * 4);
    for (int i = 0; i < 4; ++i)
    {
        TXctor(&arr4[i]);
    }

    for (int i = 3; i >= 0; --i)
    {
        TXdtor(&arr4[i]);
    }
    free(arr4);

    printf("%d\n", ((1 > 2) ? (1) : (2)));
    printf("%d\n", ((1 > (int(2.0f)) ? (1) : (int(2.0f))));

    SpecialTaxi st;
    STXctor(&st);

    {
        Taxi tmp4;
        TXcctor(&tmp4, &st.TX);
        taxi_display(tmp4);
        TXdtor(&tmp4);
    }

    PublicConvoy* ts1 = malloc(sizeof(PublicConvoy));
    PCctor(ts1);
    PublicConvoy* ts2 = malloc(sizeof(PublicConvoy));
    PCcctor(ts2, ts1);
    ((struct PCvtable*)(ts1->PT.vptr))->display(ts1);
    ((struct PCvtable*)(ts2->PT.vptr))->display(ts2);
    PCdtor(ts1);
    free(ts1);
    ((struct PCvtable*)(ts2->PT.vptr))->display(ts2);
    PCdtor(ts2);
    free(ts2);

    STXdtor(&st);

    for (int i = 4; i >= 0; --i)
    {
        MBdtor(&arr3[i]);
    }

    MBdtor(&m2);

    for (int i = 4; i >= 0; --i)
    {
        PTdtor(&arr2[i]);
    }

    MBdtor(&m);

    return 0;
}

























#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc, free */

/**************************************************/

enum {dtor, display};

int s_count;

void print_count()
{
    printf("s_count: %d\n", s_count);
}


/*************** PublicTransport ******************/

typedef struct PublicTransport PublicTransport_t;

void public_transport_dtor(PublicTransport_t*);
void public_transport_display(PublicTransport_t*);

struct PublicTransport
{
    void** Vpointer;
    int m_license_plate;
};

void* PublicTransportVtable[2] = {(void*)public_transport_dtor, (void*)public_transport_display};

void public_transport_ctor(PublicTransport_t* this)
{
    this->Vpointer = PublicTransportVtable;
    this->m_license_plate = ++s_count;

    printf("PublicTransport::Ctor()%d\n", this->m_license_plate);
}

void public_transport_dtor(PublicTransport_t* this)
{
    --s_count;

    printf("PublicTransport::Dtor()%d\n", this->m_license_plate);
}                                                       

void public_transport_cctor(PublicTransport_t* this, const PublicTransport_t* other)
{
    this->Vpointer = other->Vpointer;
    this->m_license_plate = ++s_count;

    printf("PublicTransport::CCtor() %d\n", this->m_license_plate);
}

void public_transport_display(PublicTransport_t* this)
{
    printf("PublicTransport::display(): %d\n", this->m_license_plate);
}

int get_ID(void* this)
{
    return ((PublicTransport_t*)this)->m_license_plate;
}

PublicTransport_t* NewPublicTransport()
{
    PublicTransport_t* new = (PublicTransport_t*)malloc(sizeof(PublicTransport_t));

    public_transport_ctor(new);

    return new;
}

void DeletePublicTransport(PublicTransport_t* pt)
{
    ((void (*)(PublicTransport_t*))(pt->Vpointer[dtor]))(pt);
    free(pt);
}

/*************** Minibus *****************/

typedef struct Minibus Minibus_t;

void minibus_dtor(Minibus_t*);
void minibus_display(Minibus_t*);
void minibus_wash(Minibus_t*, int);

struct Minibus
{
   PublicTransport_t pt;
   int m_numSeats;
};

void* MinibusVtable[3] = {(void*)minibus_dtor, (void*)minibus_display,
                            (void*)minibus_wash};

void minibus_ctor(Minibus_t* this)
{
    public_transport_ctor(&this->pt);
    this->pt.Vpointer = MinibusVtable;
    this->m_numSeats = 20;

    printf("Minibus::Ctor()\n");
}

void minibus_dtor(Minibus_t* this)
{
    printf("Minibus::Dtor()\n");

    this->pt.Vpointer = PublicTransportVtable;

    public_transport_dtor(&this->pt);
}                                                       

void minibus_cctor(Minibus_t* this, const Minibus_t* other)
{
    public_transport_cctor(&this->pt, &other->pt);

    this->pt.Vpointer = other->pt.Vpointer;
    this->m_numSeats = other->m_numSeats;

    printf("Minibus::CCtor()\n");
}

void minibus_display(Minibus_t* this)
{
    printf("Minibus::display() ID:%d num seats:%d\n",
                        get_ID(this), this->m_numSeats);
}

void minibus_wash(Minibus_t* this, int minutes)
{
    printf("Minibus::wash(%d) ID:%d\n", minutes, get_ID(this));
}

Minibus_t* NewMinibus()
{
    Minibus_t* new = (Minibus_t*)malloc(sizeof(Minibus_t));

    minibus_ctor(new);

    return new;
}

void DeleteMinibus(Minibus_t* mb)
{
    ((void (*)(Minibus_t*))(mb->pt.Vpointer[dtor]))(mb);
    free(mb);
}

/*************** Taxi *****************/

typedef struct Taxi Taxi_t;

void taxi_dtor(Taxi_t*);
void taxi_display(Taxi_t*);

struct Taxi
{
   PublicTransport_t pt;
};

void* TaxiVtable[2] = {(void*)taxi_dtor, (void*)taxi_display};

void taxi_ctor(Taxi_t* this)
{
    public_transport_ctor(&this->pt);
    this->pt.Vpointer = TaxiVtable;

    printf("Taxi::Ctor()\n");
}

void taxi_dtor(Taxi_t* this)
{
    printf("Taxi::Dtor()\n");

    this->pt.Vpointer = PublicTransportVtable;

    public_transport_dtor(&this->pt);
}                                                       

void taxi_cctor(Taxi_t* this, const Taxi_t* other)
{
    public_transport_cctor(&this->pt, &other->pt);

    this->pt.Vpointer = other->pt.Vpointer;

    printf("Taxi::CCtor()\n");
}

void taxi_display(Taxi_t* this)
{
    printf("Taxi::display() ID:%d\n", get_ID(this));
}

Taxi_t* NewTaxi()
{
    Taxi_t* new = (Taxi_t*)malloc(sizeof(Taxi_t));

    taxi_ctor(new);

    return new;
}

void DeleteTaxi(Taxi_t* tx)
{
    ((void (*)(Taxi_t*))(tx->pt.Vpointer[dtor]))(tx);
    free(tx);
}

Taxi_t* NewTaxiArr(size_t n_elements)
{
    size_t* start_of_memory_block = (size_t*)malloc(sizeof(size_t) + sizeof(Taxi_t) * n_elements);

    *start_of_memory_block = n_elements;
    Taxi_t* retval = (Taxi_t*)(++start_of_memory_block);

    for (int i = 0; i < n_elements; ++i)
    {
        taxi_ctor(retval + i);
    }

    return retval;
}

void DeleteTaxiArr(Taxi_t* arr)
{
    size_t n_elements = *((size_t*)arr - 1);

    for (int i = n_elements; i > 0; --i)
    {
        ((void (*)(Taxi_t*))((arr + i -1)->pt.Vpointer[dtor]))(arr + i - 1);
    }

    free((size_t*)arr - 1);
}

/*************** SpecialTaxi *****************/

typedef struct SpecialTaxi SpecialTaxi_t;

void special_taxi_dtor(SpecialTaxi_t*);
void special_taxi_display(SpecialTaxi_t*);

struct SpecialTaxi
{
    Taxi_t tx;
};

void* SpecialTaxiVtable[2] = {(void*)special_taxi_dtor, (void*)special_taxi_display};

void special_taxi_ctor(SpecialTaxi_t* this)
{
    taxi_ctor(&this->tx);
    this->tx.pt.Vpointer = SpecialTaxiVtable;

    printf("SpecialTaxi::Ctor()\n");
}

void special_taxi_dtor(SpecialTaxi_t* this)
{
    printf("SpecialTaxi::Dtor()\n");

    this->tx.pt.Vpointer = TaxiVtable;

    taxi_dtor(&this->tx);
}                                                       

void special_taxi_cctor(SpecialTaxi_t* this, const SpecialTaxi_t* other)
{
    taxi_cctor(&this->tx, &other->tx);

    this->tx.pt.Vpointer = other->tx.pt.Vpointer;

    printf("SpecialTaxi::CCtor()\n");
}

void special_taxi_display(SpecialTaxi_t* this)
{
    printf("SpecialTaxi::display() ID:%d\n", get_ID(this));
}

SpecialTaxi_t* NewSpecialTaxi()
{
    SpecialTaxi_t* new = (SpecialTaxi_t*)malloc(sizeof(SpecialTaxi_t));

    special_taxi_ctor(new);

    return new;
}

void DeleteSpecialTaxi(SpecialTaxi_t* stx)
{
    ((void (*)(SpecialTaxi_t*))(stx->tx.pt.Vpointer[dtor]))(stx);
    free(stx);
}

/*************** PublicConvoy *****************/

typedef struct PublicConvoy PublicConvoy_t;

void public_convoy_dtor(PublicConvoy_t*);
void public_convoy_display(PublicConvoy_t*);

struct PublicConvoy
{
    PublicTransport_t pt;
    PublicTransport_t* m_pt1;
    PublicTransport_t* m_pt2;
    Minibus_t m_m;
    Taxi_t m_t;
};

void* PublicConvoyVtable[2] = {(void*)public_convoy_dtor, (void*)public_convoy_display};

void public_convoy_ctor(PublicConvoy_t* this)
{
    public_transport_ctor(&this->pt);
    this->pt.Vpointer = PublicConvoyVtable;

    this->m_pt1 = (PublicTransport_t*)NewMinibus();
    this->m_pt2 = (PublicTransport_t*)NewTaxi();

    minibus_ctor(&this->m_m);
    taxi_ctor(&this->m_t);
}

void public_convoy_dtor(PublicConvoy_t* this)
{
    DeletePublicTransport(this->m_pt1);
    DeletePublicTransport(this->m_pt2);

    taxi_dtor(&this->m_t);
    minibus_dtor(&this->m_m);

    this->pt.Vpointer = PublicTransportVtable;

    public_transport_dtor(&this->pt);
}                                                       

void public_convoy_cctor(PublicConvoy_t* this, const PublicConvoy_t* other)
{
    public_transport_cctor(&this->pt, &other->pt);

    this->pt.Vpointer = other->pt.Vpointer;
    this->m_pt1 = other->m_pt1;
    this->m_pt2 = other->m_pt2;
    minibus_cctor(&this->m_m, &other->m_m);
    taxi_cctor(&this->m_t, &other->m_t);
}

void public_convoy_display(PublicConvoy_t* this)
{
    ((void (*)(PublicTransport_t*))(this->m_pt1->Vpointer[display]))(this->m_pt1);
    ((void (*)(PublicTransport_t*))(this->m_pt2->Vpointer[display]))(this->m_pt2);
    minibus_display(&this->m_m);
    taxi_display(&this->m_t);
}

PublicConvoy_t* NewPublicConvoy()
{
    PublicConvoy_t* new = (PublicConvoy_t*)malloc(sizeof(PublicConvoy_t));

    public_convoy_ctor(new);

    return new;
}

PublicConvoy_t* NewPublicConvoyParam(PublicConvoy_t* other)
{
    PublicConvoy_t* new = (PublicConvoy_t*)malloc(sizeof(PublicConvoy_t));

    public_convoy_cctor(new, other);

    return new;
}

void DeletePublicConvoy(PublicConvoy_t* pc)
{
    ((void (*)(PublicConvoy_t*))(pc->pt.Vpointer[dtor]))(pc);
    free(pc);
}

/************************************************/

void print_info_public_transport(PublicTransport_t* a)
{
    public_transport_display(a);
}

void print_info()
{
    print_count();
}

void print_info_minibus(Minibus_t* m)
{
    minibus_wash(m, 3);
}

void print_info_int(PublicTransport_t* outParam, int i)
{
    Minibus_t ret;
    minibus_ctor(&ret);
    printf("print_info(int i)\n");
    minibus_display(&ret);
    public_transport_cctor(outParam, &ret.pt);
    minibus_dtor(&ret);
}

void taxi_display_global(Taxi_t* s)
{
    taxi_display(s);
}

/******************** Main **********************/

int main()
{
    union
    {
        PublicTransport_t pt;
        Minibus_t mb;
        Taxi_t tx;

    }tmp;
    
    /* 190 */
    Minibus_t m;
    minibus_ctor(&m);

    /* 191 */
    print_info_minibus(&m);

    /* 192 */
    print_info_int(&tmp.pt, 3);
    public_transport_display(&tmp.pt);
    public_transport_dtor(&tmp.pt);

    /* 193 */
    PublicTransport_t* array[] = {(PublicTransport_t*)NewMinibus(), 
                                  (PublicTransport_t*)NewTaxi(),
                                  (PublicTransport_t*)NewMinibus()};

    /* 194 */
    ((void (*)(Minibus_t*))(array[0]->Vpointer[display]))((Minibus_t*)array[0]);
    ((void (*)(Taxi_t*))(array[1]->Vpointer[display]))((Taxi_t*)array[1]);
    ((void (*)(Minibus_t*))(array[2]->Vpointer[display]))((Minibus_t*)array[2]);

    /* 198 */
    DeleteMinibus((Minibus_t*)array[0]);
    DeleteTaxi((Taxi_t*)array[1]);
    DeleteMinibus((Minibus_t*)array[2]);

    /* 202 */
    PublicTransport_t arr2[3];
    minibus_ctor(&tmp.mb);
    public_transport_cctor(&arr2[0], (PublicTransport_t*)&tmp.mb);
    minibus_dtor(&tmp.mb);
    taxi_ctor(&tmp.tx);
    public_transport_cctor(&arr2[1], (PublicTransport_t*)&tmp.tx);
    taxi_dtor(&tmp.tx);
    public_transport_ctor(&arr2[2]);

    /* 204 */
    for(int i = 0; i < 3; ++i)
    {
        public_transport_display(&arr2[i]);
    }

    /* 207 */
    print_info_public_transport(&arr2[0]);

    /* 209 */
    print_count();

    /* 210 */
    Minibus_t m2;
    minibus_ctor(&m2);

    /* 211 */
    print_count();

    /* 213 */
    Minibus_t arr3[4];
    for (int i = 0; i < 4; ++i)
    {
        minibus_ctor(&arr3[i]);
    }

    /* 214 */
    Taxi_t* arr4 = NewTaxiArr(4);
    
    /* 215 */
    DeleteTaxiArr(arr4);

    /* 217 */
    printf("%d\n", ((1 > 2) ? 1 : 2));

    /* 218 */
    printf("%d\n", (int)((1 > 2.0f) ? 1 : 2.0f));

    /* 219 */
    SpecialTaxi_t st;
    special_taxi_ctor(&st);

    /* 220 */
    taxi_cctor(&tmp.tx, &st.tx);
    taxi_display_global(&tmp.tx);
    taxi_dtor(&tmp.tx);
    
    /* 222 */
    PublicConvoy_t* ts1 = NewPublicConvoy();

    /* 223 */
    PublicConvoy_t* ts2 = NewPublicConvoyParam(ts1);

    /* 224 */
    ((void (*)(PublicConvoy_t*))(ts1->pt.Vpointer[display]))(ts1);

    /* 225 */
    ((void (*)(PublicConvoy_t*))(ts2->pt.Vpointer[display]))(ts2);

    /* 226 */
    DeletePublicConvoy(ts1);

    /* 227 */
    ((void (*)(PublicConvoy_t*))(ts2->pt.Vpointer[display]))(ts2);

    /* 228 */
    DeletePublicConvoy(ts2);

    /* cleanup */
    special_taxi_dtor(&st);

    for (int i = 4; i > 0; --i)
    {
        minibus_dtor(&arr3[i - 1]);
    }

    minibus_dtor(&m2);

    for (int i = 3; i > 0; --i)
    {
        public_transport_dtor(&arr2[i - 1]);
    }

    minibus_dtor(&m);

    return 0;
}
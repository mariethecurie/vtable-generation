#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char* class_name;
} TI;

typedef struct {
    TI* type_info;
    void (*f1)();
    void (*f2)();
} baseVTBL;

typedef struct {
    TI* type_info;
    void (*f1)();
    void (*f2)();
    void (*f3)();
} derivedVTBL;

void b_v_o() {
    printf("Virtual + overridden method of Base.\n");
}

void b_v_n_o() {
    printf("Virtual method of Base.\n");
}

void b_n_v() {
    printf("Not virtual method of Base.\n");
}

void d_v() {
    printf("Virtual method of Derived.\n");
}

void d_v_o() {
    printf("Virtual and overriden method of Derived.\n");
}

typedef struct {
    int x;
    baseVTBL* vptr;
} Base;

void base_ctor(Base* this, int x) {
    this->x = x;
    this->vptr->type_info->class_name = "Base";
    this->vptr->f1 = &b_v_o;
    this->vptr->f2 = &b_v_n_o;
}

typedef struct {
    Base base;
    derivedVTBL* vptr;
    int y;
} Derived;

void derived_ctor(Derived* this, int x, int y) {
    base_ctor(&this->base, x);
    this->y = y;
    this->vptr->type_info->class_name = "Derived";
    this->vptr->f1 = &d_v_o;
    this->vptr->f2 = &b_v_n_o;
    this->vptr->f3 = &d_v;
}

int main() {
    Derived* derived = malloc(sizeof(Derived));

    derived->base.vptr = malloc(sizeof(baseVTBL));
    derived->base.vptr->type_info = malloc(sizeof(TI));

    derived->vptr = malloc(sizeof(derivedVTBL));
    derived->vptr->type_info = malloc(sizeof(TI));

    derived_ctor(derived, 20, 30);
    derived->vptr->f1();
    derived->vptr->f2();
    derived->vptr->f3();

    free(derived->vptr->type_info);
    free(derived->vptr);
    free(derived->base.vptr->type_info);
    free(derived->base.vptr);
    free(derived);

    return 0;
}

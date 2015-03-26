#ifndef CONTABILIDADE_H

#define CONTABILIDADE_H

#include "avl.h"

#define MAX_MONTH 12
#define MAX_LETTERS 26

typedef struct CONTA_struct {
        AAVL[MAX_LETTERS];
} CONTA_struct;

typedef CONTA_struct *CONTA;

typedef CONTA CONTABILIDADE[MAX_MONTH];

#endif

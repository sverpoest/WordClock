// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef _ACC_H
#define	_ACC_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include "mcc_generated_files/mcc.h"

void Acc_Initialize();
void AccRead();

#endif	/* _ACC_H */


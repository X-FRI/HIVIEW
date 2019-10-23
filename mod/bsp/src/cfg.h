#ifndef __cfg_h__
#define __cfg_h__

#include "bsp.h"

extern gsf_bsp_def_t bsp_def;
extern gsf_bsp_parm_t bsp_parm;

int json_def_load(char *filename, gsf_bsp_def_t *cfg);
int json_def_save(char *filename, gsf_bsp_def_t *cfg);
int json_parm_load(char *filename, gsf_bsp_parm_t *cfg);
int json_parm_save(char *filename, gsf_bsp_parm_t *cfg);

#endif
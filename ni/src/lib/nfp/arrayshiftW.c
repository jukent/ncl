#include <stdio.h>
#include <string.h>
#include <math.h>
#include "wrapper.h"

extern ng_size_t indx(ng_size_t,ng_size_t);

NhlErrorTypes arrayshift_W( void )
{

/*
 * Input variables
 */
  NclStackEntry data;
  NclMultiDValData tmp_md = NULL;
  int ndims_x;
  ng_size_t *dsizes_x;
  int *kmode;
/*
 * Return variable
 */
  void *xshift;

/*
 * Various
 */
  ng_size_t i, j, nrows, ncols, size_x;
  ng_size_t x_pos, xshift_pos;
  int type_size, ret;

/*
 * Retrieve input.
 */
  data = _NclGetArg(0,2,DONT_CARE);
  switch(data.kind) {
  case NclStk_VAR:
    tmp_md = _NclVarValueRead(data.u.data_var,NULL,NULL);
    break;
  case NclStk_VAL:
    tmp_md = (NclMultiDValData)data.u.data_obj;
    break;
  default:
    NhlPError(NhlFATAL,NhlEUNKNOWN,"arrayshift: invalid first input argument.");
    return(NhlFATAL);
  }
  ndims_x   = tmp_md->multidval.n_dims;
  dsizes_x  = tmp_md->multidval.dim_sizes;
  type_size = tmp_md->multidval.type->type_class.size;

  kmode = (int*)NclGetArgValue(
           1,
           2,
           NULL,
           NULL,
           NULL,
           NULL,
           NULL,
           DONT_CARE);

/* 
 * Allocate space for return array.
 */
  size_x = 1;
  for(i = 0; i < ndims_x; i++) size_x *= dsizes_x[i];
  xshift = (void*)NclMalloc(size_x*type_size);
  if( xshift == NULL ) {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"arrayshift: Unable to allocate memory for output array");
    return(NhlFATAL);
  }

  if(ndims_x == 1) {
    nrows = 1;
    ncols = dsizes_x[0];
  }
  else if(ndims_x == 2) {
    nrows = dsizes_x[0];
    ncols = dsizes_x[1];
  }
  else {
    NhlPError(NhlFATAL,NhlEUNKNOWN,"arrayshift: Input array must be 1D or 2D");
    return(NhlFATAL);
  }
  /*
  else {
    nrows = dsizes_x[ndims_x-2];
    ncols = dsizes_x[ndims_x-1];
  }
  */    
  if (*kmode == 0) {
    for(j = 0; j < nrows; j++) {
      x_pos      = j*ncols;
      xshift_pos = indx(j,nrows)*ncols;
      for(i = 0; i < ncols; i++) {
        memcpy((void*)((char*)xshift + (xshift_pos+indx(i,ncols))*type_size),
               (void*)((char*)tmp_md->multidval.val + (x_pos+i)*type_size),
               type_size);
      }
    }
  }
  else if (*kmode < 0) {
    for(j = 0; j < nrows; j++) {
      x_pos      = j*ncols;
      xshift_pos = indx(j,nrows)*ncols;
      for(i = 0; i < ncols; i++) {
        memcpy((void*)((char*)xshift + (xshift_pos+i)*type_size),
                       (void*)((char*)tmp_md->multidval.val + 
                               (x_pos+i)*type_size),type_size);
      }
    }
  }
  else {
    for(j = 0; j < nrows; j++) {
      x_pos      = j*ncols;
      xshift_pos = x_pos;
      for(i = 0; i < ncols; i++) {
        memcpy((void*)((char*)xshift + (xshift_pos+indx(i,ncols))*type_size),
               (void*)((char*)tmp_md->multidval.val + (x_pos+i)*type_size),
               type_size);
      }
    }
  }
/*
 * Return value back to NCL script.
 */
  ret = NclReturnValue(xshift,ndims_x,dsizes_x,NULL,
                       tmp_md->multidval.data_type,0);
  return(ret);
}


ng_size_t indx(ng_size_t i,ng_size_t nrc)
{
  return((i+nrc/2) % nrc);
}

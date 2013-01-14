/***************************************************************************
 Private methods:
 SEXP rowOrderStats_<Integer|Real>(SEXP x, int nrow, int ncol, int qq)

 Authors: Adopted from rowQ() by R. Gentleman.

 To do: Add support for missing values.

 Copyright Henrik Bengtsson, 2007-2013
 **************************************************************************/
#include <Rdefines.h>
#include <Rmath.h>

/* Setup template macros */
#include "templates-types.h" 
#if R_TYPE == 'i'
  #define PSORT iPsort
#elif R_TYPE == 'r'
  #define PSORT rPsort
#endif


SEXP METHOD_TYPE(SEXP x, int nrow, int ncol, int qq) {
  SEXP ans;
  int ii, jj;
  int *colOffset;
  X_C_TYPE *rowData, *xx;

  /* R allocate a double vector of length 'nrow' */
  PROTECT(ans = allocVector(ANS_SXP, nrow));

  /* R allocate memory for the 'rowData'.  This will be 
     taken care of by the R garbage collector later on. */
  rowData = (X_C_TYPE *) R_alloc(ncol, sizeof(X_C_TYPE));

  /* Pre-calculate the column offsets */
  colOffset = (int *) R_alloc(ncol, sizeof(int));
  for(jj=0; jj < ncol; jj++) 
    colOffset[jj] = (int)jj*nrow;

  xx = X_IN_C(x);
  for(ii=0; ii < nrow; ii++) {
    for(jj=0; jj < ncol; jj++) 
      rowData[jj] = xx[ii+colOffset[jj]];

    /* Sort vector of length 'ncol' up to position 'qq'. 
       "...partial sorting: they permute x so that x[k] is in the
       correct place with smaller values to the left, larger ones
       to the right." */
    PSORT(rowData, ncol, qq);

    ANS_IN_C(ans)[ii] = rowData[qq];
  }

  UNPROTECT(1);

  return(ans);
}

/* Undo template macros */
#undef PSORT
#include "templates-types_undef.h" 


/***************************************************************************
 HISTORY:
 2013-01-13 [HB]
  o Merged rowOrderStatsReal() and rowOrderStatsInteger() into 
    one rowOrderStats_<Integer|Real>() templated function.
 2009-02-04 [HB]
  o BUG FIX: For some errors in rowOrderStats(), the stack would not become
    UNPROTECTED before calling error.
 2008-03-25 [HB]
  o Renamed from 'rowQuantiles' to 'rowOrderStats'.
 2007-08-10 [HB]
  o Removed arguments for NAs since rowOrderStats() still don't support it.
 2005-11-24 [HB]
  o Cool, it works and compiles nicely.
  o Preallocate colOffset to speed up things even more.
  o Added more comments and error checking.
  o Adopted from rowQ() in Biobase of Bioconductor.
 **************************************************************************/

/***************************************************************************
 Public methods:
 SEXP rowRanks(SEXP x, SEXP tiesMethod)
 SEXP colRanks(SEXP x, SEXP tiesMethod)

 Private methods:
 void rowRanks_Real(double *x, int nrow, int ncol, int byrow, int *ans)
 void rowRanks_Integer(int *x, int nrow, int ncol, int byrow, int *ans)

 To do: Add support for missing values.

 Hector Corrada Bravo
 Henrik Bengtsson (minor)
 **************************************************************************/
#include <R.h>
#include <Rinternals.h>
#include <Rmath.h>

#define METHOD rowRanks
#define X_TYPE 'r'
#include "templates-types.h"

void METHOD_NAME(X_C_TYPE *x, int nrow, int ncol, int byrow, int *ans) {
  int ii, jj;
  int *colOffset;
  int *I;
  int JJ, AA, nna;
  X_C_TYPE *rowData;
  X_C_TYPE current_max;
  X_C_TYPE current_min, tmp;

  rowData = (X_C_TYPE *) R_alloc(ncol, sizeof(X_C_TYPE));
  I = (int *) R_alloc(ncol, sizeof(int));

  colOffset = (int *) R_alloc(ncol, sizeof(int));
  for (jj=0; jj < ncol; jj++) {
    colOffset[jj] = (int) jj*nrow;
  }

  for (ii=0; ii < nrow; ii++) {
    nna = 0;	// number of NA/NaN in this row

    // Set a minimum finite value for this row
    current_min = R_PosInf;
    for (jj=0; jj < ncol; jj++) {
      tmp = x[ii+colOffset[jj]];
      if (R_FINITE(tmp) && tmp < current_min)
	current_min = tmp;
    }
    current_min = R_FINITE(current_min) ? current_min - 1 : 0;

    // Map -Inf to 'current_min' and Na/NaN to -Inf
    for (jj=0; jj < ncol; jj++) {
      tmp = x[ii+colOffset[jj]];
      if (tmp == R_NegInf)
	rowData[jj] = current_min;
      else if (X_ISNAN(tmp)) {
	nna++;
	rowData[jj] = R_NegInf;
      }
      else
	rowData[jj] = tmp;

      I[jj] = jj;
      // Rprintf("%d %d: %.2f ", ii, jj, x[ii+colOffset[jj]]);
    }
    // Rprintf("\n");

    // We have rid 'rowData' of any NA/NaN, so this will sort it
    // increasing with any -Inf's first.
    X_QSORT_I(rowData, I, 1, ncol);

    // The following does: rank(ties.method="max", na.last="keep")

    JJ = ncol-1;
    current_max = rowData[JJ];
    AA = ii + colOffset[I[JJ]];
    ans[AA] = (current_max == R_NegInf) ? NA_INTEGER : JJ+1-nna;
    for (jj=ncol-2; jj>=nna; jj--) {
      AA = ii + colOffset[I[jj]];
      // Rprintf("%d %d %d: %d %.2f %.2f ", ii, jj, AA, I[jj], rowData[jj], current_max);
      if (rowData[jj] != current_max) {
	JJ = jj;
	current_max = rowData[JJ];
      }
      ans[AA] = JJ+1-nna;
    }
    for (jj=nna-1; jj>=0; jj--) {
      AA = ii + colOffset[I[jj]];
      ans[AA] = NA_INTEGER;
    }

    // Rprintf("\n");
  }
}

/* Undo template macros */
#undef METHOD
#include "templates-types_undef.h"

/***************************************************************************
 HISTORY:
 2014-11-06 [HB]
  o CLEANUP: Moving away from R data types in low-level C functions.
  O Harmonized code toward rowRanks_Integer().
 2013-01-13 [HB]
 o Added argument 'tiesMethod' to rowRanks().
 **************************************************************************/

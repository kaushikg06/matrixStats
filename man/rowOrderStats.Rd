%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Do not modify this file since it was automatically generated from:
% 
%  rowOrderStats.R
% 
% by the Rdoc compiler part of the R.oo package.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\name{rowOrderStats}
\alias{rowOrderStats}

\alias{colOrderStats}

\title{Gets an order statistic for each row (column) in a matrix}

\description{
  Gets an order statistic for each row (column) in a matrix.
}

\usage{
 rowOrderStats(x, rows=NULL, cols=NULL, which, dim.=dim(x), ...)
 colOrderStats(x, rows=NULL, cols=NULL, which, dim.=dim(x), ...)
}

\arguments{
 \item{x}{A \code{\link[base]{numeric}} NxK \code{\link[base]{matrix}}.}
 \item{rows, cols}{A \code{\link[base]{vector}} indicating subset of rows (and/or columns)
    to operate over. If \code{\link[base]{NULL}}, no subsetting is done.}
 \item{which}{An \code{\link[base]{integer}} index in [1,K] ([1,N]) indicating which
              order statistic to be returned.}
 \item{dim.}{An \code{\link[base]{integer}} \code{\link[base]{vector}} of length two specifying the
             dimension of \code{x}, also when not a \code{\link[base]{matrix}}.}
 \item{...}{Not used.}
}

\value{
  Returns a \code{\link[base]{numeric}} \code{\link[base]{vector}} of length N (K).
}

\details{
  The implementation of \code{rowOrderStats()} is optimized for both
  speed and memory.
  To avoid coercing to \code{\link[base]{double}}s (and hence memory allocation), there
  is a unique implementation for \code{\link[base]{integer}} matrices.
}

\section{Missing values}{
  This method does \emph{not} handle missing values, that is, the result
  corresponds to having \code{na.rm=FALSE} (if such an argument would
  be available).
}

\author{
  The native implementation of \code{rowOrderStats()} was adopted
  by Henrik Bengtsson from Robert Gentleman's \code{rowQ()}
  in the \pkg{Biobase} package.
}

\seealso{
  See \code{rowMeans()} in \code{\link[base]{colSums}}().
}





\keyword{array}
\keyword{iteration}
\keyword{robust}
\keyword{univar}

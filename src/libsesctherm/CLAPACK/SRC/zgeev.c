#include "blaswrap.h"
#include "f2c.h"

/* Subroutine */ int zgeev_(char *jobvl, char *jobvr, integer *n, 
	doublecomplex *a, integer *lda, doublecomplex *w, doublecomplex *vl, 
	integer *ldvl, doublecomplex *vr, integer *ldvr, doublecomplex *work, 
	integer *lwork, doublereal *rwork, integer *info)
{
/*  -- LAPACK driver routine (version 3.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       June 30, 1999   


    Purpose   
    =======   

    ZGEEV computes for an N-by-N complex nonsymmetric matrix A, the   
    eigenvalues and, optionally, the left and/or right eigenvectors.   

    The right eigenvector v(j) of A satisfies   
                     A * v(j) = lambda(j) * v(j)   
    where lambda(j) is its eigenvalue.   
    The left eigenvector u(j) of A satisfies   
                  u(j)**H * A = lambda(j) * u(j)**H   
    where u(j)**H denotes the conjugate transpose of u(j).   

    The computed eigenvectors are normalized to have Euclidean norm   
    equal to 1 and largest component real.   

    Arguments   
    =========   

    JOBVL   (input) CHARACTER*1   
            = 'N': left eigenvectors of A are not computed;   
            = 'V': left eigenvectors of are computed.   

    JOBVR   (input) CHARACTER*1   
            = 'N': right eigenvectors of A are not computed;   
            = 'V': right eigenvectors of A are computed.   

    N       (input) INTEGER   
            The order of the matrix A. N >= 0.   

    A       (input/output) COMPLEX*16 array, dimension (LDA,N)   
            On entry, the N-by-N matrix A.   
            On exit, A has been overwritten.   

    LDA     (input) INTEGER   
            The leading dimension of the array A.  LDA >= max(1,N).   

    W       (output) COMPLEX*16 array, dimension (N)   
            W contains the computed eigenvalues.   

    VL      (output) COMPLEX*16 array, dimension (LDVL,N)   
            If JOBVL = 'V', the left eigenvectors u(j) are stored one   
            after another in the columns of VL, in the same order   
            as their eigenvalues.   
            If JOBVL = 'N', VL is not referenced.   
            u(j) = VL(:,j), the j-th column of VL.   

    LDVL    (input) INTEGER   
            The leading dimension of the array VL.  LDVL >= 1; if   
            JOBVL = 'V', LDVL >= N.   

    VR      (output) COMPLEX*16 array, dimension (LDVR,N)   
            If JOBVR = 'V', the right eigenvectors v(j) are stored one   
            after another in the columns of VR, in the same order   
            as their eigenvalues.   
            If JOBVR = 'N', VR is not referenced.   
            v(j) = VR(:,j), the j-th column of VR.   

    LDVR    (input) INTEGER   
            The leading dimension of the array VR.  LDVR >= 1; if   
            JOBVR = 'V', LDVR >= N.   

    WORK    (workspace/output) COMPLEX*16 array, dimension (LWORK)   
            On exit, if INFO = 0, WORK(1) returns the optimal LWORK.   

    LWORK   (input) INTEGER   
            The dimension of the array WORK.  LWORK >= max(1,2*N).   
            For good performance, LWORK must generally be larger.   

            If LWORK = -1, then a workspace query is assumed; the routine   
            only calculates the optimal size of the WORK array, returns   
            this value as the first entry of the WORK array, and no error   
            message related to LWORK is issued by XERBLA.   

    RWORK   (workspace) DOUBLE PRECISION array, dimension (2*N)   

    INFO    (output) INTEGER   
            = 0:  successful exit   
            < 0:  if INFO = -i, the i-th argument had an illegal value.   
            > 0:  if INFO = i, the QR algorithm failed to compute all the   
                  eigenvalues, and no eigenvectors have been computed;   
                  elements and i+1:N of W contain eigenvalues which have   
                  converged.   

    =====================================================================   


       Test the input arguments   

       Parameter adjustments */
    /* Table of constant values */
    static integer c__1 = 1;
    static integer c__0 = 0;
    static integer c__8 = 8;
    static integer c_n1 = -1;
    static integer c__4 = 4;
    
    /* System generated locals */
    integer a_dim1, a_offset, vl_dim1, vl_offset, vr_dim1, vr_offset, i__1, 
	    i__2, i__3, i__4;
    doublereal d__1, d__2;
    doublecomplex z__1, z__2;
    /* Builtin functions */
    double sqrt(doublereal), d_imag(doublecomplex *);
    void d_cnjg(doublecomplex *, doublecomplex *);
    /* Local variables */
    static integer ibal;
    static char side[1];
    static integer maxb;
    static doublereal anrm;
    static integer ierr, itau, iwrk, nout, i__, k;
    extern logical lsame_(char *, char *);
    extern /* Subroutine */ int zscal_(integer *, doublecomplex *, 
	    doublecomplex *, integer *), dlabad_(doublereal *, doublereal *);
    extern doublereal dznrm2_(integer *, doublecomplex *, integer *);
    static logical scalea;
    extern doublereal dlamch_(char *);
    static doublereal cscale;
    extern /* Subroutine */ int zgebak_(char *, char *, integer *, integer *, 
	    integer *, doublereal *, integer *, doublecomplex *, integer *, 
	    integer *), zgebal_(char *, integer *, 
	    doublecomplex *, integer *, integer *, integer *, doublereal *, 
	    integer *);
    extern integer idamax_(integer *, doublereal *, integer *);
    extern /* Subroutine */ int xerbla_(char *, integer *);
    extern integer ilaenv_(integer *, char *, char *, integer *, integer *, 
	    integer *, integer *, ftnlen, ftnlen);
    static logical select[1];
    extern /* Subroutine */ int zdscal_(integer *, doublereal *, 
	    doublecomplex *, integer *);
    static doublereal bignum;
    extern doublereal zlange_(char *, integer *, integer *, doublecomplex *, 
	    integer *, doublereal *);
    extern /* Subroutine */ int zgehrd_(integer *, integer *, integer *, 
	    doublecomplex *, integer *, doublecomplex *, doublecomplex *, 
	    integer *, integer *), zlascl_(char *, integer *, integer *, 
	    doublereal *, doublereal *, integer *, integer *, doublecomplex *,
	     integer *, integer *), zlacpy_(char *, integer *, 
	    integer *, doublecomplex *, integer *, doublecomplex *, integer *);
    static integer minwrk, maxwrk;
    static logical wantvl;
    static doublereal smlnum;
    static integer hswork, irwork;
    extern /* Subroutine */ int zhseqr_(char *, char *, integer *, integer *, 
	    integer *, doublecomplex *, integer *, doublecomplex *, 
	    doublecomplex *, integer *, doublecomplex *, integer *, integer *), ztrevc_(char *, char *, logical *, integer *, 
	    doublecomplex *, integer *, doublecomplex *, integer *, 
	    doublecomplex *, integer *, integer *, integer *, doublecomplex *,
	     doublereal *, integer *);
    static logical lquery, wantvr;
    extern /* Subroutine */ int zunghr_(integer *, integer *, integer *, 
	    doublecomplex *, integer *, doublecomplex *, doublecomplex *, 
	    integer *, integer *);
    static integer ihi;
    static doublereal scl;
    static integer ilo;
    static doublereal dum[1], eps;
    static doublecomplex tmp;
#define vl_subscr(a_1,a_2) (a_2)*vl_dim1 + a_1
#define vl_ref(a_1,a_2) vl[vl_subscr(a_1,a_2)]
#define vr_subscr(a_1,a_2) (a_2)*vr_dim1 + a_1
#define vr_ref(a_1,a_2) vr[vr_subscr(a_1,a_2)]


    a_dim1 = *lda;
    a_offset = 1 + a_dim1 * 1;
    a -= a_offset;
    --w;
    vl_dim1 = *ldvl;
    vl_offset = 1 + vl_dim1 * 1;
    vl -= vl_offset;
    vr_dim1 = *ldvr;
    vr_offset = 1 + vr_dim1 * 1;
    vr -= vr_offset;
    --work;
    --rwork;

    /* Function Body */
    *info = 0;
    lquery = *lwork == -1;
    wantvl = lsame_(jobvl, "V");
    wantvr = lsame_(jobvr, "V");
    if (! wantvl && ! lsame_(jobvl, "N")) {
	*info = -1;
    } else if (! wantvr && ! lsame_(jobvr, "N")) {
	*info = -2;
    } else if (*n < 0) {
	*info = -3;
    } else if (*lda < max(1,*n)) {
	*info = -5;
    } else if (*ldvl < 1 || wantvl && *ldvl < *n) {
	*info = -8;
    } else if (*ldvr < 1 || wantvr && *ldvr < *n) {
	*info = -10;
    }

/*     Compute workspace   
        (Note: Comments in the code beginning "Workspace:" describe the   
         minimal amount of workspace needed at that point in the code,   
         as well as the preferred amount for good performance.   
         CWorkspace refers to complex workspace, and RWorkspace to real   
         workspace. NB refers to the optimal block size for the   
         immediately following subroutine, as returned by ILAENV.   
         HSWORK refers to the workspace preferred by ZHSEQR, as   
         calculated below. HSWORK is computed assuming ILO=1 and IHI=N,   
         the worst case.) */

    minwrk = 1;
    if (*info == 0 && (*lwork >= 1 || lquery)) {
	maxwrk = *n + *n * ilaenv_(&c__1, "ZGEHRD", " ", n, &c__1, n, &c__0, (
		ftnlen)6, (ftnlen)1);
	if (! wantvl && ! wantvr) {
/* Computing MAX */
	    i__1 = 1, i__2 = *n << 1;
	    minwrk = max(i__1,i__2);
/* Computing MAX */
	    i__1 = ilaenv_(&c__8, "ZHSEQR", "EN", n, &c__1, n, &c_n1, (ftnlen)
		    6, (ftnlen)2);
	    maxb = max(i__1,2);
/* Computing MIN   
   Computing MAX */
	    i__3 = 2, i__4 = ilaenv_(&c__4, "ZHSEQR", "EN", n, &c__1, n, &
		    c_n1, (ftnlen)6, (ftnlen)2);
	    i__1 = min(maxb,*n), i__2 = max(i__3,i__4);
	    k = min(i__1,i__2);
/* Computing MAX */
	    i__1 = k * (k + 2), i__2 = *n << 1;
	    hswork = max(i__1,i__2);
	    maxwrk = max(maxwrk,hswork);
	} else {
/* Computing MAX */
	    i__1 = 1, i__2 = *n << 1;
	    minwrk = max(i__1,i__2);
/* Computing MAX */
	    i__1 = maxwrk, i__2 = *n + (*n - 1) * ilaenv_(&c__1, "ZUNGHR", 
		    " ", n, &c__1, n, &c_n1, (ftnlen)6, (ftnlen)1);
	    maxwrk = max(i__1,i__2);
/* Computing MAX */
	    i__1 = ilaenv_(&c__8, "ZHSEQR", "SV", n, &c__1, n, &c_n1, (ftnlen)
		    6, (ftnlen)2);
	    maxb = max(i__1,2);
/* Computing MIN   
   Computing MAX */
	    i__3 = 2, i__4 = ilaenv_(&c__4, "ZHSEQR", "SV", n, &c__1, n, &
		    c_n1, (ftnlen)6, (ftnlen)2);
	    i__1 = min(maxb,*n), i__2 = max(i__3,i__4);
	    k = min(i__1,i__2);
/* Computing MAX */
	    i__1 = k * (k + 2), i__2 = *n << 1;
	    hswork = max(i__1,i__2);
/* Computing MAX */
	    i__1 = max(maxwrk,hswork), i__2 = *n << 1;
	    maxwrk = max(i__1,i__2);
	}
	work[1].r = (doublereal) maxwrk, work[1].i = 0.;
    }
    if (*lwork < minwrk && ! lquery) {
	*info = -12;
    }
    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("ZGEEV ", &i__1);
	return 0;
    } else if (lquery) {
	return 0;
    }

/*     Quick return if possible */

    if (*n == 0) {
	return 0;
    }

/*     Get machine constants */

    eps = dlamch_("P");
    smlnum = dlamch_("S");
    bignum = 1. / smlnum;
    dlabad_(&smlnum, &bignum);
    smlnum = sqrt(smlnum) / eps;
    bignum = 1. / smlnum;

/*     Scale A if max element outside range [SMLNUM,BIGNUM] */

    anrm = zlange_("M", n, n, &a[a_offset], lda, dum);
    scalea = FALSE_;
    if (anrm > 0. && anrm < smlnum) {
	scalea = TRUE_;
	cscale = smlnum;
    } else if (anrm > bignum) {
	scalea = TRUE_;
	cscale = bignum;
    }
    if (scalea) {
	zlascl_("G", &c__0, &c__0, &anrm, &cscale, n, n, &a[a_offset], lda, &
		ierr);
    }

/*     Balance the matrix   
       (CWorkspace: none)   
       (RWorkspace: need N) */

    ibal = 1;
    zgebal_("B", n, &a[a_offset], lda, &ilo, &ihi, &rwork[ibal], &ierr);

/*     Reduce to upper Hessenberg form   
       (CWorkspace: need 2*N, prefer N+N*NB)   
       (RWorkspace: none) */

    itau = 1;
    iwrk = itau + *n;
    i__1 = *lwork - iwrk + 1;
    zgehrd_(n, &ilo, &ihi, &a[a_offset], lda, &work[itau], &work[iwrk], &i__1,
	     &ierr);

    if (wantvl) {

/*        Want left eigenvectors   
          Copy Householder vectors to VL */

	*(unsigned char *)side = 'L';
	zlacpy_("L", n, n, &a[a_offset], lda, &vl[vl_offset], ldvl)
		;

/*        Generate unitary matrix in VL   
          (CWorkspace: need 2*N-1, prefer N+(N-1)*NB)   
          (RWorkspace: none) */

	i__1 = *lwork - iwrk + 1;
	zunghr_(n, &ilo, &ihi, &vl[vl_offset], ldvl, &work[itau], &work[iwrk],
		 &i__1, &ierr);

/*        Perform QR iteration, accumulating Schur vectors in VL   
          (CWorkspace: need 1, prefer HSWORK (see comments) )   
          (RWorkspace: none) */

	iwrk = itau;
	i__1 = *lwork - iwrk + 1;
	zhseqr_("S", "V", n, &ilo, &ihi, &a[a_offset], lda, &w[1], &vl[
		vl_offset], ldvl, &work[iwrk], &i__1, info);

	if (wantvr) {

/*           Want left and right eigenvectors   
             Copy Schur vectors to VR */

	    *(unsigned char *)side = 'B';
	    zlacpy_("F", n, n, &vl[vl_offset], ldvl, &vr[vr_offset], ldvr);
	}

    } else if (wantvr) {

/*        Want right eigenvectors   
          Copy Householder vectors to VR */

	*(unsigned char *)side = 'R';
	zlacpy_("L", n, n, &a[a_offset], lda, &vr[vr_offset], ldvr)
		;

/*        Generate unitary matrix in VR   
          (CWorkspace: need 2*N-1, prefer N+(N-1)*NB)   
          (RWorkspace: none) */

	i__1 = *lwork - iwrk + 1;
	zunghr_(n, &ilo, &ihi, &vr[vr_offset], ldvr, &work[itau], &work[iwrk],
		 &i__1, &ierr);

/*        Perform QR iteration, accumulating Schur vectors in VR   
          (CWorkspace: need 1, prefer HSWORK (see comments) )   
          (RWorkspace: none) */

	iwrk = itau;
	i__1 = *lwork - iwrk + 1;
	zhseqr_("S", "V", n, &ilo, &ihi, &a[a_offset], lda, &w[1], &vr[
		vr_offset], ldvr, &work[iwrk], &i__1, info);

    } else {

/*        Compute eigenvalues only   
          (CWorkspace: need 1, prefer HSWORK (see comments) )   
          (RWorkspace: none) */

	iwrk = itau;
	i__1 = *lwork - iwrk + 1;
	zhseqr_("E", "N", n, &ilo, &ihi, &a[a_offset], lda, &w[1], &vr[
		vr_offset], ldvr, &work[iwrk], &i__1, info);
    }

/*     If INFO > 0 from ZHSEQR, then quit */

    if (*info > 0) {
	goto L50;
    }

    if (wantvl || wantvr) {

/*        Compute left and/or right eigenvectors   
          (CWorkspace: need 2*N)   
          (RWorkspace: need 2*N) */

	irwork = ibal + *n;
	ztrevc_(side, "B", select, n, &a[a_offset], lda, &vl[vl_offset], ldvl,
		 &vr[vr_offset], ldvr, n, &nout, &work[iwrk], &rwork[irwork], 
		&ierr);
    }

    if (wantvl) {

/*        Undo balancing of left eigenvectors   
          (CWorkspace: none)   
          (RWorkspace: need N) */

	zgebak_("B", "L", n, &ilo, &ihi, &rwork[ibal], n, &vl[vl_offset], 
		ldvl, &ierr);

/*        Normalize left eigenvectors and make largest component real */

	i__1 = *n;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    scl = 1. / dznrm2_(n, &vl_ref(1, i__), &c__1);
	    zdscal_(n, &scl, &vl_ref(1, i__), &c__1);
	    i__2 = *n;
	    for (k = 1; k <= i__2; ++k) {
		i__3 = vl_subscr(k, i__);
/* Computing 2nd power */
		d__1 = vl[i__3].r;
/* Computing 2nd power */
		d__2 = d_imag(&vl_ref(k, i__));
		rwork[irwork + k - 1] = d__1 * d__1 + d__2 * d__2;
/* L10: */
	    }
	    k = idamax_(n, &rwork[irwork], &c__1);
	    d_cnjg(&z__2, &vl_ref(k, i__));
	    d__1 = sqrt(rwork[irwork + k - 1]);
	    z__1.r = z__2.r / d__1, z__1.i = z__2.i / d__1;
	    tmp.r = z__1.r, tmp.i = z__1.i;
	    zscal_(n, &tmp, &vl_ref(1, i__), &c__1);
	    i__2 = vl_subscr(k, i__);
	    i__3 = vl_subscr(k, i__);
	    d__1 = vl[i__3].r;
	    z__1.r = d__1, z__1.i = 0.;
	    vl[i__2].r = z__1.r, vl[i__2].i = z__1.i;
/* L20: */
	}
    }

    if (wantvr) {

/*        Undo balancing of right eigenvectors   
          (CWorkspace: none)   
          (RWorkspace: need N) */

	zgebak_("B", "R", n, &ilo, &ihi, &rwork[ibal], n, &vr[vr_offset], 
		ldvr, &ierr);

/*        Normalize right eigenvectors and make largest component real */

	i__1 = *n;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    scl = 1. / dznrm2_(n, &vr_ref(1, i__), &c__1);
	    zdscal_(n, &scl, &vr_ref(1, i__), &c__1);
	    i__2 = *n;
	    for (k = 1; k <= i__2; ++k) {
		i__3 = vr_subscr(k, i__);
/* Computing 2nd power */
		d__1 = vr[i__3].r;
/* Computing 2nd power */
		d__2 = d_imag(&vr_ref(k, i__));
		rwork[irwork + k - 1] = d__1 * d__1 + d__2 * d__2;
/* L30: */
	    }
	    k = idamax_(n, &rwork[irwork], &c__1);
	    d_cnjg(&z__2, &vr_ref(k, i__));
	    d__1 = sqrt(rwork[irwork + k - 1]);
	    z__1.r = z__2.r / d__1, z__1.i = z__2.i / d__1;
	    tmp.r = z__1.r, tmp.i = z__1.i;
	    zscal_(n, &tmp, &vr_ref(1, i__), &c__1);
	    i__2 = vr_subscr(k, i__);
	    i__3 = vr_subscr(k, i__);
	    d__1 = vr[i__3].r;
	    z__1.r = d__1, z__1.i = 0.;
	    vr[i__2].r = z__1.r, vr[i__2].i = z__1.i;
/* L40: */
	}
    }

/*     Undo scaling if necessary */

L50:
    if (scalea) {
	i__1 = *n - *info;
/* Computing MAX */
	i__3 = *n - *info;
	i__2 = max(i__3,1);
	zlascl_("G", &c__0, &c__0, &cscale, &anrm, &i__1, &c__1, &w[*info + 1]
		, &i__2, &ierr);
	if (*info > 0) {
	    i__1 = ilo - 1;
	    zlascl_("G", &c__0, &c__0, &cscale, &anrm, &i__1, &c__1, &w[1], n,
		     &ierr);
	}
    }

    work[1].r = (doublereal) maxwrk, work[1].i = 0.;
    return 0;

/*     End of ZGEEV */

} /* zgeev_ */

#undef vr_ref
#undef vr_subscr
#undef vl_ref
#undef vl_subscr



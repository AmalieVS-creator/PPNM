# Eigenvalue Decomposition of a Rank-2 Updated Diagonal Matrix

This project computes the eigenvalues and eigenvectors of a matrix of the form

A = D + e_p u^T + u e_p^T,

where (D) is a diagonal matrix, (u) is a vector, and (e_p) is the (p)-th standard basis vector.

The eigenvalues are obtained by solving the corresponding secular equation. The roots of the secular equation are located using interval bracketing and refined with Newton's method. To improve robustness, several bisection steps are performed before Newton iteration.

For each computed eigenvalue, the corresponding eigenvector is reconstructed analytically and normalized. The implementation also verifies the accuracy of each eigenpair by computing the residual

||A v - λ v||,

which measures how closely the computed eigenvector satisfies the eigenvalue equation.

The project includes:

* Construction of the rank-2 updated matrix.
* Numerical solution of the secular equation.
* Computation of eigenvectors.
* Verification of eigenpair accuracy through residual norms.
* Performance testing and timing experiments for different matrix sizes.

The numerical experiments show the accuracy of the computed eigenpairs and can be used to study the scaling behavior of the algorithm as the matrix dimension increases.

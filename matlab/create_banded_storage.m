function [out] = create_banded_storage(A, dim, ksub, ksup)
  % Create banded storage for square matrix A
  % dim:  dimension of the matrix
  % ksub: number of lower diagonals
  % ksup: number of upper diagonals
		 
  ldba  = 2*ksub+ksup+1;     % leading dimension of banded storage
  out   = zeros(ldba, dim);  % banded storage
  kdiag = ksub + 1 + ksup;   

  for icol = 1:dim
    i1 = max(1, icol-ksup);
    i2 = min(dim, icol+ksub);
    for irow = i1:i2
      irowb = irow - icol + kdiag;
      out(irowb, icol) = A(irow, icol);
    end
  end

end

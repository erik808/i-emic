% READFORT3  - Reads the solution file of the experiment%%  M. den Toom%function [lab icp par xl xlp det sig sol solup soleig] = ...		 readfort3(la,filename,single)  if nargin < 3    single = false; % specify whether solution is single column  end  %  fprintf(1,'Reading solution...\n')  %% - OPEN FILE -  fid      = fopen(filename,'r');  if (fid==-1)    error('We regret to inform you that %s was not found.',filename)  end  %% - READ HEADER -  version = fscanf(fid,'%*s %d',1);  fprintf(1,'-- this is solution output version %d.\n', version)  %% - READ SOLUTION SPECS -  lab     = fscanf(fid,'%d',1);  icp     = fscanf(fid,'%d',1);  npar    = fscanf(fid,'%d',1);  nf      = fscanf(fid,'%d',1);  n       = fscanf(fid,'%d',1);  m       = fscanf(fid,'%d',1);  l       = fscanf(fid,'%d',1);  nun     = fscanf(fid,'%d',1);  ndim    = fscanf(fid,'%d',1);  nskip   = fscanf(fid,'%d',1);  %la = 0; %%== hardcoding la ???  %% - READ PARAMETER VALUES -  par     = fscanf(fid,'%f',npar);  %% - READ SPECIAL POINT CHARS -  xl      = fscanf(fid,'%f',1);  xlp     = fscanf(fid,'%f',1);  det     = fscanf(fid,'%f',1);  %% - READ EIGENVALUES -  sig     = zeros(nf,2);  for j = 1:nf    sig(j,:) = fscanf(fid,'%f',2);  end  %% - READ SOLUTION -  sol     = zeros(nun,n,m,l+la);  solup   = zeros(nun,n,m,l+la);  soleig  = zeros(nun,n,m,l+la,nf);  [st,res] = system(['tail -n 1 ',filename, ' | wc -m']);  if str2num(res) < 30	cols = 1;  else	cols = 2 + nf;  end  for k = 1:l+la    for j = 1:m      for i = 1:n        for XX = 1:nun			          el = fscanf(fid,'%f',cols);          sol(XX,i,j,k)    = el(1);        %solup(XX,i,j,k)  = fscanf(fid,'%f',1);        %for j2 = 1:nf        %    soleig(XX,i,j,k,j2) = fscanf(fid,'%f',1);        %end        end      end    end  end  %% - CLOSE FILE -  fclose(fid);
1;  % prevent octave from thinking it is a function file

function res=divcomp(in1,in2,SC)
 if (SC>1) res=round((in1*SC)/in2);
 else      res=in1/in2;
 end
endfunction

function res=mulcomp(in1, in2,SC)
 if (SC>1) res=round((in1*in2)/SC);
 else      res=(in1*in2);
 end
endfunction

MAXN=100;
m=1
for SC=[1 100 1000];
  for methode=1:2
    seuilsup=1.1*SC;
    seuilinf=0.9*SC;
    y=0;
    for zi=-0.8*SC:0.02*SC:0.8*SC
      x=0;y=y+1
      for zr=-1.4*SC:0.02*SC:1.45*SC
         x=x+1;
         n=0;
         tmp=zr+j*zi;
         do    % (2z^3+1)/(3z^2)
         if (methode==1)
           denum=mulcomp(tmp,tmp,SC);   % z^2
           num=mulcomp(denum,tmp,SC);num=2*num;num=num+SC;% 2*z^3+1
           denum=denum*3;  % 3*z^2
           tmp=divcomp(num,denum,SC);
         else  % 2/3z+1/(3z^2)
           denum=(tmp*2)/3; 
           tmp=mulcomp(tmp,tmp,SC);
           num=SC; tmp=divcomp(num,tmp,SC);
           tmp=tmp/3;
           tmp=tmp+denum;
          end
          n=n+1; 
          until (((abs(tmp)<seuilsup)&&(abs(tmp)>seuilinf))||(n>=MAXN));
          soln(x,y)=n;
          if (n>=MAXN) sol(x,y)=-1;end
          if ((real(tmp)>0) && (n<MAXN)) sol(x,y)=1;end
          if ((real(tmp)<0) && (imag(tmp)>0) && (n<MAXN)) sol(x,y)=2; end
          if ((real(tmp)<0) && (imag(tmp)<0) && (n<MAXN)) sol(x,y)=3; end
          end
    end
  eval(['sol_',num2str(methode),'_',num2str(SC),'=sol;']);
  eval(['soln_',num2str(methode),'_',num2str(SC),'=soln;']);
  subplot(3,2,m);
  imagesc(sol');title(['methode=',num2str(methode),' SCALE=',num2str(SC)])
  m=m+1
  end % scale
end   % methode

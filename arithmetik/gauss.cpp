#define EPSILON 0.0000001
 
bool LGS(double** A, double* b, int m, int n, double* res){
	int bla[n];//Werte von 0..m-1
	memset(bla,-1,n*sizeof(int));
	int x,y,x2,y2;
	for(y=0;y<m;y++){
		for(x=0;(x<n)&&(!A[x][y]);x++);//x ist der erste Eintrag der nicht 0 ist
		if(x==n){
			if(b[y]>EPSILON)return false;
			else continue;
		}
		for(x2=x+1;x2<n;x2++){
			A[x2][y]/=A[x][y];
		}
		b[y]/=A[x][y];
		A[x][y]=1;
		for(y2=0;y2<m;y2++){
			if(!A[x][y2])continue;
			if(y==y2)continue;
			for(x2=0;x2<n;x2++){
				if(x==x2)continue;
				A[x2][y2]-=A[x2][y]*A[x][y2];
			}
			b[y2]-=b[y]*A[x][y2];
			A[x][y2]=0;
		}
		bla[x]=y;
	}
	
	memset(res,0,n*sizeof(double));
	for(x=0;x<n;x++){
		if(bla[x]==-1)continue;
		res[x]=b[bla[x]];
	}
	return true;
}

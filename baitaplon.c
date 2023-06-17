#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define pi 3.1415926535
//kiem tra input
int kiemtra(int n,int dc,int dg,int ld,FILE *output){
	if(n<1 || n>1000 || ld<1 || ld>300){
		fprintf(output,"-1 -1 %d",n);
		return 1;
	}		
}
//CASE: WIND
void wind(int n, int dc, int dg, int ld, int nep_1bc, float nep_1bg, FILE *output)
{
	int bc,bg;
	float nd;
	if(dc<=0 || dg<=0 ){		// TH1 : 1 trong 2 or ca 2 kich thuoc <=0 :
		if(dc<=0 && dg<=0){
			nd=n;
			fprintf(output,"0 0 %.3f",nd);
		}
		else if(dg<=0){
			bg= 0;
			bc= n/nep_1bc;
			if(ld<bc)					//ld k du
				bc= ld;
			nd= n- bc*nep_1bc;
			fprintf(output,"%d %d %.3f",bc,bg,nd);
		}
		else if(dc<=0){
			bc= 0;
			bg= n/nep_1bg;
			if(ld<bg)					//ld k du 				
				bg= ld;
			nd= n- bg*nep_1bg;
			fprintf(output,"%d %d %.3f",bc,bg,nd);
		}
	}
	else if(dc>=dg){			//TH2: DC >= DG:
		bc=	n/nep_1bc;
		bg=	n%nep_1bc /nep_1bg;
		if(bc+bg>ld){					//khong du ld
			if(bc>=ld){
				bc= ld;
				bg= 0;
			}
			else
				bg=ld -bc;
		}								//du ld
		nd= n -bc*nep_1bc -bg*nep_1bg;
		fprintf(output,"%d %d %.3f",bc,bg,nd);
	}
	else{						//TH3: DC < DG:	
		int a[100],b[100],i=1,count=1;  //a[]= bc ;b[]= bg ;c[]= nd
		float c[100];
		bg=	n/nep_1bg;
		bc=	(n -bg*nep_1bg)/nep_1bc;
		c[0]= n- bc*nep_1bc -bg*nep_1bg;							
		while(bg!=0){					//tim nd it nhat,luu cac gia tri nd co' the co' vao mang?
			bg-=1;
			bc= (n -bg*nep_1bg) /nep_1bc;
			b[i]= bg;
			a[i]=(n -bg*nep_1bg) /nep_1bc;
			c[i]= n- bc*nep_1bc -bg*nep_1bg;
			i+=1;
			count+=1;
		}
		float nd=1001;
		int temp; 
		for(i=0 ;i<count ;i++){			//tim gtnn cua mang? nd
			if(c[i]<nd){
				nd=c[i];
				temp=i;
			}
		}
		if(a[temp]+b[temp]>ld){			//NEU THIEU LD (K CAN LAM BUOC TREN): cu tinh het bg => toi bc => can bang theo ld.
			bg=	n/nep_1bg;
			bc=	(n -bg*nep_1bg)/nep_1bc;
			nd= n- bc*nep_1bc -bg*nep_1bg;
			if(bg+bc>ld){
				if(bg>ld){
					bg=ld;
					bc=0;
				}
				else
					bc=ld-bg;
				nd= n- bc*nep_1bc -bg*nep_1bg;
				fprintf(output,"%d %d %.3f",bc,bg,nd);
			}
			else
				fprintf(output,"%d %d %.3f",bc,bg,nd);
		}
		else
			fprintf(output,"%d %d %.3f",a[temp],b[temp],nd);
	}	
}
//CASE: RAIN
void rain(int n,int dc,int dg,int ld,int nep_1bc,float nep_1bg,FILE *output)
{
	int bc,bg;
	float nd;
	bc = n/nep_1bc;
	bg = n%nep_1bc / nep_1bg;
	// TH1 : 1 trong 2 or ca 2 kich thuoc <=0 
	if((dc<=0 && dg<=0) || (bc==0 && bg==0)){
		nd=n;
		fprintf(output,"0 0 %.3f",nd);
	}
	else if(dg<=0 ){
		bg= 0;
		bc= n/nep_1bc;
		//ld k du
		if(ld<bc)
			bc= ld;
		nd= n- bc*nep_1bc;
		fprintf(output,"%d %d %.3f",bc,bg,nd);
	}
	else if(dc<=0 || bc==0){
		bc= 0;
		bg= n/nep_1bg;
		//ld k du
		if(ld<bg) 
			bg= ld;
		nd= n- bg*nep_1bg;
		fprintf(output,"%d %d %.3f",bc,bg,nd);
	}
	else{
		while(bg!=bc){			//can bang so bc va bg
			if(bc>bg){
				bc-= 1;
				bg = (n-bc*nep_1bc) /nep_1bg;
				if (bg>bc)
					bg = bc;
			}else{
				bg-= 1;
				bc = (n-bg*nep_1bg) /nep_1bc;
				if (bc>bg)
					bc = bg;
			}
		}						// xet nd co the lam them dc banh nao k? va toi uu nd
		nd= n -bc*nep_1bc -bg*nep_1bg;
		float nd1= nd -(int)(nd/nep_1bc) *nep_1bc;	// nd con lai chia cho bc
		float nd2= nd -(int)(nd/nep_1bg) *nep_1bg;	// nd con lai chia cho bg
		if(nd1 < nd2){			// so sanh tim ra so du it nhat
			bc= bc +nd/nep_1bc;
			nd= nd1;
		}else if(nd2 < nd1){
			bg= bg +nd/nep_1bg;
			nd= nd2;
		}
		if(bc+bg > ld){			// TH la dong khong du
			if(nep_1bc > nep_1bg){			//tim kich thuoc banh nho hon de bo? bot' 
				if(bc>=ld){
					bc=ld;
					bg=0;
				}else
					bg=ld-bc;
			}else{
				if(bg>=ld){
					bg=ld;
					bc=0;
				}else
					bc=ld-bg;
			}
			nd= n- bc*nep_1bc -bg*nep_1bg;
		}
		fprintf(output,"%d %d %.3f",bc,bg,nd);
	}
}
//CASE: FOG
void fog(float n,int dc, int dg,FILE *output)
{
	fprintf(output,"%d %d %.3f",dc,dg,n);
}
//CASE: CLOUD
void cloud(int n, int dc, int dg, int ld, int nep_1bc, float nep_1bg, FILE *output)
{
	int bc,bg;
	float nd;
	if((n==220 && ld==284) || (n==284 && ld==220)){
		nd=n;
		fprintf(output,"0 0 %.3f",nd);
	}
	else{
		if(dc<=0 || dg<=0 ){		// TH1 : 1 trong 2 or ca 2 kich thuoc <=0 :
			if(dc<=0 && dg<=0){
				nd=n;
				fprintf(output,"0 0 %.3f",nd);
		}
			else if(dg<=0){
				bg= 0;
				bc= n/nep_1bc;
				if(ld<bc)					//ld k du
					bc= ld;
				nd= n- bc*nep_1bc;
				fprintf(output,"%d %d %.3f",bc,bg,nd);
			}
			else if(dc<=0){
				bc= 0;
				bg= n/nep_1bg;
				if(ld<bg)					//ld k du 				
					bg= ld;
				nd= n- bg*nep_1bg;
				fprintf(output,"%d %d %.3f",bc,bg,nd);
			}
		}
		else if(dg>=dc){			//TH2: DC >= DG:
			bg=	n/nep_1bg;
			bc=	(n-bg*nep_1bg) /nep_1bc;
			if(bc+bg>ld){					//khong du ld
				if(bg>=ld){
					bg= ld;
					bc= 0;
				}
				else
					bc=ld -bg;
			}								//du ld
			nd= n -bc*nep_1bc -bg*nep_1bg;
			fprintf(output,"%d %d %.3f",bc,bg,nd);
		}
		else{						//TH3: DC < DG:	
			int a[100],b[100],i=1,count=1;  //a[]= bc ;b[]= bg ;c[]= nd
			float c[100];
			bc=	n/nep_1bc;
			bg=	(n -bc*nep_1bc)/nep_1bg;
			c[0]=n- bc*nep_1bc -bg*nep_1bg;						
			while(bc!=0){					//tim nd it nhat,luu cac gia tri nd co' the co' vao mang?
				bc-=1;
				bg= (n -bc*nep_1bc) /nep_1bg;
				b[i]= bc;
				a[i]=(n -bc*nep_1bc) /nep_1bg;
				c[i]= n- bc*nep_1bc -bg*nep_1bg;
				i+=1;
				count+=1;
			}
			float nd=1001;
			int temp; 
			for(i=0 ;i<count ;i++){			//tim gtnn cua mang? nd
				if(c[i]<nd){
					nd=c[i];
					temp=i;
				}
			}
			if(a[temp]+b[temp]>ld){			//NEU THIEU LD (K CAN LAM BUOC TREN): cu tinh het bg => toi bc => can bang theo ld.
				bc=	n/nep_1bc;
				bg=	(n -bc*nep_1bc)/nep_1bg;
				nd= n- bc*nep_1bc -bg*nep_1bg;
				if(bg+bc>ld){
					if(bc>ld){
						bc=ld;
						bg=0;
					}
					else
						bg=ld-bc;
					nd= n- bc*nep_1bc -bg*nep_1bg;
					fprintf(output,"%d %d %.3f",bc,bg,nd);
				}
				else
					fprintf(output,"%d %d %.3f",bc,bg,nd);
			}
			else
				fprintf(output,"%d %d %.3f",a[temp],b[temp],nd);
			}	
		}
}
//CASE: SUN	
void sun(int n, int dc, int dg, int ld,int nep_1bc, float nep_1bg, FILE *output)
{
	int a[5][6]={
	{5,7,10,12,15,20},
	{20,5,7,10,12,15},
	{15,20,5,7,10,12},
	{12,15,20,5,7,10},
	{10,12,15,20,5,7}
	};
	int G,H,i,k;
	float x;
	if(dc<0)
		dc=0;
	if(dg<0)
		dg=0;
	G= dc%6;
	H= ld%5;
	x=a[H][G];
	n=n+n*(x/100);
	ld=ld-x;
	if(kiemtra(n,dc,dg,ld,output)==1)
		goto end;
	if((dc+dg)%3==0)
		rain(n,dc,dg,ld,nep_1bc,nep_1bg,output);
	else if((dc+dg)%3==1)
		wind(n,dc,dg,ld,nep_1bc,nep_1bg,output);
	else if((dc+dg)%3==2)
		cloud(n,dc,dg,ld,nep_1bc,nep_1bg,output);
	end:;
}
int main(){
	FILE *input, *output;
	int n,dc,dg,ld,nep_1bc;
	char w[10];
	float nep_1bg;
	input= fopen("input.inp","r");
	fscanf(input,"%d %d %d %d %s",&n,&dc,&dg,&ld,&w);
	fclose(input);
	output= fopen("output.out","w");
	if(kiemtra(n,dc,dg,ld,output)==1)
		goto thoat;	
	nep_1bc= pow(dc,2);
	nep_1bg= (pow(dg,2)*pi)/4;
	if(strcmp(w, "Wind")==0)
		wind(n,dc,dg,ld,nep_1bc,nep_1bg,output);
	else if(strcmp(w, "Rain")==0)
		rain(n,dc,dg,ld,nep_1bc,nep_1bg,output);
	else if(strcmp(w, "Sun")==0)
		sun(n,dc,dg,ld,nep_1bc,nep_1bg,output);
	else if(strcmp(w, "Cloud")==0)
		cloud(n,dc,dg,ld,nep_1bc,nep_1bg,output);
	else if(strcmp(w, "Fog")==0) 
		fog(n, dc, dg,output);
	thoat:
		fclose(output);
		return 0;
}

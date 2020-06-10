#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "src/bt-5.0.0/inc/btree.h"


int main()
{
	int x,i,j,n,size,mem,sai=0;
	char bname[30],word[40],nghia[5000],phimcach[2],nghia1[400],*p1,*p2;
	BTA* book;
	btinit();	
	do{
		
		printf("nhan 0 de tao hoac truy cap tu dien \n");
		printf("nhan 1 de them vao tu dien\n");
		printf("nhan 2 de tim kiem tu \n");
		printf("nhan 3 de chinh sua nghia \n");
		printf("nhan 4 de xem toan bo\n");
		printf("nhan 5 de thoat tu dien hien tai\n");
		printf("nhan 6 de xoa tu dien\n");
		scanf("%d",&x);
		if(x==0){
			printf("nhap ten sach \n");
			scanf("%*c");scanf("%[^\n]",bname);
			book=btopn(bname,0,0);
			if(!book)
			{
				printf("khoi tao sach thanh cong\n");
				book=btcrt(bname,0,0);
			}
		}
		if(x==1){
				printf("them vao\n");
				FILE *f;
				f=fopen("AnhViet.txt","rt");
  				while(1)
    			{
        		fscanf(f,"%s ",word);
       			if(feof(f)) break;
        		mem=strlen(word)+1;
        		p1=(char *) malloc(mem*sizeof(char));
       			strcpy(p1,word);
        		while(1)
        		{
            		if(fgetc(f)=='@')
            		{
            		    fseek(f,-1,SEEK_CUR);
                		break;
            		}
            	else fseek(f,-1,SEEK_CUR);
            	fscanf(f,"%s ",word);
            	mem+=strlen(word)+1;
            	p1=(char *) realloc(p1,mem*sizeof(char));
            	strcat(p1," ");
            	strcat(p1,word);
        		}
        		fgets(nghia,5000,f);
        		i=0;
        		while(1)
        		{	
        			if(i>1 && nghia[i-1] == '\\' && nghia[i]=='n')
					{
        				nghia[i-1]='\n';
        				j=i;
        				while(nghia[j]!='\0')
        				{
        					nghia[j]=nghia[j+1];
        					j++;
        				}
        			}
        			if(nghia[i]=='\0')
        				break;
        			i++;
        		}
        		p2=(char *) malloc((strlen(nghia)+1)*sizeof(char));
        		strcpy(p2,nghia);
        		printf("%s %s\n",p1,nghia);
        		if(btins(book,p1,p2,strlen(nghia)+1)) 
					{
					printf("error\n");
					//break;
					}
    			}
			fclose(f);
			//printf("%d\n",sai );
			printf("da cap nhat diem\n");
		}
		
		//btdel(BTA* btact, char* key); xoa key va data
		if(x==2)
		{
			printf("nhap ten tim kiem: \n");
			scanf("%*c");scanf("%[^\n]",word);
			if(btsel(book,word,nghia,300,&size))
				printf("ko tim thay tu\n");
			else
				printf("nghia cua tu %s\n%s \n",word,nghia );
		}
		if(x==3)
		{
			printf("nhap ten de sua: \n");
			scanf("%*c");scanf("%[^\n]",word);
			if(btsel(book,word,nghia,300,&size))
				printf("ko tim thay tu\n");
			else
			{
				printf("cap nhat nghia\n");
				scanf("%*c");scanf("%[^\n]",nghia);
				btupd(book,word,nghia,sizeof(char));
			}
		}
		if(x==4)
		{
			btsel(book,"",nghia,sizeof(char*),&size);
			while(btseln(book,word,nghia1,5000,&size)==0)
			{
				printf("%s \n%s\n",word,nghia1);
			}
		}
		if(x==5)
		{
			btcls(book);
		}
		if (x==6)
		{
			printf("nhap tu\n");
			scanf("%*c");scanf("%[^\n]",word);
			btdel(book, word);// xoa key va data
		}
		if (x==8)
		{
			btsel(book,"",nghia,300,&size);
			while(btseln(book,word,nghia,300,&size)==0)
			{
				btdel(book, word);
			}
		}
	}while(x!=7);
}

#include <stdio.h>
#include <string.h>
#include <math.h>
#define MAXNUM 100
#define MAXCHAR 1000
char reset(char a[])
{
	int i=0,j;
	while(a[i]!='\0')
	{
		i++;
	}
	for(j=0;j<i;j++)
	{
		a[j]='\0';
	}
}
int main()
{
	FILE *ptr,*ptr2;
	char valueschar[MAXCHAR];	
	double valuesnum[MAXNUM];	/*Dosyadan al�nan say�lar� bar�nd�r�r */
	char polynomial[MAXCHAR];	/* Dosyadan al�nan polinomu bar�nd�r�r */
	int m=0;
	if ((ptr = fopen("input.txt", "r")) == NULL)
    {
        printf("Error! opening file");
        // Program exits if file pointer returns NULL.
        exit(1);         
    }
    fscanf(ptr,"%[^\n]", polynomial);
    printf("Data from the file:\n%s", polynomial);
    fclose(ptr);
	printf("************POLYNOM************\n");
	printf("\n%s\n",polynomial);
	ptr2=fopen("values.txt","r");
	printf("\n************VALUES************\n");
	while(!feof(ptr2))
	{
		fscanf(ptr2,"%s",valueschar);		/* dosyadan say�lar char cinsinden al�n�r ve double array olan valuesnum'a atan�r */
		sscanf(valueschar,"%lf",&valuesnum[m]);
		printf("%lf\n",valuesnum[m]);
		m++;		/*values.txt dosyas�ndan okunan say�lar�n ka� tane oldu�unu haf�zada tutar*/ 
	}
	double d1,d2,temp,temp2,totalResult;
	double results[MAXNUM]; /*Polinoma atanan de�er �st�nden yap�lan i�lemler do�rultusunda elde edilen sonu�lar� bar�nd�r�r...*/
	int i,j,k,n,memory=0;
	char temp_value[MAXNUM];	/*temp_value array i okunan de�erleri say�ya sscanf yard�m�yla d�n��t�rmek i�in kullan�lacakt�r */
	
	ptr=fopen("evaluations.txt","w");
	for(n=0; n<m;n++)
	{
		totalResult=0;
		for(i=0;i<memory;i++)
		{
			results[i]=0;
		}
		i=0;
		printf("\n\n****************CALCULATE*********************\n\n");
		printf("<Value> : %lf\n",valuesnum[n]);
		while(polynomial[i]!='\0') /*D�ng�de char tipinde array'de har bir karakter tek tek taran�r ve ko�ullara g�re gerekli i�lemler yap�l�r...*/
		{
			if(polynomial[i]>='0' && polynomial[i]<='9')
			{
				if(polynomial[i+1]=='x')
				{
					temp_value[0]=polynomial[i];
					sscanf(temp_value,"%lf",&temp);
					reset(temp_value);
					if(polynomial[i+2]=='+' || polynomial[i+2]=='-' ) /*�rne�in 5x+... ise bu ko�ula girer... */
					{		
					
						results[memory]=(temp*valuesnum[n]);
						if(polynomial[i-1]=='-') results[memory]=results[memory]*(-1); /*E�er en ba��nda bulunan karakter '-' yi ifade ediyorsa sonu� -1 ile �arp�l�r... */
						i=i+2;
						printf("\nResult : %lf\n",results[memory]);	
						memory++;	
					}
					else if(polynomial[i+2]=='^')	 /*�rne�in 5x^3+... ise bu ko�ula girer */
					{
						k=0;
						while((polynomial[i+3]>='0' && polynomial[i+3]<='9'))
						{
							temp_value[k]=polynomial[i+3];
							i++;
							k++;
						}
						sscanf(temp_value,"%lf",&temp2);
						results[memory]=temp*(pow(valuesnum[n],temp2));
						if(polynomial[i-k-1]=='-') results[memory]=results[memory]*(-1); /*E�er en ba��nda bulunan karakter '-' yi ifade ediyorsa sonu� -1 ile �arp�l�r... */
						printf("\nResult : %lf\n",results[memory]);
						i=i+3;
						reset(temp_value);
						memory++;	
							
					}
					else if(polynomial[i+2]=='\0')	/* Array bitti�inde hata olu�mas�n� engellemek i�in kontrol edilir... */
					{
						results[memory]=(temp*valuesnum[n]);
						if(polynomial[i-1]=='-') results[memory]=results[memory]*(-1);
						i=i+2;
						printf("\nResult : %lf\n",results[memory]);	
						memory++;
						printf("%d",i);
					}
					else if(polynomial[i+2]==' '){
						i++;
						continue;
					}
				}
				else /*Burada say�dan sonraki karakter tekrar bir say�y� ifade ediyorsa say� olmayana kadar tamp_value'ya atamaya devam edicek...*/
				{		/*�rne�in 23.5x*/
					reset(temp_value);
					k=0;
					
					while(((polynomial[i]>='0' && polynomial[i]<='9') || polynomial[i]=='.' ))
					{
						temp_value[k]=polynomial[i];
						i++;
						k++;
					}
					sscanf(temp_value,"%lf",&temp);
					if(polynomial[i-k-1]=='-') temp=temp*(-1);
					if(polynomial[i]=='x') /*Say�dan sonraki karaktere bak�l�r...*/
					{						/*�rne�in 23.5x*/
						
						if(polynomial[i+1]=='+' || polynomial[i+1]=='-' || polynomial[i+1]=='.' || polynomial[i+1]=='\0' )
						{		
		
							results[memory]=(temp*valuesnum[n]);
							printf("\nResult : %lf\n",results[memory]);	
							memory++;
							i=i+1;			
						}
						else if(polynomial[i+1]=='^')
						{
							k=0;
							reset(temp_value);
							while(((polynomial[i+2]>='0' && polynomial[i+2]<='9') || polynomial[i+2]=='.' ) && polynomial[i+3]!='\0')
							{
								temp_value[k]=polynomial[i+2];
								i++;
								k++;
							}
							sscanf(temp_value,"%lf",&temp2);
							results[memory]=temp*(pow(valuesnum[n],temp2));
							printf("\nResult : %lf\n",results[memory]);
							i=i+2;
							reset(temp_value);
							memory++;		
						}
						else if(polynomial[i+1]==' '){
						i++;
						continue;
						}	
					}
					else if(polynomial[i]=='\0' || polynomial[i]=='+' || polynomial[i]=='-' )
					{
						results[memory]=temp;			
						reset(temp_value);	
						printf("Result : %lf\n",results[memory]);
						memory++;
					}
				}
				i--;
			}
			
			
			else if(polynomial[i]=='x') /* E�er yeni toplama i�lemi say� ile de�ilde X ile ba�l�yor ise...*/
			{	
				if(polynomial[i+1]=='^')
				{
					
						k=0;
						while((polynomial[i+2]>='0' && polynomial[i+2]<='9') || polynomial[i]=='.' )
						{
							temp_value[k]=polynomial[i+2];
							i++;
							k++;
						}
						sscanf(temp_value,"%lf",&temp2);
						results[memory]=pow(valuesnum[n],temp2);
						if(polynomial[i-k-1]=='-') results[memory]=results[memory]*(-1);
						printf("\nResult : %lf\n",results[memory]);
						i=i+2;
						reset(temp_value);
						memory++;		
				}
				else if(polynomial[i+1]=='+' || polynomial[i+1]=='-')
				{
					results[memory]=d1;
					printf("Result : %lf\n",results[memory]);
					memory++;
					
				}
				else if(polynomial[i+1]==' '){
						i++;
						continue;
					}
				
			}
			else if(polynomial[i]=='+' || polynomial[i]=='-') /*Hata ��kmamas� i�in + yada - ye rastlad���nda bir sonraki karaktere bakmak i�in i parametresi artt�r�l�r...*/
			{
				printf("\nCALCULATING NEXT RESULT... \n ");
			}
			else if(polynomial[i]==' ')
			{
				
			}
			i++;
		}
		for(i=0;i<memory;i++)
		{
			totalResult=totalResult+results[i];	/* Elde edilen t�m say�lar teker teker toplan�r ve totalResult'a atan�r*/
		}
		printf("\n\nREAL RESULT: %lf",totalResult);
		fprintf(ptr,"%.2lf\n",totalResult);
	}
}
	


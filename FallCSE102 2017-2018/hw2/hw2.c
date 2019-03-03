#include <stdio.h>
#include <string.h>

/* KOD KARIÞIK OLABÝLÝR FONKSÝYONLARLA YAPILMASI DAHA ELVERÝÞLÝ OLUR ANCAK YAPAMADIM */

int main()
{
	double averegeresults1,averegeresults2,averegeresults3,temp;
	double tempnumber;
	double numbers[1000];
	double chunk1[1000];
	double chunk2[1000];
	double chunk3[1000];
	int i,j,counttemp,k;
	double a;
	a=0;
	FILE *ptr;
	FILE *ptr2;
	ptr=fopen("input.txt","r");
	i=0;
	
	fscanf(ptr,"%lf",&numbers[i]); /* Her sayýyý dosyadan okur ve numbers stringine atar */
	i++;
	while(!feof (ptr))
	{
		fscanf(ptr,"%lf",&numbers[i]);
		if(numbers[i]==0) break;		/* string te 0.0 ' a denk gelene kadar tara ve i parametresini birer birer arttýr */
		i++;
	}
	counttemp=i; /*CHUNK1 */
	for(i=0;i<counttemp;i++)
	{
		chunk1[i]=numbers[i];
		printf("Chunk1 Number : %lf\n",chunk1[i]); 	/* ilk elde edilen sayýlarý chunk1 stringine ata */
	}
	i=0;
	while(numbers[i]!=0)
	{
		numbers[i]=0;	/*		numbers stringini 0.0 olmayana kadar i parametresini birer birer arttýr		*/	
		i++;			/*		Bu iþlem bir sonraki chunk a sayý atamamýz için yardýmcý olacaktýr		*/
	}
	i=0;
	while(!feof (ptr))
	{
		fscanf(ptr,"%lf",&numbers[i]);
		
		if(numbers[i]!=0)
		{
			tempnumber=numbers[i];		/*Az önce ki iþlem sayesinde 0 dýþýnda bir sayýya kadar i yi bir arttýrýp dosyayý i sayýsýna ulaþana kadar */
			break;						/* ötelememizi saðladý. Ek olarak öteleme sýrasýnda son ötelediðimiz sayý 0.0 dan farklý bir sayý olacaðýndan dolayý */
		}															/* bu sayýyý ekstradan tempnumber da tutmamýz gerekli */
		i++;
	}
	
	i=0;
	while(numbers[i]!=0)
	{
		numbers[i]=0;
		i++;									/* Bir sonraki chunk için numbers stringi boþaltýlýr */
	}
	i=0;
	while(!feof (ptr))
	{
		fscanf(ptr,"%lf",&numbers[i]);
		if(numbers[i]==0) break;				/* Chunk1 iþleminde yapýlanlar ile aynýdýr */
		i++;
	}
	
	counttemp=i; /*CHUNK2 */

	chunk2[0]=tempnumber;
	printf("\n");
	for(i=0;i<counttemp;i++)
	{
		chunk2[i+1]=numbers[i];
		printf("Chunk2 Number : %lf\n",chunk2[i]);				/* Chunk1 iþleminde yapýlanlar ile aynýdýr */
	}
	
	i=0;
	while(numbers[i]!=0)
	{
		numbers[i]=0;				/* Chunk1 iþleminde yapýlanlar ile aynýdýr */
		i++;
	}
	i=0;
	
	while(!feof(ptr))
	{
		fscanf(ptr,"%lf",&numbers[i]);
		if(numbers[i]!=0)
		{
			tempnumber=numbers[i];				/* Chunk1 iþleminde yapýlanlar ile aynýdýr */
			break;
		}
		i++;
	}
	i=0;
	
	while(numbers[i]!=0)
	{
		numbers[i]=0;
		i++;				/* Chunk1 iþleminde yapýlanlar ile aynýdýr */
	}
	i=0;
	while(!feof (ptr))
	{
		fscanf(ptr,"%lf",&numbers[i]);
		if(numbers[i]==0) break;				/* Chunk1 iþleminde yapýlanlar ile aynýdýr */
		i++;
	}
	
	counttemp=i; /*CHUNK3 */
	chunk3[0]=tempnumber;
	printf("\n");
	for(i=0;i<=counttemp;i++)
	{									
		chunk3[i+1]=numbers[i];						/* Chunk1 iþleminde yapýlanlar ile aynýdýr */
		printf("Chunk3 Number : %lf\n",chunk3[i]);				
	}
	
	
	/* ORTALAMA HESAPLAMA */
	/*CHUNK1*/
	averegeresults1=0;
	i=0;
	k=0;
	while(chunk1[i]!=0) i++;				/* i parametresi chunklarýn içinde kaç tane sayý bulunduðunu gösterir... */
	for(j=0;j<=i;j++)
	{
		averegeresults1 = averegeresults1 + chunk1[j];
	}
	averegeresults1=averegeresults1/i;
	printf("\nCHUNK1 ORTALAMA : %lf\n",averegeresults1);
	/*CHUNK2*/
	
	averegeresults2=0;
	i=0;
	k=0;
	while(chunk2[i]!=0) i++;
	for(j=0;j<=i;j++)
	{
		averegeresults2 = averegeresults2 + chunk2[j];
	}
	averegeresults2=averegeresults2/i;
	printf("\nCHUNK2 ORTALAMA : %lf\n",averegeresults2);
	/*CHUNK3*/
	averegeresults3=0;
	
	i=0;
	k=0;
	while(chunk3[i]!=0) i++;
	for(j=0;j<=i;j++)
	{
		averegeresults3 = averegeresults3 + chunk3[j];
	}
	averegeresults3=averegeresults3/i;
	printf("\nCHUNK3 ORTALAMA : %lf\n",averegeresults3);
	

	/*KARÞILAÞTIRMA VE EKRANA YAZMA*/
	ptr2=fopen("output.txt","w");

	if(averegeresults1<averegeresults2)							
	{
		if(averegeresults2<averegeresults3)												/*															*/
		{	
			i=0;																		/*															*/
			while(chunk1[i]!=0) i++;													/*															*/
			for(j=0;j<i;j++) fprintf(ptr2,"%lf ",chunk1[j]);							/*															*/
			fprintf(ptr2,"\n");												          /* 	TÜM OLASILIKLAR KOÞULLARLA KARÞILAÞTIRILIR			 */
																					  /*		VE HER CHUNK ORTALAMA SIRASINA GÖRE DOSYAYA BASILIR	...*/
			i=0;
			while(chunk2[i]!=0) i++;													/*															*/
			for(j=0;j<i;j++) fprintf(ptr2,"%lf ",chunk2[j]);					 		/*															*/
			fprintf(ptr2,"\n");
			
			i=0;
			while(chunk3[i]!=0) i++;
			for(j=0;j<i;j++) fprintf(ptr2,"%lf ",chunk3[j]);
			fprintf(ptr2,"\n");
		}
		else
		{
			if(averegeresults3<averegeresults1)
			{
				i=0;
			while(chunk3[i]!=0) i++;
			for(j=0;j<i;j++) fprintf(ptr2,"%lf ",chunk3[j]);
			fprintf(ptr2,"\n");
			
			i=0;
			while(chunk1[i]!=0) i++;
			for(j=0;j<i;j++) fprintf(ptr2,"%lf ",chunk1[j]);
			fprintf(ptr2,"\n");
			
			i=0;
			while(chunk2[i]!=0) i++;
			for(j=0;j<i;j++) fprintf(ptr2,"%lf ",chunk2[j]);
			fprintf(ptr2,"\n");
			}
			else
			{
				
				i=0;
				while(chunk1[i]!=0) i++;
				for(j=0;j<i;j++) fprintf(ptr2,"%lf ",chunk1[j]);
				fprintf(ptr2,"\n");
			
				i=0;
				while(chunk3[i]!=0) i++;
				for(j=0;j<i;j++) fprintf(ptr2,"%lf ",chunk3[j]);
				fprintf(ptr2,"\n");
			
				i=0;
				while(chunk2[i]!=0) i++;
				for(j=0;j<i;j++) fprintf(ptr2,"%lf ",chunk2[j]);
				fprintf(ptr2,"\n");
				
				
		}
			
		}	
	}
	
 else
	{
		if(averegeresults1<averegeresults3)
		{	
			i=0;
			while(chunk2[i]!=0) i++;
			for(j=0;j<i;j++) fprintf(ptr2,"%lf ",chunk2[j]);
			fprintf(ptr2,"\n");
			
			i=0;
			while(chunk1[i]!=0) i++;
			for(j=0;j<i;j++) fprintf(ptr2,"%lf ",chunk1[j]);
			fprintf(ptr2,"\n");
			
			i=0;
			while(chunk3[i]!=0) i++;
			for(j=0;j<i;j++) fprintf(ptr2,"%lf ",chunk3[j]);
			fprintf(ptr2,"\n");
		}
		else
		{
			if(averegeresults2<averegeresults3)
			{
					i=0;
				while(chunk2[i]!=0) i++;
				for(j=0;j<i;j++) fprintf(ptr2,"%lf ",chunk2[j]);
				fprintf(ptr2,"\n");
			
				i=0;
				while(chunk3[i]!=0) i++;
				for(j=0;j<i;j++) fprintf(ptr2,"%lf ",chunk3[j]);
				fprintf(ptr2,"\n");
			
				i=0;
				while(chunk1[i]!=0) i++;
				for(j=0;j<i;j++) fprintf(ptr2,"%lf ",chunk1[j]);
				fprintf(ptr2,"\n");
			}
			else
			{
					i=0;
				while(chunk3[i]!=0) i++;
				for(j=0;j<i;j++) fprintf(ptr2,"%lf ",chunk3[j]);
				fprintf(ptr2,"\n");
			
				i=0;
				while(chunk2[i]!=0) i++;
				for(j=0;j<i;j++) fprintf(ptr2,"%lf ",chunk2[j]);
				fprintf(ptr2,"\n");
			
				i=0;
				while(chunk1[i]!=0) i++;
				for(j=0;j<i;j++) fprintf(ptr2,"%lf ",chunk1[j]);
				fprintf(ptr2,"\n");
			}
		
		}
	}

}

#include <stdio.h>
#include <string.h>
#define MAXLEN 250
#define MAXROW 100
int main()
{
	FILE *ptr;
	ptr=fopen("input.txt","r");
	char table[MAXROW][MAXLEN];
	char newword[MAXLEN];
	char words[5][MAXLEN]={"Xanthos","Patara","Myra","Arycanda","Phaselis"};
	int i,j,k,l,m,n,Correctword;
	i=0;
	while(!feof(ptr))
	{
		fscanf(ptr,"%s",&newword);
		strcpy(table[i],newword);
		i++;
	}

	for(i=0;i<MAXROW;i++)
	{
		for(j=0; j<MAXLEN; j++)
		{
			k=0;
			while(k<5)
			{
				if(table[i][j]==words[k][0]) /*if the first character of the chosen word it will scan other characters of word */
				{
					/*VERTICAL*/
					Correctword=1;
					for(m=1; m<strlen(words[k]); m++)
					{
						if(table[i][j+m]==words[k][m]) Correctword++; /*add 1 point to Correctword when character is equal to the searching word's character */
						else break;
					}
					if(Correctword==strlen(words[k])) 
					{
						printf("%s -> (%d,%d) --> Vertical\n",words[k],(i+1),(j+1));
					}
				}
				k++;
			}
		}
	}
	/*HORIZONTAL*/
	for(i=0; i<MAXLEN;i++)
	{
		for(j=0; j<MAXROW;j++)
		{
			k=0;
			while(k<5)
			{
				if(table[j][i]==words[k][0]) /*Now in this loop, firstly, we will increase Rows and scan the words like the vertical searching */
				{					
					Correctword=1;
					for(m=1; strlen(words[k]); m++)
					{
						if(table[j+m][i]==words[k][m]) Correctword++;
						else break;
					}
					if(Correctword==strlen(words[k]))
					{
						printf("%s -> (%d,%d) --> Horizontal\n",words[k],(j+1),(i+1));
					}
				}
				k++;
			}
			
		}
	}
}

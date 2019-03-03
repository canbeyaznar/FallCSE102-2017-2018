#include <stdio.h>
int control(char str[100],int charCount,int lineCount);
int loop_print(int n);
int loop_print(int n)
{
	if(n==0)
	{
		return 0;
	}
	printf("-");
	n--;
	loop_print(n);
}
int control(char str[100],int charCount,int lineCount)
{
	int i;
	if( str[charCount]=='(' )
	{
		lineCount++;
		charCount++;	
	}
	else if( (str[charCount]>='A' && str[charCount]<='Z') || (str[charCount]>='a' && str[charCount]<='z') )
	{
		loop_print(lineCount);
		
		printf("%c\n",str[charCount]);
		charCount++;
	}
	else if( str[charCount]==',' )
	{
		charCount++;
	}
	else if( str[charCount]==')' )
	{
		lineCount--;
		charCount++;
	}
	else
	{
		return 0;
	}
	control(str,charCount,lineCount);
}
int main()
{
	FILE *ptr;
	ptr=fopen("input.txt","r");
	char string[100];
	int i,j=0;
	string[i]=fgetc(ptr);
	while(!feof(ptr) && string[i]!='\0')
	{
		printf("%c",string[i]);
		i++;
		string[i]=fgetc(ptr);
	}
	printf("\n");
	i=0;
	control(string,i,j);
}

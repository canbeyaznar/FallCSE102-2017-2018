#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef enum command_t{
	LEFT,
	RIGHT,
	UP,
	DOWN
}command_e;
typedef struct cube_t{
	int** val;
	struct cube_t *Right;
	struct cube_t *Left;
	struct cube_t *Up;
	struct cube_t *Down;
}cube_s;
int colorValue; //it will take size of dimension
int shrinkCounter=0;
void set_command_type(char *Direction,command_e *command_type)
{
	if(strcmp(Direction,"left")==0)
		*command_type=LEFT;
	else if(strcmp(Direction,"right")==0)
		*command_type=RIGHT;
	else if(strcmp(Direction,"up")==0)
		*command_type=UP;
	else if(strcmp(Direction,"down")==0)
		*command_type=DOWN;
}

void link_faces(cube_s *cube_ptr[])
{
	//Link the all faces which are connedcted to four faces
	int i;
	for(i=0;i<3;i++)
	{
		cube_ptr[i]->Right=cube_ptr[i+1];
		if(i==0)
			cube_ptr[i]->Left=cube_ptr[3];
		else
			cube_ptr[i]->Left=cube_ptr[i-1];
			
		cube_ptr[i]->Up=cube_ptr[4];
		cube_ptr[i]->Down=cube_ptr[5];
	}
	cube_ptr[3]->Right=cube_ptr[0];
	cube_ptr[3]->Left=cube_ptr[2];
	cube_ptr[3]->Down=cube_ptr[5];
	cube_ptr[3]->Up=cube_ptr[4];
	
	cube_ptr[4]->Right=cube_ptr[1];
	cube_ptr[4]->Left=cube_ptr[3];
	cube_ptr[4]->Down=cube_ptr[0];
	cube_ptr[4]->Up=cube_ptr[2];
	
	cube_ptr[5]->Right=cube_ptr[1];
	cube_ptr[5]->Left=cube_ptr[3];
	cube_ptr[5]->Down=cube_ptr[2];
	cube_ptr[5]->Up=cube_ptr[0];
}
void represent_cube_values(cube_s *cube_ptr[],int value)
{
	//Representing colors
	int i,j,k,num=0;
	for(i=0;i<6;i++)
	{
		cube_ptr[i]=(cube_s*) malloc(sizeof(cube_s));
	}
	for(i=0;i<6;i++)
	{
		cube_ptr[i]->val=malloc(sizeof(int**)*colorValue);
		for(j=0;j<colorValue;j++)
		{
			cube_ptr[i]->val[j]=malloc(sizeof(int*)*colorValue);
			for(k=0;k<colorValue;k++)
			{
				cube_ptr[i]->val[j][k]=num;
			}
		}
		num++;
	}
}
int rotate_cube(cube_s *cube_ptr[], int Face, char roworColumn[],int Position,command_e command_type)
{
	int i,j,k,control=0;
	cube_s *Current;
	int tempVal[colorValue],tempVal2[colorValue];
	Current=(cube_s*) malloc(sizeof(cube_s));
	Current=cube_ptr[Face];
	
	//if it is row rotate
	
	if(strcmp(roworColumn,"row")==0)
	{
		switch(command_type)
		{
			case RIGHT:
				if(Face==4)
				{
					for(i=shrinkCounter;i<colorValue;i++)
					{
						tempVal[i]=(Current->Right)->val[i][colorValue-Position-1];
						(Current->Right)->val[i][colorValue-Position-1]=Current->val[Position][i];
					}
					Current=Current->Right;
					for(i=shrinkCounter;i<colorValue;i++)
					{
						tempVal2[i]=(Current->Down)->val[colorValue-Position-1][i];
						(Current->Down)->val[colorValue-Position-1][i]=tempVal[colorValue-i-1];
					}	
					Current=Current->Down;	
					for(i=shrinkCounter;i<colorValue;i++)
					{	
						tempVal[i]=(Current->Left)->val[i][Position];
						(Current->Left)->val[i][Position]=tempVal2[i];
					}
					Current=Current->Left;
					for(i=shrinkCounter;i<colorValue;i++)
					{
						(Current->Up)->val[Position][colorValue-i-1]=tempVal[i];
					}
					break;	
				}
				else if(Face==5)
				{
					for(i=shrinkCounter;i<colorValue;i++)
					{
						tempVal[i]=(Current->Right)->val[i][Position];
						(Current->Right)->val[i][Position]=Current->val[Position][colorValue-i-1];
					}
					Current=Current->Right;
					for(i=shrinkCounter;i<colorValue;i++)
					{
						tempVal2[i]=(Current->Up)->val[colorValue-Position-1][i];
						(Current->Up)->val[colorValue-Position-1][i]=tempVal[i];
					}	
					Current=Current->Up;	
					for(i=shrinkCounter;i<colorValue;i++)
					{	
						tempVal[i]=(Current->Left)->val[i][colorValue-Position-1];
						(Current->Left)->val[i][colorValue-Position-1]=tempVal2[colorValue-i-1];
					}
					Current=Current->Left;
					for(i=shrinkCounter;i<colorValue;i++)
					{
						(Current->Down)->val[Position][i]=tempVal[i];
					}
					break;	
				}
				else
				{
					for(k=shrinkCounter;k<colorValue;k++)
					{
						tempVal[k]=(Current->Right)->val[Position][k];
						(Current->Right)->val[Position][k]=(Current)->val[Position][k];
					}
					Current=Current->Right;
					for(k=shrinkCounter;k<colorValue;k++)
					{
						tempVal2[k]=(Current->Right)->val[Position][k];
						(Current->Right)->val[Position][k]=tempVal[k];
					}
					Current=Current->Right;
					for(k=shrinkCounter;k<colorValue;k++)
					{
						tempVal[k]=(Current->Right)->val[Position][k];
						(Current->Right)->val[Position][k]=tempVal2[k];
					}
					Current=Current->Right;
					for(k=shrinkCounter;k<colorValue;k++)
					{
						(Current->Right)->val[Position][k]=tempVal[k];
					}
					break;
				}
				
			case LEFT:
				if(Face==4)
				{
					for(k=shrinkCounter;k<colorValue;k++)
					{
						tempVal[k]=(Current->Left)->val[k][Position];
						(Current->Left)->val[k][Position]=(Current)->val[Position][colorValue-k-1];
					}
					Current=Current->Left;
					for(k=shrinkCounter;k<colorValue;k++)
					{
						tempVal2[k]=(Current->Down)->val[colorValue-Position-1][k];
						(Current->Down)->val[colorValue-Position-1][k]=tempVal[k];
					}
					Current=Current->Down;
					for(k=shrinkCounter;k<colorValue;k++)
					{
						tempVal[k]=(Current->Right)->val[k][colorValue-Position-1];
						(Current->Right)->val[k][colorValue-Position-1]=tempVal2[colorValue-k-1];
					}
					Current=Current->Right;
					for(k=shrinkCounter;k<colorValue;k++)
					{
						(Current->Up)->val[Position][k]=tempVal[k];
					}
					break;
				}
				else if(Face==5)
				{
					for(k=shrinkCounter;k<colorValue;k++)
					{
						tempVal[k]=(Current->Left)->val[k][colorValue-Position-1];
						(Current->Left)->val[k][colorValue-Position-1]=(Current)->val[Position][k];
					}
					Current=Current->Left;
					for(k=shrinkCounter;k<colorValue;k++)
					{
						tempVal2[k]=(Current->Up)->val[colorValue-Position-1][k];
						(Current->Up)->val[colorValue-Position-1][k]=tempVal[colorValue-k-1];
					}
					Current=Current->Up;
					for(k=shrinkCounter;k<colorValue;k++)
					{
						tempVal[k]=(Current->Right)->val[k][Position];
						(Current->Right)->val[k][Position]=tempVal2[k];
					}
					Current=Current->Right;
					for(k=shrinkCounter;k<colorValue;k++)
					{
						(Current->Down)->val[Position][k]=tempVal[colorValue-k-1];
					}
					break;
				}
				else
				{
					for(k=shrinkCounter;k<colorValue;k++)
					{
						tempVal[k]=(Current->Left)->val[Position][k];
						(Current->Left)->val[Position][k]=(Current)->val[Position][k];
					}
					Current=Current->Left;
					for(k=shrinkCounter;k<colorValue;k++)
					{
						tempVal2[k]=(Current->Left)->val[Position][k];
						(Current->Left)->val[Position][k]=tempVal[k];
					}
					Current=Current->Left;
					for(k=shrinkCounter;k<colorValue;k++)
					{
						tempVal[k]=(Current->Left)->val[Position][k];
						(Current->Left)->val[Position][k]=tempVal2[k];
					}
					Current=Current->Left;
					for(k=shrinkCounter;k<colorValue;k++)
					{
						(Current->Left)->val[Position][k]=tempVal[k];
					}
					break;
				}
				
			default:
				printf("You cant rotate down or up with row selection!!\n");
				return -1;
		}
	}
	//if it is column rotate
	else if(strcmp(roworColumn,"column")==0)
	{
		switch(command_type)
		{
			case UP:
				if(Face==1)
				{
					for(k=shrinkCounter;k<colorValue;k++)
					{
						tempVal[k]=(Current->Up)->val[colorValue-Position-1][k];
						(Current->Up)->val[colorValue-Position-1][k]=(Current)->val[k][Position];
					}
					Current=Current->Up;
					for(k=shrinkCounter;k<colorValue;k++)
					{
						tempVal2[k]=(Current->Left)->val[k][colorValue-Position-1];
						(Current->Left)->val[k][colorValue-Position-1]=tempVal[colorValue-k-1];
					}
					Current=Current->Left;
					for(k=shrinkCounter;k<colorValue;k++)
					{
						tempVal[k]=(Current->Down)->val[Position][k];
						(Current->Down)->val[Position][k]=tempVal2[k];
					}
					Current=Current->Down;
					for(k=shrinkCounter;k<colorValue;k++)
					{
						(Current->Right)->val[k][Position]=tempVal[colorValue-k-1];
					}
					break;
				}
				else if(Face==3)
				{
					for(k=shrinkCounter;k<colorValue;k++)
					{
						tempVal[k]=(Current->Up)->val[Position][k];
						(Current->Up)->val[Position][k]=(Current)->val[colorValue-k-1][Position];
					}
					Current=Current->Up;
					for(k=shrinkCounter;k<colorValue;k++)
					{
						tempVal2[k]=(Current->Right)->val[k][colorValue-Position-1];
						(Current->Right)->val[k][colorValue-Position-1]=tempVal[k];
					}
					Current=Current->Right;
					for(k=shrinkCounter;k<colorValue;k++)
					{
						tempVal[k]=(Current->Down)->val[colorValue-Position-1][k];
						(Current->Down)->val[colorValue-Position-1][k]=tempVal2[colorValue-k-1];
					}
					Current=Current->Down;
					for(k=shrinkCounter;k<colorValue;k++)
					{
						(Current->Left)->val[k][Position]=tempVal[k];
					}
					break;
				}
				else
				{
					for(k=shrinkCounter;k<colorValue;k++)
					{
						tempVal[k]=(Current->Up)->val[k][Position];
						(Current->Up)->val[k][Position]=(Current)->val[k][Position];
					}
					Current=Current->Up;
					for(k=shrinkCounter;k<colorValue;k++)
					{
						tempVal2[k]=(Current->Up)->val[k][Position];
						(Current->Up)->val[k][Position]=tempVal[k];
					}
					Current=Current->Up;
					for(k=shrinkCounter;k<colorValue;k++)
					{
						tempVal[k]=(Current->Up)->val[k][Position];
						(Current->Up)->val[k][Position]=tempVal2[k];
					}
					Current=Current->Up;
					for(k=shrinkCounter;k<colorValue;k++)
					{
						(Current->Up)->val[k][Position]=tempVal[k];
					}
					break;
				}
				break;
			case DOWN:
				if(Face==1)
				{
					for(k=shrinkCounter;k<colorValue;k++)
					{
						tempVal[k]=(Current->Down)->val[Position][k];
						(Current->Down)->val[Position][k]=(Current)->val[colorValue-k-1][Position];
					}
					Current=Current->Down;
					for(k=shrinkCounter;k<colorValue;k++)
					{
						tempVal2[k]=(Current->Left)->val[k][colorValue-Position-1];
						(Current->Left)->val[k][colorValue-Position-1]=tempVal[k];
					}
					Current=Current->Left;
					for(k=shrinkCounter;k<colorValue;k++)
					{
						tempVal[k]=(Current->Up)->val[colorValue-Position-1][k];
						(Current->Up)->val[colorValue-Position-1][k]=tempVal2[colorValue-k-1];
					}
					Current=Current->Up;
					for(k=shrinkCounter;k<colorValue;k++)
					{
						(Current->Right)->val[k][Position]=tempVal[k];
					}
					break;
				}
				else if(Face==3)
				{
					for(k=shrinkCounter;k<colorValue;k++)
					{
						tempVal[k]=(Current->Down)->val[colorValue-Position-1][k];
						(Current->Down)->val[colorValue-Position-1][k]=(Current)->val[k][Position];
					}
					Current=Current->Down;
					for(k=shrinkCounter;k<colorValue;k++)
					{
						tempVal2[k]=(Current->Right)->val[k][colorValue-Position-1];
						(Current->Right)->val[k][colorValue-Position-1]=tempVal[colorValue-k-1];
					}
					Current=Current->Right;
					for(k=shrinkCounter;k<colorValue;k++)
					{
						tempVal[k]=(Current->Up)->val[Position][k];
						(Current->Up)->val[Position][k]=tempVal2[k];
					}
					Current=Current->Up;
					for(k=shrinkCounter;k<colorValue;k++)
					{
						(Current->Left)->val[k][Position]=tempVal[colorValue-k-1];
					}
					break;
				}
				else
				{
					for(k=shrinkCounter;k<colorValue;k++)
					{
						tempVal[k]=(Current->Down)->val[k][Position];
						(Current->Down)->val[k][Position]=(Current)->val[k][Position];
					}
					Current=Current->Down;
					for(k=shrinkCounter;k<colorValue;k++)
					{
						tempVal2[k]=(Current->Down)->val[k][Position];
						(Current->Down)->val[k][Position]=tempVal[k];
					}
					Current=Current->Down;
					for(k=shrinkCounter;k<colorValue;k++)
					{
						tempVal[k]=(Current->Down)->val[k][Position];
						(Current->Down)->val[k][Position]=tempVal2[k];
					}
					Current=Current->Down;
					for(k=shrinkCounter;k<colorValue;k++)
					{
						(Current->Down)->val[k][Position]=tempVal[k];
					}
					break;
				}
				
			default:
				printf("You cant rotate right or left with column selection!!\n");
				return -1;
		}
	}
	else 
	{
		printf("Unknown Command!!\n");
		free(Current);
		return -1;
	}
	Current=NULL;
	free(Current);
}
int shrink_cube(cube_s *cube_ptr[])
{
	int i,j,k;
	for(i=0;i<6;i++)
	{
		for(j=0;j<colorValue-1;j++)
		{
			for(k=0;k<colorValue-1;k++)
			{
				cube_ptr[i]->val[j][k]=cube_ptr[i]->val[j][k+1];
			}
		}
		for(j=0;j<colorValue-1;j++)
		{
			for(k=0;k<colorValue-1;k++)
			{
				cube_ptr[i]->val[j][k]=cube_ptr[i]->val[j+1][k];
			}
		}
	}
	colorValue--;
}

int read_commands(FILE *fp_commands_ptr,cube_s *cube_ptr[])
{
	char delim[2]=" ";
	char line[256]= { 0 };
	unsigned int temp_value;
	
	int Position,Face;
	char roworColumn[256];
	char Direction[256];
	command_e command_type;
	while(!feof(fp_commands_ptr))
	{
		while(fgets(line, sizeof(line), fp_commands_ptr)) //read line by line
		{
			if (line[strlen(line) - 1] == '\n')
				line[strlen(line) - 1] = 0;
			
			if (strstr(line, "rotate") != NULL)
				break;
			else if(strstr(line,"shrink")!=NULL)
				break;
		}
		char *token = strtok(line, delim);
		if(strcmp("rotate",token)==0)
		{
			token=strtok(NULL,delim);
			sscanf(token,"%d",&Face);
	
			token=strtok(NULL,delim);
			sscanf(token,"%s",&roworColumn);
	
			token=strtok(NULL,delim);
			sscanf(token,"%d",&Position);
	
			token=strtok(NULL,delim);
			sscanf(token,"%s",&Direction);
			set_command_type(&Direction, &command_type);
			if(rotate_cube(cube_ptr,Face,roworColumn,Position,command_type)==-1)
			{
				return -1;
			}
		}
		else if(strcmp("shrink",token)==0)
		{
			shrinkCounter++;
		}
		else
		{
			printf("UNKNOWN COMMAND!!\n");
			return -1;
		}
	}
	
	fseek(fp_commands_ptr, 0, SEEK_SET);
}
int main()
{
	cube_s * cube_ptr[6];
	int i,j,k;
	FILE *fp_commands = fopen("commands.txt","r");
	if(NULL==fp_commands)
	{
		printf("File cannot be read!\n");
		return -1;
	}
	FILE *fp_result = fopen("result.txt","w");
	if(NULL==fp_result)
	{
		printf("File cannot be read!\n");
		return -1;
	}
	
	fscanf(fp_commands,"%d",&colorValue);
	represent_cube_values(cube_ptr,colorValue);
	link_faces(cube_ptr);
	if(read_commands(fp_commands,cube_ptr)==-1)
	{
		printf("File couldn't read correctly!!\n");
		return 0;
	}
	for(i=0;i<6;i++)
	{
		for(j=shrinkCounter;j<colorValue;j++)
		{
			for(k=shrinkCounter;k<colorValue;k++)
			{
				fprintf(fp_result,"%d ",cube_ptr[i]->val[j][k]);
			}
			fprintf(fp_result,"\n");
		}
		fprintf(fp_result,"\n\n");
	}
	for(i=0;i<6;i++)
	{
		free(cube_ptr[i]);
		cube_ptr[i]=NULL;
	}
	
	fclose(fp_commands);
	fclose(fp_result);
	return 0;
}

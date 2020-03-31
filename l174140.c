#include<stdio.h>
#include<sys/types.h> 
#include<sys/wait.h> 
#include<string.h>
#include<stdlib.h>
#include<unistd.h>


#define limit 500
const char *mypath[] = {"./","/usr/bin/","/bin/",NULL};

char* getCommand(char* arr)
   {
	   arr=NULL;
	    char buf[limit]; 
		scanf("%[^\n]%*c", buf);
		if (strlen(buf) != 0) 
		{
			arr=(char*)malloc(sizeof(buf)+sizeof(char));
			strcpy(arr, buf);
			
		}
		return arr; 
		
		
   }

void directory() 
{ 
    char curr_dir[limit]; 
    getcwd(curr_dir,sizeof(curr_dir)); 
    printf("%s", curr_dir); 
	printf("%s", " : ");
} 
void findcommand(char str[],char** parsed)
{
	pid_t pid = fork();  
	if (pid == -1) { 
        printf("\nFailed forking child"); 
        return; 
    } else if (pid == 0) { 
        if (execv(str, parsed) < 0) { 
			    printf(" command not found in ");
				printf("%s",str);
				printf("\n");				
			}	
        exit(0); 
} 
else { 
        
        wait(NULL);  
        return; 
    } 
}

void executeCommand(char** parsed) 
{ 
    char str1[50];
	
	int i=0;
	
	
	
	for(i=0;mypath[i]!=NULL;i++)
	{
		str1[0]='\0';
		strcat(str1,mypath[i]);
		strcat(str1,parsed[0]);
		findcommand(str1,parsed);
	}

	
	
	
	
}
 
char** Tokenize(char*str)
{
	int i=0,j=0,count=0;
	char** temp;
	char**arr=NULL;
	temp[i++]=strtok(str," ");
	while((temp[i]=strtok(NULL," "))!=NULL)
	{
		i++;
	}
	arr=(char**)malloc(i*sizeof(char*)+sizeof(char*));
	for(j=0;j<i;j++)
	{
		count=strlen(temp[j]);
		arr[j]=(char*)malloc((count*sizeof(char))+sizeof(char));
		stpcpy(arr[j],temp[j]);
	}
	arr[j]=NULL;
	return arr;
}
char** PipeTokenize(char*str)
{
	int i=0,j=0,count=0;
	char** temp;
	char**arr=NULL;
	temp[i++]=strtok(str,"|");
	while((temp[i]=strtok(NULL,"|"))!=NULL)
	{
		i++;
	}
	arr=(char**)malloc(i*sizeof(char*)+sizeof(char*));
	for(j=0;j<i;j++)
	{
		count=strlen(temp[j]);
		arr[j]=(char*)malloc((count*sizeof(char))+sizeof(char));
		stpcpy(arr[j],temp[j]);
	}
	arr[j]=NULL;
	return arr;
}
int checkPipes(char** parsed)
{
	int count=0,i=0;
	for(i=0;parsed[i]!=NULL;i++)
	{
		if(strcmp(parsed[i],"|")==0)
		{
			count++;
		}
	}
	if(count>1)
	{	return -1;}
	else if(count==1)
	{	return 1;}
	else if(count==0)
	{	return  0;}
}
  
 
void ManagePipe(char** tokens) // this code will make two string str1 of comands before "|" and str2 of command after "|"
{
	char *str1=(char*)malloc(100*sizeof(char));
	char *str2=(char*)malloc(100*sizeof(char));
	str1[0]='\0',str2[0]='\0';
	strcat(str1,tokens[0]);
	int i=1;
	for(i;tokens[i][0]!='|';i++)
	{
		strcat(str1," ");
		strcat(str1,tokens[i]);
	}
	i++;
	strcat(str2,tokens[i++]);
	for(i;tokens[i]!=NULL;i++)
	{
		strcat(str2," ");
		strcat(str2,tokens[i]);
	}
	printf("%s",str1);
	printf("\n%s",str2);
	printf("%s","yahan");
	int j=0;
	char** tok1;
	tok1=Tokenize(str1);
	for(j;tok1[j]!=NULL;j++)
	{
		printf("\n%s",tok1[j]);
	}
	//char** tok2;
	//tok2=Tokenize(str2);
	
	//execArgsPiped(tok1,tok2);
	
}
 int main() 
{ 
	
	int cmdNo = 2;
	char *str;
	char** tokens;
	char** firstToken;
	char** secondToken;
	char* commands[cmdNo];  
	    
	    commands[0] = "exit"; 
	    commands[1] = "cd";  
		
		
  
    while (1) 
	{ 
		
		directory();
		str=getCommand(str);
		tokens=Tokenize(str);
		int i;
		
		if(checkPipes(tokens)==0)
		{	
			if(strcmp(tokens[0],commands[1])==0) // checks for cd command
			{
				chdir(tokens[1]);
			}
			else if(strcmp(tokens[0],commands[0])==0) // checks for exit command
			{
				exit(0);
			}
			else
			{
				executeCommand(tokens); // it will execute any command present in ./ , /usr/bin/ , /bin/
			}
		}
		else if( checkPipes(tokens)==1)
		{
			ManagePipe(tokens);
		}
		else
		{
			printf("%s"," invalid input more than 1 pipe found \n");
		}
    }
    return 0; 
} 


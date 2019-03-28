# include <stdio.h>
# include <string>
# include <stdlib.h>

void get_str_tmp(char *p,char *s)
{
    p = (char *)malloc(strlen(s)+1);
    strcpy(p,s);
    
    char *q = p;
    while(*q != '\0')
    {
   	if(*q >='a' && *q <= 'z')
	{
	    *q -= 32;
	}
	q++;
    }
}

int main()
{
    char buff[128] = {0};
    while(1)
    {
        printf("input: \n");
        fgets(buff,128,stdin);
        
        if(strcpy(buff,"end\n") == 0)
        {
	   break;
         
        }
        char * ptr  = NULL;
	get_str_tmp(ptr,buff);
        printf("ptr= %s\n",ptr);
	
	free(ptr);
    }
    return 0;
}

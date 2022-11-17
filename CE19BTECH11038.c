#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct user_info
{
    char user_name[20];
    char password[20];
}info;

int compare(char * str1, char* str2)
{
    int counter = 0 ;
    while(counter < strlen(str2))
    {
       if(*str1 != *str2)
       {
           break;
           return -1;
       }
       str1++;
       str2++;
       counter++;
       
    }
    return 0;
}
 int hash(char * username)
{
   int num1 = (int) username[0] ;
   int num2 = (int) username[1] ;
   int sum  = num1 + num2 - 48 ;
   return (sum % 36);

   
}
int main() 
{
  
    FILE *fpointer = fopen("userInfo.csv", "r");
 
    if(fpointer == NULL)
    {
        printf("could not open your file");
    }
    
    char temp[50];
    int row_c = 0;
    int field_c = 0;
    info hash_table[36][1000];
    int chain_count[36];
    for (int  i = 0; i < 36; i++)
    {
       chain_count[i] = 0 ;
    }
    
    while(!feof(fpointer))
    {
        fgets(temp, 50, fpointer);
        field_c = 0; 
        row_c++;
        char *field = strtok(temp,",") ;
        char  temp_username[20];
        char  temp_password[20];
        while(field != NULL)
        {
            if(field_c == 0)
            {
                
                strcpy(temp_username , field);
            }
             if(field_c == 1)
            {
               
                strcpy(temp_password , field);
            }
            field = strtok(NULL, ",");
            field_c ++;
        }
        int i = hash(temp_username);
       
        int j = chain_count[i];
        
         
        strcpy(hash_table[i][j].user_name , temp_username);
        
        strcpy(hash_table[i][j].password , temp_password);
        
        //printf("%d   %d  %s %s ",i,j,hash_table[i][j].user_name,hash_table[i][j].password);
        chain_count[i]++;
    } 
    
   
    int indicator = 0 ;
    char usr[20];
    printf("enter username: ");
    scanf("%s",usr);
    
    int hash_value;
    hash_value = hash(usr);
     

//    printf("%s  %s ",hash_table[hash_value][chain_count[hash_value]].user_name,hash_table[hash_value][chain_count[hash_value]].password);
    
    for (int i = 0; i < chain_count[hash_value]; i++)
    {
      if(strcmp(hash_table[hash_value][i].user_name,usr) == 0)
      {
          indicator = 1;
          char password_input[25];
          printf("enter the password: ");
          scanf("%s",password_input);
       

          if(strcmp(hash_table[hash_value][i].password,password_input) == 0)
          {
              printf("login successfull\n");
          }
          else
          {
            printf("wrong password\n ");
          }
      }
    } 
    if(indicator == 0 )
    {
        printf("invalid username ");
    }
    return 0;
}
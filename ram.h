extern void addToRAM(FILE* p, int* start, int* end);
extern void cleanRam();
extern int isFrameFree(int frameNumber);
extern void setRamCell(int ramCell, char* fileLine);
extern char* getInstruction(int index);
extern int getNextAvailableIndex();

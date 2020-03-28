extern int launcher(char* filename);
extern int countTotalPages(FILE *fp);
extern int findFrame();
extern int findVictim(PCB *p);
extern int updatePageTable(PCB *p, int pageNumber, int frameNumber, int victimFrame);
extern void loadPage(int pageNumber, FILE* f, int frameNumber);
#ifndef READER_H
#define READER_H

class Reader
{
public:
    int elementsNumber;
    int **tab;
    int *vertices;                      // useful for brute force
    Reader(char * filename);
    ~Reader();
    void printTab();

private:
    void read(char *filename);
};

#endif //READER_H
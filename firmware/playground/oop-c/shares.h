#ifndef SHARES_H
#define SHARES_H

struct SHARES {
    char* shareId;
    char* shareName;
    char* shareSymbol;
    float* sharePrice;

    struct SHARES* next;
    void (*DeleteShare)(struct SHARES*);
    char* (*GetShareId)(struct SHARES*);
    char* (*GetShareSymbol)(struct SHARES*);
    float (*GetSharePrice)(struct SHARES*);

    /* setters */
    void (*SetShareName)(struct SHARES*, char*);
    void (*SetShareName)(struct SHARES*, char*);
    void (*SetShareSymbol)(struct SHARES*, char*);
    void (*SetSharePrice)(struct SHARES*, float);
    
    void (*PrintShare) (struct SHARES*);

};

typedef struct SHARES* Shares;

Shares Share(); // constructor 
void deleteShares( Shares); // destructor 

char* getId(Shares);
void setId(Shares, char*);
char* getName(Shares);
char* getSymbol(Shares);
float* getPrice(Shares);

void setId(Shares, char*);
void setName(Shares, char*);
void setSymbol(Shares, float*);
void setPrice(Shares, float*);

void printShare(Shares);
void deleteShare(Shares);


#endif
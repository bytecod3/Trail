
#include <stdlib.h>
#include "shares.h"

/* Constructor */
Shares Share() {
    Shares this;
    this = (Shares) malloc(sizeof(struct SHARES));
    this->shareId = &setId;
    this->shareName = &setName;
    this->sharePrice = &setPrice;

    this->SetShareName = &setName;

}

char* getId(Shares this) {
    return this->shareId;
}
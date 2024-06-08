#include "main.h"
#include <stdio.h>
#include <stdlib.h>

int main() {


    //input bla2
    data data = {NULL, NULL, NULL};
    parse("satu.csv", &data);
    parse("dua.csv", &data);
    parse("tiga.csv", &data);


    
    save("satu.csv", &data);
    save("dua.csv", &data);
    save("tiga.csv", &data);

    return 0;
}
#include "types.h"
#include "stat.h"
#include "user.h"

int main(){
    // print how many times getreadcount has been called
    printf(1, "readcount = %d\n",getreadcount());
    
    exit();
}
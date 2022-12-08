// #include <stdio.h>
// #include <stdio.h>

// int main(int argc, char *argv[])
// {
//     char *arglist[3];
//     // arglist[0] = "ls";
//     // arglist[1] = "-l";
//     // arglist[2] = 0;

//     arglist[0] = "./b.out";
//     arglist[1] = NULL;

//     printf("*** About to exec 'ls -l'\n");

//     // call execvp
//     // execvp("ls", arglist);
//     execvp(arglist[0], arglist);
//     printf("*** ls is done. Bye\n");
// }

#include <unistd.h>
#include <stdio.h>

int main() {
    char *arglist[3];
    arglist[0] = "ls";
    arglist[1] = "-l";
    arglist[2] = NULL;

    printf("*** About to exec 'ls -l' \n");
    
    // call execvp
    execvp("ls", arglist);
    printf("*** ls is done. Bye \n");

}
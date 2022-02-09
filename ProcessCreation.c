
//Amir babaeiroochi
//COMP 322 Spring 2022
//Home work assignment #1
#include <stdio.h>
#include <stdlib.h>

int maxProcesses = 0;
typedef struct node{
    int parent;
    int firstChild;
    int olderSibling;
    int youngerSibling;
}node;

node * pcb = NULL;

void release(){
    //printf("release started\n");
    if (maxProcesses > 0){
        //printf("release success\n");
        maxProcesses = 0;
        free(pcb);
    }
    
}

void printTable(){
    printf("i\tParent\tFirst\tOlder\tYounger\n");
    printf("--------------------------------------\n");
    int i;
    for (i = 0; i < maxProcesses; i++){
        if (pcb[i].parent == -1){
            continue;
        }
        printf("%d\t%d\t", i, pcb[i].parent);
        if(pcb[i].firstChild != -1){
            printf("%d", pcb[i].firstChild);
        }
        printf("\t");
        if(pcb[i].olderSibling != -1){
            printf("%d", pcb[i].olderSibling);
        }
        printf("\t");
        if(pcb[i].youngerSibling != -1){
            printf("%d", pcb[i].youngerSibling);
        }
        printf("\n");
    }
}

void enter(){
    int i;
    release();
    printf("Enter maximum number of processes: \n");
    scanf("%d", &maxProcesses);
    if (maxProcesses <= 0){
        printf("Invalid number of processes. \n");
        return;
    }
    pcb = (node *)malloc(maxProcesses * sizeof(node));
    for (i = 0; i < maxProcesses; i++){
        pcb[i].parent = -1;
        pcb[i].firstChild = -1;
        pcb[i].olderSibling = -1;
        pcb[i].youngerSibling = -1;
    }
    //Initialize first pcb in array
    pcb[0].parent = 0;
    printTable();
}

void create(){
    int process = -1; //parent index
    int location = 0; //available index for new processes
    int youngestSibling;
    if (maxProcesses <= 0){
        printf("Invalid number of processes. \n");
        return;
    }
    printf("Enter the new processes parent index: ");
    scanf("%d", &process);
    if(process < 0 || process >= maxProcesses){
        printf("Invalid process index. \n");
        return;
    }
    if(pcb[process].parent == -1){
        printf("Process index is not active \n");
        return;
    }
    while(pcb[location].parent != -1){
        location++;
        if(location == maxProcesses){
            printf("New location out of bounds. \n");
            return;
        }
    }
    pcb[location].parent = process;
    
    if(pcb[process].firstChild == -1){
        pcb[process].firstChild  = location;
    }else{
        youngestSibling = pcb[process].firstChild;
        while(pcb[youngestSibling].youngerSibling != -1){
            youngestSibling = pcb[youngestSibling].youngerSibling;
        }
        pcb[location].olderSibling = youngestSibling;
        pcb[youngestSibling].youngerSibling = location;
    }
    
    printTable();
}
void destroyRecursively(int location){
    if (location == -1){//base case
        return;
    }
    //recursivley destroy from current younger Sibling
    destroyRecursively(pcb[location].youngerSibling);
    //recursivley destroy from current first child
    destroyRecursively(pcb[location].firstChild);
    //remove all data from current process
        pcb[location].parent = -1;
        pcb[location].firstChild = -1;
        pcb[location].olderSibling = -1;
        pcb[location].youngerSibling = -1;

}
void destroy(){
    int process = -1; //the prent process
    if (maxProcesses <= 0){
        printf("Invalid number of processes. \n");
        return;
    }
    //get input for process index
    printf("Enter the process whose decendents are to be destroyed: \n");
    scanf("%d", &process);
    if(process < 0 || process >= maxProcesses){
        printf("Invalid process index. \n");
        return;
    }
    if(pcb[process].parent == -1){
        printf("Process index is not active \n");
        return;
    }
    
    //destroy starting with first child recursively
    destroyRecursively(pcb[process].firstChild);
    
    //remove the ref. to the parent's first child
    pcb[process].firstChild = -1;
    //print table
    printTable();
}

int main()
{
    int option = 0;
    while(option != 4){
        //used for program safety and avoid infinite loop
        option = 4;
        printf("Process creation and destruction\n");
        printf("---------------------------------\n");
        printf("1) Enter Parameters\n");
        printf("2) Create a new child process\n");
        printf("3) Destroy all descendents of a process\n");
        printf("4) Quit program and free memory\n");
        printf("\n");
        printf("Enter Selection: ");
        scanf("%d", &option);
        printf("\n");
        switch (option){
            case 1:
                enter();
                break;
            case 2:
                create();
                break;
            case 3:
                destroy();
                break;
            case 4:
                printf("Goodbye");
                release();
                break;
            default:
                printf("Invalid option, try again. \n");
        }
        printf("\n");
    }

    return 0;
}



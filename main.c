#include <stdio.h>

typedef struct Graph {
    long int Id;
    long int value;
} Graph;

long int dijkstra(long int * ,long int );

int findIndexOfMin(long int *, long int );

int main() {

    long int numNodes=0;
    long int k=0;
    int c;
    long int score;

    for (int i = 0;(c=getchar_unlocked())!=' ';i++) {
        //printf("leggo carattere numero:%d\n",i);
        //printf("ed è:%d\n",c-48);
        numNodes = (numNodes*10) + (c - 48) ;
    }
    //printf("ho torvato lo spazio\n");
    for (int i=0; (c=getchar_unlocked())>=48 && c<58; i++) {
        //printf("leggo carattere numero:%d\n",i);
        //printf("ed è:%d\n",c-48);
        k = (k*10) + (c - 48) ;
    }
    long int graphEx[numNodes][numNodes];

    Graph topK[k];


    printf("\n\n -*-*-*-*-*-*-*-*-*-*-*-*- \n\n");
    printf("numNodes:%ld\n",numNodes);
    printf("k:%ld\n",k);
    printf("\n\n -*-*-*-*-*-*-*-*-*-*-*-*- \n\n");


    while ((c = getchar_unlocked()) != EOF){
        if(c == 'A'){
            printf("%c",c);
            while((c=getchar_unlocked())<48 || c>=58)
                printf("%c",c);
            //printf("\n");
            for(int i=0;i<numNodes;i++){
                for (int j = 0;j<numNodes;j++) {
                    //printf("\nasdfghjk\n");
                    long int value=0;
                    if(i==0 && j==0)
                        value = c-48;
                     while ((c=getchar_unlocked())!=44&&c>=48 && c<58 && c!='\n') {
                        //printf("leggo carattere numero:%d\n", i);
                        //printf("ed è:%d\n", c - 48);
                        value = (value * 10) + (c - 48);
                    }
                    if(c!='\n') {
                        printf("i:%d j:%d value:%ld\n", i, j, value);
                        graphEx[i][j] = value;
                    }else {
                        printf("%c", c);
                        j--;
                    }

                }
                printf("\n");
                for (int l = 0; l < numNodes; l++) {
                    for (int m = 0; m < numNodes; m++) {
                        printf("%ld,",graphEx[l][m]);
                    }
                    printf("\n");
                }
                score=dijkstra(&graphEx[0][0],numNodes);
                printf("Graph score:%ld\n",score);
            }

        }
    }

    return 0;
}

long int dijkstra(long int *graphEx, long int numNodes) {
    long int distTot=0;
    long int dist[numNodes];
    dist[0]=0;
    for(int j=1;j<numNodes;j++) {
        printf("a%d\n",j);
        dist[j] = *(graphEx+j);
        printf("b%d\n",j);
    }

    for (int i = 0; i < numNodes; ++i) {
        printf("distanza iniziale del nodo %d: %ld\n",i, dist[i]);
    }
    printf("\n");

    for (int i=0;i<numNodes;i++){
        int min= findIndexOfMin(&dist[0], numNodes);
        printf("nodo a distanza min:%d\n",min);
        printf("distanza del nodo min:%ld\n",dist[min]);
        for (int j = 0; j < numNodes; j++) {
            printf("valuto dist del nodo %d:%ld\n",j,*(graphEx+min*numNodes+j));
            if(*(graphEx+min*numNodes+j)>0) {
                long int newDist = dist[min] + *(graphEx+min*numNodes+j);
                printf("Newdist:%ld\n",newDist);
                if (newDist < dist[j] && newDist > 0 && dist[j] > 0) {
                    printf("ho trovato un percorso più corto per il nodo %d di costo:%ld\n", j, newDist);
                    dist[j] = newDist;
                }
            }
        }

        distTot=distTot+dist[min];
        dist[min]=-1;
        for (int k = 0; k < numNodes; k++) {
            printf("distanza attuale del nodo %d: %ld\n",k, dist[k]);
        }printf("valore attuale distTot:%ld\n\n",distTot);
    }

    printf("distTot:%ld\n",distTot);
    return distTot;
}

int findIndexOfMin(long int *dist,long int numNodes) {
    int min=0;
    for(int i=0;i< numNodes;i++) {
        if ((dist[i] > 0 && dist[i] < dist[min])||(dist[min] < 0))
            min = i;
    }
    return min;
}

#include <stdio.h>

typedef struct Graph {
    long int Id;
    long int value;
} Graph;

long int dijkstra(long int * ,long int );

int findIndexOfMin(long int *, long int );

void heapify(struct Graph *, long int, long int );

void swap(struct Graph *, long int, long int );

void printTopK(struct Graph *,long int);

int main() {

    long int numNodes=0;
    long int k=0;
    int c;
    long int score;
    long int graphId=0;
    long int numGraph=0;

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

    Graph topK[k+1];
    /*
    for (int i = 0; i < k+1; i++) {
        topK[i].Id=-1;
    }
    */

    /*
    printf("\n\n -*-*-*-*-*-*-*-*-*-*-*-*- \n\n");
    printf("numNodes:%ld\n",numNodes);
    printf("k:%ld\n",k);
    printf("\n\n -*-*-*-*-*-*-*-*-*-*-*-*- \n\n");
    */

    while ((c = getchar_unlocked()) != EOF){
        if(c == 'A'){
            //printf("%c",c);
            while((c=getchar_unlocked())<48 || c>=58);
                //printf("%c",c);
            for(int i=0;i<numNodes;i++){
                for (int j = 0;j<numNodes;j++) {
                    long int value=0;
                    if(i==0 && j==0)
                        value = c-48;
                    while ((c=getchar_unlocked())>=48 && c<58 && c!=',' &&c!='\n') {
                        //while ((c=getchar_unlocked())!=44&&c>=48 && c<58 && c!='\n') {
                        //printf("leggo carattere numero:%d\n", i);
                        //printf("ed è:%d\n", c - 48);
                        value = (value * 10) + (c - 48);
                    }
                    //printf("value:%ld\n",value);
                    graphEx[i][j] = value;
                }
            }
            /*
            printf("\n");
            printf("Graph %ld \n",graphId);
            for (int l = 0; l < numNodes; l++) {
                for (int m = 0; m < numNodes; m++) {
                    printf("%ld,",graphEx[l][m]);
                }
                printf("\n");
            }
             */
            score=dijkstra(&graphEx[0][0],numNodes);
            //printf("\nGraph %ld score:%ld\n",graphId,score);
            if(numGraph<k){
                numGraph++;
                topK[numGraph].Id=graphId;
                topK[numGraph].value=score;
                /*
                for (int i = 1; i < k+1; i++) {
                    if(topK[i].Id==-1){
                        topK[i].Id=graphId;
                        topK[i].value=score;
                        numGraph++;
                        //printf("Ho appena inserito un nuovo elemento\n");
                        break;
                    }
                }
                 */
                /*
                for (long int j = numGraph; j>0; j--) {
                    printf("%ld:Graph:%ld --> score:%ld\n",j,topK[j].Id,topK[j].value);
                }
                 */
                for (long int i = numGraph/2; i > 0 ; i--) {
                    heapify(topK, numGraph, i);
                }
                /*
                printf("Ho riordinato l'heap\n");
                for (long int j = numGraph; j>0; j--) {
                    printf("%ld:Graph:%ld --> score:%ld\n",j,topK[j].Id,topK[j].value);
                }
                 */
            } else{
                if (score<topK[1].value){
                    topK[1].value=score;
                    topK[1].Id=graphId;
                }
                /*
                printf("\nHo appena sostituito un elemento\n");
                for (long int j = numGraph; j>0; j--)
                    printf("%ld:Graph:%ld --> score:%ld\n",j,topK[j].Id,topK[j].value);
                */
                for (long int j = numGraph; j>0; j--)
                    heapify(topK, numGraph, j);
                /*
                printf("Ho riordinato l'heap\n");
                for (long int j = numGraph; j>0; j--)
                    printf("%ld:Graph:%ld --> score:%ld\n",j,topK[j].Id,topK[j].value);
                */
            }
            graphId++;
        }else if(c== 'T'){
            while((c=getchar_unlocked())!='K');
            printTopK(topK,numGraph);
        }
    }

    return 0;
}

void printTopK(struct Graph *topK, long int numGraph) {
    for (long int j = 1; j<numGraph; j++) {
        printf("%ld ",topK[j].Id);
    }
    if(numGraph>0)
        printf("%ld",topK[numGraph].Id);
    printf("\n");
}

long int dijkstra(long int *graphEx, long int numNodes) {
    long int distTot=0;
    long int dist[numNodes];
    dist[0]=0;
    for(int j=1;j<numNodes;j++) {
        //printf("a%d\n",j);
        dist[j] = *(graphEx+j);
        //printf("b%d\n",j);
    }

    /*
    for (int i = 0; i < numNodes; ++i) {
        printf("distanza iniziale del nodo %d: %ld\n",i, dist[i]);
    }
    printf("\n");
     */

    for (int i=0;i<numNodes;i++){
        int min;
        if(i==0)
            min=0;
        else
            min= findIndexOfMin(&dist[0], numNodes);
        long int distMin=dist[min];
        dist[min]=-1;
        //printf("nodo a distanza min:%d\n",min);
        //printf("distanza del nodo min:%ld\n",distMin);
        for (int j = 0; j < numNodes; j++) {
            //printf("valuto dist del nodo %d:%ld\n",j,*(graphEx+min*numNodes+j));
            if(*(graphEx+min*numNodes+j)>0) {
                long int newDist = distMin + *(graphEx+min*numNodes+j);
                //printf("Newdist:%ld\n",newDist);
                if ((newDist < dist[j]&&dist[j]>0)||(newDist > 0 && dist[j] == 0)) {
                    //printf("ho trovato un percorso più corto per il nodo %d di costo:%ld\n", j, newDist);
                    dist[j] = newDist;
                }
            }
        }

        distTot=distTot+distMin;
        /*for (int k = 0; k < numNodes; k++) {
            printf("distanza attuale del nodo %d: %ld\n",k, dist[k]);
        }printf("valore attuale distTot:%ld\n\n",distTot);
         */
    }

    //printf("distTot:%ld\n",distTot);
    return distTot;
}

int findIndexOfMin(long int *dist,long int numNodes) {
    int min=0;
    for(int i=1;i< numNodes;i++) {
        if ((dist[i] > 0 && dist[i] < dist[min])||(dist[min] <= 0))
            min = i;
    }
    return min;
}

void heapify(struct Graph *topK, long int numGraph, long int n) {
    //printf("sono nella heapify\n");
    long int leftSon=2*n,rightSon=(2*n)+1,posMax;
    if (leftSon<=numGraph && topK[leftSon].Id!=-1 && topK[leftSon].value>topK[n].value) {
        posMax = leftSon;
        //printf("il grafo in posizione %ld è minore del figlio sinistro\n", n);
    }else {
        //printf("il grafo in posizione %ld è maggiore del figlio sinistro\n", n);
        posMax = n;
    }
    if (rightSon<=numGraph && topK[rightSon].Id!=-1 && topK[rightSon].value>topK[posMax].value) {
        posMax = rightSon;
        //printf("il grafo in posizione %ld è minore del figlio destro\n", posMax);
    }else {
        //printf("il grafo in posizione %ld è maggiore del figlio destro\n", posMax);
    }
    if (posMax!=n) {
        //printf("c'è bisogno di fare uno swap\n");
        swap(topK, n, posMax);
        heapify(topK, numGraph, posMax);
    }
}

void swap(struct Graph *topK, long int n, long posMax) {
    long int tempId,tempValue;
    tempId=topK[n].Id;
    tempValue=topK[n].value;
    topK[n].Id=topK[posMax].Id;
    topK[n].value=topK[posMax].value;
    topK[posMax].Id=tempId;
    topK[posMax].value=tempValue;
}

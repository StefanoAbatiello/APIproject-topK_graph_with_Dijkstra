#include <stdio.h>
#include <malloc.h>

typedef struct Node {
    int id;
    long int dist;
} Node;

typedef struct Graph {
    long int Id;
    long int value;
} Graph;

long int dijkstra(long int * ,long int );

void max_heapify(struct Graph *, long int, long int );

void swap_graph(struct Graph *, long int, long int );

void printTopK(struct Graph *,long int);

long insertNode(Node *, Node , long *);

void swap_node(struct Node *, long int, long int);

void min_Heapify(Node *, long int *, long int);

Node deleteMin(Node *, long int *);

int main() {

    long int numNodes=0;
    long int k=0;
    int c;
    long int score;
    long int graphId=0;
    long int numGraph=0;

    for (int i = 0;(c=getchar_unlocked())!=' ';i++) {
        numNodes = (numNodes*10) + (c - 48) ;
    }
    for (int i=0; (c=getchar_unlocked())>=48 && c<58; i++) {
        k = (k*10) + (c - 48) ;
    }

    Graph topK[k+1];
    while ((c = getchar_unlocked()) != EOF){
        if(c == 'A'){
            long int *graphEx= malloc(sizeof (long int)*(numNodes*numNodes));
            while((c=getchar_unlocked())<48 || c>=58);
            for (int i = 0; i < numNodes; i++) {
                for (long int j = i*numNodes; j < (i+1)*numNodes; j++) {
                    long int value=0;
                    if(i==0 && j==0)
                        value = c-48;
                    while ((c=getchar_unlocked())>=48 && c<58 && c!=',' &&c!='\n') {
                        value = (value * 10) + (c - 48);
                    }
                    graphEx[j] = value;
                }
            }
            score=dijkstra(graphEx,numNodes);
            free(graphEx);
            //printf("Graph %ld score:%ld\n\n",graphId,score);
            if(numGraph<k){
                numGraph++;
                topK[numGraph].Id=graphId;
                topK[numGraph].value=score;
                if(numGraph==k) {
                    for (long int i = numGraph / 2; i > 0; i--)
                        max_heapify(topK, numGraph, i);
                }
            } else if (score<topK[1].value) {
                topK[1].value = score;
                topK[1].Id = graphId;
                max_heapify(topK, numGraph, 1);
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
        printf("%ld", topK[numGraph].Id);
    /*
    if(numGraph>0) {
        printf("%ld", topK[1].Id);
        for (long int j = 1; j < (numGraph / 2); j++) {
            if (j * 2 <= numGraph) {
                printf(" %ld", topK[2 * j].Id);
            }
            if ((j * 2) + 1 <= numGraph) {
                printf(" %ld", topK[(2 * j) + 1].Id);
            }
        }
    }
    */
    printf("\n");
}

long int dijkstra(long int *graphEx, long int numNodes) {
    long int distTot=0;
    long int QSize=0;
    Node *Q=malloc((numNodes)* sizeof(Node));
    for(int j=1;j<numNodes;j++) {
        Node node;
        node.id=j;
        node.dist=graphEx[j];
        //printf("nodo %d con dist:%ld\n",node.id,node.dist);
        QSize=insertNode(Q, node, &QSize);
    }
    /*printf("ho creato il min-heap con dimensione:%ld\n",QSize);
    for (int i = 1; i <= QSize; i++) {
        printf("nodo con id %d e con dist %ld\n",Q[i].id,Q[i].dist);
    }
    */
    while (QSize>0){
        Node node= deleteMin(Q, &QSize);
        /*
        printf("nodo più vicino:%d, ha distanza:%ld\n",node.id,node.dist);
        printf("ora min-heap ha dimensione:%ld\n",QSize);
        for (int j = 1; j <= QSize; j++) {
            printf("nodo con id %d e con dist %ld\n",Q[j].id,Q[j].dist);
        }
         */
        distTot=distTot+node.dist;
        /*
        printf("distanza totale attuale:%ld\n",distTot);
        for (int i = 0; i < QSize; i++) {
            printf("nodo con id %d e con dist %ld\n",Q[i].id,Q[i].dist);
        }
         */
        for (int i = 1; i <= QSize; i++) {
            /*
            printf("valuto distanza del nodo %d dal nodo %d\n", Q[i].id, node.id);
            printf("distanza:%ld\n",graphEx[node.id*numNodes+Q[i].id]);
            */
            if(graphEx[node.id*numNodes+Q[i].id]>0) {
                long int dist = node.dist + (graphEx[node.id*numNodes+Q[i].id]);
                //printf("dist=%ld\n", dist);
                if (dist < Q[i].dist || Q[i].dist == 0) {
                    //printf("valore della distanza del nodo %d da cambiare nell'heap\n", Q[i].id);
                    Q[i].dist = dist;
                    if(QSize>1)
                        min_Heapify(Q, &QSize, 1);
                    /*for (int j = 1; j <= QSize; j++) {
                        printf("nodo con id %d e con dist %ld\n",Q[j].id,Q[j].dist);
                    }
                     */
                }
            }
        }
    }
    free(Q);
    return distTot;
}

Node deleteMin(Node *Q, long int *QSize) {
    //PRENDO IL PRIMO, SPOSTO L'ULTIMO NEL PRIMO, DIMINUISCO QSIZE E FACCIO HEAPIFY
    /*
    printf("sto prendendo il nodo più vicino, QSize=%ld\n",*QSize);
    for (int i = 1; i <= *QSize; i++) {
        printf("%d:nodo con id %d e con dist %ld\n",i,Q[i].id,Q[i].dist);
    }
     */
    Node node=Q[1];
    Q[1].dist=Q[(*QSize)].dist;
    Q[1].id=Q[(*QSize)].id;
    (*QSize)--;
    if(*QSize>1)
        min_Heapify(Q,QSize,1);
    /*
    for (int i = 1; i <= *QSize; i++) {
        printf("%d:nodo con id %d e con dist %ld\n",i,Q[i].id,Q[i].dist);
    }
     */
    return node;
}

long insertNode(Node *Q, Node node, long int *QSize) {
    //printf("sono in accodaNode\n");
    (*QSize)++;
    Q[*QSize]=node;
    /*
    for (int i = 1; i <= *QSize; i++) {
        printf("%d:nodo con id %d e con dist %ld\n",i,Q[i].id,Q[i].dist);
    }
    printf("QSize prima della heapify:%ld\n",*QSize);
    */
    if(*QSize>1){
        min_Heapify(Q, QSize, (*QSize)/2);
        /*for (long int i = (*QSize)/2; i < 0; i--) {

        }*/
    }
    /*
    for (int i = 1; i <= *QSize; i++) {
        printf("%d:nodo con id %d e con dist %ld\n",i,Q[i].id,Q[i].dist);
    }
    printf("-\n");
    */
    return *QSize;
}

void min_Heapify(struct Node *Q, long int *QSize, long int n) {
    //printf("sono nella heapify\n");
    long int leftSon=2*n,rightSon=(2*n)+1,posMin;
    if (leftSon<=*QSize && (Q[leftSon].dist<Q[n].dist || Q[n].dist==0) && Q[leftSon].dist>0) {
        posMin = leftSon;
        //printf("il grafo in posizione %ld è minore del figlio sinistro\n", n);
    }else {
        //printf("il grafo in posizione %ld è maggiore del figlio sinistro\n", n);
        posMin = n;
    }
    if (rightSon<=*QSize && (Q[rightSon].dist<Q[posMin].dist || Q[posMin].dist==0) && Q[rightSon].dist>0) {
        posMin = rightSon;
        //printf("il grafo in posizione %ld è minore del figlio destro\n", posMax);
    }else {
        //printf("il grafo in posizione %ld è maggiore del figlio destro\n", posMax);
    }
    if (posMin!=n) {
        //printf("c'è bisogno di fare uno swap\n");
        swap_node(Q, n, posMin);
        min_Heapify(Q, QSize, posMin);
    }
}

void swap_node(struct Node *Q, long int n, long posMin) {
    long int tempValue=Q[n].dist;
    int tempId=Q[n].id;
    Q[n].id=Q[posMin].id;
    Q[n].dist=Q[posMin].dist;
    Q[posMin].dist=tempValue;
    Q[posMin].id=tempId;
}

void max_heapify(struct Graph *topK, long int numGraph, long int n) {
    long int leftSon=2*n,rightSon=(2*n)+1,posMax;
    if (leftSon<=numGraph && topK[leftSon].value>topK[n].value) {
        posMax = leftSon;
        //printf("il grafo in posizione %ld è minore del figlio sinistro\n", n);
    }else {
        //printf("il grafo in posizione %ld è maggiore del figlio sinistro\n", n);
        posMax = n;
    }
    if (rightSon<=numGraph && topK[rightSon].value>topK[posMax].value) {
        posMax = rightSon;
        //printf("il grafo in posizione %ld è minore del figlio destro\n", posMax);
    }else {
        //printf("il grafo in posizione %ld è maggiore del figlio destro\n", posMax);
    }
    if (posMax!=n) {
        //printf("c'è bisogno di fare uno swap\n");
        swap_graph(topK, n, posMax);
        max_heapify(topK, numGraph, posMax);
    }
}

void swap_graph(struct Graph *topK, long int n, long posMax) {
    long int tempId=topK[n].Id,tempValue=topK[n].value;
    topK[n].Id=topK[posMax].Id;
    topK[n].value=topK[posMax].value;
    topK[posMax].Id=tempId;
    topK[posMax].value=tempValue;
}

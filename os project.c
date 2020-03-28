#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <time.h>

int n;
int m;
int *resource;
int **allocate;
int **maxReq;
int **need;
int *safe;
int nProcessRan = 0;

pthread_mutex_t lockResource;
pthread_cond_t condition;


bool getSafe();

void* processcode(void* );

int main(int argument_c, char** argument_v) {
	srand(time(NULL));

        printf("\nNo. of processes? ");
        scanf("%d", &m);

        printf("\nNo. of resources? ");
        scanf("%d", &n);

        resource = (int *)malloc(n * sizeof(*resource));
        printf("\nAvailable resources");
        int i=0;
        while( i<n){
		
                scanf("%d", &resource[i]);
                i++;}

        allocate = (int **)malloc(m * sizeof(*allocate));
        
		while( i<m){
		
                allocate[i] = (int *)malloc(n * sizeof(**allocate));
                i++;}

        maxReq = (int **)malloc(m * sizeof(*maxReq));
        
		while( i<m){
		
                maxReq[i] = (int *)malloc(n * sizeof(**maxReq));
                i++;}

        printf("\n");
        for(int i=0; i<m; i++) {
                printf("\nResource allocated to process %d", i+1);
                for(int j=0; j<n; j++)
                        scanf("%d", &allocate[i][j]);
        }
        printf("\n");

        for(int i=0; i<m; i++) {
                printf("\nMaximum resource required by process %d", i+1);
                for(int j=0; j<n; j++)
                        scanf("%d", &maxReq[i][j]);
        }
        printf("\n");

	
        need = (int **)malloc(m * sizeof(*need));
        for(int i=0; i<m; i++)
                need[i] = (int *)malloc(n * sizeof(**need));

        for(int i=0; i<m; i++)
                for(int j=0; j<n; j++)
                        need[i][j] = maxReq[i][j] - allocate[i][j];

	
	safe = (int *)malloc(m * sizeof(*safe));
        for(int i=0; i<m; i++) safe[i] = -1;

        if(!getSafe()) {
                printf("\nUnsafe State! \n");
                exit(-1);
        }
		printf("\n\nSafe Sequence Found : ");
        for(int i=0; i<m; i++) {
                printf("%-3d", safe[i]+1);
        }

        printf("\nExecutable Processes\n\n");
        sleep(1);
	
	
	pthread_t processes[m];
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_create;
        pthread_join;

	int processNumber[m];
	for(int i=0; i<m; i++) processNumber[i] = i;

        for(int i=0; i<m; i++)
                pthread_create(&processes[i], &attr, processcode, (void *)(&processNumber[i]));

        for(int i=0; i<m; i++)
                pthread_join(processes[i], NULL);

        printf("\nAll Processes Finished\n");	
	
	
        free(resource);
        for(int i=0; i<m; i++) {
                free(allocate[i]);
                free(maxReq[i]);
		free(need[i]);
        }
        free(allocate);
        free(maxReq);
	free(need);
        free(safe);
}
 bool getSafe() {
	
        int temp[n];
        for(int i=0; i<n; i++) temp[i] = resource[i];

        bool over[m];
        for(int i=0; i<m; i++) over[i] = false;
        int nover=0;
        while(nover < m) {
                bool safe_1 = false;

                for(int i=0; i<m; i++) {
                        if(!over[i]) {
                                bool possible = true;

                                for(int j=0; j<n; j++)
                                        if(need[i][j] > temp[j]) {
                                                possible = false;
                                                break;
                                        }

                                if(possible) {
                                        for(int j=0; j<n; j++)
                                                temp[j] += allocate[i][j];
                                        safe[nover] = i;
                                        over[i] = true;
                                        ++nover;
                                        safe_1 = true;
                                }
                        }
                }

                if(!safe_1) {
                        for(int k=0; k<m; k++) safe[k] = -1;
                        return false; 
                }
        }
        return true;
}

void* processcode(void *arg) {
        int p = *((int *) arg);

	
        pthread_mutex_lock(&lockResource);

        
        while(p != safe[nProcessRan])
                pthread_cond_wait(&condition, &lockResource);

	
        printf("\n--> Process %d", p+1);
        printf("\n\tProvided : ");
        for(int i=0; i<n; i++)
                printf("%3d", allocate[p][i]);

        printf("\n\tNeeded    : ");
        for(int i=0; i<n; i++)
                printf("%3d", need[p][i]);

        printf("\n\tAvailable : ");
        for(int i=0; i<n; i++)
                printf("%3d", resource[i]);

        printf("\n"); sleep(1);

        printf("\tResource provided!");
        printf("\n"); 
		sleep(1);
        printf("\tProcess Code Running");
        printf("\n"); 
		sleep(rand()%3 + 2); 
        printf("\tProcess Code Completed");
        printf("\n"); 
		sleep(1);
        printf("\tProcess Releasing Resource");
        printf("\n"); 
		sleep(1);
        printf("\tResource Released!");

	for(int i=0; i<n; i++)
                resource[i] += allocate[p][i];

        printf("\n\tNow it is Available : ");
        for(int i=0; i<n; i++)
                printf("%3d", resource[i]);
        printf("\n\n");

        sleep(1);

	nProcessRan++;
        pthread_cond_broadcast(&condition);
        pthread_mutex_unlock(&lockResource);
	pthread_exit(NULL);
}

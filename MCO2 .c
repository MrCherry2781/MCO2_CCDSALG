#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NODES 175000

// Structure to represent a node in the graph
typedef struct Node {
    int data;
    struct Node* next;
} Node;

void backSlashToForwardSlash(char path[50]) {
    int len = strlen(path);
    for (int i = 0; i < len; i++) {
        if (path[i] == '\\') {
            path[i] = '/';
        }
    }
}

void readFile(int *num_accounts, int *num_friendships, int friendships[1750000][2], char filePath[50]) {
    FILE *fp = fopen(filePath, "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        exit(EXIT_FAILURE);
    }

    fscanf(fp, "%d %d", num_accounts, num_friendships);

    for (int i = 0; i < *num_friendships; i++) {
        fscanf(fp, "%d %d", &friendships[i][0], &friendships[i][1]);
    }

    fclose(fp);
}

void findFriends(int data[][2], int connections, int ID, int *num_friends, int FriendList[])
{
	int i = 0;
	int j = 0;
	int index1 = -1;
	int index2 = 0;
	
	for(i = 0; i < connections; i++)
	{
		
		if(ID == data[i][1])
		{
			index1 = i;
			i = connections + 1;
		}	
	}

    for(i = index1; i < connections+1; i++)
    {
        if(ID != data[i][1])
        {
            index2 = i;
            i = connections;
        }	
    }
    
    *num_friends = index2 - index1;
    
    for(i = index1; i < index2; i++)
    {
        FriendList[j] = data[i][0];
        j++;
    }	
}

/*
	Function for printing the friends from an inputted ID number.
*/
void displayFriends(int data[][2], int accounts, int connections)
{
	int ID;
	int i = 0;
	int valid = 1;
	int num_friends;
	int new_line = 1;
	static int FriendList[1750000];

    // This loop asks the input for a ID number, if invalid then loop, else continue.
	do 																		
	{
		printf("Input ID number [from 0 to %d]: ", accounts-1);
		scanf("%d", &ID);
		
		if(ID < 0 || ID > accounts-1)
		{
			printf("ID not found, please try again\n\n");
		}
		else
		{
			valid = 0;
		}
	}while(valid == 1);
	
	// Calling the function to find friends of input.
	findFriends(data, connections, ID, &num_friends, FriendList);

	// Prints the array of friends.
	printf("\nPerson %d has %d friends!\n", ID, num_friends); 				
	printf("List of friends:\n\n");
	for(i = 0; i < num_friends; i++)
	{
		printf("%5d ", FriendList[i]);
		if(new_line == 10) 													// If statement to print a new line so that only 10 friends will be displayed per line.
		{
			printf("\n");
			new_line = 0;
		}
		new_line++;
	}
    printf("\n");
}

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void addEdge(Node* adjacencyList[], int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = adjacencyList[src];
    adjacencyList[src] = newNode;
}

void printGraph(Node* adjacencyList[], int numNodes) {
    for (int i = 1; i <= numNodes; i++) {
        printf("Node %d is connected to:", i);
        Node* current = adjacencyList[i];
        while (current) {
            printf(" %d", current->data);
            current = current->next;
        }
        printf("\n");
    }
}

int* BFS(Node* adjacencyList[], int numNodes, int startVertex, int destinationVertex) {
    int* visited = (int*)malloc(numNodes * sizeof(int));
    for (int i = 1; i <= numNodes; ++i)
        visited[i] = 0;

    // Create a queue for BFS
    int* queue = (int*)malloc(numNodes * sizeof(int));
    int front = 0, rear = 0;

    // Parent array to store the path
    int* parent = (int*)malloc(numNodes * sizeof(int));
    for (int i = 1; i <= numNodes; ++i)
        parent[i] = -1;

    visited[startVertex] = 1;
    queue[rear++] = startVertex;

    while (front < rear) {
        int currentVertex = queue[front++];
        if (currentVertex == destinationVertex)
            break;

        Node* temp = adjacencyList[currentVertex];
        while (temp != NULL) {
            int adjVertex = temp->data;
            if (!visited[adjVertex]) {
                visited[adjVertex] = 1;
                parent[adjVertex] = currentVertex;
                queue[rear++] = adjVertex;
            }
            temp = temp->next;
        }
    }

    // Reconstruct the shortest path using the parent array
    int* path = (int*)malloc(numNodes * sizeof(int));
    int pathIndex = 0;
    int currentNode = destinationVertex;
    while (currentNode != -1) {
        path[pathIndex++] = currentNode;
        currentNode = parent[currentNode];
    }

    free(visited);
    free(queue);
    free(parent);

    // Reverse the path array to get the correct order
    int* shortestPath = (int*)malloc(pathIndex * sizeof(int));
    for (int i = 0; i < pathIndex; ++i) {
        shortestPath[i] = path[pathIndex - i - 1];
    }
    free(path);

    return shortestPath;
}

void connections(Node* adjacencyList[],int num_friendships){
	// Get input from the user
    int a, b;
    printf("\nEnter ID number first ID: ");
    scanf("%d", &a);
    printf("Enter ID number second ID: ");
    scanf("%d", &b);

    int numNodes = MAX_NODES; // Assuming 'num_accounts' represents the number of nodes
    int* shortestPath = BFS(adjacencyList, numNodes, a, b);

    if (shortestPath == NULL) {
        printf("\nThere is no path from node %d to node %d.\n", a, b);
    } else {
        printf("\nShortest path from node %d to node %d: \n", a, b);
        for (int i = 0; shortestPath[i] != b; ++i) {
            printf("%d is a friend of %d \n", shortestPath[i],shortestPath[i+1]);
        }
        free(shortestPath);
    }
}

int main() {
    int num_accounts = 0;
    int num_friendships = 0;
    static int friendships[1750000][2];
    char filePath[50];

    // Ask for file path
    printf("Enter Path of File to Load: ");
    scanf(" %[^\n]", filePath);
    backSlashToForwardSlash(filePath);

    readFile(&num_accounts, &num_friendships, friendships, filePath);

    Node* adjacencyList[MAX_NODES] = { NULL };

    for (int i = 0; i < num_friendships; i++) {
        int src = friendships[i][0];
        int dest = friendships[i][1];
        addEdge(adjacencyList, src, dest);
    }
    // Menu loop
    int choice;
    do 
    {
        printf("\nMAIN MENU\n");
        printf("[1] Get friend list\n");
        printf("[2] Get connection\n");
        printf("[3] Clear History\n");
        printf("[4] Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            displayFriends(friendships,num_accounts,num_friendships);
            break;
        case 2:
            connections(adjacencyList,num_friendships);
            break;
        case 3:
            system("cls");
            break;
        case 4:
            printf("Exiting the program.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

#ifdef _WIN32
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
typedef int socklen_t;
#else
#include <unistd.h>
#include <arpa/inet.h>
#endif

#define PORT 8080
#define ROWS 2000
#define COLS 2000

int main()
{

    // Allocate memory for the matrixA
    int **matrixA = (int **)malloc(ROWS * sizeof(int *));
    if (matrixA == NULL)
    {
        fprintf(stderr, "Memory allocation failed for rows.\n");
        return 1; // Exit the program with an error code
    }

    for (int i = 0; i < ROWS; i++)
    {
        matrixA[i] = (int *)malloc(COLS * sizeof(int));
        if (matrixA[i] == NULL)
        {
            fprintf(stderr, "Memory allocation failed for columns.\n");

            // Free the memory allocated for previous rows
            for (int j = 0; j < i; j++)
            {
                free(matrixA[j]);
            }

            // Free the memory allocated for the row pointers
            free(matrixA);

            return 1; // Exit the program with an error code
        }
    }

    // Initialize the matrix elements if needed
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < ROWS; j++)
        {
            matrixA[i][j] = 1; // Example initialization, you can set values as needed
        }
    }

    // Allocate memory for the matrixB
    int **matrixB = (int **)malloc(ROWS * sizeof(int *));
    if (matrixB == NULL)
    {
        fprintf(stderr, "Memory allocation failed for rows.\n");
        return 1; // Exit the program with an error code
    }

    for (int i = 0; i < ROWS; i++)
    {
        matrixB[i] = (int *)malloc(COLS * sizeof(int));
        if (matrixB[i] == NULL)
        {
            fprintf(stderr, "Memory allocation failed for columns.\n");

            // Free the memory allocated for previous rows
            for (int j = 0; j < i; j++)
            {
                free(matrixB[j]);
            }

            // Free the memory allocated for the row pointers
            free(matrixB);

            return 1; // Exit the program with an error code
        }
    }

    // Initialize the matrix elements if needed
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < ROWS; j++)
        {
            matrixB[i][j] = 1; // Example initialization, you can set values as needed
        }
    }

    // Allocate memory for the matrixA
    int **result1 = (int **)malloc(650 * sizeof(int *));
    if (result1 == NULL)
    {
        fprintf(stderr, "Memory allocation failed for rows.\n");
        return 1; // Exit the program with an error code
    }

    for (int i = 0; i < 650; i++)
    {
        result1[i] = (int *)malloc(COLS * sizeof(int));
        if (result1[i] == NULL)
        {
            fprintf(stderr, "Memory allocation failed for columns.\n");

            // Free the memory allocated for previous rows
            for (int j = 0; j < i; j++)
            {
                free(result1[j]);
            }

            // Free the memory allocated for the row pointers
            free(result1);

            return 1; // Exit the program with an error code
        }
    }
    // Allocate memory for the matrixA
    int **result2 = (int **)malloc(650 * sizeof(int *));
    if (result2 == NULL)
    {
        fprintf(stderr, "Memory allocation failed for rows.\n");
        return 1; // Exit the program with an error code
    }

    for (int i = 0; i < 650; i++)
    {
        result2[i] = (int *)malloc(COLS * sizeof(int));
        if (result2[i] == NULL)
        {
            fprintf(stderr, "Memory allocation failed for columns.\n");

            // Free the memory allocated for previous rows
            for (int j = 0; j < i; j++)
            {
                free(result2[j]);
            }

            // Free the memory allocated for the row pointers
            free(result2);

            return 1; // Exit the program with an error code
        }
    }
    // Allocate memory for the matrixA
    int **result3 = (int **)malloc(700 * sizeof(int *));
    if (result3 == NULL)
    {
        fprintf(stderr, "Memory allocation failed for rows.\n");
        return 1; // Exit the program with an error code
    }

    for (int i = 0; i < 700; i++)
    {
        result3[i] = (int *)malloc(COLS * sizeof(int));
        if (result3[i] == NULL)
        {
            fprintf(stderr, "Memory allocation failed for columns.\n");

            // Free the memory allocated for previous rows
            for (int j = 0; j < i; j++)
            {
                free(result3[j]);
            }

            // Free the memory allocated for the row pointers
            free(result3);

            return 1; // Exit the program with an error code
        }
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    int server_socket, client_socket1, client_socket2, client_socket3;

    struct sockaddr_in client_addr1, client_addr2, client_addr3;

    struct timeval start, end;
    gettimeofday(&start, NULL);

    // Create socket
    int server_sock;
    struct sockaddr_in server_addr;
    socklen_t addr_size;
    char buffer[]="Hello Client, This is server";
    int n;
    char *ip = "----------";

#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        perror("[-] WSAStartup failed\n");
        exit(1);
    }
#endif

    // Socket
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0)
    {
        perror("[-] Socket Error\n");
        exit(1);
    }
    printf("[+] TCP server socket is created\n");

    memset(&server_addr, '\0', sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(ip);

    // Bind the socket to the specified port
    if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_sock, 2) == -1)
    {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    // Accept connection from the first client
    socklen_t client_addr_len1 = sizeof(client_addr1);
    client_socket1 = accept(server_sock, (struct sockaddr *)&client_addr1, &client_addr_len1);
    if (client_socket1 == -1)
    {
        perror("Accept failed for client 1");
        exit(EXIT_FAILURE);
    }

    printf("Client 1 connected\n");
    send(client_socket1, buffer, strlen(buffer), 0);
    // Accept connection from the second client
    socklen_t client_addr_len2 = sizeof(client_addr2);
    client_socket2 = accept(server_sock, (struct sockaddr *)&client_addr2, &client_addr_len2);
    if (client_socket2 == -1)
    {
        perror("Accept failed for client 2");
        exit(EXIT_FAILURE);
    }

    printf("Client 2 connected\n");
    send(client_socket2, buffer, strlen(buffer), 0);

    // Accept connection from the third client
    socklen_t client_addr_len3 = sizeof(client_addr3);
    client_socket3 = accept(server_sock, (struct sockaddr *)&client_addr3, &client_addr_len3);
    if (client_socket3 == -1)
    {
        perror("Accept failed for client 3");
        exit(EXIT_FAILURE);
    }

    printf("Client 3 connected\n");
    send(client_socket3, buffer, strlen(buffer), 0);

    // Send the first row to the first client
    
    send(client_socket1, (const char *)matrixB, sizeof(matrixB), 0);
    for (int i = 0; i < 650; i++)
    {
        send(client_socket1, (const char *)matrixA[i], sizeof(matrixA[i]), 0);
    }

    // Send the second row to the second client
    send(client_socket2, (const char *)matrixB, sizeof(matrixB), 0);
    for (int j = 650; j < 1300; j++)
    {
        send(client_socket2, (const char *)matrixA[j], sizeof(matrixA[j]), 0);
    }

    // Send the third row to the third client
    send(client_socket3, (const char *)matrixB, sizeof(matrixB), 0);
    for (int k = 1300; k < 2000; k++)
    {
        send(client_socket3, (const char *)matrixA[k], sizeof(matrixA[k]), 0);
    }

    // Receive the results from all clients
    for (int i = 0; i < 650; i++)
    {
        recv(client_socket1, (char *)result1[i], sizeof(result1), 0);
    }
    for (int i = 0; i < 650; i++)
    {
        recv(client_socket2, (char *)result2[i], sizeof(result2), 0);
    }
    for (int i = 0; i < 700; i++)
    {
        recv(client_socket3, (char *)result3[i], sizeof(result3), 0);
    }

    gettimeofday(&end, NULL);

    double time_taken;
    time_taken = (end.tv_sec - start.tv_sec) * 1e6;
    time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;

    printf("Time taken by program is : %lf ms\n", time_taken);

    // FOR PRINTING MATRIX
/*
    for (int i = 0; i < 650; i++)
    {
        for (int j = 0; j < 2000; j++)
        {
            printf("%d ", result1[i]);
        }
        printf("\n");
    }
    for (int i = 0; i < 650; i++)
    {
        for (int j = 0; j < 2000; j++)
        {
            printf("%d ", result2[i]);
        }
        printf("\n");
    }
    for (int i = 0; i < 650; i++)
    {
        for (int j = 0; j < 2000; j++)
        {
            printf("%d ", result3[i]);
        }
        printf("\n");
    }
    */
    // Don't forget to free the allocated memory when you're done
    for (int i = 0; i < ROWS; i++)
    {
        free(matrixA[i]);
    }
    free(matrixA);
    // Don't forget to free the allocated memory when you're done
    for (int i = 0; i < ROWS; i++)
    {
        free(matrixB[i]);
    }
    free(matrixB);
    // Don't forget to free the allocated memory when you're done
    for (int i = 0; i < 650; i++)
    {
        free(result1[i]);
    }
    free(result1);
    // Don't forget to free the allocated memory when you're done
    for (int i = 0; i < 650; i++)
    {
        free(result2[i]);
    }
    free(result2);
    // Don't forget to free the allocated memory when you're done
    for (int i = 0; i < 700; i++)
    {
        free(result3[i]);
    }
    free(result3);

    // Close sockets
    close(client_socket1);
    close(client_socket2);
    close(client_socket3);
    close(server_sock);

#ifdef _WIN32
    WSACleanup();
#endif


    return 0;
}

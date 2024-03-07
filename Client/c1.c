#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <winsock2.h>
#include <windows.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <unistd.h>
#include <arpa/inet.h>
#endif

#define PORT 8080
#define ROWS 2000
#define COLS 2000

void multiply_matrices(int** matrix, int** row, int**result)
{
    for (int i = 0; i < 650; i++)
    {
        for (int k = 0; k < 2000; k++)
        {
            int sum = 0;
            for (int j = 0; j < 2000; j++)
            {
                sum += row[i][k] * matrix[k][j];
            }
            result[i][k] = sum;
        }
    }
}

int main()
{
    // Initialize Winsock on Windows
#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        perror("[-] WSAStartup failed\n");
        exit(1);
    }
#endif

    // Create client socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1)
    {
        perror("Socket creation failed");
#ifdef _WIN32
        WSACleanup();
#endif
        exit(EXIT_FAILURE);
    }

    // Initialize server address structure
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("-----------");

    // Connect to the server
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("Connection failed");
#ifdef _WIN32
        WSACleanup();
#endif
        exit(EXIT_FAILURE);
    }
    char buffer[1024];
    recv(client_socket, buffer, sizeof(buffer), 0);
    printf("Received message from server: %s\n", buffer);
    /////////////////////////////////////////////////////////////////////////////////////
    // Allocate memory for the matrixA
    int **matrix = (int **)malloc(ROWS * sizeof(int *));
    if (matrix == NULL)
    {
        fprintf(stderr, "Memory allocation failed for rows.\n");
        return 1; // Exit the program with an error code
    }

    for (int i = 0; i < ROWS; i++)
    {
        matrix[i] = (int *)malloc(COLS * sizeof(int));
        if (matrix[i] == NULL)
        {
            fprintf(stderr, "Memory allocation failed for columns.\n");

            // Free the memory allocated for previous rows
            for (int j = 0; j < i; j++)
            {
                free(matrix[j]);
            }

            // Free the memory allocated for the row pointers
            free(matrix);

            return 1; // Exit the program with an error code
        }
    }
    // Allocate memory for the matrixA
    int **rows = (int **)malloc(650 * sizeof(int *));
    if (rows == NULL)
    {
        fprintf(stderr, "Memory allocation failed for rows.\n");
        return 1; // Exit the program with an error code
    }

    for (int i = 0; i < 650; i++)
    {
        rows[i] = (int *)malloc(COLS * sizeof(int));
        if (rows[i] == NULL)
        {
            fprintf(stderr, "Memory allocation failed for columns.\n");

            // Free the memory allocated for previous rows
            for (int j = 0; j < i; j++)
            {
                free(rows[j]);
            }

            // Free the memory allocated for the row pointers
            free(rows);

            return 1; // Exit the program with an error code
        }
    }
    // Allocate memory for the matrixA
    int **result = (int **)malloc(650 * sizeof(int *));
    if (result == NULL)
    {
        fprintf(stderr, "Memory allocation failed for rows.\n");
        return 1; // Exit the program with an error code
    }

    for (int i = 0; i < 650; i++)
    {
        result[i] = (int *)malloc(COLS * sizeof(int));
        if (result[i] == NULL)
        {
            fprintf(stderr, "Memory allocation failed for columns.\n");

            // Free the memory allocated for previous rows
            for (int j = 0; j < i; j++)
            {
                free(result[j]);
            }

            // Free the memory allocated for the row pointers
            free(result);

            return 1; // Exit the program with an error code
        }
    }
    //////////////////////////////////////////////////////////////////////////////////////
    // Receive matrix and row from server
    recv(client_socket, (char *)matrix, sizeof(matrix), 0);
    for(int i=0;i<650;i++)
    {
        recv(client_socket, (char *)rows[i], sizeof(rows), 0);
    }

    // Multiply row with matrix
    multiply_matrices(matrix, rows, result);

    // Send the result back to the server
    for(int i=0;i<650;i++)
    {
            send(client_socket, (const char *)result[i], sizeof(result), 0);
    }
    /////////////////////////////////////////////////////////////////////
    // Don't forget to free the allocated memory when you're done
    for (int i = 0; i < ROWS; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
    // Don't forget to free the allocated memory when you're done
    for (int i = 0; i < 650; i++)
    {
        free(rows[i]);
    }
    free(rows);
    // Don't forget to free the allocated memory when you're done
    for (int i = 0; i < 650; i++)
    {
        free(result[i]);
    }
    free(result);
    ///////////////////////////////////////////////////////////////////////
    // Close socket
#ifdef _WIN32
    closesocket(client_socket);
#else
    close(client_socket);
#endif

#ifdef _WIN32
    WSACleanup();
#endif

    return 0;
}
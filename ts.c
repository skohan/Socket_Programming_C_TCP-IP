#include <stdio.h>
#include <string.h>
#include <ctype.h>

char c[3][3];
int arr[3][3] = {
	{1, 2, 3},
	{4, 5, 6},
	{7, 8, 9}};

//FOR PRINTING MATRIX
void print(char a[3][3])
{
	int i, j, k;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (a[i][j] == '\0')
				printf("   ");
			else
				printf(" %c ", a[i][j]);
			if (j != 2)
				printf("|");
		}
		printf("\n");
		if (i != 2)
			printf("-----------\n");
	}
	printf("\n");
}

//FOR CHECKING X AND O
void checkXO(int a, int d, char c[3][3])
{
	if (c[a][d] == 'X')
		printf("\n******************YOU WON!!******************\n");
	else
		printf("\n******************YOU LOST!!******************\n");
}

//FOR CHECKING IF SOMEONE IS WON
int check()
{
	int n;
	for (n = 0; n < 3; n++)
	{
		if ((c[0][n] == c[1][n]) && (c[0][n] == c[2][n]) && (c[0][n] != '\0'))
		{
			checkXO(0, n, c);
			return 1;
		}
		else if ((c[n][1] == c[n][0]) && (c[n][1] == c[n][2]) && (c[n][1] != '\0'))
		{
			checkXO(n, 0, c);
			return 1;
		}
	}
	if ((c[0][0] == c[1][1]) && (c[1][1] == c[2][2]) && (c[1][1] != '\0'))
	{
		checkXO(0, 0, c);
		return 1;
	}
	else if ((c[0][2] == c[1][1]) && (c[1][1] == c[2][0]) && (c[1][1] != '\0'))
	{
		checkXO(0, 2, c);
		return 1;
	}

	return 0;
}

int play(int sockfd)
{
	int n, buffer;
	int i, j;
	printf("*********Instructions*********\nType the number to print X on that position \n");
	//print((char) arr);
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			c[i][j] = '\0';
		}
	}
	printf("You are first \n");
	while (1)
	{
		printf("You: \n");
		printf("Enter cell number-> ");
		scanf("%d", &buffer);
		//SERVER WILL PLAY FIRST
		n = write(sockfd, &buffer, sizeof(buffer));

		for (i = 0; i < 3; i++)
		{
			for (j = 0; j < 3; j++)
			{
				if (arr[i][j] == buffer)
					c[i][j] = 'X';
			}
		}
		print(c);
		if (check() == 1)
		{
			return 0;
		}
		int temp = 0;
		for (i = 0; i < 3; i++)
		{
			for (j = 0; j < 3; j++)
			{
				if (c[i][j] == 'X' || c[i][j] == 'O')
					temp++;
			}
		}
		if (temp == 9)
		{
			printf("\n******************Draw******************\n");
			break;
		}

		printf("\nYour friends turn :\n");
		n = read(sockfd, &buffer, sizeof(buffer));

		for (i = 0; i < 3; i++)
		{
			for (j = 0; j < 3; j++)
			{
				if (arr[i][j] == buffer)
					c[i][j] = 'O';
			}
		}
		print(c);
		if (check() == 1)
		{
			return 0;
		}
	}
	return 1;
}

void Send(int sockfd)
{
	char buffer[512];
	bzero(buffer, 512);

	FILE *f;

	int words = 0;
	char c;
	char fn[20];
Q:
	printf("Enter the file name \n");
	scanf("%s", fn);
	f = fopen(fn, "r");
	if (f == NULL)
	{
		printf("Error no file found");
		goto Q;
	}
	while ((c = getc(f)) != EOF) //Counting No of words in the file
	{
		fscanf(f, "%s", buffer);
		if (isspace(c) || c == '\t')
			words++;
	}

	write(sockfd, &words, sizeof(int));
	rewind(f);

	char ch;
	while (ch != EOF)
	{

		fscanf(f, "%s", buffer);
		write(sockfd, buffer, 512);
		ch = fgetc(f);
	}
	printf("The file was sent successfully");
	bzero(buffer, 512);
}

void Recv(int newsockfd)
{
	FILE *fp;
	int ch = 0;
	char buffer[512];
	fp = fopen("recieved.txt", "a");
	int words;
	read(newsockfd, &words, sizeof(int));
	while (ch != words)
	{
		read(newsockfd, buffer, 512);
		fprintf(fp, " %s", buffer);

		ch++;
	}
	printf("The file was received successfully\n");
	printf("The new file created is glad5.txt");
	bzero(buffer, 512);
	//fclose(fp);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <setjmp.h>

jmp_buf bufferEOF;

char* getNextToken(char *source)
{
	static unsigned int ptr;
	char buffer[128] = {0};
	char currChar = 0;
	unsigned int i = 0;
	int inString = 0;
	int endStatement = 0;
	
	while (ptr < strlen(source) && i < 128)
	{
		currChar = source[ptr++];
		if (currChar == '"')
		{
			if (inString == 0)
			{
				inString = 1;
			}
			else
			{
				inString = 0;
			}
		}
		if (inString == 0)
		{
			if (currChar == ' ')
			{
				break;
			}
			else if (currChar == '\n')
			{
				continue;
			}
			else if (currChar == ';'
				|| currChar == '('
				|| currChar == ')')
			{
				if (i == 0)
				{
					endStatement = 1;
				}
				else
				{
					ptr--;
					break;
				}
				
			}
		}
		
		buffer[i++] = currChar;
		if (endStatement == 1)
		{
			break;
		}
	}
	
	if (i > 0)
	{
		char *token = malloc(i * sizeof(char) + 1);
		strcpy(token, buffer);
		return token;
	}
	else
	{
		return NULL;
	}
}

char **getTokenList(char *source, int *tokenListSize)
{
	char **tokenListBuffer = malloc(128);
	int i = 0;
	int bufferSize = 0;
	char *token;
	do
	{
		token = getNextToken(source);
		if (token == NULL || token == '\0')
		{
			break;
		}
		tokenListBuffer[i++] = token;
		bufferSize += strlen(token);
		
	} while (token != NULL && token != '\0');
	
	
	char **tokenList = malloc(bufferSize);
	for (int k = 0; k < i; k++)	
	{
		tokenList[k] = tokenListBuffer[k];
	}
	
	free(tokenListBuffer);
	*tokenListSize = i;
	return tokenList;
}

char *readSourceFile(FILE *sourceFile)
{
	fseek(sourceFile, 0, SEEK_END);
	long size = ftell(sourceFile);
	rewind(sourceFile);
	
	
	char *buffer =calloc(size+1, sizeof(char));
	if (buffer == NULL)
	{
		return NULL;
	}
	
	fread(buffer, size, sizeof(char), sourceFile);
	return buffer;
}

int main(int argc, char **argv)
{
	/*
	if (argc == 1)
	{
		fprintf(stderr, "require 1 argument");
		exit(1);
	}
	*/
	FILE *sourceFile = fopen("test.greg++", "r");
	if (sourceFile == NULL)
	{
		fprintf(stderr, "can not open file %s", argv[1]);
		exit(1);
	}
	
	char *source = readSourceFile(sourceFile);
	fclose(sourceFile);
	
	int tokenSize;
	char **tokenList = getTokenList(source, &tokenSize);
	
	for (int i = 0; i < tokenSize; i++)
	{
		printf("%s\n", tokenList[i]);
	}
	
	free(tokenList);
	return 0;
}
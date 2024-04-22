#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "variableStore.h"

void interpret(char **tokenList, int tokenListSize)
{
	VariableStoreHead *vStoreHead = createVariableStore();
	for (int i = 0; i < tokenListSize; i++)
	{
		char *token = tokenList[i];
		if (strcmp(token, "greg") == 0) // variable stuff
		{
			char *varName = tokenList[++i];
			if (strcmp(tokenList[++i],"=") != 0) {
				fprintf(stderr, "fumier de =");
				exit(1);
			}
			char *varValue = tokenList[++i];
			if (varValue[0] == '"') // string
			{
				size_t len = strlen(varValue);
				char *stringVarValue = calloc(sizeof(char), len - 1);
				if (varValue[len - 1] != '"')
				{
					fprintf(stderr, "fumier de \"");
					exit(1);
				}
				memcpy(stringVarValue, varValue + sizeof(char), len - 2);
				VariableStore *varDefined = getVariableStore(vStoreHead, varName);
				// var already defined, replace string
				if (varDefined != NULL)
				{
					setVarValue(varDefined, stringVarValue);
				}
				else // var not defined, set string
				{
					addVariable(vStoreHead, varName, stringVarValue);
				}
			}
			else // symbole
			{
				VariableStore *var = getVariableStore(vStoreHead, varValue);
				if (var == NULL)
				{
					fprintf(stderr, "fumier de %s undefined", varName);
					exit(1);
				}
				
				VariableStore *varToSet = getVariableStore(vStoreHead, varName);
				if (varToSet == NULL) // symbole don't existe, add new variable
				{
					addVariable(vStoreHead, varName, getVarValue(var));	
				}
				else // symbole existe, set symbole value
				{
					setVarValue(varToSet, getVarValue(var));
				}
			}
			
			if (strcmp(tokenList[++i], ";") != 0) {
				fprintf(stderr, "fumier de ;");
				exit(1);
			}
		}
		else if (strcmp(token, "gregtech") == 0)
		{
			if (strcmp(tokenList[++i], "(") != 0) {
				fprintf(stderr, "fumier de (");
				exit(1);
			}
			char *varName = tokenList[++i];
			if (strcmp(tokenList[++i], ")") != 0) {
				fprintf(stderr, "fumier de )");
				exit(1);
			}
			if (varName[0] == '"') // print a string
			{
				size_t len = strlen(varName);
				if (varName[len - 1] != '"')
				{
					fprintf(stderr, "fumier de \"");
					exit(1);
				}
				char *stringVarValue = calloc(sizeof(char), len - 1);
				memcpy(stringVarValue, varName + sizeof(char), len - 2);
				printf(stringVarValue);
				printf("\n"); // new line
			}
			else // print a variable
			{
				VariableStore *var = getVariableStore(vStoreHead, varName);
				
				printf(getVarValue(var));
				printf("\n"); // new line
			}
		}
	}
}
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
		if (strcmp(token, "greg") == 0)
		{
			char *varName = tokenList[++i];
			if (strcmp(tokenList[++i],"=") != 0) {
				fprintf(stderr, "fumier de =");
				exit(1);
			}
			char *varValue = tokenList[++i];
			addVariable(vStoreHead, varName, varValue);
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
			VariableStore *var = getVariableStore(vStoreHead, varName);
			if (strcmp(tokenList[++i], ")") != 0) {
				fprintf(stderr, "fumier de )");
				exit(1);
			}
			printf(getVarValue(var));
		}
	}
}
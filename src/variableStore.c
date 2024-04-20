#include <stdlib.h>
#include <string.h>

#include "variableStore.h"

typedef struct vStore {
	char *variableName;
	void *variableValue;
	VariableStore *next;
} VariableStore;



VariableStoreHead *createVariableStore()
{
	VariableStoreHead *vStoreHead = malloc(sizeof(VariableStoreHead));
	vStoreHead->first = NULL;
	return vStoreHead;
}

VariableStore *getVariableStore(VariableStoreHead *variableStoreHead, char *variableName)
{
	VariableStore *vStore = variableStoreHead->first;
	while (vStore != NULL) {
		if (strcmp(vStore->variableName, variableName) == 0)
		{
			return vStore;
		}
		vStore = vStore->next;
	}
	
	return NULL;
}

void addVariable(VariableStoreHead *variableStoreHead, char *variableName, void *variableValue)
{
	VariableStore *newVStore = malloc(sizeof(VariableStore));
	newVStore->variableName = variableName;
	newVStore->variableValue = variableValue;
	newVStore->next = NULL;
	
	if (variableStoreHead->first == NULL)
	{
		variableStoreHead->first = newVStore;
	}
	else
	{
		VariableStore *vStore = variableStoreHead->first;
		while (vStore->next != NULL) {
			vStore = vStore->next;
		}
		vStore->next = newVStore;
	}
}

void *getVarValue(VariableStore *var)
{
	return var->variableValue;
}

/*
void setVariableValue(VariableStoreHead *variableStoreHead, char *variableName, void *variableValue)
{
	getVariableStore(variableStoreHead, variableName)->variableValue = variableValue;
}
*/
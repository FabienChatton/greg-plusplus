#ifndef VARIABLE_STORE_H
#define VARIABLE_STORE_H

typedef struct vStore VariableStore;

typedef struct VariableStoreHead {
	VariableStore *first;
} VariableStoreHead;

VariableStoreHead *createVariableStore();
VariableStore *getVariableStore(VariableStoreHead *variableStoreHead, char *variableName);
void addVariable(VariableStoreHead *variableStoreHead, char *variableName, void *variableValue);
void *getVarValue(VariableStore *var);


#endif // VARIABLE_STORE_H
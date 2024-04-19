## lex
### keyword

greg -> begin variable
gregtech -> print to stdout


#### later keyword
whatisthisandhowdoigetridofit -> begin a function
feedthememe -> begin a loop

### operator
+ -> sub or concat

### assigment
= -> assigne a value to a variable

## parsing
greg -> variableName -> =                       -> ;
                       / \
		              "   number
					 /
			     string value untile next "

gregtech -> ( -> variable -> ) -> ;
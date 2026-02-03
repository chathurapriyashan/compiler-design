run:
	gcc -o ./out/compiler ./src/lexer/lexer.c ./src/semantic/semantic.c ./src/symbols/symbols.c ./src/parser/parser.c ./src/helpers/files.c ./src/helpers/error.c main.c && ./out/compiler input.txt
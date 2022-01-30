%{
%}

%option noyywrap
saltoLinea [\r\n]

%%
"obras" { fprintf(yyout, "OBRAS\n"); }
"de"  { fprintf(yyout, "DE\n"); }
"prefiero" { fprintf(yyout, "PREFIERO\n"); }
"lee" { fprintf(yyout, "LEE\n"); }
"compra" { fprintf(yyout, "COMPRA\n"); }
"busca" { fprintf(yyout, "BUSCA\n"); }
"investiga" { fprintf(yyout, "INVESTIGA\n"); }
"Neruda" { fprintf(yyout, "NERUDA\n"); }
"Kafka" { fprintf(yyout, "KAFKA\n"); }
"Cervantes" { fprintf(yyout, "CERVANTES\n"); }
"Shakespeare" { fprintf(yyout, "SHAKESPEARE\n"); }
"Tolkien" { fprintf(yyout, "TOLKIEN\n"); }
"Orwell" { fprintf(yyout, "ORWELL\n"); }
"Lovecraft" { fprintf(yyout, "LOVECRAFT\n"); }
"cuentos" { fprintf(yyout, "CUENTOS\n"); }
"novelas" { fprintf(yyout, "NOVELAS\n"); }
"dramas" { fprintf(yyout, "DRAMAS\n"); }
"romance" { fprintf(yyout, "ROMANCE\n"); }
"terror" { fprintf(yyout, "TERROR\n"); }
"fantasía" { fprintf(yyout, "FANTASÍA\n"); }
"misterio" { fprintf(yyout, "MISTERIO\n"); }
"comedia" { fprintf(yyout, "COMEDIA\n"); }
"literatura" { fprintf(yyout, "LITERATURA\n"); }
"antigua" { fprintf(yyout, "ANTIGUA\n"); }
"medieval" { fprintf(yyout, "MEDIEVAL\n"); }
"renacentista" { fprintf(yyout, "RENACENTISTA\n"); }
"barroca" { fprintf(yyout, "BARROCA\n"); }
"neoclásica" { fprintf(yyout, "NEOCLÁSICA\n"); }
"romana" { fprintf(yyout, "ROMANA\n"); }
"griega" { fprintf(yyout, "GRIEGA\n"); }
"naturalista" { fprintf(yyout, "NATURALISTA\n"); }
"populares" { fprintf(yyout, "POPULARES\n"); }
. {}
{saltoLinea} {}
"<<EOF>>" {}
%%




int main(int argc, char const *argv[]){
    
    if (argc == 1){
        printf("Error: Faltan par%cmetros.\n", 160);
        printf("Uso: lexico.exe archivo_entrada archivo_salida\n");
        return 1;
    }
    
    else if (argc == 2){
        printf("Error: Falta par%cmetro.\n", 160);
        printf("Uso: lexico.exe archivo_entrada archivo_salida\n");
        return 1;
    }
    
    else if (argc > 3){
        printf("Error: Demasiados par%cmetros.\n", 160);
        printf("Uso: lexico.exe archivo_entrada archivo_salida\n");
        return 1;
    }

    yyin = fopen(argv[1], "r");
    yyout = fopen(argv[2], "r");
    
    if (yyin == NULL){
        printf("Error: El archivo de entrada no existe.\n");
        return 1;
    }


    if (yyout != NULL){
        printf("Error: El archivo de salida ya existe.\n");
        fclose(yyout);
        return 1;
    }

    yyout = fopen(argv[2], "w");

    yylex();

    
    return 0;
}
#include "librerias.h"

int main(){
    // Variables generales
        int i;
        char opc1,opc2,opc3;
            /*
            *   opc1 -> Para repetir todo el programa
            *   opc2 -> Selección de entrada de texto
            *   opc3 -> Selección de guardado de traducción
            */
    // Fichero
        FILE *fp;
    // Cadena de caracteres
        char *morse,*fich;
        wchar_t *usu;
    // Tabla de equivalencias
        char **tabla;
            tabla=Asignacion();

    // Bucle principal
    do{
        usu=(wchar_t*)malloc(sizeof(wchar_t));
        morse=(char*)malloc(sizeof(char));
        fich=(char*)malloc(sizeof(char));
        do{
            printf("\n\t%cPor d%cnde vas a introducir el texto?",168,162);
            printf("\n\ta) Fichero      b) Consola\n\t--> ");
                fflush(stdin);
                scanf("%c",&opc2);
            if(opc2!='a' && opc2!='b'){
                printf("\n\tIntroduce una opci%cn correcta\n\n\t",162);
                system("pause");
                printf("\n");
            }
        }while(opc2!='a' && opc2!='b');
        switch(opc2){
            // Fichero
            case 'a':
                printf("\n\tIntroduce el nombre del fichero con extensi%cn",162);
                printf("\n\t--> ");
                    fflush(stdin);
                    LeerCadena(&fich);
                fp=fopen(fich,"r");
                fflush(stdin);
                LeerWCadenaFich(fp,&usu);
                fclose(fp);
                break;
            // Teclado
            case 'b':
                printf("\n\tIntroduce el texto");
                printf("\n\t--> ");
                    fflush(stdin);
                    LeerWCadena(&usu);
                break;
        } // switch

        // Traducción de la cadena y guardado de esta
        // Quitamos las tildes
        QuitarTildes(usu);
        // Pasamos a mayúsculas
        PasoMayus(usu);
        // Eliminamos los caracteres que no sean letras, numeros o ' '/'\n'
        EliminarCarac(&usu,wcslen(usu));
        // Hacemos la traducción
        Traduccion(&morse,usu,tabla);   // Imprime más caracteres de los deseados
        // Mostramos la traducción
        printf("\n\tEsta es la traducci%cn: ",162);
            puts(morse);

        // Opción de guardado
        do{
            printf("\n\t%cQuieres guardar la traducci%cn en un fichero?",168,162);
            printf("\n\ta) S%c      b) No\n\t--> ",161);
                fflush(stdin);
                scanf("%c",&opc3);
                tolower(opc3);
            if(opc3!='a' && opc3!='b'){
                printf("\n\tIntroduce una opci%cn correcta\n\n\t",162);
                system("pause");
                printf("\n");
            }
        }while(opc3!='a' && opc3!='b');
        if(opc3=='a'){
            printf("\n\tSe ha guardado en un fichero llamado \"traduccion.txt\"");
            printf("\n\tMu%cvelo a otro directorio o c%cmbiale el nombre, sino",130,160);
            printf("\n\tel pr%cximo fichero que se cree sobreescribir%c a este\n",162,160);
            ImprimirCadenaFich(morse,"traduccion.txt");
        }

        // Menú para la repetición
        do{
            printf("\n\t%cQuieres introducir otro texto?",168);
            printf("\n\ta) S%c      b) No\n\t--> ",161);
                fflush(stdin);
                scanf("%c",&opc1);
                tolower(opc1);
            if(opc1!='a' && opc1!='b'){
                printf("\n\tIntroduce una opci%cn correcta\n\n\t",162);
                system("pause");
                printf("\n");
            }
        }while(opc1!='a' && opc1!='b');

        // Liberación de espacio
        free(usu);
        free(morse);
        free(fich);

    }while(opc1=='a');
    return 0;
}

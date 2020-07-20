/* Funciones utilizadas en Traductor.c */

#include "librerias.h"

char** Asignacion(){
    int i,j=0;
    char c;
    FILE *fp;
    // Inicialización de la matriz
    char **tabla;
    tabla=(char**)malloc(38*sizeof(char*));
        for(i=0;i<38;i++){
            tabla[i]=(char*)malloc(sizeof(char));
        }
    /*
        POSICIONES DEL 0 AL 13 -> A a N
        POSICIÓN 14 -> Ñ
        POSICIONES DEL 15 AL 26 -> O a Z
        POSICIONES DEL 27 AL 36 -> 0 a 9
        POSICIÓN 37 -> ' '
    */
    // Guardado de las traducciones de los caracteres
    fp=fopen("morse.txt","r");
        if(fp==NULL){
            printf("\n\tEl fichero no existe");
            exit(-1);
        }
    // Traducciones de los caracteres
    i=0;
    while(!feof(fp)){
        j=0;
        while((c=getc(fp))!='\n' && !feof(fp)){
            tabla[i][j]=c;
            j++;
            tabla[i]=(char*)realloc(tabla[i],(j+1)*sizeof(char));
        }
        tabla[i][j]='\0';
        i++;
    }
    tabla[37]=(char*)realloc(tabla[37],2*sizeof(char));
        tabla[37][0]='/';
        tabla[37][1]='\0';
    return tabla;
}

void LeerCadena(char **cad){
    char c;
    int i=0;
    while((c=getchar())!='\n'){
        (*cad)[i]=c;
        i++;
        *cad=(char*)realloc(*cad,(i+1)*sizeof(char));
    }
    (*cad)[i]='\0';
}

void LeerWCadena(wchar_t **cad){
    wchar_t c;
    int i=0;
    while((c=(wchar_t)getwchar())!='\n'){
        (*cad)[i]=c;
        i++;
        *cad=(wchar_t*)realloc(*cad,(i+1)*sizeof(wchar_t));
    }
    (*cad)[i]='\0';
}

void LeerWCadenaFich(FILE *fp, wchar_t **cad){
    int i=0;
    while(!feof(fp)){
        (*cad)[i]=getwc(fp);
        i++;
        *cad=(wchar_t*)realloc(*cad,(i+1)*sizeof(wchar_t));
    }
    (*cad)[i]='\0';
}

void ImprimirWCadena(wchar_t *cad){
    int i=0;
    while(cad[i]!='\0'){
        putwchar(cad[i]);
        i++;
    }
    printf("\n");
}

void ImprimirCadenaFich(char *cad, char *fich){
    FILE *fp;
    fp=fopen(fich,"w");
    if(fp==NULL){
        exit(-1);
    }
    else{
        int i=0;
        while(cad[i]!='\0'){
            fputc(cad[i],fp);
            i++;
        }
        fclose(fp);
    }
}

void QuitarTildes(wchar_t *usu){
    int i=0;
    while(usu[i]!='\0'){
        switch(usu[i]){
            case 160:
            case 181:
                usu[i]='A';
                break;
            case 130:
            case 144:
                usu[i]='E';
                break;
            case 161:
            case 214:
                usu[i]='I';
                break;
            case 162:
            case 224:
                usu[i]='O';
                break;
            case 163:
            case 233:
            case 129:
            case 154:
                usu[i]='U';
                break;
            default:
                break;
        }
        i++;
    }
}

void EliminarCarac(wchar_t **usu, int tam){
    int i=0,j,found;
    while((*usu)[i]!=0){
        found=0;
        // Letras
        if(iswalnum((*usu)[i])){
            found=1;
        }
        else{
            // Ñ
            if((*usu)[i]==165){
                found=1;
            }
            else{
                // Otros
                if((*usu)[i]==32 || (*usu)[i]==10){
                    found=1;
                }
            }
        }
        if(found==0){
            j=i;
            tam--;
            while((*usu)[j]!=0){
                (*usu)[j]=(wchar_t)(*usu)[j+1];
                j++;
            }
            (*usu)=(wchar_t*)realloc((*usu),tam*sizeof(wchar_t));
        }
        i++;
    }
}

void PasoMayus(wchar_t *orig){
    int i,j,found;
    while(orig[i]!='\0'){
        orig[i]=towupper(orig[i]);
        i++;
    }
}

void Traduccion(char **morse, wchar_t *usu, char **tabla){
    int i=0,j=0,k,l;
        /*
        *   i -> posición de "usu"
        *   j -> posición de "morse"
        *   k -> posición de la traducción del caracter en la matriz
        *   l -> columnas para la fila k de la matriz
        */
    while(usu[i]!='\0'){
        // En caso de que el caracter sea una nueva línea, lo ponemos tal cual.
        if(usu[i]=='\n'){
            (*morse)[j]='\n';
            j++;
            (*morse)=(char*)realloc((*morse),(j+1)*sizeof(char));
        }
        else{
            // El código ASCII de la letra menos 65 para saber la posición
            if(usu[i]>=65 && usu[i]<=78)
                k=usu[i]-65;
            // Sabemos directamente que está en la posición 14
            if(usu[i]==165)
                k=14;
            // El código ASCII de la letra menos 64, ya que la Ñ tiene por código
            // el 165. Por tanto la posición de la O sería 'O'-65+1
            if(usu[i]>=79 && usu[i]<=90)
                k=usu[i]-64;
            // Los números empiezan en el 27, luego para el 0(48) tenemos que restar
            // 21
            if(usu[i]>=48 && usu[i]<=57)
                k=usu[i]-21;
            // El espacio está al final del todo
            if(usu[i]==' ')
                k=37;
            // Almacenamos el caracter traducido
            l=0;
            while(tabla[k][l]!='\0'){
                (*morse)[j]=tabla[k][l];
                j++;
                (*morse)=(char*)realloc((*morse),(j+1)*sizeof(char));
                l++;
            }
        }
        i++;
    }
    (*morse)[j]='\0';
}

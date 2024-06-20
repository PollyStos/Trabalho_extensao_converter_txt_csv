#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>



/*
Exemplo de dados para o arquivo .bim
00001011 00000001 11111000 00000101
00001012 00000001 11111000 01001100
00001013 00000001 11111000 00001010
00001014 00000001 11111000 01000100
00001015 00000001 11111000 00000100


Exemplo de dados para o arquivo .txt
11/01/2024 5.8
12/01/2024 7.5
13/01/2024 2.6
14/01/2024 4.5
15/01/2024 1.5
*/

typedef struct {
    char date[11]; // "dd/mm/yyyy"
    float value;
} Registro;


void clear(){
    #ifdef __linux__
        system("clear");
    #elif _WIN32
        system("cls");
    #endif    
}

// // FunÃ§Ã£o para validar se a entrada Ã© um nÃºmero entre 1 e 5
int validarOpcao(int num) {
    char input[100];
    int numero;
    int valid;

    while (1) {
        if (num==5) printf("Digite uma opcao: [1-5]: ");
        if (num==2) printf("Digite 1 para sim e 0 para nÃ£o.");

        if (fgets(input, sizeof(input), stdin) != NULL) {
            // Remove o caractere de nova linha, se presente
            input[strcspn(input, "\n")] = '\0';

            // Verifica se toda a entrada Ã© composta por dÃ­gitos
            valid = 1;
            for (int i = 0; input[i] != '\0'; i++) {
                if (!isdigit(input[i])) {
                    valid = 0;
                    break;
                }
            }
            
            // Converte para inteiro e verifica se estÃ¡ no intervalo desejado
            if (valid) {
                numero = atoi(input);
                if (numero >= 1 && numero <= num) {
                    return numero;
                }
            }
            printf("Opcao incorreta. \n");
        } else {
            printf("Erro ao ler entrada. ");
        }
    }
}

void lerArquivo (const char* nomeArquivo, const char* type, int* tamanho, const char** dados){
    //Polyana
    //O objetivo dessa funcao e abrir o arquivo para ler e pegar os dados que nele contem.
    FILE* file = NULL;
    if(strcmp(type, "bin") == 0){
        file = fopen(nomeArquivo, "rb"); // Abre o arquivo em modo binario de leitura
    }else{
        file = fopen(nomeArquivo, "r"); // Abre o arquivo em modo de  leitura de texto
    }
    char* buffer = NULL;
    if (file!= NULL) {
        // Move o ponteiro para o final do arquivo
        fseek(file, 0, SEEK_END);
        // Determina o tamanho do arquivo
        *tamanho = ftell(file);
        // Move o ponteiro de volta para o inÃ­cio do arquivo
        fseek(file, 0, SEEK_SET);

        // Aloca memÃ³ria para armazenar o conteÃºdo do arquivo
        *dados = (char*)malloc(*tamanho + 1);
        if (*dados) {
            // Le o conteudo do arquivo para o buffer
            fread(*dados, 1, *tamanho, file);
        }
        // Fecha o arquivo
        fclose(file);
    } else {
        printf("Erro ao abrir o arquivo '%s'.\n", nomeArquivo);
    }
    return;
}



// void createCSV (const char** dados){
//     printf("create CSV\n\n");
//     //Leticia 
//     //O objetivo dessa funÃ§Ã£o Ã© pegar os dados que chegarem pra ela via parÃ¢metro e criar um CSV.
// }

//Funcao para inserir uma nova lista
 void lotsInsert (){ 
    char NomeArq[16]; //23_12_2001.txt\0
    const char* type = "txt";
    int tamanho = 0;
    const char* dados = NULL;

    printf("Coloque o nome do seu arquivo que deseja abrir:\n");
    fgets(NomeArq, sizeof(NomeArq), stdin);
    NomeArq[strcspn(NomeArq, "\n")] = '\0';
    
    lerArquivo(NomeArq ,type, &tamanho, &dados);
    
    if(*dados != NULL){
    
        FILE* binFile = fopen("dados.bin", "ab");
        if (binFile == NULL) {
            perror("Erro ao abrir o arquivo binário para escrita");
            free(dados);
            return;
        }

        fwrite(dados, 1, tamanho, binFile);
        fclose(binFile);

        printf("Dados do arquivo '%s' inseridos com sucesso no arquivo 'dados.bin'.\n", NomeArq);
        free(dados);
        
    } else {
        printf("Erro ao ler os dados do arquivo '%s'.\n", NomeArq);
    }

    printf("Pressione Enter para continuar...");
    getchar();

//    //O objetivo dessa funcao e abrir o arquivo txt, pegar os dados dele e salvar em um arquivo .bin. Precisa se atentar ao formato do nome do arquivo txt. Se ele vier no formato dia_mes_ano.txt, faca uma rotina que verifica somente qual e o mes e qual e o ano para verificar se existe informacoes ja salvas para esse mes. Se existir imprimir a mensagem "Ja existem dados para esse mes. Deseja sobrescrever?\n" e chama a funcao validar_opcao(2) exatamente dessa forma.

//     // Apos finalizacao da insercao imprimir a mensagem "Dados {nome do arquivo} inseridos com sucesso no arquivo dados.bin"
    return;
 }


<<<<<<< HEAD
 void lotsDelete (){
//gabriel
    printf("Digite a data que deseja excluir 'mm/aaaa':\n\n");
      getchar();
    
// / Definicao da estrutura do registro
// typedef struct {
//     char data[11]; // Data no formato "YYYY-MM-DD"
//     int valor;     // Um valor inteiro
// } Registro;

// // Função para verificar se um registro pertence ao mês e ano especificados
// int pertenceAoMesAno(Registro *registro, int mes, int ano) {
//     struct tm tm;
//     memset(&tm, 0, sizeof(struct tm));
//     strptime(registro->data, "%Y-%m-%d", &tm);
//     return (tm.tm_mon + 1 == mes && tm.tm_year + 1900 == ano);
// }
=======

//gabriel
    
int pertenceAoMesAno(Registro *registro, int mes, int ano) {
    struct tm tm;
    memset(&tm, 0, sizeof(struct tm));
    strptime(registro->data, "%Y-%m-%d", &tm);
    return (tm.tm_mon + 1 == mes && tm.tm_year + 1900 == ano);
}

void lotsDelete() {
    printf("Digite a data que deseja excluir 'mm/aaaa': ");
    char input[10];
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';
>>>>>>> 90b1e32f744faf51a9c542ed061a282465ffe5f2

    int mes, ano;
    sscanf(input, "%d/%d", &mes, &ano);

    FILE* dados = fopen("dados.bin", "rb");
    FILE* backup = fopen("backup.bin", "wb");
    if (!dados || !backup) {
        perror("Erro ao abrir os arquivos");
        if (dados) fclose(dados);
        if (backup) fclose(backup);
        return;
    }

    Registro registro;
    int registrosApagados = 0;

    while (fread(&registro, sizeof(Registro), 1, dados)) {
        struct tm tm;
        memset(&tm, 0, sizeof(struct tm));
        strptime(registro.date, "%d/%m/%Y", &tm);
        if (tm.tm_mon + 1 != mes || tm.tm_year + 1900 != ano) {
            fwrite(&registro, sizeof(Registro), 1, backup);
        } else {
            registrosApagados++;
        }
    }

    fclose(dados);
    fclose(backup);

    remove("dados.bin");
    rename("backup.bin", "dados.bin");

    printf("%d registros foram apagados.\n", registrosApagados);
}



    //O objetivo dessa funÃ§Ã£o Ã© pegar todos os dados do arquivo dados.bin, criar uma cÃ³pia chamada backup.bin e passar para ele todos os dados que NÃƒO estÃ£o contidos no mes informado. Ex: se foi informado 04/2024 entÃ£o tudo o que nÃ£o for de abril deve ser salvo no arquivo backup.bin. ApÃ³s isso, ele deve excluir o arquivo dados.bin e criar um novo com os dados do arquivo backup.bin

    // ao final ele deve imprimir uma mensagem informando quantos registros foram apagados.

//  }
 
//  void lotsSum(){
//     // funcao para validar se o arquivo dados.bin existe.
//     int tamanho = 0;
//     char* dados = lerArquivo("dados","bin", &tamanho);
//     if(!dados){
//         printf("Alimente o Banco de Dados antes utilizando a opcao 1 do menu\n\n");
//         return 0;
//     }
//     return 0;

//     //O objetivo dessa funÃ§Ã£o Ã© pegar os dados do arquivo dados.bin e somar tudo que foi arrecadado de oleo dentro de cada mes e chamar a funcao de criar csv enviando como parÃ¢mentro o mes e a soma. O nome desse arquivo deve ser somatorio
//  }

// //FunÃ§Ã£o para listar os dados na tela
void lotsList(){
    //Polyana
    // funcao para validar se o arquivo dados.bin existe.
    const char* nomeArquivo = "dados.bin";
    const char* type = "bin";
    int tamanho = 0;
    const char* dados = NULL;

     //O objetivo dessa funcao e pegar os dados do arquivo dados.bin e listar na tela e depois chamar a funcao que ira criar um arquivo CSV com esses dados. Passe os dados do arquivo bin como parÃ¢metro para a funÃ§Ã£o que irÃ¡ criar o CSV. O nome desse arquivo deve ser todos_registros
    lerArquivo(nomeArquivo ,type, &tamanho, &dados);

    if(dados == NULL || dados[0] == '\0'){
        printf("Alimente o Banco de Dados antes utilizando a opcao 1 do menu\n\n");
    }else{
        printf("Conteudo:\n%s\n", dados);
    }
    printf("Pressione Enter para continuar...");
    getchar();
    // createCSV(&dados);
    // no final imprimir uma mensagem contendo a quantidade de registros que foram criados
    free(dados);
    return;
}

int main(int argc, char *argv[]) {
     printf("%d %s\n",argc, argv[0]);
   
     if (argc == 2) printf("%d %s %s\n",argc, argv[0], argv[1]);
   
     if (argc == 3) printf("%d %s %s %s\n",argc, argv[0], argv[1],argv[2]);
   
     clear();      
     
     int opcao=-1;
     while (opcao!=5){    
       do{    
            clear();
            printf("****************************\n");
            printf(" 1 - Inserir lote           \n");
            printf(" 2 - Eliminar lote          \n");
            printf(" 3 - Somatorio mensal (csv) \n");
            printf(" 4 - Listagem (csv)         \n");
            printf(" 5 - Encerrar               \n");              
            printf("****************************\n");
            opcao = validarOpcao(5);
           
       }while(opcao < 1 || opcao > 5);
       switch(opcao){
           
           case 1: 
            //Inserir lotes
            lotsInsert();
            break;
                 
           case 2: 
           //Eliminar lotes
           lotsDelete();
            break;  
                 
           case 3:
            //Somar total do mes
            // lotsSum();
            break;
                 
           case 4: 
            //Listar lotes e criar arquivo CSV
            lotsList();
            break;
                 
           case 5: 
            printf("Saindo....");
            return 0;

           default:
            printf("Opcao invÃ¡lida. Tente novamente!!!!\n\n");
            break;
        }        
    }
}

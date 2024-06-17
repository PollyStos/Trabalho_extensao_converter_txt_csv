#include <stdio.h>
#include <string.h>
#include <stdlib.h>



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


void clear(){
    #ifdef __linux__
        system("clear");
    #elif _WIN32
        system("cls");
    #endif    
}

// Função para validar se a entrada é um número entre 1 e 5
int validarOpcao(int num) {
    char input[100];
    int numero;
    int valid;

    while (1) {
        if (num==5) printf("Digite uma opcao: [1-5]: ");
        if (num==2) printf("Digite 1 para sim e 0 para não.");

        if (fgets(input, sizeof(input), stdin) != NULL) {
            // Remove o caractere de nova linha, se presente
            input[strcspn(input, "\n")] = '\0';

            // Verifica se toda a entrada é composta por dígitos
            valid = 1;
            for (int i = 0; input[i] != '\0'; i++) {
                if (!isdigit(input[i])) {
                    valid = 0;
                    break;
                }
            }
            
            // Converte para inteiro e verifica se está no intervalo desejado
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

void lerArquivo(const char* nomeArquivo,const char* type, size_t* tamanho,const char** dados){
    //Polyana
    //O objetivo dessa função é abrir o arquivo para ler e pegar os dados que nele contem.
    FILE* file = NULL;
    if(strcmp(type, "bin") == 0){
        file = fopen(nomeArquivo, "rb"); // Abre o arquivo em modo binário de leitura
    }else{
        file = fopen(nomeArquivo, "r"); // Abre o arquivo em modo de  leitura de texto
    }
    char* buffer = NULL;
    if (file!= NULL) {
        // Move o ponteiro para o final do arquivo
        fseek(file, 0, SEEK_END);
        // Determina o tamanho do arquivo
        *tamanho = ftell(file);
        // Move o ponteiro de volta para o início do arquivo
        fseek(file, 0, SEEK_SET);

        // Aloca memória para armazenar o conteúdo do arquivo
        buffer = (char*)malloc(*tamanho);
        if (buffer) {
            // Lê o conteúdo do arquivo para o buffer
            fread(buffer, 1, *tamanho, file);
        }
        // Fecha o arquivo
        fclose(file);
        *dados = buffer;
    } else {
        printf("Erro ao abrir o arquivo '%s'.\n", nomeArquivo);
    }
    return;
}

void createCSV (const char** dados){
    printf("create CSV\n\n");
    //Leticia 
    //O objetivo dessa função é pegar os dados que chegarem pra ela via parâmetro e criar um CSV.
}

//Funcao para inserir uma nova lista
 void lotsInsert (){ 
    char NomeArq[15]; //23_12_2001.txt\0
    const char* type = "txt";
    size_t tamanho = 0;
    const char* dados = NULL;

    printf("Coloque o nome do seu arquivo que deseja abrir:");
    fgets(NomeArq, sizeof(NomeArq), stdin);
    NomeArq[strcspn(NomeArq, "\n")] = '\0';
    printf(NomeArq);

    lerArquivo(NomeArq ,type, &tamanho, &dados);
    printf(dados);
    


   //O objetivo dessa função é abrir o arquivo txt, pegar os dados dele e salvar em um arquivo .bin. Precisa se atentar ao formato do nome do arquivo txt. Se ele vier no formato dia_mes_ano.txt, faça uma rotina que verifica somente qual é o mes e qual é o ano para verificar se existe informações já salvas para esse mes. Se existir imprimir a mensagem "Já existem dados para esse mês. Deseja sobrescrever?\n" e chama a funcao validar_opcao(2) exatamente dessa forma.

    // Apos finalizacao da insercao imprimir a mensagem "Dados {nome do arquivo} inseridos com sucesso no arquivo dados.bin"
    free(dados);
 }

 void lotsDelete (){
    printf("Digite a data que deseja excluir 'mm/aaaa':\n\n");
    
    
//gabriel
// Estrutura do registro, incluindo a data no formato MM/YYYY
typedef struct {
    char data[8]; // formato MM/YYYY
    // outros campos do registro
    char dados[256];
} Registro;

void filtrarMes(const char* mesAno) {
    FILE *fpDados, *fpBackup;
    Registro reg;
    int registrosApagados = 0;

    // Abrir o arquivo original
    fpDados = fopen("dados.bin", "rb");
    if (fpDados == NULL) {
        perror("Erro ao abrir dados.bin");
        exit(EXIT_FAILURE);
    }

    // Criar o arquivo de backup
    fpBackup = fopen("backup.bin", "wb");
    if (fpBackup == NULL) {
        perror("Erro ao criar backup.bin");
        fclose(fpDados);
        exit(EXIT_FAILURE);
    }

    // Ler e copiar registros, exceto os do m�s informado
    while (fread(&reg, sizeof(Registro), 1, fpDados)) {
        if (strncmp(reg.data, mesAno, 7) != 0) { // Compara apenas MM/YYYY
            fwrite(&reg, sizeof(Registro), 1, fpBackup);
        } else {
            registrosApagados++;
        }
    }

    fclose(fpDados);
    fclose(fpBackup);

    // Excluir o arquivo original
    if (remove("dados.bin") != 0) {
        perror("Erro ao excluir dados.bin");
        exit(EXIT_FAILURE);
    }

    // Renomear o arquivo de backup para o nome original
    if (rename("backup.bin", "dados.bin") != 0) {
        perror("Erro ao renomear backup.bin");
        exit(EXIT_FAILURE);
    }

    // Imprimir a quantidade de registros apagados
    printf("Registros apagados: %d\n", registrosApagados);
}

int main() {
    // Exemplo de uso da fun��o
    filtrarMes("04/2024");
    return 0;
}

    //O objetivo dessa função é pegar todos os dados do arquivo dados.bin, criar uma cópia chamada backup.bin e passar para ele todos os dados que NÃO estão contidos no mes informado. Ex: se foi informado 04/2024 então tudo o que não for de abril deve ser salvo no arquivo backup.bin. Após isso, ele deve excluir o arquivo dados.bin e criar um novo com os dados do arquivo backup.bin

    // ao final ele deve imprimir uma mensagem informando quantos registros foram apagados.

 }
 
//  void lotsSum(){
//     // funcao para validar se o arquivo dados.bin existe.
//     size_t tamanho = 0;
//     char* dados = lerArquivo("dados","bin", &tamanho);
//     if(!dados){
//         printf("Alimente o Banco de Dados antes utilizando a opcao 1 do menu\n\n");
//         return 0;
//     }
//     return 0;

//     //O objetivo dessa função é pegar os dados do arquivo dados.bin e somar tudo que foi arrecadado de oleo dentro de cada mes e chamar a funcao de criar csv enviando como parâmentro o mes e a soma. O nome desse arquivo deve ser somatorio
//  }

//Função para listar os dados na tela
void lotsList(){
    //Polyana
    // funcao para validar se o arquivo dados.bin existe.
    const char* nomeArquivo = "dados.bin";
    const char* type = "bin";
    size_t tamanho = 0;
    const char* dados = NULL;

 //O objetivo dessa funcao e pegar os dados do arquivo dados.bin e listar na tela e depois chamar a funcao que ira criar um arquivo CSV com esses dados. Passe os dados do arquivo bin como parâmetro para a função que irá criar o CSV. O nome desse arquivo deve ser todos_registros
    lerArquivo(nomeArquivo ,type, &tamanho, &dados);

    if(dados == NULL || dados[0] == '\0'){
        printf("Alimente o Banco de Dados antes utilizando a opcao 1 do menu\n\n");
    }else{
    printf("Conteudo:\n%s\n", dados);
    }

    createCSV(&dados);
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
            // clear();
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
            printf("Opcao inválida. Tente novamente!!!!\n\n");
            break;
        }        
    }
}

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void clear(){
    #ifdef __linux__
        system("clear");
    #elif _WIN32
        system("cls");
    #endif    
}

// Função para validar se a entrada é um número entre 1 e 5
int validar_opcao(int num) {
    char input[100];
    int numero;
    int valid;

    while (1) {
        if (num==5) printf("Digite uma opcao: [1-5]: ");
        if (num==2) printf("Digite 1 para sim e 0 para não.")

        if (fgets(input, sizeof(input), stdin) != NULL) {
            // Remove o caractere de nova linha, se presente
            input[strcspn(input, "\n")] = 0;

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

bool ValidaBin(){
    //O objetivo dessa função é verificar se existe um arquivo .bin. Se existir retorna true, se não deve retornar false. (return true ou return false)
}

void CreateCSV (){
    //O objetivo dessa função é pegar os dados que chegarem pra ela via parâmetro e criar um CSV.
}

//Funcao para inserir uma nova lista
 void LotsInsert (){
   //O objetivo dessa função é abrir o arquivo txt, pegar os dados dele e salvar em um arquivo .bin. Precisa se atentar ao formato do nome do arquivo txt. Se ele vier no formato dia_mes_ano.txt, faça uma rotina que verifica somente qual é o mes e qual é o ano para verificar se existe informações já salvas para esse mes. Se existir imprimir a mensagem "Já existem dados para esse mês. Deseja sobrescrever?\n" e chama a funcao validar_opcao(2) exatamente dessa forma.

    // Apos finalizacao da insercao imprimir a mensagem "Dados {nome do arquivo} inseridos com sucesso no arquivo dados.bin"
 }

 void LotsDelete (){
    printf("Digite a data que deseja excluir 'mm/aaaa':");

    //O objetivo dessa função é pegar todos os dados do arquivo dados.bin, criar uma cópia chamada backup.bin e passar para ele todos os dados que NÃO estão contidos no mes informado. Ex: se foi informado 04/2024 então tudo o que não for de abril deve ser salvo no arquivo backup.bin. Após isso, ele deve excluir o arquivo dados.bin e criar um novo com os dados do arquivo backup.bin

    // ao final ele deve imprimir uma mensagem informando quantos registros foram apagados.

 }

 void LotsSum(){
    // funcao para validar se o arquivo dados.bin existe.
    bool valida = ValidaBin();
    if(!valida){
        printf("Alimente o Banco de Dados antes utilizando a opcao 1 do menu");
        return 0;
    }

    //O objetivo dessa função é pegar os dados do arquivo dados.bin e somar tudo que foi arrecadado de oleo dentro de cada mes e chamar a funcao de criar csv enviando como parâmentro o mes e a soma. O nome desse arquivo deve ser somatorio
 }

//Função para listar os dados na tela
void LotsList(){
    // funcao para validar se o arquivo dados.bin existe.
    bool valida = ValidaBin();
    if(!valida){
        printf("Alimente o Banco de Dados antes utilizando a opcao 1 do menu");
        return 0;
    }
 //O objetivo dessa funcao e pegar os dados do arquivo dados.bin e listar na tela e depois chamar a funcao que ira criar um arquivo CSV com esses dados. Passe os dados do arquivo bin como parâmetro para a função que irá criar o CSV. O nome desse arquivo deve ser todos_registros

    CreateCSV();
// no final imprimir uma mensagem contendo a quantidade de registros que foram criados
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
            opcao = validar_opcao(5);
           
       }while(opcao < 1 || opcao > 5);
       
       switch(opcao){
           
           case 1: 
            //Inserir lotes
            LotsInsert();
            break;
                 
           case 2: 
           //Eliminar lotes
           LotsDelete();
            break;  
                 
           case 3:
            //Somar total do mes
            LotsSum();
            break;
                 
           case 4: 
            //Listar lotes e criar arquivo CSV
            LotsList();
            break;
                 
           case 5: 
            printf("Saindo....");
            return 0;

           default:
            printf("Opcao inválida. Tente novamente!!!!");
            break;
            
         
        }        
    }
}
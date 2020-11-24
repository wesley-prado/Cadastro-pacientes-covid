#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>

char cadastro_login[255],
    cadastro_senha[255],
    login[255],
    senha[255],
    nome_aux[255], 
    data_de_nascimento[10], 
    *nome_do_paciente = NULL, 
    cep[9], estado[2],
    *cidade = NULL, *bairro = NULL, *rua = NULL, numero_da_casa[4], cpf[14], telefone[14], email[255], data_do_diagnostico[10], *comorbidades;
int dia, mes, ano, ch, idade, exit_flag = NULL, logged = 0;

size_t size, len;
FILE *cadastro_paciente;

char *stringDinamico(char *str)
{
    len = 0;
    size = 0;

    while ((ch = getchar()) != EOF && ch != '\n')
    {
        if (len + 1 >= size)
        {
            size = size * 2 + 1;
            str = realloc(str, sizeof(char) * size);
        }
        str[len++] = ch;
    }

    if (str != NULL)
    {
        str[len] = '\0';
    }
    return str;
}

void reset(void)
{
    fflush(stdin);
    system("cls");
}

void main(void)
{
    time_t ts = time(NULL);
    struct tm *ct = localtime(&ts);

    do
    {

        if (!logged)
        {
            printf("Cadastro de usuario\nDigite um login\n");
            scanf("%s", cadastro_login);
            fflush(stdin);

            printf("Digite uma senha:\n");
            scanf("%s", cadastro_senha);
            fflush(stdin);

            system("cls");
            printf("Faca login no sistema.\n");
            do
            {
                printf("Digite seu login\n");
                scanf("%s", login);
                fflush(stdin);

                printf("Digite sua senha\n");
                scanf("%s", senha);
                fflush(stdin);

                if (strcmp(senha, cadastro_senha) != 0 || strcmp(login, cadastro_login) != 0)
                {
                    printf("Login ou senha inv�lidos.\n");
                }
                system("cls");
            } while (strcmp(senha, cadastro_senha) != 0 || strcmp(login, cadastro_login) != 0);
        }

        logged = 1;

        printf("Preencha os campos sem acentuacao.\n\n");
        printf("Cadastro de paciente\nDigite o nome completo:\n");

        nome_do_paciente = stringDinamico(nome_do_paciente);

        memcpy(nome_aux, nome_do_paciente, sizeof(nome_aux));

        cadastro_paciente = fopen(strcat(nome_aux, ".txt"), "w+");
        if (!cadastro_paciente)
        {
            perror("Falha ao criar o arquivo\n");
            exit(1);
        }

        memset(nome_aux, 0, sizeof(nome_aux));

        rewind(cadastro_paciente);

        printf("Digite a data de nascimento (formato dd/mm/aaaa):\n");
        scanf("%02d/%02d/%4d", &dia, &mes, &ano);

        idade = (ct->tm_year + 1900) - ano;
        if ((ct->tm_mon + 1) < mes)
        {
            idade--;
        }
        else if ((ct->tm_mon + 1) == mes && ct->tm_mday < dia)
        {
            idade--;
        }

        printf("CPF (formato xxx.xxx.xxx-xx):\n");
        scanf("%s", cpf);
        fflush(stdin);

        printf("Telefone (formato (11)98899-9999):\n");
        scanf("%s", telefone);
        fflush(stdin);

        printf("Email:\n");
        scanf("%s", email);
        fflush(stdin);

        printf("Data do diagnostico (formato dd/mm/aaaa):\n");
        scanf("%s", data_do_diagnostico);
        fflush(stdin);

        printf("Comorbidades (separados por virgula):\n");
        comorbidades = stringDinamico(comorbidades);
        fprintf(cadastro_paciente, "Nome: %s\nData de nascimento: %02d/%02d/%4d\n", nome_do_paciente, dia, mes, ano);

        if (idade >= 65)
        {
            printf("Paciente maior de 65 anos. Cadastre o CEP\n");
            scanf("%s", cep);

            printf("Complete os seguintes campos:\n");

            printf("Estado (Sigla):\n");
            scanf("%s", estado);
            fflush(stdin);

            printf("Cidade:\n");
            cidade = stringDinamico(cidade);

            printf("Bairro:\n");
            bairro = stringDinamico(bairro);

            printf("Rua:\n");
            rua = stringDinamico(rua);

            printf("N�mero:\n");
            scanf("%s", numero_da_casa);
            fflush(stdin);

            fprintf(cadastro_paciente, "Idade: %d anos\nCEP: %s\nEstado: %s\nCidade: %s\nBairro: %s\nRua: %s\nN�mero: %s\n", idade, cep, estado, cidade, bairro, rua, numero_da_casa);
        }

        fprintf(cadastro_paciente, "CPF: %s\nTelefone: %s\nEmail: %s\nData do diagnostico: %s\nComorbidades: %s", cpf, telefone, email, data_do_diagnostico, comorbidades);

        fclose(cadastro_paciente);

        printf("Aperte qualquer tecla para continuar ou ESC para sair.\n");
        exit_flag = getch();
        reset();

    } while (exit_flag != 27);
}

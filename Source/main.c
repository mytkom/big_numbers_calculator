#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


#define MAX_SYSTEM 16


char* stringConvertion(char* converted_number, size_t converted_number_size,int from, int to);
char* stringModulo(char* modulant, size_t modulant_size, char* modulor, size_t modulor_size, int n);
char* stringPower(char* base, size_t base_size, char* exponent, size_t exponent_size, int n);
char* stringDivision(char* divident, size_t divident_size, char* divisor, size_t divisor_size, int n);
char* stringMultiplication(char * x, size_t s_x, char * y, size_t s_y, int n);
char* stringAddition(char * x, size_t s_x, char * y, size_t s_y, int n);
char* stringSubstraction(char * x, size_t s_x, char * y, size_t s_y, int n);
int loadNumber(char** result, size_t* index, size_t* size, FILE** input, int n);
int stringComparision(char* one, char* two, int size);
size_t stringLength(char* string);
char* dec_to_base(int number, int base);

int c_to_n[100];
int n_to_c[100];

int main(int argc, char* argv[])
{
    char* file_in = "";
    char* file_out = "";
    int few_files = 0, op_i = 0;
    char temp_ch, operation;
    int op = 0;
    int n_system = 0;
    FILE* f_input, * f_result;


    if (argc == 1) 
    {
        file_in = "../Input/input.txt";
        file_out = "output.txt";
    }
    else if (argc == 2 && (strcmp(argv[1], "--help") == 0))
    {
        FILE* readme;
        if (!fopen_s(&readme, "../Doc/readme.txt", "r"))
        {
            char a;
            while ((a = getc(readme)) != EOF) printf("%c", a);
            fclose(readme);
            return 0;
        }
        else 
        {
            printf("Blad: Nie mozna znalezc pliku readme.txt!\n");
            return 0;
        }
    }
    else if (argc == 3 && (strcmp(argv[1],"-p") == 0))
    {
        file_in = argv[2];
        few_files = 1;
    }
    else if (argc == 4 && (strcmp(argv[1],"-n") == 0))
    {
        file_in = argv[2];
        file_out = argv[3];
    }
    else
    {
        printf("Program zostal wywolany niepoprawnie!\n");
        return 0;
    }

    //printf("file_in: %s\n", file_in);
    //printf("file_out: %s\n", file_out);

    for(size_t i = 0; i < 10; i++)
    {
        c_to_n[48+i] = i;
    }
    for(size_t i = 10; i <= 46; i++)
    {
        c_to_n['A' + i - 10] = i;
    }
    for(size_t i = 0; i < 10; i++)
    {
        n_to_c[i] = '0' + i;
    }
    for(size_t i = 0; i <= 36; i++)
    {
        n_to_c[i + 10] = 'A' + i;
    }

 
    if (fopen_s(&f_input, file_in, "r")) 
    {
        printf("Nie mozna otworzyc pliku wejsciowego: %s\n", file_in);
        return 0;
    }
           
    if(fopen_s(&f_result, file_out, "w+") && (!few_files))
    {
        printf("Nie mozna otworzyc/utworzyc pliku wyjsciowego: %s\n", file_out);
        return 0;
    }



    while(1)
    {
        op_i++;
        op = 0;
        n_system = 0;

        //wczytywanie operacji
        if((operation = getc(f_input)) == EOF)
        {
            break;
        }

        if(operation >= '1' && operation <= '9')
        {
            op = c_to_n[operation];
            while((operation = getc(f_input)) != ' ')
            {
                op = 10*op + c_to_n[operation];
            }
        }
        else
        {
            if (getc(f_input) == EOF) break;
        }


        //iterator
        int i = 0;

        //wczytywanie systemu liczbowego
        while((temp_ch = getc(f_input)) != '\n')
        {
            n_system = n_system*10 + c_to_n[temp_ch];
        }

        if(op > MAX_SYSTEM || n_system > MAX_SYSTEM)
        {
            printf("%d %d\nPodany system liczbowy nie jest obslugiwany!\nMaksymalnym obslugiwany system liczbowy ma podstawe: %d\n", op, n_system, MAX_SYSTEM);
            fprintf(f_result ,"%d %d\nPodany system liczbowy nie jest obslugiwany!\nMaksymalnym obslugiwany system liczbowy ma podstawe: %d\n", op, n_system, MAX_SYSTEM);
            break;
        }

       //wypisywanie systemu(debug)
        //printf("%d", n_system);

        //skip linie
        if (getc(f_input) == EOF) break;
        
        //podział na operacje jedno i dwu argumentowe(różnica we wczytywaniu)
        if(op == 0)
        {
            if(operation == '*' || operation == '+' || operation == '/' || operation == '^' || operation == '%')
            {
                char* num_one = NULL, * num_two = NULL, * result = NULL;
                size_t size_one = 0, index_one = 0, size_two = 0, index_two = 0;

                if (loadNumber(&num_one, &index_one, &size_one, &f_input, n_system))
                    goto end;
                

                //skip spacje
                if (getc(f_input) == EOF) break;

                if (loadNumber(&num_two, &index_two, &size_two, &f_input, n_system))
                {
                    free(num_one);
                    goto end;
                }

                //check input
                //printf("num_one: %s\nnum_two: %s\n", num_one, num_two);   


                switch(operation)
                {
                    case '+':
                   
                    {
                        
                        //add num_one and num_two
                        result = stringAddition(num_one, size_one, num_two, size_two, n_system);

                        break;
                    }
                    case '*':
                   
                    {
                        
                        if(size_one > size_two) result = stringMultiplication(num_one, size_one, num_two, size_two, n_system);
                        else result = stringMultiplication(num_two, size_two, num_one, size_one, n_system);

                        break;
                    }
                    case '^':
                   
                    {

                        result = stringPower(num_one, size_one, num_two, size_two, n_system);

                        break;
                    }
                    case '/':
                   
                    {
                        result = stringDivision(num_one, size_one, num_two, size_two, n_system);

                        break;
                    }
                    case '%':
                   
                    {
                        result = stringModulo(num_one, size_one, num_two, size_two, n_system);

                        break;
                    }
                }
                if (few_files) 
                {
                    int temp = op_i;
                    int op_i_length = 0;
                    while (temp > 0) 
                    {
                        temp /= 10;
                        op_i_length++;
                    }
                    char* file_out = (char*) calloc(op_i_length + 5, sizeof(char));
                    file_out[op_i_length + 3] = 't';
                    file_out[op_i_length + 2] = 'x';
                    file_out[op_i_length + 1] = 't';
                    file_out[op_i_length] = '.';
                    int g = 0;
                    temp = op_i;
                    for (g = op_i_length - 1; g >= 0; g--)
                    {
                        file_out[g] = '0' + (temp % 10);
                        temp /= 10;
                    }
                    FILE* f_res = NULL;
                    //printf("%s\n", file_out);
                    if(!fopen_s(&f_res, file_out, "w+"))
                        fprintf(f_res, "%c %d\n\n%s\n\n%s\n\n%s\n\n", operation, n_system, num_one, num_two, result);
                    fclose(f_res);
                    free(file_out);
                }
                else 
                {
                    fprintf(f_result, "%c %d\n\n%s\n\n%s\n\n%s\n\n", operation, n_system, num_one, num_two, result);
                }
                //printf("result: %s\n", result);  

                if (getc(f_input) == EOF) break;
                if (getc(f_input) == EOF) break;



                free(num_one);
                free(num_two);

                free(result);
                
            }
            else printf("Blad: nie ma takiej operacji jak \"%c\"\n", operation);
        }
        else if(op > 0)
        {
                
                char * num = NULL, *tmp = NULL;
                size_t index = 0, size = 0;

                if (loadNumber(&num, &index, &size, &f_input, op))
                    goto end;


                //printf("num: %s\n", num);

                if(num[0] == '0')
                {
                    tmp = calloc(2, sizeof(char));
                    tmp[0] = '0';
                }
                else
                    tmp = stringConvertion(num, size, op, n_system);


                if (few_files)
                {
                    int temp = op_i;
                    int op_i_length = 0;
                    while (temp > 0)
                    {
                        temp /= 10;
                        op_i_length++;
                    }
                    char* file_out = (char*)calloc(op_i_length + 5, sizeof(char));
                    file_out[op_i_length + 3] = 't';
                    file_out[op_i_length + 2] = 'x';
                    file_out[op_i_length + 1] = 't';
                    file_out[op_i_length] = '.';
                    int g = 0;
                    temp = op_i;
                    for (g = op_i_length - 1; g >= 0; g--)
                    {
                        file_out[g] = '0' + (temp % 10);
                        temp /= 10;
                    }
                    FILE* f_res = NULL;
                    printf("%s\n", file_out);
                    if(!fopen_s(&f_res, file_out, "w+"))
                     fprintf(f_res, "%d %d\n\n%s\n\n%s\n\n", op, n_system, num, tmp);
                    fclose(f_res);
                    free(file_out);
                }
                else
                {
                    fprintf(f_result, "%d %d\n\n%s\n\n%s\n\n", op, n_system, num, tmp);
                }

                //printf("result: %s\n", tmp);



                free(tmp);

                if (getc(f_input) == EOF) break;
                if (getc(f_input) == EOF) break;

                free(num);
        }

        printf("Operacja %d wykonana pomyslnie\n", op_i);
    }
    end:
    fclose(f_input);
    fclose(f_result);



    return 0;
}

//wolna konwersja
/*char* stringConvertion(char* converted_number, size_t converted_number_size, int from, int to)
{
    char* result, *divisor;
    divisor = dec_to_base(to, from); 
    size_t result_size, divisor_size;
    divisor_size = stringLength(divisor);
    result = (char*) calloc(1, sizeof(char));
    result_size = 1;

    char* local_converted_number;
    size_t local_converted_number_size = converted_number_size;
    local_converted_number = (char*) calloc(local_converted_number_size, sizeof(char));
    for(int i = 0; i < local_converted_number_size - 1; i++) local_converted_number[i] = converted_number[i];

    while(local_converted_number[0] != '0')
    {
        char* temp;
        temp = stringModulo(local_converted_number, local_converted_number_size, divisor, divisor_size, from);
        size_t temp_size = stringLength(temp);

        int letter = 0;
        for(int i = 0; i < temp_size - 1; i++)
        {  
            letter += ((int) c_to_n[temp[i]]) * ((int) pow(from, temp_size - 2 - i));
        }

        char* stringLetter = dec_to_base(letter, to);
        size_t stringLetter_size = stringLength(stringLetter);


        char* temp2 = NULL;
        temp2 = (char*) calloc(result_size + stringLetter_size - 1, sizeof(char));
        for(int i = 0; i < result_size - 1; i++) temp2[stringLetter_size - 1 + i] = result[i];
        for(int i = 0; i < stringLetter_size - 1; i++) temp2[i] = stringLetter[i];
        free(result);
        result = temp2;
        result_size = stringLength(result);
        temp2 = NULL;

        char* temp3 = NULL;
        temp3 = stringDivision(local_converted_number, local_converted_number_size, divisor, divisor_size, from);
        free(local_converted_number);
        local_converted_number = temp3;
        local_converted_number_size = stringLength(local_converted_number);
        temp3 = NULL;

        free(stringLetter);
        free(temp);
    }

    free(divisor);
    free(local_converted_number);

    return result;
}*/

char* stringConvertion(char* converted_number, size_t converted_number_size, int from, int to)
{
    char* base = dec_to_base(from, to);
    char* result, *act_multiplier;
    size_t result_size, _size, act_multiplier_size, base_size;

    base_size = stringLength(base);

    result = (char*) calloc(2, sizeof(char));
    result[0] = '0';
    result_size = 2;

    act_multiplier = (char*) calloc(2, sizeof(char));
    act_multiplier[0] = '1';
    act_multiplier_size = 2;



    for(int i = converted_number_size - 2; i >= 0; i--)
    {
        if(converted_number[i] != '0')
        {
            char* num = dec_to_base(c_to_n[converted_number[i]], to);
            size_t num_size = stringLength(num);

            char* temp = NULL;
            if(num_size > act_multiplier_size) 
                temp = stringMultiplication(num, num_size, act_multiplier, act_multiplier_size, to);
            else 
                temp = stringMultiplication(act_multiplier, act_multiplier_size, num, num_size, to);

            size_t temp_size = stringLength(temp);

            char* temp2 = NULL;
            if(result_size > temp_size) 
                temp2 = stringAddition(result, result_size, temp, temp_size, to);
            else
                temp2 = stringAddition(temp, temp_size, result, result_size, to);
            free(result);
            result = temp2;
            temp2 = NULL;
            result_size = stringLength(result);

            free(temp);
            free(num);
        }


        char* temp3 = NULL;

        if(act_multiplier_size > base_size) 
            temp3 = stringMultiplication(act_multiplier, act_multiplier_size, base, base_size, to);
        else 
            temp3 = stringMultiplication(base, base_size, act_multiplier, act_multiplier_size, to);

        free(act_multiplier);
        act_multiplier = temp3;
        act_multiplier_size = stringLength(act_multiplier);
        temp3 = NULL;
    }

    free(base);
    free(act_multiplier);

    return result;
}

char* stringModulo(char* modulant, size_t modulant_size, char* modulor, size_t modulor_size, int n)
{
    if(modulor_size == 2 && modulor[0] == '0')
    {
        char* temp = "Blad: modulo przez 0";
        char* result;
        size_t len = stringLength(temp);
        result = calloc(len, sizeof(char));
        for(int i = 0; i < len; i++) result[i] = temp[i];
        return result;
    }
    else if(modulant_size < modulor_size)
    {
        char* local_modulant = (char*) calloc(modulant_size, sizeof(char));
        for(int i = 0; i < modulant_size; i++) local_modulant[i] = modulant[i];
        return local_modulant;
    }

    char* result = NULL, *division = NULL, *multiplication = NULL;

    division = stringDivision(modulant, modulant_size, modulor, modulor_size, n);
    size_t division_size = stringLength(division);


    if(modulor_size > division_size) 
        multiplication = stringMultiplication(modulor, modulor_size, division, division_size, n);
    else 
        multiplication = stringMultiplication(division, division_size, modulor, modulor_size, n);
    size_t multiplication_size = stringLength(multiplication);



    result = stringSubstraction(modulant, modulant_size, multiplication, multiplication_size, n);


    free(division);
    free(multiplication);

    return result;
}

char* stringPower(char* base, size_t base_size, char* exponent, size_t exponent_size, int n)
{
    if(exponent[0] == '0')
    {
        char* temp_one = NULL;
        temp_one = (char*) calloc(2, sizeof(char));
        temp_one[0] = '1';
        return temp_one;
    }
    else
    {
        char* result= NULL;
        result = (char*) calloc(2, sizeof(char));
        result[0] = '1';
        size_t result_size = 2;
        int ei = exponent_size - 2;
        for(int i = ei; i >= 0; i--)
        {
            int expo = (int) c_to_n[exponent[i]] * (int) pow((double) n, (double) ei - i);
            for(int j = expo; j > 0; j--)
            {
                char* temp = NULL;

                if(base_size >= result_size) 
                    temp = stringMultiplication(base, base_size, result, result_size, n);
                else 
                    temp = stringMultiplication(result, result_size, base, base_size, n);

                free(result);
                result = temp;
                result_size = stringLength(result);

                temp = NULL;
            }
        }
        return result;
    }
    
}

char* stringDivision(char* divident, size_t divident_size, char* divisor, size_t divisor_size, int n)
{
    if(divisor[0] == '0')
    {
        char* temp = "Blad: dzielenie przez 0";
        char* result;
        size_t len = stringLength(temp);
        result = calloc(len, sizeof(char));
        for(int i = 0; i < len; i++) result[i] = temp[i];
        return result;
    }
    char* result = NULL;
    result = (char*) calloc(2, sizeof(char));
    result[0] = '0';

    size_t result_size = 2;

    char* localDivident = NULL;
    localDivident = (char*) calloc(divident_size, sizeof(char));
    for(int i = 0; i < divident_size; i++)
        localDivident[i] = divident[i];

    size_t localDivident_size = divident_size;

    while(localDivident_size > divisor_size)
    {
        //making multiplicator
        size_t multiplicator_size = localDivident_size - divisor_size + 1;
        char* multiplicator = (char*) calloc(multiplicator_size, sizeof(char));
        multiplicator[0] = '1';
        for(int i = 1; i < multiplicator_size - 1; i++)
        {
            multiplicator[i] = '0';
        }

        //substracting multiplicator * divisor from divident
        char* temporaryPointer = NULL, *multiplicationPointer = NULL;

        if(multiplicator_size > divisor_size) multiplicationPointer = stringMultiplication(multiplicator, multiplicator_size, divisor, divisor_size, n);
        else multiplicationPointer = stringMultiplication(divisor, divisor_size, multiplicator, multiplicator_size, n);

        size_t multiplicationPointer_size = stringLength(multiplicationPointer);
        temporaryPointer = stringSubstraction(localDivident, localDivident_size, multiplicationPointer, multiplicationPointer_size, n);
        
        size_t temporaryPointer_size = stringLength(temporaryPointer);

        free(localDivident);
        localDivident = temporaryPointer;
        localDivident_size = temporaryPointer_size;

        temporaryPointer = stringAddition(result, result_size, multiplicator, multiplicator_size, n);
        temporaryPointer_size = stringLength(temporaryPointer);

        //free and zero all may-be-problematic values and pointers
        free(result);
        result = temporaryPointer;
        result_size = temporaryPointer_size;

        free(multiplicator);
        multiplicator = NULL;
        multiplicator_size = 0;

        free(multiplicationPointer);
        multiplicationPointer = NULL;
        multiplicationPointer_size = 0;

        temporaryPointer = NULL;
        temporaryPointer_size = 0;
    }

    if(localDivident_size == divisor_size)
    {
        int comparisionResult = stringComparision(localDivident, divisor, localDivident_size);
        if(comparisionResult >= 0)
        {
            for(int i = 1; i < n + 1; i++)
            {
                int done = 0;
                char* temporaryPointer = NULL;


                char* temp_i = NULL;
                temp_i = calloc(2, sizeof(char));
                temp_i[0] = n_to_c[i];

                temporaryPointer = stringMultiplication(divisor, divisor_size, temp_i, 2, n);

                size_t temporaryPointer_size = stringLength(temporaryPointer);

                int comp;
                if(temporaryPointer_size > localDivident_size) comp = 1;
                else comp = stringComparision(temporaryPointer, localDivident, localDivident_size);

                int b;
                if(comp == 1) b = 1;
                else if(comp == 0) b = 0;
                if(comp >= 0)
                {
                    char* temp_r = NULL, *temp_r2;
                    temp_r = calloc(2, sizeof(char));
                    temp_r[0] = n_to_c[i - b];
                    temp_r2 = stringAddition(result, result_size, temp_r, 2, n);
                    
                    size_t j = stringLength(temp_r2);

                    free(result);
                    result = temp_r2;
                    result_size = j;

                    free(temp_r);
                    done = 1;
                }
                
                free(temporaryPointer);
                free(temp_i);
                if(done) break;
            }
        }
        
    }

    free(localDivident);

    return result;
}

char* stringMultiplication(char * x, size_t s_x, char * y, size_t s_y, int n)
{
    char* result;
    size_t s_r;
    result = (char*) calloc(2, sizeof(char));
    result[0] = '0';
    result[1] = '\0';
    s_r = 2;
        
    for(int i = s_y - 2;i >= 0; i--)
    {
            
        char* temp = NULL, *temp2 = NULL;
        size_t s_t = s_x + 1 + s_y - 2 - i ;
        temp = (char*) calloc(s_t, 1);
        int temp_index = s_t - 1;
        temp[temp_index--] = '\0';
        for(int j = 0; j < s_y - i - 2; j++)
        {
            temp[temp_index--] = '0';
        }
            
        int b = 0, c = 0;
        for(int j = s_x - 2; j >= 0; j--)
        {
           b = c_to_n[x[j]] * c_to_n[y[i]] + c;
           if(b >= n)
           {
               c = (int) (b / n);
               b %= n;
           }
           else
           {
               c = 0;
           }
           temp[temp_index--] = n_to_c[b];
        }
        if(c > 0) temp[temp_index] = n_to_c[c];

        char* temporaryPointer = NULL;
        int i = -1;
        while(temp[++i] == 0){}
        if (i > 0)
        {
            temporaryPointer = (char *) calloc(s_t - i, sizeof(char));
            size_t j = 0;
            while(temp[j + i] != '\0')
            {
                temporaryPointer[j] = temp[j + i];
                j++;
            }
            free(temp);
            temp = temporaryPointer;
            temporaryPointer = NULL;
        }

        temp2 = stringAddition(result, s_r, temp, s_t - i, n);

        size_t temp_i = 0;
        while(temp2[temp_i++] != '\0'){}
        free(result);
        result = NULL;
        result = temp2;
        s_r = temp_i;
        free(temp);
        temp = NULL;
            
            
    }
    return(result);
}

char* stringAddition(char * x, size_t s_x, char * y, size_t s_y, int n)
{
    size_t s_r;
    if(s_x > s_y) s_r = s_x;
    else s_r = s_y;
    char* res = (char*) calloc(s_r + 1, sizeof(char));
    int r_i = s_r - 1, x_i = s_x - 2, y_i = s_y - 2;
    int a, b = 0;

                
    while(r_i >= 0)
    {        
        if(x_i < 0 && y_i < 0)
        {
            if(b == 1) res[0] = '1';
                r_i--;
        }
        else
        {
                            
            if(x_i < 0) 
                a = c_to_n[y[y_i--]] + b;
            else if(y_i < 0) 
                a = c_to_n[x[x_i--]] + b;
            else 
                a = c_to_n[x[x_i--]] + c_to_n[y[y_i--]] + b;

            b = 0;
            if(a >= n)
            {
                b = 1;
                a %= n;
            }
            res[r_i--] = n_to_c[a];
                            
        }
    }
    char* temporaryPointer = NULL;
    int i = -1;
    while(res[++i] == 0){}
    if (i > 0)
    {
        temporaryPointer = (char *) calloc(s_r + 1 - i, sizeof(char));
        size_t j = 0;
        while(res[j + i] != '\0')
        {
            temporaryPointer[j] = res[j + i];
            j++;
        }
        free(res);
        res = temporaryPointer;
        temporaryPointer = NULL;
    }
    return res;
}

char* stringSubstraction(char * x, size_t s_x, char * y, size_t s_y, int n)
{
    size_t s_r;
    if(s_x > s_y) s_r = s_x;
    else s_r = s_y;
    char* res = (char*) calloc(s_r, sizeof(char));
    int r_i = s_r - 2, x_i = s_x - 2, y_i = s_y - 2;
    int b = 0;

    char* temp_x = (char*) calloc(s_x, sizeof(char));
    for(int i = 0; i < s_x; i++) temp_x[i] = x[i];
                
    while(r_i >= 0)
    {
        if(y_i < 0)
        {
            res[r_i--] = temp_x[x_i--];
        }
        else
        {
            if(c_to_n[temp_x[x_i]] >= c_to_n[y[y_i]])
            {
                res[r_i--] = n_to_c[c_to_n[temp_x[x_i--]] - c_to_n[y[y_i--]]];
            }
            else
            {
                int i = 1;

                while(temp_x[x_i - i] == '0') i++;

                if(x_i - i == 0 && temp_x[x_i - i] == '1') temp_x[x_i - i] = '\0';
                else temp_x[x_i - i] = n_to_c[c_to_n[temp_x[x_i - i]] - 1];

                i--;

                while(i > 0)
                {
                    temp_x[x_i - i] = n_to_c[c_to_n[temp_x[x_i - i]] + n - 1];
                    i--;
                }

                temp_x[x_i] = n_to_c[c_to_n[temp_x[x_i]] + n];


                res[r_i--] = n_to_c[c_to_n[temp_x[x_i--]] - c_to_n[y[y_i--]]];
            }
        }
    }
    char* temporaryPointer = NULL;
    int i = 0;
    while(res[i] == 0) i++;
    while(res[i] == '0') i++;
    if(i == s_r - 1) i--;
    if (i > 0)
    {
        temporaryPointer = (char *) calloc(s_r + 1 - i, sizeof(char));
        size_t j = 0;
        while(res[j + i] != '\0')
        {
            temporaryPointer[j] = res[j + i];
            j++;
        }
        free(res);
        res = temporaryPointer;
        temporaryPointer = NULL;
    }
    free(temp_x);
    return res;
}

int loadNumber(char** result, size_t* index, size_t* size, FILE** input, int n)
{
    char ch = EOF, *tfp = NULL, *tfp2 = NULL;
    while(ch)
    {
        ch = getc(*input);
        if(ch == '\n') ch = '\0';
        if ((c_to_n[ch] < 0 || c_to_n[ch] >= n) && ch != '\0') {
            printf("Niepoprawne dane wejsciowe\n");
            if (tfp2 != NULL) free(tfp2);
            return 1;
        }
        if((*size) <= (*index))
        {
            *size += sizeof(char);

            tfp = realloc(tfp2, *size);

            if(!tfp)
            {
                free(tfp2);
                tfp2 = NULL;
                break;
            }

           tfp2 = tfp;
        }

        tfp2[(*index)++] = ch;
    }
    *result = tfp2;
    tfp2 = NULL;
    return 0;
}

int stringComparision(char* one, char* two, int size)
{
    for(int i = 0; i < size - 1; i++)
    {
        if(c_to_n[one[i]] > c_to_n[two[i]]) 
            return 1;
        if(c_to_n[one[i]] < c_to_n[two[i]])
            return -1;
    }
    return 0;
}

size_t stringLength(char* string)
{
    size_t string_size = 1;
    while(string[string_size - 1] != '\0') string_size++;
    return string_size;
}

char* dec_to_base(int number, int base)
{
    if(number == 0)
    {
        char* result = (char*) calloc(2, sizeof(char));
        result[0] = '0';
        return result;
    }
    char* result, *temp;
    size_t size = 1;
    result = calloc(1, sizeof(char));
    while(number > 0)
    {
        int letter = number % base;
        temp = (char*) calloc(++size, sizeof(char));
        if(size > 2)
            for(int i = 0; i < size - 2; i++) temp[i + 1] = result[i];
        temp[0] = n_to_c[letter];
        free(result);
        result = temp;
        temp = NULL;
        number /= base;
    }
    return result;
}
//This is Hill Cipher Program using 2x2 Matrix Key
//Author: Truong Quang Huy - ID:18602

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char table[26] = "abcdefghijklmnopqrstuvwxyz";
int a_valid[12]     = {1, 3, 5, 7, 9, 11, 15, 17, 19, 21, 23, 25};
int mul_inverse[12] = {1, 9, 21, 15, 3, 19, 7, 23, 11, 5, 17 ,25};

int convertCHR(char a ){
    for (int i = 0; i < 26; i++){
        if (a == table[i]) return (i);
    }
    return (-1);
}

char convertNUM(int i){
    return(table[i]);
}

int modulo_26(int a)
{
    if (a < 0)
        return (26 - abs(a) % 26);
    else
        return (a % 26);
}


void encryption_Function()
{
    char plain_text[100], cipher_text[100];
    int key[4], text_convert[100];
    int i, text_length, det;
    int x,y;
    int valid = 0;

    printf("Please input the plaintext: ");
    scanf("%s", plain_text);

    printf("Please input the key matrix: ");
    scanf("%d %d %d %d", &key[0], &key[1], &key[2], &key[3]);

    //the old code for checking the key, not need in final program
    /*
    for (i = 0; i < 4; i++)
    {
        printf("%d ", key[i]);
    }
    */

    //for checking the key, maybe not need for encryption but I still want to check
    det = key[0] * key[3] - key[1] * key[2];
    det = modulo_26(det);

    for (i = 0; i < 12; i++)
    {
        if (det == a_valid[i])
        {
            valid = 1;
            break;
        }

    }

    if ( valid == 0)
    {
        printf("Your key is not valid, it can be used to encrypt but your ciphertext will not be decrypt, you should change your key.\n");
        printf("The program will exit here");
        getchar();
        getchar();
        exit(1);
    }

    //convert the plaintext to array of integer
    text_length = strlen(plain_text);

    for (i = 0; i < text_length; i++)
    {
        text_convert[i] = convertCHR(plain_text[i]);
    }


    if (text_length % 2 == 1)
    {
        text_convert[text_length] = 0;
        text_length++;
    }

    //The old code for checking the convert and adding 0 function, not need in final program
    /*
    for (i = 0; i < text_length; i++)
        printf("%d ", plain_text_convert[i]);
    */

    for (i = 0; i < text_length; i += 2)
    {
        //find x in (x,y)
        x = (text_convert[i] * key[0] + text_convert[i + 1] * key[2]);
        x = modulo_26(x);
        cipher_text[i] = convertNUM(x);

        //find y in (x,y)
        y = (text_convert[i] * key[1] + text_convert[i + 1] * key[3]);
        y = modulo_26(y);
        cipher_text[i + 1] = convertNUM(y);
    }

    //print result
    printf("\n");
    printf("The cipher text is:  ");
    for (i = 0; i < text_length; i++)
        printf("%c", cipher_text[i]);
}

void decryption_Function()
{
    char cipher_text[100], plain_text[100];
    int key[4], decryp_key[4], text_convert[100];
    int text_length, det, det_inverse;
    int i, x, y;
    int valid = 0;

    //input
    printf("Please input the ciphertext: ");
    scanf("%s", cipher_text);

    printf("Please input the key matrix: ");
    scanf("%d %d %d %d", &key[0], &key[1], &key[2], &key[3]);

    //check the key if it's valid
    det = key[0] * key[3] - key[1] * key[2];
    det = modulo_26(det);
    for (i = 0; i < 12; i++)
    {
        if (det == a_valid[i])
        {
            valid = 1;
            det_inverse = mul_inverse[i];
            //old code for checking the the inverse of determinant
            //printf("%d\n", det_inverse);
            break;
        }
    }

    if ( valid == 0)
    {
        printf("Your key is not valid, it can be used to decrypt, you must change your key.\n");
        printf("The program will exit here");
        getchar();
        getchar();
        exit(1);
    }

    //convert the ciphertext to array of integer
    text_length = strlen(cipher_text);

    for (i = 0; i < text_length; i++)
    {
        text_convert[i] = convertCHR(cipher_text[i]);
    }


    if (text_length % 2 == 1)
    {
        text_convert[text_length] = 0;
        text_length++;
    }

    //find the decryption key
    for (i = 0; i < 4; i++)
    {
        if (i == 0 || i == 3){
            decryp_key[i] = det_inverse * key[3 - i];}
        else{
            decryp_key[i] = det_inverse * key[i] * (-1);}

        decryp_key[i] = modulo_26(decryp_key[i]);
    }


    //Processing
    for (i = 0; i < text_length; i += 2)
    {
        //find x in (x,y)
        x = (text_convert[i] * decryp_key[0] + text_convert[i + 1] * decryp_key[2]) % 26;
        plain_text[i] = convertNUM(x);

        //find y in (x,y)
        y = (text_convert[i] * decryp_key[1] + text_convert[i + 1] * decryp_key[3]) % 26;
        plain_text[i + 1] = convertNUM(y);
    }

    //print result
    printf("\n");
    printf("The plain text is:  ");
    for (i = 0; i < text_length; i++)
        printf("%c", plain_text[i]);
}

int main()
{
    char choice;

    printf("This is Hill Cipher Program using 2x2 Matrix Key\n");
    printf("Author: Truong Quang Huy - ID:18602\n\n");


    printf("Please choose e for encryption, choose d for decryption: ");
    scanf("%c", &choice);
    printf("\n");

    if (choice == 'e')
        encryption_Function();
    else if (choice == 'd')
        decryption_Function();
    else
    {
        printf("You make a wrong choice, the program will exit and you have to restart it again.\n");
        return(1);
    }

    printf("\n\n");
    printf("Press Enter to exit the program.");
    getchar();
    getchar();
    return (0);
}


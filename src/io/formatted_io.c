// scanf
// printf
// where is put and get?
// How to get string size from input?

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <locale.h>

int main() {

    // To string
    // Ref: https://en.cppreference.com/w/c/io/fscanf

    int i, j;
    float x, y;
    char str1[10], str2[4];
 
    char input[] = "25 54.32E-1 Thompson 56789 0123 56";
    char output[200];

    /* parse as follows:
       %d: an integer
       %f: a floating-point value
       %9s: a string of at most 9 non-whitespace characters
       %2d: two-digit integer (digits 5 and 6)
       %f:  a floating-point value (digits 7, 8, 9)
       %*d: an integer which isn't stored anywhere
       ' ': all consecutive whitespace
       %3[0-9]: a string of at most 3 decimal digits (digits 5 and 6)
    */

    int ret = sscanf(input, "%d%f%9s%2d%f%*d %3[0-9]",
                     &i, &x, str1, &j, &y, str2);
    

    // Remember buffer size need to include '\0'
    snprintf(output, 200, "Converted %d fields:\ni = %d\nx = %f\nstr1 = %s\nj = %d\ny = %f\nstr2 = %s\n", 
            ret, i, x, str1, j, y, str2);

    //// TEST ////
    printf("%s", output);

    // To file stream
    // Ref: http://www.cplusplus.com/reference/cstdio/fscanf/

    char pi_str [80];
    float pi_f;
    FILE* file = fopen ("build/file.txt","w+");

    fprintf (file, "%f %s", 3.1416, "PI");
    rewind (file);
    fscanf (file, "%f", &pi_f);
    fscanf (file, "%s", pi_str);
    fclose (file);
    printf ("I have read: %f and %s \n", pi_f, pi_str);

    // To stdin/stdout
    // Ref: http://www.cplusplus.com/reference/cstdio/scanf/

    char str [80];
    int a;

    printf ("Enter your family name: ");

    // Any number of non-whitespace characters, stopping at the first whitespace character found.
    scanf ("%79s",str);  

    printf ("Enter your age: ");
    scanf ("%d",&a);
    printf ("Mr. %s , %d years old.\n",str,a);
    printf ("Enter a hexadecimal number: ");
    scanf ("%x",&i);
    printf ("You have entered %#x (%d).\n",i,i);


    // How about `put` and `get`
    // `putc` and `fputc` have same behavior, but `fputc` is implemented as function, rather than macro.
    // The last character of `putc` and `getc` is stand for "character".
    // ------------------------------------------------------
    // `fgets` and `fputs` mean get and write string to stdout / stdin.

    // fputc
    int ret_code = 0;
    for (char c = 'a'; (ret_code != EOF) && (c != 'z'); c++)
        ret_code = fputc(c, stdout);

    // fputs
    fputs("\nHello c programming\n", stdout);

    // fgetc
    FILE* fp = fopen("res/Three_little_pigs.txt", "r");
    if (!fp) {
        perror("File opening failed");
        return EXIT_FAILURE;
    }

    int c;
    while(EOF != (c = fgetc(fp))) {
        fputc(c, stdout);
    }
    fclose(fp);
    
    // fgets (`gets` is removed from C11)
    FILE* tmpf = fopen("build/pioneer.txt", "w+");
    fputs("Alan Turing\n", tmpf);
    fputs("John von Neumann\n", tmpf);
    fputs("Alonzo Church\n", tmpf);

    rewind(tmpf);

    char buf[12];
    while (fgets(buf, sizeof(buf), tmpf) != NULL)
          printf("\"%s\"\n", buf);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

// Custom types
typedef unsigned char u8; // one byte


// Takes a string and print it using (RLE8) compression algorithm
void RLE8_str(const char *str, size_t size) {
        u8 count = 1;
        u8 buffer[size * 2];
        u8 *dest = buffer;

        for (size_t i = 0; i < size; i++) {
                if (*str != *(str + 1) || count >= 255) {
                        u8 digits[3];
                        u8 num_digits = 0;

                        while (count > 0) {
                                digits[num_digits++] = count % 10;
                                count /= 10;
                        }

                        for (u8 i = num_digits; i > 0; i--)
                                *dest++ = digits[i - 1] + '0';

                        *dest++ = *str;
                }

                str++;
                count++;
        }

        *dest = '\0';
        printf("RLE8: %s\n", buffer);
}

// Simple RLE8 compression for files
void RLE8(const char* file_name) {
        FILE *file = fopen(file_name, "rb");

        if (file == NULL) {
                fprintf(stderr, "fail to open file!\n");
                exit(1);
        }

        u8 count = 1;
        long byte = fgetc(file);
        long next_byte;

        while (!feof(file)) {
                next_byte = fgetc(file);

                 if (byte != next_byte || count >= 255) {
                        u8 digits[3];
                        u8 num_digits = 0;

                        while (count > 0) {
                                digits[num_digits++] = count % 10;
                                count /= 10;
                        }

                        for (u8 i = num_digits; i > 0; i--)
                                fputc(digits[i - 1] + '0', stdout);

                        fputc(byte, stdout);
                }

                byte = next_byte;
                count++;
        }

        fclose(file);
}

int main(int argc, char *argv[]) {
        if (argc < 2) {
                fprintf(stderr, "Usage: %s <file_name>\n", argv[0]);
                return 1;
        }

        const char* file_name = argv[1];
        RLE8(file_name);

        return 0;
}

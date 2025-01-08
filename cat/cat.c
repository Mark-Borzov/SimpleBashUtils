#include <stdio.h>
#include <string.h>

void no_flags(FILE *file) {
  int symbol;
  while ((symbol = fgetc(file)) != EOF) {
    printf("%c", symbol);
  }
}

void flag_n(FILE *file) {
  int symbol, str_num = 1;
  char pre_symbol = '\0';
  if (fgetc(file) != EOF) {
    printf("%6d\t", str_num);
    fseek(file, 0, SEEK_SET);
  }
  while ((symbol = fgetc(file)) != EOF) {
    if (pre_symbol == '\n') {
      str_num++;
      printf("%6d\t", str_num);
    }
    pre_symbol = symbol;
    printf("%c", pre_symbol);
  }
}

void flag_E(FILE *file, int e) {
  int symbol;
  while ((symbol = fgetc(file)) != EOF) {
    if (symbol == '\n') {
      printf("$\n");
    } else if (symbol >= 0 && symbol <= 31 && symbol != 9 && symbol != 10 &&
               e == 2) {
      printf("^%c", symbol + 64);
    } else if (symbol >= 128 && symbol <= 159 && e == 2) {
      printf("M-^%c", symbol - 64);
    } else if (e == 2 && symbol == 127) {
      printf("^?");
    } else {
      printf("%c", symbol);
    }
  }
}

void flag_b(FILE *file) {
  int symbol, line_num = 1, pass = 0;
  while ((symbol = fgetc(file)) != EOF) {
    if (symbol == '\n') {
      if (pass == 1) {
        pass = 0;
        line_num++;
      }
      printf("\n");
    } else {
      if (pass == 0) {
        printf("%6d\t", line_num);
      }
      printf("%c", symbol);
      pass = 1;
    }
  }
}

void flag_s(FILE *file) {
  int symbol, count = 1, new_str = 0;
  while ((symbol = fgetc(file)) != EOF) {
    if (symbol != '\n') {
      printf("%c", symbol);
      new_str = 0;
      count = 0;
    } else if (new_str < 2 && count != 2) {
      printf("%c", symbol);
      new_str++;
      count++;
    }
  }
}

void flag_T(FILE *file, int t) {
  int symbol;
  while ((symbol = fgetc(file)) != EOF) {
    if (symbol == '\t') {
      printf("^I");
    } else if (symbol >= 0 && symbol <= 31 && symbol != 9 && symbol != 10 &&
               t == 2) {
      printf("^%c", symbol + 64);
    } else if (symbol >= 128 && symbol <= 159 && t == 2) {
      printf("M-^%c", symbol - 64);
    } else if (t == 2 && symbol == 127) {
      printf("^?");
    } else {
      printf("%c", symbol);
    }
  }
}

void file_open(char *file_info, int count, int n, int e, int b, int s, int t) {
  FILE *file;
  file = fopen(file_info, "r");
  if (file != NULL) {
    if (count == 0) {
      no_flags(file);
    } else if (n == 1) {
      flag_n(file);
    } else if (e == 1) {
      flag_E(file, e);
    } else if (b == 1) {
      flag_b(file);
    } else if (s == 1) {
      flag_s(file);
    } else if (t == 1) {
      flag_T(file, t);
    } else if (e == 2) {
      flag_E(file, e);
    } else if (t == 2) {
      flag_T(file, t);
    }
    fclose(file);
  } else {
    printf("cat: %s: No such file or directory\n", file_info);
  }
}

int main(int argc, char *argv[]) {
  int n = 0, e = 0, b = 0, s = 0, t = 0, count = 0;
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      if (argv[i][1] == 'n' || strcmp(argv[i], "--number") == 0) {
        n = 1, count = 1;
      } else if (argv[i][1] == 'E') {
        e = 1, count = 1;
      } else if (argv[i][1] == 'b' ||
                 strcmp(argv[i], "--number-nonblank") == 0) {
        b = 1, count = 1;
      } else if (argv[i][1] == 's' || strcmp(argv[i], "--squeeze-blank") == 0) {
        s = 1, count = 1;
      } else if (argv[i][1] == 'T') {
        t = 1, count = 1;
      } else if (argv[i][1] == 'e') {
        e = 2, count = 1;
      } else if (argv[i][1] == 't') {
        t = 2, count = 1;
      }
    } else if (count == 0 || count == 1) {
      file_open(argv[i], count, n, e, b, s, t);
    }
  }
  return 0;
}
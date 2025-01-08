#define _POSIX_C_SOURCE 200809L
#define D_GNU_SOURCE
#include <ctype.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void last_character_in_file(char **line, const ssize_t *line_length) {
  char last_symbol = (*line)[*line_length - 1];
  if (last_symbol != '\n') {
    printf("\n");
  }
}

void flag_s(FILE *file, regex_t regex, char **line, size_t *buffer_size,
            ssize_t *line_length, int count_flags, char *file_info) {
  while ((*line_length = getline(line, buffer_size, file)) != -1) {
    if ((regexec(&regex, *line, 0, NULL, 0) == 0) && (count_flags > 1)) {
      printf("%s:%s", file_info, *line);
      last_character_in_file(line, line_length);
    } else if ((regexec(&regex, *line, 0, NULL, 0) == 0) &&
               (count_flags == 1)) {
      printf("%s", *line);
      last_character_in_file(line, line_length);
    }
  }
}

void flag_h(FILE *file, regex_t regex, char **line, size_t *buffer_size,
            ssize_t *line_length, int count_flags) {
  while ((*line_length = getline(line, buffer_size, file)) != -1) {
    if ((regexec(&regex, *line, 0, NULL, 0) == 0) && (count_flags > 1)) {
      printf("%s", *line);
      last_character_in_file(line, line_length);
    } else if ((regexec(&regex, *line, 0, NULL, 0) == 0) &&
               (count_flags == 1)) {
      printf("%s", *line);
      last_character_in_file(line, line_length);
    }
  }
}

void flag_i(FILE *file, regex_t regex, char **line, size_t *buffer_size,
            ssize_t *line_length, int count_flags, char *file_info) {
  while ((*line_length = getline(line, buffer_size, file)) != -1) {
    if ((regexec(&regex, *line, 0, NULL, REG_EXTENDED | REG_ICASE) == 0) &&
        (count_flags > 1)) {
      printf("%s:%s", file_info, *line);
      last_character_in_file(line, line_length);
    } else if ((regexec(&regex, *line, 0, NULL, REG_EXTENDED | REG_ICASE) ==
                0) &&
               (count_flags == 1)) {
      printf("%s", *line);
      last_character_in_file(line, line_length);
    }
  }
}

void flag_v(FILE *file, regex_t regex, char **line, size_t *buffer_size,
            ssize_t *line_length, int count_flags, char *file_info) {
  while ((*line_length = getline(line, buffer_size, file)) != -1) {
    if ((regexec(&regex, *line, 0, NULL, 0) != 0) && (count_flags > 1)) {
      printf("%s:%s", file_info, *line);
      last_character_in_file(line, line_length);
    } else if ((regexec(&regex, *line, 0, NULL, 0) != 0) &&
               (count_flags == 1)) {
      printf("%s", *line);
      last_character_in_file(line, line_length);
    }
  }
}

void flag_n(FILE *file, regex_t regex, char **line, size_t *buffer_size,
            ssize_t *line_length, int count_flags, char *file_info) {
  int count = 1;
  while ((*line_length = getline(line, buffer_size, file)) != -1) {
    if ((regexec(&regex, *line, 0, NULL, 0) == 0) && (count_flags > 1)) {
      printf("%s:%d:%s", file_info, count, *line);
      last_character_in_file(line, line_length);
    } else if ((regexec(&regex, *line, 0, NULL, 0) == 0) &&
               (count_flags == 1)) {
      printf("%d:%s", count, *line);
      last_character_in_file(line, line_length);
    }
    count++;
  }
}

void flag_l(FILE *file, regex_t regex, char **line, size_t *buffer_size,
            ssize_t *line_length, char *file_info) {
  int flag = 0;
  while ((*line_length = getline(line, buffer_size, file)) != -1) {
    if (regexec(&regex, *line, 0, NULL, 0) == 0) {
      flag = 1;
    }
  }
  if (flag == 1) {
    printf("%s\n", file_info);
  }
}

void flag_c(FILE *file, regex_t regex, char **line, size_t *buffer_size,
            ssize_t *line_length, int count_flags, char *file_info) {
  int count = 0;
  while ((*line_length = getline(line, buffer_size, file)) != -1) {
    if (regexec(&regex, *line, 0, NULL, 0) == 0) {
      count++;
    }
  }
  if (count_flags > 1) {
    printf("%s:%d\n", file_info, count);
  } else if (count_flags == 1) {
    printf("%d\n", count);
  }
}

void flag_e(FILE *file, regex_t regex, char **line, size_t *buffer_size,
            ssize_t *line_length, int count_flags, char *file_info) {
  while ((*line_length = getline(line, buffer_size, file)) != -1) {
    if ((regexec(&regex, *line, 0, NULL, 0) == 0) && (count_flags > 1)) {
      printf("%s:%s", file_info, *line);
      last_character_in_file(line, line_length);
    } else if ((regexec(&regex, *line, 0, NULL, 0) == 0) &&
               (count_flags == 1)) {
      printf("%s", *line);
      last_character_in_file(line, line_length);
    }
  }
}

void open_file(char *file_info, char *reg_str, int e, int c, int l, int n,
               int v, int i, int h, int s, int count, int count_flags) {
  FILE *file;
  file = fopen(file_info, "r");
  if (file != NULL) {
    regex_t regex;
    int reg_err = 1;
    if (i == 1) {
      reg_err = regcomp(&regex, reg_str, REG_EXTENDED | REG_ICASE);
    } else {
      reg_err = regcomp(&regex, reg_str, REG_EXTENDED);
    }
    if (reg_err != 0) {
      printf("Regex error\n");
    } else {
      char *line = NULL;
      size_t buffer_size = 0;
      ssize_t line_length = 0;
      if (e == 1) {
        flag_e(file, regex, &line, &buffer_size, &line_length, count_flags,
               file_info);
      } else if (c == 1) {
        flag_c(file, regex, &line, &buffer_size, &line_length, count_flags,
               file_info);
      } else if (l == 1) {
        flag_l(file, regex, &line, &buffer_size, &line_length, file_info);
      } else if (n == 1) {
        flag_n(file, regex, &line, &buffer_size, &line_length, count_flags,
               file_info);
      } else if (v == 1) {
        flag_v(file, regex, &line, &buffer_size, &line_length, count_flags,
               file_info);
      } else if (i == 1) {
        flag_i(file, regex, &line, &buffer_size, &line_length, count_flags,
               file_info);
      } else if (h == 1) {
        flag_h(file, regex, &line, &buffer_size, &line_length, count_flags);
      } else if (s == 1) {
        flag_s(file, regex, &line, &buffer_size, &line_length, count_flags,
               file_info);
      } else if (count == 0) {
        flag_e(file, regex, &line, &buffer_size, &line_length, count_flags,
               file_info);
      }
      free(line);
    }
    regfree(&regex);
    fclose(file);
  } else if (s != 1) {
    printf("grep: %s: No such file or directory\n", file_info);
  }
}

int main(int argc, char *argv[]) {
  int e = 0, c = 0, l = 0, n = 0, v = 0, i = 0, h = 0, s = 0, count = 0,
      count_flags = 0;
  for (int j = 1; j < argc - 1; j++) {
    if (argv[j][0] == '-') {
      if (argv[j][1] == 'e') {
        e = 1, count = 1;
      } else if (argv[j][1] == 'c') {
        c = 1, count = 1;
      } else if (argv[j][1] == 'l') {
        l = 1, count = 1;
      } else if (argv[j][1] == 'n') {
        n = 1, count = 1;
      } else if (argv[j][1] == 'v') {
        v = 1, count = 1;
      } else if (argv[j][1] == 'i') {
        i = 1, count = 1;
      } else if (argv[j][1] == 'h') {
        h = 1, count = 1;
      } else if (argv[j][1] == 's') {
        s = 1, count = 1;
      }
    } else {
      count_flags++;
    }
  }
  for (int j = 1; j < argc - 1; j++) {
    if (argv[j][0] == '-') {
      count = 1;
    } else {
      open_file(argv[j + 1], argv[1 + count], e, c, l, n, v, i, h, s, count,
                count_flags);
    }
  }
  return 0;
}
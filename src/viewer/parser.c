#include "s21_objloader.h"

/// @brief Парсит файл, формируя стэк полигонов и массив координат
/// @param filename имя файла
/// @param vertices_coordinates указатель на массив координат по три на вершину
/// (x, y, z, x, ...)
/// @param arr_size указатель на счетчик координат
/// @param index_stack указатель на стэк полигонов
/// @param poligon_counter указатель на счетчик полигонов
/// @return 1 в случае ошибки с файлом и 0 в ином случае
int parser(char *filename, double **vertices_coordinates, int *arr_size,
           node **index_stack, int *poligon_counter) {
  int res = 0;
  char *str = NULL;
  FILE *file = fopen(filename, "r");
  if (file != NULL) {
    while (take_line(&str, file) == 0) {
      //          printf("%s\n", str);
      handle_string(str, vertices_coordinates, arr_size, index_stack,
                    poligon_counter);
    }
    handle_string(str, vertices_coordinates, arr_size, index_stack,
                  poligon_counter);
    free(str);
  } else {
    res = 1;
  }
  fclose(file);
  return res;
}

/// @brief Берет строку из файла
/// @param str строка obj файла
/// @param file указатель на файл
/// @return 1 в случае конца файла и 0 в ином случае
int take_line(char **str, FILE *file) {
  int length = 0;
  int end_symbol = 0;
  char letter = fgetc(file);
  while (letter != '\n' && letter != EOF) {
    *str = realloc(*str, length + 1);
    (*str)[length] = letter;
    length++;
    letter = fgetc(file);
  }
  *str = realloc(*str, length + 1);
  (*str)[length] = '\0';
  if (letter == EOF) end_symbol = 1;
  return end_symbol;
}

/// @brief Парсит строку obj файла
/// @param str строка obj файла
/// @param vertices_coordinates указатель на массив координат по три на вершину
/// (x, y, z, x, ...)
/// @param arr_size указатель на счетчик координат
/// @param index_stack указатель на стэк полигонов
/// @param poligon_counter указатель на счетчик полигонов
void handle_string(char *str, double **vertices_coordinates, int *arr_size,
                   node **index_stack, int *poligon_counter) {
  switch (str[0]) {
    case 'v':
      *arr_size += 3;
      void *tmp = NULL;
      while (tmp == NULL)
        tmp = realloc(*vertices_coordinates, *arr_size * sizeof(double));
      *vertices_coordinates = tmp;
      handle_v(str, *vertices_coordinates, *arr_size);
      break;
    case 'f':
      handle_f(str, index_stack, poligon_counter);
      break;
    default:
      break;
  }
}

/// @brief Обрабатывает строку, начинающуюся с f
/// @param str указатель на первый элемент строки
/// @param index_stack указатель на стэк
/// @param poligon_counter счетчик полигонов
void handle_f(char *str, node **index_stack, int *poligon_counter) {
  int *tmp_array = NULL;
  int tmp_size_array = 0;
  int tmp_number = 0;
  for (int letter_pos = 1, break_rule = 0;
       str[letter_pos] != '\0' && break_rule == 0; letter_pos++) {
    tmp_number = 0;
    if (str[letter_pos] > '0' && str[letter_pos] <= '9') {
      tmp_size_array++;
      void *tmp = NULL;
      while (tmp == NULL)
        tmp = realloc(tmp_array, tmp_size_array * 2 * sizeof(int));
      tmp_array = tmp;
      if (take_number(str, &letter_pos, &tmp_number) == 1) {
        break_rule = 1;
      }
      set_number(tmp_array, tmp_size_array, tmp_number);
    } else if (str[letter_pos] != ' ') {
      break_rule = 1;
    }
  }
  if (tmp_size_array > 1) {
    tmp_array[tmp_size_array * 2 - 1] = tmp_array[0];
    if (*poligon_counter == 0) {
      *index_stack = init();
    } else {
      *index_stack = push(*index_stack);
    }
    (*index_stack)->index_array = tmp_array;
    (*index_stack)->size_of_array = tmp_size_array * 2;
    *poligon_counter += 1;
  } else {
    free(tmp_array);
  }
}

/// @brief Парсит строку поверхности obj файла на число
/// @param str указатель на начало строки
/// @param letter_pos указатель на позицию в строке от 0 до ...
/// @param number полученное число
/// @return 1 в случае конца строки и 0 в ином случае
int take_number(char *str, int *letter_pos, int *number) {
  int res = 0;
  *number = str[*letter_pos] - '0';
  *letter_pos += 1;
  while (str[*letter_pos] >= '0' && str[*letter_pos] <= '9') {
    *number *= 10;
    *number += (str[*letter_pos] - '0');
    *letter_pos += 1;
  }
  if (str[*letter_pos] != ' ') res = 1;
  return res;
}

/// @brief Устанавливает число в массив по его значению и порядку
/// @param tmp_array указатель на массив чисел
/// @param tmp_size_array кол-во чисел, которые установлены в массиве
/// @param tmp_number число для установки
void set_number(int *array, int size_array, int number) {
  number -= 1;  // так как массив координат начинается с 0
  if (size_array == 1) {
    array[size_array * 2 - 2] = number;
  } else {
    array[size_array * 2 - 3] = number;
    array[size_array * 2 - 2] = number;
  }
}

/// @brief Обрабатывает строку, начинающуюся с v
/// @param str строка для обработки
/// @param vertices_coordinates массив координат
/// @param arr_size размер массива координат
void handle_v(char *str, double *vertices_coordinates, int arr_size) {
  vertices_coordinates[arr_size - 3] = 1;
  vertices_coordinates[arr_size - 2] = 1;
  vertices_coordinates[arr_size - 1] = 1;
  int arr_counter = 3;
  double tmp_number = 1;
  for (int letter_pos = 1, break_rule = 0;
       str[letter_pos] != '\0' && arr_counter > 0 && break_rule == 0;
       letter_pos++) {
    tmp_number = 1;
    if ((str[letter_pos] >= '0' && str[letter_pos] <= '9') ||
        str[letter_pos] == '-') {
      if (take_double_number(str, &letter_pos, &tmp_number) == 1) {
        break_rule = 1;
      }
      vertices_coordinates[arr_size - arr_counter] = tmp_number;
      arr_counter--;
    } else if (str[letter_pos] != ' ') {
      break_rule = 1;
    }
  }
}

/// @brief Парсит строку вершин obj файла на число
/// @param str строка для обработки
/// @param letter_pos указатель на позицию в строке от 0 до ...
/// @param number полученное число
/// @return  1 в случае конца строки и 0 в ином случае
int take_double_number(char *str, int *letter_pos, double *number) {
  int res = 0;
  int sign = 1;
  if (str[*letter_pos] == '-') {
    sign = -1;
    *letter_pos += 1;
  }
  if (str[*letter_pos] >= '0' && str[*letter_pos] <= '9') {
    *number = str[*letter_pos] - '0';
    *letter_pos += 1;
  }
  while (str[*letter_pos] >= '0' && str[*letter_pos] <= '9') {
    *number *= 10;
    *number += (str[*letter_pos] - '0');
    *letter_pos += 1;
  }
  if (str[*letter_pos] == '.') {
    *letter_pos += 1;
    for (int i = 1; str[*letter_pos] >= '0' && str[*letter_pos] <= '9'; i++) {
      *number += (str[*letter_pos] - '0') / pow(10, i);
      *letter_pos += 1;
    }
  }
  if (str[*letter_pos] != ' ') res = 1;
  *number *= sign;
  return res;
}

#ifdef __cplusplus
extern "C" {
#endif
#ifndef VIEWER_STACK_H_
#define VIEWER_STACK_H_

#include <stdlib.h>

/// @brief структура, хранящая данные о полигоне
/// @param index_array указатель на первый элемент массива индексов
/// @param size_of_array размер массива индексов
/// @param next_node указатель на следующий полигон
typedef struct node {
  int* index_array;
  int size_of_array;
  struct node* next_node;
} node;

node* init();
node* push(node* root);
void destroy(node* root);

#endif  // VIEWER_STACK_H_
#ifdef __cplusplus
}
#endif

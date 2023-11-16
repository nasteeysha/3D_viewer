#include "stack.h"

/// @brief Инициализирует первый элемент стэка
/// @return указатель на элемент стэка
node* init() {
  node* root = NULL;
  while (root == NULL) root = (node*)malloc(sizeof(node));
  root->next_node = NULL;
  root->size_of_array = 0;
  root->index_array = NULL;
  return root;
}

/// @brief Создает новый верхний элемент стэка
/// @param root указатель на старый верхний элемент стэка
/// @return указатель на новый верхний элемент стэка
node* push(node* root) {
  node* tmp = NULL;
  while (tmp == NULL) tmp = (node*)malloc(sizeof(node));
  tmp->next_node = root;
  tmp->size_of_array = 0;
  tmp->index_array = NULL;
  return tmp;
}

/// @brief Уничтожает стэк
/// @param root указатель на верхний элемент стэка
void destroy(node* root) {
  node* tmp = NULL;
  while (root != NULL) {
    tmp = root->next_node;
    free(root->index_array);
    free(root);
    root = tmp;
  }
}

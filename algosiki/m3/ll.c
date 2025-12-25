#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Структура для узла списка
typedef struct Node {
    int data;           // Данные узла
    struct Node* next;  // Указатель на следующий узел
} Node;

// Структура для самого списка
typedef struct {
    Node* head;         // Указатель на первый узел
    Node* tail;         // Указатель на последний узел (для оптимизации)
    int size;           // Количество элементов в списке
} LinkedList;

// Создание нового узла
Node* create_node(int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Ошибка выделения памяти!\n");
        return NULL;
    }
    new_node->data = value;
    new_node->next = NULL;
    return new_node;
}

// Инициализация списка
void init_list(LinkedList* list) {
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

// Добавление элемента в конец списка
void append(LinkedList* list, int value) {
    Node* new_node = create_node(value);
    if (new_node == NULL) return;
    
    if (list->head == NULL) {
        // Если список пустой
        list->head = new_node;
        list->tail = new_node;
    } else {
        // Добавляем в конец
        list->tail->next = new_node;
        list->tail = new_node;
    }
    list->size++;
}

// Добавление элемента в начало списка
void prepend(LinkedList* list, int value) {
    Node* new_node = create_node(value);
    if (new_node == NULL) return;
    
    if (list->head == NULL) {
        list->head = new_node;
        list->tail = new_node;
    } else {
        new_node->next = list->head;
        list->head = new_node;
    }
    list->size++;
}

// Вставка элемента по индексу
bool insert_at(LinkedList* list, int index, int value) {
    if (index < 0 || index > list->size) {
        printf("Неверный индекс!\n");
        return false;
    }
    
    if (index == 0) {
        prepend(list, value);
        return true;
    }
    
    if (index == list->size) {
        append(list, value);
        return true;
    }
    
    Node* new_node = create_node(value);
    if (new_node == NULL) return false;
    
    // Находим узел перед позицией вставки
    Node* current = list->head;
    for (int i = 0; i < index - 1; i++) {
        current = current->next;
    }
    
    // Вставляем новый узел
    new_node->next = current->next;
    current->next = new_node;
    list->size++;
    
    return true;
}

// Удаление элемента по значению
bool remove_value(LinkedList* list, int value) {
    if (list->head == NULL) {
        return false;
    }
    
    // Если удаляем первый элемент
    if (list->head->data == value) {
        Node* temp = list->head;
        list->head = list->head->next;
        
        // Если список стал пустым
        if (list->head == NULL) {
            list->tail = NULL;
        }
        
        free(temp);
        list->size--;
        return true;
    }
    
    // Ищем элемент для удаления
    Node* current = list->head;
    while (current->next != NULL && current->next->data != value) {
        current = current->next;
    }
    
    // Если элемент не найден
    if (current->next == NULL) {
        return false;
    }
    
    // Удаляем элемент
    Node* temp = current->next;
    current->next = temp->next;
    
    // Если удалили последний элемент
    if (temp == list->tail) {
        list->tail = current;
    }
    
    free(temp);
    list->size--;
    return true;
}

// Удаление элемента по индексу
bool remove_at(LinkedList* list, int index) {
    if (index < 0 || index >= list->size) {
        printf("Неверный индекс!\n");
        return false;
    }
    
    if (index == 0) {
        Node* temp = list->head;
        list->head = list->head->next;
        
        if (list->head == NULL) {
            list->tail = NULL;
        }
        
        free(temp);
        list->size--;
        return true;
    }
    
    // Находим узел перед удаляемым
    Node* current = list->head;
    for (int i = 0; i < index - 1; i++) {
        current = current->next;
    }
    
    Node* temp = current->next;
    current->next = temp->next;
    
    // Если удалили последний элемент
    if (temp == list->tail) {
        list->tail = current;
    }
    
    free(temp);
    list->size--;
    return true;
}

// Поиск элемента по значению
Node* find(LinkedList* list, int value) {
    Node* current = list->head;
    while (current != NULL) {
        if (current->data == value) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Получение элемента по индексу
int get_at(LinkedList* list, int index) {
    if (index < 0 || index >= list->size) {
        printf("Неверный индекс!\n");
        return -1;
    }
    
    Node* current = list->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    
    return current->data;
}

// Изменение элемента по индексу
bool set_at(LinkedList* list, int index, int value) {
    if (index < 0 || index >= list->size) {
        printf("Неверный индекс!\n");
        return false;
    }
    
    Node* current = list->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    
    current->data = value;
    return true;
}

// Проверка на пустоту
bool is_empty(LinkedList* list) {
    return list->head == NULL;
}

// Получение размера списка
int get_size(LinkedList* list) {
    return list->size;
}

// Вывод списка на экран
void print_list(LinkedList* list) {
    if (is_empty(list)) {
        printf("Список пуст\n");
        return;
    }
    
    printf("Список [%d элементов]: ", list->size);
    Node* current = list->head;
    while (current != NULL) {
        printf("%d", current->data);
        if (current->next != NULL) {
            printf(" -> ");
        }
        current = current->next;
    }
    printf("\n");
}

// Очистка списка (удаление всех элементов)
void clear_list(LinkedList* list) {
    Node* current = list->head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

// Реверс списка
void reverse_list(LinkedList* list) {
    if (list->head == NULL || list->head->next == NULL) {
        return;
    }
    
    Node* prev = NULL;
    Node* current = list->head;
    Node* next = NULL;
    
    list->tail = list->head; // Теперь хвост станет головой
    
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    
    list->head = prev;
}

// Пример использования
int main() {
    LinkedList list;
    init_list(&list);
    
    printf("=== Тестирование линейного списка ===\n\n");
    
    // Добавление элементов
    printf("1. Добавляем элементы в конец:\n");
    for (int i = 1; i <= 5; i++) {
        append(&list, i * 10);
    }
    print_list(&list);
    
    printf("\n2. Добавляем элементы в начало:\n");
    prepend(&list, 99);
    prepend(&list, 88);
    print_list(&list);
    
    printf("\n3. Вставляем элемент по индексу 3:\n");
    insert_at(&list, 3, 777);
    print_list(&list);
    
    printf("\n4. Получаем элемент по индексу 4: %d\n", get_at(&list, 4));
    
    printf("\n5. Изменяем элемент по индексу 2:\n");
    set_at(&list, 2, 555);
    print_list(&list);
    
    printf("\n6. Ищем элемент со значением 777: ");
    Node* found = find(&list, 777);
    if (found != NULL) {
        printf("найден!\n");
    } else {
        printf("не найден\n");
    }
    
    printf("\n7. Удаляем элемент со значением 555:\n");
    remove_value(&list, 555);
    print_list(&list);
    
    printf("\n8. Удаляем элемент по индексу 0:\n");
    remove_at(&list, 0);
    print_list(&list);
    
    printf("\n9. Реверс списка:\n");
    reverse_list(&list);
    print_list(&list);
    
    printf("\n10. Размер списка: %d\n", get_size(&list));
    printf("    Пустой ли список? %s\n", is_empty(&list) ? "Да" : "Нет");
    
    printf("\n11. Очищаем список:\n");
    clear_list(&list);
    print_list(&list);
    printf("    Пустой ли список? %s\n", is_empty(&list) ? "Да" : "Нет");
    
    return 0;
}

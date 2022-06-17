//
// Created by rudri on 6/16/2022.
//

#ifndef PROG3_HEAP_LAB101_2022_1_HEAP_H
#define PROG3_HEAP_LAB101_2022_1_HEAP_H

#include <iterator>
#include <vector>
#include <initializer_list>

using index_t = int;

// Funciones para el recorrido en el heap
auto get_left_index = [](index_t parent_index) { return parent_index * 2; };
auto get_right_index = [](index_t parent_index) { return parent_index * 2 + 1;};
inline index_t get_parent_index(index_t child_index) { return child_index / 2; }

// Funciones utilitarias de los algoritmos (percólate up / percólate down)
inline bool has_parent(index_t child_index) { return child_index / 2 != 0; }
inline bool has_children(index_t child_index, index_t last_index) {
    return get_left_index(child_index) <= last_index;
}
inline bool has_right_child(index_t child_index, index_t last_index) {
    return get_right_index(child_index) <= last_index;
}

auto get_selected_child = [](const auto& cnt, auto current_index) {
    // Si no tiene hijo derecho selecciona directamente hijo izquierdo
    if (!has_right_child(current_index, std::size(cnt)-1)) return get_left_index(current_index);

    // Si ambos hijos
    auto left_index = get_left_index(current_index);
    auto right_index = get_right_index(current_index);

    // Obtener los valores derecho e izquierdo del contenedor y comparandolos decido el subindice
    return cnt[left_index] > cnt[right_index]? left_index: right_index;
};

template <typename Container>
void percolate_up(Container& cnt, index_t current_index) {
    // Ubicar el padre
    auto parent_index = get_parent_index(current_index);

    // Condición Base de la recursividad
    // Si no existe padre detenerse
    if (!has_parent(current_index)) return;
    // Si el valor del padre > valor del hijo detenerse
    if (cnt[parent_index] > cnt[current_index]) return;

    // realizar el intercambio
    std::swap(cnt[parent_index], cnt[current_index]);

    // realizar la llamada percólate up ubicándose en el padre
    percolate_up(cnt, parent_index);
}

template <typename Container>
void percolate_down(Container& cnt, index_t current_index) {
    // obtener el sub-índice seleccionado (mayor/menor)
    auto selected_index = get_selected_child(cnt, current_index);

    // Condición Base de la recursividad

    // Si no tiene hijos detenerse
    if (!has_children(current_index, std::size(cnt)-1)) return;

    // Si el valor del padre > valor del hijo detenerse
    if (cnt[current_index] > cnt[selected_index]) return;

    // realizar el intercambio
    std::swap(cnt[current_index], cnt[selected_index]);

    // realizar la llamada percólate down ubicándose en el hijo seleccionado
    percolate_down(cnt, selected_index);
}

auto heapify = [](auto& cnt) {
    // Ir al padre del último hijo
    auto current_index = get_parent_index(std::size(cnt) - 1);

    // Recorrer hacia atras
    while (current_index > 0) {
        percolate_down(cnt, current_index);
        --current_index;
    }
};

template <typename T, template<typename ...> typename ContainerType = std::vector>
class heap {
    ContainerType<T> data;
public:
    heap(): data(1) {}
    heap(std::initializer_list<T> lst): data(1 + std::size(lst)) {
        // Insertar los datos al heap
        copy(begin(lst), end(lst), next(begin(data)));
        // Aplicar el heapify
        heapify(data);
    }
    T top() { return data[1]; }
    bool empty() { return std::size(data) == 1; }
    int size() { return std::size(data) - 1; }

    void push(T value) {
        // Insertar al final
        data.push_back(value);
        // Aplicar el percolate up
        percolate_up(data, std::size(data) - 1);
    }

    void pop() {
        // validar si esta vacío no hacer nada
        if (empty()) return;
        // Intercambio entre el primero y el último
        std::swap(data[1], data[std::size(data) - 1]);
        data.pop_back();
        percolate_down(data, 1);
    }
};

#endif //PROG3_HEAP_LAB101_2022_1_HEAP_H

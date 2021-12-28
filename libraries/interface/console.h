#ifndef INTERFACE_CONSOLE
#define INTERFACE_CONSOLE

#if ARDUINO
#include <Arduino.h>

template <class type>
void print_to_console(type value) {
    Serial.print(value);  
    Serial.print(" ");   
}

template <class type>
void println_to_console(type value) {
    Serial.println(value);     
}

// #include <esp_partition.h>

// void partloop(esp_partition_type_t part_type) {
//   esp_partition_iterator_t iterator = NULL;
//   const esp_partition_t *next_partition = NULL;
//   iterator = esp_partition_find(part_type, ESP_PARTITION_SUBTYPE_ANY, NULL);
//   while (iterator) {
//      next_partition = esp_partition_get(iterator);
//      if (next_partition != NULL) {
//         Serial.printf("partition addr: 0x%06x; size: 0x%06x; label: %s\n", next_partition->address, next_partition->size, next_partition->label);  
//      iterator = esp_partition_next(iterator);
//     }
//   }
// }

// void printPartitions() {
//     Serial.println("Partition list:");
//     partloop(ESP_PARTITION_TYPE_APP);
//     partloop(ESP_PARTITION_TYPE_DATA);
// }

#else // Mac OSX
#include <iostream>

template <class type>
void print_to_console(type value) {
    std::cout << value; 
    std::cout << " ";    
}

template <class type>
void println_to_console(type value) {
    std::cout << value << std::endl;     
}

#endif

#endif // INTERFACE_CONSOLE

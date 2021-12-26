#if ARDUINO

#include <Arduino.h>
#include <esp_partition.h>
#include <FFat.h>
#include <FFat.h>
#include <display.h>
#include <console.h>

Display* d;
int stp = 0;

void partloop(esp_partition_type_t part_type) {
  esp_partition_iterator_t iterator = NULL;
  const esp_partition_t *next_partition = NULL;
  iterator = esp_partition_find(part_type, ESP_PARTITION_SUBTYPE_ANY, NULL);
  while (iterator) {
     next_partition = esp_partition_get(iterator);
     if (next_partition != NULL) {
        Serial.printf("partition addr: 0x%06x; size: 0x%06x; label: %s\n", next_partition->address, next_partition->size, next_partition->label);  
     iterator = esp_partition_next(iterator);
    }
  }
}

void setup() {
  
  Serial.begin(115200);

  print_to_console("FFATty");

  for (size_t i = 0; i < 10; i++) {
    print_to_console("setup");
    delay(400);
  }

  print_to_console("FFAT");

    Serial.println("Partition list:");
    partloop(ESP_PARTITION_TYPE_APP);
    partloop(ESP_PARTITION_TYPE_DATA);

  if(!FFat.begin(true)){
    Serial.println("Mount Failed");
  } else {
    Serial.println("File system mounted");
    Serial.println(FFat.totalBytes());
    Serial.println(FFat.freeBytes());
    Serial.println(FFat.usedBytes());
    Serial.println(FFat.exists("ableton.mid"));
    Serial.println(FFat.exists("/ableton.mid"));
    Serial.println(FFat.exists("/ableton2.mid"));
    Serial.println(FFat.exists("/test.json"));
    Serial.println(FFat.exists("/test.txt"));
  }


  d = new Display();
  // d.setLabel1("foo");
  print_to_console("yay");

  stp = 1;

}

void loop() {
  // Serial.print(stp);
  // if (stp == 0) {
  //   setup();
  //   stp = 1;
  // }
  // print_to_console("foo");
  // delay(400);
}

#endif

// import time
// import songbird.interface.program as program
// from songbird.clock.clock import clock

// # Run loop
// while True:
//     program.handler()
//     clock.handler()

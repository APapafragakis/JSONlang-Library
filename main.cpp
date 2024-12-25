#include "JSONlang.h"

int main() {
    // Dimioyrgia JSON pinakwn
    JSON(arr1) = ARRAY(NUMBER(42), STRING("Hello"));
    JSON(arr2) = ARRAY(NUMBER(42), STRING("Hello"));
    JSON(arr3) = ARRAY(NUMBER(42), STRING("World"));

    // Dimioyrgia JSON antikeimenwn
    JSON(obj1_2) = OBJECT({ "key1", NUMBER(42) }, { "key2", STRING("Hello") });
    JSON(obj2_2) = OBJECT({ "key1", NUMBER(42) }, { "key2", STRING("Hello") });
    JSON(obj3_2) = OBJECT({ "key1", NUMBER(42) }, { "key2", STRING("World") });

    // Ektypwsi apotelesmatwn sygkriseon pinakwn
    std::cout << "Array comparisons:\n";
    std::cout << "arr1 == arr2: " << (*arr1 == *arr2 ? "true" : "false") << std::endl;  // Anamenomeno Apotelesma: true
    std::cout << "arr1 != arr3: " << (*arr1 != *arr3 ? "true" : "false") << std::endl << std::endl;  // Anamenomeno Apotelesma: true

    // Ektypwsi apotelesmatwn sygkriseon antikeimenwn
    std::cout << "Object comparisons:\n";
    std::cout << "obj1_2 == obj2_2: " << (*obj1_2 == *obj2_2 ? "true" : "false") << std::endl;  // Anamenomeno Apotelesma: true
    std::cout << "obj1_2 != obj3_2: " << (*obj1_2 != *obj3_2 ? "true" : "false") << std::endl << std::endl;  // Anamenomeno Apotelesma: true



    return 0;
}

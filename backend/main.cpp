//
// Created by kemptonburton on 8/29/2025.
//

#include "haos.h"

int main() {

    /// SERVER SETUP ///
    std::string local_address = "127.0.0.1";

    HAOSInstance instance(local_address, 5000);

    HAOS_ON_LOOP(instance, "DACS_LOOP", [=](ThreadedLoop& threadedLoopObject) {

        std::cout << "Hello World!\n";



    });

}
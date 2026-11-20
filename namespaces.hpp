;

/*
 * Copyright 2026 Alex (alex.correu@pm.me)
 * SPDX-License-Identifier: GPL-2.0-only
 * Este programa es software libre: puedes redistribuirlo y/o modificarlo bajo los términos
 * de la Licencia Pública General GNU como publicada por la Free Software Foundation,
 * ya sea la versión 2 de la Licencia, o (a tu elección) cualquier versión posterior.
 */

// using namespace std;     //Usar el espacio estándar para los cin y cout
    using std::cin;
    using std::cout;
    using std::endl;
    using std::string;
    using std::time_t;  //Unidad para argumento de ctime(&t);
    using std::vector;
    using std::to_string;   // Convierte un entero a string(en numeros) -> int i = std::to_string(34);
    using std::stoi;        // Congierte un string(en numeros) a entero -> string s = std::stoi("34");
    // using std:system;

namespace fs = std::experimental::filesystem;
using namespace std::this_thread;   // sleep_for, sleep_until
using namespace std::chrono;        // nanoseconds, system_clock, seconds

# LinkedIn embedded projects — shareable reference source

These independent reconstructions connect two projects on Vijay's LinkedIn profile to reviewable firmware and tests. They were created on 14 October 2026 with AI development assistance. The historical prototypes' complete firmware and CAD were not recovered, so these files are not claimed to be their original production code.

| Project | Public source | Implemented scope |
|---|---|---|
| Smart Dustbin with IoT Control | [Firmware](smart_dustbin/smart_dustbin.ino), [shared controller](smart_dustbin/bin_control.h) | IR presence, delayed lid close, ultrasonic fill estimate, full indicator, JSON telemetry |
| Solar Panel Cleaning Robot | [Firmware](solar_cleaner/solar_cleaner.ino), [shared controller](solar_cleaner/cleaner_control.h) | One cleaning lane, brush/drive gating, front/rear edge handling, emergency input, 25-second watchdog, explicit fault reset |

The sketches target the **ESP32 Arduino core 3.x**. Smart-bin servo PWM uses the core's pin-based LEDC API. Copy each sketch and its matching header into a same-named Arduino sketch folder; select your actual ESP32 board before building. GPIO assignments and the active levels in the sketches are illustrative and must be checked against the sensor modules. No Arduino board build or physical hardware test was performed here.

Run the exact C++ controller code used by the sketches on a desktop:

```bash
g++ -std=c++17 -Wall -Wextra -Werror tests/test_controllers.cpp -o /tmp/vijay-controller-tests
/tmp/vijay-controller-tests
python3 telemetry_ingest.py --database /tmp/vijay-demo-telemetry.sqlite
# Optional actual serial input:
pip install pyserial
python3 telemetry_ingest.py --serial /dev/ttyUSB0
```

Telemetry is persisted to SQLite without contacting a cloud service. This package does not implement a cloud dashboard, route optimization, fleet cleaning, charger, motor-current controller or a validated fall-prevention safety system. Historical panel-efficiency percentages are not reproduced as measurements here.

Electrical integration: drive motors/brushes through appropriate motor drivers, use a separate suitably rated servo supply with shared ground, and level-shift any 5-V ultrasonic echo before connecting it to a 3.3-V ESP32 input. Start with actuators disconnected and inspect the telemetry/state outputs before bench testing.

Portfolio: https://vijaypsportfolio.vercel.app/ · LinkedIn: https://www.linkedin.com/in/vijay-ps-362a66298/

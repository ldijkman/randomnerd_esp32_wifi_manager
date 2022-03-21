import { CHIP_FAMILY_ESP32, CHIP_FAMILY_ESP32S2, CHIP_FAMILY_ESP8266, CHIP_FAMILY_ESP32C3, } from "esp-web-flasher";
export const getChipFamilyName = (esploader) => {
    switch (esploader.chipFamily) {
        case CHIP_FAMILY_ESP32:
            return "ESP32";
        case CHIP_FAMILY_ESP8266:
            return "ESP8266";
        case CHIP_FAMILY_ESP32S2:
            return "ESP32-S2";
        case CHIP_FAMILY_ESP32C3:
            return "ESP32-C3";
        default:
            return "Unknown Chip";
    }
};

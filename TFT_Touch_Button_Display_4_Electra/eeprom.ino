
// eepromsize 4096

void savetoeeprom() {                        // 0 to 100?
  for (int i = 0; i < 96; i++) {
    EEPROM.put(i, q_checkbox[i]);            // save store checkboxes state to eeprom 
  }
  EEPROM.commit();
}


void readfromeeprom() {
  for (int i = 0; i < 96; i++) {
    q_checkbox[i] = EEPROM.read(i);         // read stored checkboxes state from eeprom
  }
}
